#include <GeomFill_LocationDraft.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Geom_Line.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomFill_DraftTrihedron.hpp>
#include <GeomFill_FunctionDraft.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <GeomFill_Tensor.hpp>
#include <GeomFill_TrihedronLaw.hpp>
#include <gp_Dir.hpp>
#include <gp_Mat.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <IntCurveSurface_HInter.hpp>
#include <IntCurveSurface_Intersection.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Gauss.hpp>
#include <math_Matrix.hpp>
#include <math_NewtonFunctionSetRoot.hpp>
#include <math_Vector.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_LocationDraft, GeomFill_LocationLaw)

GeomFill_LocationDraft::GeomFill_LocationDraft(const gp_Dir& Direction, const double Angle)
{
  myDir = Direction;

  myAngle = Angle;

  mySurf.Nullify();
  myLaw     = new (GeomFill_DraftTrihedron)(myDir, Angle);
  myNbPts   = 41;
  myPoles2d = new (NCollection_HArray1<gp_Pnt2d>)(1, 2 * myNbPts);
  Intersec  = false;
  WithTrans = false;
}

occ::handle<GeomFill_LocationLaw> GeomFill_LocationDraft::Copy() const
{
  occ::handle<GeomFill_TrihedronLaw> law;
  law                                      = myLaw->Copy();
  occ::handle<GeomFill_LocationDraft> copy = new (GeomFill_LocationDraft)(myDir, myAngle);
  copy->SetCurve(myCurve);
  copy->SetStopSurf(mySurf);
  if (WithTrans)
    copy->SetTrsf(Trans);

  return copy;
}

void GeomFill_LocationDraft::SetTrsf(const gp_Mat& Transfo)
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

bool GeomFill_LocationDraft::SetCurve(const occ::handle<Adaptor3d_Curve>& C)
{
  myCurve   = C;
  myTrimmed = C;
  bool isOK = myLaw->SetCurve(C);

  Prepare();
  return isOK;
}

void GeomFill_LocationDraft::SetStopSurf(const occ::handle<Adaptor3d_Surface>& Surf)
{
  mySurf = Surf;
  Prepare();
}

void GeomFill_LocationDraft::SetAngle(const double Angle)
{
  myAngle = Angle;
  myLaw->SetAngle(myAngle);
  Prepare();
}

void GeomFill_LocationDraft::Prepare()
{
  if (mySurf.IsNull())
  {
    Intersec = false;
    return;
  }

  Intersec = true;

  int                               ii, jj;
  double                            f, l, t;
  gp_Pnt                            P;
  gp_Vec                            D, T, N, B;
  occ::handle<Geom_Line>            L;
  IntCurveSurface_IntersectionPoint P1, P2;
  f = myCurve->FirstParameter();
  l = myCurve->LastParameter();

  for (ii = 1; ii <= myNbPts; ii++)
  {
    t = double(myNbPts - ii) * f + double(ii - 1) * l;
    t /= (myNbPts - 1);

    myCurve->D0(t, P);
    myLaw->D0(t, T, N, B);

    D = std::cos(myAngle) * B + std::sin(myAngle) * N;

    L = new (Geom_Line)(P, D);

    IntCurveSurface_HInter         Int;
    occ::handle<GeomAdaptor_Curve> AC = new (GeomAdaptor_Curve)(L);
    Int.Perform(AC, mySurf);

    if (Int.NbPoints() > 0)
    {
      P1 = Int.Point(1);

      for (jj = 2; jj <= Int.NbPoints(); jj++)
      {
        P2 = Int.Point(jj);
        if (P1.W() > P2.W())
          P1 = P2;
      }

      gp_Pnt2d p(P1.W(), t);
      gp_Pnt2d q(P1.U(), P1.V());
      myPoles2d->SetValue(2 * ii - 1, p);
      myPoles2d->SetValue(2 * ii, q);
    }
    else
    {
      Intersec = false;
    }
  }
}

const occ::handle<Adaptor3d_Curve>& GeomFill_LocationDraft::GetCurve() const
{
  return myCurve;
}

