#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class Law_BSpFunc;
class Law_Linear;
class Law_BSpline;
class Adaptor3d_Curve;

//! Multiple services concerning 1d functions.
class Law
{
public:
  DEFINE_STANDARD_ALLOC

  //! This algorithm searches the knot values corresponding to the
  //! splitting of a given B-spline law into several arcs with
  //! the same continuity. The continuity order is given at the
  //! construction time.
  //! Builds a 1d bspline that is near from Lin with null
  //! derivatives at the extremities.
  Standard_EXPORT static occ::handle<Law_BSpFunc> MixBnd(const occ::handle<Law_Linear>& Lin);

  //! Builds the poles of the 1d bspline that is near from
  //! Lin with null derivatives at the extremities.
  Standard_EXPORT static occ::handle<NCollection_HArray1<double>> MixBnd(
    const int                         Degree,
    const NCollection_Array1<double>& Knots,
    const NCollection_Array1<int>&    Mults,
    const occ::handle<Law_Linear>&    Lin);

  //! Builds the poles of the 1d bspline that is null on the
  //! right side of Knots(Index) (on the left if
  //! NulOnTheRight is false) and that is like a
  //! t*(1-t)(1-t) curve on the left side of Knots(Index)
  //! (on the right if NulOnTheRight is false). The result
  //! curve is C1 with a derivative equal to 1. at first
  //! parameter (-1 at last parameter if NulOnTheRight is
  //! false).
  //! Warning: Mults(Index) must greater or equal to degree-1.
  Standard_EXPORT static occ::handle<NCollection_HArray1<double>> MixTgt(
    const int                         Degree,
    const NCollection_Array1<double>& Knots,
    const NCollection_Array1<int>&    Mults,
    const bool                        NulOnTheRight,
    const int                         Index);

  //! Computes a 1d curve to reparametrize a curve. Its an
  //! interpolation of NbPoints points calculated at quasi
  //! constant abscissa.
  Standard_EXPORT static occ::handle<Law_BSpline> Reparametrize(const Adaptor3d_Curve& Curve,
                                                                const double           First,
                                                                const double           Last,
                                                                const bool             HasDF,
                                                                const bool             HasDL,
                                                                const double           DFirst,
                                                                const double           DLast,
                                                                const bool             Rev,
                                                                const int              NbPoints);

  //! Computes a 1d curve to scale a field of tangency.
  //! Value is 1. for t = (First+Last)/2 .
  //! If HasFirst value for t = First is VFirst (null derivative).
  //! If HasLast value for t = Last is VLast (null derivative).
  //!
  //! 1.                   _
  //! _/ \_
  //! __/     \__
  //! /
  //! VFirst    ____/
  //! VLast                        \____
  //! First                    Last
  Standard_EXPORT static occ::handle<Law_BSpline> Scale(const double First,
                                                        const double Last,
                                                        const bool   HasF,
                                                        const bool   HasL,
                                                        const double VFirst,
                                                        const double VLast);

  Standard_EXPORT static occ::handle<Law_BSpline> ScaleCub(const double First,
                                                           const double Last,
                                                           const bool   HasF,
                                                           const bool   HasL,
                                                           const double VFirst,
                                                           const double VLast);
};

