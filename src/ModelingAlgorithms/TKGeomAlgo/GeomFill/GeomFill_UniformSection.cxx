#include <GCPnts_AbscissaPoint.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Geometry.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomConvert.hpp>
#include <GeomFill_UniformSection.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(GeomFill_UniformSection, GeomFill_SectionLaw)

GeomFill_UniformSection::GeomFill_UniformSection(const occ::handle<Geom_Curve>& C,
                                                 const double                   FirstParameter,
                                                 const double                   LastParameter)
    : First(FirstParameter),
      Last(LastParameter)
{
  mySection = occ::down_cast<Geom_Curve>(C->Copy());
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

//=======================================================
// Purpose :D0
//=======================================================
bool GeomFill_UniformSection::D0(const double,
                                 NCollection_Array1<gp_Pnt>& Poles,
                                 NCollection_Array1<double>& Weights)
{
  myCurve->Poles(Poles);
  myCurve->Weights(Weights);

  return true;
}

//=======================================================
// Purpose :D1
//=======================================================
bool GeomFill_UniformSection::D1(const double,
                                 NCollection_Array1<gp_Pnt>& Poles,
                                 NCollection_Array1<gp_Vec>& DPoles,
                                 NCollection_Array1<double>& Weights,
                                 NCollection_Array1<double>& DWeights)
{
  myCurve->Poles(Poles);
  myCurve->Weights(Weights);
  gp_Vec V0(0, 0, 0);
  DPoles.Init(V0);
  DWeights.Init(0);

  return true;
}

//=======================================================
// Purpose :D2
//=======================================================
bool GeomFill_UniformSection::D2(const double,
                                 NCollection_Array1<gp_Pnt>& Poles,
                                 NCollection_Array1<gp_Vec>& DPoles,
                                 NCollection_Array1<gp_Vec>& D2Poles,
                                 NCollection_Array1<double>& Weights,
                                 NCollection_Array1<double>& DWeights,
                                 NCollection_Array1<double>& D2Weights)
{
  myCurve->Poles(Poles);
  myCurve->Weights(Weights);
  gp_Vec V0(0, 0, 0);
  DPoles.Init(V0);
  DWeights.Init(0);
  D2Poles.Init(V0);
  D2Weights.Init(0);

  return true;
}

//=======================================================
// Purpose :BSplineSurface()
//=======================================================
occ::handle<Geom_BSplineSurface> GeomFill_UniformSection::BSplineSurface() const
{
  int                        ii, NbPoles = myCurve->NbPoles();
  NCollection_Array2<gp_Pnt> Poles(1, NbPoles, 1, 2);
  NCollection_Array1<double> UKnots(1, myCurve->NbKnots()), VKnots(1, 2);
  NCollection_Array1<int>    UMults(1, myCurve->NbKnots()), VMults(1, 2);

  for (ii = 1; ii <= NbPoles; ii++)
  {
    Poles(ii, 1) = Poles(ii, 2) = myCurve->Pole(ii);
  }

  myCurve->Knots(UKnots);
  VKnots(1) = First;
  VKnots(2) = Last;

  myCurve->Multiplicities(UMults);
  VMults.Init(2);

  occ::handle<Geom_BSplineSurface> BS = new (Geom_BSplineSurface)(Poles,
                                                                  UKnots,
                                                                  VKnots,
                                                                  UMults,
                                                                  VMults,
                                                                  myCurve->Degree(),
                                                                  1,
                                                                  myCurve->IsPeriodic());

  return BS;
}

//=======================================================
// Purpose :SectionShape
//=======================================================
void GeomFill_UniformSection::SectionShape(int& NbPoles, int& NbKnots, int& Degree) const
{
  NbPoles = myCurve->NbPoles();
  NbKnots = myCurve->NbKnots();
  Degree  = myCurve->Degree();
}

void GeomFill_UniformSection::Knots(NCollection_Array1<double>& TKnots) const
{
  myCurve->Knots(TKnots);
}

//=======================================================
// Purpose :Mults
//=======================================================
void GeomFill_UniformSection::Mults(NCollection_Array1<int>& TMults) const
{
  myCurve->Multiplicities(TMults);
}

//=======================================================
// Purpose :IsRational
//=======================================================
bool GeomFill_UniformSection::IsRational() const
{
  return myCurve->IsRational();
}

//=======================================================
// Purpose :IsUPeriodic
//=======================================================
bool GeomFill_UniformSection::IsUPeriodic() const
{
  return myCurve->IsPeriodic();
}

//=======================================================
// Purpose :IsVPeriodic
//=======================================================
bool GeomFill_UniformSection::IsVPeriodic() const
{
  return true;
}

//=======================================================
// Purpose :NbIntervals
//=======================================================
// int GeomFill_UniformSection::NbIntervals(const GeomAbs_Shape S) const
int GeomFill_UniformSection::NbIntervals(const GeomAbs_Shape) const
{
  return 1;
}

//=======================================================
// Purpose :Intervals
//=======================================================
void GeomFill_UniformSection::Intervals(NCollection_Array1<double>& T,
                                        //					 const GeomAbs_Shape S) const
                                        const GeomAbs_Shape) const
{
  T(T.Lower()) = First;
  T(T.Upper()) = Last;
}

//=======================================================
// Purpose : SetInterval
//=======================================================
void GeomFill_UniformSection::SetInterval(const double, const double)
{
  // Ne fait Rien
}

//=======================================================
// Purpose : GetInterval
//=======================================================
void GeomFill_UniformSection::GetInterval(double& F, double& L) const
{
  F = First;
  L = Last;
}

//=======================================================
// Purpose : GetDomain
//=======================================================
void GeomFill_UniformSection::GetDomain(double& F, double& L) const
{
  F = First;
  L = Last;
}

//=======================================================
// Purpose : GetTolerance
//=======================================================
void GeomFill_UniformSection::GetTolerance(const double BoundTol,
                                           const double SurfTol,
                                           //					    const double AngleTol,
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

//=======================================================
// Purpose :
//=======================================================
gp_Pnt GeomFill_UniformSection::BarycentreOfSurf() const
{
  double U = mySection->FirstParameter(), Delta;
  gp_Pnt P, Bary;

  Delta = (myCurve->LastParameter() - U) / 20;
  Bary.SetCoord(0., 0., 0.);
  for (int ii = 0; ii <= 20; ii++, U += Delta)
  {
    P = myCurve->Value(U);
    Bary.ChangeCoord() += P.XYZ();
  }
  Bary.ChangeCoord() /= 21.;

  return Bary;
}

double GeomFill_UniformSection::MaximalSection() const
{
  GeomAdaptor_Curve AC(mySection);
  return GCPnts_AbscissaPoint::Length(AC);
}

void GeomFill_UniformSection::GetMinimalWeight(NCollection_Array1<double>& Weights) const
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

bool GeomFill_UniformSection::IsConstant(double& Error) const
{
  Error = 0.;
  return true;
}

occ::handle<Geom_Curve> GeomFill_UniformSection::ConstantSection() const
{
  occ::handle<Geom_Curve> C;
  C = occ::down_cast<Geom_Curve>(mySection->Copy());
  return C;
}
