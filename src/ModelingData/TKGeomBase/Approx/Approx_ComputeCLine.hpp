#include <Approx_ParametrizationType.hpp>
#include <AppCont_LeastSquare.hpp>
#include <NCollection_Array1.hpp>
#include <AppParCurves_Constraint.hpp>
#include <Approx_Status.hpp>
#include <Precision.hpp>

const static int MAXSEGM = 1000;

Approx_ComputeCLine::Approx_ComputeCLine(const MultiLine&              Line,
                                         const int                     degreemin,
                                         const int                     degreemax,
                                         const double                  Tolerance3d,
                                         const double                  Tolerance2d,
                                         const bool                    cutting,
                                         const AppParCurves_Constraint FirstC,
                                         const AppParCurves_Constraint LastC)
{
  mydegremin     = degreemin;
  mydegremax     = degreemax;
  mytol3d        = Tolerance3d;
  mytol2d        = Tolerance2d;
  mycut          = cutting;
  myfirstC       = FirstC;
  mylastC        = LastC;
  myMaxSegments  = MAXSEGM;
  myInvOrder     = true;
  myHangChecking = true;
  alldone        = false;
  tolreached     = false;
  currenttol3d   = 0.0;
  currenttol2d   = 0.0;
  Perform(Line);
}

Approx_ComputeCLine::Approx_ComputeCLine(const int                     degreemin,
                                         const int                     degreemax,
                                         const double                  Tolerance3d,
                                         const double                  Tolerance2d,
                                         const bool                    cutting,
                                         const AppParCurves_Constraint FirstC,
                                         const AppParCurves_Constraint LastC)
{
  alldone        = false;
  mydegremin     = degreemin;
  mydegremax     = degreemax;
  mytol3d        = Tolerance3d;
  mytol2d        = Tolerance2d;
  mycut          = cutting;
  myfirstC       = FirstC;
  mylastC        = LastC;
  myMaxSegments  = MAXSEGM;
  myInvOrder     = true;
  myHangChecking = true;
  tolreached     = false;
  currenttol3d   = 0.0;
  currenttol2d   = 0.0;
}

