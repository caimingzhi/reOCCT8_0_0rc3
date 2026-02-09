

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_BrentMinimum.hpp>
#include <math_Function.hpp>
#include <math_FunctionSetRoot.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Gauss.hpp>
#include <math_GaussLeastSquare.hpp>
#include <math_IntegerVector.hpp>
#include <math_Matrix.hpp>
#include <math_SVD.hpp>
#include <Precision.hpp>
#include <Standard_DimensionError.hpp>
#include <StdFail_NotDone.hpp>

#define FSR_DEBUG(arg)

class MyDirFunction : public math_Function
{

  math_Vector*                     P0;
  math_Vector*                     Dir;
  math_Vector*                     P;
  math_Vector*                     FV;
  math_FunctionSetWithDerivatives* F;

public:
  MyDirFunction(math_Vector&                     V1,
                math_Vector&                     V2,
                math_Vector&                     V3,
                math_Vector&                     V4,
                math_FunctionSetWithDerivatives& f);

  void Initialize(const math_Vector& p0, const math_Vector& dir) const;

  bool Value(const math_Vector& Sol,
             math_Vector&       FF,
             math_Matrix&       DF,
             math_Vector&       GH,
             double&            F2,
             double&            Gnr1);

  bool Value(const double x, double& fval) override;
};

MyDirFunction::MyDirFunction(math_Vector&                     V1,
                             math_Vector&                     V2,
                             math_Vector&                     V3,
                             math_Vector&                     V4,
                             math_FunctionSetWithDerivatives& f)
{

  P0  = &V1;
  Dir = &V2;
  P   = &V3;
  FV  = &V4;
  F   = &f;
}

void MyDirFunction::Initialize(const math_Vector& p0, const math_Vector& dir) const
{
  *P0  = p0;
  *Dir = dir;
}

bool MyDirFunction::Value(const double x, double& fval)
{
  double p;
  for (int i = P->Lower(); i <= P->Upper(); i++)
  {
    p           = Dir->Value(i);
    P->Value(i) = p * x + P0->Value(i);
  }
  if (F->Value(*P, *FV))
  {

    double aVal = 0.0;

    for (int i = FV->Lower(); i <= FV->Upper(); i++)
    {
      aVal = FV->Value(i);
      if (aVal <= -1.e+100)
        return false;
      else if (aVal >= 1.e+100)
        return false;
    }

    fval = 0.5 * (FV->Norm2());
    return true;
  }
  return false;
}

bool MyDirFunction::Value(const math_Vector& Sol,
                          math_Vector&       FF,
                          math_Matrix&       DF,
                          math_Vector&       GH,
                          double&            F2,
                          double&            Gnr1)
{
  if (F->Values(Sol, FF, DF))
  {

    double aVal = 0.;

    for (int i = FF.Lower(); i <= FF.Upper(); i++)
    {

      aVal = FF.Value(i);
      if (aVal < 0.)
      {
        if (aVal <= -1.e+100)
          return false;
      }
      else if (aVal >= 1.e+100)
        return false;
    }

    F2 = 0.5 * (FF.Norm2());
    GH.TMultiply(DF, FF);
    for (int i = GH.Lower(); i <= GH.Upper(); i++)
    {
      if (Precision::IsInfinite((GH.Value(i))))
      {
        return false;
      }
    }
    Gnr1 = GH.Norm2();
    return true;
  }
  return false;
}

static bool MinimizeDirection(const math_Vector& P0,
                              const math_Vector& P1,
                              const math_Vector& P2,
                              const double       F1,
                              math_Vector&       Delta,
                              const math_Vector& Tol,
                              MyDirFunction&     F)

{

  double tol1d = 2.1, invnorme, tsol;
  double Eps   = 1.e-16;
  double ax, bx, cx;

  for (int ii = 1; ii <= Tol.Length(); ii++)
  {
    invnorme = std::abs(Delta(ii));
    if (invnorme > Eps)
      tol1d = std::min(tol1d, Tol(ii) / invnorme);
  }
  if (tol1d > 1.9)
    return false;
  tol1d /= 3;

  const math_Vector& PP0 = P0;
  const math_Vector& PP1 = P1;
  Delta                  = PP1 - PP0;

  invnorme = Delta.Norm();
  if (invnorme <= Eps)
    return false;
  invnorme = ((double)1) / invnorme;

  F.Initialize(P1, Delta);

  FSR_DEBUG("      minimisation dans la direction")
  ax = -1;
  bx = 0;
  cx = (P2 - P1).Norm() * invnorme;
  if (cx < 1.e-2)
    return false;

  math_BrentMinimum Sol(tol1d, 100, tol1d);
  Sol.Perform(F, ax, bx, cx);

  if (Sol.IsDone())
  {
    tsol = Sol.Location();
    if (Sol.Minimum() < F1)
    {
      Delta.Multiply(tsol);
      return true;
    }
  }
  return false;
}

