#pragma once

#include <vector>

#include "core/reference.h"
#include "core/primitive.h"

#define MAX_VOXELS 128

namespace tracer
{

/*!
 * Struktura, která představuje voxel v prostoru.
 * Uchovává pouze objekty a zprostředkovává výpočty průsečíků stejně jako
 * BruteForce struktura. Poloha voxelu je určena z jeho polohy v mřížce.
 */
struct Voxel
{
    /*! Vytvoří prázdný voxel. */
    Voxel();

    /*!
	 * Vytvoří voxel s jedním tělesem.
	 * \param[in] p reference na těleso.
	 */
    Voxel(Reference<Primitive>& p);

    /*!
	 * Přidá těleso do voxelu.
	 * \param p reference na těleso.
	 */
    void addPrimitive(Reference<Primitive>& p);

    /*! \copydoc Primitive::intersect() */
    bool intersect(const Ray& ray, Intersection& inter) const;

    /*! \copydoc Primitive::intersect() */
    bool intersectP(const Ray& ray) const;

private:
    std::vector<Reference<Primitive>> primitives;
};

class Grid : public AccelerationStructure
{
public:
    /*!
     * Vytvoření akcelerační struktury mřížky ze zadaných těles.
     * Nad každým tělesem se zkusí provést Primitive::Refine().
     */
    Grid(std::vector<Reference<Primitive> >& p);

    virtual ~Grid();

    /*! \copydoc Primitive::intersect() Využívá 3D DDA algoritmu. */
    virtual bool intersect(const Ray& ray, Intersection& sr) override;

    /*! \copydoc Primitive::intersectP() Využívá 3D DDA algoritmu. */
    virtual bool intersectP(const Ray& ray) override;

    virtual BBox bounds() const;

private:
    /*!
	 * Dokáže určit ve kterém voxelu zadané osy se bod nachází.
	 * \param p bod pro který je hledá voxel.
	 * \param axis osa ve které se má hledat.
	 * \return číslo hledaného voxelu.
	 */
    inline size_t posToVoxel(const Vector& p, int axis) const
    {
        size_t v = (size_t) ((p[axis] - m_bounds.pMin[axis]) * invWidth[axis]);
        return clamp(v, 0, nVoxels[axis] - 1);
    }

    /*!
	 * Obrácený postup než je ve funkci PosToVoxel.
	 * \param p číslo voxelu
	 * \param axis osa
	 * \return nejnižší hodnota pozice voxelu v hledané ose.
	 */
    Real voxelToPos(int p, int axis) const
    {
        return m_bounds.pMin[axis] + p * width[axis];
    }

    /*!
	 * Vypočítá index v poli na základě zadaných poloh pro každý rozměr.
	 * \param x poloha voxelu podél osy X
	 * \param y poloha voxelu podél osy Y
	 * \param z poloha voxelu podél osy Z
	 */
    inline size_t offset(size_t x, size_t y, size_t z) const
    {
        return x + y * nVoxels[0] + z * nVoxels[0] * nVoxels[1];
    }

    size_t nv; ///< Počet voxelů.
    size_t nVoxels[3]; /// Počet voxelů v každém rozměru.
    Vector width; ///< Rozměr voxelů (může být různý pro každý směr).
    Vector invWidth; ///< Inverzni hodnoty k width.

    /**
     * Pole ukazatelů na voxely. Pro příjemnější práci se používá jednorozměrné
     * pole a pomocí metody offset() se zajišťuje správný posun.
     */
    Voxel** voxels;
    BBox m_bounds; ///< Obalová krychle struktury.
    std::vector<Reference<Primitive> > primitives; ///< Seznam všech těles ve struktuře.
};

}