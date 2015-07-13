#include "renderer.h"

using namespace tracer;

Renderer::Renderer(Scene* sc)
    : scene(sc)
{
    cam = scene->camera;
    film = scene->film;
}

Renderer::~Renderer()
{
    if (scene)
    {
        delete scene;
        scene = nullptr;
    }
}
