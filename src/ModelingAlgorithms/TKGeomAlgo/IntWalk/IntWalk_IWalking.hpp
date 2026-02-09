#include <Bnd_Range.hpp>
#include <IntWalk_StatusDeflection.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_LocalArray.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <math_FunctionSetRoot.hpp>

#ifdef CHRONO
  #include <OSD_Chronometer.hpp>
OSD_Chronometer Chronrsnld;
#endif

static bool IsTangentExtCheck(TheIWFunction& theFunc,
                              const double   theU,
                              const double   theV,
                              const double   theStepU,
                              const double   theStepV,
                              const double   theUinf,
                              const double   theUsup,
                              const double   theVinf,
                              const double   theVsup)
{
  const double aTol            = theFunc.Tolerance();
  const int    aNbItems        = 4;
  const double aParU[aNbItems] = {std::min(theU + theStepU, theUsup),
                                  std::max(theU - theStepU, theUinf),
                                  theU,
                                  theU};
  const double aParV[aNbItems] = {theV,
                                  theV,
                                  std::min(theV + theStepV, theVsup),
                                  std::max(theV - theStepV, theVinf)};

  math_Vector aX(1, 2), aVal(1, 1);

  for (int i = 0; i < aNbItems; i++)
  {
    aX.Value(1) = aParU[i];
    aX.Value(2) = aParV[i];

    if (!theFunc.Value(aX, aVal))
      continue;

    if (std::abs(theFunc.Root()) > aTol)
      return false;
  }

  return true;
}

IntWalk_IWalking::IntWalk_IWalking(const double Epsilon,
                                   const double Deflection,
                                   const double Increment,
                                   const bool   theToFillHoles)
    : done(false),
      fleche(Deflection),
      pas(Increment),
      tolerance(1, 2),
      epsilon(Epsilon * Epsilon),
      reversed(false),
      wd1(IntWalk_VectorOfWalkingData::allocator_type(new NCollection_IncAllocator)),
      wd2(wd1.get_allocator()),
      nbMultiplicities(wd1.get_allocator()),
      Um(0.0),
      UM(0.0),
      Vm(0.0),
      VM(0.0),
      ToFillHoles(theToFillHoles)
{
}

void IntWalk_IWalking::Clear()
{
  wd1.clear();
  wd2.clear();
  IntWalk_WalkingData aDummy;
  aDummy.etat   = -10;
  aDummy.ustart = aDummy.vstart = 0.;
  wd1.push_back(aDummy);
  wd2.push_back(aDummy);
  nbMultiplicities.clear();
  nbMultiplicities.push_back(-1);

  done = false;
  seqAjout.Clear();
  lines.Clear();
}

void IntWalk_IWalking::Perform(const ThePOPIterator& Pnts1,
                               const ThePOLIterator& Pnts2,
                               TheIWFunction&        Func,
                               const ThePSurface&    Caro,
                               const bool            Reversed)

{
  int    I;
  bool   Rajout  = false;
  int    nbPnts1 = Pnts1.Length();
  int    nbPnts2 = Pnts2.Length();
  double U, V;

  Clear();
  reversed = Reversed;

  Um = ThePSurfaceTool::FirstUParameter(Caro);
  Vm = ThePSurfaceTool::FirstVParameter(Caro);
  UM = ThePSurfaceTool::LastUParameter(Caro);
  VM = ThePSurfaceTool::LastVParameter(Caro);

  if (UM < Um)
  {
    double utemp = UM;
    UM           = Um;
    Um           = utemp;
  }
  if (VM < Vm)
  {
    double vtemp = VM;
    VM           = Vm;
    Vm           = vtemp;
  }

  const double aStepU = pas * (UM - Um), aStepV = pas * (VM - Vm);

  NCollection_Sequence<double> Umult;
  NCollection_Sequence<double> Vmult;

  int decal = 0;
  wd1.reserve(nbPnts1 + decal);
  nbMultiplicities.reserve(nbPnts1 + decal);
  for (I = 1; I <= nbPnts1 + decal; I++)
  {
    const ThePointOfPath& PathPnt = Pnts1.Value(I - decal);
    IntWalk_WalkingData   aWD1;
    aWD1.etat = 1;
    if (!ThePointOfPathTool::IsPassingPnt(PathPnt))
      aWD1.etat = 11;
    if (!ThePointOfPathTool::IsTangent(PathPnt))
      ++aWD1.etat;

    if (aWD1.etat == 2)
    {
      aWD1.etat = 11;
    }

    ThePointOfPathTool::Value2d(PathPnt, aWD1.ustart, aWD1.vstart);
    mySRangeU.Add(aWD1.ustart);
    mySRangeV.Add(aWD1.vstart);

    wd1.push_back(aWD1);
    int aNbMult = ThePointOfPathTool::Multiplicity(PathPnt);
    nbMultiplicities.push_back(aNbMult);

    for (int J = 1; J <= aNbMult; J++)
    {
      ThePointOfPathTool::Parameters(PathPnt, J, U, V);
      Umult.Append(U);
      Vmult.Append(V);
    }
  }

  wd2.reserve(nbPnts2);
  for (I = 1; I <= nbPnts2; I++)
  {
    IntWalk_WalkingData aWD2;
    aWD2.etat                         = 1;
    const IntSurf_InteriorPoint& anIP = Pnts2.Value(I);
    ThePointOfLoopTool::Value2d(anIP, aWD2.ustart, aWD2.vstart);
    mySRangeU.Add(aWD2.ustart);
    mySRangeV.Add(aWD2.vstart);

    if (!IsTangentExtCheck(Func, aWD2.ustart, aWD2.vstart, aStepU, aStepV, Um, UM, Vm, VM))
      aWD2.etat = 13;

    wd2.push_back(aWD2);
  }

  tolerance(1) = ThePSurfaceTool::UResolution(Caro, Precision::Confusion());
  tolerance(2) = ThePSurfaceTool::VResolution(Caro, Precision::Confusion());

  Func.Set(Caro);

  if (mySRangeU.Delta() > std::max(tolerance(1), Precision::PConfusion()))
  {
    mySRangeU.Enlarge(mySRangeU.Delta());
    mySRangeU.Common(Bnd_Range(Um, UM));
  }
  else
  {
    mySRangeU = Bnd_Range(Um, UM);
  }

  if (mySRangeV.Delta() > std::max(tolerance(2), Precision::PConfusion()))
  {
    mySRangeV.Enlarge(mySRangeV.Delta());
    mySRangeV.Common(Bnd_Range(Vm, VM));
  }
  else
  {
    mySRangeV = Bnd_Range(Vm, VM);
  }

  if (nbPnts1 != 0)
    ComputeOpenLine(Umult, Vmult, Pnts1, Func, Rajout);

  if (nbPnts2 != 0)
    ComputeCloseLine(Umult, Vmult, Pnts1, Pnts2, Func, Rajout);

  if (ToFillHoles)
  {
    int MaxNbIter = 10, nb_iter = 0;
    while (seqAlone.Length() > 1 && nb_iter < MaxNbIter)
    {
      nb_iter++;
      NCollection_Sequence<IntSurf_InteriorPoint> PntsInHoles;
      NCollection_Sequence<int>                   CopySeqAlone = seqAlone;
      FillPntsInHoles(Func, CopySeqAlone, PntsInHoles);
      wd2.clear();
      IntWalk_WalkingData aDummy;
      aDummy.etat   = -10;
      aDummy.ustart = aDummy.vstart = 0.;
      wd2.push_back(aDummy);
      int nbHoles = PntsInHoles.Length();
      wd2.reserve(nbHoles);
      for (I = 1; I <= nbHoles; I++)
      {
        IntWalk_WalkingData aWD2;
        aWD2.etat                         = 13;
        const IntSurf_InteriorPoint& anIP = PntsInHoles.Value(I);
        ThePointOfLoopTool::Value2d(anIP, aWD2.ustart, aWD2.vstart);
        wd2.push_back(aWD2);
      }
      ComputeCloseLine(Umult, Vmult, Pnts1, PntsInHoles, Func, Rajout);
    }
  }

  for (I = 1; I <= nbPnts1; I++)
  {
    if (wd1[I].etat > 0)
      seqSingle.Append(Pnts1(I));
  }
  done = true;
}

void IntWalk_IWalking::Perform(const ThePOPIterator& Pnts1,
                               TheIWFunction&        Func,
                               const ThePSurface&    Caro,
                               const bool            Reversed)

{
  int    I;
  bool   Rajout  = false;
  int    nbPnts1 = Pnts1.Length();
  double U, V;

  reversed = Reversed;

  NCollection_Sequence<double> Umult;
  NCollection_Sequence<double> Vmult;

  wd1.reserve(nbPnts1);
  for (I = 1; I <= nbPnts1; I++)
  {
    const ThePointOfPath& PathPnt = Pnts1.Value(I);
    IntWalk_WalkingData   aWD1;
    aWD1.etat = 1;
    if (!ThePointOfPathTool::IsPassingPnt(PathPnt))
      aWD1.etat = 11;
    if (!ThePointOfPathTool::IsTangent(PathPnt))
      ++aWD1.etat;
    ThePointOfPathTool::Value2d(PathPnt, aWD1.ustart, aWD1.vstart);
    wd1.push_back(aWD1);
    int aNbMult = ThePointOfPathTool::Multiplicity(PathPnt);
    nbMultiplicities.push_back(aNbMult);

    for (int J = 1; J <= aNbMult; J++)
    {
      ThePointOfPathTool::Parameters(PathPnt, J, U, V);
      Umult.Append(U);
      Vmult.Append(V);
    }
  }

  tolerance(1) = ThePSurfaceTool::UResolution(Caro, Precision::Confusion());
  tolerance(2) = ThePSurfaceTool::VResolution(Caro, Precision::Confusion());

  Um = ThePSurfaceTool::FirstUParameter(Caro);
  Vm = ThePSurfaceTool::FirstVParameter(Caro);
  UM = ThePSurfaceTool::LastUParameter(Caro);
  VM = ThePSurfaceTool::LastVParameter(Caro);

  if (UM < Um)
  {
    double utemp = UM;
    UM           = Um;
    Um           = utemp;
  }
  if (VM < Vm)
  {
    double vtemp = VM;
    VM           = Vm;
    Vm           = vtemp;
  }

  Func.Set(Caro);

  if (nbPnts1 != 0)
    ComputeOpenLine(Umult, Vmult, Pnts1, Func, Rajout);

  for (I = 1; I <= nbPnts1; I++)
  {
    if (wd1[I].etat > 0)
      seqSingle.Append(Pnts1(I));
  }
  done = true;
}

#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

static void CutVectorByTolerances(gp_Vec2d& theVector, const math_Vector& theTolerance)
{
  if (std::abs(theVector.X()) < theTolerance(1))
    theVector.SetX(0.);
  if (std::abs(theVector.Y()) < theTolerance(2))
    theVector.SetY(0.);
}

bool IntWalk_IWalking::Cadrage(math_Vector& BornInf,
                               math_Vector& BornSup,
                               math_Vector& UVap,
                               double&      Step,

                               const int StepSign) const

