

#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <Extrema_GenLocateExtPS.hpp>
#include <Geom_Surface.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <IntImp_ComputeTangence.hpp>
#include <IntSurf_LineOn2S.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <IntWalk_PWalking.hpp>
#include <IntWalk_StatusDeflection.hpp>
#include <math_FunctionSetRoot.hpp>
#include <Precision.hpp>
#include <Standard_Failure.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <NCollection_Array1.hpp>

void IntWalk_PWalking::ComputePasInit(const double theDeltaU1,
                                      const double theDeltaV1,
                                      const double theDeltaU2,
                                      const double theDeltaV2)
{
  const double                          aRangePart = 0.01;
  const double                          Increment  = 2.0 * pasMax;
  const occ::handle<Adaptor3d_Surface>& Caro1 = myIntersectionOn2S.Function().AuxillarSurface1();
  const occ::handle<Adaptor3d_Surface>& Caro2 = myIntersectionOn2S.Function().AuxillarSurface2();

  const double aDeltaU1 = std::abs(UM1 - Um1);
  const double aDeltaV1 = std::abs(VM1 - Vm1);
  const double aDeltaU2 = std::abs(UM2 - Um2);
  const double aDeltaV2 = std::abs(VM2 - Vm2);

  if (!Precision::IsInfinite(aDeltaU1))
    pasuv[0] = std::max(Increment * std::max(theDeltaU1, aRangePart * aDeltaU1), pasuv[0]);
  else
    pasuv[0] = std::max(Increment * theDeltaU1, pasuv[0]);

  if (!Precision::IsInfinite(aDeltaV1))
    pasuv[1] = std::max(Increment * std::max(theDeltaV1, aRangePart * aDeltaV1), pasuv[1]);
  else
    pasuv[1] = std::max(Increment * theDeltaV1, pasuv[1]);

  if (!Precision::IsInfinite(aDeltaU2))
    pasuv[2] = std::max(Increment * std::max(theDeltaU2, aRangePart * aDeltaU2), pasuv[2]);
  else
    pasuv[2] = std::max(Increment * theDeltaU2, pasuv[2]);

  if (!Precision::IsInfinite(aDeltaV2))
    pasuv[3] = std::max(Increment * std::max(theDeltaV2, aRangePart * aDeltaV2), pasuv[3]);
  else
    pasuv[3] = std::max(Increment * theDeltaV2, pasuv[3]);

  const double ResoU1tol = Adaptor3d_HSurfaceTool::UResolution(Caro1, tolconf);
  const double ResoV1tol = Adaptor3d_HSurfaceTool::VResolution(Caro1, tolconf);
  const double ResoU2tol = Adaptor3d_HSurfaceTool::UResolution(Caro2, tolconf);
  const double ResoV2tol = Adaptor3d_HSurfaceTool::VResolution(Caro2, tolconf);

  myStepMin[0] = std::max(myStepMin[0], 2.0 * ResoU1tol);
  myStepMin[1] = std::max(myStepMin[1], 2.0 * ResoV1tol);
  myStepMin[2] = std::max(myStepMin[2], 2.0 * ResoU2tol);
  myStepMin[3] = std::max(myStepMin[3], 2.0 * ResoV2tol);

  for (int i = 0; i < 4; i++)
  {
    pasuv[i] = std::max(myStepMin[i], pasuv[i]);
  }
}

static void IsParallel(const occ::handle<IntSurf_LineOn2S>& theLine,
                       const bool                           theCheckSurf1,
                       const double                         theToler,
                       bool&                                theIsUparallel,
                       bool&                                theIsVparallel)
{
  const int aNbPointsMAX = 23;

  theIsUparallel = theIsVparallel = true;

  const int aNbLinePnts = theLine->NbPoints();
  int       aNbPoints   = aNbLinePnts;
  if (aNbPoints > aNbPointsMAX)
  {
    aNbPoints = aNbPointsMAX;
  }
  else if (aNbPoints < 3)
  {

    return;
  }

  double aStep   = IntToReal(theLine->NbPoints()) / aNbPoints;
  double aNPoint = 1.0;

  double aUmin = RealLast(), aUmax = RealFirst(), aVmin = RealLast(), aVmax = RealFirst();
  for (int aNum = 1; aNum <= aNbPoints; aNum++, aNPoint += aStep)
  {

    if (aNPoint > aNbLinePnts)
      aNPoint = aNbLinePnts;

    double u, v;
    if (theCheckSurf1)
      theLine->Value(RealToInt(aNPoint)).ParametersOnS1(u, v);
    else
      theLine->Value(RealToInt(aNPoint)).ParametersOnS2(u, v);

    if (u < aUmin)
      aUmin = u;

    if (u > aUmax)
      aUmax = u;

    if (v < aVmin)
      aVmin = v;

    if (v > aVmax)
      aVmax = v;
  }

  theIsVparallel = ((aUmax - aUmin) < theToler);
  theIsUparallel = ((aVmax - aVmin) < theToler);
}

static bool AdjustToDomain(const int           theNbElem,
                           double*             theParam,
                           const double* const theLowBorder,
                           const double* const theUppBorder)
{
  bool aRetVal = false;
  for (int i = 0; i < theNbElem; i++)
  {
    if ((theParam[i] - theLowBorder[i]) < -Precision::PConfusion())
    {
      theParam[i] = theLowBorder[i];
      aRetVal     = true;
    }

    if ((theParam[i] - theUppBorder[i]) > Precision::PConfusion())
    {
      theParam[i] = theUppBorder[i];
      aRetVal     = true;
    }
  }

  return aRetVal;
}

IntWalk_PWalking::IntWalk_PWalking(const occ::handle<Adaptor3d_Surface>& Caro1,
                                   const occ::handle<Adaptor3d_Surface>& Caro2,
                                   const double                          TolTangency,
                                   const double                          Epsilon,
                                   const double                          Deflection,
                                   const double                          Increment)
    :

      done(true),
      close(false),
      tgfirst(false),
      tglast(false),
      myTangentIdx(0),
      fleche(Deflection),
      pasMax(0.0),
      tolconf(Epsilon),
      myTolTang(TolTangency),
      sensCheminement(1),
      previoustg(false),
      myIntersectionOn2S(Caro1, Caro2, TolTangency),
      STATIC_BLOCAGE_SUR_PAS_TROP_GRAND(0),
      STATIC_PRECEDENT_INFLEXION(0)
{
  double KELARG = 20.;

  pasMax = Increment * 0.2;
  Um1    = Adaptor3d_HSurfaceTool::FirstUParameter(Caro1);
  Vm1    = Adaptor3d_HSurfaceTool::FirstVParameter(Caro1);
  UM1    = Adaptor3d_HSurfaceTool::LastUParameter(Caro1);
  VM1    = Adaptor3d_HSurfaceTool::LastVParameter(Caro1);

  Um2 = Adaptor3d_HSurfaceTool::FirstUParameter(Caro2);
  Vm2 = Adaptor3d_HSurfaceTool::FirstVParameter(Caro2);
  UM2 = Adaptor3d_HSurfaceTool::LastUParameter(Caro2);
  VM2 = Adaptor3d_HSurfaceTool::LastVParameter(Caro2);

  ResoU1 = Adaptor3d_HSurfaceTool::UResolution(Caro1, Precision::Confusion());
  ResoV1 = Adaptor3d_HSurfaceTool::VResolution(Caro1, Precision::Confusion());

  ResoU2 = Adaptor3d_HSurfaceTool::UResolution(Caro2, Precision::Confusion());
  ResoV2 = Adaptor3d_HSurfaceTool::VResolution(Caro2, Precision::Confusion());

  double NEWRESO;
  double MAXVAL;
  double MAXVAL2;

  MAXVAL  = std::abs(Um1);
  MAXVAL2 = std::abs(UM1);
  if (MAXVAL2 > MAXVAL)
    MAXVAL = MAXVAL2;
  NEWRESO = ResoU1 * MAXVAL;
  if (NEWRESO > ResoU1 && NEWRESO < 10)
  {
    ResoU1 = NEWRESO;
  }

  MAXVAL  = std::abs(Um2);
  MAXVAL2 = std::abs(UM2);
  if (MAXVAL2 > MAXVAL)
    MAXVAL = MAXVAL2;
  NEWRESO = ResoU2 * MAXVAL;
  if (NEWRESO > ResoU2 && NEWRESO < 10)
  {
    ResoU2 = NEWRESO;
  }

  MAXVAL  = std::abs(Vm1);
  MAXVAL2 = std::abs(VM1);
  if (MAXVAL2 > MAXVAL)
    MAXVAL = MAXVAL2;
  NEWRESO = ResoV1 * MAXVAL;
  if (NEWRESO > ResoV1 && NEWRESO < 10)
  {
    ResoV1 = NEWRESO;
  }

  MAXVAL  = std::abs(Vm2);
  MAXVAL2 = std::abs(VM2);
  if (MAXVAL2 > MAXVAL)
    MAXVAL = MAXVAL2;
  NEWRESO = ResoV2 * MAXVAL;
  if (NEWRESO > ResoV2 && NEWRESO < 10)
  {
    ResoV2 = NEWRESO;
  }

  pasuv[0] = pasMax * std::abs(UM1 - Um1);
  pasuv[1] = pasMax * std::abs(VM1 - Vm1);
  pasuv[2] = pasMax * std::abs(UM2 - Um2);
  pasuv[3] = pasMax * std::abs(VM2 - Vm2);

  if (ResoU1 > 0.0001 * pasuv[0])
    ResoU1 = 0.00001 * pasuv[0];
  if (ResoV1 > 0.0001 * pasuv[1])
    ResoV1 = 0.00001 * pasuv[1];
  if (ResoU2 > 0.0001 * pasuv[2])
    ResoU2 = 0.00001 * pasuv[2];
  if (ResoV2 > 0.0001 * pasuv[3])
    ResoV2 = 0.00001 * pasuv[3];

  if (!Adaptor3d_HSurfaceTool::IsUPeriodic(Caro1))
  {
  }
  else
  {
    double t = UM1 - Um1;
    if (t < Adaptor3d_HSurfaceTool::UPeriod(Caro1))
    {
      t = 0.5 * (Adaptor3d_HSurfaceTool::UPeriod(Caro1) - t);
      t = (t > KELARG * pasuv[0]) ? KELARG * pasuv[0] : t;
      UM1 += t;
      Um1 -= t;
    }
  }

  if (!Adaptor3d_HSurfaceTool::IsVPeriodic(Caro1))
  {
  }
  else
  {
    double t = VM1 - Vm1;
    if (t < Adaptor3d_HSurfaceTool::VPeriod(Caro1))
    {
      t = 0.5 * (Adaptor3d_HSurfaceTool::VPeriod(Caro1) - t);
      t = (t > KELARG * pasuv[1]) ? KELARG * pasuv[1] : t;
      VM1 += t;
      Vm1 -= t;
    }
  }

  if (!Adaptor3d_HSurfaceTool::IsUPeriodic(Caro2))
  {
  }
  else
  {
    double t = UM2 - Um2;
    if (t < Adaptor3d_HSurfaceTool::UPeriod(Caro2))
    {
      t = 0.5 * (Adaptor3d_HSurfaceTool::UPeriod(Caro2) - t);
      t = (t > KELARG * pasuv[2]) ? KELARG * pasuv[2] : t;
      UM2 += t;
      Um2 -= t;
    }
  }

  if (!Adaptor3d_HSurfaceTool::IsVPeriodic(Caro2))
  {
  }
  else
  {
    double t = VM2 - Vm2;
    if (t < Adaptor3d_HSurfaceTool::VPeriod(Caro2))
    {
      t = 0.5 * (Adaptor3d_HSurfaceTool::VPeriod(Caro2) - t);
      t = (t > KELARG * pasuv[3]) ? KELARG * pasuv[3] : t;
      VM2 += t;
      Vm2 -= t;
    }
  }

  myStepMin[0] = 100.0 * ResoU1;
  myStepMin[1] = 100.0 * ResoV1;
  myStepMin[2] = 100.0 * ResoU2;
  myStepMin[3] = 100.0 * ResoV2;

  for (int i = 0; i <= 3; i++)
  {
    if (pasuv[i] > 10)
      pasuv[i] = 10;
    pasInit[i] = pasSav[i] = pasuv[i];
  }
}

