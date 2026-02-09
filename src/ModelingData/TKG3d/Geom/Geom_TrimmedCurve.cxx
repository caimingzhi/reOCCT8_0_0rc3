#include <ElCLib.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Geometry.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Geom_UndefinedDerivative.hpp>
#include <gp.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_RangeError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_TrimmedCurve, Geom_BoundedCurve)

typedef Geom_TrimmedCurve TrimmedCurve;
typedef gp_Ax1            Ax1;
typedef gp_Ax2            Ax2;
typedef gp_Pnt            Pnt;
typedef gp_Trsf           Trsf;
typedef gp_Vec            Vec;

occ::handle<Geom_Geometry> Geom_TrimmedCurve::Copy() const
{

  occ::handle<Geom_TrimmedCurve> Tc = new TrimmedCurve(basisCurve, uTrim1, uTrim2);
  return Tc;
}

Geom_TrimmedCurve::Geom_TrimmedCurve(const occ::handle<Geom_Curve>& C,
                                     const double                   U1,
                                     const double                   U2,
                                     const bool                     Sense,
                                     const bool                     theAdjustPeriodic)
    : uTrim1(U1),
      uTrim2(U2)
{

  occ::handle<Geom_TrimmedCurve> T = occ::down_cast<Geom_TrimmedCurve>(C);
  if (!T.IsNull())
    basisCurve = occ::down_cast<Geom_Curve>(T->BasisCurve()->Copy());
  else
    basisCurve = occ::down_cast<Geom_Curve>(C->Copy());

  SetTrim(U1, U2, Sense, theAdjustPeriodic);
}

void Geom_TrimmedCurve::Reverse()
{
  double U1 = basisCurve->ReversedParameter(uTrim2);
  double U2 = basisCurve->ReversedParameter(uTrim1);
  basisCurve->Reverse();
  SetTrim(U1, U2, true, false);
}

double Geom_TrimmedCurve::ReversedParameter(const double U) const
{
  return basisCurve->ReversedParameter(U);
}

void Geom_TrimmedCurve::SetTrim(const double U1,
                                const double U2,
                                const bool   Sense,
                                const bool   theAdjustPeriodic)
{
  bool sameSense = true;
  if (U1 == U2)
    throw Standard_ConstructionError("Geom_TrimmedCurve::U1 == U2");

  double Udeb = basisCurve->FirstParameter();
  double Ufin = basisCurve->LastParameter();

  if (basisCurve->IsPeriodic())
  {
    sameSense = Sense;

    uTrim1 = U1;
    uTrim2 = U2;
    if (theAdjustPeriodic)
      ElCLib::AdjustPeriodic(Udeb,
                             Ufin,
                             std::min(std::abs(uTrim2 - uTrim1) / 2, Precision::PConfusion()),
                             uTrim1,
                             uTrim2);
  }

  else
  {
    if (U1 < U2)
    {
      sameSense = Sense;
      uTrim1    = U1;
      uTrim2    = U2;
    }
    else
    {
      sameSense = !Sense;
      uTrim1    = U2;
      uTrim2    = U1;
    }

    if ((Udeb - uTrim1 > Precision::PConfusion()) || (uTrim2 - Ufin > Precision::PConfusion()))
      throw Standard_ConstructionError("Geom_TrimmedCurve::parameters out of range");
  }
  if (!sameSense)
  {
    Reverse();
  }
}

bool Geom_TrimmedCurve::IsClosed() const
{
  return (StartPoint().Distance(EndPoint()) <= gp::Resolution());
}

bool Geom_TrimmedCurve::IsPeriodic() const
{

  return false;
}

double Geom_TrimmedCurve::Period() const
{
  return basisCurve->Period();
}

GeomAbs_Shape Geom_TrimmedCurve::Continuity() const
{

  return basisCurve->Continuity();
}

occ::handle<Geom_Curve> Geom_TrimmedCurve::BasisCurve() const
{

  return basisCurve;
}

void Geom_TrimmedCurve::D0(const double U, Pnt& P) const
{

  basisCurve->D0(U, P);
}

void Geom_TrimmedCurve::D1(const double U, Pnt& P, Vec& V1) const
{

  basisCurve->D1(U, P, V1);
}

void Geom_TrimmedCurve::D2(const double U, Pnt& P, Vec& V1, Vec& V2) const
{

  basisCurve->D2(U, P, V1, V2);
}

void Geom_TrimmedCurve::D3(const double U, Pnt& P, Vec& V1, Vec& V2, Vec& V3) const
{

  basisCurve->D3(U, P, V1, V2, V3);
}

Vec Geom_TrimmedCurve::DN(const double U, const int N) const
{
  return basisCurve->DN(U, N);
}

Pnt Geom_TrimmedCurve::EndPoint() const
{

  return basisCurve->Value(uTrim2);
}

double Geom_TrimmedCurve::FirstParameter() const
{

  return uTrim1;
}

double Geom_TrimmedCurve::LastParameter() const
{

  return uTrim2;
}

Pnt Geom_TrimmedCurve::StartPoint() const
{

  return basisCurve->Value(uTrim1);
}

bool Geom_TrimmedCurve::IsCN(const int N) const
{

  Standard_RangeError_Raise_if(N < 0, " ");
  return basisCurve->IsCN(N);
}

void Geom_TrimmedCurve::Transform(const Trsf& T)
{
  basisCurve->Transform(T);
  double U1 = basisCurve->TransformedParameter(uTrim1, T);
  double U2 = basisCurve->TransformedParameter(uTrim2, T);
  SetTrim(U1, U2, true, false);
}

double Geom_TrimmedCurve::TransformedParameter(const double U, const gp_Trsf& T) const
{
  return basisCurve->TransformedParameter(U, T);
}

double Geom_TrimmedCurve::ParametricTransformation(const gp_Trsf& T) const
{
  return basisCurve->ParametricTransformation(T);
}

void Geom_TrimmedCurve::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_BoundedCurve)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, basisCurve.get())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, uTrim1)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, uTrim2)
}
