#pragma once

#include "core/core.h"
#include "core/geometry.h"
#include "core/intersection.h"
#include "core/color.h"
#include "core/film.h"
#include "core/camera.h"
#include "core/light.h"
#include "primitive.h"

namespace tracer
{

/*!
 * Třída implementuje vykreslovanou prostorovou scénu.
 * Obsahuje atributy o barvě pozadí, světlech, objektech, kamerách atd.
 */
class Scene
{
public:
    Scene();

    ~Scene();

    /*!
	 * Vybuduje scénu podle souboru XML, který definuje scénu.
	 * Používá k tomu třídu XMLSceneImporter.
	 * \param file cesta k souboru
	 */
    void build(const char* file);

    /*!
	 * Vypočítá průsečík paprsku se scénou. Deleguje tento problém na tělesa ve scéně,
	 * nebo akcelerační struktury.
	 * \param ray paprsek se kterým je počítán průsečík
	 * \param sr reference na strukturu Intersection, kterou naplníme údaji o případném průsečíku
	 * \return jestli má paprsek průsečík s tělesem
	 */
    bool intersect(const Ray& ray, Intersection& inter) const;

    /*!
	 * Optimalizovaná verze metody Intersect(). Opět deleguje problém.
	 * \param ray paprsek se kterým je počítán průsečík
	 * \return jestli má paprsek průsečík s tělesem
	 */
    bool intersectP(const Ray& ray) const;

    /*!
	 * Získá obalový kvádr scény. Ten je vypočítán jako sjendocení obalových kvádrů
	 * všech těles ve scéně, čili jako obalový kvádr akcelerační struktury.
	 * \return Obalový kvádr scény.
	 */
    BBox bounds() const;

public:
    RGBColor background; ///< Barva pozadí.
    Light* ambient;
    std::vector<Light*> lights;
    Film* film;
    Camera* camera;
    AccelerationStructure* aggregator;
};

}