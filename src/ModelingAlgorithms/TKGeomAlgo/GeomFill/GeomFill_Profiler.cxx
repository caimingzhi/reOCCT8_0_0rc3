#include <BSplCLib.hpp>
#include <Geom_Conic.hpp>
#include <Geom_Curve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomConvert.hpp>
#include <GeomConvert_ApproxCurve.hpp>
#include <GeomFill_Profiler.hpp>
#include <Standard_DomainError.hpp>
#include <StdFail_NotDone.hpp>

static void UnifyByInsertingAllKnots(NCollection_Sequence<occ::handle<Geom_Curve>>& theCurves,
                                     const double                                   PTol)
{

  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(theCurves(1));

  int i;
  for (i = 2; i <= theCurves.Length(); i++)
  {
    occ::handle<Geom_BSplineCurve> Ci = occ::down_cast<Geom_BSplineCurve>(theCurves(i));
    NCollection_Array1<double>     Ki(1, Ci->NbKnots());
    Ci->Knots(Ki);
    NCollection_Array1<int> Mi(1, Ci->NbKnots());
    Ci->Multiplicities(Mi);

    C->InsertKnots(Ki, Mi, PTol, false);
  }

  NCollection_Array1<double> NewKnots(1, C->NbKnots());
  C->Knots(NewKnots);
  NCollection_Array1<int> NewMults(1, C->NbKnots());
  C->Multiplicities(NewMults);
  for (i = 2; i <= theCurves.Length(); i++)
  {
    occ::handle<Geom_BSplineCurve> Ci = occ::down_cast<Geom_BSplineCurve>(theCurves(i));
    Ci->InsertKnots(NewKnots, NewMults, PTol, false);
  }

  for (i = 1; i <= theCurves.Length(); i++)
  {
    occ::handle<Geom_BSplineCurve> Ci = occ::down_cast<Geom_BSplineCurve>(theCurves(i));
    if (Ci->IsRational())
    {
      int    np    = Ci->NbPoles();
      double sigma = 0.;
      int    j;
      for (j = 1; j <= np; j++)
      {
        sigma += Ci->Weight(j);
      }
      sigma /= np;
      for (j = 1; j <= np; j++)
      {
        Ci->SetWeight(j, Ci->Weight(j) / sigma);
      }
    }
  }
}

static void UnifyBySettingMiddleKnots(NCollection_Sequence<occ::handle<Geom_Curve>>& theCurves)
{
  int i, j;

  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(theCurves(1));

  int    NbKnots = C->NbKnots();
  double ULast   = C->Knot(C->LastUKnotIndex());
  double UFirst  = C->Knot(C->FirstUKnotIndex());

  NCollection_Array1<double> NewKnots(1, NbKnots);
  NewKnots(1)       = UFirst;
  NewKnots(NbKnots) = ULast;
  for (j = 2; j < NbKnots; j++)
  {
    double aMidKnot = 0.;
    for (i = 1; i <= theCurves.Length(); i++)
    {
      occ::handle<Geom_BSplineCurve> Ctemp = occ::down_cast<Geom_BSplineCurve>(theCurves(i));
      aMidKnot += Ctemp->Knot(j);
    }
    aMidKnot /= theCurves.Length();
    NewKnots(j) = aMidKnot;
  }

  for (i = 1; i <= theCurves.Length(); i++)
  {
    occ::handle<Geom_BSplineCurve> Cres = occ::down_cast<Geom_BSplineCurve>(theCurves(i));
    Cres->SetKnots(NewKnots);
  }
}

GeomFill_Profiler::GeomFill_Profiler()
{
  myIsDone     = false;
  myIsPeriodic = true;
}

GeomFill_Profiler::~GeomFill_Profiler() = default;

void GeomFill_Profiler::AddCurve(const occ::handle<Geom_Curve>& Curve)
{
  occ::handle<Geom_Curve> C;

  occ::handle<Geom_Curve> theCurve = Curve;
  if (theCurve->IsInstance(STANDARD_TYPE(Geom_TrimmedCurve)))
    theCurve = occ::down_cast<Geom_TrimmedCurve>(theCurve)->BasisCurve();
  if (theCurve->IsKind(STANDARD_TYPE(Geom_Conic)))
  {
    GeomConvert_ApproxCurve appr(Curve, Precision::Confusion(), GeomAbs_C1, 16, 14);
    if (appr.HasResult())
      C = appr.Curve();
  }
  if (C.IsNull())
    C = GeomConvert::CurveToBSplineCurve(Curve);

  mySequence.Append(C);

  if (myIsPeriodic && !C->IsPeriodic())
    myIsPeriodic = false;
}

