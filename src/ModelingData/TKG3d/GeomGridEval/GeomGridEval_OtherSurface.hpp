#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Geom_Surface.hpp>
#include <GeomGridEval.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <variant>

class GeomGridEval_OtherSurface
{
public:
  DEFINE_STANDARD_ALLOC

  GeomGridEval_OtherSurface(const Adaptor3d_Surface* theSurface)
      : mySurface(theSurface)
  {
  }

  GeomGridEval_OtherSurface(const occ::handle<Geom_Surface>& theSurface)
      : mySurface(theSurface)
  {
  }

  GeomGridEval_OtherSurface(const GeomGridEval_OtherSurface&)            = delete;
  GeomGridEval_OtherSurface& operator=(const GeomGridEval_OtherSurface&) = delete;
  GeomGridEval_OtherSurface(GeomGridEval_OtherSurface&&)                 = delete;
  GeomGridEval_OtherSurface& operator=(GeomGridEval_OtherSurface&&)      = delete;

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
  void evaluateD0(double theU, double theV, gp_Pnt& thePoint) const;

  void evaluateD1(double theU, double theV, gp_Pnt& thePoint, gp_Vec& theD1U, gp_Vec& theD1V) const;

  void evaluateD2(double  theU,
                  double  theV,
                  gp_Pnt& thePoint,
                  gp_Vec& theD1U,
                  gp_Vec& theD1V,
                  gp_Vec& theD2U,
                  gp_Vec& theD2V,
                  gp_Vec& theD2UV) const;

  void evaluateD3(double  theU,
                  double  theV,
                  gp_Pnt& thePoint,
                  gp_Vec& theD1U,
                  gp_Vec& theD1V,
                  gp_Vec& theD2U,
                  gp_Vec& theD2V,
                  gp_Vec& theD2UV,
                  gp_Vec& theD3U,
                  gp_Vec& theD3V,
                  gp_Vec& theD3UUV,
                  gp_Vec& theD3UVV) const;

  gp_Vec evaluateDN(double theU, double theV, int theNU, int theNV) const;

private:
  std::variant<const Adaptor3d_Surface*, occ::handle<Geom_Surface>> mySurface;
};
