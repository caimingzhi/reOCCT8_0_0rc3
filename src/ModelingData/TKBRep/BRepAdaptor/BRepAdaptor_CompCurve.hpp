#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Wire.hpp>
#include <Standard_Real.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomAbs_CurveType.hpp>

class TopoDS_Edge;
class gp_Pnt;
class gp_Vec;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Hypr;
class gp_Parab;
class Geom_BezierCurve;
class Geom_BSplineCurve;

class BRepAdaptor_CompCurve : public Adaptor3d_Curve
{
  DEFINE_STANDARD_RTTIEXT(BRepAdaptor_CompCurve, Adaptor3d_Curve)
public:
  Standard_EXPORT BRepAdaptor_CompCurve();

  Standard_EXPORT BRepAdaptor_CompCurve(const TopoDS_Wire& W,
                                        const bool         KnotByCurvilinearAbcissa = false);

  Standard_EXPORT BRepAdaptor_CompCurve(const TopoDS_Wire& W,
                                        const bool         KnotByCurvilinearAbcissa,
                                        const double       First,
                                        const double       Last,
                                        const double       Tol);

  Standard_EXPORT occ::handle<Adaptor3d_Curve> ShallowCopy() const override;

  Standard_EXPORT void Initialize(const TopoDS_Wire& W, const bool KnotByCurvilinearAbcissa);

  Standard_EXPORT void Initialize(const TopoDS_Wire& W,
                                  const bool         KnotByCurvilinearAbcissa,
                                  const double       First,
                                  const double       Last,
                                  const double       Tol);

  Standard_EXPORT const TopoDS_Wire& Wire() const;

  Standard_EXPORT void Edge(const double U, TopoDS_Edge& E, double& UonE) const;

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

private:
  Standard_EXPORT void Prepare(double& W, double& D, int& ind) const;

  Standard_EXPORT void InvPrepare(const int ind, double& F, double& D) const;

  TopoDS_Wire                                         myWire;
  double                                              TFirst;
  double                                              TLast;
  double                                              PTol;
  occ::handle<NCollection_HArray1<BRepAdaptor_Curve>> myCurves;
  occ::handle<NCollection_HArray1<double>>            myKnots;
  int                                                 CurIndex;
  bool                                                Forward;
  bool                                                IsbyAC;
};
