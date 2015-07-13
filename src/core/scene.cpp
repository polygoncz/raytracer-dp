#include <stdexcept>
#include "scene.h"

using namespace tracer;

Scene::Scene()
    : background(WHITE),
      ambient(nullptr),
      film(nullptr),
      camera(nullptr),
      aggregator(nullptr)
{ }

Scene::~Scene()
{
    for (size_t i = 0; i < lights.size(); ++i)
        if (lights[i]) delete lights[i];
    lights.clear();

    if (film) delete film;
    if (ambient) delete ambient;
    if (camera) delete camera;
    if (aggregator) delete aggregator;
}

BBox Scene::bounds() const
{
    return aggregator->bounds();
}

bool Scene::intersect(const Ray& ray, Intersection& inter) const
{
    return aggregator->intersect(ray, inter);
}

bool Scene::intersectP(const Ray& ray) const
{
    return aggregator->intersectP(ray);
}

void Scene::build(const char* file)
{
    throw std::runtime_error("Not implemented yet.");
}
