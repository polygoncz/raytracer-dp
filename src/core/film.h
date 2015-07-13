#pragma once

#include "core.h"

namespace tracer
{

/*!
 * Třída Film reprezentuje film v kameře. Narozdíl od klasického filmu v reálném světě,
 * tento uchovává takové atributy, které jsou potom využitelné pro práci s počítačovou grafikou.
 */
class Film
{
public:
    Film() = delete;

    /*!
     * Kopírovací konstruktor.
     * @param plane kopírovaná instance
     */
    Film(const Film& film);

    /*!
     * Parametrický konstruktor.
     * \param width výška v pixelech
     * \param height šířka v pixelech
     * \param size velikost pixelu ve scéně
     * \param gamma gamma obrázku
     * \param invGamma inverzní gamma pro zjednodušení operace dělení
     */
    Film(int width, int height, Real size, Real gamma = 1.f, Real invGamma = 1.f);

    /*!
     * Destruktor
     */
    ~Film();

public:
    int width; ///< výška v pixelech
    int height; ///< šířka v pixelech
    float size; ///< velikost pixelu ve scéně
    float gamma; ///< gamma obrázku
    float invGamma; ///< inverzní gamma pro zjednodušení operace dělení
};

}
