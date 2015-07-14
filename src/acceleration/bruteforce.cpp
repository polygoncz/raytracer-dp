#include "bruteforce.h"

using namespace tracer;

/*!
 * Nad každým tělesem zkusí provést Primitive::Refine() tak,
 * aby bylo možné s každým tělesem provést výpočet průsečíku.
 */
BruteForce::BruteForce(std::vector<Reference<Primitive>>& p)
{
    for (size_t i = 0; i < p.size(); ++i)
    {
        if (!p[i]->canIntersect())
            p[i]->refine(primitives);
        else
            primitives.push_back(p[i]);
    }
}

BruteForce::~BruteForce()
{ }

bool BruteForce::intersectP(const Ray& ray)
{
    for (size_t i = 0; i < primitives.size(); ++i)
        if (primitives[i]->intersectP(ray))
            return true;

    return false;
}

bool BruteForce::intersect(const Ray& ray, Intersection& inter)
{
    for (size_t i = 0; i < primitives.size(); ++i)
        primitives[i]->intersect(ray, inter);

    return inter.hitObject;
}

BBox BruteForce::bounds() const
{
    BBox b;
    for (size_t i = 0; i < primitives.size(); ++i)
        unite(b, primitives[i]->bounds());
    return b;
}