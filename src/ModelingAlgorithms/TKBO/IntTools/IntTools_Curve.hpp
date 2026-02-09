#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_CurveType.hpp>
class Geom_Curve;
class Geom2d_Curve;
class gp_Pnt;

class IntTools_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_Curve();

  Standard_EXPORT IntTools_Curve(const occ::handle<Geom_Curve>&   the3dCurve3d,
                                 const occ::handle<Geom2d_Curve>& the2dCurve1,
                                 const occ::handle<Geom2d_Curve>& the2dCurve2,
                                 const double                     theTolerance           = 0.0,
                                 const double                     theTangentialTolerance = 0.0);

  void SetCurves(const occ::handle<Geom_Curve>&   the3dCurve,
                 const occ::handle<Geom2d_Curve>& the2dCurve1,
                 const occ::handle<Geom2d_Curve>& the2dCurve2)
  {
    my3dCurve  = the3dCurve;
    my2dCurve1 = the2dCurve1;
    my2dCurve2 = the2dCurve2;
  }

  void SetCurve(const occ::handle<Geom_Curve>& the3dCurve) { my3dCurve = the3dCurve; }

  void SetFirstCurve2d(const occ::handle<Geom2d_Curve>& the2dCurve1) { my2dCurve1 = the2dCurve1; }

  void SetSecondCurve2d(const occ::handle<Geom2d_Curve>& the2dCurve2) { my2dCurve2 = the2dCurve2; }

  void SetTolerance(const double theTolerance) { myTolerance = theTolerance; }

  void SetTangentialTolerance(const double theTangentialTolerance)
  {
    myTangentialTolerance = theTangentialTolerance;
  }

  const occ::handle<Geom_Curve>& Curve() const { return my3dCurve; }

  const occ::handle<Geom2d_Curve>& FirstCurve2d() const { return my2dCurve1; }

  const occ::handle<Geom2d_Curve>& SecondCurve2d() const { return my2dCurve2; }

  double Tolerance() const { return myTolerance; }

  double TangentialTolerance() const { return myTangentialTolerance; }

  Standard_EXPORT bool HasBounds() const;

  Standard_EXPORT bool Bounds(double& theFirst,
                              double& theLast,
                              gp_Pnt& theFirstPnt,
                              gp_Pnt& theLastPnt) const;

  Standard_EXPORT bool D0(const double& thePar, gp_Pnt& thePnt) const;

  Standard_EXPORT GeomAbs_CurveType Type() const;

private:
  occ::handle<Geom_Curve>   my3dCurve;
  occ::handle<Geom2d_Curve> my2dCurve1;
  occ::handle<Geom2d_Curve> my2dCurve2;
  double                    myTolerance;
  double                    myTangentialTolerance;
};
