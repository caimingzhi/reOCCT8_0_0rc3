#include <GeomFill_GuideTrihedronPlan.hpp>

#include <Adaptor3d_Curve.hpp>
#include <ElCLib.hpp>
#include <Geom_Plane.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomFill_Frenet.hpp>
#include <GeomFill_PlanFunc.hpp>
#include <GeomFill_TrihedronLaw.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <IntCurveSurface_HInter.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <math_FunctionRoot.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_GuideTrihedronPlan, GeomFill_TrihedronWithGuide)

#ifdef OCCT_DEBUG
static void TracePlan(const occ::handle<Geom_Surface>&)
{
  std::cout << "Pas d'intersection Guide/Plan" << std::endl;
}
#endif

static void InGoodPeriod(const double Prec, const double Period, double& Current)
{
  double Diff = Current - Prec;
  int    nb   = (int)std::trunc(Diff / Period);
  Current -= nb * Period;
  Diff = Current - Prec;
  if (Diff > Period / 2)
    Current -= Period;
  else if (Diff < -Period / 2)
    Current += Period;
}

GeomFill_GuideTrihedronPlan::GeomFill_GuideTrihedronPlan(
  const occ::handle<Adaptor3d_Curve>& theGuide)
    : X(1, 1),
      XTol(1, 1),
      Inf(1, 1),
      Sup(1, 1),
      myStatus(GeomFill_PipeOk)
{
  myCurve.Nullify();
  myGuide = theGuide;
  myTrimG = theGuide;
  myNbPts = 20;
  Pole    = new (NCollection_HArray2<gp_Pnt2d>)(1, 1, 1, myNbPts);
  frenet  = new (GeomFill_Frenet)();
  XTol.Init(1.e-6);
  XTol(1) = myGuide->Resolution(1.e-6);
}

void GeomFill_GuideTrihedronPlan::Init()
{
  myStatus = GeomFill_PipeOk;
  gp_Pnt P;

  gp_Vec Tangent, Normal, BiNormal;
  int    ii;
  double t, DeltaG, w = 0.;
  double f = myCurve->FirstParameter();
  double l = myCurve->LastParameter();

  occ::handle<Geom_Plane>           Plan;
  occ::handle<GeomAdaptor_Surface>  Pl;
  IntCurveSurface_IntersectionPoint PInt;
  IntCurveSurface_HInter            Int;
  frenet->SetCurve(myCurve);
  DeltaG = (myGuide->LastParameter() - myGuide->FirstParameter()) / 2;

  Inf(1) = myGuide->FirstParameter() - DeltaG;
  Sup(1) = myGuide->LastParameter() + DeltaG;

  if (!myGuide->IsPeriodic())
  {
    myTrimG = myGuide->Trim(myGuide->FirstParameter() - DeltaG / 100,
                            myGuide->LastParameter() + DeltaG / 100,
                            DeltaG * 1.e-7);
  }
  else
  {
    myTrimG = myGuide;
  }

  DeltaG /= 3;
  for (ii = 1; ii <= myNbPts; ii++)
  {
    t = double(myNbPts - ii) * f + double(ii - 1) * l;
    t /= (myNbPts - 1);
    myCurve->D0(t, P);
    frenet->D0(t, Tangent, Normal, BiNormal);
    Plan = new (Geom_Plane)(P, Tangent);
    Pl   = new (GeomAdaptor_Surface)(Plan);

    Int.Perform(myTrimG, Pl);
    if (Int.NbPoints() == 0)
    {
#ifdef OCCT_DEBUG
      TracePlan(Plan);
#endif
      w = (fabs(myGuide->LastParameter() - w) > fabs(myGuide->FirstParameter() - w)
             ? myGuide->FirstParameter()
             : myGuide->LastParameter());

      myStatus = GeomFill_PlaneNotIntersectGuide;
    }
    else
    {
      gp_Pnt Pmin;
      PInt        = Int.Point(1);
      Pmin        = PInt.Pnt();
      double Dmin = P.Distance(Pmin);
      for (int jj = 2; jj <= Int.NbPoints(); jj++)
      {
        Pmin = Int.Point(jj).Pnt();
        if (P.Distance(Pmin) < Dmin)
        {
          PInt = Int.Point(jj);
          Dmin = P.Distance(Pmin);
        }
      }

      w = PInt.W();
    }
    if (ii > 1)
    {
      double Diff = w - Pole->Value(1, ii - 1).Y();
      if (std::abs(Diff) > DeltaG)
      {
        if (myGuide->IsPeriodic())
        {
          InGoodPeriod(Pole->Value(1, ii - 1).Y(), myGuide->Period(), w);

          Diff = w - Pole->Value(1, ii - 1).Y();
        }
      }

#ifdef OCCT_DEBUG
      if (std::abs(Diff) > DeltaG)
      {
        std::cout << "Trihedron Plan Diff on Guide : " << Diff << std::endl;
      }
#endif
    }

    gp_Pnt2d p1(t, w);
    Pole->SetValue(1, ii, p1);
  }
}