{
  double Duvx = previousd2d.X();
  double Duvy = previousd2d.Y();

  if (!reversed)
  {
    previousPoint.ParametersOnS2(UVap(1), UVap(2));
  }
  else
  {
    previousPoint.ParametersOnS1(UVap(1), UVap(2));
  }

  double U1 = UVap(1) + Step * Duvx * StepSign;
  double V1 = UVap(2) + Step * Duvy * StepSign;

  bool infu = (U1 <= BornInf(1) + Precision::PConfusion());
  bool supu = (U1 >= BornSup(1) - Precision::PConfusion());
  bool infv = (V1 <= BornInf(2) + Precision::PConfusion());
  bool supv = (V1 >= BornSup(2) - Precision::PConfusion());

  double theStepU, theStepV;

  if (!infu && !supu && !infv && !supv)
  {
    UVap(1) = U1;
    UVap(2) = V1;
    return false;
  }

  if ((infu || supu) && (infv || supv))
  {
    if (infu)
    {
      if (Duvx)
      {
        theStepU = std::abs((BornInf(1) - UVap(1)) / Duvx);
      }
      else
      {
        theStepU = Step;
      }
    }
    else
    {
      if (Duvx)
      {
        theStepU = std::abs((BornSup(1) - UVap(1)) / Duvx);
      }
      else
      {
        theStepU = Step;
      }
    }
    if (infv)
    {
      if (Duvy)
      {
        theStepV = std::abs((BornInf(2) - UVap(2)) / Duvy);
      }
      else
      {
        theStepV = Step;
      }
    }
    else
    {
      if (Duvy)
      {
        theStepV = std::abs((BornSup(2) - UVap(2)) / Duvy);
      }
      else
      {
        theStepV = Step;
      }
    }

    if (theStepU <= theStepV)
    {
      Step = theStepU;
      if (infu)
      {
        UVap(1)    = BornInf(1);
        BornSup(1) = BornInf(1);
      }
      else
      {
        UVap(1)    = BornSup(1);
        BornInf(1) = BornSup(1);
      }
      UVap(2) += Step * Duvy * StepSign;
    }
    else
    {
      Step = theStepV;
      if (infv)
      {
        UVap(2)    = BornInf(2);
        BornSup(2) = BornInf(2);
      }
      else
      {
        UVap(2)    = BornSup(2);
        BornInf(2) = BornSup(2);
      }
      UVap(1) += Step * Duvx * StepSign;
    }
    return true;
  }

  else if (infu)
  {
    if (Duvx)
    {
      double aStep = std::abs((BornInf(1) - UVap(1)) / Duvx);
      if (aStep < Step)
        Step = aStep;
    }
    BornSup(1) = BornInf(1);
    UVap(1)    = BornInf(1);
    UVap(2) += Step * Duvy * StepSign;
    return true;
  }
  else if (supu)
  {
    if (Duvx)
    {
      double aStep = std::abs((BornSup(1) - UVap(1)) / Duvx);
      if (aStep < Step)
        Step = aStep;
    }
    BornInf(1) = BornSup(1);
    UVap(1)    = BornSup(1);
    UVap(2) += Step * Duvy * StepSign;
    return true;
  }
  else if (infv)
  {
    if (Duvy)
    {
      double aStep = std::abs((BornInf(2) - UVap(2)) / Duvy);
      if (aStep < Step)
        Step = aStep;
    }
    BornSup(2) = BornInf(2);
    UVap(1) += Step * Duvx * StepSign;
    UVap(2) = BornInf(2);
    return true;
  }
  else if (supv)
  {
    if (Duvy)
    {
      double aStep = std::abs((BornSup(2) - UVap(2)) / Duvy);
      if (aStep < Step)
        Step = aStep;
    }
    BornInf(2) = BornSup(2);
    UVap(1) += Step * Duvx * StepSign;
    UVap(2) = BornSup(2);
    return true;
  }
  return true;
}

bool IntWalk_IWalking::TestArretPassage(const NCollection_Sequence<double>& Umult,
                                        const NCollection_Sequence<double>& Vmult,
                                        TheIWFunction&                      sp,
                                        math_Vector&                        UV,
                                        int&                                Irang)

{
  double Up, Vp, Du, Dv, Dup, Dvp, Utest, Vtest;
  int    j, N, ind;
  double tolu  = tolerance(1);
  double tolv  = tolerance(2);
  double tolu2 = 10. * tolerance(1);
  double tolv2 = 10. * tolerance(2);

  bool Arrive = false;

  if (!reversed)
  {
    previousPoint.ParametersOnS2(Up, Vp);
  }
  else
  {
    previousPoint.ParametersOnS1(Up, Vp);
  }

  for (size_t i = 1; i < wd2.size(); i++)
  {
    if (wd2[i].etat > 0)
    {

      Utest = wd2[i].ustart;
      Vtest = wd2[i].vstart;

      Du  = UV(1) - Utest;
      Dv  = UV(2) - Vtest;
      Dup = Up - Utest;
      Dvp = Vp - Vtest;

      if ((std::abs(Du) < tolu2 && std::abs(Dv) < tolv2)
          || (std::abs(Dup) < tolu2 && std::abs(Dvp) < tolv2))
      {
        wd2[i].etat = -wd2[i].etat;
      }
      else
      {
        double DDu = (UV(1) - Up);
        double DDv = (UV(2) - Vp);
        double DDD = DDu * DDu + DDv * DDv;
        double DD1 = Du * Du + Dv * Dv;
        if (DD1 <= DDD)
        {
          double DD2 = Dup * Dup + Dvp * Dvp;
          if (DD2 <= DDD && ((Du * Dup) + (Dv * Dvp * tolu / tolv) <= 0.))
          {
            wd2[i].etat = -wd2[i].etat;
          }
        }
      }
    }
  }

  int l;

  NCollection_Sequence<int>    i_candidates;
  NCollection_Sequence<double> SqDist_candidates;

  for (l = 1; l <= 2 && !Arrive; l++)
  {
    bool isToCheck;

    for (size_t i = 1; i < wd1.size(); i++)
    {
      if (l == 1)
        isToCheck = (wd1[i].etat > 0);
      else
        isToCheck = (wd1[i].etat < 0);

      if (isToCheck)
      {

        Utest = wd1[i].ustart;
        Vtest = wd1[i].vstart;
        Dup   = Up - Utest;
        Dvp   = Vp - Vtest;
        if (std::abs(Dup) >= tolu || std::abs(Dvp) >= tolv)
        {
          double UV1mUtest = UV(1) - Utest;
          double UV2mVtest = UV(2) - Vtest;
          if (((Dup * UV1mUtest + Dvp * UV2mVtest) < 0)
              || (std::abs(UV1mUtest) < tolu && std::abs(UV2mVtest) < tolv))
          {
            i_candidates.Append((int)i);
            SqDist_candidates.Append(Dup * Dup + Dvp * Dvp);
          }
          else if (nbMultiplicities[i] > 0 && i_candidates.IsEmpty())
          {
            N = 0;
            for (size_t k = 1; k < i; k++)
            {
              N += nbMultiplicities[k];
            }
            for (j = N + 1; j <= N + nbMultiplicities[i]; j++)
            {
              if (((Up - Umult(j)) * (UV(1) - Umult(j)) + (Vp - Vmult(j)) * (UV(2) - Vmult(j)) < 0)
                  || (std::abs(UV(1) - Umult(j)) < tolu && std::abs(UV(2) - Vmult(j)) < tolv))
              {
                Irang  = (int)i;
                Arrive = true;
                UV(1)  = Utest;
                UV(2)  = Vtest;
                break;
              }
            }
          }
          if (Arrive)
          {
            double      abidF[1], abidD[1][2];
            math_Vector bidF(abidF, 1, 1);
            math_Matrix bidD(abidD, 1, 1, 1, 2);
            sp.Values(UV, bidF, bidD);
            break;
          }
        }
      }
    }
    if (!i_candidates.IsEmpty())
    {
      double MinSqDist = RealLast();
      for (ind = 1; ind <= i_candidates.Length(); ind++)
        if (SqDist_candidates(ind) < MinSqDist)
        {
          MinSqDist = SqDist_candidates(ind);
          Irang     = i_candidates(ind);
        }
      Arrive = true;
      UV(1)  = wd1[Irang].ustart;
      UV(2)  = wd1[Irang].vstart;
    }
  }
  return Arrive;
}

bool IntWalk_IWalking::TestArretPassage(const NCollection_Sequence<double>& Umult,
                                        const NCollection_Sequence<double>& Vmult,
                                        const math_Vector&                  UV,
                                        const int                           Index,
                                        int&                                Irang)
{

  double Up, Vp, Scal;
  bool   Arrive = false;
  int    N, k, i;
  double Utest, Vtest;
  double tolu = tolerance(1);
  double tolv = tolerance(2);

  if (!reversed)
  {
    previousPoint.ParametersOnS2(Up, Vp);
  }
  else
  {
    previousPoint.ParametersOnS1(Up, Vp);
  }

  double UV1 = UV(1);
  double UV2 = UV(2);

  const bool   isHighlyAnisotropic = std::max(tolu, tolv) > 1000. * std::min(tolu, tolv);
  const double deltau =
    mySRangeU.IsVoid()
      ? UM - Um
      : (isHighlyAnisotropic ? mySRangeU.Delta() : std::max(mySRangeU.Delta(), 1.0));
  const double deltav =
    mySRangeV.IsVoid()
      ? VM - Vm
      : (isHighlyAnisotropic ? mySRangeV.Delta() : std::max(mySRangeV.Delta(), 1.0));

  Up /= deltau;
  UV1 /= deltau;
  Vp /= deltav;
  UV2 /= deltav;

  tolu /= deltau;
  tolv /= deltav;

  double tolu2 = tolu + tolu;
  double tolv2 = tolv + tolv;

  double dPreviousCurrent = (Up - UV1) * (Up - UV1) + (Vp - UV2) * (Vp - UV2);
  for (k = 1; k < (int)wd2.size(); k++)
  {
    if (wd2[k].etat > 0)
    {
      Utest = wd2[k].ustart;
      Vtest = wd2[k].vstart;

      Utest /= deltau;
      Vtest /= deltav;

      double UV1mUtest = UV1 - Utest;
      double UV2mVtest = UV2 - Vtest;
      if ((UV1mUtest < tolu2 && UV1mUtest > -tolu2) && (UV2mVtest < tolv2 && UV2mVtest > -tolv2))
      {
        if (Index != k)
        {

          wd2[k].etat = -wd2[k].etat;
        }
        else
        {

          Arrive = true;
        }
      }
      else
      {
        double UpmUtest       = (Up - Utest);
        double VpmVtest       = (Vp - Vtest);
        double dPreviousStart = (UpmUtest) * (UpmUtest) + (VpmVtest) * (VpmVtest);
        double dCurrentStart  = UV1mUtest * UV1mUtest + UV2mVtest * UV2mVtest;

        Scal = (UpmUtest) * (UV1mUtest) + (VpmVtest) * (UV2mVtest);
        if ((std::abs(UpmUtest) < tolu && std::abs(VpmVtest) < tolv))
        {
          if (Index != k)
          {

            wd2[k].etat = -wd2[k].etat;
          }
        }
        else if (Scal < 0 && (dPreviousStart + dCurrentStart < dPreviousCurrent))
        {
          if (Index == k)
          {
            Arrive = true;
          }
          else
          {

            wd2[k].etat = -wd2[k].etat;
          }
        }
        else if (k != Index)
        {
          if (dPreviousStart < dPreviousCurrent * 0.25)
          {
            wd2[k].etat = -wd2[k].etat;
          }
          else
          {
            if (dCurrentStart < dPreviousCurrent * 0.25)
            {

              wd2[k].etat = -wd2[k].etat;
            }
            else
            {
              double UMidUtest    = 0.5 * (UV1 + Up) - Utest;
              double VMidVtest    = 0.5 * (UV2 + Vp) - Vtest;
              double dMiddleStart = UMidUtest * UMidUtest + VMidVtest * VMidVtest;

              if (dMiddleStart < dPreviousCurrent * 0.5)
              {

                wd2[k].etat = -wd2[k].etat;
              }
            }
          }
        }
      }
    }
  }

  Irang = 0;
  for (i = 1; i < (int)wd1.size(); i++)
  {
    if (wd1[i].etat > 0 && wd1[i].etat < 11)
    {
      Utest = wd1[i].ustart;
      Vtest = wd1[i].vstart;
      Utest /= deltau;
      Vtest /= deltav;

      if (((Up - Utest) * (UV1 - Utest) + (Vp - Vtest) * (UV2 - Vtest) < 0)
          || (std::abs(UV1 - Utest) < tolu && std::abs(UV2 - Vtest) < tolv))
        Irang = i;
      else if (nbMultiplicities[i] > 0)
      {
        N = 0;
        for (k = 1; k < i; k++)
          N = N + nbMultiplicities[k];
        for (int j = N + 1; j <= N + nbMultiplicities[i]; j++)
        {
          double Umultj = Umult(j) / deltau;
          double Vmultj = Vmult(j) / deltav;
          if (((Up - Umultj) * (UV1 - Umultj) + (Vp - Vmultj) * (UV2 - Vmultj) < 0)
              || (std::abs(UV1 - Umultj) < tolu && std::abs(UV2 - Vmultj) < tolv))
          {
            Irang = i;
            break;
          }
        }
      }
    }
  }
  return Arrive;
}

