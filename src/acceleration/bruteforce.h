#pragma once

#include <vector>

#include "core/primitive.h"

namespace tracer
{

/*!
 * Akcelerační struktura provádí výpočet průsečíku s každým tělesem scény.
 */
class BruteForce : public AccelerationStructure
{
public:
    /*!
	 * Vytvoří instanci se zadanými tělesy.
	 * \param p std::vector s tělesy.
	 */
    BruteForce(std::vector<Reference<Primitive>>& p);

    virtual ~BruteForce();

    /*! \copydoc Primitive::intersect() */
    virtual bool intersect(const Ray& ray, Intersection& inter) override;

    /*! \copydoc Primitive::intersectP() */
    virtual bool intersectP(const Ray& ray) override;

    /*! Vypočítá obalovou krychli kolem všech svých těles. */
    virtual BBox bounds() const override;

private:
    /*!
	 * std::vector obsahující tělesa.
	 */
    mutable std::vector<Reference<Primitive>> primitives;
};

}
