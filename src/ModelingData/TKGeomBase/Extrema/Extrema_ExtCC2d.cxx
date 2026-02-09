#include <Adaptor2d_Curve2d.hpp>
#include <ElCLib.hpp>
#include <Extrema_Curve2dTool.hpp>
#include <Extrema_ECC2d.hpp>
#include <Extrema_ExtCC2d.hpp>
#include <Extrema_ExtElC2d.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <NCollection_Sequence.hpp>
#include <GeomAbs_CurveType.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>
#include <Standard_MemoryUtils.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

Extrema_ExtCC2d::Extrema_ExtCC2d()
    : myIsFindSingleSolution(false),
      myDone(false),
      myIsPar(false),
      mynbext(0),
      inverse(false),
      myC(nullptr),
      myv1(0.0),
      myv2(0.0),
      mytolc1(0.0),
      mytolc2(0.0),
      mydist11(0.0),
      mydist12(0.0),
      mydist21(0.0),
      mydist22(0.0)
{
}

Extrema_ExtCC2d::Extrema_ExtCC2d(const Adaptor2d_Curve2d& C1,
                                 const Adaptor2d_Curve2d& C2,
                                 const double             TolC1,
                                 const double             TolC2)
    : myIsFindSingleSolution(false)
{
  Initialize(C2,
             Extrema_Curve2dTool::FirstParameter(C2),
             Extrema_Curve2dTool::LastParameter(C2),
             TolC1,
             TolC2);
  Perform(C1, Extrema_Curve2dTool::FirstParameter(C1), Extrema_Curve2dTool::LastParameter(C1));
}

Extrema_ExtCC2d::Extrema_ExtCC2d(const Adaptor2d_Curve2d& C1,
                                 const Adaptor2d_Curve2d& C2,
                                 const double             U1,
                                 const double             U2,
                                 const double             V1,
                                 const double             V2,
                                 const double             TolC1,
                                 const double             TolC2)
    : myIsFindSingleSolution(false)
{
  Initialize(C2, V1, V2, TolC1, TolC2);
  Perform(C1, U1, U2);
}

void Extrema_ExtCC2d::Initialize(const Adaptor2d_Curve2d& C2,
                                 const double             V1,
                                 const double             V2,
                                 const double             TolC1,
                                 const double             TolC2)
{
  myC     = &C2;
  myv1    = V1;
  myv2    = V2;
  mytolc1 = TolC1;
  mytolc2 = TolC2;
}

