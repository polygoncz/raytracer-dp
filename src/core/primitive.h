#pragma once

#include <vector>

#include "core/geometry.h"
#include "core/material.h"
#include "core/intersection.h"
#include "core/reference.h"

namespace tracer
{

/*!
 * Rozhraní, které musí implementovat tělesa ve scéně.
 * Třída Primitive dědí z třídy ReferenceCounted, takže může být předávána pomocí
 * instance třídy Reference<Primitive>.
 */
class Primitive : public ReferenceCounted
{
public:
    Primitive();

    virtual ~Primitive();

    /*!
     * Zjistí, zdali má paprsek průsečík s tělesem a naplní strukturu ::Intersection.
     * Používá se při výpočtech s primárními a sekundárními paprsky.
     * @param ray paprsek se kterým je počítán průsečík
     * @param sr reference na strukturu Intersection, kterou naplníme údaji o případném průsečíku
     * @return jestli má paprsek průsečík s tělesem
     */
    virtual bool intersect(const Ray& ray, Intersection& sr) = 0;

    /*!
     * Zjistí, zdali má paprsek průsečík s tělesem. Metoda je oproštěna od dodatečných výpočtů.
     * Používá se při výpočtech se stínovými paprsky.
     * \param ray paprsek se kterým je počítán průsečík
     * \return jestli má paprsek průsečík s tělesem
     */
    virtual bool intersectP(const Ray& ray) = 0;

    /*!
     * Metoda vrací, zdali je těleso schopné provést výpočet průsečíku s paprskem.
     * Pokud toho schopné není, je třeba implementovat metodu @a Primitive::Refine(vector<Reference<Primitive> > &),
     * která zajistí rozklad na taková tělesa, která toho schopná jsou.
     * \see Primitive::Refine(vector<Reference<Primitive> > &)
     * \return jestli je možné vypočítat průsečík paprsek-těleso
     */
    virtual bool canIntersect() const = 0;

    /*!
     * Rozdělí objekt na jednodušší tělesa. Využívá se spolu s metodou @a CanIntersect().
     * \param refined reference na std::vector do kterého budou vkládána nová tělesa
     * \see CanIntersect()
     * \see Reference<Primitive>
     */
    virtual void refine(std::vector<Reference<Primitive>>& refined) = 0;

    /*!
     * Vrátí vypočítanou obalovou krychli tělesa.
     * \return instanci BBox představující obalovou krychli
     */
    virtual BBox bounds() const = 0;
};

/**
 * Bázová třída pro objekty, které představují geomettrická tělesa.
 * Implementuje metody pro práci s materiály.
 */
class GeometricPrimitive : public Primitive
{
public:
    /*!
     * Kontruktor s parametrem materiálu.
     * \param _mat materiál nového tělesa
     */
    GeometricPrimitive(const Reference<Material>& mat);

    /*!
     * Kopírovací konstruktor
     * \param prm kopírovaná instance
     */
    GeometricPrimitive(const GeometricPrimitive& prm);

    /*!
     * Virtuální konstruktor.
     */
    virtual ~GeometricPrimitive();

    /*!
     * Získá materiál tělesa.
     * \return Reference na Material tělesa
     */
    Reference<Material> material() const;

    /*!
     * Nastaví materiál tělesa.
     * \param _material nově nastavený materiál
     */
    void setMaterial(const Reference<Material>& m);

protected:
    mutable Reference<Material> _material; ///< Materiál tělesa.
};

/*!
 * Třída vznikla ze sémantických důvodů jako předek tříd pro implementaci
 * akceleračních struktur.
 */
class AccelerationStructure : public Primitive
{
public:
    /*!
     * Všechny akcelerační struktury dokáží vypočítat průsečík s tělesem.
     * \return true
     */
    virtual bool canIntersect() const
    { return true; }

    /*!
     * Vzhledem k implementaci funkce CanIntersect() není třeba mít
     * implementovanou tuto metodu. Aby náhodou nedošlo ke kopírování
     * struktury, tak je metoda reimplementována tak aby nic nedělala.
     */
    virtual void refine(std::vector<Reference<Primitive>>& refined)
    { return; }
};

}