#include <Bisector_Bisec.hpp>
#include <Bisector_BisecAna.hpp>
#include <Bisector_BisecCC.hpp>
#include <Bisector_BisecPC.hpp>
#include <Bisector_Curve.hpp>
#include <Bisector_FunctionInter.hpp>
#include <Bisector_Inter.hpp>
#include <ElCLib.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <IntRes2d_Domain.hpp>
#include <IntRes2d_Intersection.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <IntRes2d_Transition.hpp>
#include <math_BissecNewton.hpp>
#include <Precision.hpp>

#ifdef OCCT_DEBUG
#endif

Bisector_Inter::Bisector_Inter() = default;

Bisector_Inter::Bisector_Inter(const Bisector_Bisec&  C1,
                               const IntRes2d_Domain& D1,
                               const Bisector_Bisec&  C2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol,
                               const bool             ComunElement)
{
  Perform(C1, D1, C2, D2, TolConf, Tol, ComunElement);
}

static occ::handle<Geom2d_Line> ConstructSegment(const gp_Pnt2d& PMin,
                                                 const gp_Pnt2d& PMax,
                                                 const double    UMin,

                                                 const double)
{
  gp_Dir2d                 Dir(PMax.X() - PMin.X(), PMax.Y() - PMin.Y());
  occ::handle<Geom2d_Line> L =
    new Geom2d_Line(gp_Pnt2d(PMin.X() - UMin * Dir.X(), PMin.Y() - UMin * Dir.Y()), Dir);
  return L;
}

void Bisector_Inter::Perform(const Bisector_Bisec&  C1,
                             const IntRes2d_Domain& D1,
                             const Bisector_Bisec&  C2,
                             const IntRes2d_Domain& D2,
                             const double           TolConf,
                             const double           Tol,
                             const bool             ComunElement)
{
  occ::handle<Bisector_Curve> Bis1 = occ::down_cast<Bisector_Curve>(C1.Value()->BasisCurve());
  occ::handle<Bisector_Curve> Bis2 = occ::down_cast<Bisector_Curve>(C2.Value()->BasisCurve());

  occ::handle<Geom2d_Curve>* SBis1 = new occ::handle<Geom2d_Curve>[Bis1->NbIntervals() + 1];
  occ::handle<Geom2d_Curve>* SBis2 = new occ::handle<Geom2d_Curve>[Bis2->NbIntervals() + 1];
  IntRes2d_Domain*           SD1   = new IntRes2d_Domain[Bis1->NbIntervals() + 1];
  IntRes2d_Domain*           SD2   = new IntRes2d_Domain[Bis2->NbIntervals() + 1];

  int      NB1 = 0;
  int      NB2 = 0;
  double   MinDomain, MaxDomain;
  double   UMin, UMax;
  gp_Pnt2d PMin, PMax;

  if (D1.HasFirstPoint())
  {
    MinDomain = D1.FirstParameter();
  }
  else
  {
    MinDomain = RealFirst();
  }

  if (D1.HasLastPoint())
  {
    MaxDomain = D1.LastParameter();
  }
  else
  {
    MaxDomain = RealLast();
  }

  int IB1;
  for (IB1 = 1; IB1 <= Bis1->NbIntervals(); IB1++)
  {
    UMin = Bis1->IntervalFirst(IB1);
    UMax = Bis1->IntervalLast(IB1);
    if (UMax > MinDomain && UMin < MaxDomain)
    {
      UMin = std::max(UMin, MinDomain);
      UMax = std::min(UMax, MaxDomain);
      PMin = Bis1->Value(UMin);
      PMax = Bis1->Value(UMax);
      SD1[IB1].SetValues(PMin, UMin, D1.FirstTolerance(), PMax, UMax, D1.LastTolerance());

      if ((IB1 == 1 && Bis1->IsExtendAtStart())
          || (IB1 == Bis1->NbIntervals() && Bis1->IsExtendAtEnd()))
      {

        SBis1[IB1] = ConstructSegment(PMin, PMax, UMin, UMax);
      }
      else
      {
        SBis1[IB1] = Bis1;
      }
      NB1++;
    }
  }

  if (D2.HasFirstPoint())
  {
    MinDomain = D2.FirstParameter();
  }
  else
  {
    MinDomain = RealFirst();
  }

  if (D2.HasLastPoint())
  {
    MaxDomain = D2.LastParameter();
  }
  else
  {
    MaxDomain = RealLast();
  }

  int IB2;
  for (IB2 = 1; IB2 <= Bis2->NbIntervals(); IB2++)
  {
    UMin = Bis2->IntervalFirst(IB2);
    UMax = Bis2->IntervalLast(IB2);
    if (UMax > MinDomain && UMin < MaxDomain)
    {
      UMin = std::max(UMin, MinDomain);
      UMax = std::min(UMax, MaxDomain);
      PMin = Bis2->Value(UMin);
      PMax = Bis2->Value(UMax);
      SD2[IB2].SetValues(PMin, UMin, D2.FirstTolerance(), PMax, UMax, D2.LastTolerance());

      if ((IB2 == 1 && Bis2->IsExtendAtStart())
          || (IB2 == Bis1->NbIntervals() && Bis2->IsExtendAtEnd()))
      {

        SBis2[IB2] = ConstructSegment(PMin, PMax, UMin, UMax);
      }
      else
      {
        SBis2[IB2] = Bis2;
      }
      NB2++;
    }
  }

  for (IB1 = 1; IB1 <= NB1; IB1++)
  {
    for (IB2 = 1; IB2 <= NB2; IB2++)
    {
      SinglePerform(SBis1[IB1], SD1[IB1], SBis2[IB2], SD2[IB2], TolConf, Tol, ComunElement);
    }
  }
  delete[] SBis1;
  delete[] SBis2;
  delete[] SD1;
  delete[] SD2;
}

