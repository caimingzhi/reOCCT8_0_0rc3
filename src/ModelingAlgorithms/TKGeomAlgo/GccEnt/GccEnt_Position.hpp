#pragma once


//! Qualifies the position of a solution of a construction
//! algorithm with respect to one of its arguments. This is one of the following:
//! -   GccEnt_unqualified: the position of the solution
//! is undefined with respect to the argument,
//! -   GccEnt_enclosing: the solution encompasses the argument,
//! -   GccEnt_enclosed: the solution is encompassed by the argument,
//! -   GccEnt_outside: the solution and the argument
//! are external to one another,
//! -   GccEnt_noqualifier: the value returned during a
//! consultation of the qualifier when the argument is
//! defined as GccEnt_unqualified.
//! Note: the interior of a line or any open curve is
//! defined as the left-hand side of the line or curve in
//! relation to its orientation.
enum GccEnt_Position
{
  GccEnt_unqualified,
  GccEnt_enclosing,
  GccEnt_enclosed,
  GccEnt_outside,
  GccEnt_noqualifier
};

