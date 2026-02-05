#include <ElCLib.hpp>
#include <Geom_Line.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Precision.hpp>
#include <Standard_RangeError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Line, Geom_Curve)

//=================================================================================================

occ::handle<Geom_Geometry> Geom_Line::Copy() const
{

  occ::handle<Geom_Line> L;
  L = new Geom_Line(pos);
  return L;
}

//=================================================================================================

Geom_Line::Geom_Line(const gp_Ax1& A)
    : pos(A)
{
}

//=================================================================================================

Geom_Line::Geom_Line(const gp_Lin& L)
    : pos(L.Position())
{
}

//=================================================================================================

Geom_Line::Geom_Line(const gp_Pnt& P, const gp_Dir& V)
    : pos(P, V)
{
}

//=================================================================================================

void Geom_Line::Reverse()
{
  pos.Reverse();
}

//=================================================================================================

double Geom_Line::ReversedParameter(const double U) const
{
  return (-U);
}

//=================================================================================================

void Geom_Line::SetDirection(const gp_Dir& V)
{
  pos.SetDirection(V);
}

//=================================================================================================

void Geom_Line::SetLin(const gp_Lin& L)
{
  pos = L.Position();
}

//=================================================================================================

void Geom_Line::SetLocation(const gp_Pnt& P)
{
  pos.SetLocation(P);
}

//=================================================================================================

void Geom_Line::SetPosition(const gp_Ax1& A1)
{
  pos = A1;
}

//=================================================================================================

const gp_Ax1& Geom_Line::Position() const
{
  return pos;
}

//=================================================================================================

bool Geom_Line::IsClosed() const
{
  return false;
}

//=================================================================================================

bool Geom_Line::IsPeriodic() const
{
  return false;
}

//=================================================================================================

GeomAbs_Shape Geom_Line::Continuity() const
{
  return GeomAbs_CN;
}

//=================================================================================================

double Geom_Line::FirstParameter() const
{
  return -Precision::Infinite();
}

//=================================================================================================

double Geom_Line::LastParameter() const
{
  return Precision::Infinite();
}

//=================================================================================================

gp_Lin Geom_Line::Lin() const
{
  return gp_Lin(pos);
}

//=================================================================================================

bool Geom_Line::IsCN(const int) const
{
  return true;
}

//=================================================================================================

void Geom_Line::Transform(const gp_Trsf& T)
{
  pos.Transform(T);
}

//=================================================================================================

void Geom_Line::D0(const double U, gp_Pnt& P) const
{
  P = ElCLib::LineValue(U, pos);
}

//=================================================================================================

void Geom_Line::D1(const double U, gp_Pnt& P, gp_Vec& V1) const
{

  ElCLib::LineD1(U, pos, P, V1);
}

//=================================================================================================

void Geom_Line::D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
{

  ElCLib::LineD1(U, pos, P, V1);
  V2.SetCoord(0.0, 0.0, 0.0);
}

//=================================================================================================

void Geom_Line::D3(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const
{

  ElCLib::LineD1(U, pos, P, V1);
  V2.SetCoord(0.0, 0.0, 0.0);
  V3.SetCoord(0.0, 0.0, 0.0);
}

//=================================================================================================

gp_Vec Geom_Line::DN(const double, const int N) const
{

  Standard_RangeError_Raise_if(N <= 0, " ");
  if (N == 1)
    return gp_Vec(pos.Direction());
  else
    return gp_Vec(0.0, 0.0, 0.0);
}

//=================================================================================================

double Geom_Line::TransformedParameter(const double U, const gp_Trsf& T) const
{
  if (Precision::IsInfinite(U))
    return U;
  return U * std::abs(T.ScaleFactor());
}

//=================================================================================================

double Geom_Line::ParametricTransformation(const gp_Trsf& T) const
{
  return std::abs(T.ScaleFactor());
}

//=================================================================================================

void Geom_Line::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_Curve)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &pos)
}