IntWalk_PWalking::IntWalk_PWalking(const occ::handle<Adaptor3d_Surface>& Caro1,
                                   const occ::handle<Adaptor3d_Surface>& Caro2,
                                   const double                          TolTangency,
                                   const double                          Epsilon,
                                   const double                          Deflection,
                                   const double                          Increment,
                                   const double                          U1,
                                   const double                          V1,
                                   const double                          U2,
                                   const double                          V2)
    :

      done(true),
      close(false),
      fleche(Deflection),
      tolconf(Epsilon),
      myTolTang(TolTangency),
      sensCheminement(1),
      myIntersectionOn2S(Caro1, Caro2, TolTangency),
      STATIC_BLOCAGE_SUR_PAS_TROP_GRAND(0),
      STATIC_PRECEDENT_INFLEXION(0)
{
  double KELARG = 20.;

  pasMax = Increment * 0.2;

  Um1 = Adaptor3d_HSurfaceTool::FirstUParameter(Caro1);
  Vm1 = Adaptor3d_HSurfaceTool::FirstVParameter(Caro1);
  UM1 = Adaptor3d_HSurfaceTool::LastUParameter(Caro1);
  VM1 = Adaptor3d_HSurfaceTool::LastVParameter(Caro1);

  Um2 = Adaptor3d_HSurfaceTool::FirstUParameter(Caro2);
  Vm2 = Adaptor3d_HSurfaceTool::FirstVParameter(Caro2);
  UM2 = Adaptor3d_HSurfaceTool::LastUParameter(Caro2);
  VM2 = Adaptor3d_HSurfaceTool::LastVParameter(Caro2);

  ResoU1 = Adaptor3d_HSurfaceTool::UResolution(Caro1, Precision::Confusion());
  ResoV1 = Adaptor3d_HSurfaceTool::VResolution(Caro1, Precision::Confusion());

  ResoU2 = Adaptor3d_HSurfaceTool::UResolution(Caro2, Precision::Confusion());
  ResoV2 = Adaptor3d_HSurfaceTool::VResolution(Caro2, Precision::Confusion());

  double NEWRESO, MAXVAL, MAXVAL2;

  MAXVAL  = std::abs(Um1);
  MAXVAL2 = std::abs(UM1);
  if (MAXVAL2 > MAXVAL)
  {
    MAXVAL = MAXVAL2;
  }
  NEWRESO = ResoU1 * MAXVAL;
  if (NEWRESO > ResoU1)
  {
    ResoU1 = NEWRESO;
  }

  MAXVAL  = std::abs(Um2);
  MAXVAL2 = std::abs(UM2);
  if (MAXVAL2 > MAXVAL)
  {
    MAXVAL = MAXVAL2;
  }
  NEWRESO = ResoU2 * MAXVAL;
  if (NEWRESO > ResoU2)
  {
    ResoU2 = NEWRESO;
  }

  MAXVAL  = std::abs(Vm1);
  MAXVAL2 = std::abs(VM1);
  if (MAXVAL2 > MAXVAL)
  {
    MAXVAL = MAXVAL2;
  }
  NEWRESO = ResoV1 * MAXVAL;
  if (NEWRESO > ResoV1)
  {
    ResoV1 = NEWRESO;
  }

  MAXVAL  = std::abs(Vm2);
  MAXVAL2 = std::abs(VM2);
  if (MAXVAL2 > MAXVAL)
  {
    MAXVAL = MAXVAL2;
  }
  NEWRESO = ResoV2 * MAXVAL;
  if (NEWRESO > ResoV2)
  {
    ResoV2 = NEWRESO;
  }

  pasuv[0] = pasMax * std::abs(UM1 - Um1);
  pasuv[1] = pasMax * std::abs(VM1 - Vm1);
  pasuv[2] = pasMax * std::abs(UM2 - Um2);
  pasuv[3] = pasMax * std::abs(VM2 - Vm2);

  if (!Adaptor3d_HSurfaceTool::IsUPeriodic(Caro1))
  {
    UM1 += KELARG * pasuv[0];
    Um1 -= KELARG * pasuv[0];
  }
  else
  {
    double t = UM1 - Um1;
    if (t < Adaptor3d_HSurfaceTool::UPeriod(Caro1))
    {
      t = 0.5 * (Adaptor3d_HSurfaceTool::UPeriod(Caro1) - t);
      t = (t > KELARG * pasuv[0]) ? KELARG * pasuv[0] : t;
      UM1 += t;
      Um1 -= t;
    }
  }

  if (!Adaptor3d_HSurfaceTool::IsVPeriodic(Caro1))
  {
    VM1 += KELARG * pasuv[1];
    Vm1 -= KELARG * pasuv[1];
  }
  else
  {
    double t = VM1 - Vm1;
    if (t < Adaptor3d_HSurfaceTool::VPeriod(Caro1))
    {
      t = 0.5 * (Adaptor3d_HSurfaceTool::VPeriod(Caro1) - t);
      t = (t > KELARG * pasuv[1]) ? KELARG * pasuv[1] : t;
      VM1 += t;
      Vm1 -= t;
    }
  }

  if (!Adaptor3d_HSurfaceTool::IsUPeriodic(Caro2))
  {
    UM2 += KELARG * pasuv[2];
    Um2 -= KELARG * pasuv[2];
  }
  else
  {
    double t = UM2 - Um2;
    if (t < Adaptor3d_HSurfaceTool::UPeriod(Caro2))
    {
      t = 0.5 * (Adaptor3d_HSurfaceTool::UPeriod(Caro2) - t);
      t = (t > KELARG * pasuv[2]) ? KELARG * pasuv[2] : t;
      UM2 += t;
      Um2 -= t;
    }
  }

  if (!Adaptor3d_HSurfaceTool::IsVPeriodic(Caro2))
  {
    VM2 += KELARG * pasuv[3];
    Vm2 -= KELARG * pasuv[3];
  }
  else
  {
    double t = VM2 - Vm2;
    if (t < Adaptor3d_HSurfaceTool::VPeriod(Caro2))
    {
      t = 0.5 * (Adaptor3d_HSurfaceTool::VPeriod(Caro2) - t);
      t = (t > KELARG * pasuv[3]) ? KELARG * pasuv[3] : t;
      VM2 += t;
      Vm2 -= t;
    }
  }

  for (int i = 0; i <= 3; i++)
  {
    pasInit[i] = pasSav[i] = pasuv[i];
  }

  if (ResoU1 > 0.0001 * pasuv[0])
    ResoU1 = 0.00001 * pasuv[0];
  if (ResoV1 > 0.0001 * pasuv[1])
    ResoV1 = 0.00001 * pasuv[1];
  if (ResoU2 > 0.0001 * pasuv[2])
    ResoU2 = 0.00001 * pasuv[2];
  if (ResoV2 > 0.0001 * pasuv[3])
    ResoV2 = 0.00001 * pasuv[3];

  myStepMin[0] = 100.0 * ResoU1;
  myStepMin[1] = 100.0 * ResoV1;
  myStepMin[2] = 100.0 * ResoU2;
  myStepMin[3] = 100.0 * ResoV2;

  NCollection_Array1<double> Par(1, 4);
  Par(1) = U1;
  Par(2) = V1;
  Par(3) = U2;
  Par(4) = V2;
  Perform(Par);
}

bool IntWalk_PWalking::PerformFirstPoint(const NCollection_Array1<double>& ParDep,
                                         IntSurf_PntOn2S&                  FirstPoint)
{
  sensCheminement = 1;
  close           = false;

  int                        i;
  NCollection_Array1<double> Param(1, 4);

  for (i = 1; i <= 4; ++i)
  {
    Param(i) = ParDep(i);
  }

  math_FunctionSetRoot Rsnld(myIntersectionOn2S.Function());

  myIntersectionOn2S.Perform(Param, Rsnld);
  if (!myIntersectionOn2S.IsDone())
  {
    return false;
  }

  if (myIntersectionOn2S.IsEmpty())
  {
    return false;
  }

  FirstPoint = myIntersectionOn2S.Point();
  return true;
}

void IntWalk_PWalking::Perform(const NCollection_Array1<double>& ParDep)
{
  Perform(ParDep, Um1, Vm1, Um2, Vm2, UM1, VM1, UM2, VM2);
}

static double SQDistPointSurface(const gp_Pnt&            thePnt,
                                 const Adaptor3d_Surface& theSurf,
                                 const double             theU0,
                                 const double             theV0)
{
  Extrema_GenLocateExtPS aExtPS(theSurf);
  aExtPS.Perform(thePnt, theU0, theV0);

  if (!aExtPS.IsDone())
    return RealLast();

  return aExtPS.SquareDistance();
}

static bool IsTangentExtCheck(const occ::handle<Adaptor3d_Surface>& theSurf1,
                              const occ::handle<Adaptor3d_Surface>& theSurf2,
                              const double                          theU10,
                              const double                          theV10,
                              const double                          theU20,
                              const double                          theV20,
                              const double                          theToler,
                              const double                          theArrStep[])
{
  {
    gp_Pnt aPt;
    gp_Vec aDu1, aDv1, aDu2, aDv2;
    theSurf1->D1(theU10, theV10, aPt, aDu1, aDv1);
    theSurf2->D1(theU20, theV20, aPt, aDu2, aDv2);

    const gp_Vec aN1(aDu1.Crossed(aDv1)), aN2(aDu2.Crossed(aDv2));
    const double aDP = aN1.Dot(aN2), aSQ1 = aN1.SquareMagnitude(), aSQ2 = aN2.SquareMagnitude();

    if ((aSQ1 < RealSmall()) || (aSQ2 < RealSmall()))
      return true;

    if (aDP * aDP < 0.9998 * aSQ1 * aSQ2)
    {
      return false;
    }
  }

  const double aSQToler          = 4.0 * theToler * theToler;
  const int    aNbItems          = 4;
  const double aParUS1[aNbItems] = {theU10 + theArrStep[0], theU10 - theArrStep[0], theU10, theU10};
  const double aParVS1[aNbItems] = {theV10, theV10, theV10 + theArrStep[1], theV10 - theArrStep[1]};
  const double aParUS2[aNbItems] = {theU20 + theArrStep[2], theU20 - theArrStep[2], theU20, theU20};
  const double aParVS2[aNbItems] = {theV20, theV20, theV20 + theArrStep[3], theV20 - theArrStep[3]};

  for (int i = 0; i < aNbItems; i++)
  {
    gp_Pnt       aP(theSurf1->Value(aParUS1[i], aParVS1[i]));
    const double aSqDist = SQDistPointSurface(aP, *theSurf2, theU20, theV20);
    if (aSqDist > aSQToler)
      return false;
  }

  for (int i = 0; i < aNbItems; i++)
  {
    gp_Pnt       aP(theSurf2->Value(aParUS2[i], aParVS2[i]));
    const double aSqDist = SQDistPointSurface(aP, *theSurf1, theU10, theV10);
    if (aSqDist > aSQToler)
      return false;
  }

  return true;
}

