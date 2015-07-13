#pragma once

#include "core/color.h"
#include "core/core.h"
#include "core/intersection.h"
#include "core/reference.h"
#include "core/brdf.h"

#include <cstdint>

#define MAX_BXDFS 8

namespace tracer
{

/*!
 * Třída reprezentuje sadu BRDF funkcí tvořící povrch.
 * BRDF funkce tak mohou být mezi sebou libovolně míchány.
 */
class BSDF
{
public:
    /*!
     * Bezparametrický konstruktor.
     */
    BSDF();

    /*!
     * Dektruktor. Vymaže vytvořené BRDF z paměti.
     */
    ~BSDF();

    /*!
     * Přidá do pole BRDF funkcí další ukazatel na objekt typu BxDF resp. jeho potomka.
     * Kontroluje, jestli nebyla přesáhnuta velikost pole.
     * \param bxdf ukazatel na BRDF funkci
     */
    void add(BxDF* bxdf);

    /*!
     * Metoda vrací aktuální počet BRDF komponent v poli.
     * \return počet BRDF komponent
     */
    size_t numComponents() const;

    /*!
     * Přetížení operátoru přístupu. Poskytuje přístup k poli,
     * kde jsou uložené BRDF komponenty. Kontroluje přetečení
     * přes jejich aktuální počet.
     * \param i index položky
     * \return ukazatel na BRDF funkci
     */
    BxDF* operator[](int i) const;

private:
    BxDF* bxdfs[MAX_BXDFS]; ///< statické pole pro uchování ukazatelů na BRDF komponenty. Jeho velikost odpovídá konstantě MAX_BRDFS.
    size_t nBxDFs; ///< aktuální počet uložených BRDF komponent.
};

/*!
 * Rozhraní, které definuje metody, které musejí implementovat konkrétní materiály.
 * Třída Material dědí z třídy ReferenceCounted, takže může být předávána pomocí
 * instance třídy Reference<Material>.
 */
class Material : public ReferenceCounted
{
public:
    /*!
     * Bezparametrický konstruktor.
     */
    Material();

    /*!
     * Kopírovací konstruktor.
     * \param material kopírovaná instance
     */
    Material(const Material& material);

    /*!
     * Virtuální destruktor.
     */
    virtual ~Material();

    /*!
     * Metoda vytvoří na haldě objekt ::BSDF, který reprezentuje povrch pomocí sady BRDF funkcí.
     * Jako parametry je předávána normála a směr paprsku, kvůli výpočtům jako jsou
     * Fresnelovy rovnice.
     * \param normal normála v místě dopadu
     * \param incident směr paprsku
     * \return objekt BSDF reprezentující povrch pomocí BRDF funkcí
     */
    virtual BSDF* getBSDF(const Vector& normal, const Vector& incident) const = 0;
};

/*!
 * Pomocná funkce, která vypočítá reflektanci pomocí Fresnelových rovnic.
 * \param normal normála v místě dopadu
 * \param incident směr paprsku
 * \param n1 index lomu prvního prostředí
 * \param n2 index lomu druhého prostředí
 * \return reflaktanci v místě dopadu
 */
Real fresnelReflectance(const Vector& normal, const Vector& incident, Real n1, Real n2);

/*!
 * Pomocná funkce, která vypočítá reflektanci pomocí Schlickovi aproximace Fresnelových rovnic.
 * \param normal normála v místě dopadu
 * \param incident směr paprsku
 * \param n1 index lomu prvního prostředí
 * \param n2 index lomu druhého prostředí
 * \return reflaktanci v místě dopadu
 */
Real schlickReflectance(const Vector& normal, const Vector& incident, Real n1, Real n2);

}