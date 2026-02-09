#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_OStream.hpp>

class Approx_CurvilinearParameter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Approx_CurvilinearParameter(const occ::handle<Adaptor3d_Curve>& C3D,
                                              const double                        Tol,
                                              const GeomAbs_Shape                 Order,
                                              const int                           MaxDegree,
                                              const int                           MaxSegments);

  Standard_EXPORT Approx_CurvilinearParameter(const occ::handle<Adaptor2d_Curve2d>& C2D,
                                              const occ::handle<Adaptor3d_Surface>& Surf,
                                              const double                          Tol,
                                              const GeomAbs_Shape                   Order,
                                              const int                             MaxDegree,
                                              const int                             MaxSegments);

  Standard_EXPORT Approx_CurvilinearParameter(const occ::handle<Adaptor2d_Curve2d>& C2D1,
                                              const occ::handle<Adaptor3d_Surface>& Surf1,
                                              const occ::handle<Adaptor2d_Curve2d>& C2D2,
                                              const occ::handle<Adaptor3d_Surface>& Surf2,
                                              const double                          Tol,
                                              const GeomAbs_Shape                   Order,
                                              const int                             MaxDegree,
                                              const int                             MaxSegments);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve3d() const;

  Standard_EXPORT double MaxError3d() const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2d1() const;

  Standard_EXPORT double MaxError2d1() const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2d2() const;

  Standard_EXPORT double MaxError2d2() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  Standard_EXPORT static void ToleranceComputation(const occ::handle<Adaptor2d_Curve2d>& C2D,
                                                   const occ::handle<Adaptor3d_Surface>& S,
                                                   const int                             MaxNumber,
                                                   const double                          Tol,
                                                   double&                               TolV,
                                                   double&                               TolW);

private:
  int                              myCase;
  bool                             myDone;
  bool                             myHasResult;
  occ::handle<Geom_BSplineCurve>   myCurve3d;
  double                           myMaxError3d;
  occ::handle<Geom2d_BSplineCurve> myCurve2d1;
  double                           myMaxError2d1;
  occ::handle<Geom2d_BSplineCurve> myCurve2d2;
  double                           myMaxError2d2;
};