void Bisector_Inter::SinglePerform(const occ::handle<Geom2d_Curve>& CBis1,
                                   const IntRes2d_Domain&           D1,
                                   const occ::handle<Geom2d_Curve>& CBis2,
                                   const IntRes2d_Domain&           D2,
                                   const double                     TolConf,
                                   const double                     Tol,
                                   const bool                       ComunElement)
{
  const occ::handle<Geom2d_Curve>& Bis1 = CBis1;
  const occ::handle<Geom2d_Curve>& Bis2 = CBis2;

  occ::handle<Standard_Type> Type1 = Bis1->DynamicType();
  occ::handle<Standard_Type> Type2 = Bis2->DynamicType();

  if (Type1 == STANDARD_TYPE(Bisector_BisecAna) || Type2 == STANDARD_TYPE(Bisector_BisecAna))
  {
    occ::handle<Geom2d_Curve> C2Bis1, C2Bis2;
    if (Type1 == STANDARD_TYPE(Bisector_BisecAna))
    {
      C2Bis1 = occ::down_cast<Bisector_BisecAna>(Bis1)->Geom2dCurve();
    }
    else
    {
      C2Bis1 = Bis1;
    }
    if (Type2 == STANDARD_TYPE(Bisector_BisecAna))
    {
      C2Bis2 = occ::down_cast<Bisector_BisecAna>(Bis2)->Geom2dCurve();
    }
    else
    {
      C2Bis2 = Bis2;
    }
    Type1 = C2Bis1->DynamicType();
    Type2 = C2Bis2->DynamicType();
    if (Type1 == STANDARD_TYPE(Geom2d_Line) && Type2 != STANDARD_TYPE(Geom2d_Line))
    {
      TestBound(occ::down_cast<Geom2d_Line>(C2Bis1), D1, C2Bis2, D2, TolConf, false);
    }
    else if (Type2 == STANDARD_TYPE(Geom2d_Line) && Type1 != STANDARD_TYPE(Geom2d_Line))
    {
      TestBound(occ::down_cast<Geom2d_Line>(C2Bis2), D2, C2Bis1, D1, TolConf, true);
    }
    Geom2dInt_GInter    Intersect;
    Geom2dAdaptor_Curve AC2Bis1(C2Bis1);
    Geom2dAdaptor_Curve AC2Bis2(C2Bis2);
    Intersect.Perform(AC2Bis1, D1, AC2Bis2, D2, TolConf, Tol);
    Append(Intersect,
           D1.FirstParameter(),
           D1.LastParameter(),
           D2.FirstParameter(),
           D2.LastParameter());
  }
  else if (Type1 == STANDARD_TYPE(Bisector_BisecPC) || Type2 == STANDARD_TYPE(Bisector_BisecPC))
  {
    Geom2dInt_GInter    Intersect;
    Geom2dAdaptor_Curve ABis1(Bis1);
    Geom2dAdaptor_Curve ABis2(Bis2);
    Intersect.Perform(ABis1, D1, ABis2, D2, TolConf, Tol);
    Append(Intersect,
           D1.FirstParameter(),
           D1.LastParameter(),
           D2.FirstParameter(),
           D2.LastParameter());
  }
  else if (ComunElement && Type1 == STANDARD_TYPE(Bisector_BisecCC)
           && Type2 == STANDARD_TYPE(Bisector_BisecCC))
  {
    NeighbourPerform(occ::down_cast<Bisector_BisecCC>(Bis1),
                     D1,
                     occ::down_cast<Bisector_BisecCC>(Bis2),
                     D2,
                     Tol);
  }
  else
  {

    if (Type1 == STANDARD_TYPE(Geom2d_Line) && Type2 != STANDARD_TYPE(Geom2d_Line))
    {
      TestBound(occ::down_cast<Geom2d_Line>(Bis1), D1, Bis2, D2, TolConf, false);
    }
    else if (Type2 == STANDARD_TYPE(Geom2d_Line) && Type1 != STANDARD_TYPE(Geom2d_Line))
    {
      TestBound(occ::down_cast<Geom2d_Line>(Bis2), D2, Bis1, D1, TolConf, true);
    }
    Geom2dInt_GInter    Intersect;
    Geom2dAdaptor_Curve ABis1(Bis1);
    Geom2dAdaptor_Curve ABis2(Bis2);
    Intersect.Perform(ABis1, D1, ABis2, D2, TolConf, Tol);
    Append(Intersect,
           D1.FirstParameter(),
           D1.LastParameter(),
           D2.FirstParameter(),
           D2.LastParameter());
  }
}

