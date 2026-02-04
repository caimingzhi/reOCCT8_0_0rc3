#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class GccInt_Bisec;
class gp_Lin2d;
class gp_Pnt2d;

//! Describes functions for building bisecting curves between a 2D line and a point.
//! A bisecting curve between a line and a point is such a
//! curve that each of its points is at the same distance from
//! the circle and the point. It can be a parabola or a line,
//! depending on the relative position of the line and the
//! circle. There is always one unique solution.
//! A LinPnt2dBisec object provides a framework for:
//! - defining the construction of the bisecting curve,
//! - implementing the construction algorithm, and
//! - consulting the result.
class GccAna_LinPnt2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a bisecting curve between the line Line1 and the point Point2.
  Standard_EXPORT GccAna_LinPnt2dBisec(const gp_Lin2d& Line1, const gp_Pnt2d& Point2);

  //! Returns True if the algorithm succeeded.
  Standard_EXPORT bool IsDone() const;

  //! Returns the number of solutions.
  //! It raises NotDone if the construction algorithm didn't succeed.
  Standard_EXPORT occ::handle<GccInt_Bisec> ThisSolution() const;

private:
  bool                      WellDone;
  occ::handle<GccInt_Bisec> bissol;
};