static bool MinimizeDirection(const math_Vector& P,
                              math_Vector&       Dir,
                              const double&      PValue,
                              const double&      PDirValue,
                              const math_Vector& Gradient,
                              const math_Vector& DGradient,
                              const math_Vector& Tol,
                              MyDirFunction&     F)

{
  if (Precision::IsInfinite(PValue) || Precision::IsInfinite(PDirValue))
  {
    return false;
  }

  bool   good  = false;
  double Eps   = 1.e-20;
  double tol1d = 1.1, Result = PValue, absdir;

  for (int ii = 1; ii <= Tol.Length(); ii++)
  {
    absdir = std::abs(Dir(ii));
    if (absdir > Eps)
      tol1d = std::min(tol1d, Tol(ii) / absdir);
  }
  if (tol1d > 0.9)
    return false;

  double ax, bx, cx, df1, df2, Delta, tsol, fsol, tsolbis;
  FSR_DEBUG("     essai d interpolation");

  df1 = Gradient * Dir;
  df2 = DGradient * Dir;

  if (df1 < -Eps && df2 > Eps)
  {
    tsol = -df1 / (df2 - df1);
  }
  else
  {
    cx = PValue;
    bx = df1;
    ax = PDirValue - (bx + cx);

    if (std::abs(ax) <= Eps)
    {
      if (std::abs(bx) >= Eps)
        tsol = -cx / bx;
      else
        tsol = 0;
    }
    else
    {
      Delta = bx * bx - 4 * ax * cx;
      if (Delta > 1.e-9)
      {

        Delta   = std::sqrt(Delta);
        tsol    = -(bx + Delta);
        tsolbis = (Delta - bx);
        if (std::abs(tsolbis) < std::abs(tsol))
          tsol = tsolbis;
        tsol /= 2 * ax;
      }
      else
      {

        tsol = -(0.5 * bx) / ax;
      }
    }
  }

  if (std::abs(tsol) >= 1)
    return false;

  F.Initialize(P, Dir);
  F.Value(tsol, fsol);

  if (fsol < PValue)
  {
    good   = true;
    Result = fsol;
    FSR_DEBUG("t= " << tsol << " F = " << fsol << " OldF = " << PValue);
  }

  if ((fsol > 0.2 * PValue) && (tol1d < 0.5))
  {

    if (tsol < 0)
    {
      ax = tsol;
      bx = 0.0;
      cx = 1.0;
    }
    else
    {
      ax = 0.0;
      bx = tsol;
      cx = 1.0;
    }
    FSR_DEBUG(" minimisation dans la direction");

    math_BrentMinimum Sol(tol1d, 100, tol1d);

    Sol.Perform(F, ax, bx, cx);
    if (Sol.IsDone())
    {
      if (Sol.Minimum() <= Result)
      {
        tsol   = Sol.Location();
        good   = true;
        Result = Sol.Minimum();

        if (Gradient.Norm2() > 1.0 / Precision::SquareConfusion() && tsol > ax && tsol < cx)
        {

          Sol.Perform(F, ax, (ax + tsol) / 2.0, tsol);
          if (Sol.IsDone())
          {
            if (Sol.Minimum() <= Result)
            {
              tsol   = Sol.Location();
              good   = true;
              Result = Sol.Minimum();
            }
          }

          Sol.Perform(F, tsol, (cx + tsol) / 2.0, cx);
          if (Sol.IsDone())
          {
            if (Sol.Minimum() <= Result)
            {
              tsol   = Sol.Location();
              good   = true;
              Result = Sol.Minimum();
            }
          }
        }
      }
    }
  }

  if (good)
  {

    Dir.Multiply(tsol);
  }
  return good;
}

