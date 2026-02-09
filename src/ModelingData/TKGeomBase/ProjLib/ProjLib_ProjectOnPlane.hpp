#pragma once

#include <Adaptor3d_Curve.hpp>
#include <gp_Ax3.hpp>
#include <gp_Dir.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>

class gp_Pnt;
class gp_Vec;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Hypr;
class gp_Parab;
class Geom_BezierCurve;
class Geom_BSplineCurve;

class ProjLib_ProjectOnPlane : public Adaptor3d_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ProjLib_ProjectOnPlane();

  Standard_EXPORT ProjLib_ProjectOnPlane(const gp_Ax3& Pl);

  Standard_EXPORT ProjLib_ProjectOnPlane(const gp_Ax3& Pl, const gp_Dir& D);

  Standard_EXPORT occ::handle<Adaptor3d_Curve> ShallowCopy() const override;

  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Curve>& C,
                            const double                        Tolerance,
                            const bool                          KeepParametrization = true);

  Standard_EXPORT const gp_Ax3& GetPlane() const;

  Standard_EXPORT const gp_Dir& GetDirection() const;

  Standard_EXPORT const occ::handle<Adaptor3d_Curve>& GetCurve() const;

  Standard_EXPORT const occ::handle<GeomAdaptor_Curve>& GetResult() const;

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

protected:
  void GetTrimmedResult(const occ::handle<Geom_Curve>& theProjCurve);

  bool BuildParabolaByApex(occ::handle<Geom_Curve>& theGeomParabolaPtr);
  bool BuildHyperbolaByApex(occ::handle<Geom_Curve>& theGeomParabolaPtr);

  void BuildByApprox(const double theLimitParameter);

private:
  occ::handle<Adaptor3d_Curve>   myCurve;
  gp_Ax3                         myPlane;
  gp_Dir                         myDirection;
  bool                           myKeepParam;
  double                         myFirstPar;
  double                         myLastPar;
  double                         myTolerance;
  GeomAbs_CurveType              myType;
  occ::handle<GeomAdaptor_Curve> myResult;
  bool                           myIsApprox;
};
