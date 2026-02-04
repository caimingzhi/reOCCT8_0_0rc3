#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
class GccInt_Bisec;

//! This class describes functions for building bisecting curves between two 2D circles.
//! A bisecting curve between two circles is a curve such
//! that each of its points is at the same distance from the
//! two circles. It can be an ellipse, hyperbola, circle or line,
//! depending on the relative position of the two circles.
//! The algorithm computes all the elementary curves which
//! are solutions. There is no solution if the two circles are coincident.
//! A Circ2dBisec object provides a framework for:
//! -   defining the construction of the bisecting curves,
//! -   implementing the construction algorithm, and consulting the result.
class GccAna_Circ2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs bisecting curves between the two circles Circ1 and Circ2.
  Standard_EXPORT GccAna_Circ2dBisec(const gp_Circ2d& Circ1, const gp_Circ2d& Circ2);

  //! This method returns True if the construction algorithm succeeded.
  Standard_EXPORT bool IsDone() const;

  //! This method returns the number of solutions.
  //! Raises NotDone if the construction algorithm didn't succeed.
  Standard_EXPORT int NbSolutions() const;

  //! Returns the solution number Index
  //! Raises OutOfRange exception if Index is greater than
  //! the number of solutions.
  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  Standard_EXPORT occ::handle<GccInt_Bisec> ThisSolution(const int Index) const;

private:
  bool      WellDone;
  int       NbrSol;
  int       intersection;
  bool      sameradius;
  gp_Circ2d circle1;
  gp_Circ2d circle2;
};