static void SearchDirection(const math_Matrix& DF,
                            const math_Vector& GH,
                            const math_Vector& FF,
                            bool               ChangeDirection,
                            const math_Vector& InvLengthMax,
                            math_Vector&       Direction,
                            double&            Dy)

{
  int    Ninc = DF.ColNumber(), Neq = DF.RowNumber();
  double Eps = 1.e-32;
  if (!ChangeDirection)
  {
    if (Ninc == Neq)
    {
      for (int i = FF.Lower(); i <= FF.Upper(); i++)
      {
        Direction(i) = -FF(i);
      }
      math_Gauss Solut(DF, 1.e-9);
      if (Solut.IsDone())
        Solut.Solve(Direction);
      else
      {
        FSR_DEBUG(" Matrice singuliere : On prend SVD");
        math_SVD SolvebySVD(DF);
        if (SolvebySVD.IsDone())
          SolvebySVD.Solve(-1 * FF, Direction);
        else
          ChangeDirection = true;
      }
    }
    else if (Ninc > Neq)
    {
      math_SVD Solut(DF);
      if (Solut.IsDone())
        Solut.Solve(-1 * FF, Direction);
      else
        ChangeDirection = true;
    }
    else if (Ninc < Neq)
    {
      math_GaussLeastSquare Solut(DF);
      if (Solut.IsDone())
        Solut.Solve(-1 * FF, Direction);
      else
        ChangeDirection = true;
    }
  }

  double ratio = std::abs(Direction(Direction.Lower()) * InvLengthMax(Direction.Lower()));
  int    i;
  for (i = Direction.Lower() + 1; i <= Direction.Upper(); i++)
  {
    ratio = std::max(ratio, std::abs(Direction(i) * InvLengthMax(i)));
  }
  if (ratio > 1)
  {
    Direction /= ratio;
  }

  Dy = Direction * GH;
  if (Dy >= -Eps)
  {
    ChangeDirection = true;
  }
  if (ChangeDirection)
  {
    for (i = Direction.Lower(); i <= Direction.Upper(); i++)
    {
      Direction(i) = -GH(i);
    }
    Dy = -(GH.Norm2());
  }
}

static void SearchDirection(const math_Matrix&        DF,
                            const math_Vector&        GH,
                            const math_Vector&        FF,
                            const math_IntegerVector& Constraints,

                            const math_Vector&,
                            bool               ChangeDirection,
                            const math_Vector& InvLengthMax,
                            math_Vector&       Direction,
                            double&            Dy)

{
  int Ninc = DF.ColNumber(), Neq = DF.RowNumber();
  int i, j, k, Cons = 0;

  for (i = 1; i <= Ninc; i++)
  {
    if (Constraints(i) != 0)
      Cons++;
  }

  if (Cons == 0)
  {
    SearchDirection(DF, GH, FF, ChangeDirection, InvLengthMax, Direction, Dy);
  }
  else if (Cons == Ninc)
  {
    for (i = Direction.Lower(); i <= Direction.Upper(); i++)
    {
      Direction(i) = 0;
    }
    Dy = 0;
  }
  else
  {
    math_Matrix DF2(1, Neq, 1, Ninc - Cons);
    math_Vector MyGH(1, Ninc - Cons);
    math_Vector MyDirection(1, Ninc - Cons);
    math_Vector MyInvLengthMax(1, Ninc);

    for (k = 1, i = 1; i <= Ninc; i++)
    {
      if (Constraints(i) == 0)
      {
        MyGH(k)           = GH(i);
        MyInvLengthMax(k) = InvLengthMax(i);
        MyDirection(k)    = Direction(i);
        for (j = 1; j <= Neq; j++)
        {
          DF2(j, k) = DF(j, i);
        }
        k++;
      }
    }

    SearchDirection(DF2, MyGH, FF, ChangeDirection, MyInvLengthMax, MyDirection, Dy);

    for (i = 1, k = 1; i <= Ninc; i++)
    {
      if (Constraints(i) == 0)
      {
        if (!ChangeDirection)
        {
          Direction(i) = MyDirection(k);
        }
        else
          Direction(i) = -GH(i);
        k++;
      }
      else
      {
        Direction(i) = 0.0;
      }
    }
  }
}

bool Bounds(const math_Vector&  InfBound,
            const math_Vector&  SupBound,
            const math_Vector&  Tol,
            math_Vector&        Sol,
            const math_Vector&  SolSave,
            math_IntegerVector& Constraints,
            math_Vector&        Delta,
            bool&               theIsNewSol)

