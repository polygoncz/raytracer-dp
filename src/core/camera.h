#pragma once

/*!
 * \file
 */

#include "core/core.h"

#include "core/geometry.h"
#include "core/film.h"

namespace tracer
{

/*!
 * Struktura která, určuje polohu vzorku na filmu kamery.
 * Počítáno dle zvyklostí od levého horního rohu.
 */
struct CameraSample
{
    Real x, y;
};

typedef CameraSample Pixel; ///< sémantika

/*!
 * Bázová třída kamery. Hlavní schopností je generování paprsku
 * na základě polohy vzorku na filmu.
 */
class Camera
{
public:
    Camera() = delete;

    /*!
     * Konstruktor.
     * \param eye bod pozorovatele
     * \param target cíl pozorování
     * \param up vektor natočení
     * \param exposure expozice (FUTURE)
     */
    Camera(const Vector& eye, const Vector& target, const Vector& up,
           Real exposure = 1.f);

    /*!
     * Virtuální destruktor.
     */
    virtual ~Camera();

    /*!
     * Na základě zadaných parametrů v podobě vzorku na filmu kamery vypočítá
     * odpovídající transformovaný paprsek. Implementace je potom provedena
     * v potomcích třídy.
     * \param sample vzorek na filmu kamery
     * \param ray ukazatel na instanci třídy Ray, slouží jako návratová hodnota
     */
    virtual void generateRay(const Pixel& sample, Ray* ray) const = 0;

protected:
    /*!
     * Výpočet ortonormální báze pohledu.
     */
    void computeUVW();

protected:
    Film* film; ///< Ukazatel na film.
    Vector eye; ///< Bod pozorovatele.
    Vector target; ///< Bod cíle pozorování.
    Vector up; ///< Vektor natočení kamery.
    Vector u; ///< Vektor ortonormální báze pohledu
    Vector v; ///< Vektor ortonormální báze pohledu
    Vector w; ///< Vektor ortonormální báze pohledu
    Real exposure; ///< expozice (FUTURE)
};

}