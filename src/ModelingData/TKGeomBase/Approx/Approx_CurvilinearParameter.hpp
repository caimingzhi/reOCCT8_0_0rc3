#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_OStream.hpp>

//! Approximation of a Curve to make its parameter be its curvilinear abscissa.
//! If the curve is a curve on a surface S, C2D is the corresponding Pcurve,
//! we consider the curve is given by its representation
//! @code
//!   S(C2D(u))
//! @endcode
//! If the curve is a curve on 2 surfaces S1 and S2 and C2D1 C2D2 are the two corresponding Pcurve,
//! we consider the curve is given by its representation
//! @code
//!   1/2(S1(C2D1(u) + S2(C2D2(u)))
//! @endcode
class Approx_CurvilinearParameter
{
public:
  DEFINE_STANDARD_ALLOC

  //! case of a free 3D curve
  Standard_EXPORT Approx_CurvilinearParameter(const occ::handle<Adaptor3d_Curve>& C3D,
                                              const double                        Tol,
                                              const GeomAbs_Shape                 Order,
                                              const int                           MaxDegree,
                                              const int                           MaxSegments);

  //! case of a curve on one surface
  Standard_EXPORT Approx_CurvilinearParameter(const occ::handle<Adaptor2d_Curve2d>& C2D,
                                              const occ::handle<Adaptor3d_Surface>& Surf,
                                              const double                          Tol,
                                              const GeomAbs_Shape                   Order,
                                              const int                             MaxDegree,
                                              const int                             MaxSegments);

  //! case of a curve on two surfaces
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

  //! returns the Bspline curve corresponding to the reparametrized 3D curve
  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve3d() const;

  //! returns the maximum error on the reparametrized 3D curve
  Standard_EXPORT double MaxError3d() const;

  //! returns the BsplineCurve representing the reparametrized 2D curve on the
  //! first surface (case of a curve on one or two surfaces)
  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2d1() const;

  //! returns the maximum error on the first reparametrized 2D curve
  Standard_EXPORT double MaxError2d1() const;

  //! returns the BsplineCurve representing the reparametrized 2D curve on the
  //! second surface (case of a curve on two surfaces)
  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve2d2() const;

  //! returns the maximum error on the second reparametrized 2D curve
  Standard_EXPORT double MaxError2d2() const;

  //! print the maximum errors(s)
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
