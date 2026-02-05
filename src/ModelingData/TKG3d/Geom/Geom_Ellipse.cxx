#include <ElCLib.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Geometry.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Elips.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_RangeError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Ellipse, Geom_Conic)

typedef gp_Ax1  Ax1;
typedef gp_Ax2  Ax2;
typedef gp_Pnt  Pnt;
typedef gp_Vec  Vec;
typedef gp_Trsf Trsf;
typedef gp_XYZ  XYZ;

//=================================================================================================

occ::handle<Geom_Geometry> Geom_Ellipse::Copy() const
{
  occ::handle<Geom_Ellipse> E;
  E = new Geom_Ellipse(pos, majorRadius, minorRadius);
  return E;
}

//=================================================================================================

Geom_Ellipse::Geom_Ellipse(const gp_Elips& E)
    : majorRadius(E.MajorRadius()),
      minorRadius(E.MinorRadius())
{
  pos = E.Position();
}

//=================================================================================================

Geom_Ellipse::Geom_Ellipse(const Ax2& A, const double MajorRadius, const double MinorRadius)
    : majorRadius(MajorRadius),
      minorRadius(MinorRadius)
{

  if (MajorRadius < MinorRadius || MinorRadius < 0.0)
  {
    throw Standard_ConstructionError();
  }
  pos = A;
}

//=================================================================================================

bool Geom_Ellipse::IsClosed() const
{
  return true;
}

//=================================================================================================

bool Geom_Ellipse::IsPeriodic() const
{
  return true;
}

//=================================================================================================

double Geom_Ellipse::FirstParameter() const
{
  return 0.0;
}

//=================================================================================================

double Geom_Ellipse::LastParameter() const
{
  return 2.0 * M_PI;
}

//=================================================================================================

double Geom_Ellipse::MajorRadius() const
{
  return majorRadius;
}

//=================================================================================================

double Geom_Ellipse::MinorRadius() const
{
  return minorRadius;
}

//=================================================================================================

void Geom_Ellipse::SetElips(const gp_Elips& E)
{

  majorRadius = E.MajorRadius();
  minorRadius = E.MinorRadius();
  pos         = E.Position();
}

//=================================================================================================

void Geom_Ellipse::SetMajorRadius(const double MajorRadius)
{

  if (MajorRadius < minorRadius)
    throw Standard_ConstructionError();
  else
    majorRadius = MajorRadius;
}

//=================================================================================================

void Geom_Ellipse::SetMinorRadius(const double MinorRadius)
{

  if (MinorRadius < 0 || majorRadius < MinorRadius)
  {
    throw Standard_ConstructionError();
  }
  else
  {
    minorRadius = MinorRadius;
  }
}

//=================================================================================================

gp_Elips Geom_Ellipse::Elips() const
{

  return gp_Elips(pos, majorRadius, minorRadius);
}

//=================================================================================================

double Geom_Ellipse::ReversedParameter(const double U) const
{
  return (2. * M_PI - U);
}

//=================================================================================================

Ax1 Geom_Ellipse::Directrix1() const
{

  gp_Elips Ev(pos, majorRadius, minorRadius);
  return Ev.Directrix1();
}

//=================================================================================================

Ax1 Geom_Ellipse::Directrix2() const
{

  gp_Elips Ev(pos, majorRadius, minorRadius);
  return Ev.Directrix2();
}

//=================================================================================================

void Geom_Ellipse::D0(const double U, gp_Pnt& P) const
{

  P = ElCLib::EllipseValue(U, pos, majorRadius, minorRadius);
}

//=================================================================================================

void Geom_Ellipse::D1(const double U, Pnt& P, Vec& V1) const
{

  ElCLib::EllipseD1(U, pos, majorRadius, minorRadius, P, V1);
}

//=================================================================================================

void Geom_Ellipse::D2(const double U, Pnt& P, Vec& V1, Vec& V2) const
{

  ElCLib::EllipseD2(U, pos, majorRadius, minorRadius, P, V1, V2);
}

//=================================================================================================

void Geom_Ellipse::D3(const double U, Pnt& P, Vec& V1, Vec& V2, Vec& V3) const
{

  ElCLib::EllipseD3(U, pos, majorRadius, minorRadius, P, V1, V2, V3);
}

//=================================================================================================

Vec Geom_Ellipse::DN(const double U, const int N) const
{

  Standard_RangeError_Raise_if(N < 1, " ");
  return ElCLib::EllipseDN(U, pos, majorRadius, minorRadius, N);
}

//=================================================================================================

double Geom_Ellipse::Eccentricity() const
{

  if (majorRadius == 0.0)
  {
    return 0.0;
  }
  else
  {
    return (std::sqrt(majorRadius * majorRadius - minorRadius * minorRadius)) / majorRadius;
  }
}

//=================================================================================================

double Geom_Ellipse::Focal() const
{

  return 2.0 * std::sqrt(majorRadius * majorRadius - minorRadius * minorRadius);
}

//=================================================================================================

Pnt Geom_Ellipse::Focus1() const
{

  double C = std::sqrt(majorRadius * majorRadius - minorRadius * minorRadius);
  double Xp, Yp, Zp, Xd, Yd, Zd;
  pos.Location().Coord(Xp, Yp, Zp);
  pos.XDirection().Coord(Xd, Yd, Zd);
  return Pnt(Xp + C * Xd, Yp + C * Yd, Zp + C * Zd);
}

//=================================================================================================

Pnt Geom_Ellipse::Focus2() const
{

  double C = std::sqrt(majorRadius * majorRadius - minorRadius * minorRadius);
  double Xp, Yp, Zp, Xd, Yd, Zd;
  pos.Location().Coord(Xp, Yp, Zp);
  pos.XDirection().Coord(Xd, Yd, Zd);
  return Pnt(Xp - C * Xd, Yp - C * Yd, Zp - C * Zd);
}

//=================================================================================================

double Geom_Ellipse::Parameter() const
{

  if (majorRadius == 0.0)
    return 0.0;
  else
    return (minorRadius * minorRadius) / majorRadius;
}

//=================================================================================================

void Geom_Ellipse::Transform(const Trsf& T)
{

  majorRadius = majorRadius * std::abs(T.ScaleFactor());
  minorRadius = minorRadius * std::abs(T.ScaleFactor());
  pos.Transform(T);
}

//=================================================================================================

void Geom_Ellipse::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_Conic)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, majorRadius)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, minorRadius)
}