bool IntWalk_IWalking::TestArretAjout(TheIWFunction&   sp,
                                      math_Vector&     UV,
                                      int&             Irang,
                                      IntSurf_PntOn2S& Psol)

{
  bool   Arrive = false;
  double U1, V1;
  double Up, Vp;

  if (!reversed)
  {
    previousPoint.ParametersOnS2(Up, Vp);
  }
  else
  {
    previousPoint.ParametersOnS1(Up, Vp);
  }

  int nbAjout = seqAjout.Length();
  for (int i = 1; i <= nbAjout; i++)
  {
    Irang = seqAjout.Value(i);

    if (std::abs(Irang) <= lines.Length())
    {
      const occ::handle<IntWalk_TheIWLine>& Line = lines.Value(std::abs(Irang));
      if (Irang > 0)
        Psol = Line->Value(Line->NbPoints());
      else
        Psol = Line->Value(1);
      if (!reversed)
      {
        Psol.ParametersOnS2(U1, V1);
      }
      else
      {
        Psol.ParametersOnS1(U1, V1);
      }
      if (((Up - U1) * (UV(1) - U1) + (Vp - V1) * (UV(2) - V1)) < 0
          || (std::abs(UV(1) - U1) < tolerance(1) && std::abs(UV(2) - V1) < tolerance(2)))
      {

        Arrive = true;
        UV(1)  = U1;
        UV(2)  = V1;
        double      abidF[1], abidD[1][2];
        math_Vector bidF(abidF, 1, 1);
        math_Matrix bidD(abidD, 1, 1, 1, 2);
        sp.Values(UV, bidF, bidD);
        break;
      }
    }
  }
  return Arrive;
}

void IntWalk_IWalking::FillPntsInHoles(TheIWFunction&                               sp,
                                       NCollection_Sequence<int>&                   CopySeqAlone,
                                       NCollection_Sequence<IntSurf_InteriorPoint>& PntsInHoles)
{
  math_Vector BornInf(1, 2), BornSup(1, 2);
  BornInf(1) = Um;
  BornSup(1) = UM;
  BornInf(2) = Vm;
  BornSup(2) = VM;
  PointLineLine.Clear();
  NCollection_Sequence<int> SeqToRemove;
  NCollection_Map<int>      BadSolutions;

  for (int i = 1; i < CopySeqAlone.Length(); i++)
  {
    int Irang1 = CopySeqAlone(i);
    if (Irang1 == 0)
      continue;
    bool                                  ToRemove = false;
    IntSurf_PntOn2S                       PointAlone1, PointAlone2;
    const occ::handle<IntWalk_TheIWLine>& Line1 = lines.Value(std::abs(Irang1));
    if (Irang1 > 0)
      PointAlone1 = Line1->Value(Line1->NbPoints());
    else
      PointAlone1 = Line1->Value(1);
    gp_Pnt2d P2d1      = PointAlone1.ValueOnSurface(reversed), P2d2;
    double   MinSqDist = RealLast();
    int      MinRang = 0, MinIndex = 0;
    for (int j = i + 1; j <= CopySeqAlone.Length(); j++)
    {
      int Irang2 = CopySeqAlone(j);
      if (Irang2 == 0 || BadSolutions.Contains(Irang2))
        continue;
      const occ::handle<IntWalk_TheIWLine>& Line2 = lines.Value(std::abs(Irang2));
      if (Irang2 > 0)
        PointAlone2 = Line2->Value(Line2->NbPoints());
      else
        PointAlone2 = Line2->Value(1);
      P2d2           = PointAlone2.ValueOnSurface(reversed);
      double aSqDist = P2d1.SquareDistance(P2d2);
      if (aSqDist < MinSqDist)
      {
        MinSqDist = aSqDist;
        MinRang   = Irang2;
        MinIndex  = j;
      }
    }

    if (MinRang == 0)
    {
      SeqToRemove.Append(Irang1);
      BadSolutions.Clear();
      continue;
    }

    if (std::abs(Irang1) == std::abs(MinRang) && lines.Value(std::abs(Irang1))->NbPoints() == 2)
    {
      SeqToRemove.Append(Irang1);
      SeqToRemove.Append(MinRang);
      CopySeqAlone(i)        = 0;
      CopySeqAlone(MinIndex) = 0;
      BadSolutions.Clear();
      continue;
    }

    const occ::handle<IntWalk_TheIWLine>& Line2 = lines.Value(std::abs(MinRang));
    if (MinRang > 0)
      PointAlone2 = Line2->Value(Line2->NbPoints());
    else
      PointAlone2 = Line2->Value(1);
    gp_Pnt Pnt1        = PointAlone1.Value();
    gp_Pnt Pnt2        = PointAlone2.Value();
    P2d2               = PointAlone2.ValueOnSurface(reversed);
    double MinSqDist3d = Pnt1.SquareDistance(Pnt2);
    if (MinSqDist3d <= epsilon
        || (std::abs(P2d1.X() - P2d2.X()) <= tolerance(1)
            && std::abs(P2d1.Y() - P2d2.Y()) <= tolerance(2)))
      ToRemove = true;
    else
    {
      math_Vector UVap(1, 2), UV(1, 2);
      UVap(1) = (P2d1.X() + P2d2.X()) / 2;
      UVap(2) = (P2d1.Y() + P2d2.Y()) / 2;
      math_FunctionSetRoot Rsnld(sp, tolerance);
      Rsnld.Perform(sp, UVap, BornInf, BornSup);
      if (Rsnld.IsDone() && std::abs(sp.Root()) <= sp.Tolerance() && !sp.IsTangent())
      {
        Rsnld.Root(UV);
        gp_Pnt2d Pmid(UV(1), UV(2));
        gp_Vec2d P1P2(P2d1, P2d2);
        gp_Vec2d P1Pmid(P2d1, Pmid);
        gp_Vec2d P2Pmid(P2d2, Pmid);
        double   ScalProd1   = P1P2 * P1Pmid;
        double   ScalProd2   = P1P2 * P2Pmid;
        bool     IsPmidValid = (ScalProd1 > 0. && ScalProd2 < 0);
        if (IsPmidValid)
        {
          for (int iline = 1; iline <= lines.Length(); iline++)
            if (IsPointOnLine(Pmid, iline))
            {
              IsPmidValid = false;
              break;
            }
        }
        if (IsPmidValid)
        {
          IntSurf_InteriorPoint aPoint(sp.Point(),
                                       UV(1),
                                       UV(2),
                                       sp.Direction3d(),
                                       sp.Direction2d());
          PntsInHoles.Append(aPoint);
          NCollection_List<int> LineLine;
          LineLine.Append(Irang1);
          LineLine.Append(MinRang);
          PointLineLine.Bind(PntsInHoles.Length(), LineLine);
        }
        else
        {
          BadSolutions.Add(MinRang);
          i--;
          continue;
        }
      }
      else
      {
        BadSolutions.Add(MinRang);
        i--;
        continue;
      }
    }
    CopySeqAlone(i)        = 0;
    CopySeqAlone(MinIndex) = 0;
    if (ToRemove)
    {
      SeqToRemove.Append(Irang1);
      SeqToRemove.Append(MinRang);
    }
    BadSolutions.Clear();
  }

  for (int i = 1; i <= SeqToRemove.Length(); i++)
    for (int j = 1; j <= seqAlone.Length(); j++)
      if (seqAlone(j) == SeqToRemove(i))
      {
        seqAlone.Remove(j);
        break;
      }
}

void IntWalk_IWalking::TestArretCadre(const NCollection_Sequence<double>&   Umult,
                                      const NCollection_Sequence<double>&   Vmult,
                                      const occ::handle<IntWalk_TheIWLine>& Line,
                                      TheIWFunction&                        sp,
                                      math_Vector&                          UV,
                                      int&                                  Irang)

