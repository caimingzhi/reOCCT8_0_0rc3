#include <GCPnts_AbscissaPoint.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Geometry.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomConvert.hpp>
#include <GeomFill_EvolvedSection.hpp>
#include <gp_Pnt.hpp>
#include <Law_Function.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(GeomFill_EvolvedSection, GeomFill_SectionLaw)

GeomFill_EvolvedSection::GeomFill_EvolvedSection(const occ::handle<Geom_Curve>&   C,
                                                 const occ::handle<Law_Function>& L)
{
  L->Bounds(First, Last);
  mySection = occ::down_cast<Geom_Curve>(C->Copy());
  myLaw     = L->Trim(First, Last, 1.e-20);
  TLaw      = myLaw;
  myCurve   = occ::down_cast<Geom_BSplineCurve>(C);
  if (myCurve.IsNull())
  {
    myCurve = GeomConvert::CurveToBSplineCurve(C, Convert_QuasiAngular);
    if (myCurve->IsPeriodic())
    {
      int M = myCurve->Degree() / 2 + 1;
      myCurve->RemoveKnot(1, M, Precision::Confusion());
    }
  }
}

bool GeomFill_EvolvedSection::D0(const double                U,
                                 NCollection_Array1<gp_Pnt>& Poles,
                                 NCollection_Array1<double>& Weights)
{
  double val;
  int    ii, L = Poles.Length();
  val = TLaw->Value(U);
  myCurve->Poles(Poles);
  for (ii = 1; ii <= L; ii++)
  {
    Poles(ii).ChangeCoord() *= val;
  }
  myCurve->Weights(Weights);

  return true;
}

bool GeomFill_EvolvedSection::D1(const double                U,
                                 NCollection_Array1<gp_Pnt>& Poles,
                                 NCollection_Array1<gp_Vec>& DPoles,
                                 NCollection_Array1<double>& Weights,
                                 NCollection_Array1<double>& DWeights)
{
  double val, dval;
  int    ii, L = Poles.Length();
  TLaw->D1(U, val, dval);

  myCurve->Poles(Poles);
  myCurve->Weights(Weights);
  for (ii = 1; ii <= L; ii++)
  {
    DPoles(ii).SetXYZ(Poles(ii).XYZ());
    DPoles(ii) *= dval;
    Poles(ii).ChangeCoord() *= val;
  }
  DWeights.Init(0);

  return true;
}

bool GeomFill_EvolvedSection::D2(const double                U,
                                 NCollection_Array1<gp_Pnt>& Poles,
                                 NCollection_Array1<gp_Vec>& DPoles,
                                 NCollection_Array1<gp_Vec>& D2Poles,
                                 NCollection_Array1<double>& Weights,
                                 NCollection_Array1<double>& DWeights,
                                 NCollection_Array1<double>& D2Weights)
{
  double val, dval, d2val;
  int    ii, L = Poles.Length();
  TLaw->D2(U, val, dval, d2val);
  myCurve->Poles(Poles);
  myCurve->Weights(Weights);

  for (ii = 1; ii <= L; ii++)
  {
    DPoles(ii).SetXYZ(Poles(ii).XYZ());
    D2Poles(ii) = DPoles(ii);
    D2Poles(ii) *= d2val;
    DPoles(ii) *= dval;
    Poles(ii).ChangeCoord() *= val;
  }

  DWeights.Init(0);
  D2Weights.Init(0);

  return true;
}

occ::handle<Geom_BSplineSurface> GeomFill_EvolvedSection::BSplineSurface() const
{

  occ::handle<Geom_BSplineSurface> BS;
  BS.Nullify();
  return BS;
}

void GeomFill_EvolvedSection::SectionShape(int& NbPoles, int& NbKnots, int& Degree) const
{
  NbPoles = myCurve->NbPoles();
  NbKnots = myCurve->NbKnots();
  Degree  = myCurve->Degree();
}

void GeomFill_EvolvedSection::Knots(NCollection_Array1<double>& TKnots) const
{
  myCurve->Knots(TKnots);
}

