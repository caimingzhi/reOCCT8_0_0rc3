#include <Geom2d_Curve.hpp>
#include <Geom2dLProp_Curve2dTool.hpp>
#include <Geom2dLProp_FuncCurExt.hpp>
#include <Geom2dLProp_FuncCurNul.hpp>
#include <Geom2dLProp_NumericCurInf2d.hpp>
#include <LProp_CurAndInf.hpp>
#include <math_BracketedRoot.hpp>
#include <math_FunctionRoots.hpp>
#include <Precision.hpp>

//=================================================================================================

Geom2dLProp_NumericCurInf2d::Geom2dLProp_NumericCurInf2d()
    : isDone(false)
{
}

//=================================================================================================

void Geom2dLProp_NumericCurInf2d::PerformCurExt(const occ::handle<Geom2d_Curve>& C,
                                                LProp_CurAndInf&                 Result)
{
  PerformCurExt(C,
                Geom2dLProp_Curve2dTool::FirstParameter(C),
                Geom2dLProp_Curve2dTool::LastParameter(C),
                Result);
}

//=================================================================================================

void Geom2dLProp_NumericCurInf2d::PerformCurExt(const occ::handle<Geom2d_Curve>& C,
                                                const double                     UMin,
                                                const double                     UMax,
                                                LProp_CurAndInf&                 Result)
{
  isDone = true;

  double           EpsH = 1.e-4 * (UMax - UMin);
  constexpr double Tol  = Precision::PConfusion();

  // la premiere recherce se fait avec une tolerance assez grande
  // car la derivee de la fonction est estimee assez grossierement.

  Geom2dLProp_FuncCurExt F(C, EpsH);
  int                    NbSamples = 100;
  bool                   SolType;

  math_FunctionRoots SolRoot(F, UMin, UMax, NbSamples, EpsH, EpsH, EpsH);

  if (SolRoot.IsDone())
  {
    for (int j = 1; j <= SolRoot.NbSolutions(); j++)
    {
      double Param = SolRoot.Value(j);
      // la solution est affinee.
      math_BracketedRoot BS(F, Param - EpsH, Param + EpsH, Tol);
      if (BS.IsDone())
      {
        Param = BS.Root();
      }
      SolType = F.IsMinKC(Param);
      Result.AddExtCur(Param, SolType);
    }
  }
  else
  {
    isDone = false;
  }
}

//=================================================================================================

void Geom2dLProp_NumericCurInf2d::PerformInf(const occ::handle<Geom2d_Curve>& C,
                                             LProp_CurAndInf&                 Result)
{
  PerformInf(C,
             Geom2dLProp_Curve2dTool::FirstParameter(C),
             Geom2dLProp_Curve2dTool::LastParameter(C),
             Result);
}

//=================================================================================================

void Geom2dLProp_NumericCurInf2d::PerformInf(const occ::handle<Geom2d_Curve>& C,
                                             const double                     UMin,
                                             const double                     UMax,
                                             LProp_CurAndInf&                 Result)
{
  isDone = true;
  Geom2dLProp_FuncCurNul F(C);
  double                 EpsX      = 1.e-6;
  double                 EpsF      = 1.e-6;
  int                    NbSamples = 30;

  math_FunctionRoots SolRoot(F, UMin, UMax, NbSamples, EpsX, EpsF, EpsX);

  if (SolRoot.IsDone())
  {
    for (int j = 1; j <= SolRoot.NbSolutions(); j++)
    {
      Result.AddInflection(SolRoot.Value(j));
    }
  }
  else
  {
    isDone = false;
  }
}

//=================================================================================================

bool Geom2dLProp_NumericCurInf2d::IsDone() const
{
  return isDone;
}