{
  double Scal, Up, Vp, Uc, Vc;
  int    N;
  bool   Found = false;

  Irang = 0;
  for (int i = 1; i < (int)wd1.size(); i++)
  {
    if (wd1[i].etat < 0)
    {
      N = 0;
      if (nbMultiplicities[i] > 0)
      {
        for (int k = 1; k < i; k++)
          N += nbMultiplicities[k];
      }
      if (!reversed)
      {
        Line->Value(1).ParametersOnS2(Up, Vp);
      }
      else
      {
        Line->Value(1).ParametersOnS1(Up, Vp);
      }
      int nbp = Line->NbPoints();
      for (int j = 2; j <= nbp; j++)
      {
        if (!reversed)
        {
          Line->Value(j).ParametersOnS2(Uc, Vc);
        }
        else
        {
          Line->Value(j).ParametersOnS1(Uc, Vc);
        }

        gp_Vec2d aVec1(Up - wd1[i].ustart, Vp - wd1[i].vstart),
          aVec2(Uc - wd1[i].ustart, Vc - wd1[i].vstart);
        CutVectorByTolerances(aVec1, tolerance);
        CutVectorByTolerances(aVec2, tolerance);

        Scal = aVec1 * aVec2;

        if (Scal < 0)
        {
          Line->Cut(j);
          nbp   = Line->NbPoints();
          Irang = i;
          UV(1) = wd1[Irang].ustart;
          UV(2) = wd1[Irang].vstart;
          Found = true;
        }
        else if (std::abs(Uc - wd1[i].ustart) < tolerance(1)
                 && std::abs(Vc - wd1[i].vstart) < tolerance(2))
        {
          Line->Cut(j);
          nbp   = Line->NbPoints();
          Irang = i;
          UV(1) = wd1[Irang].ustart;
          UV(2) = wd1[Irang].vstart;
          Found = true;
        }
        else if (nbMultiplicities[i] > 0)
        {
          for (int k = N + 1; k <= N + nbMultiplicities[i]; k++)
          {
            aVec1.SetCoord(Up - Umult(k), Vp - Vmult(k)),
              aVec2.SetCoord(Uc - Umult(k), Vc - Vmult(k));
            CutVectorByTolerances(aVec1, tolerance);
            CutVectorByTolerances(aVec2, tolerance);

            Scal = aVec1 * aVec2;

            if (Scal < 0)
            {
              Line->Cut(j);
              nbp   = Line->NbPoints();
              Irang = i;
              UV(1) = wd1[Irang].ustart;
              UV(2) = wd1[Irang].vstart;
              Found = true;
              break;
            }
            else if (std::abs(Uc - Umult(k)) < tolerance(1)
                     && std::abs(Vc - Vmult(k)) < tolerance(2))
            {
              Line->Cut(j);
              nbp   = Line->NbPoints();
              Irang = i;
              UV(1) = wd1[Irang].ustart;
              UV(2) = wd1[Irang].vstart;
              Found = true;
              break;
            }
          }
        }
        if (Found)
        {
          double      abidF[1], abidD[1][2];
          math_Vector bidF(abidF, 1, 1);
          math_Matrix bidD(abidD, 1, 1, 1, 2);
          sp.Values(UV, bidF, bidD);
          int NBP = Line->NbPoints();
          int Indextg;
          Line->TangentVector(Indextg);
          if (Indextg > NBP)
          {
            if (j > 3 && j <= NBP + 1)
            {
              gp_Vec Dir3d  = sp.Direction3d();
              gp_Vec Dir3d1 = gp_Vec(Line->Value(j - 2).Value(), Line->Value(j - 1).Value());
              double dot    = Dir3d.Dot(Dir3d1);
              if (dot < 0.0)
              {
                Dir3d.Reverse();
              }
              Line->SetTangentVector(previousd3d, j - 1);
            }
#ifdef OCCT_DEBUG
            else
            {
              std::cout << " IntWalk_IWalking_2.gxx : bizarrerie 30 10 97 " << std::endl;
            }
#endif
          }

          return;
        }
        Up = Uc;
        Vp = Vc;
      }

      gp_Vec2d aVec1(Up - wd1[i].ustart, Vp - wd1[i].vstart),
        aVec2(UV(1) - wd1[i].ustart, UV(2) - wd1[i].vstart);
      CutVectorByTolerances(aVec1, tolerance);
      CutVectorByTolerances(aVec2, tolerance);

      Scal = aVec1 * aVec2;

      if (Scal < 0)
      {
        Irang = i;
        UV(1) = wd1[Irang].ustart;
        UV(2) = wd1[Irang].vstart;
        Found = true;
      }
      else if (std::abs(UV(1) - wd1[i].ustart) < tolerance(1)
               && std::abs(UV(2) - wd1[i].vstart) < tolerance(2))
      {
        Irang = i;
        UV(1) = wd1[Irang].ustart;
        UV(2) = wd1[Irang].vstart;
        Found = true;
      }
      else if (nbMultiplicities[i] > 0)
      {
        for (int j = N + 1; j <= N + nbMultiplicities[i]; j++)
        {
          aVec1.SetCoord(Up - Umult(j), Vp - Vmult(j));
          aVec2.SetCoord(UV(1) - Umult(j), UV(2) - Vmult(j));
          CutVectorByTolerances(aVec1, tolerance);
          CutVectorByTolerances(aVec2, tolerance);

          Scal = aVec1 * aVec2;

          if (Scal < 0)
          {
            Irang = i;
            UV(1) = wd1[Irang].ustart;
            UV(2) = wd1[Irang].vstart;
            Found = true;
            break;
          }
          else if (std::abs(UV(1) - Umult(j)) < tolerance(1)
                   && std::abs(UV(2) - Vmult(j)) < tolerance(2))
          {
            Irang = i;
            UV(1) = wd1[Irang].ustart;
            UV(2) = wd1[Irang].vstart;
            Found = true;
            break;
          }
        }
      }
      if (Found)
      {
        Irang = -Irang;
        double      abidF[1], abidD[1][2];
        math_Vector bidF(abidF, 1, 1);
        math_Matrix bidD(abidD, 1, 1, 1, 2);
        sp.Values(UV, bidF, bidD);
        return;
      }
    }
  }
}

static bool TestPassedSolutionWithNegativeState(const IntWalk_VectorOfWalkingData&  wd,
                                                const NCollection_Sequence<double>& Umult,
                                                const NCollection_Sequence<double>& Vmult,
                                                const double&                       prevUp,
                                                const double&                       prevVp,
                                                const IntWalk_VectorOfInteger& nbMultiplicities,
                                                const math_Vector&             tolerance,
                                                TheIWFunction&                 sp,
                                                math_Vector&                   UV,
                                                int&                           Irang);

void IntWalk_IWalking::ComputeOpenLine(const NCollection_Sequence<double>& Umult,
                                       const NCollection_Sequence<double>& Vmult,
                                       const ThePOPIterator&               Pnts1,
                                       TheIWFunction&                      Func,
                                       bool&                               Rajout)