void Extrema_ExtCC2d::Perform(const Adaptor2d_Curve2d& C1, const double U1, const double U2)
{
  mypoints.Clear();
  mySqDist.Clear();
  GeomAbs_CurveType type1 = Extrema_Curve2dTool::GetType(C1),
                    type2 = Extrema_Curve2dTool::GetType(*myC);
  double U11, U12, U21, U22, Tol = std::min(mytolc1, mytolc2);

  mynbext = 0;
  inverse = false;
  myIsPar = false;

  U11 = U1;
  U12 = U2;
  U21 = myv1;
  U22 = myv2;
  P1f = Extrema_Curve2dTool::Value(C1, U11);
  P1l = Extrema_Curve2dTool::Value(C1, U12);
  P2f = Extrema_Curve2dTool::Value(*myC, U21);
  P2l = Extrema_Curve2dTool::Value(*myC, U22);

  std::shared_ptr<Extrema_ExtElC2d> aXtream;
  std::shared_ptr<Extrema_ECC2d>    aParamSolver;

  switch (type1)
  {

    case GeomAbs_Circle:
    {

      switch (type2)
      {
        case GeomAbs_Line:
        {
          inverse = true;
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Line(*myC),
                                                               Extrema_Curve2dTool::Circle(C1),
                                                               Tol);
          Results(*aXtream, U11, U12, U21, U22, 2 * M_PI, 0.);
        }
        break;
        case GeomAbs_Circle:
        {
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Circle(C1),
                                                               Extrema_Curve2dTool::Circle(*myC));
          Results(*aXtream, U11, U12, U21, U22, 2 * M_PI, 2 * M_PI);
        }
        break;
        case GeomAbs_Ellipse:
        {
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Circle(C1),
                                                               Extrema_Curve2dTool::Ellipse(*myC));
          Results(*aXtream, U11, U12, U21, U22, 2 * M_PI, 2 * M_PI);
        }
        break;
        case GeomAbs_Parabola:
        {
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Circle(C1),
                                                               Extrema_Curve2dTool::Parabola(*myC));
          Results(*aXtream, U11, U12, U21, U22, 2 * M_PI, 0.);
        }
        break;
        case GeomAbs_Hyperbola:
        {
          aXtream =
            opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Circle(C1),
                                                       Extrema_Curve2dTool::Hyperbola(*myC));
          Results(*aXtream, U11, U12, U21, U22, 2 * M_PI, 0.);
        }
        break;
        default:
        {
          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          double Period2 = 0.;
          if (Extrema_Curve2dTool::IsPeriodic(*myC))
            Period2 = Extrema_Curve2dTool::Period(*myC);
          Results(*aParamSolver, U11, U12, U21, U22, 2 * M_PI, Period2);
        }
        break;
      };
    }
    break;

    case GeomAbs_Ellipse:
    {

      switch (type2)
      {
        case GeomAbs_Line:
        {
          inverse = true;
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Line(*myC),
                                                               Extrema_Curve2dTool::Ellipse(C1));
          Results(*aXtream, U11, U12, U21, U22, 2 * M_PI, 0.);
        }
        break;
        case GeomAbs_Circle:
        {
          inverse = true;
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Circle(*myC),
                                                               Extrema_Curve2dTool::Ellipse(C1));
          Results(*aXtream, U11, U12, U21, U22, 2 * M_PI, 2 * M_PI);
        }
        break;
        case GeomAbs_Ellipse:
        {
          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          Results(*aParamSolver, U11, U12, U21, U22, 2 * M_PI, 2 * M_PI);
        }
        break;
        case GeomAbs_Parabola:
        {

          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          Results(*aParamSolver, U11, U12, U21, U22, 2 * M_PI, 0.);
        }
        break;
        case GeomAbs_Hyperbola:
        {

          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          Results(*aParamSolver, U11, U12, U21, U22, 2 * M_PI, 0.);
        }
        break;
        default:
        {
          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          double Period2 = 0.;
          if (Extrema_Curve2dTool::IsPeriodic(*myC))
            Period2 = Extrema_Curve2dTool::Period(*myC);
          Results(*aParamSolver, U11, U12, U21, U22, 2 * M_PI, Period2);
        }
        break;
      };
    }
    break;

    case GeomAbs_Parabola:
    {

      switch (type2)
      {
        case GeomAbs_Line:
        {
          inverse = true;
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Line(*myC),
                                                               Extrema_Curve2dTool::Parabola(C1));
          Results(*aXtream, U11, U12, U21, U22, 0., 0.);
        }
        break;
        case GeomAbs_Circle:
        {
          inverse = true;
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Circle(*myC),
                                                               Extrema_Curve2dTool::Parabola(C1));
          Results(*aXtream, U11, U12, U21, U22, 0., 2 * M_PI);
        }
        break;
        case GeomAbs_Ellipse:
        {

          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          Results(*aParamSolver, U11, U12, U21, U22, 0., 2 * M_PI);
        }
        break;
        case GeomAbs_Parabola:
        {

          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          Results(*aParamSolver, U11, U12, U21, U22, 0., 0.);
        }
        break;
        case GeomAbs_Hyperbola:
        {

          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          Results(*aParamSolver, U11, U12, U21, U22, 0., 0.);
        }
        break;
        default:
        {
          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          double Period2 = 0.;
          if (Extrema_Curve2dTool::IsPeriodic(*myC))
            Period2 = Extrema_Curve2dTool::Period(*myC);
          Results(*aParamSolver, U11, U12, U21, U22, 0., Period2);
        }
        break;
      };
    }
    break;

    case GeomAbs_Hyperbola:
    {

      switch (type2)
      {
        case GeomAbs_Line:
        {
          inverse = true;
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Line(*myC),
                                                               Extrema_Curve2dTool::Hyperbola(C1));
          Results(*aXtream, U11, U12, U21, U22, 0., 0.);
        }
        break;
        case GeomAbs_Circle:
        {
          inverse = true;
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Circle(*myC),
                                                               Extrema_Curve2dTool::Hyperbola(C1));
          Results(*aXtream, U11, U12, U21, U22, 0., 2 * M_PI);
        }
        break;
        case GeomAbs_Ellipse:
        {

          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          Results(*aParamSolver, U11, U12, U21, U22, 0., 2 * M_PI);
        }
        break;
        case GeomAbs_Parabola:
        {

          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          Results(*aParamSolver, U11, U12, U21, U22, 0., 0.);
        }
        break;
        case GeomAbs_Hyperbola:
        {

          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          Results(*aParamSolver, U11, U12, U21, U22, 0., 0.);
        }
        break;
        default:
        {
          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          double Period2 = 0.;
          if (Extrema_Curve2dTool::IsPeriodic(*myC))
            Period2 = Extrema_Curve2dTool::Period(*myC);
          Results(*aParamSolver, U11, U12, U21, U22, 0., Period2);
        }
        break;
      };
    }
    break;

    case GeomAbs_Line:
    {

      switch (type2)
      {
        case GeomAbs_Line:
        {
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Line(C1),
                                                               Extrema_Curve2dTool::Line(*myC),
                                                               Tol);
          Results(*aXtream, U11, U12, U21, U22, 0., 0.);
        }
        break;
        case GeomAbs_Circle:
        {
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Line(C1),
                                                               Extrema_Curve2dTool::Circle(*myC),
                                                               Tol);
          Results(*aXtream, U11, U12, U21, U22, 0., 2 * M_PI);
        }
        break;
        case GeomAbs_Ellipse:
        {
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Line(C1),
                                                               Extrema_Curve2dTool::Ellipse(*myC));
          Results(*aXtream, U11, U12, U21, U22, 0., 2 * M_PI);
        }
        break;
        case GeomAbs_Parabola:
        {
          aXtream = opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Line(C1),
                                                               Extrema_Curve2dTool::Parabola(*myC));
          Results(*aXtream, U11, U12, U21, U22, 0., 0.);
        }
        break;
        case GeomAbs_Hyperbola:
        {
          aXtream =
            opencascade::make_shared<Extrema_ExtElC2d>(Extrema_Curve2dTool::Line(C1),
                                                       Extrema_Curve2dTool::Hyperbola(*myC));
          Results(*aXtream, U11, U12, U21, U22, 0., 0.);
        }
        break;
        default:
        {
          aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
          aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
          aParamSolver->Perform();
          double Period2 = 0.;
          if (Extrema_Curve2dTool::IsPeriodic(*myC))
            Period2 = Extrema_Curve2dTool::Period(*myC);
          Results(*aParamSolver, U11, U12, U21, U22, 0., Period2);
        }
        break;
      };
    }
    break;

    default:
    {
      aParamSolver = opencascade::make_shared<Extrema_ECC2d>(C1, *myC);
      aParamSolver->SetSingleSolutionFlag(GetSingleSolutionFlag());
      aParamSolver->Perform();
      double Period1 = 0.;
      if (Extrema_Curve2dTool::IsPeriodic(C1))
        Period1 = Extrema_Curve2dTool::Period(C1);
      double Period2 = 0.;
      if (Extrema_Curve2dTool::IsPeriodic(*myC))
        Period2 = Extrema_Curve2dTool::Period(*myC);
      Results(*aParamSolver, U11, U12, U21, U22, Period1, Period2);
    }
    break;
  };
}

