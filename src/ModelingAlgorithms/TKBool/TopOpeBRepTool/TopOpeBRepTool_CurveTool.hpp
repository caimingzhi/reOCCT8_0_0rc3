#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepTool_GeomTool.hpp>
#include <TopOpeBRepTool_OutCurveType.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
class Geom_Curve;
class Geom2d_Curve;
class TopoDS_Shape;

class TopOpeBRepTool_CurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_CurveTool();

  Standard_EXPORT TopOpeBRepTool_CurveTool(const TopOpeBRepTool_OutCurveType OCT);

  Standard_EXPORT TopOpeBRepTool_CurveTool(const TopOpeBRepTool_GeomTool& GT);

  Standard_EXPORT TopOpeBRepTool_GeomTool& ChangeGeomTool();

  Standard_EXPORT const TopOpeBRepTool_GeomTool& GetGeomTool() const;

  Standard_EXPORT void SetGeomTool(const TopOpeBRepTool_GeomTool& GT);

  //! Approximates curves.
  //! Returns False in the case of failure
  Standard_EXPORT bool MakeCurves(const double                     min,
                                  const double                     max,
                                  const occ::handle<Geom_Curve>&   C3D,
                                  const occ::handle<Geom2d_Curve>& PC1,
                                  const occ::handle<Geom2d_Curve>& PC2,
                                  const TopoDS_Shape&              S1,
                                  const TopoDS_Shape&              S2,
                                  occ::handle<Geom_Curve>&         C3DN,
                                  occ::handle<Geom2d_Curve>&       PC1N,
                                  occ::handle<Geom2d_Curve>&       PC2N,
                                  double&                          Tol3d,
                                  double&                          Tol2d) const;

  Standard_EXPORT static occ::handle<Geom_Curve> MakeBSpline1fromPnt(
    const NCollection_Array1<gp_Pnt>& P);

  Standard_EXPORT static occ::handle<Geom2d_Curve> MakeBSpline1fromPnt2d(
    const NCollection_Array1<gp_Pnt2d>& P);

  Standard_EXPORT static bool IsProjectable(const TopoDS_Shape&            S,
                                            const occ::handle<Geom_Curve>& C);

  Standard_EXPORT static occ::handle<Geom2d_Curve> MakePCurveOnFace(
    const TopoDS_Shape&            S,
    const occ::handle<Geom_Curve>& C,
    double&                        TolReached2d,
    const double                   first = 0.0,
    const double                   last  = 0.0);

protected:
  TopOpeBRepTool_GeomTool myGeomTool;
};