bool GeomFill_LocationDraft::D0(const double Param, gp_Mat& M, gp_Vec& V)
{
  bool   Ok;
  gp_Vec T, N, B;
  gp_Pnt P;

  myTrimmed->D0(Param, P);
  V.SetXYZ(P.XYZ());

  Ok = myLaw->D0(Param, T, N, B);
  if (!Ok)
    return Ok;
  M.SetCols(N.XYZ(), B.XYZ(), T.XYZ());

  if (WithTrans)
  {
    M *= Trans;
  }

  return true;
}

bool GeomFill_LocationDraft::D0(const double                  Param,
                                gp_Mat&                       M,
                                gp_Vec&                       V,
                                NCollection_Array1<gp_Pnt2d>& Poles2d)
{
  bool Ok;

  gp_Vec D, T, N, B;
  gp_Pnt P;

  myCurve->D0(Param, P);
  V.SetXYZ(P.XYZ());
  Ok = myLaw->D0(Param, T, N, B);
  if (!Ok)
    return Ok;
  M.SetCols(N.XYZ(), B.XYZ(), T.XYZ());

  if (WithTrans)
  {
    M *= Trans;
  }

  if (Intersec)
  {

    D = std::cos(myAngle) * B + std::sin(myAngle) * N;

    occ::handle<Geom_Line>         L = new (Geom_Line)(P, D);
    occ::handle<GeomAdaptor_Curve> G = new (GeomAdaptor_Curve)(L);

    double t1, t2, Paramt1, t2Param;
    double U0 = 0, V0 = 0, W0 = 0;

    int ii = 1;

    while (ii < 2 * myNbPts && myPoles2d->Value(ii).Coord(2) < Param)
      ii = ii + 2;

    if (ii < 2 * myNbPts && !IsEqual(myPoles2d->Value(ii).Coord(2), Param))
    {

      t1 = myPoles2d->Value(ii).Coord(2);
      t2 = myPoles2d->Value(ii - 2).Coord(2);

      Paramt1 = (Param - t1) / (t2 - t1);
      t2Param = (t2 - Param) / (t2 - t1);

      W0 = myPoles2d->Value(ii - 2).Coord(1) * Paramt1 + myPoles2d->Value(ii).Coord(1) * t2Param;
      U0 =
        myPoles2d->Value(ii - 1).Coord(1) * Paramt1 + myPoles2d->Value(ii + 1).Coord(1) * t2Param;
      V0 =
        myPoles2d->Value(ii - 1).Coord(2) * Paramt1 + myPoles2d->Value(ii + 1).Coord(2) * t2Param;
    }

    else if (ii < 2 * myNbPts && IsEqual(myPoles2d->Value(ii).Coord(2), Param))
    {
      W0 = myPoles2d->Value(ii).Coord(1);
      U0 = myPoles2d->Value(ii + 1).Coord(1);
      V0 = myPoles2d->Value(ii + 1).Coord(2);
    }

    math_Vector X(1, 3);
    X(1) = W0;
    X(2) = U0;
    X(3) = V0;

    math_Vector XTol(1, 3);
    XTol.Init(0.00001);

    double FTol = 0.0000001;
    int    Iter = 100;

    GeomFill_FunctionDraft E(mySurf, G);

    math_NewtonFunctionSetRoot Result(E, XTol, FTol, Iter);
    Result.Perform(E, X);

    if (Result.IsDone())
    {
      math_Vector R(1, 3);
      Result.Root(R);

      gp_Pnt2d p(R(2), R(3));
      gp_Pnt2d q(R(1), Param);
      Poles2d.SetValue(1, p);
      Poles2d.SetValue(2, q);
    }
    else
    {
      return false;
    }
  }

  return true;
}

