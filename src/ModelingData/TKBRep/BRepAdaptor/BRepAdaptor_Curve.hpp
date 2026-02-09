#pragma once

#include <Adaptor3d_CurveOnSurface.hpp>
#include <gp_Trsf.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <TopoDS_Edge.hpp>
#include <Adaptor3d_Curve.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_CurveType.hpp>

class TopoDS_Face;
class Adaptor3d_CurveOnSurface;
class gp_Pnt;
class gp_Vec;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Hypr;
class gp_Parab;
class Geom_BezierCurve;
class Geom_BSplineCurve;
class Geom_OffsetCurve;

class BRepAdaptor_Curve : public Adaptor3d_Curve
{
  DEFINE_STANDARD_RTTIEXT(BRepAdaptor_Curve, Adaptor3d_Curve)
public:
  Standard_EXPORT BRepAdaptor_Curve();

  Standard_EXPORT BRepAdaptor_Curve(const TopoDS_Edge& E);

  Standard_EXPORT BRepAdaptor_Curve(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT occ::handle<Adaptor3d_Curve> ShallowCopy() const override;

  Standard_EXPORT void Reset();

  Standard_EXPORT void Initialize(const TopoDS_Edge& E);

  Standard_EXPORT void Initialize(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT const gp_Trsf& Trsf() const;

  Standard_EXPORT bool Is3DCurve() const;

  Standard_EXPORT bool IsCurveOnSurface() const;

  Standard_EXPORT const GeomAdaptor_Curve& Curve() const;

  Standard_EXPORT const Adaptor3d_CurveOnSurface& CurveOnSurface() const;

  Standard_EXPORT const TopoDS_Edge& Edge() const;

  Standard_EXPORT double Tolerance() const;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT occ::handle<Adaptor3d_Curve> Trim(const double First,
                                                    const double Last,
                                                    const double Tol) const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT gp_Pnt Value(const double U) const override;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  Standard_EXPORT double Resolution(const double R3d) const override;

  Standard_EXPORT GeomAbs_CurveType GetType() const override;

  Standard_EXPORT gp_Lin Line() const override;

  Standard_EXPORT gp_Circ Circle() const override;

  Standard_EXPORT gp_Elips Ellipse() const override;

  Standard_EXPORT gp_Hypr Hyperbola() const override;

  Standard_EXPORT gp_Parab Parabola() const override;

  Standard_EXPORT int Degree() const override;

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT int NbPoles() const override;

  Standard_EXPORT int NbKnots() const override;

  Standard_EXPORT occ::handle<Geom_BezierCurve> Bezier() const override;

  Standard_EXPORT occ::handle<Geom_BSplineCurve> BSpline() const override;

  Standard_EXPORT occ::handle<Geom_OffsetCurve> OffsetCurve() const override;

private:
  gp_Trsf                               myTrsf;
  GeomAdaptor_Curve                     myCurve;
  occ::handle<Adaptor3d_CurveOnSurface> myConSurf;
  TopoDS_Edge                           myEdge;
};
