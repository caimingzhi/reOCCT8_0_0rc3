#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <AppParCurves_Constraint.hpp>

class Geom2d_BSplineCurve;
class Geom2d_BezierCurve;

class ProjLib_ComputeApprox
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ProjLib_ComputeApprox();

  Standard_EXPORT ProjLib_ComputeApprox(const occ::handle<Adaptor3d_Curve>&   C,
                                        const occ::handle<Adaptor3d_Surface>& S,
                                        const double                          Tol);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>&   C,
                               const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT void SetTolerance(const double theTolerance);

  Standard_EXPORT void SetDegree(const int theDegMin, const int theDegMax);

  Standard_EXPORT void SetMaxSegments(const int theMaxSegments);

  Standard_EXPORT void SetBndPnt(const AppParCurves_Constraint theBndPnt);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> BSpline() const;

  Standard_EXPORT occ::handle<Geom2d_BezierCurve> Bezier() const;

  Standard_EXPORT double Tolerance() const;

private:
  double                           myTolerance;
  occ::handle<Geom2d_BSplineCurve> myBSpline;
  occ::handle<Geom2d_BezierCurve>  myBezier;
  int                              myDegMin;
  int                              myDegMax;
  int                              myMaxSegments;
  AppParCurves_Constraint          myBndPnt;
};
