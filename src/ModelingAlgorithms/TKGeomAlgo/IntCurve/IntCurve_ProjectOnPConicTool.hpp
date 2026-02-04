#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class IntCurve_PConic;
class gp_Pnt2d;

//! This class provides a tool which computes the parameter
//! of a point near a parametric conic.
class IntCurve_ProjectOnPConicTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the parameter V of the point on the
  //! parametric curve corresponding to the Point Pnt. The
  //! Correspondence between Pnt and the point P(V) on the
  //! parametric curve must be coherent with the way of
  //! determination of the signed distance between a point and
  //! the implicit curve. Tol is the tolerance on the distance
  //! between a point and the parametrised curve. In that case,
  //! no bounds are given. The research of the right parameter
  //! has to be made on the natural parametric domain of the
  //! curve.
  Standard_EXPORT static double FindParameter(const IntCurve_PConic& C,
                                              const gp_Pnt2d&        Pnt,
                                              const double           Tol);

  //! Returns the parameter V of the point on the
  //! parametric curve corresponding to the Point Pnt. The
  //! Correspondence between Pnt and the point P(V) on the
  //! parametric curve must be coherent with the way of
  //! determination of the signed distance between a point and
  //! the implicit curve. Tol is the tolerance on the distance
  //! between a point and the parametrised curve. LowParameter
  //! and HighParameter give the boundaries of the interval in
  //! which the parameter certainly lies. These parameters are
  //! given to implement a more efficient algorithm. So, it is
  //! not necessary to check that the returned value verifies
  //! LowParameter <= Value <= HighParameter.
  Standard_EXPORT static double FindParameter(const IntCurve_PConic& C,
                                              const gp_Pnt2d&        Pnt,
                                              const double           LowParameter,
                                              const double           HighParameter,
                                              const double           Tol);
};