void IntWalk_PWalking::Perform(const NCollection_Array1<double>& ParDep,
                               const double                      u1min,
                               const double                      v1min,
                               const double                      u2min,
                               const double                      v2min,
                               const double                      u1max,
                               const double                      v1max,
                               const double                      u2max,
                               const double                      v2max)
{
  const double aSQDistMax = 1.0e-14;

  int                        NbPasOKConseq = 0;
  NCollection_Array1<double> Param(1, 4);
  IntImp_ConstIsoparametric  ChoixIso;

  done = false;

  const occ::handle<Adaptor3d_Surface>& Caro1 = myIntersectionOn2S.Function().AuxillarSurface1();
  const occ::handle<Adaptor3d_Surface>& Caro2 = myIntersectionOn2S.Function().AuxillarSurface2();

  const double UFirst1 = Adaptor3d_HSurfaceTool::FirstUParameter(Caro1);
  const double VFirst1 = Adaptor3d_HSurfaceTool::FirstVParameter(Caro1);
  const double ULast1  = Adaptor3d_HSurfaceTool::LastUParameter(Caro1);
  const double VLast1  = Adaptor3d_HSurfaceTool::LastVParameter(Caro1);

  const double UFirst2 = Adaptor3d_HSurfaceTool::FirstUParameter(Caro2);
  const double VFirst2 = Adaptor3d_HSurfaceTool::FirstVParameter(Caro2);
  const double ULast2  = Adaptor3d_HSurfaceTool::LastUParameter(Caro2);
  const double VLast2  = Adaptor3d_HSurfaceTool::LastVParameter(Caro2);

  ComputePasInit(u1max - u1min, v1max - v1min, u2max - u2min, v2max - v2min);

  for (int i = 0; i < 4; ++i)
  {
    if (pasuv[i] > 10)
    {
      pasuv[i] = 10;
    }

    pasInit[i] = pasSav[i] = pasuv[i];
  }

  line = new IntSurf_LineOn2S();

  for (int i = 1; i <= 4; ++i)
  {
    Param(i) = ParDep(i);
  }

  for (int i = 0; i < 4; ++i)
  {
    pasSav[i] = pasuv[i] = pasInit[i];
  }

  math_FunctionSetRoot Rsnld(myIntersectionOn2S.Function());

  ChoixIso = myIntersectionOn2S.Perform(Param, Rsnld);
  if (!myIntersectionOn2S.IsDone())
  {
    return;
  }

  if (myIntersectionOn2S.IsEmpty())
  {
    return;
  }

  if (myIntersectionOn2S.IsTangent())
  {
    return;
  }

  bool      Arrive, DejaReparti;
  const int RejectIndexMAX = 250000;
  int       IncKey, RejectIndex;
  gp_Pnt    pf, pl;

  DejaReparti = false;
  IncKey      = 0;
  RejectIndex = 0;

  previousPoint = myIntersectionOn2S.Point();
  previoustg    = false;
  previousd     = myIntersectionOn2S.Direction();
  previousd1    = myIntersectionOn2S.DirectionOnS1();
  previousd2    = myIntersectionOn2S.DirectionOnS2();
  myTangentIdx  = 1;
  tgdir         = previousd;
  firstd1       = previousd1;
  firstd2       = previousd2;
  tgfirst = tglast = false;
  choixIsoSav      = ChoixIso;

  pf                   = previousPoint.Value();
  bool bTestFirstPoint = true;

  previousPoint.Parameters(Param(1), Param(2), Param(3), Param(4));

  if (IsTangentExtCheck(Caro1, Caro2, Param(1), Param(2), Param(3), Param(4), myTolTang, pasuv))
    return;

  AddAPoint(previousPoint);

  IntWalk_StatusDeflection aStatus = IntWalk_OK, aPrevStatus = IntWalk_OK;
  bool                     NoTestDeflection = false;
  double                   SvParam[4], f;
  int                      LevelOfEmptyInmyIntersectionOn2S = 0;
  int                      LevelOfPointConfondu             = 0;
  int                      LevelOfIterWithoutAppend         = -1;

  const double aTol[4] = {Epsilon(UM1 - Um1),
                          Epsilon(VM1 - Vm1),
                          Epsilon(UM2 - Um2),
                          Epsilon(VM2 - Vm2)};

  int aPrevNbPoints = line->NbPoints();

  Arrive = false;
  while (!Arrive)
  {
    aPrevStatus = aStatus;

    LevelOfIterWithoutAppend++;
    if (LevelOfIterWithoutAppend > 20)
    {
      Arrive = true;
      if (DejaReparti)
      {
        break;
      }
      RepartirOuDiviser(DejaReparti, ChoixIso, Arrive);
      LevelOfIterWithoutAppend = 0;
    }

    f = 0.;
    switch (ChoixIso)
    {
      case IntImp_UIsoparametricOnCaro1:
        f = std::abs(previousd1.X());
        break;
      case IntImp_VIsoparametricOnCaro1:
        f = std::abs(previousd1.Y());
        break;
      case IntImp_UIsoparametricOnCaro2:
        f = std::abs(previousd2.X());
        break;
      case IntImp_VIsoparametricOnCaro2:
        f = std::abs(previousd2.Y());
        break;
      default:
        break;
    }

    if (f < 0.1)
    {
      f = 0.1;
    }

    previousPoint.Parameters(Param(1), Param(2), Param(3), Param(4));

    double aIncKey, aEps, dP1, dP2, dP3, dP4;

    dP1 = sensCheminement * pasuv[0] * previousd1.X() / f;
    dP2 = sensCheminement * pasuv[1] * previousd1.Y() / f;
    dP3 = sensCheminement * pasuv[2] * previousd2.X() / f;
    dP4 = sensCheminement * pasuv[3] * previousd2.Y() / f;

    aIncKey = 5. * (double)IncKey;
    aEps    = 1.e-7;
    if (ChoixIso == IntImp_UIsoparametricOnCaro1 && std::abs(dP1) < aEps)
    {
      dP1 *= aIncKey;
    }

    if (ChoixIso == IntImp_VIsoparametricOnCaro1 && std::abs(dP2) < aEps)
    {
      dP2 *= aIncKey;
    }

    if (ChoixIso == IntImp_UIsoparametricOnCaro2 && std::abs(dP3) < aEps)
    {
      dP3 *= aIncKey;
    }

    if (ChoixIso == IntImp_VIsoparametricOnCaro2 && std::abs(dP4) < aEps)
    {
      dP4 *= aIncKey;
    }

    Param(1) += dP1;
    Param(2) += dP2;
    Param(3) += dP3;
    Param(4) += dP4;

    SvParam[0] = Param(1);
    SvParam[1] = Param(2);
    SvParam[2] = Param(3);
    SvParam[3] = Param(4);

    int                       aTryNumber = 0;
    bool                      isBadPoint = false;
    IntImp_ConstIsoparametric aBestIso   = ChoixIso;
    do
    {
      isBadPoint = false;

      ChoixIso = myIntersectionOn2S.Perform(Param, Rsnld, aBestIso);

      if (myIntersectionOn2S.IsDone() && !myIntersectionOn2S.IsEmpty())
      {

        double aNewPnt[4], anAbsParamDist[4];
        myIntersectionOn2S.Point().Parameters(aNewPnt[0], aNewPnt[1], aNewPnt[2], aNewPnt[3]);
        const double aParMin[4] = {Um1, Vm1, Um2, Vm2};
        const double aParMax[4] = {UM1, VM1, UM2, VM2};

        for (int i = 0; i < 4; i++)
        {
          if (std::abs(aNewPnt[i] - aParMin[i]) < aTol[i])
            aNewPnt[i] = aParMin[i];
          else if (std::abs(aNewPnt[i] - aParMax[i]) < aTol[i])
            aNewPnt[i] = aParMax[i];
        }

        if (aNewPnt[0] < Um1 || aNewPnt[0] > UM1 || aNewPnt[1] < Vm1 || aNewPnt[1] > VM1
            || aNewPnt[2] < Um2 || aNewPnt[2] > UM2 || aNewPnt[3] < Vm2 || aNewPnt[3] > VM2)
        {

          break;
        }

        myIntersectionOn2S.ChangePoint().SetValue(aNewPnt[0], aNewPnt[1], aNewPnt[2], aNewPnt[3]);

        anAbsParamDist[0] = std::abs(Param(1) - dP1 - aNewPnt[0]);
        anAbsParamDist[1] = std::abs(Param(2) - dP2 - aNewPnt[1]);
        anAbsParamDist[2] = std::abs(Param(3) - dP3 - aNewPnt[2]);
        anAbsParamDist[3] = std::abs(Param(4) - dP4 - aNewPnt[3]);
        if (anAbsParamDist[0] < ResoU1 && anAbsParamDist[1] < ResoV1 && anAbsParamDist[2] < ResoU2
            && anAbsParamDist[3] < ResoV2 && aStatus != IntWalk_PasTropGrand)
        {
          isBadPoint = true;
          aBestIso   = IntImp_ConstIsoparametric((aBestIso + 1) % 4);
        }
      }
    } while (isBadPoint && ++aTryNumber <= 4);

    if (!myIntersectionOn2S.IsDone())
    {

      Arrive   = false;
      Param(1) = SvParam[0];
      Param(2) = SvParam[1];
      Param(3) = SvParam[2];
      Param(4) = SvParam[3];
      RepartirOuDiviser(DejaReparti, ChoixIso, Arrive);
    }
    else
    {

      if (myIntersectionOn2S.IsEmpty())
      {
        double u1, v1, u2, v2;
        previousPoint.Parameters(u1, v1, u2, v2);

        Arrive = false;
        if (u1 < UFirst1 || u1 > ULast1)
        {
          Arrive = true;
        }

        if (u2 < UFirst2 || u2 > ULast2)
        {
          Arrive = true;
        }

        if (v1 < VFirst1 || v1 > VLast1)
        {
          Arrive = true;
        }

        if (v2 < VFirst2 || v2 > VLast2)
        {
          Arrive = true;
        }

        RepartirOuDiviser(DejaReparti, ChoixIso, Arrive);
        LevelOfEmptyInmyIntersectionOn2S++;

        if (LevelOfEmptyInmyIntersectionOn2S > 10)
        {
          pasuv[0] = pasSav[0];
          pasuv[1] = pasSav[1];
          pasuv[2] = pasSav[2];
          pasuv[3] = pasSav[3];
        }
      }
      else
      {

        if (NoTestDeflection)
        {
          NoTestDeflection = false;
        }
        else
        {
          if (--LevelOfEmptyInmyIntersectionOn2S <= 0)
          {
            LevelOfEmptyInmyIntersectionOn2S = 0;
            if (LevelOfIterWithoutAppend < 10)
            {
              aStatus = TestDeflection(ChoixIso, aStatus);
            }
            else
            {
              if (aStatus != IntWalk_StepTooSmall)
              {

                pasuv[0] *= 0.5;
                pasuv[1] *= 0.5;
                pasuv[2] *= 0.5;
                pasuv[3] *= 0.5;
              }
            }
          }
        }

        if (LevelOfPointConfondu > 5)
        {
          aStatus              = IntWalk_ArretSurPoint;
          LevelOfPointConfondu = 0;
        }

        if (aStatus == IntWalk_OK)
        {
          NbPasOKConseq++;
          if (NbPasOKConseq >= 5)
          {
            NbPasOKConseq = 0;
            bool   pastroppetit;
            double t;

            do
            {
              pastroppetit = true;

              if (pasuv[0] < pasInit[0])
              {
                t = (pasInit[0] - pasuv[0]) * 0.25;
                if (t > 0.1 * pasInit[0])
                {
                  t = 0.1 * pasuv[0];
                }

                pasuv[0] += t;
                pastroppetit = false;
              }

              if (pasuv[1] < pasInit[1])
              {
                t = (pasInit[1] - pasuv[1]) * 0.25;
                if (t > 0.1 * pasInit[1])
                {
                  t = 0.1 * pasuv[1];
                }

                pasuv[1] += t;
                pastroppetit = false;
              }

              if (pasuv[2] < pasInit[2])
              {
                t = (pasInit[2] - pasuv[2]) * 0.25;
                if (t > 0.1 * pasInit[2])
                {
                  t = 0.1 * pasuv[2];
                }

                pasuv[2] += t;
                pastroppetit = false;
              }

              if (pasuv[3] < pasInit[3])
              {
                t = (pasInit[3] - pasuv[3]) * 0.25;
                if (t > 0.1 * pasInit[3])
                {
                  t = 0.1 * pasuv[3];
                }
                pasuv[3] += t;
                pastroppetit = false;
              }
              if (pastroppetit)
              {
                if (pasMax < 0.1)
                {
                  pasMax *= 1.1;
                  pasInit[0] *= 1.1;
                  pasInit[1] *= 1.1;
                  pasInit[2] *= 1.1;
                  pasInit[3] *= 1.1;
                }
                else
                {
                  pastroppetit = false;
                }
              }
            } while (pastroppetit);
          }
        }
        else
          NbPasOKConseq = 0;

        switch (aStatus)
        {
          case IntWalk_ArretSurPointPrecedent:
          {
            Arrive = false;
            RepartirOuDiviser(DejaReparti, ChoixIso, Arrive);
            break;
          }
          case IntWalk_PasTropGrand:
          {
            Param(1) = SvParam[0];
            Param(2) = SvParam[1];
            Param(3) = SvParam[2];
            Param(4) = SvParam[3];

            if (LevelOfIterWithoutAppend > 5)
            {
              for (int i = 0; i < 4; i++)
              {
                if (pasSav[i] > pasInit[i])
                  continue;

                const double aDelta = (pasInit[i] - pasSav[i]) * 0.25;

                if (aDelta > Epsilon(pasInit[i]))
                {
                  pasInit[i] -= aDelta;
                  if ((aPrevStatus != IntWalk_StepTooSmall) && (line->NbPoints() != aPrevNbPoints))
                  {
                    LevelOfIterWithoutAppend = 0;
                  }

                  aPrevNbPoints = line->NbPoints();
                }
              }
            }

            break;
          }
          case IntWalk_PointConfondu:
          {
            LevelOfPointConfondu++;

            if (LevelOfPointConfondu > 5)
            {
              bool pastroppetit;

              do
              {
                pastroppetit = true;

                for (int i = 0; i < 4; i++)
                {
                  if (pasuv[i] < pasInit[i])
                  {
                    pasuv[i] += (pasInit[i] - pasuv[i]) * 0.25;
                    pastroppetit = false;
                  }
                }

                if (pastroppetit)
                {
                  if (pasMax < 0.1)
                  {
                    pasMax *= 1.1;
                    pasInit[0] *= 1.1;
                    pasInit[1] *= 1.1;
                    pasInit[2] *= 1.1;
                    pasInit[3] *= 1.1;
                  }
                  else
                  {
                    pastroppetit = false;
                  }
                }
              } while (pastroppetit);
            }

            break;
          }
          case IntWalk_StepTooSmall:
          {
            bool hasStepBeenIncreased = false;

            for (int i = 0; i < 4; i++)
            {
              const double aNewStep = std::min(1.5 * pasuv[i], pasInit[i]);
              if (aNewStep > pasuv[i])
              {
                pasuv[i]             = aNewStep;
                hasStepBeenIncreased = true;
              }
            }

            if (hasStepBeenIncreased)
            {
              Param(1) = SvParam[0];
              Param(2) = SvParam[1];
              Param(3) = SvParam[2];
              Param(4) = SvParam[3];

              if ((aPrevStatus != IntWalk_PasTropGrand) && (line->NbPoints() != aPrevNbPoints))
              {
                LevelOfIterWithoutAppend = 0;
              }

              aPrevNbPoints = line->NbPoints();

              break;
            }
          }
            [[fallthrough]];
          case IntWalk_OK:
          case IntWalk_ArretSurPoint:
          {

            Arrive = TestArret(DejaReparti, Param, ChoixIso);

            if (!Arrive && aStatus == IntWalk_ArretSurPoint)
            {
              Arrive = true;
#ifdef OCCT_DEBUG
              std::cout << "IntWalk_PWalking_1.gxx: Problems with intersection" << std::endl;
#endif
            }

            if (Arrive)
            {
              NbPasOKConseq = -10;
            }

            if (!Arrive)
            {

              bool pointisvalid = false;
              {
                double u1, v1, u2, v2;
                myIntersectionOn2S.Point().Parameters(u1, v1, u2, v2);

                if (u1 <= UM1 && u2 <= UM2 && v1 <= VM1 && v2 <= VM2 && u1 >= Um1 && u2 >= Um2
                    && v1 >= Vm1 && v2 >= Vm2)
                {
                  pointisvalid = true;
                }
              }

              if (pointisvalid)
              {
                previousPoint = myIntersectionOn2S.Point();
                previoustg    = myIntersectionOn2S.IsTangent();

                if (!previoustg)
                {
                  previousd  = myIntersectionOn2S.Direction();
                  previousd1 = myIntersectionOn2S.DirectionOnS1();
                  previousd2 = myIntersectionOn2S.DirectionOnS2();
                }

                {
                  double u1, v1, u2, v2;
                  previousPoint.Parameters(u1, v1, u2, v2);
                  if (u1 <= UM1 && u2 <= UM2 && v1 <= VM1 && v2 <= VM2 && u1 >= Um1 && u2 >= Um2
                      && v1 >= Vm1 && v2 >= Vm2)
                  {
                    pl = previousPoint.Value();
                    if (bTestFirstPoint)
                    {
                      if (pf.SquareDistance(pl) < aSQDistMax)
                      {
                        IncKey++;
                        if (IncKey == 5000)
                          return;
                        else
                          continue;
                      }
                      else
                      {
                        bTestFirstPoint = false;
                      }
                    }

                    AddAPoint(previousPoint);
                    RejectIndex++;

                    if (RejectIndex >= RejectIndexMAX)
                    {
                      Arrive = true;
                      break;
                    }

                    LevelOfIterWithoutAppend = 0;
                  }
                }
              }

              if (aStatus == IntWalk_ArretSurPoint)
              {
                RepartirOuDiviser(DejaReparti, ChoixIso, Arrive);
              }
              else
              {
                if (line->NbPoints() == 2)
                {
                  pasSav[0] = pasuv[0];
                  pasSav[1] = pasuv[1];
                  pasSav[2] = pasuv[2];
                  pasSav[3] = pasuv[3];

                  if ((aPrevStatus == IntWalk_PasTropGrand) && (LevelOfIterWithoutAppend > 0))
                  {
                    pasInit[0] = pasuv[0];
                    pasInit[1] = pasuv[1];
                    pasInit[2] = pasuv[2];
                    pasInit[3] = pasuv[3];
                  }
                }
              }
            }
            else
            {
              if (close)
              {

                AddAPoint(line->Value(1));
                LevelOfIterWithoutAppend = 0;
              }
              else
              {

                bool bPrevNotTangent = !previoustg || !myIntersectionOn2S.IsTangent();

                IntImp_ConstIsoparametric SauvChoixIso = ChoixIso;
                ChoixIso = myIntersectionOn2S.Perform(Param, Rsnld, ChoixIso);

                if (!myIntersectionOn2S.IsEmpty())
                {

                  if (TestArret(true, Param, ChoixIso))
                  {
                    NbPasOKConseq = -10;
                    ChoixIso      = myIntersectionOn2S.Perform(Param, Rsnld, ChoixIso);

                    if (!myIntersectionOn2S.IsEmpty())
                    {
                      previousPoint = myIntersectionOn2S.Point();
                      previoustg    = myIntersectionOn2S.IsTangent();

                      if (!previoustg)
                      {
                        previousd  = myIntersectionOn2S.Direction();
                        previousd1 = myIntersectionOn2S.DirectionOnS1();
                        previousd2 = myIntersectionOn2S.DirectionOnS2();
                      }

                      pl = previousPoint.Value();

                      if (bTestFirstPoint)
                      {
                        if (pf.SquareDistance(pl) < aSQDistMax)
                        {
                          IncKey++;
                          if (IncKey == 5000)
                            return;
                          else
                            continue;
                        }
                        else
                        {
                          bTestFirstPoint = false;
                        }
                      }

                      AddAPoint(previousPoint);
                      RejectIndex++;

                      if (RejectIndex >= RejectIndexMAX)
                      {
                        Arrive = true;
                        break;
                      }

                      LevelOfIterWithoutAppend = 0;
                      RepartirOuDiviser(DejaReparti, ChoixIso, Arrive);
                    }
                    else
                    {

                      Arrive = false;
                      RepartirOuDiviser(DejaReparti, ChoixIso, Arrive);
                      NoTestDeflection = true;
                      ChoixIso         = SauvChoixIso;
                    }
                  }
                  else
                  {

                    IntSurf_PntOn2S previousPointSave = previousPoint;
                    bool            previoustgSave    = previoustg;
                    gp_Dir          previousdSave     = previousd;
                    gp_Dir2d        previousd1Save    = previousd1;
                    gp_Dir2d        previousd2Save    = previousd2;

                    previousPoint = myIntersectionOn2S.Point();
                    previoustg    = myIntersectionOn2S.IsTangent();
                    Arrive        = false;

                    if (!previoustg)
                    {
                      previousd  = myIntersectionOn2S.Direction();
                      previousd1 = myIntersectionOn2S.DirectionOnS1();
                      previousd2 = myIntersectionOn2S.DirectionOnS2();
                    }

                    {
                      double u1, v1, u2, v2;
                      previousPoint.Parameters(u1, v1, u2, v2);

                      gp_Pnt2d ParamPntOnS1(Param(1), Param(2));
                      gp_Pnt2d ParamPntOnS2(Param(3), Param(4));

                      Param(1) = u1;
                      Param(2) = v1;
                      Param(3) = u2;
                      Param(4) = v2;

                      bool   bFlag1, bFlag2;
                      double aTol2D = 1.e-11;

                      bFlag1 = u1 >= Um1 - aTol2D && v1 >= Vm1 - aTol2D && u1 <= UM1 + aTol2D
                               && v1 <= VM1 + aTol2D;
                      bFlag2 = u2 >= Um2 - aTol2D && v2 >= Vm2 - aTol2D && u2 <= UM2 + aTol2D
                               && v2 <= VM2 + aTol2D;
                      if (bFlag1 && bFlag2)
                      {
                        if (line->NbPoints() > 1)
                        {
                          IntSurf_PntOn2S prevprevPoint = line->Value(line->NbPoints() - 1);
                          double          ppU1, ppV1, ppU2, ppV2;
                          prevprevPoint.Parameters(ppU1, ppV1, ppU2, ppV2);
                          double pU1, pV1, pU2, pV2;
                          previousPointSave.Parameters(pU1, pV1, pU2, pV2);
                          gp_Vec2d V1onS1(gp_Pnt2d(ppU1, ppV1), gp_Pnt2d(pU1, pV1));
                          gp_Vec2d V2onS1(gp_Pnt2d(pU1, pV1), gp_Pnt2d(u1, v1));
                          gp_Vec2d V1onS2(gp_Pnt2d(ppU2, ppV2), gp_Pnt2d(pU2, pV2));
                          gp_Vec2d V2onS2(gp_Pnt2d(pU2, pV2), gp_Pnt2d(u2, v2));

                          const double aDot1 = V1onS1 * V2onS1;
                          const double aDot2 = V1onS2 * V2onS2;

                          if ((aDot1 < 0.0) || (aDot2 < 0.0))
                          {
                            Arrive = true;
                            break;
                          }
                        }

                        pl = previousPoint.Value();

                        if (bTestFirstPoint)
                        {
                          if (pf.SquareDistance(pl) < aSQDistMax)
                          {
                            IncKey++;

                            if (IncKey == 5000)
                              return;
                            else
                              continue;
                          }
                          else
                          {
                            bTestFirstPoint = false;
                          }
                        }

                        if (previoustg)
                        {

                          double prevU1, prevV1, prevU2, prevV2;
                          previousPointSave.Parameters(prevU1, prevV1, prevU2, prevV2);
                          gp_Pnt2d     prevPntOnS1(prevU1, prevV1), prevPntOnS2(prevU2, prevV2);
                          gp_Pnt2d     curPntOnS1(u1, v1), curPntOnS2(u2, v2);
                          gp_Vec2d     PrevToParamOnS1(prevPntOnS1, ParamPntOnS1);
                          gp_Vec2d     PrevToCurOnS1(prevPntOnS1, curPntOnS1);
                          gp_Vec2d     PrevToParamOnS2(prevPntOnS2, ParamPntOnS2);
                          gp_Vec2d     PrevToCurOnS2(prevPntOnS2, curPntOnS2);
                          double       MaxAngle  = 3 * M_PI / 4;
                          double       anAngleS1 = 0.0, anAngleS2 = 0.0;
                          const double aSQMParS1 = PrevToParamOnS1.SquareMagnitude();
                          const double aSQMParS2 = PrevToParamOnS2.SquareMagnitude();
                          const double aSQMCurS1 = PrevToCurOnS1.SquareMagnitude();
                          const double aSQMCurS2 = PrevToCurOnS2.SquareMagnitude();

                          if (aSQMCurS1 < gp::Resolution())
                          {

                            anAngleS1 = M_PI;
                          }
                          else if (aSQMParS1 < gp::Resolution())
                          {

                            anAngleS1 = 0.0;
                          }
                          else
                          {
                            anAngleS1 = std::abs(PrevToParamOnS1.Angle(PrevToCurOnS1));
                          }

                          if (aSQMCurS2 < gp::Resolution())
                          {

                            anAngleS2 = M_PI;
                          }
                          else if (aSQMParS2 < gp::Resolution())
                          {

                            anAngleS2 = 0.0;
                          }
                          else
                          {
                            anAngleS2 = std::abs(PrevToParamOnS2.Angle(PrevToCurOnS2));
                          }

                          if ((anAngleS1 > MaxAngle) && (anAngleS2 > MaxAngle))
                          {
                            Arrive = true;
                            break;
                          }

                          {

                            const gp_Vec2d aDirS1(prevPntOnS1, curPntOnS1),
                              aDirS2(prevPntOnS2, curPntOnS2);

                            gp_Pnt aPtemp;
                            gp_Vec aDuS1, aDvS1, aDuS2, aDvS2;

                            myIntersectionOn2S.Function().AuxillarSurface1()->D1(curPntOnS1.X(),
                                                                                 curPntOnS1.Y(),
                                                                                 aPtemp,
                                                                                 aDuS1,
                                                                                 aDvS1);
                            myIntersectionOn2S.Function().AuxillarSurface2()->D1(curPntOnS2.X(),
                                                                                 curPntOnS2.Y(),
                                                                                 aPtemp,
                                                                                 aDuS2,
                                                                                 aDvS2);

                            const double aF1x = aDuS1.X() * aDirS1.X() + aDvS1.X() * aDirS1.Y();
                            const double aF1y = aDuS1.Y() * aDirS1.X() + aDvS1.Y() * aDirS1.Y();
                            const double aF1z = aDuS1.Z() * aDirS1.X() + aDvS1.Z() * aDirS1.Y();
                            const double aF2x = aDuS2.X() * aDirS2.X() + aDvS2.X() * aDirS2.Y();
                            const double aF2y = aDuS2.Y() * aDirS2.X() + aDvS2.Y() * aDirS2.Y();
                            const double aF2z = aDuS2.Z() * aDirS2.X() + aDvS2.Z() * aDirS2.Y();

                            const double aF1 = aF1x * aF1x + aF1y * aF1y + aF1z * aF1z;
                            const double aF2 = aF2x * aF2x + aF2y * aF2y + aF2z * aF2z;

                            if ((aF1 < gp::Resolution()) && (aF2 < gp::Resolution()))
                            {

                              Arrive = true;
                              break;
                            }
                          }
                        }

                        AddAPoint(previousPoint);
                        RejectIndex++;

                        if (RejectIndex >= RejectIndexMAX)
                        {
                          Arrive = true;
                          break;
                        }

                        LevelOfIterWithoutAppend = 0;
                        Arrive                   = true;
                      }
                      else
                      {

                        previousPoint = previousPointSave;
                        previoustg    = previoustgSave;
                        previousd     = previousdSave;
                        previousd1    = previousd1Save;
                        previousd2    = previousd2Save;
                      }
                    }

                    bool wasExtended = false;

                    if (Arrive && myIntersectionOn2S.IsTangent() && bPrevNotTangent)
                    {
                      if (ExtendLineInCommonZone(SauvChoixIso, DejaReparti))
                      {
                        wasExtended = true;
                        Arrive      = false;
                        ChoixIso    = SauvChoixIso;
                      }
                    }

                    RepartirOuDiviser(DejaReparti, ChoixIso, Arrive);

                    if (Arrive && myIntersectionOn2S.IsDone() && !myIntersectionOn2S.IsEmpty()
                        && myIntersectionOn2S.IsTangent() && bPrevNotTangent && !wasExtended)
                    {
                      if (ExtendLineInCommonZone(SauvChoixIso, DejaReparti))
                      {
                        wasExtended = true;
                        Arrive      = false;
                        ChoixIso    = SauvChoixIso;
                      }
                    }
                  }
                }
                else
                {

                  Arrive           = false;
                  NoTestDeflection = true;
                  RepartirOuDiviser(DejaReparti, ChoixIso, Arrive);
                }
              }
            }
          }
        }
      }
    }
  }

  done = true;
}