{
  bool   Out = false;
  int    i, Ninc = Sol.Length();
  double monratio = 1;

  theIsNewSol = true;

  for (i = 1; i <= Ninc; i++)
  {
    Constraints(i) = 0;
    Delta(i)       = Sol(i) - SolSave(i);
    if (InfBound(i) == SupBound(i))
    {
      Constraints(i) = 1;
      Out            = true;
    }
    else if (Sol(i) < InfBound(i))
    {
      Constraints(i) = 1;
      Out            = true;

      if (-Delta(i) > Tol(i))
        monratio = std::min(monratio, (InfBound(i) - SolSave(i)) / Delta(i));
    }
    else if (Sol(i) > SupBound(i))
    {
      Constraints(i) = 1;
      Out            = true;

      if (Delta(i) > Tol(i))
        monratio = std::min(monratio, (SupBound(i) - SolSave(i)) / Delta(i));
    }
  }

  if (Out)
  {
    if (monratio == 0.0)
    {
      theIsNewSol = false;
      Sol         = SolSave;
      Delta.Init(0.0);
    }
    else
    {
      Delta *= monratio;
      Sol = SolSave + Delta;
      for (i = 1; i <= Ninc; i++)
      {
        if (Sol(i) < InfBound(i))
        {
          Sol(i)   = InfBound(i);
          Delta(i) = Sol(i) - SolSave(i);
        }
        else if (Sol(i) > SupBound(i))
        {
          Sol(i)   = SupBound(i);
          Delta(i) = Sol(i) - SolSave(i);
        }
      }
    }
  }
  return Out;
}

math_FunctionSetRoot::math_FunctionSetRoot(math_FunctionSetWithDerivatives& theFunction,
                                           const math_Vector&               theTolerance,
                                           const int                        theNbIterations)

    : Delta(1, theFunction.NbVariables()),
      Sol(1, theFunction.NbVariables()),
      DF(1, theFunction.NbEquations(), 1, theFunction.NbVariables()),
      Tol(1, theFunction.NbVariables()),
      Done(false),
      Kount(0),
      State(0),
      Itermax(theNbIterations),
      InfBound(1, theFunction.NbVariables(), RealFirst()),
      SupBound(1, theFunction.NbVariables(), RealLast()),
      SolSave(1, theFunction.NbVariables()),
      GH(1, theFunction.NbVariables()),
      DH(1, theFunction.NbVariables()),
      DHSave(1, theFunction.NbVariables()),
      FF(1, theFunction.NbEquations()),
      PreviousSolution(1, theFunction.NbVariables()),
      Save(0, theNbIterations),
      Constraints(1, theFunction.NbVariables()),
      Temp1(1, theFunction.NbVariables()),
      Temp2(1, theFunction.NbVariables()),
      Temp3(1, theFunction.NbVariables()),
      Temp4(1, theFunction.NbEquations()),
      myIsDivergent(false)
{
  SetTolerance(theTolerance);
}

math_FunctionSetRoot::math_FunctionSetRoot(math_FunctionSetWithDerivatives& theFunction,
                                           const int                        theNbIterations)

    : Delta(1, theFunction.NbVariables()),
      Sol(1, theFunction.NbVariables()),
      DF(1, theFunction.NbEquations(), 1, theFunction.NbVariables()),
      Tol(1, theFunction.NbVariables()),
      Done(false),
      Kount(0),
      State(0),
      Itermax(theNbIterations),
      InfBound(1, theFunction.NbVariables(), RealFirst()),
      SupBound(1, theFunction.NbVariables(), RealLast()),
      SolSave(1, theFunction.NbVariables()),
      GH(1, theFunction.NbVariables()),
      DH(1, theFunction.NbVariables()),
      DHSave(1, theFunction.NbVariables()),
      FF(1, theFunction.NbEquations()),
      PreviousSolution(1, theFunction.NbVariables()),
      Save(0, theNbIterations),
      Constraints(1, theFunction.NbVariables()),
      Temp1(1, theFunction.NbVariables()),
      Temp2(1, theFunction.NbVariables()),
      Temp3(1, theFunction.NbVariables()),
      Temp4(1, theFunction.NbEquations()),
      myIsDivergent(false)
{
}

