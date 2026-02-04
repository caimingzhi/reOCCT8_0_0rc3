#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Lin2d.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class Geom2dGcc_QCurve;
class GccEnt_QualifiedCirc;

//! This class implements the algorithms used to
//! create 2d lines tangent to 2 other elements which
//! can be circles, curves or points.
//! More than one argument must be a curve.
//!
//! Note: Some constructors may check the type of the qualified argument
//! and raise BadQualifier Error in case of incorrect couple (qualifier,
//! curv).
//! For example: "EnclosedCirc".
class Geom2dGcc_Lin2d2TanIter
{
public:
  DEFINE_STANDARD_ALLOC

  //! This class implements the algorithms used to create 2d
  //! lines passing through a point and tangent to a curve.
  //! Tolang is used to determine the tolerance for the
  //! tangency points.
  //! Param2 is used for the initial guess on the curve.
  Standard_EXPORT Geom2dGcc_Lin2d2TanIter(const Geom2dGcc_QCurve& Qualified1,
                                          const gp_Pnt2d&         ThePoint,
                                          const double            Param1,
                                          const double            Tolang);

  //! This class implements the algorithms used to create 2d
  //! line tangent to a circle and to a curve.
  //! Tolang is used to determine the tolerance for the
  //! tangency points.
  //! Param2 is used for the initial guess on the curve.
  //! Exception BadQualifier is raised in the case of
  //! EnclosedCirc
  Standard_EXPORT Geom2dGcc_Lin2d2TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                          const Geom2dGcc_QCurve&     Qualified2,
                                          const double                Param2,
                                          const double                Tolang);

  //! This class implements the algorithms used to create 2d
  //! line tangent to two curves.
  //! Tolang is used to determine the tolerance for the
  //! tangency points.
  //! Param1 is used for the initial guess on the first curve.
  //! Param2 is used for the initial guess on the second curve.
  Standard_EXPORT Geom2dGcc_Lin2d2TanIter(const Geom2dGcc_QCurve& Qualified1,
                                          const Geom2dGcc_QCurve& Qualified2,
                                          const double            Param1,
                                          const double            Param2,
                                          const double            Tolang);

  //! This methode returns true when there is a solution
  //! and false in the other cases.
  Standard_EXPORT bool IsDone() const;

  //! Returns the solution.
  Standard_EXPORT gp_Lin2d ThisSolution() const;

  Standard_EXPORT void WhichQualifier(GccEnt_Position& Qualif1, GccEnt_Position& Qualif2) const;

  //! Returns information about the tangency point between the
  //! result and the first argument.
  //! ParSol is the intrinsic parameter of the point PntSol on
  //! the solution curv.
  //! ParArg is the intrinsic parameter of the point PntSol on
  //! the argument curv.
  Standard_EXPORT void Tangency1(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT void Tangency2(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

private:
  bool            WellDone;
  gp_Lin2d        linsol;
  GccEnt_Position qualifier1;
  GccEnt_Position qualifier2;
  gp_Pnt2d        pnttg1sol;
  gp_Pnt2d        pnttg2sol;
  double          par1sol;
  double          par2sol;
  double          pararg1;
  double          pararg2;
};

