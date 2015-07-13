#pragma once

/*!
 * \file
 * V souboru jsou definovány některé pomocné funkce.
 * Dále slouží jako pomůcka pro překladač.
 */

#include <algorithm>
#include <cmath>


namespace tracer
{

/*!
 * Datovy typ realnych hodnot. Vychozi hodnota je float.
 */
typedef float Real;

/*!
 * Ořezání hodnoty pomocí intervalu <from; to> pro hodnoty zadaného typu pomocí šablony.
 * \tparam T Musí mít přetíženy operátory menší a větší (<, >)
 * \param val vstupní hodnota
 * \param from spodní hranice intervalu
 * \param to horní hranice intervalu
 * \return ořezaná hodnota zadaného typu
 */
template<class T>
inline T clamp(T val, T from, T to)
{
    if (val < from) return from;
    if (val > to) return to;

    return val;
}

/*!
 * Hledá minimum z předaných hodnot.
 * \param t1 první hodnota
 * \param t2 druhá hodnota
 * \return menší ze dvou hodnot
 */
template<class T>
inline T min(const T& t1, const T& t2)
{
    return std::min(t1, t2);
}

/*!
 * Hledá maximum z předaných hodnot.
 * \param t1 první hodnota
 * \param t2 druhá hodnota
 * \return menší ze dvou hodnot
 */
template<class T>
inline T max(const T& t1, const T& t2)
{
    return std::max(t1, t2);
}

/*!
 * Hledá maximum z nabízených hodnot.
 * \param t1 první hodnota
 * \param t2 druhá hodnota
 * \return větší ze dvou hodnot
 */
template<class T>
inline void swap(T& a, T& b)
{
    std::swap(a, b);
}

/*!
 * Prohodí dvě zadané hodnoty. Protože jsou parametry zadané jako reference, změna se projeví i vně funkce.
 * \param a reference na první hodnotu
 * \param b reference na druhou hodnotu
 */
inline Real Lerp(Real t, Real a, Real b)
{
    return (1.f - t) * a + t * b;
}

/*!
 * Funkce pro výpočet kořenů kvadratické funkce.
 * \param a první koeficient kvadratické funkce
 * \param b druhý koeficient kvadratické funkce
 * \param c třetí koeficient kvadratické funkce
 * \param t0 ukazatel na float, kam má být uložena hodnota prvního kořenu
 * \param t1 ukazatel na float, kam má být uložena hodnota druhého kořenu
 * \return vrací, zdali má rovnice řešení v oboru reálných čísel
 */
inline bool quadratic(Real a, Real b, Real c, Real* t0, Real* t1)
{
    Real disc = b * b - 4 * a * c;

    if (disc < 0.f) return false;

    Real e = std::sqrt(disc);
    Real invLowerPart = 1.f / (2.f * a);

    if (t0) *t0 = (-b + e) * invLowerPart;
    if (t1) *t1 = (-b - e) * invLowerPart;

    return true;
}

/*!
 * Převed číslo float na int spolu se zaokrouhlením.
 * \param f hodnota float, kterou chceme zaokrouhlit
 * \return zaokrouhlená hodnota typu int
 */
inline int round2Int(Real f)
{
    return static_cast<int>(f + 0.5f);
}


}
