#include <ElSLib.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Geometry.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <gp.hpp>
#include <gp_Ax3.hpp>
#include <gp_Circ.hpp>
#include <gp_Pnt.hpp>
#include <gp_Torus.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_DimensionError.hpp>
#include <Standard_RangeError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_ToroidalSurface, Geom_ElementarySurface)

typedef Geom_ToroidalSurface       ToroidalSurface;
typedef NCollection_Array1<double> Array1OfReal;
typedef gp_Ax1                     Ax1;
typedef gp_Ax2                     Ax2;
typedef gp_Ax3                     Ax3;
typedef gp_Circ                    Circ;
typedef gp_Dir                     Dir;
typedef gp_Pnt                     Pnt;
typedef gp_Trsf                    Trsf;
typedef gp_Vec                     Vec;
typedef gp_XYZ                     XYZ;

//=================================================================================================

occ::handle<Geom_Geometry> Geom_ToroidalSurface::Copy() const
{

  occ::handle<Geom_ToroidalSurface> Cs;
  Cs = new ToroidalSurface(pos, majorRadius, minorRadius);
  return Cs;
}

//=================================================================================================

Geom_ToroidalSurface::Geom_ToroidalSurface(const Ax3&   A3,
                                           const double MajorRadius,
                                           const double MinorRadius)

    : majorRadius(MajorRadius),
      minorRadius(MinorRadius)
{

  if (MinorRadius < 0.0 || MajorRadius < 0.0)
  {
    throw Standard_ConstructionError();
  }
  else
  {
    pos = A3;
  }
}

//=================================================================================================

Geom_ToroidalSurface::Geom_ToroidalSurface(const gp_Torus& T)
    : majorRadius(T.MajorRadius()),
      minorRadius(T.MinorRadius())
{

  pos = T.Position();
}

//=================================================================================================

double Geom_ToroidalSurface::MajorRadius() const
{

  return majorRadius;
}

//=================================================================================================

double Geom_ToroidalSurface::MinorRadius() const
{

  return minorRadius;
}

//=================================================================================================

double Geom_ToroidalSurface::UReversedParameter(const double U) const
{

  return (2. * M_PI - U);
}

//=================================================================================================

double Geom_ToroidalSurface::VReversedParameter(const double V) const
{

  return (2. * M_PI - V);
}

//=================================================================================================

bool Geom_ToroidalSurface::IsUClosed() const
{

  return true;
}

//=================================================================================================

bool Geom_ToroidalSurface::IsVClosed() const
{

  return true;
}

//=================================================================================================

bool Geom_ToroidalSurface::IsUPeriodic() const
{

  return true;
}

//=================================================================================================

bool Geom_ToroidalSurface::IsVPeriodic() const
{

  return true;
}

//=================================================================================================

void Geom_ToroidalSurface::SetMajorRadius(const double MajorRadius)
{

  if (MajorRadius - minorRadius <= gp::Resolution())
    throw Standard_ConstructionError();
  else
    majorRadius = MajorRadius;
}

//=================================================================================================

void Geom_ToroidalSurface::SetMinorRadius(const double MinorRadius)
{

  if (MinorRadius < 0.0 || majorRadius - MinorRadius <= gp::Resolution())
    throw Standard_ConstructionError();
  else
    minorRadius = MinorRadius;
}

//=================================================================================================

void Geom_ToroidalSurface::SetTorus(const gp_Torus& T)
{

  minorRadius = T.MinorRadius();
  majorRadius = T.MajorRadius();
  pos         = T.Position();
}

//=================================================================================================

double Geom_ToroidalSurface::Area() const
{
  return 4.0 * M_PI * M_PI * minorRadius * majorRadius;
}

//=================================================================================================

void Geom_ToroidalSurface::Bounds(double& U1, double& U2, double& V1, double& V2) const
{

  U1 = 0.0;
  V1 = 0.0;
  U2 = 2 * M_PI;
  V2 = 2 * M_PI;
}

//=================================================================================================

void Geom_ToroidalSurface::Coefficients(Array1OfReal& Coef) const
{

  gp_Torus Tor(pos, majorRadius, minorRadius);
  Tor.Coefficients(Coef);
}

//=================================================================================================

void Geom_ToroidalSurface::D0(const double U, const double V, Pnt& P) const
{

  ElSLib::TorusD0(U, V, pos, majorRadius, minorRadius, P);
}

//=================================================================================================

void Geom_ToroidalSurface::D1(const double U, const double V, Pnt& P, Vec& D1U, Vec& D1V) const
{
  ElSLib::TorusD1(U, V, pos, majorRadius, minorRadius, P, D1U, D1V);
}

//=================================================================================================

void Geom_ToroidalSurface::D2(const double U,
                              const double V,
                              Pnt&         P,
                              Vec&         D1U,
                              Vec&         D1V,
                              Vec&         D2U,
                              Vec&         D2V,
                              Vec&         D2UV) const
{
  ElSLib::TorusD2(U, V, pos, majorRadius, minorRadius, P, D1U, D1V, D2U, D2V, D2UV);
}

//=================================================================================================

void Geom_ToroidalSurface::D3(const double U,
                              const double V,
                              Pnt&         P,
                              Vec&         D1U,
                              Vec&         D1V,
                              Vec&         D2U,
                              Vec&         D2V,
                              Vec&         D2UV,
                              Vec&         D3U,
                              Vec&         D3V,
                              Vec&         D3UUV,
                              Vec&         D3UVV) const
{

  ElSLib::TorusD3(U,
                  V,
                  pos,
                  majorRadius,
                  minorRadius,
                  P,
                  D1U,
                  D1V,
                  D2U,
                  D2V,
                  D2UV,
                  D3U,
                  D3V,
                  D3UUV,
                  D3UVV);
}

//=================================================================================================

Vec Geom_ToroidalSurface::DN(const double U, const double V, const int Nu, const int Nv) const
{

  Standard_RangeError_Raise_if(Nu + Nv < 1 || Nu < 0 || Nv < 0, "  ");
  return ElSLib::TorusDN(U, V, pos, majorRadius, minorRadius, Nu, Nv);
}

//=================================================================================================

gp_Torus Geom_ToroidalSurface::Torus() const
{

  return gp_Torus(pos, majorRadius, minorRadius);
}

//=================================================================================================

occ::handle<Geom_Curve> Geom_ToroidalSurface::UIso(const double U) const
{
  occ::handle<Geom_Circle> GC =
    new Geom_Circle(ElSLib::TorusUIso(pos, majorRadius, minorRadius, U));
  return GC;
}

//=================================================================================================

occ::handle<Geom_Curve> Geom_ToroidalSurface::VIso(const double V) const
{
  occ::handle<Geom_Circle> GC =
    new Geom_Circle(ElSLib::TorusVIso(pos, majorRadius, minorRadius, V));
  return GC;
}

//=================================================================================================

double Geom_ToroidalSurface::Volume() const
{

  return (M_PI * minorRadius * minorRadius) * (2.0 * M_PI * majorRadius);
}

//=================================================================================================

void Geom_ToroidalSurface::Transform(const Trsf& T)
{

  majorRadius = majorRadius * std::abs(T.ScaleFactor());
  minorRadius = minorRadius * std::abs(T.ScaleFactor());
  pos.Transform(T);
}

//=================================================================================================

void Geom_ToroidalSurface::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_ElementarySurface)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, majorRadius)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, minorRadius)
}