bool Extrema_ExtCC2d::IsDone() const
{
  return myDone;
}

double Extrema_ExtCC2d::SquareDistance(const int N) const
{
  if (!myDone)
    throw StdFail_NotDone();
  if ((N <= 0) || (N > mynbext))
    throw Standard_OutOfRange();
  return mySqDist.Value(N);
}

int Extrema_ExtCC2d::NbExt() const
{
  if (!myDone)
    throw StdFail_NotDone();
  return mynbext;
}

void Extrema_ExtCC2d::Points(const int N, Extrema_POnCurv2d& P1, Extrema_POnCurv2d& P2) const
{
  if (!myDone)
    throw StdFail_NotDone();
  if ((N <= 0) || (N > mynbext))
    throw Standard_OutOfRange();
  P1 = mypoints.Value(2 * N - 1);
  P2 = mypoints.Value(2 * N);
}

void Extrema_ExtCC2d::TrimmedSquareDistances(double&   dist11,
                                             double&   dist12,
                                             double&   dist21,
                                             double&   dist22,
                                             gp_Pnt2d& P11,
                                             gp_Pnt2d& P12,
                                             gp_Pnt2d& P21,
                                             gp_Pnt2d& P22) const
{
  dist11 = mydist11;
  dist12 = mydist12;
  dist21 = mydist21;
  dist22 = mydist22;
  P11    = P1f;
  P12    = P1l;
  P21    = P2f;
  P22    = P2l;
}

