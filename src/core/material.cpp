#include "material.h"

using namespace tracer;

/************************************************************************/
/* BSDF methods                                                         */
/************************************************************************/

BSDF::BSDF()
{
    nBxDFs = 0;
}

BSDF::~BSDF()
{
    for (size_t i = 0; i < nBxDFs; ++i)
    {
        if (bxdfs[i]) delete bxdfs[i];
    }
}

void BSDF::add(BxDF* bxdf)
{
    assert(nBxDFs < MAX_BXDFS);
    bxdfs[nBxDFs++] = bxdf;
}

size_t BSDF::numComponents() const
{
    return nBxDFs;
}

BxDF* BSDF::operator[](int i) const
{
    assert(i < nBxDFs);
    return bxdfs[i];
}

/************************************************************************/
/* Material methods                                                     */
/************************************************************************/

Material::Material()
{ }

Material::Material(const Material& material)
{ }

Material::~Material()
{ }

/************************************************************************/
/* Helper functions                                                     */
/************************************************************************/
Real fresnelReflectance(const Vector& normal, const Vector& incident, Real n1, Real n2)
{
    const Real n = n1 / n2;
    const Real cosI = -dot(normal, incident);
    const Real sinT2 = n * n * (1.f - cosI * cosI);
    if (sinT2 > 1.f) return 1.f;
    const Real cosT = std::sqrt(1.f - sinT2);

    Real rs = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
    rs *= rs;

    Real rp = (n1 * cosT - n2 * cosI) / (n1 * cosT + n2 * cosT);
    rp *= rp;

    return (rs + rp) * 0.5f;
}

Real schlickReflectance(const Vector& normal, const Vector& incident, Real n1, Real n2)
{
    Real r0 = (n1 - n2) / (n1 + n2);
    r0 *= r0;
    Real cosI = -dot(normal, incident);
    if (n1 > n2)
    {
        const Real n = n1 / n2;
        const Real sinT2 = n * n * (1.f - cosI * cosI);
        if (sinT2 > 1.f) return 1.f;
        cosI = std::sqrt(1.f - sinT2);
    }
    const Real x = 1.f - cosI;
    return r0 + (1.f - r0) * x * x * x * x * x;
}