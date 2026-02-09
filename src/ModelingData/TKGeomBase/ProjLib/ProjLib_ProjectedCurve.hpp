#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <AppParCurves_Constraint.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <ProjLib_Projector.hpp>
#include <NCollection_Array1.hpp>

class gp_Pnt2d;
class gp_Vec2d;
class gp_Lin2d;
class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;
class Geom2d_BezierCurve;
class Geom2d_BSplineCurve;

class ProjLib_ProjectedCurve : public Adaptor2d_Curve2d
{
  DEFINE_STANDARD_RTTIEXT(ProjLib_ProjectedCurve, Adaptor2d_Curve2d)
public:
  Standard_EXPORT ProjLib_ProjectedCurve();

  Standard_EXPORT ProjLib_ProjectedCurve(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT ProjLib_ProjectedCurve(const occ::handle<Adaptor3d_Surface>& S,
                                         const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT ProjLib_ProjectedCurve(const occ::handle<Adaptor3d_Surface>& S,
                                         const occ::handle<Adaptor3d_Curve>&   C,
                                         const double                          Tol);

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> ShallowCopy() const override;

  Standard_EXPORT void Load(const double Tolerance);

  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>& C);

  Standard_EXPORT void SetDegree(const int theDegMin, const int theDegMax);

  Standard_EXPORT void SetMaxSegments(const int theMaxSegments);

  Standard_EXPORT void SetBndPnt(const AppParCurves_Constraint theBndPnt);

  Standard_EXPORT void SetMaxDist(const double theMaxDist);

  Standard_EXPORT const occ::handle<Adaptor3d_Surface>& GetSurface() const;

  Standard_EXPORT const occ::handle<Adaptor3d_Curve>& GetCurve() const;

  Standard_EXPORT double GetTolerance() const;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> Trim(const double First,
                                                      const double Last,
                                                      const double Tol) const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT gp_Pnt2d Value(const double U) const override;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT double Resolution(const double R3d) const override;

  Standard_EXPORT GeomAbs_CurveType GetType() const override;

  Standard_EXPORT gp_Lin2d Line() const override;

  Standard_EXPORT gp_Circ2d Circle() const override;

  Standard_EXPORT gp_Elips2d Ellipse() const override;

  Standard_EXPORT gp_Hypr2d Hyperbola() const override;

  Standard_EXPORT gp_Parab2d Parabola() const override;

  Standard_EXPORT int Degree() const override;

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT int NbPoles() const override;

  Standard_EXPORT int NbKnots() const override;

  Standard_EXPORT occ::handle<Geom2d_BezierCurve> Bezier() const override;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> BSpline() const override;

private:
  double                         myTolerance;
  occ::handle<Adaptor3d_Surface> mySurface;
  occ::handle<Adaptor3d_Curve>   myCurve;
  ProjLib_Projector              myResult;
  int                            myDegMin;
  int                            myDegMax;
  int                            myMaxSegments;
  double                         myMaxDist;
  AppParCurves_Constraint        myBndPnt;
};