{
  int             I = 0, N = 0, SaveN = 0;
  double          aBornInf[2] = {}, aBornSup[2] = {}, aUVap[2] = {};
  math_Vector     BornInf(aBornInf, 1, 2), BornSup(aBornSup, 1, 2), UVap(aUVap, 1, 2);
  double          PasC = 0.0, PasCu = 0.0, PasCv = 0.0;
  bool            Arrive     = false;
  bool            Cadre      = false;
  bool            ArretAjout = false;
  IntSurf_PntOn2S Psol;
  occ::handle<IntWalk_TheIWLine> CurrentLine;
  bool                           Tgtend = false;

  IntWalk_StatusDeflection aStatus = IntWalk_OK, StatusPrecedent = IntWalk_OK;

  int NbDivision = 0;

  int StepSign = 0;

  ThePointOfPath PathPnt;

  BornInf(1) = Um;
  BornSup(1) = UM;
  BornInf(2) = Vm;
  BornSup(2) = VM;

  math_FunctionSetRoot Rsnld(Func, tolerance);
  int                  nbPath = Pnts1.Length();

  NCollection_LocalArray<int> movementdirectioninfoarr(nbPath + 1);
  int*                        movementdirectioninfo = movementdirectioninfoarr;
  for (I = 0; I <= nbPath; I++)
  {
    movementdirectioninfo[I] = 0;
  }

  TheIWFunction aFuncForDuplicate = Func;

  for (I = 1; I <= nbPath; I++)
  {

    if ((wd1[I].etat > 11) || ((wd1[I].etat < -11) && (movementdirectioninfo[I] != 0)))
    {

      PathPnt = Pnts1.Value(I);
      UVap(1) = wd1[I].ustart;
      UVap(2) = wd1[I].vstart;
      MakeWalkingPoint(11, UVap(1), UVap(2), Func, previousPoint);

      if (IsPointOnLine(previousPoint, BornInf, BornSup, Rsnld, aFuncForDuplicate))
      {
        wd1[I].etat = -std::abs(wd1[I].etat);
        continue;
      }

      CurrentLine = new IntWalk_TheIWLine(new NCollection_IncAllocator());
      CurrentLine->SetTangencyAtBegining(false);
      Tgtend = false;
      CurrentLine->AddStatusFirst(false, true, I, PathPnt);
      previousd3d = Func.Direction3d();
      previousd2d = Func.Direction2d();
      CurrentLine->AddPoint(previousPoint);

      if (movementdirectioninfo[I] != 0)
      {
        if (movementdirectioninfo[I] < 0)
        {
          StepSign = -1;
          CurrentLine->SetTangentVector(previousd3d.Reversed(), 1);
        }
        else
        {
          StepSign = 1;
          CurrentLine->SetTangentVector(previousd3d, 1);
        }
      }
      else
      {
        double tyutuyt = ThePointOfPathTool::Direction3d(PathPnt) * previousd3d;
        if (tyutuyt < 0)
        {
          StepSign = -1;
          CurrentLine->SetTangentVector(previousd3d.Reversed(), 1);
        }
        else
        {
          StepSign = 1;
          CurrentLine->SetTangentVector(previousd3d, 1);
        }
      }

      wd1[I].etat              = -std::abs(wd1[I].etat);
      movementdirectioninfo[I] = (movementdirectioninfo[I] == 0) ? StepSign : 0;

      double d2dx = std::abs(previousd2d.X());
      double d2dy = std::abs(previousd2d.Y());
      if (d2dx < tolerance(1))
      {
        PasC = pas * (VM - Vm) / d2dy;
      }
      else if (d2dy < tolerance(2))
      {
        PasC = pas * (UM - Um) / d2dx;
      }
      else
      {
        PasC = pas * std::min((UM - Um) / d2dx, (VM - Vm) / d2dy);
      }

      Arrive          = false;
      ArretAjout      = false;
      NbDivision      = 0;
      StatusPrecedent = IntWalk_OK;

      int IndexOfPathPointDoNotCheck = 0;
      int aNbIter                    = 10;
      while (!Arrive)
      {
        Cadre = Cadrage(BornInf, BornSup, UVap, PasC, StepSign);

#ifdef CHRONO
        Chronrsnld.Start();
#endif

        Rsnld.Perform(Func, UVap, BornInf, BornSup);

#ifdef CHRONO
        Chronrsnld.Stop();
#endif

        if (Cadre)
        {
          BornInf(1) = Um;
          BornSup(1) = UM;
          BornInf(2) = Vm;
          BornSup(2) = VM;
        }
        if (Rsnld.IsDone())
        {
          if (std::abs(Func.Root()) > Func.Tolerance())
          {
            PasC  = PasC / 2.0;
            PasCu = std::abs(PasC * previousd2d.X());
            PasCv = std::abs(PasC * previousd2d.Y());
            if (PasCu <= tolerance(1) && PasCv <= tolerance(2))
            {
              if (CurrentLine->NbPoints() == 1)
                break;
              Arrive = true;
              CurrentLine->AddStatusLast(false);
              Tgtend = true;
              Rajout = true;
              seqAlone.Append(lines.Length() + 1);
              seqAjout.Append(lines.Length() + 1);
            }
          }
          else
          {
            Rsnld.Root(UVap);
            Arrive = TestArretPassage(Umult, Vmult, Func, UVap, N);
            if (Arrive)
            {
              Cadre = false;
            }
            else
            {
              if (Rajout)
              {
                ArretAjout = TestArretAjout(Func, UVap, N, Psol);
                SaveN      = N;
                if (ArretAjout)
                {

                  Tgtend = lines.Value(N)->IsTangentAtEnd();
                  N      = -N;
                }
              }

              if (!(Rajout && ArretAjout))
              {
                double prevUp, prevVp;
                if (!reversed)
                {
                  previousPoint.ParametersOnS2(prevUp, prevVp);
                }
                else
                {
                  previousPoint.ParametersOnS1(prevUp, prevVp);
                }
                Arrive = TestPassedSolutionWithNegativeState(wd1,
                                                             Umult,
                                                             Vmult,
                                                             prevUp,
                                                             prevVp,
                                                             nbMultiplicities,
                                                             tolerance,
                                                             Func,
                                                             UVap,
                                                             N);
                if (Arrive)
                {
                  Cadre = false;
                }
              }

              if (!ArretAjout && Cadre)
              {
                if (CurrentLine->NbPoints() == 1)
                  break;
                TestArretCadre(Umult, Vmult, CurrentLine, Func, UVap, N);

                if (N <= 0)
                {
                  MakeWalkingPoint(2, UVap(1), UVap(2), Func, Psol);
                  Tgtend = Func.IsTangent();
                  N      = -N;
                }
              }
            }
            aStatus =
              TestDeflection(Func, Arrive, UVap, StatusPrecedent, NbDivision, PasC, StepSign);
            StatusPrecedent = aStatus;
            if (aStatus == IntWalk_PasTropGrand)
            {
              Arrive     = false;
              ArretAjout = false;
              Tgtend     = false;
              if (!reversed)
              {
                previousPoint.ParametersOnS2(UVap(1), UVap(2));
              }
              else
              {
                previousPoint.ParametersOnS1(UVap(1), UVap(2));
              }
            }
            else if (ArretAjout || Cadre)
            {
              Arrive = true;
              CurrentLine->AddStatusLast(false);

              CurrentLine->AddPoint(Psol);

              for (int iseq = 1; iseq <= seqAlone.Length(); iseq++)
                if (seqAlone(iseq) == SaveN)
                {
                  seqAlone.Remove(iseq);
                  break;
                }

              if (Cadre && N == 0)
              {
                Rajout = true;
                seqAjout.Append(lines.Length() + 1);
              }
            }
            else if (aStatus == IntWalk_ArretSurPointPrecedent)
            {
              if (CurrentLine->NbPoints() == 1)
              {
                Arrive = false;
                break;
              }
              Arrive = true;
              Rajout = true;

              seqAlone.Append(lines.Length() + 1);
              seqAjout.Append(lines.Length() + 1);
              CurrentLine->AddStatusLast(false);
              Tgtend = true;
            }
            else if (Arrive)
            {
              if (CurrentLine->NbPoints() == 1 && (N == I || aStatus == IntWalk_PointConfondu))
              {

                Arrive = false;
                break;
              }

              PathPnt = Pnts1.Value(N);

              int etat1N = wd1[N].etat;

              if (std::abs(etat1N) < 11)
              {

                if (aStatus == IntWalk_ArretSurPoint)
                {
                  CurrentLine->AddStatusLast(false);
                  Tgtend = true;
                }
                else
                {
                  Arrive = false;
                }
                CurrentLine->AddIndexPassing(N);
              }
              else
              {
                if (etat1N == 11)
                {
                  Tgtend = true;
                }
                CurrentLine->AddStatusLast(true, N, PathPnt);
              }
              AddPointInCurrentLine(N, PathPnt, CurrentLine);
              if ((etat1N != 1 && etat1N != 11))
              {

                wd1[N].etat              = -std::abs(etat1N);
                movementdirectioninfo[N] = (movementdirectioninfo[N] == 0) ? StepSign : 0;
                if (Arrive && movementdirectioninfo[N] != 0)
                {
                  IndexOfPathPointDoNotCheck = N;
                }

                if (Arrive)
                {
                  Rajout = true;
                  seqAjout.Append(lines.Length() + 1);
                }
              }
            }
            else if (aStatus == IntWalk_ArretSurPoint)
            {
              Arrive = true;
              CurrentLine->AddStatusLast(false);
              Tgtend = true;
              MakeWalkingPoint(1, UVap(1), UVap(2), Func, Psol);
              CurrentLine->AddPoint(Psol);
              Rajout = true;
              seqAlone.Append(lines.Length() + 1);
              seqAjout.Append(lines.Length() + 1);
            }
            else if (aStatus == IntWalk_OK)
            {
              MakeWalkingPoint(2, UVap(1), UVap(2), Func, previousPoint);
              previousd3d = Func.Direction3d();
              previousd2d = Func.Direction2d();
              CurrentLine->AddPoint(previousPoint);
            }
            else if (aStatus == IntWalk_PointConfondu)
            {
              aNbIter--;
            }
          }
        }
        else
        {
          PasC  = PasC / 2.;
          PasCu = std::abs(PasC * previousd2d.X());
          PasCv = std::abs(PasC * previousd2d.Y());
          if (PasCu <= tolerance(1) && PasCv <= tolerance(2))
          {
            if (CurrentLine->NbPoints() == 1)
              break;
            Arrive = true;
            CurrentLine->AddStatusLast(false);
            Tgtend = true;
            Rajout = true;
            seqAlone.Append(lines.Length() + 1);
            seqAjout.Append(lines.Length() + 1);
          }
        }

        if (aNbIter < 0)
          break;
      }

      if (Arrive)
      {
        CurrentLine->SetTangencyAtEnd(Tgtend);
        lines.Append(CurrentLine);

        movementdirectioninfo[I] = 0;
        if (wd1[I].etat > 0)

          wd1[I].etat = -wd1[I].etat;

        for (int av = 1; av <= nbPath; av++)
        {

          if ((wd1[av].etat > 11)
              || ((av != I) && (av != IndexOfPathPointDoNotCheck) && (wd1[av].etat < -11)
                  && (movementdirectioninfo[av] != 0)))
          {

            double                 Uav = wd1[av].ustart;
            double                 Vav = wd1[av].vstart;
            double                 Uavp, Vavp;
            const IntSurf_PntOn2S& avP = CurrentLine->Value(CurrentLine->NbPoints());
            if (!reversed)
            {
              avP.ParametersOnS2(Uavp, Vavp);
            }
            else
            {
              avP.ParametersOnS1(Uavp, Vavp);
            }
            Uav -= Uavp;
            Vav -= Vavp;
            Uav *= 0.001;
            Vav *= 0.001;
            if (std::abs(Uav) < tolerance(1) && std::abs(Vav) < tolerance(2))
            {

              if (wd1[av].etat < 0)
              {
                movementdirectioninfo[av] = 0;
              }
              else
              {
                wd1[av].etat              = -wd1[av].etat;
                movementdirectioninfo[av] = StepSign;
              }

              CurrentLine->AddStatusLast(true, av, Pnts1.Value(av));
            }

            const IntSurf_PntOn2S& avPP = CurrentLine->Value(1);
            if (!reversed)
            {
              avPP.ParametersOnS2(Uavp, Vavp);
            }
            else
            {
              avPP.ParametersOnS1(Uavp, Vavp);
            }
            Uav = wd1[av].ustart;
            Vav = wd1[av].vstart;
            Uav -= Uavp;
            Vav -= Vavp;
            Uav *= 0.001;
            Vav *= 0.001;
            if (std::abs(Uav) < tolerance(1) && std::abs(Vav) < tolerance(2))
            {

              if (wd1[av].etat < 0)
              {
                movementdirectioninfo[av] = 0;
              }
              else
              {
                wd1[av].etat              = -wd1[av].etat;
                movementdirectioninfo[av] = -StepSign;
              }

              CurrentLine->AddStatusFirst(false, true, av, Pnts1.Value(av));
            }
          }
        }
      }
    }
  }
}

static bool TestPassedSolutionWithNegativeState(const IntWalk_VectorOfWalkingData&  wd,
                                                const NCollection_Sequence<double>& Umult,
                                                const NCollection_Sequence<double>& Vmult,
                                                const double&                       prevUp,
                                                const double&                       prevVp,
                                                const IntWalk_VectorOfInteger& nbMultiplicities,
                                                const math_Vector&             tolerance,
                                                TheIWFunction&                 sp,
                                                math_Vector&                   UV,
                                                int&                           Irang)
{
  bool   Arrive = false;
  double Dup, Dvp, Utest, Vtest;
  double tolu = tolerance(1);
  double tolv = tolerance(2);
  int    i, j, k, N;
  for (i = 1; i < (int)wd.size(); i++)
  {
    if (wd[i].etat < -11)
    {

      Utest = wd[i].ustart;
      Vtest = wd[i].vstart;
      Dup   = prevUp - Utest;
      Dvp   = prevVp - Vtest;
      if (std::abs(Dup) >= tolu || std::abs(Dvp) >= tolv)
      {
        double UV1mUtest = UV(1) - Utest;
        double UV2mVtest = UV(2) - Vtest;
        if (((Dup * UV1mUtest + Dvp * UV2mVtest) < 0)
            || (std::abs(UV1mUtest) < tolu && std::abs(UV2mVtest) < tolv))
        {
          Irang  = i;
          Arrive = true;
          UV(1)  = Utest;
          UV(2)  = Vtest;
        }
        else if (nbMultiplicities[i] > 0)
        {
          N = 0;
          for (k = 1; k < i; k++)
          {
            N += nbMultiplicities[k];
          }
          for (j = N + 1; j <= N + nbMultiplicities[i]; j++)
          {
            if (((prevUp - Umult(j)) * (UV(1) - Umult(j)) + (prevVp - Vmult(j)) * (UV(2) - Vmult(j))
                 < 0)
                || (std::abs(UV(1) - Umult(j)) < tolu && std::abs(UV(2) - Vmult(j)) < tolv))
            {
              Irang  = i;
              Arrive = true;
              UV(1)  = Utest;
              UV(2)  = Vtest;
              break;
            }
          }
        }
        if (Arrive)
        {
          double      abidF[1], abidD[1][2];
          math_Vector bidF(abidF, 1, 1);
          math_Matrix bidD(abidD, 1, 1, 1, 2);
          sp.Values(UV, bidF, bidD);
          break;
        }
      }
    }
  }
  return Arrive;
}

void IntWalk_IWalking::ComputeCloseLine(const NCollection_Sequence<double>& Umult,
                                        const NCollection_Sequence<double>& Vmult,
                                        const ThePOPIterator&               Pnts1,
                                        const ThePOLIterator&               Pnts2,
                                        TheIWFunction&                      Func,
                                        bool&                               Rajout)