void GeomFill_Profiler::Perform(const double PTol)
{
  int i;

  int                            myDegree = 0;
  occ::handle<Geom_BSplineCurve> C;
  double                         U1, U2, UFirst = 0, ULast = 0;
  double                         EcartMax = 0.;

  for (i = 1; i <= mySequence.Length(); i++)
  {
    C = occ::down_cast<Geom_BSplineCurve>(mySequence(i));

    U2 = C->Knot(C->LastUKnotIndex());
    U1 = C->Knot(C->FirstUKnotIndex());

    if (!myIsPeriodic && C->IsPeriodic())
    {
      C->SetNotPeriodic();
      C->Segment(U1, U2);
    }

    myDegree = std::max(myDegree, C->Degree());

    if ((U2 - U1) > EcartMax)
    {
      EcartMax = U2 - U1;
      UFirst   = U1;
      ULast    = U2;
    }
  }

  for (i = 1; i <= mySequence.Length(); i++)
  {
    C = occ::down_cast<Geom_BSplineCurve>(mySequence(i));

    C->IncreaseDegree(myDegree);

    NCollection_Array1<double> Knots(1, C->NbKnots());
    C->Knots(Knots);
    BSplCLib::Reparametrize(UFirst, ULast, Knots);
    C->SetKnots(Knots);
  }

  NCollection_Sequence<occ::handle<Geom_Curve>> theCurves;
  for (i = 1; i <= mySequence.Length(); i++)
    theCurves.Append(occ::down_cast<Geom_Curve>(mySequence(i)->Copy()));

  UnifyByInsertingAllKnots(theCurves, PTol);

  bool Unified    = true;
  int  theNbKnots = (occ::down_cast<Geom_BSplineCurve>(theCurves(1)))->NbKnots();
  for (i = 2; i <= theCurves.Length(); i++)
    if ((occ::down_cast<Geom_BSplineCurve>(theCurves(i)))->NbKnots() != theNbKnots)
    {
      Unified = false;
      break;
    }

  if (Unified)
    mySequence = theCurves;
  else
    UnifyBySettingMiddleKnots(mySequence);

  myIsDone = true;
}

int GeomFill_Profiler::Degree() const
{
  if (!myIsDone)
    throw StdFail_NotDone("GeomFill_Profiler::Degree");

  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(mySequence(1));
  return C->Degree();
}

int GeomFill_Profiler::NbPoles() const
{
  if (!myIsDone)
    throw StdFail_NotDone("GeomFill_Profiler::Degree");

  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(mySequence(1));
  return C->NbPoles();
}

void GeomFill_Profiler::Poles(const int Index, NCollection_Array1<gp_Pnt>& Poles) const
{
  if (!myIsDone)
    throw StdFail_NotDone("GeomFill_Profiler::Degree");

  Standard_DomainError_Raise_if(Poles.Length() != NbPoles(), "GeomFill_Profiler::Poles");
  Standard_DomainError_Raise_if(Index < 1 || Index > mySequence.Length(),
                                "GeomFill_Profiler::Poles");

  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(mySequence(Index));

  C->Poles(Poles);
}

void GeomFill_Profiler::Weights(const int Index, NCollection_Array1<double>& Weights) const
{
  if (!myIsDone)
    throw StdFail_NotDone("GeomFill_Profiler::Degree");

  Standard_DomainError_Raise_if(Weights.Length() != NbPoles(), "GeomFill_Profiler::Weights");
  Standard_DomainError_Raise_if(Index < 1 || Index > mySequence.Length(),
                                "GeomFill_Profiler::Weights");

  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(mySequence(Index));

  C->Weights(Weights);
}

int GeomFill_Profiler::NbKnots() const
{
  if (!myIsDone)
    throw StdFail_NotDone("GeomFill_Profiler::Degree");

  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(mySequence(1));

  return C->NbKnots();
}

void GeomFill_Profiler::KnotsAndMults(NCollection_Array1<double>& Knots,
                                      NCollection_Array1<int>&    Mults) const
{
  if (!myIsDone)
    throw StdFail_NotDone("GeomFill_Profiler::Degree");

#ifndef No_Exception
  int n = NbKnots();
#endif
  Standard_DomainError_Raise_if(Knots.Length() != n || Mults.Length() != n,
                                "GeomFill_Profiler::KnotsAndMults");

  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(mySequence(1));

  C->Knots(Knots);
  C->Multiplicities(Mults);
}
