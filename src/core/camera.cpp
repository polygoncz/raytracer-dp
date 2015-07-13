#include "camera.h"

using namespace tracer;

Camera::Camera(const Vector& eye, const Vector& target, const Vector& up, Real exposure)
    : eye(eye),
      target(target),
      up(up),
      exposure(exposure)
{
    computeUVW();
}

Camera::~Camera()
{
    if (film)
        delete film;
}

void Camera::computeUVW()
{
    w = eye - target;
    w.normalize();
    u = cross(up, w);
    u.normalize();
    v = cross(u, w);
    v.normalize();
}
