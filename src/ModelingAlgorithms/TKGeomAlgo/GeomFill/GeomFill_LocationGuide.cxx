#include <GeomFill_LocationGuide.hpp>

#include <Adaptor3d_Curve.hpp>
#include <ElCLib.hpp>
#include <Extrema_ExtCS.hpp>
#include <Extrema_POnSurf.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomFill_FunctionGuide.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <GeomFill_SectionPlacement.hpp>
#include <GeomFill_TrihedronWithGuide.hpp>
#include <GeomFill_UniformSection.hpp>
#include <GeomLib.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Mat.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <math_FunctionSetRoot.hpp>
#include <math_Gauss.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_LocationGuide, GeomFill_LocationLaw)

#ifdef OCCT_DEBUG
static void TraceRevol(const double                                    t,
                       const double                                    s,
                       const occ::handle<GeomFill_TrihedronWithGuide>& Law,
                       const occ::handle<GeomFill_SectionLaw>&         Section,
                       const occ::handle<Adaptor3d_Curve>&             Curve,
                       const gp_Mat&                                   Trans)

{
  gp_Vec T, N, B;
  gp_Pnt P;
  gp_Ax3 Rep(gp::Origin(), gp::DZ(), gp::DX());

  Curve->D0(t, P);
  Law->D0(t, T, N, B);

  gp_Mat M(N.XYZ(), B.XYZ(), T.XYZ());
  M *= Trans;

  gp_Dir D = M.Column(3);
  gp_Ax1 Ax(P, D);

  gp_Dir  N2 = N;
  gp_Ax3  N3(P, D, N2);
  gp_Trsf Transfo;
  Transfo.SetTransformation(N3, Rep);

  double                  f, l, e = 1.e-7;
  occ::handle<Geom_Curve> S, C;

  if (Section->IsConstant(e))
  {
    C = Section->ConstantSection();
  }
  else
  {
    int NbPoles, NbKnots, Deg;
    Section->SectionShape(NbPoles, NbKnots, Deg);
    NCollection_Array1<int> Mult(1, NbKnots);
    Section->Mults(Mult);
    NCollection_Array1<double> Knots(1, NbKnots);
    Section->Knots(Knots);
    NCollection_Array1<gp_Pnt> Poles(1, NbPoles);
    NCollection_Array1<double> Weights(1, NbPoles);
    Section->D0(s, Poles, Weights);
    if (Section->IsRational())
      C = new (Geom_BSplineCurve)(Poles, Weights, Knots, Mult, Deg, Section->IsUPeriodic());
    else
      C = new (Geom_BSplineCurve)(Poles, Knots, Mult, Deg, Section->IsUPeriodic());
  }

  f = C->FirstParameter();
  l = C->LastParameter();
  S = new (Geom_TrimmedCurve)(C, f, l);
  S->Transform(Transfo);

  occ::handle<Geom_Surface> Revol = new (Geom_SurfaceOfRevolution)(S, Ax);
  std::cout << "Surf Revol at parameter t = " << t << std::endl;
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

GeomFill_LocationGuide::GeomFill_LocationGuide(
  const occ::handle<GeomFill_TrihedronWithGuide>& Triedre)
    : TolRes(1, 3),
      Inf(1, 3, 0.),
      Sup(1, 3, 0.),
      X(1, 3),
      R(1, 3),
      myStatus(GeomFill_PipeOk)
{
  TolRes.Init(1.e-6);
  myLaw = Triedre;
  mySec.Nullify();
  myCurve.Nullify();
  myFirstS = myLastS = -505e77;

  myNbPts = 21;
  myGuide = myLaw->Guide();
  if (!myGuide->IsPeriodic())
  {
    double f, l, delta;
    f     = myGuide->FirstParameter();
    l     = myGuide->LastParameter();
    delta = (l - f) / 100;
    f -= delta;
    l += delta;
    myGuide = myGuide->Trim(f, l, delta * 1.e-7);
  }

  myPoles2d  = new (NCollection_HArray2<gp_Pnt2d>)(1, 2, 1, myNbPts);
  rotation   = false;
  OrigParam1 = 0;
  OrigParam2 = 1;
  Trans.SetIdentity();
  WithTrans = false;
}

void GeomFill_LocationGuide::SetRotation(const double PrecAngle, double& LastAngle)
{
  if (myCurve.IsNull())
    throw Standard_ConstructionError("GeomFill_LocationGuide::The path is not set !!");

  gp_Ax3 Rep(gp::Origin(), gp::DZ(), gp::DX());

  gp_Pnt                                   P;
  gp_Vec                                   T, N, B;
  int                                      ii, Deg;
  bool                                     isconst, israt = false;
  double                                   t, v, w, OldAngle = 0, Angle, DeltaG, Diff;
  double                                   CurAngle = PrecAngle, a1;
  gp_Pnt2d                                 p1, p2;
  occ::handle<Geom_SurfaceOfRevolution>    Revol;
  occ::handle<GeomAdaptor_Surface>         Pl;
  occ::handle<Geom_TrimmedCurve>           S;
  IntCurveSurface_IntersectionPoint        PInt;
  occ::handle<NCollection_HArray1<int>>    Mult;
  occ::handle<NCollection_HArray1<double>> Knots, Weights;
  occ::handle<NCollection_HArray1<gp_Pnt>> Poles;

  double U = 0, UPeriod = 0;
  double f = myCurve->FirstParameter();
  double l = myCurve->LastParameter();
  bool   Ok, uperiodic = mySec->IsUPeriodic();

  DeltaG = (myGuide->LastParameter() - myGuide->FirstParameter()) / 5;
  occ::handle<Geom_Curve> mySection;
  double                  Tol = 1.e-9;

  int NbPoles, NbKnots;
  mySec->SectionShape(NbPoles, NbKnots, Deg);

  if (mySec->IsConstant(Tol))
  {
    mySection = mySec->ConstantSection();
    Uf        = mySection->FirstParameter();
    Ul        = mySection->LastParameter();

    isconst = true;
  }
  else
  {
    isconst = false;
    israt   = mySec->IsRational();
    Mult    = new (NCollection_HArray1<int>)(1, NbKnots);
    mySec->Mults(Mult->ChangeArray1());
    Knots = new (NCollection_HArray1<double>)(1, NbKnots);
    mySec->Knots(Knots->ChangeArray1());
    Poles   = new (NCollection_HArray1<gp_Pnt>)(1, NbPoles);
    Weights = new (NCollection_HArray1<double>)(1, NbPoles);
    Uf      = Knots->Value(1);
    Ul      = Knots->Value(NbKnots);
  }

  double Delta;

  Delta  = myGuide->LastParameter() - myGuide->FirstParameter();
  Inf(1) = myGuide->FirstParameter() - Delta / 10;
  Sup(1) = myGuide->LastParameter() + Delta / 10;

  Inf(2) = -M_PI;
  Sup(2) = 3 * M_PI;

  Delta  = Ul - Uf;
  Inf(3) = Uf - Delta / 10;
  Sup(3) = Ul + Delta / 10;

  if (uperiodic)
    UPeriod = Ul - Uf;

  for (ii = 1; ii <= myNbPts; ii++)
  {
    t = double(myNbPts - ii) * f + double(ii - 1) * l;
    t /= (myNbPts - 1);
    myCurve->D0(t, P);
    Ok = myLaw->D0(t, T, N, B);
    if (!Ok)
    {
      myStatus = myLaw->ErrorStatus();
      return;
    }
    gp_Dir D = T;
    if (WithTrans)
    {
      gp_Mat M(N.XYZ(), B.XYZ(), T.XYZ());
      M *= Trans;
      D = M.Column(3);
    }
    gp_Ax1 Ax(P, D);

    gp_Dir  N2 = N;
    gp_Ax3  N3(P, D, N2);
    gp_Trsf Transfo;
    Transfo.SetTransformation(N3, Rep);

    if (!isconst)
    {
      U = myFirstS + (t - myCurve->FirstParameter()) * ratio;
      mySec->D0(U, Poles->ChangeArray1(), Weights->ChangeArray1());
      if (israt)
        mySection = new (Geom_BSplineCurve)(Poles->Array1(),
                                            Weights->Array1(),
                                            Knots->Array1(),
                                            Mult->Array1(),
                                            Deg,
                                            mySec->IsUPeriodic());
      else
        mySection = new (Geom_BSplineCurve)(Poles->Array1(),
                                            Knots->Array1(),
                                            Mult->Array1(),
                                            Deg,
                                            mySec->IsUPeriodic());
      S = new (Geom_TrimmedCurve)(mySection, Uf, Ul);
    }
    else
    {
      S = new (Geom_TrimmedCurve)(occ::down_cast<Geom_Curve>(mySection->Copy()), Uf, Ul);
    }
    S->Transform(Transfo);

    Revol = new (Geom_SurfaceOfRevolution)(S, Ax);

    GeomAdaptor_Surface GArevol(Revol);
    Extrema_ExtCS       DistMini(*myGuide, GArevol, Precision::Confusion(), Precision::Confusion());
    Extrema_POnCurv     Pc;
    Extrema_POnSurf     Ps;
    double              theU = 0., theV = 0.;

    if (!DistMini.IsDone() || DistMini.NbExt() == 0)
    {
#ifdef OCCT_DEBUG
      std::cout << "LocationGuide : Pas d'intersection" << std::endl;
      TraceRevol(t, U, myLaw, mySec, myCurve, Trans);
#endif
      bool SOS = false;
      if (ii > 1)
      {

        X(1) = myPoles2d->Value(1, ii - 1).Y();
        X(2) = myPoles2d->Value(2, ii - 1).X();
        X(3) = myPoles2d->Value(2, ii - 1).Y();
        GeomFill_FunctionGuide E(mySec, myGuide, U);
        E.SetParam(U, P, T.XYZ(), N.XYZ());

        math_FunctionSetRoot Result(E, TolRes);
        Result.Perform(E, X, Inf, Sup);

        if (Result.IsDone() && (Result.FunctionSetErrors().Norm() < TolRes(1) * TolRes(1)))
        {
#ifdef OCCT_DEBUG
          std::cout << "Ratrappage Reussi !" << std::endl;
#endif
          SOS = true;
          math_Vector RR(1, 3);
          Result.Root(RR);
          PInt.SetValues(P, RR(2), RR(3), RR(1), IntCurveSurface_Out);
          theU = PInt.U();
          theV = PInt.V();
        }
        else
        {
#ifdef OCCT_DEBUG
          std::cout << "Echec du Ratrappage !" << std::endl;
#endif
        }
      }
      if (!SOS)
      {
        myStatus = GeomFill_ImpossibleContact;
        return;
      }
    }
    else
    {

      double MinDist = RealLast();
      int    jref    = 0;
      for (int j = 1; j <= DistMini.NbExt(); j++)
      {
        double aDist = DistMini.SquareDistance(j);
        if (aDist < MinDist)
        {
          MinDist = aDist;
          jref    = j;
        }
      }
      MinDist = std::sqrt(MinDist);
      DistMini.Points(jref, Pc, Ps);

      Ps.Parameter(theU, theV);
      a1 = theU;

      InGoodPeriod(CurAngle, 2 * M_PI, a1);
    }

    w = Pc.Parameter();

    if (ii > 1)
    {
      Diff = w - myPoles2d->Value(1, ii - 1).Y();
      if (std::abs(Diff) > DeltaG)
      {
        if (myGuide->IsPeriodic())
        {
          InGoodPeriod(myPoles2d->Value(1, ii - 1).Y(), myGuide->Period(), w);
          Diff = w - myPoles2d->Value(1, ii - 1).Y();
        }
      }

#ifdef OCCT_DEBUG
      if (std::abs(Diff) > DeltaG)
      {
        std::cout << "Location :: Diff on Guide : " << Diff << std::endl;
      }
#endif
    }

    Angle = theU;

    if (ii > 1)
    {
      Diff = Angle - OldAngle;
      if (std::abs(Diff) > M_PI)
      {
        InGoodPeriod(OldAngle, 2 * M_PI, Angle);
        Diff = Angle - OldAngle;
      }
#ifdef OCCT_DEBUG
      if (std::abs(Diff) > M_PI / 4)
      {
        std::cout << "Diff d'angle trop grand !!" << std::endl;
      }
#endif
    }

    v = theV;

    if (ii > 1)
    {
      if (uperiodic)
      {
        InGoodPeriod(myPoles2d->Value(2, ii - 1).Y(), UPeriod, v);
      }
      Diff = v - myPoles2d->Value(2, ii - 1).Y();
#ifdef OCCT_DEBUG
      if (std::abs(Diff) > (Ul - Uf) / (2 + NbKnots))
      {
        std::cout << "Diff sur section trop grand !!" << std::endl;
      }
#endif
    }

    p1.SetCoord(t, w);
    p2.SetCoord(Angle, v);
    CurAngle = Angle;
    myPoles2d->SetValue(1, ii, p1);
    myPoles2d->SetValue(2, ii, p2);
    OldAngle = Angle;
  }

  LastAngle = CurAngle;
  rotation  = true;
}

void GeomFill_LocationGuide::Set(const occ::handle<GeomFill_SectionLaw>& Section,
                                 const bool                              rotat,
                                 const double                            SFirst,
                                 const double                            SLast,
                                 const double                            PrecAngle,
                                 double&                                 LastAngle)
{
  myStatus  = GeomFill_PipeOk;
  myFirstS  = SFirst;
  myLastS   = SLast;
  LastAngle = PrecAngle;
  if (myCurve.IsNull())
    ratio = 0.;
  else
    ratio = (SLast - SFirst) / (myCurve->LastParameter() - myCurve->FirstParameter());
  mySec = Section;

  if (rotat)
    SetRotation(PrecAngle, LastAngle);
  else
    rotation = false;
}

void GeomFill_LocationGuide::EraseRotation()
{
  rotation = false;
  if (myStatus == GeomFill_ImpossibleContact)
    myStatus = GeomFill_PipeOk;
}

occ::handle<GeomFill_LocationLaw> GeomFill_LocationGuide::Copy() const
{
  double                                   la;
  occ::handle<GeomFill_TrihedronWithGuide> L;
  L = occ::down_cast<GeomFill_TrihedronWithGuide>(myLaw->Copy());
  occ::handle<GeomFill_LocationGuide> copy = new (GeomFill_LocationGuide)(L);
  copy->SetOrigine(OrigParam1, OrigParam2);
  copy->Set(mySec, rotation, myFirstS, myLastS, myPoles2d->Value(1, 1).X(), la);
  copy->SetTrsf(Trans);

  return copy;
}

bool GeomFill_LocationGuide::SetCurve(const occ::handle<Adaptor3d_Curve>& C)
{
  double LastAngle;
  myCurve   = C;
  myTrimmed = C;

  if (!myCurve.IsNull())
  {
    myLaw->SetCurve(C);
    myLaw->Origine(OrigParam1, OrigParam2);
    myStatus = myLaw->ErrorStatus();

    if (rotation)
      SetRotation(myPoles2d->Value(1, 1).X(), LastAngle);
  }
  return myStatus == GeomFill_PipeOk;
}

const occ::handle<Adaptor3d_Curve>& GeomFill_LocationGuide::GetCurve() const
{
  return myCurve;
}

void GeomFill_LocationGuide::SetTrsf(const gp_Mat& Transfo)
{
  Trans = Transfo;
  gp_Mat Aux;
  Aux.SetIdentity();
  Aux -= Trans;
  WithTrans = false;
  for (int ii = 1; ii <= 3 && !WithTrans; ii++)
    for (int jj = 1; jj <= 3 && !WithTrans; jj++)
      if (std::abs(Aux.Value(ii, jj)) > 1.e-14)
        WithTrans = true;
}

bool GeomFill_LocationGuide::D0(const double Param, gp_Mat& M, gp_Vec& V)
{
  bool   Ok;
  gp_Vec T, N, B;
  gp_Pnt P;

  myCurve->D0(Param, P);
  V.SetXYZ(P.XYZ());
  Ok = myLaw->D0(Param, T, N, B);
  if (!Ok)
  {
    myStatus = myLaw->ErrorStatus();
    return Ok;
  }
  M.SetCols(N.XYZ(), B.XYZ(), T.XYZ());

  if (WithTrans)
  {
    M *= Trans;
  }

  if (rotation)
  {
    double U = myFirstS + (Param - myCurve->FirstParameter()) * ratio;

    InitX(Param);

    int    Iter = 100;
    gp_XYZ t, b, n;
    t = M.Column(3);
    b = M.Column(2);
    n = M.Column(1);

    GeomFill_FunctionGuide E(mySec, myGuide, U);
    E.SetParam(Param, P, t, n);

    math_FunctionSetRoot Result(E, TolRes, Iter);
    Result.Perform(E, X, Inf, Sup);

    if (Result.IsDone())
    {

      Result.Root(R);

      gp_Mat Rot;
      Rot.SetRotation(t, R(2));
      b *= Rot;
      n *= Rot;

      M.SetCols(n, b, t);
    }
    else
    {
#ifdef OCCT_DEBUG
      std::cout << "LocationGuide::D0 : No Result !" << std::endl;
      TraceRevol(Param, U, myLaw, mySec, myCurve, Trans);
#endif
      myStatus = GeomFill_ImpossibleContact;
      return false;
    }
  }

  return true;
}

bool GeomFill_LocationGuide::D0(const double Param,
                                gp_Mat&      M,
                                gp_Vec&      V,

                                NCollection_Array1<gp_Pnt2d>&)
{
  gp_Vec T, N, B;
  gp_Pnt P;
  bool   Ok;

  myCurve->D0(Param, P);
  V.SetXYZ(P.XYZ());
  Ok = myLaw->D0(Param, T, N, B);
  if (!Ok)
  {
    myStatus = myLaw->ErrorStatus();
    return Ok;
  }
  M.SetCols(N.XYZ(), B.XYZ(), T.XYZ());

  if (WithTrans)
  {
    M *= Trans;
  }

  if (rotation)
  {

    InitX(Param);
    int    Iter = 100;
    gp_XYZ b, n, t;
    t = M.Column(3);
    b = M.Column(2);
    n = M.Column(1);

    GeomFill_FunctionGuide E(mySec,
                             myGuide,
                             myFirstS + (Param - myCurve->FirstParameter()) * ratio);
    E.SetParam(Param, P, t, n);

    math_FunctionSetRoot Result(E, TolRes, Iter);
    Result.Perform(E, X, Inf, Sup);

    if (Result.IsDone())
    {

      Result.Root(R);

      gp_Mat Rot;
      Rot.SetRotation(t, R(2));

      b *= Rot;
      n *= Rot;

      M.SetCols(n, b, t);
    }
    else
    {
#ifdef OCCT_DEBUG
      double U = myFirstS + ratio * (Param - myCurve->FirstParameter());
      std::cout << "LocationGuide::D0 : No Result !" << std::endl;
      TraceRevol(Param, U, myLaw, mySec, myCurve, Trans);
#endif
      myStatus = GeomFill_ImpossibleContact;
      return false;
    }
  }

  return true;
}

bool GeomFill_LocationGuide::D1(const double Param,
                                gp_Mat&      M,
                                gp_Vec&      V,
                                gp_Mat&      DM,
                                gp_Vec&      DV,

                                NCollection_Array1<gp_Pnt2d>&,

                                NCollection_Array1<gp_Vec2d>&)
{

  gp_Vec T, N, B, DT, DN, DB;

  gp_Pnt P;
  bool   Ok;

  myCurve->D1(Param, P, DV);
  V.SetXYZ(P.XYZ());
  Ok = myLaw->D1(Param, T, DT, N, DN, B, DB);
  if (!Ok)
  {
    myStatus = myLaw->ErrorStatus();
    return Ok;
  }
  M.SetCols(N.XYZ(), B.XYZ(), T.XYZ());
  DM.SetCols(DN.XYZ(), DB.XYZ(), DT.XYZ());

  if (WithTrans)
  {
    M *= Trans;
    DM *= Trans;
  }

  if (rotation)
  {
    return false;
  }

  return true;
}

bool GeomFill_LocationGuide::D2(const double Param,
                                gp_Mat&      M,
                                gp_Vec&      V,
                                gp_Mat&      DM,
                                gp_Vec&      DV,
                                gp_Mat&      D2M,
                                gp_Vec&      D2V,

                                NCollection_Array1<gp_Pnt2d>&,

                                NCollection_Array1<gp_Vec2d>&,

                                NCollection_Array1<gp_Vec2d>&)
{
  gp_Vec T, N, B, DT, DN, DB, D2T, D2N, D2B;

  gp_Pnt P;
  bool   Ok;

  myCurve->D2(Param, P, DV, D2V);
  V.SetXYZ(P.XYZ());
  Ok = myLaw->D2(Param, T, DT, D2T, N, DN, D2N, B, DB, D2B);
  if (!Ok)
  {
    myStatus = myLaw->ErrorStatus();
    return Ok;
  }

  if (WithTrans)
  {
    M *= Trans;
    DM *= Trans;
    D2M *= Trans;
  }

  if (rotation)
  {
    return false;
  }

  else
  {
    M.SetCols(N.XYZ(), B.XYZ(), T.XYZ());
    DM.SetCols(DN.XYZ(), DB.XYZ(), DT.XYZ());
    D2M.SetCols(D2N.XYZ(), D2B.XYZ(), D2T.XYZ());
  }

  return true;
}

bool GeomFill_LocationGuide::HasFirstRestriction() const
{
  return false;
}

bool GeomFill_LocationGuide::HasLastRestriction() const
{
  return false;
}

int GeomFill_LocationGuide::TraceNumber() const
{
  return 0;
}

GeomFill_PipeError GeomFill_LocationGuide::ErrorStatus() const
{
  return myStatus;
}

int GeomFill_LocationGuide::NbIntervals(const GeomAbs_Shape S) const
{
  int Nb_Sec, Nb_Law;
  Nb_Sec = myTrimmed->NbIntervals(S);
  Nb_Law = myLaw->NbIntervals(S);

  if (Nb_Sec == 1)
  {
    return Nb_Law;
  }
  else if (Nb_Law == 1)
  {
    return Nb_Sec;
  }

  NCollection_Array1<double>   IntC(1, Nb_Sec + 1);
  NCollection_Array1<double>   IntL(1, Nb_Law + 1);
  NCollection_Sequence<double> Inter;
  myTrimmed->Intervals(IntC, S);
  myLaw->Intervals(IntL, S);

  GeomLib::FuseIntervals(IntC, IntL, Inter, Precision::PConfusion() * 0.99);
  return Inter.Length() - 1;
}

void GeomFill_LocationGuide::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const
{
  int Nb_Sec, Nb_Law;
  Nb_Sec = myTrimmed->NbIntervals(S);
  Nb_Law = myLaw->NbIntervals(S);

  if (Nb_Sec == 1)
  {
    myLaw->Intervals(T, S);
    return;
  }
  else if (Nb_Law == 1)
  {
    myTrimmed->Intervals(T, S);
    return;
  }

  NCollection_Array1<double>   IntC(1, Nb_Sec + 1);
  NCollection_Array1<double>   IntL(1, Nb_Law + 1);
  NCollection_Sequence<double> Inter;
  myTrimmed->Intervals(IntC, S);
  myLaw->Intervals(IntL, S);

  GeomLib::FuseIntervals(IntC, IntL, Inter, Precision::PConfusion() * 0.99);
  for (int ii = 1; ii <= Inter.Length(); ii++)
    T(ii) = Inter(ii);
}

void GeomFill_LocationGuide::SetInterval(const double First, const double Last)
{
  myLaw->SetInterval(First, Last);
  myTrimmed = myCurve->Trim(First, Last, 0);
}

void GeomFill_LocationGuide::GetInterval(double& First, double& Last) const
{
  First = myTrimmed->FirstParameter();
  Last  = myTrimmed->LastParameter();
}

void GeomFill_LocationGuide::GetDomain(double& First, double& Last) const
{
  First = myCurve->FirstParameter();
  Last  = myCurve->LastParameter();
}

void GeomFill_LocationGuide::SetTolerance(const double Tol3d, const double)
{
  TolRes(1) = myGuide->Resolution(Tol3d);
  Resolution(1, Tol3d, TolRes(2), TolRes(3));
}

void GeomFill_LocationGuide::Resolution(const int,
                                        const double Tol,
                                        double&      TolU,
                                        double&      TolV) const
{
  TolU = Tol / 100;
  TolV = Tol / 100;
}

double GeomFill_LocationGuide::GetMaximalNorm()
{
  return 1.;
}

void GeomFill_LocationGuide::GetAverageLaw(gp_Mat& AM, gp_Vec& AV)
{
  int    ii;
  double U, delta;
  gp_Vec V, V1, V2, V3;

  myLaw->GetAverageLaw(V1, V2, V3);
  AM.SetCols(V1.XYZ(), V2.XYZ(), V3.XYZ());

  AV.SetCoord(0., 0., 0.);
  delta = (myTrimmed->LastParameter() - myTrimmed->FirstParameter()) / 10;
  U     = myTrimmed->FirstParameter();
  for (ii = 0; ii <= myNbPts; ii++, U += delta)
  {
    V.SetXYZ(myTrimmed->Value(U).XYZ());
    AV += V;
  }
  AV = AV / (myNbPts + 1);
}

occ::handle<Geom_Curve> GeomFill_LocationGuide::Section() const
{
  return mySec->ConstantSection();
}

occ::handle<Adaptor3d_Curve> GeomFill_LocationGuide::Guide() const
{
  return myGuide;
}

bool GeomFill_LocationGuide::IsRotation(double&) const
{
  return false;
}

void GeomFill_LocationGuide::Rotation(gp_Pnt&) const
{
  throw Standard_NotImplemented("GeomFill_LocationGuide::Rotation");
}

bool GeomFill_LocationGuide::IsTranslation(double&) const
{
  return false;
}

void GeomFill_LocationGuide::InitX(const double Param)
{

  int    Ideb = 1, Ifin = myPoles2d->RowLength(), Idemi;
  double Valeur, t1, t2;

  Valeur = myPoles2d->Value(1, Ideb).X();
  if (Param == Valeur)
  {
    Ifin = Ideb + 1;
  }

  Valeur = myPoles2d->Value(1, Ifin).X();
  if (Param == Valeur)
  {
    Ideb = Ifin - 1;
  }

  while (Ideb + 1 != Ifin)
  {
    Idemi  = (Ideb + Ifin) / 2;
    Valeur = myPoles2d->Value(1, Idemi).X();
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

  t1          = myPoles2d->Value(1, Ideb).X();
  t2          = myPoles2d->Value(1, Ifin).X();
  double diff = t2 - t1;

  double W1, W2;
  W1                 = myPoles2d->Value(1, Ideb).Coord(2);
  W2                 = myPoles2d->Value(1, Ifin).Coord(2);
  const gp_Pnt2d& P1 = myPoles2d->Value(2, Ideb);
  const gp_Pnt2d& P2 = myPoles2d->Value(2, Ifin);

  if (diff > 1.e-7)
  {
    double b = (Param - t1) / diff, a = (t2 - Param) / diff;
    X(1) = a * W1 + b * W2;
    X(2) = a * P1.Coord(1) + b * P2.Coord(1);
    X(3) = a * P1.Coord(2) + b * P2.Coord(2);
  }
  else
  {
    X(1) = (W1 + W2) / 2;
    X(2) = (P1.Coord(1) + P2.Coord(1)) / 2;
    X(3) = (P1.Coord(2) + P2.Coord(2)) / 2;
  }

  if (myGuide->IsPeriodic())
  {
    X(1) = ElCLib::InPeriod(X(1), myGuide->FirstParameter(), myGuide->LastParameter());
  }
  X(2) = ElCLib::InPeriod(X(2), 0, 2 * M_PI);
  if (mySec->IsUPeriodic())
  {
    X(3) = ElCLib::InPeriod(X(3), Uf, Ul);
  }
}

void GeomFill_LocationGuide::SetOrigine(const double Param1, const double Param2)
{
  OrigParam1 = Param1;
  OrigParam2 = Param2;
}

GeomFill_PipeError GeomFill_LocationGuide::ComputeAutomaticLaw(
  occ::handle<NCollection_HArray1<gp_Pnt2d>>& ParAndRad) const
{
  gp_Pnt P;
  gp_Vec T, N, B;
  int    ii;
  double t;

  GeomFill_PipeError theStatus = GeomFill_PipeOk;

  double f = myCurve->FirstParameter();
  double l = myCurve->LastParameter();

  ParAndRad = new NCollection_HArray1<gp_Pnt2d>(1, myNbPts);
  for (ii = 1; ii <= myNbPts; ii++)
  {
    t = double(myNbPts - ii) * f + double(ii - 1) * l;
    t /= (myNbPts - 1);
    myCurve->D0(t, P);
    bool Ok = myLaw->D0(t, T, N, B);
    if (!Ok)
    {
      theStatus = myLaw->ErrorStatus();
      return theStatus;
    }
    gp_Pnt PointOnGuide = myLaw->CurrentPointOnGuide();
    double CurWidth     = P.Distance(PointOnGuide);

    gp_Pnt2d aParamWithRadius(t, CurWidth);
    ParAndRad->SetValue(ii, aParamWithRadius);
  }

  return theStatus;
}