void GeomFill_EvolvedSection::Mults(NCollection_Array1<int>& TMults) const
{
  myCurve->Multiplicities(TMults);
}

bool GeomFill_EvolvedSection::IsRational() const
{
  return myCurve->IsRational();
}

bool GeomFill_EvolvedSection::IsUPeriodic() const
{
  return myCurve->IsPeriodic();
}

bool GeomFill_EvolvedSection::IsVPeriodic() const
{
  return (std::abs(myLaw->Value(First) - myLaw->Value(Last)) < Precision::Confusion());
}

int GeomFill_EvolvedSection::NbIntervals(const GeomAbs_Shape S) const
{
  return myLaw->NbIntervals(S);
}

void GeomFill_EvolvedSection::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const
{
  myLaw->Intervals(T, S);
}

void GeomFill_EvolvedSection::SetInterval(const double F, const double L)
{
  TLaw = myLaw->Trim(F, L, Precision::PConfusion());
}

void GeomFill_EvolvedSection::GetInterval(double& F, double& L) const
{
  TLaw->Bounds(F, L);
}

void GeomFill_EvolvedSection::GetDomain(double& F, double& L) const
{
  F = First;
  L = Last;
}

void GeomFill_EvolvedSection::GetTolerance(const double BoundTol,
                                           const double SurfTol,

                                           const double,
                                           NCollection_Array1<double>& Tol3d) const
{
  Tol3d.Init(SurfTol);
  if (BoundTol < SurfTol)
  {
    Tol3d(Tol3d.Lower()) = BoundTol;
    Tol3d(Tol3d.Upper()) = BoundTol;
  }
}

gp_Pnt GeomFill_EvolvedSection::BarycentreOfSurf() const
{
  double U = mySection->FirstParameter(), Delta, b;
  int    ii;
  gp_Pnt P, Bary;

  Delta = (myCurve->LastParameter() - U) / 20;
  Bary.SetCoord(0., 0., 0.);
  for (ii = 0; ii <= 20; ii++, U += Delta)
  {
    P = myCurve->Value(U);
    Bary.ChangeCoord() += P.XYZ();
  }

  U     = First;
  Delta = (Last - First) / 20;
  for (ii = 0, b = 0.0; ii <= 20; ii++, U += Delta)
  {
    b += myLaw->Value(U);
  }
  Bary.ChangeCoord() *= b / (21 * 21);
  return Bary;
}

double GeomFill_EvolvedSection::MaximalSection() const
{
  double            L, val, max, U, Delta;
  int               ii;
  GeomAdaptor_Curve AC(mySection);
  L = GCPnts_AbscissaPoint::Length(AC);

  Delta = (Last - First) / 20;
  for (ii = 0, max = 0.0, U = First; ii <= 20; ii++, U += Delta)
  {
    val = myLaw->Value(U);
    if (val > max)
      max = val;
  }
  return L * max;
}

void GeomFill_EvolvedSection::GetMinimalWeight(NCollection_Array1<double>& Weights) const
{
  if (myCurve->IsRational())
  {
    myCurve->Weights(Weights);
  }
  else
  {
    Weights.Init(1);
  }
}

bool GeomFill_EvolvedSection::IsConstant(double& Error) const
{

  bool isconst = false;
  Error        = 0.;
  return isconst;
}

occ::handle<Geom_Curve> GeomFill_EvolvedSection::ConstantSection() const
{
  double Err, scale;
  if (!IsConstant(Err))
    throw StdFail_NotDone("The Law is not Constant!");
  gp_Trsf T;
  gp_Pnt  P(0, 0, 0);
  scale = myLaw->Value(First) + myLaw->Value((First + Last) / 2) + myLaw->Value(Last);
  T.SetScale(P, scale / 3);

  occ::handle<Geom_Curve> C;
  C = occ::down_cast<Geom_Curve>(mySection->Copy());
  C->Transform(T);
  return C;
}