bool GeomFill_GuideTrihedronPlan::SetCurve(const occ::handle<Adaptor3d_Curve>& C)
{
  myCurve = C;
  if (!myCurve.IsNull())
    Init();
  return true;
}

occ::handle<Adaptor3d_Curve> GeomFill_GuideTrihedronPlan::Guide() const
{
  return myGuide;
}

bool GeomFill_GuideTrihedronPlan::D0(const double Param,
                                     gp_Vec&      Tangent,
                                     gp_Vec&      Normal,
                                     gp_Vec&      BiNormal)
{
  gp_Pnt P, Pprime;

  myCurve->D0(Param, P);

  frenet->D0(Param, Tangent, Normal, BiNormal);

  InitX(Param);

  int Iter = 50;

  GeomFill_PlanFunc E(P, Tangent, myGuide);

  math_FunctionRoot Result(E, X(1), XTol(1), Inf(1), Sup(1), Iter);

  if (Result.IsDone())
  {
    double Res = Result.Root();

    Pprime = myTrimG->Value(Res);
    gp_Vec n(P, Pprime);

    Normal   = n.Normalized();
    BiNormal = Tangent.Crossed(Normal);
    BiNormal.Normalize();
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "D0 :";

    occ::handle<Geom_Plane> Plan = new (Geom_Plane)(P, Tangent);
    TracePlan(Plan);
#endif
    myStatus = GeomFill_PlaneNotIntersectGuide;
    return false;
  }

  return true;
}

bool GeomFill_GuideTrihedronPlan::D1(const double Param,
                                     gp_Vec&      Tangent,
                                     gp_Vec&      DTangent,
                                     gp_Vec&      Normal,
                                     gp_Vec&      DNormal,
                                     gp_Vec&      BiNormal,
                                     gp_Vec&      DBiNormal)
{

  gp_Pnt P, PG;
  gp_Vec To, TG;

  myCurve->D1(Param, P, To);
  frenet->D1(Param, Tangent, DTangent, Normal, DNormal, BiNormal, DBiNormal);

  int Iter = 50;

  InitX(Param);
  GeomFill_PlanFunc E(P, Tangent, myGuide);

  math_FunctionRoot Result(E, X(1), XTol(1), Inf(1), Sup(1), Iter);

  if (Result.IsDone())
  {
    double Res = Result.Root();

    myTrimG->D1(Res, PG, TG);
    gp_Vec n(P, PG), dn;
    double Norm = n.Magnitude();
    if (Norm < 1.e-12)
    {
      Norm = 1.0;
    }
    n /= Norm;

    Normal   = n;
    BiNormal = Tangent.Crossed(Normal);

    double dedx, dedt, dtg_dt;
    E.Derivative(Res, dedx);
    E.DEDT(Res, To, DTangent, dedt);
    dtg_dt = -dedt / dedx;

    dn.SetLinearForm(dtg_dt, TG, -1, To);

    DNormal.SetLinearForm(-(n * dn), n, dn);
    DNormal /= Norm;
    DBiNormal.SetLinearForm(Tangent.Crossed(DNormal), DTangent.Crossed(Normal));
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "D1 :";

    occ::handle<Geom_Plane> Plan = new (Geom_Plane)(P, Tangent);
    TracePlan(Plan);
#endif
    myStatus = GeomFill_PlaneNotIntersectGuide;
    return false;
  }

  return true;
}

bool GeomFill_GuideTrihedronPlan::D2(const double Param,
                                     gp_Vec&      Tangent,
                                     gp_Vec&      DTangent,
                                     gp_Vec&      D2Tangent,
                                     gp_Vec&      Normal,
                                     gp_Vec&      DNormal,
                                     gp_Vec&      D2Normal,
                                     gp_Vec&      BiNormal,
                                     gp_Vec&      DBiNormal,
                                     gp_Vec&      D2BiNormal)
{

  gp_Pnt P;

  gp_Vec To, DTo;

  myCurve->D2(Param, P, To, DTo);

  frenet->D2(Param,
             Tangent,
             DTangent,
             D2Tangent,
             Normal,
             DNormal,
             D2Normal,
             BiNormal,
             DBiNormal,
             D2BiNormal);

  return false;
}

occ::handle<GeomFill_TrihedronLaw> GeomFill_GuideTrihedronPlan::Copy() const
{
  occ::handle<GeomFill_GuideTrihedronPlan> copy = new (GeomFill_GuideTrihedronPlan)(myGuide);
  copy->SetCurve(myCurve);
  return copy;
}

