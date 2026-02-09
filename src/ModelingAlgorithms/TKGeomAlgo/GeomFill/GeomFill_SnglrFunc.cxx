#include <Adaptor3d_Curve.hpp>
#include <GeomFill_SnglrFunc.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_NotImplemented.hpp>

GeomFill_SnglrFunc::GeomFill_SnglrFunc(const occ::handle<Adaptor3d_Curve>& HC)
    : myHCurve(HC),
      ratio(1)
{
}

occ::handle<Adaptor3d_Curve> GeomFill_SnglrFunc::ShallowCopy() const
{
  occ::handle<GeomFill_SnglrFunc> aCopy = new GeomFill_SnglrFunc(myHCurve->ShallowCopy());
  aCopy->ratio                          = ratio;
  return aCopy;
}

void GeomFill_SnglrFunc::SetRatio(const double Ratio)
{
  ratio = Ratio;
}

double GeomFill_SnglrFunc::FirstParameter() const
{
  return myHCurve->FirstParameter();
}

double GeomFill_SnglrFunc::LastParameter() const
{
  return myHCurve->LastParameter();
}

int GeomFill_SnglrFunc::NbIntervals(const GeomAbs_Shape S) const
{
  GeomAbs_Shape HCS = GeomAbs_C0;
  if (S == GeomAbs_C0)
  {
    HCS = GeomAbs_C2;
  }
  else if (S == GeomAbs_C1)
  {
    HCS = GeomAbs_C3;
  }
  else if (S >= GeomAbs_C2)
  {
    HCS = GeomAbs_CN;
  }
  return myHCurve->NbIntervals(HCS);
}

void GeomFill_SnglrFunc::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const
{
  GeomAbs_Shape HCS = GeomAbs_C0;
  if (S == GeomAbs_C0)
  {
    HCS = GeomAbs_C2;
  }
  else if (S == GeomAbs_C1)
  {
    HCS = GeomAbs_C3;
  }
  else if (S >= GeomAbs_C2)
  {
    HCS = GeomAbs_CN;
  }
  myHCurve->Intervals(T, HCS);
}

bool GeomFill_SnglrFunc::IsPeriodic() const
{
  return myHCurve->IsPeriodic();
}

double GeomFill_SnglrFunc::Period() const
{
  return myHCurve->Period();
}

gp_Pnt GeomFill_SnglrFunc::Value(const double U) const
{
  gp_Pnt C;
  gp_Vec DC, D2C;
  myHCurve->D2(U, C, DC, D2C);
  DC *= ratio;
  return gp_Pnt(DC.Crossed(D2C).XYZ());
}

void GeomFill_SnglrFunc::D0(const double U, gp_Pnt& P) const
{
  gp_Pnt C;
  gp_Vec DC, D2C;
  myHCurve->D2(U, C, DC, D2C);
  DC *= ratio;
  P = gp_Pnt(DC.Crossed(D2C).XYZ());
}

void GeomFill_SnglrFunc::D1(const double U, gp_Pnt& P, gp_Vec& V) const
{
  gp_Pnt C;
  gp_Vec DC, D2C, D3C;
  myHCurve->D3(U, C, DC, D2C, D3C);
  DC *= ratio;
  P = gp_Pnt(DC.Crossed(D2C).XYZ());
  V = DC.Crossed(D3C);
}

void GeomFill_SnglrFunc::D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
{
  gp_Pnt C;
  gp_Vec DC, D2C, D3C, D4C;
  myHCurve->D3(U, C, DC, D2C, D3C);
  P   = gp_Pnt(DC.Crossed(D2C).XYZ());
  V1  = DC.Crossed(D3C);
  D4C = myHCurve->DN(U, 4);
  V2  = D2C.Crossed(D3C) + DC.Crossed(D4C);

  P.ChangeCoord() *= ratio;
  V1 *= ratio;
  V2 *= ratio;
}

void GeomFill_SnglrFunc::D3(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const
{
  gp_Vec DC, D2C, D3C, D4C, D5C;
  myHCurve->D3(U, P, DC, D2C, D3C);
  D4C = myHCurve->DN(U, 4);
  D5C = myHCurve->DN(U, 5);
  P   = gp_Pnt(DC.Crossed(D2C).XYZ()).ChangeCoord() * ratio;
  V1  = DC.Crossed(D3C) * ratio;
  V2  = (D2C.Crossed(D3C) + DC.Crossed(D4C)) * ratio;
  V3  = (DC.Crossed(D5C) + D2C.Crossed(D4C) * 2) * ratio;
}

gp_Vec GeomFill_SnglrFunc::DN(const double U, const int N) const
{
  Standard_RangeError_Raise_if(N < 1, "Exception: Geom2d_OffsetCurve::DN(). N<1.");

  gp_Vec D1C, D2C, D3C;
  gp_Pnt C;

  switch (N)
  {
    case 1:
      D1(U, C, D1C);
      return D1C;
    case 2:
      D2(U, C, D1C, D2C);
      return D2C;
    case 3:
      D3(U, C, D1C, D2C, D3C);
      return D3C;
    default:
      throw Standard_NotImplemented("Exception: Derivative order is greater than 3. "
                                    "Cannot compute of derivative.");
  }
}

double GeomFill_SnglrFunc::Resolution(const double R3D) const
{
  return Precision::Parametric(R3D);
}

GeomAbs_CurveType GeomFill_SnglrFunc::GetType() const
{
  return GeomAbs_OtherCurve;
}
