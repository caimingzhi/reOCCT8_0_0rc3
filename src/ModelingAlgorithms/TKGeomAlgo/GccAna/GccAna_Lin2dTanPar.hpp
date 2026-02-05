#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Lin2d.hpp>
#include <NCollection_Array1.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class gp_Pnt2d;
class gp_Lin2d;
class GccEnt_QualifiedCirc;

//! This class implements the algorithms used to create 2d
//! line tangent to a circle or a point and parallel to
//! another line.
//! The solution has the same orientation as the
//! second argument.
//! Describes functions for building a 2D line parallel to a line and:
//! -   tangential to a circle, or
//! -   passing through a point.
//! A Lin2dTanPar object provides a framework for:
//! -   defining the construction of 2D line(s),
//! -   implementing the construction algorithm, and consulting the result(s).
class GccAna_Lin2dTanPar
{
public:
  DEFINE_STANDARD_ALLOC

  //! This method implements the algorithms used to create a 2d
  //! line passing through a point and parallel to
  //! another line.
  Standard_EXPORT GccAna_Lin2dTanPar(const gp_Pnt2d& ThePoint, const gp_Lin2d& Lin1);

  //! This method implements the algorithms used to create a 2d
  //! line tangent to a circle and parallel to another line.
  //! It raises BadQualifier in case of EnclosedCirc.
  //! Exceptions
  //! GccEnt_BadQualifier if a qualifier is inconsistent with
  //! the argument it qualifies (for example, enclosed for a circle).
  Standard_EXPORT GccAna_Lin2dTanPar(const GccEnt_QualifiedCirc& Qualified1, const gp_Lin2d& Lin1);

  //! Returns True if the algorithm succeeded.
  Standard_EXPORT bool IsDone() const;

  //! Returns the number of solutions.
  //! Raises NotDone if the construction algorithm didn't succeed.
  Standard_EXPORT int NbSolutions() const;

  //! Returns the solution number Index and raises OutOfRange
  //! exception if Index is greater than the number of solutions.
  //! Be careful: the Index is only a way to get all the
  //! solutions, but is not associated to those outside the
  //! context of the algorithm-object.
  //! raises NotDone if the construction algorithm
  //! didn't succeed.
  //! It raises OutOfRange if Index is greater than the
  //! number of solutions.
  Standard_EXPORT gp_Lin2d ThisSolution(const int Index) const;

  //! Returns the information about the qualifiers of the
  //! tangency arguments concerning the solution number Index.
  //! It returns the real qualifiers (the qualifiers given to the
  //! constructor method in case of enclosed, enclosing and outside
  //! and the qualifiers computed in case of unqualified).
  //! Raises NotDone if the construction algorithm
  //! didn't succeed.
  //! It raises OutOfRange if Index is greater than the
  //! number of solutions.
  Standard_EXPORT void WhichQualifier(const int Index, GccEnt_Position& Qualif1) const;

  //! Returns information about the tangency point between the
  //! result number Index and the first argument.
  //! ParSol is the intrinsic parameter of the point on the
  //! solution curv.
  //! ParArg is the intrinsic parameter of the point on the
  //! argument curv.
  //! ParArg is equal 0 when the solution is passing through
  //! a point. Raises NotDone if the construction algorithm
  //! didn't succeed.
  //! It raises OutOfRange if Index is greater than the
  //! number of solutions.
  Standard_EXPORT void Tangency1(const int Index,
                                 double&   ParSol,
                                 double&   ParArg,
                                 gp_Pnt2d& Pnt) const;

private:
  bool                                WellDone;
  int                                 NbrSol;
  NCollection_Array1<gp_Lin2d>        linsol;
  NCollection_Array1<GccEnt_Position> qualifier1;
  NCollection_Array1<gp_Pnt2d>        pnttg1sol;
  NCollection_Array1<double>          par1sol;
  NCollection_Array1<double>          pararg1;
};
