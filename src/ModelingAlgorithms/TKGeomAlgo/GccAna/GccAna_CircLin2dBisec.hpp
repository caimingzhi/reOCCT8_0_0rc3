#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
class GccInt_Bisec;

//! Describes functions for building bisecting curves between a 2D line and a 2D circle.
//! A bisecting curve between a circle and a line is a curve
//! such that each of its points is at the same distance from
//! the circle and the line. It can be a parabola or a line,
//! depending of the relative position of the line and the
//! circle. The algorithm computes all the elementary curves which are solutions.
//! A CircLin2dBisec object provides a framework for:
//! -   defining the construction of the bisecting curves,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GccAna_CircLin2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs bisecting curves between the circle Circle and the line Line.
  Standard_EXPORT GccAna_CircLin2dBisec(const gp_Circ2d& Circle, const gp_Lin2d& Line);

  //! Returns true (this construction algorithm never fails).
  Standard_EXPORT bool IsDone() const;

  //! Returns the number of curves, representing solutions computed by this algorithm.
  Standard_EXPORT int NbSolutions() const;

  //! Returns the solution number Index and raises OutOfRange
  //! exception if Index is greater than the number of solutions
  //! Exceptions
  //! Standard_OutOfRange if Index is less than zero or
  //! greater than the number of solutions computed by this algorithm.
  Standard_EXPORT occ::handle<GccInt_Bisec> ThisSolution(const int Index) const;

private:
  bool      WellDone;
  int       NbrSol;
  gp_Circ2d circle;
  gp_Lin2d  line;
};

