#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

#include <math_Vector.hpp>
#include <math_Matrix.hpp>

#include <gp_Vec2d.hpp>
#include <gp_Pnt2d.hpp>

#define THECURVE1 (*((TheCurve*)thecurve1))
#define THECURVE2 (*((TheCurve*)thecurve2))

//=================================================================================================

IntCurve_DistBetweenPCurvesGen::IntCurve_DistBetweenPCurvesGen(const TheCurve& C1,
                                                               const TheCurve& C2)
{
  thecurve1 = (void*)(&C1);
  thecurve2 = (void*)(&C2);
}

//=================================================================================================

int IntCurve_DistBetweenPCurvesGen::NbVariables(void) const
{
  return (2);
}

//=================================================================================================

int IntCurve_DistBetweenPCurvesGen::NbEquations(void) const
{
  return (2);
}

//=================================================================================================

bool IntCurve_DistBetweenPCurvesGen::Value(const math_Vector& X, math_Vector& F)
{
  gp_Pnt2d P1, P2;
  TheCurveTool::D0(THECURVE1, X(1), P1);
  TheCurveTool::D0(THECURVE2, X(2), P2);
  F(1) = P1.X() - P2.X();
  F(2) = P1.Y() - P2.Y();
  return (true);
}

//=================================================================================================

bool IntCurve_DistBetweenPCurvesGen::Derivatives(const math_Vector& X, math_Matrix& D)
{
  gp_Vec2d T;
  gp_Pnt2d P;
  TheCurveTool::D1(THECURVE1, X(1), P, T);
  D.Value(1, 1) = T.X();
  D.Value(2, 1) = T.Y();

  TheCurveTool::D1(THECURVE2, X(2), P, T);
  D.Value(1, 2) = -(T.X());
  D.Value(2, 2) = -(T.Y());

  return (true);
}

//=================================================================================================

bool IntCurve_DistBetweenPCurvesGen::Values(const math_Vector& X, math_Vector& F, math_Matrix& D)
{

  gp_Vec2d T;
  gp_Pnt2d P1, P2;

  TheCurveTool::D1(THECURVE1, X(1), P1, T);
  D.Value(1, 1) = T.X();
  D.Value(2, 1) = T.Y();

  TheCurveTool::D1(THECURVE2, X(2), P2, T);
  D.Value(1, 2) = -(T.X());
  D.Value(2, 2) = -(T.Y());

  F.Value(1) = P1.X() - P2.X();
  F.Value(2) = P1.Y() - P2.Y();

  return (true);
}

//======================================================================
