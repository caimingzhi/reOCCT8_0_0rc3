#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Lin2d.hpp>
class gp_Pnt2d;

//! This class implements the algorithms used to
//! create the bisecting line between two 2d points
//! Describes functions for building a bisecting line between two 2D points.
//! The bisecting line between two points is the bisector of
//! the segment which joins the two points, if these are not coincident.
//! The algorithm does not find a solution if the two points are coincident.
//! A Pnt2dBisec object provides a framework for:
//! -   defining the construction of the bisecting line,
//! -   implementing the construction algorithm, and consulting the result.
class GccAna_Pnt2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a bisecting line between the points Point1 and Point2.
  Standard_EXPORT GccAna_Pnt2dBisec(const gp_Pnt2d& Point1, const gp_Pnt2d& Point2);

  //! Returns true (this construction algorithm never fails).
  Standard_EXPORT bool IsDone() const;

  //! Returns true if this algorithm has a solution, i.e. if the
  //! two points are not coincident.
  Standard_EXPORT bool HasSolution() const;

  //! Returns a line, representing the solution computed by this algorithm.
  Standard_EXPORT gp_Lin2d ThisSolution() const;

private:
  bool     WellDone;
  bool     HasSol;
  gp_Lin2d linsol;
};
