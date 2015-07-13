#pragma once

#include "core/core.h"
#include "core/geometry.h"
#include "core/color.h"
#include "core/intersection.h"

namespace tracer
{

/*!
 * Rozhraní pro objekty světel. Je možné z nich získat intezitu osvětlení daného bodu
 * a směr k danému bodu.
 */
class Light
{
public:
    /*!
	 * Bezparametrický konstruktor.
	 */
    Light();

    /*!
	 * Kopírovací konstruktor.
	 * \param light kopírovaná instance
	 */
    Light(const Light& light);

    /*!
	 * Virtuální destruktor
	 */
    virtual ~Light();

    /*!
	 * Vypočítá směr světla vzhledme k místu průsečíku.
	 * \param sr informace o průsečíku
	 * \return Vector směru světla
	 */
    virtual Vector direction(const Intersection& inter) const = 0;

    /*!
	 * Provede výpočet světelného příspěvku světla pro průsečík.
	 * \param sr informace o průsečíku
	 * \return hodnota světelného příspěvku
	 */
    virtual RGBColor l(const Intersection& inter) const = 0;
};

}