bool IntWalk_PWalking::ExtendLineInCommonZone(const IntImp_ConstIsoparametric theChoixIso,
                                              const bool                      theDirectionFlag)
{

  const occ::handle<Adaptor3d_Surface>& Caro1 = myIntersectionOn2S.Function().AuxillarSurface1();
  const occ::handle<Adaptor3d_Surface>& Caro2 = myIntersectionOn2S.Function().AuxillarSurface2();

  const double UFirst1 = Adaptor3d_HSurfaceTool::FirstUParameter(Caro1);
  const double VFirst1 = Adaptor3d_HSurfaceTool::FirstVParameter(Caro1);
  const double ULast1  = Adaptor3d_HSurfaceTool::LastUParameter(Caro1);
  const double VLast1  = Adaptor3d_HSurfaceTool::LastVParameter(Caro1);

  const double UFirst2 = Adaptor3d_HSurfaceTool::FirstUParameter(Caro2);
  const double VFirst2 = Adaptor3d_HSurfaceTool::FirstVParameter(Caro2);
  const double ULast2  = Adaptor3d_HSurfaceTool::LastUParameter(Caro2);
  const double VLast2  = Adaptor3d_HSurfaceTool::LastVParameter(Caro2);

  bool                                  bOutOfTangentZone = false;
  bool                                  bStop             = !myIntersectionOn2S.IsTangent();
  int                                   dIncKey           = 1;
  NCollection_Array1<double>            Param(1, 4);
  IntWalk_StatusDeflection              aStatus             = IntWalk_OK;
  int                                   nbIterWithoutAppend = 0;
  int                                   nbEqualPoints       = 0;
  int                                   parit               = 0;
  int                                   uvit                = 0;
  NCollection_Sequence<IntSurf_PntOn2S> aSeqOfNewPoint;

  previousPoint.Parameters(Param(1), Param(2), Param(3), Param(4));

  if (Param(1) - UFirst1 < ResoU1)
  {
    return bOutOfTangentZone;
  }
  else if (Param(2) - VFirst1 < ResoV1)
  {
    return bOutOfTangentZone;
  }
  else if (Param(3) - UFirst2 < ResoU2)
  {
    return bOutOfTangentZone;
  }
  else if (Param(4) - VFirst2 < ResoV2)
  {
    return bOutOfTangentZone;
  }

  if (Param(1) - ULast1 > -ResoU1)
  {
    return bOutOfTangentZone;
  }
  else if (Param(2) - VLast1 > -ResoV1)
  {
    return bOutOfTangentZone;
  }
  else if (Param(3) - ULast2 > -ResoU2)
  {
    return bOutOfTangentZone;
  }
  else if (Param(4) - VLast2 > -ResoV2)
  {
    return bOutOfTangentZone;
  }

  while (!bStop)
  {
    nbIterWithoutAppend++;

    if ((nbIterWithoutAppend > 20) || (nbEqualPoints > 20))
    {
#ifdef OCCT_DEBUG
      std::cout << "Infinite loop detected. Stop iterations (IntWalk_PWalking_1.gxx)" << std::endl;
#endif
      bStop = true;
      break;
    }
    double f = 0.;

    switch (theChoixIso)
    {
      case IntImp_UIsoparametricOnCaro1:
        f = std::abs(previousd1.X());
        break;
      case IntImp_VIsoparametricOnCaro1:
        f = std::abs(previousd1.Y());
        break;
      case IntImp_UIsoparametricOnCaro2:
        f = std::abs(previousd2.X());
        break;
      case IntImp_VIsoparametricOnCaro2:
        f = std::abs(previousd2.Y());
        break;
    }

    if (f < 0.1)
      f = 0.1;

    previousPoint.Parameters(Param(1), Param(2), Param(3), Param(4));

    double dP1 = sensCheminement * pasuv[0] * previousd1.X() / f;
    double dP2 = sensCheminement * pasuv[1] * previousd1.Y() / f;
    double dP3 = sensCheminement * pasuv[2] * previousd2.X() / f;
    double dP4 = sensCheminement * pasuv[3] * previousd2.Y() / f;

    if (theChoixIso == IntImp_UIsoparametricOnCaro1 && std::abs(dP1) < 1.e-7)
      dP1 *= (5. * (double)dIncKey);
    if (theChoixIso == IntImp_VIsoparametricOnCaro1 && std::abs(dP2) < 1.e-7)
      dP2 *= (5. * (double)dIncKey);
    if (theChoixIso == IntImp_UIsoparametricOnCaro2 && std::abs(dP3) < 1.e-7)
      dP3 *= (5. * (double)dIncKey);
    if (theChoixIso == IntImp_VIsoparametricOnCaro2 && std::abs(dP4) < 1.e-7)
      dP4 *= (5. * (double)dIncKey);

    Param(1) += dP1;
    Param(2) += dP2;
    Param(3) += dP3;
    Param(4) += dP4;
    double                    SvParam[4];
    IntImp_ConstIsoparametric ChoixIso = theChoixIso;

    for (parit = 0; parit < 4; parit++)
    {
      SvParam[parit] = Param(parit + 1);
    }
    math_FunctionSetRoot Rsnld(myIntersectionOn2S.Function());
    ChoixIso = myIntersectionOn2S.Perform(Param, Rsnld, theChoixIso);

    if (!myIntersectionOn2S.IsDone())
    {
      return bOutOfTangentZone;
    }
    else
    {
      if (myIntersectionOn2S.IsEmpty())
      {
        return bOutOfTangentZone;
      }

      aStatus = TestDeflection(ChoixIso, aStatus);

      if (aStatus == IntWalk_OK)
      {

        for (uvit = 0; uvit < 4; uvit++)
        {
          if (pasuv[uvit] < pasInit[uvit])
          {
            pasuv[uvit] = pasInit[uvit];
          }
        }
      }

      switch (aStatus)
      {
        case IntWalk_ArretSurPointPrecedent:
        {
          bStop             = true;
          bOutOfTangentZone = !myIntersectionOn2S.IsTangent();
          break;
        }
        case IntWalk_PasTropGrand:
        {
          for (parit = 0; parit < 4; parit++)
          {
            Param(parit + 1) = SvParam[parit];
          }
          bool bDecrease = false;

          for (uvit = 0; uvit < 4; uvit++)
          {
            if (pasSav[uvit] < pasInit[uvit])
            {
              pasInit[uvit] -= (pasInit[uvit] - pasSav[uvit]) * 0.1;
              bDecrease = true;
            }
          }

          if (bDecrease)
            nbIterWithoutAppend--;
          break;
        }
        case IntWalk_PointConfondu:
        {
          for (uvit = 0; uvit < 4; uvit++)
          {
            if (pasuv[uvit] < pasInit[uvit])
            {
              pasuv[uvit] += (pasInit[uvit] - pasuv[uvit]) * 0.1;
            }
          }
          break;
        }
        case IntWalk_OK:
        case IntWalk_ArretSurPoint:
        {

          bStop = TestArret(theDirectionFlag, Param, ChoixIso);

          if (!bStop)
          {
            double u11, v11, u12, v12;
            myIntersectionOn2S.Point().Parameters(u11, v11, u12, v12);
            double u21, v21, u22, v22;
            previousPoint.Parameters(u21, v21, u22, v22);

            if (((fabs(u11 - u21) < ResoU1) && (fabs(v11 - v21) < ResoV1))
                || ((fabs(u12 - u22) < ResoU2) && (fabs(v12 - v22) < ResoV2)))
            {
              nbEqualPoints++;
            }
            else
            {
              nbEqualPoints = 0;
            }
          }

          bStop             = bStop || !myIntersectionOn2S.IsTangent();
          bOutOfTangentZone = !myIntersectionOn2S.IsTangent();

          if (!bStop)
          {
            bool   pointisvalid = false;
            double u1, v1, u2, v2;
            myIntersectionOn2S.Point().Parameters(u1, v1, u2, v2);

            if (u1 <= UM1 && u2 <= UM2 && v1 <= VM1 && v2 <= VM2 && u1 >= Um1 && u2 >= Um2
                && v1 >= Vm1 && v2 >= Vm2)
              pointisvalid = true;

            if (pointisvalid)
            {
              previousPoint = myIntersectionOn2S.Point();
              previoustg    = myIntersectionOn2S.IsTangent();

              if (!previoustg)
              {
                previousd  = myIntersectionOn2S.Direction();
                previousd1 = myIntersectionOn2S.DirectionOnS1();
                previousd2 = myIntersectionOn2S.DirectionOnS2();
              }
              bool bAddPoint = true;

              if (line->NbPoints() >= 1)
              {
                gp_Pnt pf = line->Value(1).Value();
                gp_Pnt pl = previousPoint.Value();

                if (pf.Distance(pl) < Precision::Confusion())
                {
                  dIncKey++;
                  if (dIncKey == 5000)
                    return bOutOfTangentZone;
                  else
                    bAddPoint = false;
                }
              }

              if (bAddPoint)
              {
                aSeqOfNewPoint.Append(previousPoint);
                nbIterWithoutAppend = 0;
              }
            }

            if (line->NbPoints() == 2)
            {
              for (uvit = 0; uvit < 4; uvit++)
              {
                pasSav[uvit] = pasuv[uvit];
              }
            }

            if (!pointisvalid)
            {

              if ((u1 > UM1) || (u1 < Um1))
                pasuv[0] *= 0.5;

              if ((v1 > VM1) || (v1 < Vm1))
                pasuv[1] *= 0.5;

              if ((u2 > UM2) || (u2 < Um2))
                pasuv[2] *= 0.5;

              if ((v2 > VM2) || (v2 < Vm2))
                pasuv[3] *= 0.5;
            }
          }
          else
          {
            if (close && (line->NbPoints() >= 1))
            {

              if (!bOutOfTangentZone)
              {
                aSeqOfNewPoint.Append(line->Value(1));
              }
              nbIterWithoutAppend = 0;
            }
            else
            {
              ChoixIso = myIntersectionOn2S.Perform(Param, Rsnld, theChoixIso);

              if (myIntersectionOn2S.IsEmpty())
              {
                bStop             = true;
                bOutOfTangentZone = false;
              }
              else
              {
                bool bAddPoint    = true;
                bool pointisvalid = false;

                previousPoint = myIntersectionOn2S.Point();
                double u1, v1, u2, v2;
                previousPoint.Parameters(u1, v1, u2, v2);

                if (u1 <= UM1 && u2 <= UM2 && v1 <= VM1 && v2 <= VM2 && u1 >= Um1 && u2 >= Um2
                    && v1 >= Vm1 && v2 >= Vm2)
                  pointisvalid = true;

                if (pointisvalid)
                {

                  if (line->NbPoints() >= 1)
                  {
                    gp_Pnt pf = line->Value(1).Value();
                    gp_Pnt pl = previousPoint.Value();

                    if (pf.Distance(pl) < Precision::Confusion())
                    {
                      dIncKey++;
                      if (dIncKey == 5000)
                        return bOutOfTangentZone;
                      else
                        bAddPoint = false;
                    }
                  }

                  if (bAddPoint && !bOutOfTangentZone)
                  {
                    aSeqOfNewPoint.Append(previousPoint);
                    nbIterWithoutAppend = 0;
                  }
                }
              }
            }
          }
          break;
        }
        default:
        {
          break;
        }
      }
    }
  }
  bool   bExtendLine = false;
  double u1 = 0., v1 = 0., u2 = 0., v2 = 0.;

  int pit = 0;

  for (pit = 0; !bExtendLine && (pit < 2); pit++)
  {
    if (pit == 0)
      previousPoint.Parameters(u1, v1, u2, v2);
    else
    {
      if (aSeqOfNewPoint.Length() > 0)
        aSeqOfNewPoint.Value(aSeqOfNewPoint.Length()).Parameters(u1, v1, u2, v2);
      else
        break;
    }

    if (((u1 - Um1) < ResoU1) || ((UM1 - u1) < ResoU1) || ((u2 - Um2) < ResoU2)
        || ((UM2 - u2) < ResoU2) || ((v1 - Vm1) < ResoV1) || ((VM1 - v1) < ResoV1)
        || ((v2 - Vm2) < ResoV2) || ((VM2 - v2) < ResoV2))
      bExtendLine = true;
  }

  if (!bExtendLine)
  {

    if (aStatus == IntWalk_OK)
    {
      bExtendLine = true;

      if (aSeqOfNewPoint.Length() > 1)
      {
        NCollection_Array1<double> FirstParams(0, 3), LastParams(0, 3), Resolutions(0, 3);
        Resolutions(0) = ResoU1;
        Resolutions(1) = ResoV1;
        Resolutions(2) = ResoU2;
        Resolutions(3) = ResoV2;

        aSeqOfNewPoint(1).Parameters(FirstParams.ChangeValue(0),
                                     FirstParams.ChangeValue(1),
                                     FirstParams.ChangeValue(2),
                                     FirstParams.ChangeValue(3));
        aSeqOfNewPoint(aSeqOfNewPoint.Length())
          .Parameters(LastParams.ChangeValue(0),
                      LastParams.ChangeValue(1),
                      LastParams.ChangeValue(2),
                      LastParams.ChangeValue(3));
        int indexofiso = 0;

        if (theChoixIso == IntImp_UIsoparametricOnCaro1)
          indexofiso = 0;
        if (theChoixIso == IntImp_VIsoparametricOnCaro1)
          indexofiso = 1;
        if (theChoixIso == IntImp_UIsoparametricOnCaro2)
          indexofiso = 2;
        if (theChoixIso == IntImp_VIsoparametricOnCaro2)
          indexofiso = 3;

        int      afirstindex = (indexofiso < 2) ? 0 : 2;
        gp_Vec2d aTangentZoneDir(
          gp_Pnt2d(FirstParams.Value(afirstindex), FirstParams.Value(afirstindex + 1)),
          gp_Pnt2d(LastParams.Value(afirstindex), LastParams.Value(afirstindex + 1)));

        gp_Dir2d anIsoDir(gp_Dir2d::D::Y);

        if ((indexofiso == 1) || (indexofiso == 3))
          anIsoDir = gp_Dir2d(gp_Dir2d::D::X);

        if (aTangentZoneDir.SquareMagnitude() > gp::Resolution())
        {
          double piquota = M_PI * 0.25;

          if (fabs(aTangentZoneDir.Angle(anIsoDir)) > piquota)
          {
            int      ii = 1, nextii = 2;
            gp_Vec2d d1(0, 0);
            double   asqresol = gp::Resolution();
            asqresol *= asqresol;

            do
            {
              aSeqOfNewPoint(ii).Parameters(FirstParams.ChangeValue(0),
                                            FirstParams.ChangeValue(1),
                                            FirstParams.ChangeValue(2),
                                            FirstParams.ChangeValue(3));
              aSeqOfNewPoint(ii + 1).Parameters(LastParams.ChangeValue(0),
                                                LastParams.ChangeValue(1),
                                                LastParams.ChangeValue(2),
                                                LastParams.ChangeValue(3));
              d1 = gp_Vec2d(
                gp_Pnt2d(FirstParams.Value(afirstindex), FirstParams.Value(afirstindex + 1)),
                gp_Pnt2d(LastParams.Value(afirstindex), LastParams.Value(afirstindex + 1)));
              ii++;
            } while ((d1.SquareMagnitude() < asqresol) && (ii < aSeqOfNewPoint.Length()));

            nextii = ii;

            while (nextii < aSeqOfNewPoint.Length())
            {

              gp_Vec2d nextd1(0, 0);
              int      jj = nextii;

              do
              {
                aSeqOfNewPoint(jj).Parameters(FirstParams.ChangeValue(0),
                                              FirstParams.ChangeValue(1),
                                              FirstParams.ChangeValue(2),
                                              FirstParams.ChangeValue(3));
                aSeqOfNewPoint(jj + 1).Parameters(LastParams.ChangeValue(0),
                                                  LastParams.ChangeValue(1),
                                                  LastParams.ChangeValue(2),
                                                  LastParams.ChangeValue(3));
                nextd1 = gp_Vec2d(
                  gp_Pnt2d(FirstParams.Value(afirstindex), FirstParams.Value(afirstindex + 1)),
                  gp_Pnt2d(LastParams.Value(afirstindex), LastParams.Value(afirstindex + 1)));
                jj++;

              } while ((nextd1.SquareMagnitude() < asqresol) && (jj < aSeqOfNewPoint.Length()));
              nextii = jj;

              if (fabs(d1.Angle(nextd1)) > piquota)
              {
                bExtendLine = false;
                break;
              }
              d1 = nextd1;
            }
          }
        }
      }
    }
  }

  if (!bExtendLine)
  {
    return false;
  }
  int i = 0;

  for (i = 1; i <= aSeqOfNewPoint.Length(); i++)
  {
    AddAPoint(aSeqOfNewPoint.Value(i));
  }

  return bOutOfTangentZone;
}