bool GeomFill_LocationDraft::D1(const double                  Param,
                                gp_Mat&                       M,
                                gp_Vec&                       V,
                                gp_Mat&                       DM,
                                gp_Vec&                       DV,
                                NCollection_Array1<gp_Pnt2d>& Poles2d,
                                NCollection_Array1<gp_Vec2d>& DPoles2d)
{
  bool   Ok;
  gp_Vec D, T, N, B, DT, DN, DB;
  gp_Pnt P;

  myCurve->D1(Param, P, DV);
  V.SetXYZ(P.XYZ());

  Ok = myLaw->D1(Param, T, DT, N, DN, B, DB);
  if (!Ok)
    return false;

  M.SetCols(N.XYZ(), B.XYZ(), T.XYZ());
  DM.SetCols(DN.XYZ(), DB.XYZ(), DT.XYZ());

  if (WithTrans)
  {
    M *= Trans;
    DM *= Trans;
  }

  if (Intersec)
  {

    D = std::cos(myAngle) * B + std::sin(myAngle) * N;

    occ::handle<Geom_Line>         L = new (Geom_Line)(P, D);
    occ::handle<GeomAdaptor_Curve> G = new (GeomAdaptor_Curve)(L);

    double t1, t2, Paramt1, t2Param;
    double U0 = 0, V0 = 0, W0 = 0;

    int ii = 1;

    while (ii < 2 * myNbPts && myPoles2d->Value(ii).Coord(2) < Param)
      ii = ii + 2;

    if (ii < 2 * myNbPts && !IsEqual(myPoles2d->Value(ii).Coord(2), Param))
    {

      t1 = myPoles2d->Value(ii).Coord(2);
      t2 = myPoles2d->Value(ii - 2).Coord(2);

      Paramt1 = (Param - t1) / (t2 - t1);
      t2Param = (t2 - Param) / (t2 - t1);

      W0 = myPoles2d->Value(ii - 2).Coord(1) * Paramt1 + myPoles2d->Value(ii).Coord(1) * t2Param;
      U0 =
        myPoles2d->Value(ii - 1).Coord(1) * Paramt1 + myPoles2d->Value(ii + 1).Coord(1) * t2Param;
      V0 =
        myPoles2d->Value(ii - 1).Coord(2) * Paramt1 + myPoles2d->Value(ii + 1).Coord(2) * t2Param;
    }
    else if (ii < 2 * myNbPts && IsEqual(myPoles2d->Value(ii).Coord(2), Param))
    {
      W0 = myPoles2d->Value(ii).Coord(1);
      U0 = myPoles2d->Value(ii + 1).Coord(1);
      V0 = myPoles2d->Value(ii + 1).Coord(2);
    }

    math_Vector X(1, 3);
    X(1) = W0;
    X(2) = U0;
    X(3) = V0;

    math_Vector XTol(1, 3);
    XTol.Init(0.0001);

    double FTol = 0.000001;
    int    Iter = 100;

    GeomFill_FunctionDraft E(mySurf, G);

    math_NewtonFunctionSetRoot Result(E, XTol, FTol, Iter);
    Result.Perform(E, X);

    if (Result.IsDone())
    {
      math_Vector R(1, 3);
      Result.Root(R);

      gp_Pnt2d p(R(2), R(3));
      gp_Pnt2d q(R(1), Param);
      Poles2d.SetValue(1, p);
      Poles2d.SetValue(2, q);

      math_Vector DEDT(1, 3, 0);
      E.DerivT(myTrimmed, Param, R(1), DN, myAngle, DEDT);

      math_Vector DSDT(1, 3, 0);
      math_Matrix DEDX(1, 3, 1, 3, 0);
      E.Derivatives(R, DEDX);

      math_Gauss Ga(DEDX);
      if (Ga.IsDone())
      {
        Ga.Solve(DEDT.Opposite(), DSDT);
        gp_Vec2d dp(DSDT(2), DSDT(3));
        gp_Vec2d dq(DSDT(1), 1);
        DPoles2d.SetValue(1, dp);
        DPoles2d.SetValue(2, dq);
      }
    }
    else
    {
      return false;
    }
  }
  return true;
}

