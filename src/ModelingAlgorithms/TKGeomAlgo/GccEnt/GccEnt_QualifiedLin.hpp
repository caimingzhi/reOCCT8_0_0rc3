#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GccEnt_Position.hpp>
#include <gp_Lin2d.hpp>
#include <Standard_Boolean.hpp>

//! Describes a qualified 2D line.
//! A qualified 2D line is a line (gp_Lin2d line) with a
//! qualifier which specifies whether the solution of a
//! construction algorithm using the qualified line (as an argument):
//! -   is 'enclosed' by the line, or
//! -   is built so that both the line and it are external to one another, or
//! -   is undefined (all solutions apply).
//! Note: the interior of a line is defined as the left-hand
//! side of the line in relation to its orientation (i.e. when
//! moving from the start to the end of the curve).
class GccEnt_QualifiedLin
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a qualified line by assigning the qualifier
  //! Qualifier to the line Qualified.
  //! Qualifier may be:
  //! -   GccEnt_enclosed if the solution is enclosed by the line, or
  //! -   GccEnt_outside if both the solution and the line are external to one another, or
  //! -   GccEnt_unqualified if all solutions apply.
  //! Note : the interior of a line is defined as the left-hand
  //! side of the line in relation to its orientation.
  Standard_EXPORT GccEnt_QualifiedLin(const gp_Lin2d& Qualified, const GccEnt_Position Qualifier);

  //! Returns a 2D line to which the qualifier is assigned.
  Standard_EXPORT gp_Lin2d Qualified() const;

  //! Returns the qualifier of this qualified line, if it is "enclosed" or
  //! "outside", or
  //! -   GccEnt_noqualifier if it is unqualified.
  Standard_EXPORT GccEnt_Position Qualifier() const;

  //! Returns true if the solution is unqualified and false in
  //! the other cases.
  Standard_EXPORT bool IsUnqualified() const;

  //! Returns true if the solution is Enclosed in the Lin2d and false in
  //! the other cases.
  Standard_EXPORT bool IsEnclosed() const;

  //! Returns true if the solution is Outside the Lin2d and false in
  //! the other cases.
  Standard_EXPORT bool IsOutside() const;

private:
  GccEnt_Position TheQualifier;
  gp_Lin2d        TheQualified;
};
