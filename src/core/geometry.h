#pragma once

#include <assert.h>

#include "core/core.h"

namespace tracer
{

/*!
 * Trida trojrozmerneho vektoru.\n
 * Umoznuje provadet s vektorem základní matematické operace jako scitani,
 * odcitani, nasobeni konstantou, deleni konstantou, zjistovat jeho delku
 * a provadet jeho normalizaci.
 * \author Pavel Lokvenc
 */
class Vector
{
public:

    /*!
     * Defaultni konstruktor. \n
     * Vsechny slozky maji hodnotu 0.
     */
    Vector()
            : x(0.f), y(0.f), z(0.f)
    {
    }

    /*!
     * Konstruktor
     * \param _x hodnota slozky x
     * \param _y hodnota slozky y
     * \param _z hodnota slozky z
     */
    Vector(Real _x, Real _y, Real _z)
            : x(_x), y(_y), z(_z)
    {
    }

    /*!
     * Kopirovaci konstruktor
     * \param v vektor urceny ke kopirovani
     */
    Vector(const Vector& v)
            : x(v.x), y(v.y), z(v.z)
    {
    }

    /*!
     * Vypocet delky vektoru.
     * \return delka vektoru.
     */
    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    /*!
     * Vypocet druhe mocniny delky vektoru
     * \return delka na druhou.
     */
    float squarredLenght() const
    {
        return x * x + y * y + z * z;
    }

    /*!
     * Normalizuje dany vektor. Vyuzito fluent interface.
     * \return normalizovany vektor.
     */
    Vector normalize()
    {
        float lengthInv = 1.f / length();

        x *= lengthInv;
        y *= lengthInv;
        z *= lengthInv;

        return *this;
    }

    /*!
     * Pretizeni unarniho operatoru +.
     * \return hodnotu objektu (Vector).
     */
    const Vector& operator+() const
    {
        return *this;
    }

    /*!
     * Pretizeni unarniho operatoru -.
     * \return novy objekt tridy Vector
     */
    Vector operator-() const
    {
        return Vector(-x, -y, -z);
    }

    /*!
     * Pretizeni operatoru rovnosti (==).
     * Porovnavaji se jednotlive slozky.
     * \param v objekt tridy vektor, se kterym porovnavame.
     * \return true/false
     */
    bool operator==(const Vector& v)
    {
        return x == v.x && y == v.y && z == v.z;
    }

    /*!
     * Pretizeni operatoru nerovnosti (!=)
     * Porovnavaji se jednotlive slozky.
     * \param v objekt tridy vektor, se kterym porovnavame.
     * \return true/false
     */
    bool operator!=(const Vector& v)
    {
        return x != v.x || y != v.y || z != v.z;
    }