bool GeomFill_LocationDraft::D2(const double                  Param,
                                gp_Mat&                       M,
                                gp_Vec&                       V,
                                gp_Mat&                       DM,
                                gp_Vec&                       DV,
                                gp_Mat&                       D2M,
                                gp_Vec&                       D2V,
                                NCollection_Array1<gp_Pnt2d>& Poles2d,
                                NCollection_Array1<gp_Vec2d>& DPoles2d,
                                NCollection_Array1<gp_Vec2d>& D2Poles2d)
{
  bool   Ok;
  gp_Vec D, T, N, B, DT, DN, DB, D2T, D2N, D2B;
  gp_Pnt P;

  myCurve->D2(Param, P, DV, D2V);
  V.SetXYZ(P.XYZ());

  Ok = myLaw->D2(Param, T, DT, D2T, N, DN, D2N, B, DB, D2B);
  if (!Ok)
    return Ok;

  M.SetCols(N.XYZ(), B.XYZ(), T.XYZ());
  DM.SetCols(DN.XYZ(), DB.XYZ(), DT.XYZ());
  D2M.SetCols(D2N.XYZ(), D2B.XYZ(), D2T.XYZ());

  if (WithTrans)
  {
    M *= Trans;
    DM *= Trans;
    D2M *= Trans;
  }
  if (Intersec)
  {

    D = std::cos(myAngle) * B + std::sin(myAngle) * N;

    occ::handle<Geom_Line>         L = new (Geom_Line)(P, D);
    occ::handle<GeomAdaptor_Curve> G = new (GeomAdaptor_Curve)(L);

    double t1, t2, Paramt1, t2Param;
    double U0 = 0, V0 = 0, W0 = 0;

    int ii = 1;

    while (ii < 2 * myNbPts && myPoles2d->Value(ii).Coord(2) < Param)
      ii = ii + 2;

    if (ii < 2 * myNbPts && !IsEqual(myPoles2d->Value(ii).Coord(2), Param))
    {

      t1 = myPoles2d->Value(ii).Coord(2);
      t2 = myPoles2d->Value(ii - 2).Coord(2);

      Paramt1 = (Param - t1) / (t2 - t1);
      t2Param = (t2 - Param) / (t2 - t1);

      W0 = myPoles2d->Value(ii - 2).Coord(1) * Paramt1 + myPoles2d->Value(ii).Coord(1) * t2Param;
      U0 =
        myPoles2d->Value(ii - 1).Coord(1) * Paramt1 + myPoles2d->Value(ii + 1).Coord(1) * t2Param;
      V0 =
        myPoles2d->Value(ii - 1).Coord(2) * Paramt1 + myPoles2d->Value(ii + 1).Coord(2) * t2Param;
    }
    else if (ii < 2 * myNbPts && IsEqual(myPoles2d->Value(ii).Coord(2), Param))
    {
      W0 = myPoles2d->Value(ii).Coord(1);
      U0 = myPoles2d->Value(ii + 1).Coord(1);
      V0 = myPoles2d->Value(ii + 1).Coord(2);
    }

    math_Vector X(1, 3);
    X(1) = W0;
    X(2) = U0;
    X(3) = V0;

    math_Vector XTol(1, 3);
    XTol.Init(0.0001);

    double FTol = 0.000001;
    int    Iter = 150;

    GeomFill_FunctionDraft E(mySurf, G);

    math_NewtonFunctionSetRoot Result(E, XTol, FTol, Iter);
    Result.Perform(E, X);

    if (Result.IsDone())
    {
      math_Vector R(1, 3);
      Result.Root(R);

      gp_Pnt2d p(R(2), R(3));
      gp_Pnt2d q(R(1), Param);
      Poles2d.SetValue(1, p);
      Poles2d.SetValue(2, q);

      math_Vector DEDT(1, 3, 0);
      E.DerivT(myTrimmed, Param, R(1), DN, myAngle, DEDT);

      math_Vector DSDT(1, 3, 0);
      math_Matrix DEDX(1, 3, 1, 3, 0);
      E.Derivatives(R, DEDX);

      math_Gauss Ga(DEDX);
      if (Ga.IsDone())
      {
        Ga.Solve(DEDT.Opposite(), DSDT);
        gp_Vec2d dp(DSDT(2), DSDT(3));
        gp_Vec2d dq(DSDT(1), 1);
        DPoles2d.SetValue(1, dp);
        DPoles2d.SetValue(2, dq);
      }

      GeomFill_Tensor D2EDX2(3, 3, 3);
      E.Deriv2X(R, D2EDX2);

      math_Vector D2EDT2(1, 3, 0);
      E.Deriv2T(myTrimmed, Param, R(1), D2N, myAngle, D2EDT2);

      math_Matrix D2EDTDX(1, 3, 1, 3, 0);
      E.DerivTX(DN, myAngle, D2EDTDX);

      math_Vector D2SDT2(1, 3, 0);
      math_Matrix aT(1, 3, 1, 3, 0);
      D2EDX2.Multiply(DSDT, aT);

      math_Gauss Ga1(DEDX);
      if (Ga1.IsDone())
      {
        Ga1.Solve(-aT * DSDT - 2 * D2EDTDX * DSDT - D2EDT2, D2SDT2);
        gp_Vec2d d2p(D2SDT2(2), D2SDT2(3));
        gp_Vec2d d2q(D2SDT2(1), 0);
        D2Poles2d.SetValue(1, d2p);
        D2Poles2d.SetValue(2, d2q);
      }
      else
      {
        return false;
      }
    }
  }

  return true;
}