GeomFill_PipeError GeomFill_GuideTrihedronPlan::ErrorStatus() const
{
  return myStatus;
}

int GeomFill_GuideTrihedronPlan::NbIntervals(const GeomAbs_Shape S) const
{
  int           Nb;
  GeomAbs_Shape tmpS;
  switch (S)
  {
    case GeomAbs_C0:
      tmpS = GeomAbs_C1;
      break;
    case GeomAbs_C1:
      tmpS = GeomAbs_C2;
      break;
    case GeomAbs_C2:
      tmpS = GeomAbs_C3;
      break;
    default:
      tmpS = GeomAbs_CN;
  }

  Nb = myCurve->NbIntervals(tmpS);
  return Nb;
}

void GeomFill_GuideTrihedronPlan::Intervals(NCollection_Array1<double>& TT,
                                            const GeomAbs_Shape         S) const
{
  GeomAbs_Shape tmpS;
  switch (S)
  {
    case GeomAbs_C0:
      tmpS = GeomAbs_C1;
      break;
    case GeomAbs_C1:
      tmpS = GeomAbs_C2;
      break;
    case GeomAbs_C2:
      tmpS = GeomAbs_C3;
      break;
    default:
      tmpS = GeomAbs_CN;
  }
  myCurve->Intervals(TT, tmpS);
}

void GeomFill_GuideTrihedronPlan::SetInterval(const double First, const double Last)
{
  myTrimmed = myCurve->Trim(First, Last, Precision::Confusion());
}

void GeomFill_GuideTrihedronPlan::GetAverageLaw(gp_Vec& ATangent,
                                                gp_Vec& ANormal,
                                                gp_Vec& ABiNormal)
{
  int    ii;
  double t, Delta = (myCurve->LastParameter() - myCurve->FirstParameter()) / 20.001;

  ATangent.SetCoord(0., 0., 0.);
  ANormal.SetCoord(0., 0., 0.);
  ABiNormal.SetCoord(0., 0., 0.);
  gp_Vec T, N, B;

  for (ii = 1; ii <= 20; ii++)
  {
    t = myCurve->FirstParameter() + (ii - 1) * Delta;
    D0(t, T, N, B);
    ATangent += T;
    ANormal += N;
    ABiNormal += B;
  }
  ATangent /= 20;
  ANormal /= 20;
  ABiNormal /= 20;
}

bool GeomFill_GuideTrihedronPlan::IsConstant() const
{
  if ((myCurve->GetType() == GeomAbs_Line) && (myGuide->GetType() == GeomAbs_Line))
  {
    double Angle;
    Angle = myCurve->Line().Angle(myGuide->Line());
    if ((Angle < 1.e-12) || ((2 * M_PI - Angle) < 1.e-12))
      return true;
  }

  return false;
}

bool GeomFill_GuideTrihedronPlan::IsOnlyBy3dCurve() const
{
  return false;
}

void GeomFill_GuideTrihedronPlan::Origine(const double, const double) {}

void GeomFill_GuideTrihedronPlan::InitX(const double Param)
{

  int    Ideb = 1, Ifin = Pole->RowLength(), Idemi;
  double Valeur, t1, t2;

  Valeur = Pole->Value(1, Ideb).X();
  if (Param == Valeur)
  {
    Ifin = Ideb + 1;
  }

  Valeur = Pole->Value(1, Ifin).X();
  if (Param == Valeur)
  {
    Ideb = Ifin - 1;
  }

  while (Ideb + 1 != Ifin)
  {
    Idemi  = (Ideb + Ifin) / 2;
    Valeur = Pole->Value(1, Idemi).X();
    if (Valeur < Param)
    {
      Ideb = Idemi;
    }
    else
    {
      if (Valeur > Param)
      {
        Ifin = Idemi;
      }
      else
      {
        Ideb = Idemi;
        Ifin = Ideb + 1;
      }
    }
  }

  t1          = Pole->Value(1, Ideb).X();
  t2          = Pole->Value(1, Ifin).X();
  double diff = t2 - t1;
  if (diff > 1.e-7)
  {
    double b = (Param - t1) / diff, a = (t2 - Param) / diff;

    X(1) = Pole->Value(1, Ideb).Coord(2) * a + Pole->Value(1, Ifin).Coord(2) * b;
  }
  else
  {
    X(1) = (Pole->Value(1, Ideb).Coord(2) + Pole->Value(1, Ifin).Coord(2)) / 2;
  }
  if (myGuide->IsPeriodic())
  {
    X(1) = ElCLib::InPeriod(X(1), myGuide->FirstParameter(), myGuide->LastParameter());
  }
}