bool IntWalk_PWalking::DistanceMinimizeByGradient(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                                  const occ::handle<Adaptor3d_Surface>& theASurf2,
                                                  NCollection_Array1<double>&           theInit,
                                                  const double*                         theStep0)
{
  const int        aNbIterMAX = 60;
  const double     aTol       = 1.0e-14;
  constexpr double aTolNul    = 1.0 / Precision::Infinite();

  const double aMinAddValU1 = std::max(Epsilon(theInit(1)), aTolNul);
  const double aMinAddValV1 = std::max(Epsilon(theInit(2)), aTolNul);
  const double aMinAddValU2 = std::max(Epsilon(theInit(3)), aTolNul);
  const double aMinAddValV2 = std::max(Epsilon(theInit(4)), aTolNul);

  occ::handle<Geom_Surface> aS1, aS2;

  if (theASurf1->GetType() != GeomAbs_BezierSurface
      && theASurf1->GetType() != GeomAbs_BSplineSurface)
    return true;
  if (theASurf2->GetType() != GeomAbs_BezierSurface
      && theASurf2->GetType() != GeomAbs_BSplineSurface)
    return true;

  bool aStatus = false;

  gp_Pnt aP1, aP2;
  gp_Vec aD1u, aD1v, aD2U, aD2V;

  theASurf1->D1(theInit(1), theInit(2), aP1, aD1u, aD1v);
  theASurf2->D1(theInit(3), theInit(4), aP2, aD2U, aD2V);

  double aSQDistPrev = aP1.SquareDistance(aP2);

  gp_Vec aP12(aP1, aP2);

  double aGradFu(-aP12.Dot(aD1u));
  double aGradFv(-aP12.Dot(aD1v));
  double aGradFU(aP12.Dot(aD2U));
  double aGradFV(aP12.Dot(aD2V));

  double aStepU1 = 1.0e-6, aStepV1 = 1.0e-6, aStepU2 = 1.0e-6, aStepV2 = 1.0e-6;

  if (theStep0)
  {
    aStepU1 = theStep0[0];
    aStepV1 = theStep0[1];
    aStepU2 = theStep0[2];
    aStepV2 = theStep0[3];
  }

  bool flRepeat = true;
  int  aNbIter  = aNbIterMAX;

  while (flRepeat)
  {
    double       anAdd = aGradFu * aStepU1;
    const double aPARu = theInit(1) - std::copysign(std::max(std::abs(anAdd), aMinAddValU1), anAdd);

    anAdd              = aGradFv * aStepV1;
    const double aPARv = theInit(2) - std::copysign(std::max(std::abs(anAdd), aMinAddValV1), anAdd);

    anAdd              = aGradFU * aStepU2;
    const double aParU = theInit(3) - std::copysign(std::max(std::abs(anAdd), aMinAddValU2), anAdd);

    anAdd              = aGradFV * aStepV2;
    const double aParV = theInit(4) - std::copysign(std::max(std::abs(anAdd), aMinAddValV2), anAdd);

    gp_Pnt aPt1, aPt2;

    theASurf1->D1(aPARu, aPARv, aPt1, aD1u, aD1v);
    theASurf2->D1(aParU, aParV, aPt2, aD2U, aD2V);

    double aSQDist = aPt1.SquareDistance(aPt2);

    if (aSQDist < aSQDistPrev)
    {
      aSQDistPrev = aSQDist;
      theInit(1)  = aPARu;
      theInit(2)  = aPARv;
      theInit(3)  = aParU;
      theInit(4)  = aParV;

      aStatus = aSQDistPrev < aTol;
      aStepU1 *= 1.2;
      aStepV1 *= 1.2;
      aStepU2 *= 1.2;
      aStepV2 *= 1.2;
    }
    else
    {
      if (--aNbIter < 0)
      {
        flRepeat = false;
      }
      else
      {
        theASurf1->D1(theInit(1), theInit(2), aPt1, aD1u, aD1v);
        theASurf2->D1(theInit(3), theInit(4), aPt2, aD2U, aD2V);

        gp_Vec aPt12(aPt1, aPt2);
        aGradFu = -aPt12.Dot(aD1u);
        aGradFv = -aPt12.Dot(aD1v);
        aGradFU = aPt12.Dot(aD2U);
        aGradFV = aPt12.Dot(aD2V);

        if (theStep0)
        {
          aStepU1 = theStep0[0];
          aStepV1 = theStep0[1];
          aStepU2 = theStep0[2];
          aStepV2 = theStep0[3];
        }
        else
        {
          aStepU1 = aStepV1 = aStepU2 = aStepV2 = 1.0e-6;
        }
      }
    }
  }

  return aStatus;
}

