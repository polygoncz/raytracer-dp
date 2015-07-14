#include "acceleration/grid.h"

#include <string.h>


using namespace tracer;

/************************************************************************/
/* Voxel methods                                                        */
/************************************************************************/

Voxel::Voxel()
{ }

Voxel::Voxel(Reference<Primitive>& p)
{
    primitives.push_back(p);
}


void Voxel::addPrimitive(Reference<Primitive>& p)
{
    primitives.push_back(p);
}

bool Voxel::intersect(const Ray& ray, Intersection& inter) const
{
    for (size_t i = 0; i < primitives.size(); ++i)
        primitives[i]->intersect(ray, inter);

    return inter.hitObject;
}

bool Voxel::intersectP(const Ray& ray) const
{
    for (size_t i = 0; i < primitives.size(); ++i)
        if (primitives[i]->intersectP(ray))
            return true;

    return false;
}

/************************************************************************/
/* Grid methods                                                         */
/************************************************************************/

Grid::Grid(std::vector<Reference<Primitive> >& p)
{
    for (size_t i = 0; i < p.size(); ++i)
        if (p[i]->canIntersect())
            primitives.push_back(p[i]);
        else
            p[i]->refine(primitives);

    for (size_t i = 0; i < primitives.size(); ++i)
        m_bounds = unite(m_bounds, primitives[i]->bounds());

    Vector delta = m_bounds.diagonal();
    int maxAxis = m_bounds.maxDimensionIndex();
    Real invMaxWidth = 1.f / delta[maxAxis];
    Real root = 3.f * std::pow(static_cast<float>(primitives.size()), 1.f / 3.f);
    Real voxelPerUnit = root * invMaxWidth;

    for (int axis = 0; axis < 3; ++axis)
    {
        nVoxels[axis] = static_cast<size_t>(round2Int(delta[axis] * voxelPerUnit));
        nVoxels[axis] = clamp(nVoxels[axis], 1, MAX_VOXELS);
    }

    nv = nVoxels[0] * nVoxels[1] * nVoxels[2];

    for (int axis = 0; axis < 3; ++axis)
    {
        width[axis] = delta[axis] / nVoxels[axis];
        invWidth[axis] = (width[axis] == 0.f) ? 0.f : 1.f / width[axis];
    }

    voxels = new Voxel* [nv];
    memset(voxels, 0, nv * sizeof(Voxel*));

    for (size_t i = 0; i < primitives.size(); ++i)
    {
        BBox pb = primitives[i]->bounds();
        size_t vmin[3], vmax[3];
        for (int axis = 0; axis < 3; ++axis)
        {
            vmin[axis] = posToVoxel(pb.pMin, axis);
            vmax[axis] = posToVoxel(pb.pMax, axis);
        }

        for (size_t x = vmin[0]; x <= vmax[0]; ++x)
        {
            for (size_t y = vmin[1]; y <= vmax[1]; ++y)
            {
                for (size_t z = vmin[2]; z <= vmax[2]; ++z)
                {
                    size_t o = offset(x, y, z);
                    if (!voxels[o])
                        voxels[o] = new Voxel(primitives[i]);
                    else
                        voxels[o]->addPrimitive(primitives[i]);
                }
            }
        }
    }
}

Grid::~Grid()
{

}

bool Grid::intersect(const Ray& ray, Intersection& sr)
{
    Real rayT = 0.f;
    if (m_bounds.isInside(ray(ray.mint)))
        rayT = ray.mint;
    else if (!m_bounds.intersectP(ray, &rayT, nullptr))
        return false;
    Vector gridIntersect = ray(rayT);

    Real nextCrossingT[3], deltaT[3];
    size_t pos[3];
    int step[3], out[3];
    for (int axis = 0; axis < 3; ++axis)
    {
        pos[axis] = posToVoxel(gridIntersect, axis);
        if (ray.d[axis] >= 0)
        {
            nextCrossingT[axis] = rayT + (voxelToPos((int) (pos[axis] + 1), axis) - gridIntersect[axis]) / ray.d[axis];
            deltaT[axis] = width[axis] / ray.d[axis];
            step[axis] = 1;
            out[axis] = (int) nVoxels[axis];
        }
        else
        {
            nextCrossingT[axis] = rayT + (voxelToPos((int) pos[axis], axis) - gridIntersect[axis]) / ray.d[axis];
            deltaT[axis] = -width[axis] / ray.d[axis];
            step[axis] = -1;
            out[axis] = -1;
        }
    }

    bool hitSomething = false;
    while (true)
    {
        Voxel* voxel = voxels[offset(pos[0], pos[1], pos[2])];
        if (voxel)
            hitSomething |= voxel->intersect(ray, sr);

        int bits = ((nextCrossingT[0] < nextCrossingT[1]) << 2) +
                   ((nextCrossingT[0] < nextCrossingT[2]) << 1) +
                   ((nextCrossingT[1] < nextCrossingT[2]));
        const int cmpToAxis[8] = {2, 1, 2, 1, 2, 2, 0, 0};
        int stepAxis = cmpToAxis[bits];
        if (ray.maxt < nextCrossingT[stepAxis])
            break;
        pos[stepAxis] += step[stepAxis];
        if (pos[stepAxis] == out[stepAxis])
            break;
        nextCrossingT[stepAxis] += deltaT[stepAxis];
    }

    return hitSomething;
}

bool Grid::intersectP(const Ray& ray)
{
    Real rayT = 0.f;
    if (m_bounds.isInside(ray(ray.mint)))
        rayT = ray.mint;
    else if (!m_bounds.intersectP(ray, &rayT, nullptr))
        return false;
    Vector gridIntersect = ray(rayT);

    Real nextCrossingT[3], deltaT[3];
    size_t pos[3];
    int step[3], out[3];
    for (int axis = 0; axis < 3; ++axis)
    {
        pos[axis] = posToVoxel(gridIntersect, axis);
        if (ray.d[axis] >= 0)
        {
            nextCrossingT[axis] = rayT + (voxelToPos((int) (pos[axis] + 1), axis) - gridIntersect[axis]) / ray.d[axis];
            deltaT[axis] = width[axis] / ray.d[axis];
            step[axis] = 1;
            out[axis] = (int) nVoxels[axis];
        }
        else
        {
            nextCrossingT[axis] = rayT + (voxelToPos((int) pos[axis], axis) - gridIntersect[axis]) / ray.d[axis];
            deltaT[axis] = -width[axis] / ray.d[axis];
            step[axis] = -1;
            out[axis] = -1;
        }
    }

    while (true)
    {
        Voxel* voxel = voxels[offset(pos[0], pos[1], pos[2])];
        if (voxel && voxel->intersectP(ray))
            return true;

        int bits = ((nextCrossingT[0] < nextCrossingT[1]) << 2) +
                   ((nextCrossingT[0] < nextCrossingT[2]) << 1) +
                   ((nextCrossingT[1] < nextCrossingT[2]));
        const int cmpToAxis[8] = {2, 1, 2, 1, 2, 2, 0, 0};
        int stepAxis = cmpToAxis[bits];
        if (ray.maxt < nextCrossingT[stepAxis])
            break;
        pos[stepAxis] += step[stepAxis];
        if (pos[stepAxis] == out[stepAxis])
            break;
        nextCrossingT[stepAxis] += deltaT[stepAxis];
    }

    return false;
}

BBox Grid::bounds() const
{
    return m_bounds;
}
