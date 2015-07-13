#pragma once

namespace tracer
{

/*!
 * Třída reprezentující barevné hodnoty v prostoru RGB.
 */
class RGBColor
{
public:
    /*!
     * Bezparametrický konstruktor. Všechny složky jsou nastaveny na 0.
     */
    RGBColor()
    { r = g = b = 0.f; }

    /*!
     * Konstruktor. Složky jsou nastaveny podle argumentů
     * \param _r červená složka
     * \param _g zelená složka
     * \param _b modrá složka
     */
    RGBColor(Real _r, Real _g, Real _b)
            : r(_r), g(_g), b(_b)
    { }

    /*!
     * Kopírovací konstruktor
     */
    RGBColor(const RGBColor& c)
            : r(c.r), g(c.g), b(c.b)
    { }

    ~RGBColor()
    { }

    const RGBColor& operator+() const
    {
        return *this;
    }

    RGBColor operator-() const
    {
        return RGBColor(-r, -g, -b);
    }

    bool operator==(const RGBColor& v)
    {
        return r == v.r && g == v.g && b == v.b;
    }

    bool operator!=(const RGBColor& v)
    {
        return r != v.r || g != v.g || b != v.b;
    }

    RGBColor operator+(const RGBColor& v) const
    {
        return RGBColor(r + v.r, g + v.g, b + v.b);
    }

    RGBColor& operator+=(const RGBColor& v)
    {
        *this = *this + v;
        return *this;
    }

    RGBColor operator-(const RGBColor& v) const
    {
        return RGBColor(r - v.r, g - v.g, b - v.b);
    }

    RGBColor& operator-=(const RGBColor& v)
    {
        *this = *this - v;
        return *this;
    }

    RGBColor operator/(Real k) const
    {
        assert(k != 0);
        Real invK = 1.f / k;
        return RGBColor(r * invK, g * invK, b * invK);
    }

    RGBColor& operator/=(Real k)
    {
        assert(k != 0);
        Real invK = 1.f / k;

        r *= invK;
        g *= invK;
        b *= invK;

        return *this;
    }

    /*!
     * Všechny složky se vynásobí zadanou konstantou.
     * \param k násobitel
     */
    RGBColor operator*(Real k) const
    {
        return RGBColor(r * k, g * k, b * k);
    }

    /*!
     * Složky se mezi sebou násobí.
     * \param k druhá barva
     */
    RGBColor operator*(const RGBColor& k) const
    {
        return RGBColor(r * k.r, g * k.g, b * k.b);
    }

    RGBColor& operator*=(Real k)
    {
        r *= k;
        g *= k;
        b *= k;
        return *this;
    }

    friend RGBColor operator*(Real k, const RGBColor& c)
    {
        return RGBColor(c.r * k, c.g * k, c.b * k);
    }

    RGBColor& operator=(const RGBColor& v)
    {
        r = v.r;
        g = v.g;
        b = v.b;
        return *this;
    }

    /*!
     * Umocní jednotlivé složky.
     * \param c mocnina
     */
    void pow(Real c)
    {
        r = powf(r, c);
        g = powf(g, c);
        b = powf(b, c);
    }

    /*!
     * Provádí ořez barevných složek na zadaný rozsah. Původní barva zůstane nezměněna.
     * \param from začátek rozsahu
     * \param to konec rozsahu
     * \return ořezaná barva
     */
    RGBColor clamp(Real from = 0.f, Real to = 1.0)
    {
        RGBColor out;

        out.r = clamp(r, from, to);
        out.g = clamp(g, from, to);
        out.b = clamp(b, from, to);

        return out;
    }

    Real r, g, b; ///< jednotlivé barevné složky
};

const RGBColor BLACK(0.f, 0.f, 0.f); ///< konstantanta černé barvy
const RGBColor WHITE(1.f, 1.f, 1.f); ///< konstantanta bílé barvy
const RGBColor GREY(0.5f, 0.5f, 0.5f); ///< konstantanta šedé barvy
const RGBColor LIGHT_GREY(0.8f, 0.8f, 0.8f); ///< konstantanta světle šedé barvy
const RGBColor DARK_GREY(0.3f, 0.3f, 0.3f); ///< konstantanta tmavě šedé barvy
const RGBColor RED(1.0f, 0.f, 0.f); ///< konstantanta červené barvy
const RGBColor GREEN(0.0f, 1.0f, 0.0f); ///< konstantanta zelené barvy
const RGBColor BLUE(0.0f, 0.0f, 1.0f); ///< konstantanta modré barvy

}