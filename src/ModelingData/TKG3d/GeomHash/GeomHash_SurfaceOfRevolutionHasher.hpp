#pragma once


#include <Standard_HashUtils.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <GeomHash_PointHasher.hpp>
#include <GeomHash_DirectionHasher.hpp>
#include <GeomHash_CurveHasher.hpp>

//! OCCT-style hasher for Geom_SurfaceOfRevolution.
//! Used for geometry deduplication.
struct GeomHash_SurfaceOfRevolutionHasher
{
  // Hashes the revolution surface by its axis and basis curve.
  std::size_t operator()(const occ::handle<Geom_SurfaceOfRevolution>& theSurface) const noexcept
  {
    const GeomHash_PointHasher     aPointHasher;
    const GeomHash_DirectionHasher aDirHasher;
    const GeomHash_CurveHasher     aCurveHasher;

    const gp_Ax1&     anAxis     = theSurface->Axis();
    const std::size_t aHashes[3] = {aCurveHasher(theSurface->BasisCurve()),
                                    aPointHasher(anAxis.Location()),
                                    aDirHasher(anAxis.Direction())};
    return opencascade::hashBytes(aHashes, sizeof(aHashes));
  }

  // Compares two revolution surfaces.
  bool operator()(const occ::handle<Geom_SurfaceOfRevolution>& theSurface1,
                  const occ::handle<Geom_SurfaceOfRevolution>& theSurface2) const noexcept
  {
    const GeomHash_PointHasher     aPointHasher;
    const GeomHash_DirectionHasher aDirHasher;
    const GeomHash_CurveHasher     aCurveHasher;

    const gp_Ax1& anAxis1 = theSurface1->Axis();
    const gp_Ax1& anAxis2 = theSurface2->Axis();

    return aCurveHasher(theSurface1->BasisCurve(), theSurface2->BasisCurve())
           && aPointHasher(anAxis1.Location(), anAxis2.Location())
           && aDirHasher(anAxis1.Direction(), anAxis2.Direction());
  }
};

