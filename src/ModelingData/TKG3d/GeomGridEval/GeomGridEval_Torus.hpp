#pragma once

#include <Geom_ToroidalSurface.hpp>
#include <GeomGridEval.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_Torus
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_Torus(const occ::handle<Geom_ToroidalSurface>& theTorus)
      : myGeom(theTorus)
  {
  }

  GeomGridEval_Torus(const GeomGridEval_Torus&)            = delete;
  GeomGridEval_Torus& operator=(const GeomGridEval_Torus&) = delete;
  GeomGridEval_Torus(GeomGridEval_Torus&&)                 = delete;
  GeomGridEval_Torus& operator=(GeomGridEval_Torus&&)      = delete;

  const occ::handle<Geom_ToroidalSurface>& Geometry() const { return myGeom; }

  Standard_EXPORT NCollection_Array2<gp_Pnt> EvaluateGrid(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD1> EvaluateGridD1(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD2> EvaluateGridD2(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD3> EvaluateGridD3(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<gp_Vec> EvaluateGridDN(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams,
    int                               theNU,
    int                               theNV) const;

  Standard_EXPORT NCollection_Array1<gp_Pnt> EvaluatePoints(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD1> EvaluatePointsD1(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD2> EvaluatePointsD2(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD3> EvaluatePointsD3(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<gp_Vec> EvaluatePointsDN(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs,
    int                                 theNU,
    int                                 theNV) const;

private:
  struct Data
  {
    double CX, CY, CZ;
    double XX, XY, XZ;
    double YX, YY, YZ;
    double ZX, ZY, ZZ;
    double MajorRadius;
    double MinorRadius;
  };

  struct UContext
  {
    double cosU, sinU;
    double dirUX, dirUY, dirUZ;
    double dDirUX, dDirUY, dDirUZ;
  };

  Data extractData() const;

  static UContext computeUContext(const Data& theData, double theU);

  static gp_Pnt computeD0(const Data& theData, const UContext& theUCtx, double theV);

  static GeomGridEval::SurfD1 computeD1(const Data& theData, const UContext& theUCtx, double theV);

  static GeomGridEval::SurfD2 computeD2(const Data& theData, const UContext& theUCtx, double theV);

  static GeomGridEval::SurfD3 computeD3(const Data& theData, const UContext& theUCtx, double theV);

  static gp_Vec computeDN(const Data&     theData,
                          const UContext& theUCtx,
                          double          theV,
                          int             theNU,
                          int             theNV);

  occ::handle<Geom_ToroidalSurface> myGeom;
};
