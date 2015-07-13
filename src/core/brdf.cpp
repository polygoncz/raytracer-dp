#include "brdf.h"

using namespace tracer;

BxDF::BxDF(BxDFType t)
    : type(t)
{ }


BxDF::BxDF(const BxDF& bxdf)
    : type(bxdf.type)
{ }

BxDF::~BxDF()
{ }

bool BxDF::typeMatched(BxDFType flags) const
{
    return (type & flags) == type;
}