    /*!
     * Pretizeni operatoru scitani (+).
     * Scitaji se jednotlive slozky.
     * \param v objekt tridy Vector, ktery chceme pricist
     * \return novy objekt typu Vector
     */
    Vector operator+(const Vector& v) const
    {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    /*!
     * Pretizeni operatoru +=
     * Scitaji se jednotlive slozky.
     * \return reference na this
     */
    Vector& operator+=(const Vector& v)
    {
        *this = *this + v;
        return *this;
    }

    /*!
     * Pretizeni operatoru odcitani (-).
     * Odcitaji se jednotlive slozky.
     * \param v objekt tridy Vector, ktery chceme odecist
     * \return novy objekt typu Vector
     */
    Vector operator-(const Vector& v) const
    {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    /*!
     * Pretizeni operatoru -=
     * Odcitaji se jednotlive slozky.
     * \return reference na this
     */
    Vector& operator-=(const Vector& v)
    {
        *this = *this - v;
        return *this;
    }

    /*!
     * Pretizeni operatoru deleni (/).
     * Osetreno deleni 0 pomoci makra assert z <assert.h>.
     * \see assert()
     * \param k hodnota kterou chceme delit vsechny slozky.
     * \return novy objekt tridy Vector
     */
    Vector operator/(Real k) const
    {
        assert(k != 0);
        float invK = 1.f / k;
        return Vector(x * invK, y * invK, z * invK);
    }

    /*!
     * Pretizeni operatoru deleni (/=).
     * Osetreno deleni 0 pomoci makra assert z <assert.h>.
     * \see assert()
     * \param k hodnota kterou chceme delit vsechny slozky.
     * \return reference na this
     */
    Vector& operator/=(Real k)
    {
        assert(k != 0);
        float invK = 1.f / k;

        x *= invK;
        y *= invK;
        z *= invK;

        return *this;
    }

    /*!
     * Pretizeni operatoru nasobeni (*).
     * Nasobime vsechny slozky konstantou.
     * \param k konstanta pro nasobeni.
     * \return novy objekt typu Vector
     */
    Vector operator*(Real k) const
    {
        return Vector(x * k, y * k, z * k);
    }

    /*!
     * Pretizeni operatoru nasobeni (*).
     * Nasobime vsechny slozky konstantou zleva.
     * \param k konstanta pro nasobeni.
     * \param v vektor, ktery chceme nasobit.
     * \return novy objekt typu Vector
     */
    friend Vector operator*(Real k, const Vector& v)
    {
        return Vector(v.x * k, v.y * k, v.z * k);
    }

    /*!
     * Pretizeni operatoru nasobeni (*).
     * Nasobime vsechny slozky konstantou.
     * \param k konstanta pro nasobeni.
     * \return reference na this
     */
    Vector& operator*=(Real k)
    {
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    /*!
     * Pretizeni operatoru prirazeni (=).
     * \param v vektor, jehoz hodnotu chceme priradit.
     * \return reference na this
     */
    Vector& operator=(const Vector& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    /*!
     * Pretizeni operatoru pro pristup do pole ([]).
     * Pomoci makra assert z <assert.h> osetren rozsah v intervalu (0; 2).
     * Vyuzito vlastnosti, ze prekladace radi promenne "za sebe", takze lze k nim pristupovat jako k poli.
     * \param i index v intervalu (0; 2).
     * \return hodnotu x resp. y,z dle vstupniho parametru.
     */
    Real operator[](int i) const
    {
        assert(i >= 0 && i <= 2);
        return (&x)[i];
    }

    /*!
     * Pretizeni operatoru pro pristup do pole ([]).
     * Pomoci makra assert z <assert.h> osetren rozsah v intervalu (0; 2).
     * Vyuzito vlastnosti, ze prekladace radi promenne "za sebe", takze lze k nim pristupovat jako k poli.
     * \param i index v intervalu (0; 2).
     * \return hodnotu x resp. y,z dle vstupniho parametru.
     */
    Real& operator[](int i)
    {
        assert(i >= 0 && i <= 2);
        return (&x)[i];
    }

    /*! hodnota slozky vektoru x */
    Real x;
    /*! hodnota slozky vektoru y */
    Real y;
    /*! hodnota slozky vektoru z */
    Real z;
};

/*!
 * Třída reprezentuje parpsek(polopřímku) v prostoru.\n
 * Vychází z parametrické rovnice přímky.
 */
class Ray
{
public:
    /*!
     * Bezparametrický konstruktor.
     */
    Ray()
            : mint(0.f), maxt(INFINITY), rayEpsilon(EPSILON), depth(0)
    { }

    /*!
     * Konstruktor
     * \param _o počátek paprsku
     * \param _d směr paprsku
     * \param start minimální hodnota parametru t
     * \param end maximální hodnota parametru t
     * \param eps hodnota epsilon pro eliminaci chyb při výpočtech s desetinnou čárkou
     * \param _depth hloubka rekurze
     */
    Ray(const Vector& _o, const Vector& _d, float start = 0.f, float end =
    INFINITY, float eps = EPSILON, int _depth = 0)
            : o(_o), d(_d), mint(start), maxt(end), rayEpsilon(eps), depth(_depth)
    { }

    /*!
     * Pro zadaný parametr t vypočítá bod na polopřímce.
     * Použití: Ray r; r(0.568);
     * \param t hodnota parametru
     */
    Vector operator()(float t) const
    {
        return o + d * t;
    }

    Vector o; ///< pocatek paprsku
    Vector d; ///< smer paprsku
    mutable Real mint; ///< minimalni hodnota parametru t
    mutable Real maxt; ///< maximalni hodnota parametru t
    mutable Real rayEpsilon; ///< vypocitane epsilon (zamezuje vzniku artefaktu)
    mutable int depth; ///< hloubka rekurze
};

/*!
 * Třída reprezentuje obalový kvádr, jehož stěny jsou rovnoběžné s osami světových souřadnic.
 */
class BBox
{
public:
    /*!
     * Bezparametrický konstruktor.\n
     * pMin má všechny složky definované na INFINITY a pmax na -INFINITY
     * z důvodu snadnějšího slučování s jinými BBox.
     */
    BBox()
    {
        pMin = Vector(INFINITY, INFINITY, INFINITY);
        pMax = Vector(-INFINITY, -INFINITY, -INFINITY);
    }

    /*!
     * Konstruktor definovaný pomocí jednoho bodu. Vloží jeho hodnotu do pMin a pMax.
     * \param p bod
     */
    BBox(const Vector& p)
            : pMin(p), pMax(p)
    { }

    /*!
     * Konstruktor definující BBox pomocí dvou bodů.
     * Do pMin se vloží minimální složky a do pMax maximální složky z obou bodů.
     * \param p1 reference na první bod
     * \param p2 reference na druhý bod
     */
    BBox(const Vector& p1, const Vector& p2)
    {
        pMin = Vector(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
        pMax = Vector(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
    }

    /*!
     * Kopírovací konstruktor.
     */
    BBox(const BBox& b)
            : pMin(b.pMin), pMax(b.pMax)
    { }

    /*!
     * Kontroluje, jestli bod leží uvnitř BBox.
     * \param p kontrolovaný bod
     * \return jestli bod leží uvnitř obalové BBox
     */
    bool isInside(const Vector& p) const
    {
        return (p.x >= pMin.x && p.x <= pMax.x &&
                p.y >= pMin.y && p.y <= pMax.y &&
                p.z >= pMin.z && p.z <= pMax.z);
    }

    /*!
     * Kontrolu, jestli dochází k překrytí dvou BBox.
     * \param b kontrolovaný BBox
     * \return jestli se dvě BBox překrývají
     */
    bool isOverlaps(const BBox& b) const
    {
        bool x = (pMax.x >= b.pMin.x && pMin.x <= b.pMax.x);
        bool y = (pMax.y >= b.pMin.y && pMin.y <= b.pMax.y);
        bool z = (pMax.z >= b.pMin.z && pMin.z <= b.pMax.z);
        return (x && y && z);
    }

    /*!
     * Vypočítá diagonálu BBox.
     * \return Vector představující diagonálu
     */
    Vector diagonal() const
    {
        return pMax - pMin;
    }

    /*!
     * Zjišťuje, ve které ose je BBox nejrozměrnější.
     * \return číslo osy (0 - x, 1 - y, 2 - z)
     */
    int maxDimensionIndex() const
    {
        Vector diag = diagonal();
        if (diag.x > diag.y && diag.x > diag.z)
            return 0;
        else if (diag.y > diag.z)
            return 1;
        else
            return 2;
    }

    /*!
     * Metoda vypočítá střed (centroid) BBox.
     * \return Point reprezentující střed BBox
     */
    Vector centroid() const
    {
        return (pMin + pMax) / 2.f;
    }

    /*!
     * Provede sjednocení BBox a bodu.
     * @param b instance třídy BBox
     * @param p instance třídy Point
     * @return BBox vzniknutý sjednocením
     */
    friend BBox unite(const BBox& b, const Vector& p);

    /*!
     * Provede sjednocení BBox a bodu.
     * \param b instance třídy BBox
     * \param b2 instance třídy BBox
     * \return BBox vzniknutý sjednocením
     */
    friend BBox unite(const BBox& b, const BBox& b2);

    /*!
     * Zjistí, jestli existuje průsečík přímky a BBox.
     * Je také možné získat hodnoty parametrů t.
     * \param ray paprsek
     * \param hitt0 slouží k uložení hodnoty prvního parametru průsečíku t
     * \param hitt1 slouží k uložení hodnoty druhého parametru průsečíku t
     * \return zdali průsečík protnul BBox
     */
    bool intersectP(const Ray& ray, Real* hitt0, Real* hitt1) const;

    /*!
     * Lineární interpolace uvnitř BBox mezi body pMin a pMax.
     */
    Vector lerp(Real tx, Real ty, Real tz) const
    {
        return Vector(tracer::lerp(tx, pMin.x, pMax.x),
                      tracer::lerp(ty, pMin.y, pMax.y),
                      tracer::lerp(tz, pMin.z, pMax.z));
    }

    Vector operator[](int i) const
    {
        assert(i >= 0 && i <= 1);
        return (&pMin)[i];
    }

    Vector& operator[](int i)
    {
        assert(i >= 0 && i <= 2);
        return (&pMin)[i];
    }

    Vector pMin; ///< bod s nejmenšími složkami
    Vector pMax; ///< bod s největšími složkami
};

/*!
 * Skalárni součin dvou vektorů.
 */
inline float dot(const Vector& u, const Vector& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

/*!
 * Vektorový součin dvou vektorů.
 */
inline Vector cross(const Vector& u, const Vector& v)
{
    return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
                  u.x * v.y - u.y * v.x);
}

/*!
 * Vzdálenost dvou bodů.
 */
inline float distance(const Vector& p1, const Vector& p2)
{
    Vector v = p1 - p2;
    return v.length();
}

}