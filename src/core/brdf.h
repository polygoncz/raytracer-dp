#pragma once

#include "core/color.h"
#include "core/core.h"
#include "core/geometry.h"
#include "core/intersection.h"

namespace tracer
{

/*!
 * Výčtový typ, který slouží pro indentifikaci typu BRDF. Podle typu s ním lze potom odlišně pracovat.
 */
enum BxDFType
{
    BSDF_REFLECTION = 1 << 0,
    BSDF_TRANSMISSION = 1 << 1,
    BSDF_DIFFUSE = 1 << 2,
    BSDF_SPECULAR = 1 << 3,
    BSDF_AMBIENT = 1 << 4
};

/*!
 * Bázová třída, která představuje objekt obousměrné odrazové distribuční funkce (BRDF).
 */
class BxDF
{
public:
    /*!
	 * Bázový konstruktor, který nastavuje typ funkce.
	 * \param t typ funkce typu výčtu BxDFType
	 * \see BxDFType
	 */
    BxDF(BxDFType t);

    /*!
	 * Kopírovací kontruktor
	 * @param brdf kopírovaná instance
	 */
    BxDF(const BxDF& bxdf);

    /*!
	 * Virtuální destruktor
	 */
    virtual ~BxDF();

    /*!
	 * Metoda slouží k výpočtu světelného příspěvku, na základě zadaných hodnot.
	 * \param wi vektoru směrem od světla
	 * \parma wo vektoru směrem k pozorovateli
	 * \param n normála v bodě dopadu
	 * \return velikost světelného příspěvku
	 */
    virtual RGBColor f(const Vector& wi, const Vector& wo, const Vector& n) const = 0;

    /*!
	 * Metoda vypočítává hodnotu hodnotu odraženého resp. lomeného paprsku.
	 * Návrácená hodnota typu RGBColor potom slouží k určení, jaká část
	 * barevného spektra je odražena resp. propuštěna.
	 * \param wi zpravidla vektor směru od pozorovatele
	 * \param wo slouží k návratu vypočteného vektoru
	 * \param n normála v bodě dopadu
	 * \return barevná hodnota, sloužící k filtrování spektra
	 */
    virtual RGBColor sampleF(const Vector& wi, Vector& wo, const Vector& n) const = 0;

    /*!
	 * Slouží pro výpočty s globálním osvětlením. PREPARE FOR FUTURE :-)
	 */
    virtual RGBColor rho(const Vector& wi, const Vector& wo, const Vector& n) const = 0;

    /*!
	 * Porovnává, jestli BRDF funkce odpovídá zadanému typu BxDFType.
	 * \param flags porovnávané typy
	 * \see BxDFType
	 * \return true/false
	 */
    bool typeMatched(BxDFType flags) const;

private:
    BxDFType type;
};

}
