#pragma once

#include "core/color.h"
#include "core/film.h"
#include "core/camera.h"
#include "core/scene.h"
#include "core/integrator.h"

namespace tracer
{

/*!
 * Rozhraní Renderer implementují ti potomci, kteří se starají
 * o implementaci samotné renderovací smyčky a vypočítané
 * výsledky potom odesílají k dalšímu zpracování.
 */
class Renderer
{
public:
    /*!
     * Nastavuje scénu. Také ze scény vytáhne ukazatele na Film a Camera
     * pro přehlednější přístup k nim.
     * \param sc scéna která se bude renderovat.
     */
    Renderer(Scene* sc);

    /*!
     * Destruktor se volá při dokončení vykreslování. Maže po sobě scénu.
     */
    virtual ~Renderer();

    /*!
     * Slouží ke spuštění renderingu.
     */
    virtual void render() const = 0;

protected:
    Scene* scene; ///< Vykreslovaná scéna.
    Film* film; ///< Film kamery vytáhnutý ze scene, kvůli přehlednému přístupu.
    Camera* cam; ///< Kamera vytáhnutá ze scene, kvůli přehlednému přístupu.
};


}