#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
#include <NCollection_Array1.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class Geom2dGcc_QCurve;
class gp_Pnt2d;
class gp_Circ2d;

//! This class implements the algorithms used to
//! create 2d circles tangent to a curve and
//! centered on a point.
//! The arguments of all construction methods are :
//! - The qualified element for the tangency constrains
//! (QualifiedCurv).
//! -The center point Pcenter.
//! - A real Tolerance.
//! Tolerance is only used in the limits cases.
//! For example :
//! We want to create a circle tangent to an EnclosedCurv C1
//! with a tolerance Tolerance.
//! If we did not use Tolerance it is impossible to
//! find a solution in the following case : Pcenter is
//! outside C1.
//! With Tolerance we will give a solution if the distance
//! between C1 and Pcenter is lower than or equal Tolerance/2.
class Geom2dGcc_Circ2dTanCenGeo
{
public:
  DEFINE_STANDARD_ALLOC

  //! This method implements the algorithms used to
  //! create 2d circles tangent to a circle and
  //! centered on a point.
  Standard_EXPORT Geom2dGcc_Circ2dTanCenGeo(const Geom2dGcc_QCurve& Qualified1,
                                            const gp_Pnt2d&         Pcenter,
                                            const double            Tolerance);

  //! This method returns True if the construction
  //! algorithm succeeded.
  Standard_EXPORT bool IsDone() const;

  //! Returns the number of solutions and raises NotDone
  //! exception if the algorithm didn't succeed.
  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  Standard_EXPORT int NbSolutions() const;

  //! Returns the solution number Index and raises OutOfRange
  //! exception if Index is greater than the number of solutions.
  //! Be careful: the Index is only a way to get all the
  //! solutions, but is not associated to these outside the
  //! context of the algorithm-object.
  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  //! It raises OutOfRange if Index is greater than the
  //! number of solutions or less than zero.
  Standard_EXPORT gp_Circ2d ThisSolution(const int Index) const;

  Standard_EXPORT void WhichQualifier(const int Index, GccEnt_Position& Qualif1) const;

  //! Returns information about the tangency point between the
  //! result number Index and the first argument.
  //! ParSol is the intrinsic parameter of the point PntSol
  //! on the solution curv.
  //! ParArg is the intrinsic parameter of the point PntArg
  //! on the argument curv.
  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  //! It raises OutOfRange if Index is greater than the
  //! number of solutions or less than zero.
  Standard_EXPORT void Tangency1(const int Index,
                                 double&   ParSol,
                                 double&   ParArg,
                                 gp_Pnt2d& PntSol) const;

private:
  bool                                WellDone;
  int                                 NbrSol;
  NCollection_Array1<gp_Circ2d>       cirsol;
  NCollection_Array1<GccEnt_Position> qualifier1;
  NCollection_Array1<gp_Pnt2d>        pnttg1sol;
  NCollection_Array1<double>          par1sol;
  NCollection_Array1<double>          pararg1;
};