void Bisector_Inter::NeighbourPerform(const occ::handle<Bisector_BisecCC>& Bis1,
                                      const IntRes2d_Domain&               D1,
                                      const occ::handle<Bisector_BisecCC>& Bis2,
                                      const IntRes2d_Domain&               D2,
                                      const double                         Tol)
{
  double           USol, U1, U2, Dist;
  double           UMin = 0., UMax = 0.;
  constexpr double Eps = Precision::PConfusion();
  gp_Pnt2d         PSol;

  occ::handle<Geom2d_Curve>     Guide;
  occ::handle<Bisector_BisecCC> BisTemp;

  BisTemp = Bis2->ChangeGuide();
  Guide   = Bis2->Curve(2);

  gp_Pnt2d P2S = Bis2->ValueAndDist(D2.FirstParameter(), U1, UMax, Dist);
  gp_Pnt2d P2E = Bis2->ValueAndDist(D2.LastParameter(), U1, UMin, Dist);
  (void)P2S;
  (void)P2E;

  UMin = std::max(D1.FirstParameter(), UMin);
  UMax = std::min(D1.LastParameter(), UMax);

  done = true;

  if (UMin - Eps > UMax + Eps)
  {
    return;
  }

  Bisector_FunctionInter Fint(Guide, Bis1, BisTemp);

  math_BissecNewton aSolution(Tol);
  aSolution.Perform(Fint, UMin, UMax, 20);

  if (aSolution.IsDone())
    USol = aSolution.Root();
  else
    return;

  PSol = BisTemp->ValueAndDist(USol, U1, U2, Dist);

  IntRes2d_Transition        Trans1, Trans2;
  IntRes2d_IntersectionPoint PointInterSol(PSol, USol, U2, Trans1, Trans2, false);
  Append(PointInterSol);
}

void Bisector_Inter::TestBound(const occ::handle<Geom2d_Line>&  Bis1,
                               const IntRes2d_Domain&           D1,
                               const occ::handle<Geom2d_Curve>& Bis2,
                               const IntRes2d_Domain&           D2,
                               const double                     TolConf,
                               const bool                       Reverse)
{
  IntRes2d_Transition        Trans1, Trans2;
  IntRes2d_IntersectionPoint PointInterSol;

  gp_Lin2d L1 = Bis1->Lin2d();
  gp_Pnt2d PF = Bis2->Value(D2.FirstParameter());
  gp_Pnt2d PL = Bis2->Value(D2.LastParameter());

  double Tol = TolConf;

  bool BisecAlgo = false;
  if (Bis2->DynamicType() == STANDARD_TYPE(Bisector_BisecCC))
  {
    BisecAlgo = true;
  }

  if (L1.Distance(PF) < Tol)
  {
    double U1 = ElCLib::Parameter(L1, PF);

    if (D1.FirstParameter() - D1.FirstTolerance() < U1
        && D1.LastParameter() + D1.LastTolerance() > U1)
    {

      if (BisecAlgo)
        PF = ElCLib::Value(U1, L1);
      PointInterSol.SetValues(PF, U1, D2.FirstParameter(), Trans1, Trans2, Reverse);
      Append(PointInterSol);
    }
  }

  if (L1.Distance(PL) < Tol)
  {
    double U1 = ElCLib::Parameter(L1, PL);

    if (D1.FirstParameter() - D1.FirstTolerance() < U1
        && D1.LastParameter() + D1.LastTolerance() > U1)
    {

      if (BisecAlgo)
        PL = ElCLib::Value(U1, L1);
      PointInterSol.SetValues(PL, U1, D2.LastParameter(), Trans1, Trans2, Reverse);
      Append(PointInterSol);
    }
  }
}