void Extrema_ExtCC2d::Results(const Extrema_ExtElC2d& AlgExt,
                              const double            Ut11,
                              const double            Ut12,
                              const double            Ut21,
                              const double            Ut22,
                              const double            Period1,
                              const double            Period2)
{
  int               i, NbExt;
  double            Val, U, U2;
  Extrema_POnCurv2d P1, P2;

  myDone  = AlgExt.IsDone();
  myIsPar = AlgExt.IsParallel();
  if (myDone)
  {
    if (!myIsPar)
    {
      NbExt = AlgExt.NbExt();
      for (i = 1; i <= NbExt; i++)
      {

        AlgExt.Points(i, P1, P2);
        if (!inverse)
        {
          U = P1.Parameter();
          if (Period1 != 0.0)
            U = ElCLib::InPeriod(U, Ut11, Ut11 + Period1);
          U2 = P2.Parameter();
          if (Period2 != 0.0)
            U2 = ElCLib::InPeriod(U2, Ut21, Ut21 + Period2);
        }
        else
        {
          U2 = P1.Parameter();
          if (Period2 != 0.0)
            U2 = ElCLib::InPeriod(U2, Ut21, Ut21 + Period2);
          U = P2.Parameter();
          if (Period1 != 0.0)
            U = ElCLib::InPeriod(U, Ut11, Ut11 + Period1);
        }
        if ((U >= Ut11 - Precision::PConfusion()) && (U <= Ut12 + Precision::PConfusion())
            && (U2 >= Ut21 - Precision::PConfusion()) && (U2 <= Ut22 + Precision::PConfusion()))
        {
          mynbext++;
          Val = AlgExt.SquareDistance(i);
          mySqDist.Append(Val);
          if (!inverse)
          {
            P1.SetValues(U, P1.Value());
            P2.SetValues(U2, P2.Value());
            mypoints.Append(P1);
            mypoints.Append(P2);
          }
          else
          {
            P1.SetValues(U2, P1.Value());
            P2.SetValues(U, P2.Value());
            mypoints.Append(P2);
            mypoints.Append(P1);
          }
        }
      }
    }

    mydist11 = P1f.SquareDistance(P2f);
    mydist12 = P1f.SquareDistance(P2l);
    mydist21 = P1l.SquareDistance(P2f);
    mydist22 = P1l.SquareDistance(P2l);
  }
}

void Extrema_ExtCC2d::Results(const Extrema_ECC2d& AlgExt,
                              const double         Ut11,
                              const double         Ut12,
                              const double         Ut21,
                              const double         Ut22,
                              const double         Period1,
                              const double         Period2)
{
  int               i, NbExt;
  double            Val, U, U2;
  Extrema_POnCurv2d P1, P2;

  myDone = AlgExt.IsDone();
  if (myDone)
  {
    myIsPar = AlgExt.IsParallel();
    NbExt   = AlgExt.NbExt();
    for (i = 1; i <= NbExt; i++)
    {

      AlgExt.Points(i, P1, P2);
      U = P1.Parameter();
      if (Period1 != 0.0)
        U = ElCLib::InPeriod(U, Ut11, Ut11 + Period1);
      U2 = P2.Parameter();
      if (Period2 != 0.0)
        U2 = ElCLib::InPeriod(U2, Ut21, Ut21 + Period2);

      if ((U >= Ut11 - Precision::PConfusion()) && (U <= Ut12 + Precision::PConfusion())
          && (U2 >= Ut21 - Precision::PConfusion()) && (U2 <= Ut22 + Precision::PConfusion()))
      {
        mynbext++;
        Val = AlgExt.SquareDistance(i);
        P1.SetValues(U, P1.Value());
        P2.SetValues(U2, P2.Value());
        mySqDist.Append(Val);
        mypoints.Append(P1);
        mypoints.Append(P2);
      }
    }

    mydist11 = P1f.SquareDistance(P2f);
    mydist12 = P1f.SquareDistance(P2l);
    mydist21 = P1l.SquareDistance(P2f);
    mydist22 = P1l.SquareDistance(P2l);
  }
}

bool Extrema_ExtCC2d::IsParallel() const
{
  if (!myDone)
    throw StdFail_NotDone();
  return myIsPar;
}

void Extrema_ExtCC2d::SetSingleSolutionFlag(const bool theFlag)
{
  myIsFindSingleSolution = theFlag;
}

bool Extrema_ExtCC2d::GetSingleSolutionFlag() const
{
  return myIsFindSingleSolution;
}
