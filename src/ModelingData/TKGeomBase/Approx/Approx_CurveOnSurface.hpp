#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_Shape.hpp>

class Geom_BSplineCurve;
class Geom2d_BSplineCurve;

class Approx_CurveOnSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_DEPRECATED(
    "This constructor is deprecated. Use other constructor and perform method instead.")
  Standard_EXPORT Approx_CurveOnSurface(const occ::handle<Adaptor2d_Curve2d>& C2D,
                                        const occ::handle<Adaptor3d_Surface>& Surf,
                                        const double                          First,
                                        const double                          Last,
                                        const double                          Tol,
                                        const GeomAbs_Shape                   Continuity,
                                        const int                             MaxDegree,
                                        const int                             MaxSegments,
                                        const bool                            Only3d = false,
                                        const bool                            Only2d = false);

  Standard_EXPORT Approx_CurveOnSurface(const occ::handle<Adaptor2d_Curve2d>& theC2D,
                                        const occ::handle<Adaptor3d_Surface>& theSurf,
                                        const double                          theFirst,
                                        const double                          theLast,
                                        const double                          theTol);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve3d() const;

  Standard_EXPORT double MaxError3d() const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2d() const;

  Standard_EXPORT double MaxError2dU() const;

  Standard_EXPORT double MaxError2dV() const;

  Standard_EXPORT void Perform(const int           theMaxSegments,
                               const int           theMaxDegree,
                               const GeomAbs_Shape theContinuity,
                               const bool          theOnly3d = false,
                               const bool          theOnly2d = false);

protected:
  bool isIsoLine(const occ::handle<Adaptor2d_Curve2d>& theC2D,
                 bool&                                 theIsU,
                 double&                               theParam,
                 bool&                                 theIsForward) const;

  bool buildC3dOnIsoLine(const occ::handle<Adaptor2d_Curve2d>& theC2D,
                         const bool                            theIsU,
                         const double                          theParam,
                         const bool                            theIsForward);

private:
  Approx_CurveOnSurface& operator=(const Approx_CurveOnSurface&) = delete;

private:
  const occ::handle<Adaptor2d_Curve2d> myC2D;

  const occ::handle<Adaptor3d_Surface> mySurf;

  const double myFirst;

  const double myLast;

  double myTol;

  occ::handle<Geom2d_BSplineCurve> myCurve2d;
  occ::handle<Geom_BSplineCurve>   myCurve3d;
  bool                             myIsDone;
  bool                             myHasResult;
  double                           myError3d;
  double                           myError2dU;
  double                           myError2dV;
};
