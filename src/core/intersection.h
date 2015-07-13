#pragma once

#include "core/core.h"
#include "core/reference.h"


namespace tracer
{

/*!
 * Třída uchovává atributy, které představují souhrn
 * informací o průsečíku paprsku s objektem ve scéně.
 * Všechny její atributy jsou veřejné.
 */
struct Intersection
{
    Intersection()
        : hitObject(false),
          material(nullptr),
          depth(0),
          t(INFINITY)
    { }

    Intersection(const Intersection& i)
        : hitObject(i.hitObject),
          hitPoint(i.hitPoint),
          normal(i.normal),
          ray(i.ray),
          material(i.material),
          depth(i.depth),
          t(i.t)
    { }

    bool hitObject; ///< protnul paprsek objekt?
    Vector hitPoint; ///< Souřadnice místa dopadu
    Vector normal; ///< Normála v místě dopadu
    Ray ray; ///< Paprsek, pro který se provádí výpočet
    Reference<Material> material; ///< Reference na materiál objektu
    int depth; ///< Hloubka rekurze
    float t; ///< hodnota parametru t v místě dopadu
};

}