bool IntWalk_PWalking::DistanceMinimizeByExtrema(const occ::handle<Adaptor3d_Surface>& theASurf,
                                                 const gp_Pnt&                         theP0,
                                                 double&                               theU0,
                                                 double&                               theV0,
                                                 const double*                         theStep0)
{
  const double aTol = 1.0e-14;
  gp_Pnt       aPS;
  gp_Vec       aD1Su, aD1Sv, aD2Su, aD2Sv, aD2SuvTemp;
  double       aSQDistPrev = RealLast();
  double       aU = theU0, aV = theV0;

  const double aStep0[2] = {theStep0 ? theStep0[0] : 1.0, theStep0 ? theStep0[1] : 1.0};

  int aNbIter = 10;
  do
  {
    theASurf->D2(aU, aV, aPS, aD1Su, aD1Sv, aD2Su, aD2Sv, aD2SuvTemp);

    gp_Vec aVec(theP0, aPS);

    double aSQDist = aVec.SquareMagnitude();

    if (aSQDist >= aSQDistPrev)
      break;

    aSQDistPrev = aSQDist;
    theU0       = aU;
    theV0       = aV;
    aNbIter--;

    if (aSQDistPrev < aTol)
      break;

    const double aF1 = aD1Su.Dot(aVec), aF2 = aD1Sv.Dot(aVec);

    const double aDf1u = aD2Su.Dot(aVec) + aD1Su.Dot(aD1Su), aDf1v = aD2Su.Dot(aD1Sv),
                 aDf2u = aDf1v, aDf2v = aD2Sv.Dot(aVec) + aD1Sv.Dot(aD1Sv);

    const double aDet = aDf1u * aDf2v - aDf1v * aDf2u;
    aU -= aStep0[0] * (aDf2v * aF1 - aDf1v * aF2) / aDet;
    aV += aStep0[1] * (aDf2u * aF1 - aDf1u * aF2) / aDet;
  } while (aNbIter > 0);

  return (aSQDistPrev < aTol);
}

bool IntWalk_PWalking::HandleSingleSingularPoint(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                                 const occ::handle<Adaptor3d_Surface>& theASurf2,
                                                 const double                          the3DTol,
                                                 NCollection_Array1<double>&           thePnt)
{

  double                    aLowBorder[4] = {theASurf1->FirstUParameter(),
                                             theASurf1->FirstVParameter(),
                                             theASurf2->FirstUParameter(),
                                             theASurf2->FirstVParameter()};
  double                    aUppBorder[4] = {theASurf1->LastUParameter(),
                                             theASurf1->LastVParameter(),
                                             theASurf2->LastUParameter(),
                                             theASurf2->LastVParameter()};
  IntImp_ConstIsoparametric aLockedDir[4] = {IntImp_UIsoparametricOnCaro1,
                                             IntImp_VIsoparametricOnCaro1,
                                             IntImp_UIsoparametricOnCaro2,
                                             IntImp_VIsoparametricOnCaro2};

  IntWalk_TheInt2S     anInt(theASurf1, theASurf2, the3DTol);
  math_FunctionSetRoot aRsnld(anInt.Function());

  for (int i = 1; i <= 4; ++i)
  {
    if (std::abs(thePnt(i) - aLowBorder[i - 1]) < Precision::PConfusion()
        || std::abs(thePnt(i) - aUppBorder[i - 1]) < Precision::PConfusion())
    {

      anInt.Perform(thePnt, aRsnld, aLockedDir[i - 1]);

      if (!anInt.IsDone())
        continue;

      if (anInt.IsEmpty())
        continue;

      double aPars[4];
      anInt.Point().Parameters(aPars[0], aPars[1], aPars[2], aPars[3]);
      occ::handle<Adaptor3d_Surface> aSurfs[2] = {theASurf1, theASurf2};

      double aTol2 = the3DTol * the3DTol;
      gp_Pnt aP;
      gp_Vec aDU, aDV;
      gp_Pnt aPInt;
      int    k;
      for (k = 0; k < 2; ++k)
      {
        int iu, iv;
        iu = 2 * k;
        iv = iu + 1;
        aSurfs[k]->D1(aPars[iu], aPars[iv], aPInt, aDU, aDV);
        double aMod = aDU.Magnitude();
        if (aMod > Precision::Confusion())
        {
          double aTolU = the3DTol / aMod;
          if (std::abs(aLowBorder[iu] - aPars[iu]) < aTolU)
          {
            aP = aSurfs[k]->Value(aLowBorder[iu], aPars[iv]);
            if (aPInt.SquareDistance(aP) < aTol2)
              aPars[iu] = aLowBorder[iu];
          }
          else if (std::abs(aUppBorder[iu] - aPars[iu]) < aTolU)
          {
            aP = aSurfs[k]->Value(aUppBorder[iu], aPars[iv]);
            if (aPInt.SquareDistance(aP) < aTol2)
              aPars[iu] = aUppBorder[iu];
          }
        }
        aMod = aDV.Magnitude();
        if (aMod > Precision::Confusion())
        {
          double aTolV = the3DTol / aMod;
          if (std::abs(aLowBorder[iv] - aPars[iv]) < aTolV)
          {
            aP = aSurfs[k]->Value(aPars[iu], aLowBorder[iv]);
            if (aPInt.SquareDistance(aP) < aTol2)
              aPars[iv] = aLowBorder[iv];
          }
          else if (std::abs(aUppBorder[iv] - aPars[iv]) < aTolV)
          {
            aP = aSurfs[k]->Value(aPars[iu], aUppBorder[iv]);
            if (aPInt.SquareDistance(aP) < aTol2)
              aPars[iv] = aUppBorder[iv];
          }
        }
      }

      int j;
      for (j = 1; j <= 4; ++j)
      {
        thePnt(j) = aPars[j - 1];
      }
      bool isInDomain = true;
      for (j = 1; isInDomain && (j <= 4); ++j)
      {
        if ((thePnt(j) - aLowBorder[j - 1] + Precision::PConfusion())
              * (thePnt(j) - aUppBorder[j - 1] - Precision::PConfusion())
            > 0.0)
        {
          isInDomain = false;
        }
      }

      if (isInDomain)
        return true;
    }
  }

  return false;
}

bool IntWalk_PWalking::SeekPointOnBoundary(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                           const occ::handle<Adaptor3d_Surface>& theASurf2,
                                           const double                          theU1,
                                           const double                          theV1,
                                           const double                          theU2,
                                           const double                          theV2,
                                           const bool                            isTheFirst)
{
  bool isOK = false;

  const double aLowBorder[4] = {theASurf1->FirstUParameter(),
                                theASurf1->FirstVParameter(),
                                theASurf2->FirstUParameter(),
                                theASurf2->FirstVParameter()};
  const double aUppBorder[4] = {theASurf1->LastUParameter(),
                                theASurf1->LastVParameter(),
                                theASurf2->LastUParameter(),
                                theASurf2->LastVParameter()};

  const double aRes1  = std::max(Precision::PConfusion() / theASurf1->UResolution(1.0),
                                Precision::PConfusion() / theASurf1->VResolution(1.0));
  const double aRes2  = std::max(Precision::PConfusion() / theASurf2->UResolution(1.0),
                                Precision::PConfusion() / theASurf2->VResolution(1.0));
  const double a3DTol = std::max(aRes1, aRes2);
  const double aTol   = std::max(Precision::Confusion(), a3DTol);

  NCollection_Array1<double> aPnt(1, 4);
  aPnt(1) = theU1;
  aPnt(2) = theV1;
  aPnt(3) = theU2;
  aPnt(4) = theV2;
  NCollection_Array1<double> aSingularPnt(aPnt);

  int  aNbIter = 20;
  bool aStatus = false;
  do
  {
    aNbIter--;
    aStatus = DistanceMinimizeByGradient(theASurf1, theASurf2, aPnt);
    if (aStatus && !AdjustToDomain(4, &aPnt(1), &aLowBorder[0], &aUppBorder[0]))
      break;

    aStatus =
      DistanceMinimizeByExtrema(theASurf1, theASurf2->Value(aPnt(3), aPnt(4)), aPnt(1), aPnt(2));
    if (aStatus && !AdjustToDomain(2, &aPnt(1), &aLowBorder[0], &aUppBorder[0]))
      break;

    aStatus =
      DistanceMinimizeByExtrema(theASurf2, theASurf1->Value(aPnt(1), aPnt(2)), aPnt(3), aPnt(4));
    if (aStatus && !AdjustToDomain(2, &aPnt(3), &aLowBorder[2], &aUppBorder[2]))
      break;
  } while (!aStatus && (aNbIter > 0));

  bool aSingularStatus = HandleSingleSingularPoint(theASurf1, theASurf2, aTol, aSingularPnt);
  if (aSingularStatus)
    aPnt = aSingularPnt;

  if (!aStatus && !aSingularStatus)
  {
    return isOK;
  }

  gp_Pnt       aP1 = theASurf1->Value(aPnt(1), aPnt(2));
  gp_Pnt       aP2 = theASurf2->Value(aPnt(3), aPnt(4));
  const gp_Pnt aPInt(0.5 * (aP1.XYZ() + aP2.XYZ()));

  const double aSQDist = aPInt.SquareDistance(aP1);
  if (aSQDist > aTol * aTol)
  {
    return isOK;
  }

  IntSurf_PntOn2S anIP;
  anIP.SetValue(aPInt, aPnt(1), aPnt(2), aPnt(3), aPnt(4));

  if (isTheFirst)
  {
    while (line->NbPoints() > 1)
    {
      const int aNbPnts = line->NbPoints();

      int aPInd = 1;
      for (; aPInd <= aNbPnts; aPInd++)
      {
        aP1.SetXYZ(line->Value(aPInd).Value().XYZ());
        if (aP1.SquareDistance(aPInt) > Precision::SquareConfusion())
        {
          break;
        }
      }

      for (++aPInd; aPInd <= aNbPnts; aPInd++)
      {
        aP2.SetXYZ(line->Value(aPInd).Value().XYZ());
        if (aP1.SquareDistance(aP2) > Precision::SquareConfusion())
          break;
      }

      if (aPInd > aNbPnts)
      {
        return isOK;
      }

      const gp_XYZ aDir01(aP1.XYZ() - aPInt.XYZ());
      const gp_XYZ aDir12(aP2.XYZ() - aP1.XYZ());

      if (aDir01.Dot(aDir12) > 0.0)
      {
        break;
      }

      RemoveAPoint(1);
    }

    aP1.SetXYZ(line->Value(1).Value().XYZ());
    if (aP1.SquareDistance(aPInt) <= Precision::SquareConfusion())
    {
      RemoveAPoint(1);
    }

    line->InsertBefore(1, anIP);
    isOK = true;
  }
  else
  {
    while (line->NbPoints() > 1)
    {
      const int aNbPnts = line->NbPoints();

      gp_Pnt aPPrev, aPCurr;
      int    aPInd = aNbPnts;
      for (; aPInd > 0; aPInd--)
      {
        aPCurr.SetXYZ(line->Value(aPInd).Value().XYZ());
        if (aPCurr.SquareDistance(aPInt) > Precision::SquareConfusion())
        {
          break;
        }
      }

      for (--aPInd; aPInd > 0; aPInd--)
      {
        aPPrev.SetXYZ(line->Value(aPInd).Value().XYZ());
        if (aPCurr.SquareDistance(aPPrev) > Precision::SquareConfusion())
          break;
      }

      if (aPInd < 1)
      {
        return isOK;
      }

      const gp_XYZ aDirPC(aPCurr.XYZ() - aPPrev.XYZ());
      const gp_XYZ aDirCN(aPInt.XYZ() - aPCurr.XYZ());

      if (aDirPC.Dot(aDirCN) > 0.0)
      {
        break;
      }

      RemoveAPoint(aNbPnts);
    }

    int aNbPnts = line->NbPoints();
    aP1.SetXYZ(line->Value(aNbPnts).Value().XYZ());
    if (aP1.SquareDistance(aPInt) <= Precision::SquareConfusion())
    {
      RemoveAPoint(aNbPnts);
    }
    line->Add(anIP);

    isOK = true;
  }

  return isOK;
}

bool IntWalk_PWalking::PutToBoundary(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                     const occ::handle<Adaptor3d_Surface>& theASurf2)
{
  constexpr double aTolMin = Precision::Confusion();

  bool hasBeenAdded = false;

  const double aU1bFirst = theASurf1->FirstUParameter();
  const double aU1bLast  = theASurf1->LastUParameter();
  const double aU2bFirst = theASurf2->FirstUParameter();
  const double aU2bLast  = theASurf2->LastUParameter();
  const double aV1bFirst = theASurf1->FirstVParameter();
  const double aV1bLast  = theASurf1->LastVParameter();
  const double aV2bFirst = theASurf2->FirstVParameter();
  const double aV2bLast  = theASurf2->LastVParameter();

  double aTol = 1.0;
  aTol        = std::min(aTol, aU1bLast - aU1bFirst);
  aTol        = std::min(aTol, aU2bLast - aU2bFirst);
  aTol        = std::min(aTol, aV1bLast - aV1bFirst);
  aTol        = std::min(aTol, aV2bLast - aV2bFirst) * 1.0e-3;

  if (aTol <= 2.0 * aTolMin)
    return hasBeenAdded;

  bool isNeedAdding = false;
  bool isU1parallel = false, isV1parallel = false;
  bool isU2parallel = false, isV2parallel = false;
  IsParallel(line, true, aTol, isU1parallel, isV1parallel);
  IsParallel(line, false, aTol, isU2parallel, isV2parallel);

  double u1, v1, u2, v2;
  line->Value(1).Parameters(u1, v1, u2, v2);
  double aDelta = 0.0;

  if (!isV1parallel)
  {
    aDelta = u1 - aU1bFirst;
    if ((aTolMin < aDelta) && (aDelta < aTol))
    {
      u1           = aU1bFirst;
      isNeedAdding = true;
    }
    else
    {
      aDelta = aU1bLast - u1;
      if ((aTolMin < aDelta) && (aDelta < aTol))
      {
        u1           = aU1bLast;
        isNeedAdding = true;
      }
    }
  }

  if (!isV2parallel)
  {
    aDelta = u2 - aU2bFirst;
    if ((aTolMin < aDelta) && (aDelta < aTol))
    {
      u2           = aU2bFirst;
      isNeedAdding = true;
    }
    else
    {
      aDelta = aU2bLast - u2;
      if ((aTolMin < aDelta) && (aDelta < aTol))
      {
        u2           = aU2bLast;
        isNeedAdding = true;
      }
    }
  }

  if (!isU1parallel)
  {
    aDelta = v1 - aV1bFirst;
    if ((aTolMin < aDelta) && (aDelta < aTol))
    {
      v1           = aV1bFirst;
      isNeedAdding = true;
    }
    else
    {
      aDelta = aV1bLast - v1;
      if ((aTolMin < aDelta) && (aDelta < aTol))
      {
        v1           = aV1bLast;
        isNeedAdding = true;
      }
    }
  }

  if (!isU2parallel)
  {
    aDelta = v2 - aV2bFirst;
    if ((aTolMin < aDelta) && (aDelta < aTol))
    {
      v2           = aV2bFirst;
      isNeedAdding = true;
    }
    else
    {
      aDelta = aV2bLast - v2;
      if ((aTolMin < aDelta) && (aDelta < aTol))
      {
        v2           = aV2bLast;
        isNeedAdding = true;
      }
    }
  }

  if (isNeedAdding)
  {
    hasBeenAdded = SeekPointOnBoundary(theASurf1, theASurf2, u1, v1, u2, v2, true);
  }

  const int aNbPnts = line->NbPoints();
  isNeedAdding      = false;
  line->Value(aNbPnts).Parameters(u1, v1, u2, v2);

  if (!isV1parallel)
  {
    aDelta = u1 - aU1bFirst;
    if ((aTolMin < aDelta) && (aDelta < aTol))
    {
      u1           = aU1bFirst;
      isNeedAdding = true;
    }
    else
    {
      aDelta = aU1bLast - u1;
      if ((aTolMin < aDelta) && (aDelta < aTol))
      {
        u1           = aU1bLast;
        isNeedAdding = true;
      }
    }
  }

  if (!isV2parallel)
  {
    aDelta = u2 - aU2bFirst;
    if ((aTolMin < aDelta) && (aDelta < aTol))
    {
      u2           = aU2bFirst;
      isNeedAdding = true;
    }
    else
    {
      aDelta = aU2bLast - u2;
      if ((aTolMin < aDelta) && (aDelta < aTol))
      {
        u2           = aU2bLast;
        isNeedAdding = true;
      }
    }
  }

  if (!isU1parallel)
  {
    aDelta = v1 - aV1bFirst;
    if ((aTolMin < aDelta) && (aDelta < aTol))
    {
      v1           = aV1bFirst;
      isNeedAdding = true;
    }
    else
    {
      aDelta = aV1bLast - v1;
      if ((aTolMin < aDelta) && (aDelta < aTol))
      {
        v1           = aV1bLast;
        isNeedAdding = true;
      }
    }
  }

  if (!isU2parallel)
  {
    aDelta = v2 - aV2bFirst;
    if ((aTolMin < aDelta) && (aDelta < aTol))
    {
      v2           = aV2bFirst;
      isNeedAdding = true;
    }
    else
    {
      aDelta = aV2bLast - v2;
      if ((aTolMin < aDelta) && (aDelta < aTol))
      {
        v2           = aV2bLast;
        isNeedAdding = true;
      }
    }
  }

  if (isNeedAdding)
  {
    hasBeenAdded = SeekPointOnBoundary(theASurf1, theASurf2, u1, v1, u2, v2, false);
  }

  return hasBeenAdded;
}

