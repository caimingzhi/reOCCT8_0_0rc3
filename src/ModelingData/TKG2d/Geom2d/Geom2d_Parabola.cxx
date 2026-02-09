#include <ElCLib.hpp>
#include <Geom2d_Parabola.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_XY.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_RangeError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom2d_Parabola, Geom2d_Conic)

typedef Geom2d_Parabola Parabola;
typedef gp_Ax2d         Ax2d;
typedef gp_Dir2d        Dir2d;
typedef gp_Pnt2d        Pnt2d;
typedef gp_Vec2d        Vec2d;
typedef gp_Trsf2d       Trsf2d;
typedef gp_XY           XY;

occ::handle<Geom2d_Geometry> Geom2d_Parabola::Copy() const
{
  occ::handle<Geom2d_Parabola> Prb;
  Prb = new Parabola(pos, focalLength);
  return Prb;
}

Geom2d_Parabola::Geom2d_Parabola(const gp_Parab2d& Prb)
{
  focalLength = Prb.Focal();
  pos         = Prb.Axis();
}

Geom2d_Parabola::Geom2d_Parabola(const Ax2d& MirrorAxis, const double Focal, const bool Sense)
    : focalLength(Focal)
{
  if (Focal < 0.0)
  {
    throw Standard_ConstructionError();
  }
  pos = gp_Ax22d(MirrorAxis, Sense);
}

Geom2d_Parabola::Geom2d_Parabola(const gp_Ax22d& Axis, const double Focal)
    : focalLength(Focal)
{
  if (Focal < 0.0)
  {
    throw Standard_ConstructionError();
  }
  pos = Axis;
}

Geom2d_Parabola::Geom2d_Parabola(const Ax2d& D, const Pnt2d& F)
{

  gp_Parab2d Prb(D, F);
  pos         = Prb.Axis();
  focalLength = Prb.Focal();
}

void Geom2d_Parabola::SetFocal(const double Focal)
{
  if (Focal < 0.0)
    throw Standard_ConstructionError();
  focalLength = Focal;
}

void Geom2d_Parabola::SetParab2d(const gp_Parab2d& Prb)
{
  focalLength = Prb.Focal();
  pos         = Prb.Axis();
}

gp_Parab2d Geom2d_Parabola::Parab2d() const
{
  return gp_Parab2d(pos, focalLength);
}

double Geom2d_Parabola::ReversedParameter(const double U) const
{
  return (-U);
}

double Geom2d_Parabola::FirstParameter() const
{
  return -Precision::Infinite();
}

double Geom2d_Parabola::LastParameter() const
{
  return Precision::Infinite();
}

bool Geom2d_Parabola::IsClosed() const
{
  return false;
}

bool Geom2d_Parabola::IsPeriodic() const
{
  return false;
}

Ax2d Geom2d_Parabola::Directrix() const
{
  gp_Parab2d Prb(pos, focalLength);
  return Prb.Directrix();
}

double Geom2d_Parabola::Eccentricity() const
{
  return 1.0;
}

Pnt2d Geom2d_Parabola::Focus() const
{
  XY Pxy = pos.XDirection().XY();
  Pxy.Multiply(focalLength);
  Pxy.Add(pos.Location().XY());
  return Pnt2d(Pxy);
}

double Geom2d_Parabola::Focal() const
{
  return focalLength;
}

double Geom2d_Parabola::Parameter() const
{
  return 2.0 * focalLength;
}

void Geom2d_Parabola::D0(const double U, Pnt2d& P) const
{
  P = ElCLib::ParabolaValue(U, pos, focalLength);
}

void Geom2d_Parabola::D1(const double U, Pnt2d& P, Vec2d& V1) const
{
  ElCLib::ParabolaD1(U, pos, focalLength, P, V1);
}

void Geom2d_Parabola::D2(const double U, Pnt2d& P, Vec2d& V1, Vec2d& V2) const
{
  ElCLib::ParabolaD2(U, pos, focalLength, P, V1, V2);
}

void Geom2d_Parabola::D3(const double U, Pnt2d& P, Vec2d& V1, Vec2d& V2, Vec2d& V3) const
{
  ElCLib::ParabolaD2(U, pos, focalLength, P, V1, V2);
  V3.SetCoord(0.0, 0.0);
}

Vec2d Geom2d_Parabola::DN(const double U, const int N) const
{
  Standard_RangeError_Raise_if(N < 1, " ");
  return ElCLib::ParabolaDN(U, pos, focalLength, N);
}

void Geom2d_Parabola::Transform(const Trsf2d& T)
{
  focalLength *= std::abs(T.ScaleFactor());
  pos.Transform(T);
}

double Geom2d_Parabola::TransformedParameter(const double U, const gp_Trsf2d& T) const
{
  if (Precision::IsInfinite(U))
    return U;
  return U * std::abs(T.ScaleFactor());
}

double Geom2d_Parabola::ParametricTransformation(const gp_Trsf2d& T) const
{
  return std::abs(T.ScaleFactor());
}

void Geom2d_Parabola::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom2d_Conic)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, focalLength)
}