math_FunctionSetRoot::~math_FunctionSetRoot() = default;

void math_FunctionSetRoot::SetTolerance(const math_Vector& theTolerance)
{
  for (int i = 1; i <= Tol.Length(); ++i)
    Tol(i) = theTolerance(i);
}

void math_FunctionSetRoot::Perform(math_FunctionSetWithDerivatives& theFunction,
                                   const math_Vector&               theStartingPoint,
                                   const bool                       theStopOnDivergent)
{
  Perform(theFunction, theStartingPoint, InfBound, SupBound, theStopOnDivergent);
}

void math_FunctionSetRoot::Perform(math_FunctionSetWithDerivatives& F,
                                   const math_Vector&               StartingPoint,
                                   const math_Vector&               theInfBound,
                                   const math_Vector&               theSupBound,
                                   bool                             theStopOnDivergent)
{
  int Ninc = F.NbVariables(), Neq = F.NbEquations();

  if ((Neq <= 0) || (StartingPoint.Length() != Ninc) || (theInfBound.Length() != Ninc)
      || (theSupBound.Length() != Ninc))
  {
    throw Standard_DimensionError();
  }

  int                i;
  bool               ChangeDirection = false, Sort = false, isNewSol = false;
  bool               Good, Verif;
  bool               Stop;
  const double       EpsSqrt = 1.e-16, Eps = 1.e-32, Eps2 = 1.e-64, Progres = 0.005;
  double             F2, PreviousMinimum, Dy, OldF;
  double             Ambda, Ambda2, Gnr1, Oldgr;
  math_Vector        InvLengthMax(1, Ninc);
  math_IntegerVector aConstraints(1, Ninc);
  for (i = 1; i <= Ninc; i++)
  {
    const double aSupBound  = std::min(theSupBound(i), Precision::Infinite());
    const double anInfBound = std::max(theInfBound(i), -Precision::Infinite());
    InvLengthMax(i)         = 1. / std::max((aSupBound - anInfBound) / 4, 1.e-9);
  }

  MyDirFunction F_Dir(Temp1, Temp2, Temp3, Temp4, F);
  int           DescenteIter;

  Done  = false;
  Sol   = StartingPoint;
  Kount = 0;

  myIsDivergent = false;
  for (i = 1; i <= Ninc; i++)
  {
    myIsDivergent = myIsDivergent || Sol(i) < theInfBound(i) || Sol(i) > theSupBound(i);
  }
  if (theStopOnDivergent && myIsDivergent)
  {
    return;
  }

  for (i = 1; i <= Ninc; i++)
  {
    if (Sol(i) <= theInfBound(i))
      Sol(i) = theInfBound(i);
    else if (Sol(i) > theSupBound(i))
      Sol(i) = theSupBound(i);
  }

  if (!F_Dir.Value(Sol, FF, DF, GH, F2, Gnr1))
  {
    Done = false;
    if (!theStopOnDivergent || !myIsDivergent)
    {
      State = F.GetStateNumber();
    }
    return;
  }
  Ambda2 = Gnr1;

  Save(0)          = std::max(F2, EpsSqrt);
  double aTol_Func = Epsilon(F2);
  FSR_DEBUG("=== Mode Debug de Function Set Root" << std::endl);
  FSR_DEBUG("    F2 Initial = " << F2);

  if ((F2 <= Eps) || (Gnr1 <= Eps2))
  {
    Done = false;
    if (!theStopOnDivergent || !myIsDivergent)
    {
      Done  = true;
      State = F.GetStateNumber();
    }
    return;
  }

  for (Kount = 1; Kount <= Itermax; Kount++)
  {
    PreviousMinimum  = F2;
    Oldgr            = Gnr1;
    PreviousSolution = Sol;
    SolSave          = Sol;

    SearchDirection(DF, GH, FF, ChangeDirection, InvLengthMax, DH, Dy);
    if (std::abs(Dy) <= Eps)
    {
      Done = false;
      if (!theStopOnDivergent || !myIsDivergent)
      {
        Done = true;

        F.Value(Sol, FF);

        State = F.GetStateNumber();
      }
      return;
    }
    if (ChangeDirection)
    {
      Ambda = Ambda2 / std::sqrt(std::abs(Dy));
      if (Ambda > 1.0)
        Ambda = 1.0;
    }
    else
    {
      Ambda  = 1.0;
      Ambda2 = 0.5 * Ambda / DH.Norm();
    }

    for (i = Sol.Lower(); i <= Sol.Upper(); i++)
    {
      Sol(i) = Sol(i) + Ambda * DH(i);
    }

    for (i = 1; i <= Ninc; i++)
    {
      myIsDivergent = myIsDivergent || Sol(i) < theInfBound(i) || Sol(i) > theSupBound(i);
    }
    if (theStopOnDivergent && myIsDivergent)
    {
      return;
    }

    Sort = Bounds(theInfBound, theSupBound, Tol, Sol, SolSave, aConstraints, Delta, isNewSol);

    DHSave = GH;
    if (isNewSol)
    {

      if (!F_Dir.Value(Sol, FF, DF, GH, F2, Gnr1))
      {
        Done = false;
        if (!theStopOnDivergent || !myIsDivergent)
        {
          State = F.GetStateNumber();
        }
        return;
      }
    }

    FSR_DEBUG("Kount         = " << Kount);
    FSR_DEBUG("Le premier F2 = " << F2);
    FSR_DEBUG("Direction     = " << ChangeDirection);

    if ((F2 <= Eps) || (Gnr1 <= Eps2))
    {
      Done = false;
      if (!theStopOnDivergent || !myIsDivergent)
      {
        Done = true;

        F.Value(Sol, FF);

        State = F.GetStateNumber();
      }
      return;
    }

    if (Sort || (F2 / PreviousMinimum > Progres))
    {
      Dy           = GH * DH;
      OldF         = PreviousMinimum;
      Stop         = false;
      Good         = false;
      DescenteIter = 0;
      bool Sortbis;

      if (!Sort)
      {
        while ((F2 / PreviousMinimum > Progres) && !Stop)
        {
          if (F2 < OldF && (Dy < 0.0))
          {

            FSR_DEBUG(" iteration de descente = " << DescenteIter);
            DescenteIter++;
            SolSave = Sol;
            OldF    = F2;
            for (i = Sol.Lower(); i <= Sol.Upper(); i++)
            {
              Sol(i) = Sol(i) + Ambda * DH(i);
            }

            for (i = 1; i <= Ninc; i++)
            {
              myIsDivergent = myIsDivergent || Sol(i) < theInfBound(i) || Sol(i) > theSupBound(i);
            }
            if (theStopOnDivergent && myIsDivergent)
            {
              return;
            }

            Stop =
              Bounds(theInfBound, theSupBound, Tol, Sol, SolSave, aConstraints, Delta, isNewSol);
            FSR_DEBUG(" Augmentation de lambda");
            Ambda *= 1.7;
          }
          else
          {
            if ((F2 >= OldF) || (F2 >= PreviousMinimum))
            {
              Good = false;
              if (DescenteIter == 0)
              {

                DescenteIter++;
                Good = MinimizeDirection(SolSave, Delta, OldF, F2, DHSave, GH, Tol, F_Dir);
              }
              else if (ChangeDirection || (DescenteIter > 1) || (OldF > PreviousMinimum))
              {

                DescenteIter++;
                Good = MinimizeDirection(PreviousSolution, SolSave, Sol, OldF, Delta, Tol, F_Dir);
              }
              if (!Good)
              {
                Sol = SolSave;
                F2  = OldF;
              }
              else
              {
                Sol = SolSave + Delta;

                for (i = 1; i <= Ninc; i++)
                {
                  myIsDivergent =
                    myIsDivergent || Sol(i) < theInfBound(i) || Sol(i) > theSupBound(i);
                }
                if (theStopOnDivergent && myIsDivergent)
                {
                  return;
                }

                Sort = Bounds(theInfBound,
                              theSupBound,
                              Tol,
                              Sol,
                              SolSave,
                              aConstraints,
                              Delta,
                              isNewSol);
              }
              Sort = false;
            }
            Stop = true;
          }
          DHSave = GH;
          if (isNewSol)
          {

            if (!F_Dir.Value(Sol, FF, DF, GH, F2, Gnr1))
            {
              Done = false;
              if (!theStopOnDivergent || !myIsDivergent)
              {
                State = F.GetStateNumber();
              }
              return;
            }
          }
          Dy = GH * DH;
          if (std::abs(Dy) <= Eps)
          {
            if (F2 > OldF)
              Sol = SolSave;
            Done = false;
            if (!theStopOnDivergent || !myIsDivergent)
            {
              Done = true;

              F.Value(Sol, FF);

              State = F.GetStateNumber();
            }
            return;
          }
          if (DescenteIter >= 100)
          {
            Stop = true;
          }
        }
        FSR_DEBUG("--- Sortie du Traitement Standard");
        FSR_DEBUG("    DescenteIter = " << DescenteIter << " F2 = " << F2);
      }

      if (Sort)
      {
        Stop         = (F2 > 1.001 * OldF);
        Sortbis      = Sort;
        DescenteIter = 0;
        while (Sortbis && ((F2 < OldF) || (DescenteIter == 0)) && (!Stop))
        {
          DescenteIter++;

          SolSave = Sol;
          OldF    = F2;
          SearchDirection(DF, GH, FF, aConstraints, Sol, ChangeDirection, InvLengthMax, DH, Dy);
          FSR_DEBUG(" Conditional Direction = " << ChangeDirection);
          if (Dy < -Eps)
          {
            if (ChangeDirection)
            {
              Ambda = Ambda2 / std::sqrt(-Dy);
              if (Ambda > 1.0)
                Ambda = 1.0;
            }
            else
            {
              Ambda  = 1.0;
              Ambda2 = 0.5 * Ambda / DH.Norm();
            }

            for (i = Sol.Lower(); i <= Sol.Upper(); i++)
            {
              Sol(i) = Sol(i) + Ambda * DH(i);
            }

            for (i = 1; i <= Ninc; i++)
            {
              myIsDivergent = myIsDivergent || Sol(i) < theInfBound(i) || Sol(i) > theSupBound(i);
            }
            if (theStopOnDivergent && myIsDivergent)
            {
              return;
            }

            Sortbis =
              Bounds(theInfBound, theSupBound, Tol, Sol, SolSave, aConstraints, Delta, isNewSol);

            DHSave = GH;
            if (isNewSol)
            {

              if (!F_Dir.Value(Sol, FF, DF, GH, F2, Gnr1))
              {
                Done = false;
                if (!theStopOnDivergent || !myIsDivergent)
                {
                  State = F.GetStateNumber();
                }
                return;
              }
            }
            Ambda2 = Gnr1;
            FSR_DEBUG("---  Iteration au bords : " << DescenteIter);
            FSR_DEBUG("---  F2 = " << F2);
          }
          else
          {
            Stop = true;
          }

          while ((F2 / PreviousMinimum > Progres) && (F2 < OldF) && (!Stop))
          {
            DescenteIter++;
            FSR_DEBUG("--- Iteration de descente conditionnel = " << DescenteIter);
            if (F2 < OldF && Dy < 0.0)
            {

              SolSave = Sol;
              OldF    = F2;
              for (i = Sol.Lower(); i <= Sol.Upper(); i++)
              {
                Sol(i) = Sol(i) + Ambda * DH(i);
              }

              for (i = 1; i <= Ninc; i++)
              {
                myIsDivergent = myIsDivergent || Sol(i) < theInfBound(i) || Sol(i) > theSupBound(i);
              }
              if (theStopOnDivergent && myIsDivergent)
              {
                return;
              }

              Sortbis =
                Bounds(theInfBound, theSupBound, Tol, Sol, SolSave, aConstraints, Delta, isNewSol);
            }
            DHSave = GH;
            if (isNewSol)
            {

              if (!F_Dir.Value(Sol, FF, DF, GH, F2, Gnr1))
              {
                Done = false;
                if (!theStopOnDivergent || !myIsDivergent)
                {
                  State = F.GetStateNumber();
                }
                return;
              }
            }
            Ambda2 = Gnr1;
            Dy     = GH * DH;
            Stop   = ((Dy >= 0) || (DescenteIter >= 10) || Sortbis);
          }
          Stop = ((Dy >= 0) || (DescenteIter >= 10));
        }
        if (((F2 / PreviousMinimum > Progres) && (F2 >= OldF)) || (F2 >= PreviousMinimum))
        {

          DescenteIter++;
          Good = MinimizeDirection(SolSave, Delta, OldF, F2, DHSave, GH, Tol, F_Dir);
          if (!Good)
          {
            Sol  = SolSave;
            Sort = false;
          }
          else
          {
            Sol = SolSave + Delta;

            for (i = 1; i <= Ninc; i++)
            {
              myIsDivergent = myIsDivergent || Sol(i) < theInfBound(i) || Sol(i) > theSupBound(i);
            }
            if (theStopOnDivergent && myIsDivergent)
            {
              return;
            }

            Sort =
              Bounds(theInfBound, theSupBound, Tol, Sol, SolSave, aConstraints, Delta, isNewSol);
            if (isNewSol)
            {

              if (!F_Dir.Value(Sol, FF, DF, GH, F2, Gnr1))
              {
                Done = false;
                if (!theStopOnDivergent || !myIsDivergent)
                {
                  State = F.GetStateNumber();
                }
                return;
              }
            }
          }
          Dy = GH * DH;
        }
        FSR_DEBUG("--- Sortie du Traitement des Bords");
        FSR_DEBUG("--- DescenteIter = " << DescenteIter << " F2 = " << F2);
      }
    }

    Save(Kount) = F2;

    if (ChangeDirection)
      Verif = true;

    else
    {
      Verif = false;
      if (Kount > 1)
      {
        if (Save(Kount - 1) < 1.e-4 * Save(Kount - 2))
          Verif = true;
      }
      else
        Verif = (F2 < 1.e-6 * Save(0));
    }
    if (Verif)
    {
      for (i = Delta.Lower(); i <= Delta.Upper(); i++)
      {
        Delta(i) = PreviousSolution(i) - Sol(i);
      }

      if (IsSolutionReached(F))
      {
        if (PreviousMinimum < F2)
        {
          Sol = SolSave;
        }
        Done = false;
        if (!theStopOnDivergent || !myIsDivergent)
        {
          Done = true;

          F.Value(Sol, FF);

          State = F.GetStateNumber();
        }
        return;
      }
    }

    if ((F2 - PreviousMinimum) <= aTol_Func)
    {
      if (Kount > 5)
      {

        if (F2 >= 0.95 * Save(Kount - 5))
        {
          if (!ChangeDirection)
            ChangeDirection = true;
          else
          {
            Done = false;
            if (!theStopOnDivergent || !myIsDivergent)
            {
              Done  = true;
              State = F.GetStateNumber();
            }
            return;
          }
        }
        else
          ChangeDirection = false;
      }
      else
        ChangeDirection = false;

      if ((Gnr1 > 0.9 * Oldgr) && (F2 > 0.5 * PreviousMinimum))
      {
        ChangeDirection = true;
      }

      if ((!ChangeDirection) && (!Verif))
      {
        for (i = Delta.Lower(); i <= Delta.Upper(); i++)
        {
          Delta(i) = PreviousSolution(i) - Sol(i);
        }
        if (IsSolutionReached(F))
        {
          Done = false;
          if (!theStopOnDivergent || !myIsDivergent)
          {
            Done = true;

            F.Value(Sol, FF);

            State = F.GetStateNumber();
          }
          return;
        }
      }
    }
    else
    {
      if (!ChangeDirection)
      {
        ChangeDirection = true;
        Sol             = PreviousSolution;

        if (!F_Dir.Value(Sol, FF, DF, GH, F2, Gnr1))
        {
          Done = false;
          if (!theStopOnDivergent || !myIsDivergent)
          {
            State = F.GetStateNumber();
          }
          return;
        }
      }
      else
      {

        if (!theStopOnDivergent || !myIsDivergent)
        {
          State = F.GetStateNumber();
        }
        return;
      }
    }
  }
  if (!theStopOnDivergent || !myIsDivergent)
  {
    State = F.GetStateNumber();
  }
}

void math_FunctionSetRoot::Dump(Standard_OStream& o) const
{
  o << " math_FunctionSetRoot";
  if (Done)
  {
    o << " Status = Done\n";
    o << " Location value = " << Sol << "\n";
    o << " Number of iterations = " << Kount << "\n";
  }
  else
  {
    o << "Status = Not Done\n";
  }
}

void math_FunctionSetRoot::Root(math_Vector& Root) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Standard_DimensionError_Raise_if(Root.Length() != Sol.Length(), " ");
  Root = Sol;
}

void math_FunctionSetRoot::FunctionSetErrors(math_Vector& Err) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Standard_DimensionError_Raise_if(Err.Length() != Sol.Length(), " ");
  Err = Delta;
}