bool IntWalk_PWalking::SeekAdditionalPoints(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                            const occ::handle<Adaptor3d_Surface>& theASurf2,
                                            const int                             theMinNbPoints)
{
  const double aTol      = 1.0e-14;
  int          aNbPoints = line->NbPoints();
  if (aNbPoints > theMinNbPoints)
    return true;

  const double aU1bFirst = theASurf1->FirstUParameter();
  const double aU1bLast  = theASurf1->LastUParameter();
  const double aU2bFirst = theASurf2->FirstUParameter();
  const double aU2bLast  = theASurf2->LastUParameter();
  const double aV1bFirst = theASurf1->FirstVParameter();
  const double aV1bLast  = theASurf1->LastVParameter();
  const double aV2bFirst = theASurf2->FirstVParameter();
  const double aV2bLast  = theASurf2->LastVParameter();

  bool isPrecise = false;

  NCollection_Array1<double> aPnt(1, 4);
  aPnt.Init(0.0);

  int aNbPointsPrev = 0;
  while (aNbPoints < theMinNbPoints && (aNbPoints != aNbPointsPrev))
  {
    aNbPointsPrev = aNbPoints;
    for (int fp = 1, lp = 2; fp < aNbPoints; fp = lp + 1)
    {
      double U1f, V1f, U2f, V2f;
      double U1l, V1l, U2l, V2l;

      lp = fp + 1;
      line->Value(fp).Parameters(U1f, V1f, U2f, V2f);
      line->Value(lp).Parameters(U1l, V1l, U2l, V2l);

      aPnt(1) = 0.5 * (U1f + U1l);
      if (aPnt(1) < aU1bFirst)
        aPnt(1) = aU1bFirst;
      if (aPnt(1) > aU1bLast)
        aPnt(1) = aU1bLast;

      aPnt(2) = 0.5 * (V1f + V1l);
      if (aPnt(2) < aV1bFirst)
        aPnt(2) = aV1bFirst;
      if (aPnt(2) > aV1bLast)
        aPnt(2) = aV1bLast;

      aPnt(3) = 0.5 * (U2f + U2l);
      if (aPnt(3) < aU2bFirst)
        aPnt(3) = aU2bFirst;
      if (aPnt(3) > aU2bLast)
        aPnt(3) = aU2bLast;

      aPnt(4) = 0.5 * (V2f + V2l);
      if (aPnt(4) < aV2bFirst)
        aPnt(4) = aV2bFirst;
      if (aPnt(4) > aV2bLast)
        aPnt(4) = aV2bLast;

      bool aStatus = false;
      int  aNbIter = 5;
      do
      {
        aStatus = DistanceMinimizeByGradient(theASurf1, theASurf2, aPnt);
        if (aStatus)
        {
          break;
        }

        aStatus = DistanceMinimizeByExtrema(theASurf1,
                                            theASurf2->Value(aPnt(3), aPnt(4)),
                                            aPnt(1),
                                            aPnt(2));
        if (aStatus)
        {
          break;
        }

        aStatus = DistanceMinimizeByExtrema(theASurf2,
                                            theASurf1->Value(aPnt(1), aPnt(2)),
                                            aPnt(3),
                                            aPnt(4));
        if (aStatus)
        {
          break;
        }
      } while (!aStatus && (--aNbIter > 0));

      if (aStatus)
      {
        gp_Pnt aP1 = theASurf1->Value(aPnt(1), aPnt(2)), aP2 = theASurf2->Value(aPnt(3), aPnt(4));
        gp_Pnt aPInt(0.5 * (aP1.XYZ() + aP2.XYZ()));

        const double aSQDist1 = aPInt.SquareDistance(aP1), aSQDist2 = aPInt.SquareDistance(aP2);

        if ((aSQDist1 < aTol) && (aSQDist2 < aTol))
        {
          IntSurf_PntOn2S anIP;
          anIP.SetValue(aPInt, aPnt(1), aPnt(2), aPnt(3), aPnt(4));
          line->InsertBefore(lp, anIP);

          isPrecise = true;

          if (++aNbPoints >= theMinNbPoints)
            break;
        }
        else
        {
          lp--;
        }
      }
    }
  }

  return isPrecise;
}

void IntWalk_PWalking::RepartirOuDiviser(bool&                      DejaReparti,
                                         IntImp_ConstIsoparametric& ChoixIso,
                                         bool&                      Arrive)

{

  if (Arrive)
  {
    if (!DejaReparti)
    {
      Arrive        = false;
      DejaReparti   = true;
      previousPoint = line->Value(1);
      previoustg    = false;
      previousd1    = firstd1;
      previousd2    = firstd2;
      previousd     = tgdir;
      myTangentIdx  = line->NbPoints();
      tgdir.Reverse();
      line->Reverse();

      sensCheminement = -1;
      tgfirst         = tglast;
      tglast          = false;
      ChoixIso        = choixIsoSav;
      double u1, v1, u2, v2;
      double U1, V1, U2, V2;
      int    nn = line->NbPoints();
      if (nn > 2)
      {
        line->Value(nn).Parameters(u1, v1, u2, v2);
        line->Value(nn - 1).Parameters(U1, V1, U2, V2);
        pasuv[0] = std::abs(u1 - U1);
        pasuv[1] = std::abs(v1 - V1);
        pasuv[2] = std::abs(u2 - U2);
        pasuv[3] = std::abs(v2 - V2);
      }
    }
  }
  else
  {
    if (pasuv[0] * 0.5 < ResoU1 && pasuv[1] * 0.5 < ResoV1 && pasuv[2] * 0.5 < ResoU2
        && pasuv[3] * 0.5 < ResoV2)
    {
      if (!previoustg)
      {
        tglast = true;
      }

      if (!DejaReparti)
      {
        DejaReparti   = true;
        previousPoint = line->Value(1);
        previoustg    = false;
        previousd1    = firstd1;
        previousd2    = firstd2;
        previousd     = tgdir;
        myTangentIdx  = line->NbPoints();
        tgdir.Reverse();
        line->Reverse();

        sensCheminement = -1;
        tgfirst         = tglast;
        tglast          = false;
        ChoixIso        = choixIsoSav;

        double u1, v1, u2, v2;
        double U1, V1, U2, V2;
        int    nn = line->NbPoints();
        if (nn > 2)
        {
          line->Value(nn).Parameters(u1, v1, u2, v2);
          line->Value(nn - 1).Parameters(U1, V1, U2, V2);
          pasuv[0] = std::abs(u1 - U1);
          pasuv[1] = std::abs(v1 - V1);
          pasuv[2] = std::abs(u2 - U2);
          pasuv[3] = std::abs(v2 - V2);
        }
      }
      else
        Arrive = true;
    }
    else
    {
      pasuv[0] *= 0.5;
      pasuv[1] *= 0.5;
      pasuv[2] *= 0.5;
      pasuv[3] *= 0.5;
    }
  }
}

namespace
{

  static const double CosRef2D = std::cos(M_PI / 9.0), AngRef2D = M_PI / 2.0;

  static const double d = 7.0;
} // namespace

IntWalk_StatusDeflection IntWalk_PWalking::TestDeflection(const IntImp_ConstIsoparametric choixIso,
                                                          const IntWalk_StatusDeflection  theStatus)