bool GeomFill_LocationDraft::HasFirstRestriction() const
{
  return false;
}

bool GeomFill_LocationDraft::HasLastRestriction() const
{

  return Intersec;
}

int GeomFill_LocationDraft::TraceNumber() const
{
  if (Intersec)
    return 1;
  else
    return 0;
}

int GeomFill_LocationDraft::NbIntervals(const GeomAbs_Shape S) const
{
  return myLaw->NbIntervals(S);
}

void GeomFill_LocationDraft::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const
{
  myLaw->Intervals(T, S);
}

void GeomFill_LocationDraft::SetInterval(const double First, const double Last)
{
  myLaw->SetInterval(First, Last);
  myTrimmed = myCurve->Trim(First, Last, 0);
}

void GeomFill_LocationDraft::GetInterval(double& First, double& Last) const
{
  First = myTrimmed->FirstParameter();
  Last  = myTrimmed->LastParameter();
}

void GeomFill_LocationDraft::GetDomain(double& First, double& Last) const
{
  First = myCurve->FirstParameter();
  Last  = myCurve->LastParameter();
}

void GeomFill_LocationDraft::Resolution(const int    Index,
                                        const double Tol,
                                        double&      TolU,
                                        double&      TolV) const

{
  if (Index == 1)
  {
    TolU = mySurf->UResolution(Tol);
    TolV = mySurf->VResolution(Tol);
  }
  else
  {
    TolU = Tol;
    TolV = Tol;
  }
}

double GeomFill_LocationDraft::GetMaximalNorm()
{
  return 1.;
}

void GeomFill_LocationDraft::GetAverageLaw(gp_Mat& AM, gp_Vec& AV)
{
  int    ii;
  double U, delta;
  gp_Vec V1, V2, V3, V;

  myLaw->GetAverageLaw(V1, V2, V3);
  AM.SetCols(V1.XYZ(), V2.XYZ(), V3.XYZ());

  AV.SetCoord(0., 0., 0.);
  delta = (myTrimmed->LastParameter() - myTrimmed->FirstParameter()) / 10;
  U     = myTrimmed->FirstParameter();
  for (ii = 0; ii <= 10; ii++, U += delta)
  {
    V.SetXYZ(myTrimmed->Value(U).XYZ());
    AV += V;
  }
  AV /= 11;
}

bool GeomFill_LocationDraft::IsTranslation(double&) const
{
  return myLaw->IsConstant();
}

bool GeomFill_LocationDraft::IsRotation(double& Error) const
{
  GeomAbs_CurveType Type;
  Error = 0;
  Type  = myCurve->GetType();
  if (Type == GeomAbs_Circle)
  {
    return myLaw->IsOnlyBy3dCurve();
  }
  return false;
}

void GeomFill_LocationDraft::Rotation(gp_Pnt& Centre) const
{
  Centre = myCurve->Circle().Location();
}

bool GeomFill_LocationDraft::IsIntersec() const
{
  return Intersec;
}

gp_Dir GeomFill_LocationDraft::Direction() const
{
  return myDir;
}
