#pragma once

#include <cstdlib>

/**
 * Bázová třída, kterou musí dědit třídy, které chtějí používat Reference.
 * Obsahuje čítač referencí a jeho inicializaci.
 * @see Reference
 */
class ReferenceCounted
{
public:
    /**
     * Konstruktor. Inicializuje čítač referencí.
     */
    ReferenceCounted()
    { count = 0; }

    /**
     * Proměnná čítače referencí. Musí být nastavena jako @a mutable aby bylo možné
     * předávat reference jako const Reference<T>.
     */
    mutable unsigned int count;
};

/**
 * Třída implementuje garbage collector jako čítač referencí.
 * Každá každý objekt, který chce využívat této služby musí dědit
 * z ReferenceCounted. Z principu čítače referencí není možné vytvářet
 * křížové odkazy mezi objekty.
 * @tparam T datový typ se kterým bude reference pracovat.
 *           Musí dědit od třídy ReferenceCounted (nelze vynutit,
 *           takže je součástí kontraktu). Lze využívat dědičnost
 *           a polymorfismus.
 */
template<class T>
class Reference
{
public:
    /**
     * Inicializuje referenci pomocí ukazatele.
     * Zvýší počet referencí v čítači.\n
     * Použití: Reference<Foo> ref(new Foo());
     * @param _ptr ukazatel na instanci, ze které chceme vytvořit referenci.
     */
    Reference(T* _ptr = nullptr)
            : ptr(_ptr)
    {
        if (ptr)
            ptr->count = ptr->count + 1;
    }

    /**
     * Kopírovací konstruktor.
     * Zvyšuje hodnotu čítače referencí.
     * @param orig kopírovaná reference
     */
    Reference(const Reference<T>& orig)
    {
        ptr = orig.ptr;

        if (ptr)
            ptr->count = ptr->count + 1;
    }

    /**
     * Destruktor zavolá metodu decrementCount().
     * @see decrementCount()
     */
    virtual ~Reference()
    { decrementCount(); }

    /**
     * Přetížení operátoru dereference.
     * Funguje stejně jako kdyby se jednalo o C pointer.
     */
    T& operator*()
    { return *ptr; }

    /**
     * Přetížení operátoru přístupu ke členským atributům a metodám.
     * Funguje stejně jako kdyby se jednalo o C pointer.
     */
    T* operator->()
    { return ptr; }

    /**
     * Přetížení operátoru reference.
     * @return adresa instance třídy
     */
    Reference<T>* operator&()
    { return this; }

    /**
     * Přetížení operátoru rovná se. Porovnává hodnoty adres pointerů, nikoliv data.
     * Lze porovnávat s instancí Reference, která musí mít stejný parametr šablony T.\n
     * Příklad:\n
     * @code
     * struct Foo {
     *   Foo(int i) { this.i = i; }
     *   int i;
     * }
     *
     * Reference<Foo> ref1(Foo(10));
     * Reference<Foo> ref2(Foo(10));
     * Reference<Foo> ref3(ref1);
     *
     * ref1 == ref2; //return false
     * ref1 == ref3; //return true
     * ref2 == ref3; //return false
     * @endcode
     * @param right porovnávaná instance
     * @return true/false
     */
    bool operator==(const Reference<T>& right) const
    { return ptr == right.ptr; }


    /**
     * Přetížení operátoru nerovná se. Porovnává hodnoty adres pointerů, nikoliv data.
     * Lze porovnávat s instancí Reference, která musí mít stejný parametr šablony T.\n
     * @param right porovnávaná instance
     * @see operator==()
     * @return true/false
     */
    bool operator!=(const Reference<T>& right) const
    { return ptr != right.ptr; }

    /**
     * Přetížený operátor přiřazení. Dokáže přiřadit ukazatel na datový typ,
     * jaký má parametr šablony @a T. Automaticky zvyšuje hodnotu čítače.
     * Je možné přiřadit hodnotu @b NULL.
     * @param right ukazatel na adresu s datovým typem T
     */
    Reference<T>& operator=(T* right)
    {
        if (right) right->count = right->count + 1;

        decrementCount();

        ptr = right;

        return *this;
    }

    /**
     * Přetížený operátor přiřazení. Dokáže přiřadit Referenci se stejným datovým typem,
     * jaký má parametr šablony @b T. Automaticky zvyšuje hodnotu čítače u nového ukazatele,
     * a snižuje u starého pomocí metody decrementCount().
     * @param right ukazatel na adresu s datovým typem T
     */
    Reference<T>& operator=(const Reference<T>& right)
    {
        if (this == &right)
            return *this;

        decrementCount();

        right.ptr->count = right.ptr->count + 1;
        ptr = right.ptr;

        return *this;
    }

    /**
     * Slouží pro kontrolu, jestli je přiřazen nějaký ukazatel.
     */
    operator bool()
    { return ptr == NULL; }

    /**
     * Provede snížení čítače metodou decrementCount() a nastaví
     * ptr na hodnotu @b NULL.
     */
    void unset()
    {
        decrementCount();
        ptr = NULL;
    }

private:
    /**
     * Metoda snižuje hodnotu čítače referencí. Pokud dosáhne čítač hodnoty 0,
     * pak provede jeho vymazání ptr z paměti pomocí a přiřadí hodnotu NULL:
     * @code
     * delete ptr;
     * ptr = NULL;
     * @endcode
     */
    void decrementCount()
    {
        if (ptr)
        {
            if (--ptr->count == 0 && ptr)
            {
                delete ptr;
                ptr = NULL;
            }
        }
    }

private:
    T* ptr; ///< ukazatel na data s čítačem.
};