{
  if (line->NbPoints() == 1)
  {
    STATIC_BLOCAGE_SUR_PAS_TROP_GRAND = STATIC_PRECEDENT_INFLEXION = 0;
  }

  IntWalk_StatusDeflection aStatus = IntWalk_OK;
  double                   FlecheCourante, Ratio = 1.0;

  const occ::handle<Adaptor3d_Surface>& Caro1 = myIntersectionOn2S.Function().AuxillarSurface1();
  const occ::handle<Adaptor3d_Surface>& Caro2 = myIntersectionOn2S.Function().AuxillarSurface2();

  const IntSurf_PntOn2S& CurrentPoint = myIntersectionOn2S.Point();

  if (myIntersectionOn2S.IsTangent())
  {
    return IntWalk_ArretSurPoint;
  }

  const gp_Dir& TgCourante = myIntersectionOn2S.Direction();

  const double aCosBetweenTangent = TgCourante.Dot(previousd);

  if (aCosBetweenTangent < 0)
  {

    pasuv[0] *= 0.5;
    pasuv[1] *= 0.5;
    pasuv[2] *= 0.5;
    pasuv[3] *= 0.5;
    STATIC_PRECEDENT_INFLEXION += 3;
    if (pasuv[0] < ResoU1 && pasuv[1] < ResoV1 && pasuv[2] < ResoU2 && pasuv[3] < ResoV2)
      return IntWalk_ArretSurPointPrecedent;
    else
      return IntWalk_PasTropGrand;
  }
  else
  {
    if (STATIC_PRECEDENT_INFLEXION > 0)
    {
      STATIC_PRECEDENT_INFLEXION--;
      return IntWalk_OK;
    }
  }

  const double aSqDist = previousPoint.Value().SquareDistance(CurrentPoint.Value());

  if (aSqDist < Precision::SquareConfusion())
  {
    pasInit[0] = std::max(pasInit[0], 5.0 * ResoU1);
    pasInit[1] = std::max(pasInit[1], 5.0 * ResoV1);
    pasInit[2] = std::max(pasInit[2], 5.0 * ResoU2);
    pasInit[3] = std::max(pasInit[3], 5.0 * ResoV2);

    for (int i = 0; i < 4; i++)
    {
      pasuv[i] = std::max(pasuv[i], std::min(1.5 * pasuv[i], pasInit[i]));
    }

    if (std::abs(pasuv[choixIso] - pasInit[choixIso]) <= Precision::Confusion())
    {
      double CurU, CurV;
      if (choixIso == IntImp_UIsoparametricOnCaro1 || choixIso == IntImp_VIsoparametricOnCaro1)
        previousPoint.ParametersOnS1(CurU, CurV);
      else
        previousPoint.ParametersOnS2(CurU, CurV);
      gp_Pnt CurPnt =
        (choixIso == IntImp_UIsoparametricOnCaro1 || choixIso == IntImp_VIsoparametricOnCaro1)
          ? Adaptor3d_HSurfaceTool::Value(Caro1, CurU, CurV)
          : Adaptor3d_HSurfaceTool::Value(Caro2, CurU, CurV);
      gp_Pnt OffsetPnt;
      switch (choixIso)
      {
        case IntImp_UIsoparametricOnCaro1:
          OffsetPnt = Adaptor3d_HSurfaceTool::Value(Caro1, CurU + sensCheminement * pasuv[0], CurV);
          break;
        case IntImp_VIsoparametricOnCaro1:
          OffsetPnt = Adaptor3d_HSurfaceTool::Value(Caro1, CurU, CurV + sensCheminement * pasuv[1]);
          break;
        case IntImp_UIsoparametricOnCaro2:
          OffsetPnt = Adaptor3d_HSurfaceTool::Value(Caro2, CurU + sensCheminement * pasuv[2], CurV);
          break;
        case IntImp_VIsoparametricOnCaro2:
          OffsetPnt = Adaptor3d_HSurfaceTool::Value(Caro2, CurU, CurV + sensCheminement * pasuv[3]);
          break;
        default:
          break;
      }
      double RefDist    = CurPnt.Distance(OffsetPnt);
      double LocalResol = 0.;
      if (RefDist > gp::Resolution())
        LocalResol = pasuv[choixIso] * tolconf / RefDist;
      if (pasuv[choixIso] < 2 * LocalResol)
        pasuv[choixIso] = pasInit[choixIso] = 2 * LocalResol;
    }

    aStatus = IntWalk_PointConfondu;
  }

  double Up1, Vp1, Uc1, Vc1, Du1, Dv1, AbsDu1, AbsDu2, AbsDv1, AbsDv2;
  double Up2, Vp2, Uc2, Vc2, Du2, Dv2;

  previousPoint.Parameters(Up1, Vp1, Up2, Vp2);
  CurrentPoint.Parameters(Uc1, Vc1, Uc2, Vc2);

  Du1 = Uc1 - Up1;
  Dv1 = Vc1 - Vp1;
  Du2 = Uc2 - Up2;
  Dv2 = Vc2 - Vp2;

  AbsDu1 = std::abs(Du1);
  AbsDu2 = std::abs(Du2);
  AbsDv1 = std::abs(Dv1);
  AbsDv2 = std::abs(Dv2);

  if (AbsDu1 < ResoU1 && AbsDv1 < ResoV1 && AbsDu2 < ResoU2 && AbsDv2 < ResoV2)
  {
    pasuv[0] = ResoU1;
    pasuv[1] = ResoV1;
    pasuv[2] = ResoU2;
    pasuv[3] = ResoV2;
    return (IntWalk_ArretSurPointPrecedent);
  }

  double tolArea = 100.0;
  if (ResoU1 < Precision::PConfusion() || ResoV1 < Precision::PConfusion()
      || ResoU2 < Precision::PConfusion() || ResoV2 < Precision::PConfusion())
    tolArea = tolArea * 2.0;

  double Cosi1, CosRef1, Ang1, AngRef1, ResoUV1, Duv1, d1, tolCoeff1;
  double Cosi2, CosRef2, Ang2, AngRef2, ResoUV2, Duv2, d2, tolCoeff2;
  Cosi1   = Du1 * previousd1.X() + Dv1 * previousd1.Y();
  Cosi2   = Du2 * previousd2.X() + Dv2 * previousd2.Y();
  Duv1    = Du1 * Du1 + Dv1 * Dv1;
  Duv2    = Du2 * Du2 + Dv2 * Dv2;
  ResoUV1 = ResoU1 * ResoU1 + ResoV1 * ResoV1;
  ResoUV2 = ResoU2 * ResoU2 + ResoV2 * ResoV2;

  double aMinDiv2 = Precision::Confusion();
  aMinDiv2        = aMinDiv2 * aMinDiv2;

  d1 = d;
  if (Duv1 > aMinDiv2)
  {
    d1 = std::abs(ResoUV1 / Duv1);
    d1 = std::min(std::sqrt(d1) * tolArea, d);
  }
  tolCoeff1 = std::exp(d1);

  d2 = d;
  if (Duv2 > aMinDiv2)
  {
    d2 = std::abs(ResoUV2 / Duv2);
    d2 = std::min(std::sqrt(d2) * tolArea, d);
  }
  tolCoeff2 = std::exp(d2);
  CosRef1   = CosRef2D / tolCoeff1;
  CosRef2   = CosRef2D / tolCoeff2;

  if (aStatus != IntWalk_PointConfondu)
  {
    if (Cosi1 * Cosi1 < CosRef1 * Duv1 || Cosi2 * Cosi2 < CosRef2 * Duv2)
    {
      pasuv[0] *= 0.5;
      pasuv[1] *= 0.5;
      pasuv[2] *= 0.5;
      pasuv[3] *= 0.5;
      if (pasuv[0] < ResoU1 && pasuv[1] < ResoV1 && pasuv[2] < ResoU2 && pasuv[3] < ResoV2)
      {
        return (IntWalk_ArretSurPointPrecedent);
      }
      else
      {
        pasuv[0] *= 0.5;
        pasuv[1] *= 0.5;
        pasuv[2] *= 0.5;
        pasuv[3] *= 0.5;
        return (IntWalk_PasTropGrand);
      }
    }
    const gp_Dir2d& Tg2dcourante1 = myIntersectionOn2S.DirectionOnS1();
    const gp_Dir2d& Tg2dcourante2 = myIntersectionOn2S.DirectionOnS2();
    Cosi1                         = Du1 * Tg2dcourante1.X() + Dv1 * Tg2dcourante1.Y();
    Cosi2                         = Du2 * Tg2dcourante2.X() + Dv2 * Tg2dcourante2.Y();
    Ang1                          = std::abs(previousd1.Angle(Tg2dcourante1));
    Ang2                          = std::abs(previousd2.Angle(Tg2dcourante2));
    AngRef1                       = AngRef2D * tolCoeff1;
    AngRef2                       = AngRef2D * tolCoeff2;

    if (Cosi1 * Cosi1 < CosRef1 * Duv1 || Cosi2 * Cosi2 < CosRef2 * Duv2 || Ang1 > AngRef1
        || Ang2 > AngRef2)
    {
      pasuv[0] *= 0.5;
      pasuv[1] *= 0.5;
      pasuv[2] *= 0.5;
      pasuv[3] *= 0.5;
      if (pasuv[0] < ResoU1 && pasuv[1] < ResoV1 && pasuv[2] < ResoU2 && pasuv[3] < ResoV2)
        return (IntWalk_ArretSurPoint);
      else
        return (IntWalk_PasTropGrand);
    }
  }

  FlecheCourante =
    std::sqrt(std::abs((previousd.XYZ() - TgCourante.XYZ()).SquareModulus() * aSqDist)) / 8.;

  if (FlecheCourante <= fleche * 0.5)
  {
    if (FlecheCourante > 1e-16)
    {
      Ratio = 0.5 * (fleche / FlecheCourante);
    }
    else
    {
      Ratio = 10.0;
    }
    double pasSu1 = pasuv[0];
    double pasSv1 = pasuv[1];
    double pasSu2 = pasuv[2];
    double pasSv2 = pasuv[3];

    if (pasuv[0] < AbsDu1)
      pasuv[0] = AbsDu1;
    if (pasuv[1] < AbsDv1)
      pasuv[1] = AbsDv1;
    if (pasuv[2] < AbsDu2)
      pasuv[2] = AbsDu2;
    if (pasuv[3] < AbsDv2)
      pasuv[3] = AbsDv2;

    if (pasuv[0] < ResoU1)
      pasuv[0] = ResoU1;
    if (pasuv[1] < ResoV1)
      pasuv[1] = ResoV1;
    if (pasuv[2] < ResoU2)
      pasuv[2] = ResoU2;
    if (pasuv[3] < ResoV2)
      pasuv[3] = ResoV2;

    double R1, R = pasInit[0] / pasuv[0];
    R1 = pasInit[1] / pasuv[1];
    if (R1 < R)
      R = R1;
    R1 = pasInit[2] / pasuv[2];
    if (R1 < R)
      R = R1;
    R1 = pasInit[3] / pasuv[3];
    if (R1 < R)
      R = R1;
    if (Ratio > R)
      Ratio = R;
    pasuv[0] = std::min(Ratio * pasuv[0], pasInit[0]);
    pasuv[1] = std::min(Ratio * pasuv[1], pasInit[1]);
    pasuv[2] = std::min(Ratio * pasuv[2], pasInit[2]);
    pasuv[3] = std::min(Ratio * pasuv[3], pasInit[3]);
    if (pasuv[0] != pasSu1 || pasuv[2] != pasSu2 || pasuv[1] != pasSv1 || pasuv[3] != pasSv2)
    {
      if (++STATIC_BLOCAGE_SUR_PAS_TROP_GRAND > 5)
      {
        STATIC_BLOCAGE_SUR_PAS_TROP_GRAND = 0;
        return IntWalk_PasTropGrand;
      }
    }
    if (aStatus == IntWalk_OK)
    {
      STATIC_BLOCAGE_SUR_PAS_TROP_GRAND = 0;
    }
    return aStatus;
  }
  else
  {
    if (FlecheCourante > fleche)
    {
      Ratio    = fleche / FlecheCourante;
      pasuv[0] = Ratio * pasuv[0];
      pasuv[1] = Ratio * pasuv[1];
      pasuv[2] = Ratio * pasuv[2];
      pasuv[3] = Ratio * pasuv[3];

      return IntWalk_PasTropGrand;
    }
    else
    {
      Ratio = 0.75 * (fleche / FlecheCourante);
    }
  }

  if (aStatus != IntWalk_PointConfondu)
  {

    const double anInvSqAbsArcDeflMax = 0.25 * aSqDist / (tolconf * tolconf);
    const double aSinB2Max            = 1.0 - 2.0 / (1.0 + anInvSqAbsArcDeflMax);

    if (aSinB2Max >= 0.0 && (aCosBetweenTangent <= 2.0 * aSinB2Max * aSinB2Max - 1.0))
    {
      aStatus = IntWalk_PasTropGrand;
    }
    else
    {
      const double anInvSqAbsArcDeflMin = 4.0 * anInvSqAbsArcDeflMax;
      const double aSinB2Min            = 1.0 - 2.0 / (1.0 + anInvSqAbsArcDeflMin);

      if (theStatus != IntWalk_PasTropGrand
          && ((aSinB2Min < 0.0) || (aCosBetweenTangent >= 2.0 * aSinB2Min * aSinB2Min - 1.0)))
      {
        aStatus = IntWalk_StepTooSmall;
      }
    }

    if (aStatus == IntWalk_PasTropGrand)
    {
      pasuv[0] *= 0.5;
      pasuv[1] *= 0.5;
      pasuv[2] *= 0.5;
      pasuv[3] *= 0.5;
      return aStatus;
    }

    if (aStatus == IntWalk_StepTooSmall)
    {
      pasuv[0] = std::max(pasuv[0], AbsDu1);
      pasuv[1] = std::max(pasuv[1], AbsDv1);
      pasuv[2] = std::max(pasuv[2], AbsDu2);
      pasuv[3] = std::max(pasuv[3], AbsDv2);

      pasInit[0] = std::max(pasInit[0], AbsDu1);
      pasInit[1] = std::max(pasInit[1], AbsDv1);
      pasInit[2] = std::max(pasInit[2], AbsDu2);
      pasInit[3] = std::max(pasInit[3], AbsDv2);

      return aStatus;
    }
  }

  pasuv[0] = std::max(myStepMin[0], std::min(std::min(Ratio * AbsDu1, pasuv[0]), pasInit[0]));
  pasuv[1] = std::max(myStepMin[1], std::min(std::min(Ratio * AbsDv1, pasuv[1]), pasInit[1]));
  pasuv[2] = std::max(myStepMin[2], std::min(std::min(Ratio * AbsDu2, pasuv[2]), pasInit[2]));
  pasuv[3] = std::max(myStepMin[3], std::min(std::min(Ratio * AbsDv2, pasuv[3]), pasInit[3]));

  if (aStatus == IntWalk_OK)
    STATIC_BLOCAGE_SUR_PAS_TROP_GRAND = 0;
  return aStatus;
}

bool IntWalk_PWalking::TestArret(const bool                  DejaReparti,
                                 NCollection_Array1<double>& Param,
                                 IntImp_ConstIsoparametric&  ChoixIso)

{
  double Uvd[4], Uvf[4], Epsuv[4], Duv[4], Uvp[4], dv, dv2, ParC[4];
  double DPc, DPb;
  int    i = 0, k = 0;
  Epsuv[0] = ResoU1;
  Epsuv[1] = ResoV1;
  Epsuv[2] = ResoU2;
  Epsuv[3] = ResoV2;
  previousPoint.Parameters(Uvp[0], Uvp[1], Uvp[2], Uvp[3]);

  double SolParam[4];
  myIntersectionOn2S.Point().Parameters(SolParam[0], SolParam[1], SolParam[2], SolParam[3]);

  bool Trouve = false;

  Uvd[0] = Um1;
  Uvf[0] = UM1;
  Uvd[1] = Vm1;
  Uvf[1] = VM1;
  Uvd[2] = Um2;
  Uvf[2] = UM2;
  Uvd[3] = Vm2;
  Uvf[3] = VM2;

  int im1;
  for (i = 1, im1 = 0; i <= 4; i++, im1++)
  {
    switch (i)
    {
      case 1:
        k = 2;
        break;
      case 2:
        k = 1;
        break;
      case 3:
        k = 4;
        break;
      case 4:
        k = 3;
        break;
    }
    if (Param(i) < (Uvd[im1] - Epsuv[im1]) || SolParam[im1] < (Uvd[im1] - Epsuv[im1]))
    {
      Trouve    = true;
      DPc       = Uvp[im1] - Param(i);
      DPb       = Uvp[im1] - Uvd[im1];
      ParC[im1] = Uvd[im1];
      dv        = Param(k) - Uvp[k - 1];
      dv2       = dv * dv;
      if (dv2 > RealEpsilon())
      {
        Duv[im1] = DPc * DPb + dv2;
        Duv[im1] = Duv[im1] * Duv[im1] / (DPc * DPc + dv2) / (DPb * DPb + dv2);
      }
      else
      {
        Duv[im1] = -1.0;
      }
    }
    else if (Param(i) > (Uvf[im1] + Epsuv[im1]) || SolParam[im1] > (Uvf[im1] + Epsuv[im1]))
    {
      Trouve    = true;
      DPc       = Param(i) - Uvp[im1];
      DPb       = Uvf[im1] - Uvp[im1];
      ParC[im1] = Uvf[im1];

      dv = Param(k) - Uvp[k - 1];

      dv2 = dv * dv;
      if (dv2 > RealEpsilon())
      {
        Duv[im1] = DPc * DPb + dv2;
        Duv[im1] = Duv[im1] * Duv[im1] / (DPc * DPc + dv2) / (DPb * DPb + dv2);
      }
      else
      {
        Duv[im1] = -1.0;
      }
    }
    else
    {
      Duv[im1]  = -1.;
      ParC[im1] = Param(i);
    }
  }

  if (Trouve)
  {

    double ddv = -1.0;
    k          = -1;
    for (i = 0; i <= 3; i++)
    {
      Param(i + 1) = ParC[i];
      if (Duv[i] > ddv)
      {
        ddv = Duv[i];
        k   = i;
      }
    }
    if (k != -1)
    {
      ChoixIso = ChoixRef(k);
    }
    else
    {
      if ((ParC[0] <= Uvd[0] + Epsuv[0]) || (ParC[0] >= Uvf[0] - Epsuv[0]))
      {
        ChoixIso = IntImp_UIsoparametricOnCaro1;
      }
      else if ((ParC[1] <= Uvd[1] + Epsuv[1]) || (ParC[1] >= Uvf[1] - Epsuv[1]))
      {
        ChoixIso = IntImp_VIsoparametricOnCaro1;
      }
      else if ((ParC[2] <= Uvd[2] + Epsuv[2]) || (ParC[2] >= Uvf[2] - Epsuv[2]))
      {
        ChoixIso = IntImp_UIsoparametricOnCaro2;
      }
      else if ((ParC[3] <= Uvd[3] + Epsuv[3]) || (ParC[3] >= Uvf[3] - Epsuv[3]))
      {
        ChoixIso = IntImp_VIsoparametricOnCaro2;
      }
    }
    close = false;
    return true;
  }
  else
  {
    if (!DejaReparti)
    {

      double                 u, v;
      const IntSurf_PntOn2S& POn2S1 = line->Value(1);

      POn2S1.ParametersOnS1(u, v);
      gp_Pnt2d P1uvS1(u, v);
      previousPoint.ParametersOnS1(u, v);
      gp_Pnt2d PrevuvS1(u, v);
      myIntersectionOn2S.Point().ParametersOnS1(u, v);
      gp_Pnt2d myIntersuvS1(u, v);
      bool     close2dS1 = (P1uvS1.XY() - PrevuvS1.XY()) * (P1uvS1.XY() - myIntersuvS1.XY()) < 0.0;

      POn2S1.ParametersOnS2(u, v);
      gp_Pnt2d P1uvS2(u, v);
      previousPoint.ParametersOnS2(u, v);
      gp_Pnt2d PrevuvS2(u, v);
      myIntersectionOn2S.Point().ParametersOnS2(u, v);
      gp_Pnt2d myIntersuvS2(u, v);
      bool     close2dS2 = (P1uvS2.XY() - PrevuvS2.XY()) * (P1uvS2.XY() - myIntersuvS2.XY()) < 0.0;

      close = close2dS1 && close2dS2;
      return close;
    }
    else
      return false;
  }
}