void Approx_ComputeCLine::Perform(const MultiLine& Line)
{
  double UFirst, ULast;
  bool   Finish = false, begin = true, Ok = false;
  double thetol3d = Precision::Confusion(), thetol2d = Precision::Confusion();
  UFirst      = Line.FirstParameter();
  ULast       = Line.LastParameter();
  double TolU = 0.;
  if (myHangChecking)
  {
    TolU = std::max((ULast - UFirst) * 1.e-03, Precision::Confusion());
  }
  else
  {
    TolU = std::max((ULast - UFirst) * 1.e-05, Precision::PApproximation());
  }
  double myfirstU      = UFirst;
  double mylastU       = ULast;
  int    aMaxSegments  = 0;
  int    aMaxSegments1 = myMaxSegments - 1;
  int    aNbCut = 0, aNbImp = 0, aNbComp = 10;

  if (!mycut)
  {
    alldone = Compute(Line, UFirst, ULast, thetol3d, thetol2d);
    if (!alldone)
    {
      tolreached = false;
      myfirstparam.Append(UFirst);
      mylastparam.Append(ULast);
      myMultiCurves.Append(TheMultiCurve);
      Tolers3d.Append(currenttol3d);
      Tolers2d.Append(currenttol2d);
    }
  }
  else
  {

    AppParCurves_MultiCurve KeptMultiCurve;
    double                  KeptUfirst = 0., KeptUlast = 0., KeptT3d = RealLast(), KeptT2d = 0.;

    while (!Finish)
    {

      if (!begin)
      {
        if (Ok)
        {

          myfirstU = mylastU;
          mylastU  = ULast;
          aNbCut   = 0;
          aNbImp   = 0;
          if (std::abs(ULast - myfirstU) <= RealEpsilon() || aMaxSegments >= myMaxSegments)
          {
            Finish  = true;
            alldone = true;
            return;
          }
          KeptT3d    = RealLast();
          KeptT2d    = 0;
          KeptUfirst = myfirstU;
          KeptUlast  = mylastU;
        }
        else
        {

          if ((thetol3d + thetol2d) < (KeptT3d + KeptT2d))
          {
            KeptMultiCurve = TheMultiCurve;
            KeptUfirst     = myfirstU;
            KeptUlast      = mylastU;
            KeptT3d        = thetol3d;
            KeptT2d        = thetol2d;
            aNbImp++;
          }

          mylastU = (myfirstU + mylastU) / 2;
          aNbCut++;
        }
      }

      Ok = Compute(Line, myfirstU, mylastU, thetol3d, thetol2d);
      if (Ok)
      {
        aMaxSegments++;
      }

      bool aStopCutting = false;
      if (myHangChecking && aNbCut >= aNbComp)
      {
        if (aNbCut > aNbImp + 1)
        {
          aStopCutting = true;
        }
        aNbCut = 0;
        aNbImp = 0;
      }

      if (!Ok
          && (std::abs(myfirstU - mylastU) <= TolU || aMaxSegments >= aMaxSegments1
              || aStopCutting))
      {
        Ok = true;

        if ((thetol3d + thetol2d) < (KeptT3d + KeptT2d))
        {
          KeptMultiCurve = TheMultiCurve;
          KeptUfirst     = myfirstU;
          KeptUlast      = mylastU;
          KeptT3d        = thetol3d;
          KeptT2d        = thetol2d;
        }

        mylastU = KeptUlast;

        tolreached = false;
        myMultiCurves.Append(KeptMultiCurve);
        aMaxSegments++;
        Tolers3d.Append(KeptT3d);
        Tolers2d.Append(KeptT2d);
        myfirstparam.Append(KeptUfirst);
        mylastparam.Append(KeptUlast);
      }

      begin = false;
    }
  }
}

int Approx_ComputeCLine::NbMultiCurves() const
{
  return myMultiCurves.Length();
}

AppParCurves_MultiCurve Approx_ComputeCLine::Value(const int Index) const
{
  return myMultiCurves.Value(Index);
}