{
  int                            I = 0, N = 0, SaveN = 0;
  double                         aBornInf[2] = {}, aBornSup[2] = {}, aUVap[2] = {};
  math_Vector                    BornInf(aBornInf, 1, 2), BornSup(aBornSup, 1, 2);
  math_Vector                    Uvap(aUVap, 1, 2);
  double                         PasC       = 0.0;
  double                         PasCu      = 0.0;
  double                         PasCv      = 0.0;
  double                         PasSav     = 0.0;
  bool                           Arrive     = false;
  bool                           Cadre      = false;
  bool                           ArretAjout = false;
  IntSurf_PntOn2S                Psol;
  occ::handle<IntWalk_TheIWLine> CurrentLine;
  ThePointOfPath                 PathPnt;
  ThePointOfLoop                 LoopPnt;

  bool Tgtbeg = false, Tgtend = false;

  int StepSign = 0;

  IntWalk_StatusDeflection aStatus    = IntWalk_OK, StatusPrecedent;
  int                      NbDivision = 0;

  int Ipass = 0;

  BornInf(1) = Um;
  BornSup(1) = UM;
  BornInf(2) = Vm;
  BornSup(2) = VM;

  math_FunctionSetRoot Rsnld(Func, tolerance);
  int                  nbLoop = Pnts2.Length();

  math_Matrix D(1, 1, 1, 2);
  const int   aNbSamplePnt                = 10;
  bool        isLeftDegeneratedBorder[2]  = {true, true};
  bool        isRightDegeneratedBorder[2] = {true, true};
  math_Vector aStep(1, 2);
  aStep = (BornSup - BornInf) / (aNbSamplePnt - 1);
  for (int aBorderIdx = 1; aBorderIdx <= 2; aBorderIdx++)
  {
    int         aChangeIdx = aBorderIdx == 2 ? 1 : 2;
    math_Vector UV(1, 2);

    UV(aBorderIdx) = BornInf(aBorderIdx);
    for (int aParamIdx = 0; aParamIdx < aNbSamplePnt; aParamIdx++)
    {
      double aParam  = BornInf(aChangeIdx) + aParamIdx * aStep(aChangeIdx);
      UV(aChangeIdx) = aParam;
      Func.Derivatives(UV, D);
      if (std::abs(D(1, aChangeIdx)) > Precision::Confusion())
      {
        isLeftDegeneratedBorder[aBorderIdx - 1] = false;
        break;
      }
    }

    UV(aBorderIdx) = BornSup(aBorderIdx);
    for (int aParamIdx = 0; aParamIdx < aNbSamplePnt; aParamIdx++)
    {
      double aParam  = BornInf(aChangeIdx) + aParamIdx * aStep(aChangeIdx);
      UV(aChangeIdx) = aParam;
      Func.Derivatives(UV, D);
      if (std::abs(D(1, aChangeIdx)) > Precision::Confusion())
      {
        isRightDegeneratedBorder[aBorderIdx - 1] = false;
        break;
      }
    }
  }

  TheIWFunction aFuncForDuplicate = Func;

  for (I = 1; I <= nbLoop; I++)
  {
    if (wd2[I].etat > 12)
    {
      LoopPnt = Pnts2.Value(I);
      previousPoint.SetValue(ThePointOfLoopTool::Value3d(LoopPnt),
                             reversed,
                             wd2[I].ustart,
                             wd2[I].vstart);

      if (IsPointOnLine(previousPoint, BornInf, BornSup, Rsnld, aFuncForDuplicate))
      {
        wd2[I].etat = -wd2[I].etat;
        continue;
      }

      previousd3d = ThePointOfLoopTool::Direction3d(LoopPnt);
      previousd2d = ThePointOfLoopTool::Direction2d(LoopPnt);

      CurrentLine = new IntWalk_TheIWLine(new NCollection_IncAllocator());
      CurrentLine->AddPoint(previousPoint);
      CurrentLine->SetTangentVector(previousd3d, 1);
      Tgtbeg  = false;
      Tgtend  = false;
      Uvap(1) = wd2[I].ustart;
      Uvap(2) = wd2[I].vstart;

      StepSign = 1;

      double d2dx = std::abs(previousd2d.X());
      double d2dy = std::abs(previousd2d.Y());
      if (d2dx < tolerance(1))
      {
        PasC = pas * (VM - Vm) / d2dy;
      }
      else if (d2dy < tolerance(2))
      {
        PasC = pas * (UM - Um) / d2dx;
      }
      else
      {
        PasC = pas * std::min((UM - Um) / d2dx, (VM - Vm) / d2dy);
      }

      PasSav = PasC;

      Arrive          = false;
      ArretAjout      = false;
      NbDivision      = 0;
      StatusPrecedent = IntWalk_OK;
      int aNbIter     = 10;
      while (!Arrive)
      {
        Cadre = Cadrage(BornInf, BornSup, Uvap, PasC, StepSign);
#ifdef CHRONO
        Chronrsnld.Start();
#endif

        Rsnld.Perform(Func, Uvap, BornInf, BornSup);

#ifdef CHRONO
        Chronrsnld.Stop();
#endif
        bool isOnDegeneratedBorder = false;

        if (Cadre)
        {
          BornInf(1) = Um;
          BornSup(1) = UM;
          BornInf(2) = Vm;
          BornSup(2) = VM;
        }
        if (Rsnld.IsDone())
        {
          if (std::abs(Func.Root()) > Func.Tolerance())
          {
            PasC  = PasC / 2.;
            PasCu = std::abs(PasC * previousd2d.X());
            PasCv = std::abs(PasC * previousd2d.Y());

            if (PasCu <= tolerance(1) && PasCv <= tolerance(2))
            {
              if (CurrentLine->NbPoints() == 1)
              {
                RemoveTwoEndPoints(I);
                break;
              }
              if (wd2[I].etat > 12)
              {
                wd2[I].etat = 12;
                ArretAjout  = false;
                OpenLine(0, Psol, Pnts1, Func, CurrentLine);
                StepSign        = -1;
                StatusPrecedent = IntWalk_OK;
                Arrive          = false;
                PasC            = PasSav;
                Rajout          = true;
                seqAlone.Append(-lines.Length() - 1);
                seqAjout.Append(-lines.Length() - 1);
              }
              else
              {
                Arrive = true;
                CurrentLine->AddStatusLast(false);
                Rajout = true;
                seqAlone.Append(lines.Length() + 1);
                seqAjout.Append(lines.Length() + 1);
                Tgtend = true;
              }
            }
          }
          else
          {
            Rsnld.Root(Uvap);

            if (CurrentLine->NbPoints() > 2)
            {
              for (int aCoordIdx = 1; aCoordIdx <= 2; aCoordIdx++)
              {

                if ((isLeftDegeneratedBorder[aCoordIdx - 1]
                     && std::abs(Uvap(aCoordIdx) - BornInf(aCoordIdx)) < Precision::PConfusion())
                    || (isRightDegeneratedBorder[aCoordIdx - 1]
                        && std::abs(Uvap(aCoordIdx) - BornSup(aCoordIdx))
                             < Precision::PConfusion()))
                {
                  double uvprev[2], uv[2];
                  if (!reversed)
                  {
                    CurrentLine->Value(CurrentLine->NbPoints() - 1)
                      .ParametersOnS2(uvprev[0], uvprev[1]);
                    CurrentLine->Value(CurrentLine->NbPoints()).ParametersOnS2(uv[0], uv[1]);
                  }
                  else
                  {
                    CurrentLine->Value(CurrentLine->NbPoints() - 1)
                      .ParametersOnS1(uvprev[0], uvprev[1]);
                    CurrentLine->Value(CurrentLine->NbPoints()).ParametersOnS1(uv[0], uv[1]);
                  }

                  double aScaleCoeff = 0.0;

                  if (aStatus != IntWalk_PasTropGrand)
                  {

                    if (std::abs(uv[aCoordIdx - 1] - uvprev[aCoordIdx - 1]) > gp::Resolution())
                      aScaleCoeff = std::abs((Uvap(aCoordIdx) - uv[aCoordIdx - 1])
                                             / (uv[aCoordIdx - 1] - uvprev[aCoordIdx - 1]));
                    int aFixIdx = aCoordIdx == 1 ? 2 : 1;
                    Uvap(aFixIdx) =
                      uv[aFixIdx - 1] + (uv[aFixIdx - 1] - uvprev[aFixIdx - 1]) * aScaleCoeff;
                    isOnDegeneratedBorder = true;
                  }
                }
              }
            }

            Arrive = TestArretPassage(Umult, Vmult, Uvap, I, Ipass);
            if (Arrive)
            {
              Psol = CurrentLine->Value(1);
              if (!reversed)
              {
                Psol.ParametersOnS2(Uvap(1), Uvap(2));
              }
              else
              {
                Psol.ParametersOnS1(Uvap(1), Uvap(2));
              }
              Cadre = false;
            }
            else
            {
              if (Rajout)
              {
                ArretAjout = TestArretAjout(Func, Uvap, N, Psol);
                SaveN      = N;
                if (ArretAjout)
                {
                  if (N > 0)
                  {
                    Tgtend = lines.Value(N)->IsTangentAtEnd();
                    N      = -N;
                  }
                  else
                  {
                    Tgtend = lines.Value(-N)->IsTangentAtBegining();
                  }
                  Arrive = (wd2[I].etat == 12);
                }
              }

              if (!ArretAjout && Cadre)
              {
                if (CurrentLine->NbPoints() == 1)
                {
                  RemoveTwoEndPoints(I);
                  break;
                }
                TestArretCadre(Umult, Vmult, CurrentLine, Func, Uvap, N);
                SaveN = N;

                if (N <= 0)
                {
                  MakeWalkingPoint(2, Uvap(1), Uvap(2), Func, Psol);
                  Tgtend = Func.IsTangent();
                  if (isOnDegeneratedBorder)
                    Tgtend = true;
                  N = -N;
                }
                Arrive = (wd2[I].etat == 12);
              }
            }
            aStatus =
              TestDeflection(Func, Arrive, Uvap, StatusPrecedent, NbDivision, PasC, StepSign);

            if (isOnDegeneratedBorder && Tgtend)
              aStatus = IntWalk_ArretSurPoint;

            StatusPrecedent = aStatus;
            if (aStatus == IntWalk_PasTropGrand)
            {
              Arrive     = false;
              ArretAjout = false;
              Tgtend     = false;
              if (!reversed)
              {
                previousPoint.ParametersOnS2(Uvap(1), Uvap(2));
              }
              else
              {
                previousPoint.ParametersOnS1(Uvap(1), Uvap(2));
              }
            }
            else if (ArretAjout || Cadre)
            {
              if (Arrive)
              {
                CurrentLine->AddStatusLast(false);

                CurrentLine->AddPoint(Psol);

                if (IsValidEndPoint(I, SaveN))
                {
                  for (int iseq = 1; iseq <= seqAlone.Length(); iseq++)
                    if (seqAlone(iseq) == SaveN)
                    {
                      seqAlone.Remove(iseq);
                      break;
                    }
                  if (CurrentLine->NbPoints() <= 3)
                    for (int iseq = 1; iseq <= seqAjout.Length(); iseq++)
                      if (seqAjout(iseq) == SaveN)
                      {
                        seqAjout.Remove(iseq);
                        break;
                      }
                }
                else
                {
                  if (seqAlone.Last() == -lines.Length() - 1)
                  {
                    seqAlone.Remove(seqAlone.Length());
                    seqAjout.Remove(seqAjout.Length());
                  }
                  RemoveTwoEndPoints(I);
                  Arrive = false;
                  break;
                }

                if (Cadre && N == 0)
                {
                  Rajout = true;

                  seqAjout.Append(lines.Length() + 1);
                }
              }
              else
              {
                wd2[I].etat     = 12;
                Tgtbeg          = Tgtend;
                Tgtend          = false;
                ArretAjout      = false;
                StepSign        = -1;
                StatusPrecedent = IntWalk_OK;
                PasC            = PasSav;

                if (Arrive || Rajout || (!ArretAjout && Cadre && SaveN <= 0))
                {
                  if (aStatus == IntWalk_ArretSurPointPrecedent)
                  {
                    CurrentLine->AddPoint(Psol);
                    OpenLine(0, Psol, Pnts1, Func, CurrentLine);
                  }
                  else
                  {
                    OpenLine(-lines.Length() - 1, Psol, Pnts1, Func, CurrentLine);
                  }
                }

                if (IsValidEndPoint(I, SaveN))
                {
                  for (int iseq = 1; iseq <= seqAlone.Length(); iseq++)
                    if (seqAlone(iseq) == SaveN)
                    {
                      seqAlone.Remove(iseq);
                      break;
                    }
                  if (CurrentLine->NbPoints() <= 2)
                    for (int iseq = 1; iseq <= seqAjout.Length(); iseq++)
                      if (seqAjout(iseq) == SaveN)
                      {
                        seqAjout.Remove(iseq);
                        break;
                      }
                }
                else
                {
                  RemoveTwoEndPoints(I);
                  break;
                }

                if (Cadre && N == 0)
                {
                  Rajout = true;
                  seqAjout.Append(-lines.Length() - 1);
                }
              }
            }
            else if (aStatus == IntWalk_ArretSurPointPrecedent)
            {
              if (CurrentLine->NbPoints() == 1)
              {
                Arrive = false;
                RemoveTwoEndPoints(I);
                break;
              }
              if (wd2[I].etat > 12)
              {
                wd2[I].etat = 12;
                ArretAjout  = false;
                OpenLine(0, Psol, Pnts1, Func, CurrentLine);
                StepSign        = -1;
                StatusPrecedent = IntWalk_OK;
                Arrive          = false;
                PasC            = PasSav;
                Rajout          = true;
                seqAlone.Append(-lines.Length() - 1);
                seqAjout.Append(-lines.Length() - 1);
              }
              else
              {
                Arrive = true;
                CurrentLine->AddStatusLast(false);
                Rajout = true;
                seqAlone.Append(lines.Length() + 1);
                seqAjout.Append(lines.Length() + 1);
              }
            }
            else if (Arrive)
            {
              if (wd2[I].etat > 12)
              {
                CurrentLine->AddStatusFirstLast(true, false, false);
                CurrentLine->AddPoint(CurrentLine->Value(1));
              }
              else if ((N > 0) && (Pnts1.Length() >= N))
              {

                PathPnt = Pnts1.Value(N);
                CurrentLine->AddStatusLast(true, N, PathPnt);
                AddPointInCurrentLine(N, PathPnt, CurrentLine);
              }
            }
            else if (aStatus == IntWalk_ArretSurPoint)
            {
              if (wd2[I].etat > 12)
              {
                wd2[I].etat = 12;
                Tgtbeg      = true;
                Tgtend      = false;
                N           = -lines.Length() - 1;
                Psol.SetValue(Func.Point(), reversed, Uvap(1), Uvap(2));
                OpenLine(N, Psol, Pnts1, Func, CurrentLine);
                StepSign = -1;
                Rajout   = true;
                seqAlone.Append(N);
                seqAjout.Append(N);
                StatusPrecedent = IntWalk_OK;
                Arrive          = false;
                PasC            = PasSav;
              }
              else
              {
                Arrive = true;
                if (Ipass != 0)
                {
                  PathPnt = Pnts1.Value(Ipass);
                  CurrentLine->AddStatusLast(true, Ipass, PathPnt);
                  AddPointInCurrentLine(Ipass, PathPnt, CurrentLine);
                }
                else
                {
                  CurrentLine->AddStatusLast(false);
                  IntSurf_PntOn2S newP;
                  newP.SetValue(Func.Point(), reversed, Uvap(1), Uvap(2));
                  CurrentLine->AddPoint(newP);
                  Rajout = true;
                  seqAlone.Append(lines.Length() + 1);
                  seqAjout.Append(lines.Length() + 1);
                }
              }
            }
            else if (aStatus == IntWalk_OK)
            {
              if (Ipass != 0)
                CurrentLine->AddIndexPassing(Ipass);
              previousPoint.SetValue(Func.Point(), reversed, Uvap(1), Uvap(2));
              previousd3d = Func.Direction3d();
              previousd2d = Func.Direction2d();
              CurrentLine->AddPoint(previousPoint);
            }
            else if (aStatus == IntWalk_PointConfondu)
            {
              aNbIter--;
            }
          }
        }
        else
        {
          PasC  = PasC / 2.;
          PasCu = std::abs(PasC * previousd2d.X());
          PasCv = std::abs(PasC * previousd2d.Y());

          if (PasCu <= tolerance(1) && PasCv <= tolerance(2))
          {
            if (CurrentLine->NbPoints() == 1)
            {
              RemoveTwoEndPoints(I);
              break;
            }
            if (wd2[I].etat > 12)
            {
              wd2[I].etat = 12;
              ArretAjout  = false;
              OpenLine(0, Psol, Pnts1, Func, CurrentLine);
              StepSign        = -1;
              StatusPrecedent = IntWalk_OK;
              Arrive          = false;
              PasC            = PasSav;
              Rajout          = true;
              seqAlone.Append(-lines.Length() - 1);
              seqAjout.Append(-lines.Length() - 1);
            }
            else
            {
              Arrive = true;
              CurrentLine->AddStatusLast(false);
              Tgtend = true;
              Rajout = true;
              seqAlone.Append(lines.Length() + 1);
              seqAjout.Append(lines.Length() + 1);
            }
          }
        }

        if (aNbIter < 0)
          break;
      }
      if (Arrive)
      {
        CurrentLine->SetTangencyAtBegining(Tgtbeg);
        CurrentLine->SetTangencyAtEnd(Tgtend);

        lines.Append(CurrentLine);
        wd2[I].etat = -wd2[I].etat;
      }
    }
  }
}

