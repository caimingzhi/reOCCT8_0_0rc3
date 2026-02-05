#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Real.hpp>
class GccInt_Bisec;

//! Describes functions for building a bisecting curve
//! between a 2D circle and a point.
//! A bisecting curve between a circle and a point is such a
//! curve that each of its points is at the same distance from
//! the circle and the point. It can be an ellipse, hyperbola,
//! circle or line, depending on the relative position of the
//! point and the circle. The algorithm computes all the
//! elementary curves which are solutions.
//! A CircPnt2dBisec object provides a framework for:
//! -   defining the construction of the bisecting curves,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GccAna_CircPnt2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs bisecting curves between the circle Circle1 and the point Point2.
  Standard_EXPORT GccAna_CircPnt2dBisec(const gp_Circ2d& Circle1, const gp_Pnt2d& Point2);

  //! Constructs bisecting curves between the circle Circle1 and the point Point2.
  //! Tolerance is used.
  Standard_EXPORT GccAna_CircPnt2dBisec(const gp_Circ2d& Circle1,
                                        const gp_Pnt2d&  Point2,
                                        const double     Tolerance);

  //! Returns true (this construction algorithm never fails).
  Standard_EXPORT bool IsDone() const;

  //! Returns the number of curves, representing solutions computed by this algorithm.
  Standard_EXPORT int NbSolutions() const;

  //! Returns the solution number Index and raises OutOfRange
  //! exception if Index is greater than the number of solutions.
  //! Exceptions
  //! Standard_OutOfRange if Index is less than zero or
  //! greater than the number of solutions computed by this algorithm.
  Standard_EXPORT occ::handle<GccInt_Bisec> ThisSolution(const int Index) const;

private:
  //! Defines the number and the type of solutions
  //! depending on input data
  Standard_EXPORT void DefineSolutions();

  bool      WellDone;
  int       NbrSol;
  gp_Circ2d circle;
  gp_Pnt2d  point;
  int       theposition;
  double    myTolerance;
};