bool Approx_ComputeCLine::Compute(const MultiLine& Line,
                                  const double     Ufirst,
                                  const double     Ulast,
                                  double&          TheTol3d,
                                  double&          TheTol2d)
{

  const int    NbPointsMax = 24;
  const double aMinRatio   = 0.05;
  const int    aMaxDeg     = 8;

  int    deg, NbPoints;
  bool   mydone;
  double Fv;

  AppParCurves_MultiCurve aPrevCurve;
  double                  aPrevTol3d = RealLast(), aPrevTol2d = RealLast();
  bool                    aPrevIsOk  = false;
  bool                    anInvOrder = myInvOrder;
  if (anInvOrder && mydegremax > aMaxDeg)
  {
    if ((Ulast - Ufirst) / (Line.LastParameter() - Line.FirstParameter()) < aMinRatio)
    {
      anInvOrder = false;
    }
  }
  if (anInvOrder)
  {
    for (deg = mydegremax; deg >= mydegremin; deg--)
    {
      NbPoints = std::min(2 * deg + 1, NbPointsMax);
      AppCont_LeastSquare LSquare(Line, Ufirst, Ulast, myfirstC, mylastC, deg, NbPoints);
      mydone = LSquare.IsDone();
      if (mydone)
      {
        LSquare.Error(Fv, TheTol3d, TheTol2d);
        if (TheTol3d <= mytol3d && TheTol2d <= mytol2d)
        {
          if (deg == mydegremin)
          {

            tolreached = true;
            myMultiCurves.Append(LSquare.Value());
            myfirstparam.Append(Ufirst);
            mylastparam.Append(Ulast);
            Tolers3d.Append(TheTol3d);
            Tolers2d.Append(TheTol2d);
            return true;
          }
          aPrevTol3d = TheTol3d;
          aPrevTol2d = TheTol2d;
          aPrevCurve = LSquare.Value();
          aPrevIsOk  = true;
          continue;
        }
        else if (aPrevIsOk)
        {

          tolreached = true;
          TheTol3d   = aPrevTol3d;
          TheTol2d   = aPrevTol2d;
          myMultiCurves.Append(aPrevCurve);
          myfirstparam.Append(Ufirst);
          mylastparam.Append(Ulast);
          Tolers3d.Append(aPrevTol3d);
          Tolers2d.Append(aPrevTol2d);
          return true;
        }
      }
      else if (aPrevIsOk)
      {

        tolreached = true;
        TheTol3d   = aPrevTol3d;
        TheTol2d   = aPrevTol2d;
        myMultiCurves.Append(aPrevCurve);
        myfirstparam.Append(Ufirst);
        mylastparam.Append(Ulast);
        Tolers3d.Append(aPrevTol3d);
        Tolers2d.Append(aPrevTol2d);
        return true;
      }
      if (!aPrevIsOk && deg == mydegremax)
      {
        TheMultiCurve = LSquare.Value();
        currenttol3d  = TheTol3d;
        currenttol2d  = TheTol2d;
        aPrevTol3d    = TheTol3d;
        aPrevTol2d    = TheTol2d;
        aPrevCurve    = TheMultiCurve;
        break;
      }
    }
  }
  else
  {
    for (deg = mydegremin; deg <= mydegremax; deg++)
    {
      NbPoints = std::min(2 * deg + 1, NbPointsMax);
      AppCont_LeastSquare LSquare(Line, Ufirst, Ulast, myfirstC, mylastC, deg, NbPoints);
      mydone = LSquare.IsDone();
      if (mydone)
      {
        LSquare.Error(Fv, TheTol3d, TheTol2d);
        if (TheTol3d <= mytol3d && TheTol2d <= mytol2d)
        {

          tolreached = true;
          myMultiCurves.Append(LSquare.Value());
          myfirstparam.Append(Ufirst);
          mylastparam.Append(Ulast);
          Tolers3d.Append(TheTol3d);
          Tolers2d.Append(TheTol2d);
          return true;
        }
      }
      if (deg == mydegremax)
      {
        TheMultiCurve = LSquare.Value();
        currenttol3d  = TheTol3d;
        currenttol2d  = TheTol2d;
      }
    }
  }
  return false;
}

void Approx_ComputeCLine::Parameters(const int Index, double& firstpar, double& lastpar) const
{
  firstpar = myfirstparam.Value(Index);
  lastpar  = mylastparam.Value(Index);
}

void Approx_ComputeCLine::SetDegrees(const int degreemin, const int degreemax)
{
  mydegremin = degreemin;
  mydegremax = degreemax;
}

void Approx_ComputeCLine::SetTolerances(const double Tolerance3d, const double Tolerance2d)
{
  mytol3d = Tolerance3d;
  mytol2d = Tolerance2d;
}

void Approx_ComputeCLine::SetConstraints(const AppParCurves_Constraint FirstC,
                                         const AppParCurves_Constraint LastC)
{
  myfirstC = FirstC;
  mylastC  = LastC;
}

void Approx_ComputeCLine::SetMaxSegments(const int theMaxSegments)
{
  myMaxSegments = theMaxSegments;
}

void Approx_ComputeCLine::SetInvOrder(const bool theInvOrder)
{
  myInvOrder = theInvOrder;
}

void Approx_ComputeCLine::SetHangChecking(const bool theHangChecking)
{
  myHangChecking = theHangChecking;
}

bool Approx_ComputeCLine::IsAllApproximated() const
{
  return alldone;
}

bool Approx_ComputeCLine::IsToleranceReached() const
{
  return tolreached;
}

void Approx_ComputeCLine::Error(const int Index, double& tol3d, double& tol2d) const
{
  tol3d = Tolers3d.Value(Index);
  tol2d = Tolers2d.Value(Index);
}
