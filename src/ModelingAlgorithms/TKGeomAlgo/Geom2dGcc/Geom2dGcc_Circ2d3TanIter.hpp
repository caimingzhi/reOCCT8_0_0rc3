#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Circ2d.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class GccEnt_QualifiedCirc;
class Geom2dGcc_QCurve;
class GccEnt_QualifiedLin;

//! This class implements the algorithms used to
//! create 2d circles tangent to 3 points/lines/circles/
//! curves with one curve or more.
//! The arguments of all construction methods are :
//! - The three qualifiied elements for the
//! tangency constrains (QualifiedCirc, QualifiedLine,
//! Qualifiedcurv, Points).
//! - A parameter for each QualifiedCurv.
class Geom2dGcc_Circ2d3TanIter
{
public:
  DEFINE_STANDARD_ALLOC

  //! This method implements the algorithms used to
  //! create 2d circles tangent to 2 circles and a curve.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                           const GccEnt_QualifiedCirc& Qualified2,
                                           const Geom2dGcc_QCurve&     Qualified3,
                                           const double                Param1,
                                           const double                Param2,
                                           const double                Param3,
                                           const double                Tolerance);

  //! This method implements the algorithms used to
  //! create 2d circles tangent to a circle and 2 curves.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                           const Geom2dGcc_QCurve&     Qualified2,
                                           const Geom2dGcc_QCurve&     Qualified3,
                                           const double                Param1,
                                           const double                Param2,
                                           const double                Param3,
                                           const double                Tolerance);

  //! This method implements the algorithms used to
  //! create 2d circles tangent to a circle and a line and
  //! a curve.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                           const GccEnt_QualifiedLin&  Qualified2,
                                           const Geom2dGcc_QCurve&     Qualified3,
                                           const double                Param1,
                                           const double                Param2,
                                           const double                Param3,
                                           const double                Tolerance);

  //! This method implements the algorithms used to
  //! create 2d circles tangent to a circle and a point and
  //! a curve.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                           const Geom2dGcc_QCurve&     Qualified2,
                                           const gp_Pnt2d&             Point3,
                                           const double                Param1,
                                           const double                Param2,
                                           const double                Tolerance);

  //! This method implements the algorithms used to
  //! create 2d circles tangent to 2 lines and a curve.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedLin& Qualified1,
                                           const GccEnt_QualifiedLin& Qualified2,
                                           const Geom2dGcc_QCurve&    Qualified3,
                                           const double               Param1,
                                           const double               Param2,
                                           const double               Param3,
                                           const double               Tolerance);

  //! This method implements the algorithms used to
  //! create 2d circles tangent to a line and 2 curves.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedLin& Qualified1,
                                           const Geom2dGcc_QCurve&    Qualified2,
                                           const Geom2dGcc_QCurve&    Qualified3,
                                           const double               Param1,
                                           const double               Param2,
                                           const double               Param3,
                                           const double               Tolerance);

  //! This method implements the algorithms used to
  //! create 2d circles tangent to a line and a curve
  //! and a point.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedLin& Qualified1,
                                           const Geom2dGcc_QCurve&    Qualified2,
                                           const gp_Pnt2d&            Point3,
                                           const double               Param1,
                                           const double               Param2,
                                           const double               Tolerance);

  //! This method implements the algorithms used to
  //! create 2d circles tangent to a curve and 2 points.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const Geom2dGcc_QCurve& Qualified1,
                                           const gp_Pnt2d&         Point1,
                                           const gp_Pnt2d&         Point2,
                                           const double            Param1,
                                           const double            Tolerance);

  //! This method implements the algorithms used to
  //! create 2d circles tangent to 2 curves and a point.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const Geom2dGcc_QCurve& Qualified1,
                                           const Geom2dGcc_QCurve& Qualified2,
                                           const gp_Pnt2d&         Point2,
                                           const double            Param1,
                                           const double            Param2,
                                           const double            Tolerance);

  //! This method implements the algorithms used to
  //! create 2d circles tangent to 3 curves.
  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const Geom2dGcc_QCurve& Qualified1,
                                           const Geom2dGcc_QCurve& Qualified2,
                                           const Geom2dGcc_QCurve& Qualified3,
                                           const double            Param1,
                                           const double            Param2,
                                           const double            Param3,
                                           const double            Tolerance);

  //! This method returns True if the construction
  //! algorithm succeeded.
  Standard_EXPORT bool IsDone() const;

  //! Returns the solution.
  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  Standard_EXPORT gp_Circ2d ThisSolution() const;

  Standard_EXPORT void WhichQualifier(GccEnt_Position& Qualif1,
                                      GccEnt_Position& Qualif2,
                                      GccEnt_Position& Qualif3) const;

  //! Returns information about the tangency point between
  //! the result and the first argument.
  //! ParSol is the intrinsic parameter of the point PntSol
  //! on the solution curv.
  //! ParArg is the intrinsic parameter of the point PntSol
  //! on the argument curv.
  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  Standard_EXPORT void Tangency1(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  //! Returns information about the tangency point between
  //! the result and the second argument.
  //! ParSol is the intrinsic parameter of the point PntSol
  //! on the solution curv.
  //! ParArg is the intrinsic parameter of the point PntSol
  //! on the argument curv.
  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  Standard_EXPORT void Tangency2(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  //! Returns information about the tangency point between
  //! the result and the third argument.
  //! ParSol is the intrinsic parameter of the point PntSol
  //! on the solution curv.
  //! ParArg is the intrinsic parameter of the point PntSol
  //! on the argument curv.
  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  Standard_EXPORT void Tangency3(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  Standard_EXPORT bool IsTheSame1() const;

  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  Standard_EXPORT bool IsTheSame2() const;

  //! It raises NotDone if the construction algorithm
  //! didn't succeed.
  Standard_EXPORT bool IsTheSame3() const;

private:
  bool            WellDone;
  gp_Circ2d       cirsol;
  GccEnt_Position qualifier1;
  GccEnt_Position qualifier2;
  GccEnt_Position qualifier3;
  bool            TheSame1;
  bool            TheSame2;
  bool            TheSame3;
  gp_Pnt2d        pnttg1sol;
  gp_Pnt2d        pnttg2sol;
  gp_Pnt2d        pnttg3sol;
  double          par1sol;
  double          par2sol;
  double          par3sol;
  double          pararg1;
  double          pararg2;
  double          pararg3;
};