namespace
{
  static const double CosRef3D = 0.98;

  static const double CosRef2D    = 0.88;
  static const int    MaxDivision = 60;

} // namespace

IntWalk_StatusDeflection IntWalk_IWalking::TestDeflection(
  TheIWFunction&                 sp,
  const bool                     Finished,
  const math_Vector&             UV,
  const IntWalk_StatusDeflection StatusPrecedent,
  int&                           NbDivision,
  double&                        Step,
  const int                      StepSign)
{

  IntWalk_StatusDeflection aStatus = IntWalk_OK;

  double Paramu = 0.0, Paramv = 0.0;

  if (!reversed)
  {
    previousPoint.ParametersOnS2(Paramu, Paramv);
  }
  else
  {
    previousPoint.ParametersOnS1(Paramu, Paramv);
  }

  const double Du  = UV(1) - Paramu;
  const double Dv  = UV(2) - Paramv;
  const double Duv = Du * Du + Dv * Dv;

  gp_Vec Corde(previousPoint.Value(), sp.Point());

  const double Norme = Corde.SquareMagnitude();

  if ((Norme <= 4.0 * Precision::SquareConfusion())
      && ((Duv <= Precision::SquarePConfusion()) || (StatusPrecedent != IntWalk_OK)))
  {
    aStatus = IntWalk_PointConfondu;
    if (StatusPrecedent == IntWalk_PasTropGrand)
    {
      return IntWalk_ArretSurPointPrecedent;
    }
  }
  else
  {
    double Cosi  = Corde * previousd3d;
    double Cosi2 = 0.0;

    if (Cosi * StepSign >= 0.)
    {
      const double aDiv = previousd3d.SquareMagnitude() * Norme;
      if (aDiv == 0)
        return aStatus;
      Cosi2 = Cosi * Cosi / aDiv;
    }
    if (Cosi2 < CosRef3D)
    {
      Step         = Step / 2.0;
      double StepU = std::abs(Step * previousd2d.X()), StepV = std::abs(Step * previousd2d.Y());
      if (StepU < tolerance(1) && StepV < tolerance(2))
        aStatus = IntWalk_ArretSurPointPrecedent;
      else
        aStatus = IntWalk_PasTropGrand;
      return aStatus;
    }
  }

  const double aMinTolU = 0.1 * std::abs(Step * previousd2d.X()),
               aMinTolV = 0.1 * std::abs(Step * previousd2d.Y());
  const double aTolU    = (aMinTolU > 0.0) ? std::min(tolerance(1), aMinTolU) : tolerance(1),
               aTolV    = (aMinTolV > 0.0) ? std::min(tolerance(2), aMinTolV) : tolerance(2);

  if ((std::abs(Du) < aTolU) && (std::abs(Dv) < aTolV))
  {

    return IntWalk_ArretSurPointPrecedent;
  }

  double Cosi = StepSign * (Du * previousd2d.X() + Dv * previousd2d.Y());

  if (Cosi < 0 && aStatus == IntWalk_PointConfondu)
    return IntWalk_ArretSurPointPrecedent;

  if (sp.IsTangent())
    return IntWalk_ArretSurPoint;

  if ((NbDivision < MaxDivision) && (aStatus != IntWalk_PointConfondu)
      && (StatusPrecedent != IntWalk_PointConfondu))
  {
    double Cosi2 = Cosi * Cosi / Duv;
    if (Cosi2 < CosRef2D || Cosi < 0)
    {
      Step         = Step / 2.0;
      double StepU = std::abs(Step * previousd2d.X()), StepV = std::abs(Step * previousd2d.Y());

      if (StepU < tolerance(1) && StepV < tolerance(2))
        aStatus = IntWalk_ArretSurPointPrecedent;
      else
        aStatus = IntWalk_PasTropGrand;
      NbDivision = NbDivision + 1;
      return aStatus;
    }

    Cosi  = Corde * sp.Direction3d();
    Cosi2 = Cosi * Cosi / sp.Direction3d().SquareMagnitude() / Norme;
    if (Cosi2 < CosRef3D)
    {
      Step         = Step / 2.;
      double StepU = std::abs(Step * previousd2d.X()), StepV = std::abs(Step * previousd2d.Y());
      if (StepU < tolerance(1) && StepV < tolerance(2))
        aStatus = IntWalk_ArretSurPoint;
      else
        aStatus = IntWalk_PasTropGrand;
      return aStatus;
    }
    Cosi  = Du * sp.Direction2d().X() + Dv * sp.Direction2d().Y();
    Cosi2 = Cosi * Cosi / Duv;
    if (Cosi2 < CosRef2D || sp.Direction2d() * previousd2d < 0)
    {

      Step         = Step / 2.;
      double StepU = std::abs(Step * previousd2d.X()), StepV = std::abs(Step * previousd2d.Y());
      if (StepU < tolerance(1) && StepV < tolerance(2))
        aStatus = IntWalk_ArretSurPointPrecedent;
      else
        aStatus = IntWalk_PasTropGrand;
      return aStatus;
    }
  }

  if (!Finished)
  {
    if (aStatus == IntWalk_PointConfondu)
    {
      double StepU = std::min(std::abs(1.5 * Du), pas * (UM - Um)),
             StepV = std::min(std::abs(1.5 * Dv), pas * (VM - Vm));

      double d2dx = std::abs(previousd2d.X());
      double d2dy = std::abs(previousd2d.Y());

      if (d2dx < tolerance(1))
      {
        Step = StepV / d2dy;
      }
      else if (d2dy < tolerance(2))
      {
        Step = StepU / d2dx;
      }
      else
      {
        Step = std::min(StepU / d2dx, StepV / d2dy);
      }
    }
    else
    {

      double FlecheCourante =
        (previousd3d.Normalized().XYZ() - sp.Direction3d().Normalized().XYZ()).SquareModulus()
        * Norme / 64.;

      if (FlecheCourante <= 0.25 * fleche * fleche)
      {
        double d2dx = std::abs(sp.Direction2d().X());
        double d2dy = std::abs(sp.Direction2d().Y());

        double StepU = std::min(std::abs(1.5 * Du), pas * (UM - Um)),
               StepV = std::min(std::abs(1.5 * Dv), pas * (VM - Vm));

        if (d2dx < tolerance(1))
        {
          Step = StepV / d2dy;
        }
        else if (d2dy < tolerance(2))
        {
          Step = StepU / d2dx;
        }
        else
        {
          Step = std::min(StepU / d2dx, StepV / d2dy);
        }
      }
      else
      {

        if (FlecheCourante > fleche * fleche)
        {
          Step         = Step / 2.;
          double StepU = std::abs(Step * previousd2d.X()), StepV = std::abs(Step * previousd2d.Y());

          if (StepU < tolerance(1) && StepV < tolerance(2))
            aStatus = IntWalk_ArretSurPointPrecedent;
          else
            aStatus = IntWalk_PasTropGrand;
        }
        else
        {
          double d2dx = std::abs(sp.Direction2d().X());
          double d2dy = std::abs(sp.Direction2d().Y());

          double StepU = std::min(std::abs(1.5 * Du), pas * (UM - Um)),
                 StepV = std::min(std::abs(1.5 * Dv), pas * (VM - Vm));

          if (d2dx < tolerance(1))
          {
            Step = std::min(Step, StepV / d2dy);
          }
          else if (d2dy < tolerance(2))
          {
            Step = std::min(Step, StepU / d2dx);
          }
          else
          {
            Step = std::min(Step, std::min(StepU / d2dx, StepV / d2dy));
          }
        }
      }
    }
  }
  return aStatus;
}

