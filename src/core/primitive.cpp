#include "primitive.h"

using namespace tracer;

Primitive::Primitive()
{ }

Primitive::~Primitive()
{ }

GeometricPrimitive::GeometricPrimitive(const Reference<Material>& mat)
    : _material(mat)
{ }

GeometricPrimitive::GeometricPrimitive(const GeometricPrimitive& prim)
    : _material(prim.material())
{ }

GeometricPrimitive::~GeometricPrimitive()
{ }

Reference<Material> GeometricPrimitive::material() const
{
    return _material;
}

void GeometricPrimitive::setMaterial(const Reference<Material>& m)
{
    _material = m;
}
