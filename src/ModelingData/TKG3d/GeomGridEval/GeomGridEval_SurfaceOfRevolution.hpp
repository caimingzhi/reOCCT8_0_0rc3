#pragma once

#include <GeomGridEval.hpp>
#include <GeomGridEval_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class GeomGridEval_SurfaceOfRevolution
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomGridEval_SurfaceOfRevolution(
    const occ::handle<Geom_SurfaceOfRevolution>& theRevolution);

  GeomGridEval_SurfaceOfRevolution(const GeomGridEval_SurfaceOfRevolution&)            = delete;
  GeomGridEval_SurfaceOfRevolution& operator=(const GeomGridEval_SurfaceOfRevolution&) = delete;
  GeomGridEval_SurfaceOfRevolution(GeomGridEval_SurfaceOfRevolution&&)                 = delete;
  GeomGridEval_SurfaceOfRevolution& operator=(GeomGridEval_SurfaceOfRevolution&&)      = delete;

  const occ::handle<Geom_SurfaceOfRevolution>& Geometry() const { return myGeom; }

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
  occ::handle<Geom_SurfaceOfRevolution> myGeom;
  occ::handle<Geom_Curve>               myBasisCurve;
  gp_Ax1                                myAxis;
  gp_Pnt                                myAxisLocation;
  gp_Dir                                myAxisDirection;
};