#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

void IntWalk_IWalking::AddPointInCurrentLine(
  const int                             N,
  const ThePointOfPath&                 PathPnt,
  const occ::handle<IntWalk_TheIWLine>& CurrentLine) const
{
  IntSurf_PntOn2S Psol;
  Psol.SetValue(ThePointOfPathTool::Value3d(PathPnt), reversed, wd1[N].ustart, wd1[N].vstart);
  CurrentLine->AddPoint(Psol);
}

void IntWalk_IWalking::MakeWalkingPoint(const int        Case,
                                        const double     U,
                                        const double     V,
                                        TheIWFunction&   sp,
                                        IntSurf_PntOn2S& Psol)

{

  if ((Case == 1) || (Case == 2))
  {
    Psol.SetValue(sp.Point(), reversed, U, V);
  }
  else if (Case == 11 || Case == 12)
  {
    double      aUV[2] = {}, aFF[1] = {}, aDD[1][2] = {};
    math_Vector UV(aUV, 1, 2);
    math_Vector FF(aFF, 1, 1);
    math_Matrix DD(aDD, 1, 1, 1, 2);
    UV(1) = U;
    UV(2) = V;
    sp.Values(UV, FF, DD);
    MakeWalkingPoint(Case - 10, U, V, sp, Psol);
  }
  else
  {
    throw Standard_ConstructionError();
  }
}

void IntWalk_IWalking::OpenLine(const int                             N,
                                const IntSurf_PntOn2S&                Psol,
                                const ThePOPIterator&                 Pnts1,
                                TheIWFunction&                        sp,
                                const occ::handle<IntWalk_TheIWLine>& Line)

{
  ThePointOfPath PathPnt;

  double      aUV[2], aFF[1], aDD[1][2];
  math_Vector UV(aUV, 1, 2);
  math_Vector FF(aFF, 1, 1);
  math_Matrix DD(aDD, 1, 1, 1, 2);

  previousPoint = Line->Value(1);
  if (!reversed)
  {
    previousPoint.ParametersOnS2(UV(1), UV(2));
  }
  else
  {
    previousPoint.ParametersOnS1(UV(1), UV(2));
  }
  sp.Values(UV, FF, DD);
  previousd3d = sp.Direction3d();
  previousd2d = sp.Direction2d();

  if (N > 0)
  {
    PathPnt = Pnts1.Value(N);

    Line->AddStatusFirst(false, true, N, PathPnt);

    AddPointInCurrentLine(N, PathPnt, Line);
  }
  else
  {
    if (N < 0)
      Line->AddPoint(Psol);
    Line->AddStatusFirst(false, false);
  }
  Line->Reverse();
  Line->SetTangentVector(previousd3d.Reversed(), Line->NbPoints());
}

bool IntWalk_IWalking::IsValidEndPoint(const int IndOfPoint, const int IndOfLine)
{
  if (PointLineLine.IsEmpty())
    return true;

  NCollection_List<int>::Iterator itl(PointLineLine(IndOfPoint));
  for (; itl.More(); itl.Next())
    if (itl.Value() == IndOfLine)
    {
      PointLineLine(IndOfPoint).Remove(itl);
      return true;
    }
  return false;
}

void IntWalk_IWalking::RemoveTwoEndPoints(const int IndOfPoint)
{
  if (PointLineLine.IsBound(IndOfPoint))
  {
    int Line1 = PointLineLine(IndOfPoint).First();
    int Line2 = PointLineLine(IndOfPoint).Last();
    for (int iseq = 1; iseq <= seqAlone.Length(); iseq++)
    {
      if (seqAlone(iseq) == Line1 || seqAlone(iseq) == Line2)
        seqAlone.Remove(iseq--);
    }
  }
}

bool IntWalk_IWalking::IsPointOnLine(const gp_Pnt2d& theP2d, const int Irang)
{
  const occ::handle<IntWalk_TheIWLine>& aLine = lines.Value(std::abs(Irang));
  for (int i = 1; i <= aLine->NbPoints(); i++)
  {
    gp_Pnt2d P2d1 = aLine->Value(i).ValueOnSurface(reversed);
    if (std::abs(P2d1.X() - theP2d.X()) <= tolerance(1)
        && std::abs(P2d1.Y() - theP2d.Y()) <= tolerance(2))
      return true;
    if (i < aLine->NbPoints())
    {
      gp_Pnt2d P2d2 = aLine->Value(i + 1).ValueOnSurface(reversed);
      gp_Vec2d PP1(theP2d, P2d1);
      gp_Vec2d PP2(theP2d, P2d2);
      if (PP1 * PP2 < 0)
        return true;
    }
  }
  return false;
}

bool IntWalk_IWalking::IsPointOnLine(const IntSurf_PntOn2S& thePOn2S,
                                     const math_Vector&     theInfBounds,
                                     const math_Vector&     theSupBounds,
                                     math_FunctionSetRoot&  theSolver,
                                     TheIWFunction&         theFunc)
{
  const double  eps  = Epsilon(1.);
  const gp_Pnt& aP3d = thePOn2S.Value();

  for (int aLIdx = 1; aLIdx <= lines.Length(); aLIdx++)
  {
    const occ::handle<IntSurf_LineOn2S>& aL = lines(aLIdx)->Line();

    if (aL->IsOutBox(aP3d))
      continue;

    double aUMin = 0.0, aVMin = 0.0;
    double aMinSqDist = RealLast();
    for (int aPtIdx = 1; aPtIdx < aL->NbPoints(); aPtIdx++)
    {
      const gp_Pnt& aP1 = aL->Value(aPtIdx).Value();
      const gp_Pnt& aP2 = aL->Value(aPtIdx + 1).Value();

      const gp_XYZ aP1P(aP3d.XYZ() - aP1.XYZ());
      const gp_XYZ aP1P2(aP2.XYZ() - aP1.XYZ());

      const double aSq12 = aP1P2.SquareModulus();

      if (aSq12 < gp::Resolution())
        continue;

      const double aDP = aP1P.Dot(aP1P2);

      double aSqD = RealLast();
      if (aDP < 0.0)
      {
        continue;
      }
      else if (aDP > aSq12)
      {
        continue;
      }
      else
      {
        aSqD = aP1P.CrossSquareMagnitude(aP1P2) / aSq12;
      }

      if (aSqD < aMinSqDist)
      {
        aMinSqDist = aSqD;

        const double aL1 = aDP / aSq12;
        const double aL2 = 1.0 - aL1;

        if (aL1 < eps || aL2 < eps)
        {
          return true;
        }

        double aU1, aV1, aU2, aV2;
        aL->Value(aPtIdx).ParametersOnSurface(reversed, aU1, aV1);
        aL->Value(aPtIdx + 1).ParametersOnSurface(reversed, aU2, aV2);

        aUMin = aL1 * aU2 + aL2 * aU1;
        aVMin = aL1 * aV2 + aL2 * aV1;
      }
    }

    if (aMinSqDist > Precision::Infinite())
      continue;

    math_Vector aVecPrms(1, 2);
    aVecPrms(1) = aUMin;
    aVecPrms(2) = aVMin;
    theSolver.Perform(theFunc, aVecPrms, theInfBounds, theSupBounds);
    if (!theSolver.IsDone())
      continue;

    theSolver.Root(aVecPrms);

    const gp_Pnt aPa(theFunc.PSurface()->Value(aUMin, aVMin)),
      aPb(theFunc.PSurface()->Value(aVecPrms(1), aVecPrms(2)));
    const double aSqD1 = aPb.SquareDistance(aP3d);
    const double aSqD2 = aPa.SquareDistance(aPb);

    if (aSqD1 < 4.0 * aSqD2)
    {
      return true;
    }
  }

  return false;
}
