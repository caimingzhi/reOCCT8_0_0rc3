#include <BSplCLib.hpp>
#include <BSplSLib.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_Curve.hpp>
#include "Geom_ExtrusionUtils.hpp"
#include <Geom_Geometry.hpp>
#include <Geom_Line.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_UndefinedDerivative.hpp>
#include <gp.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir.hpp>
#include <gp_GTrsf2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Precision.hpp>
#include <Standard_RangeError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_SurfaceOfLinearExtrusion, Geom_SweptSurface)

#define POLES (poles->Array2())
#define WEIGHTS (weights->Array2())
#define UKNOTS (uknots->Array1())
#define VKNOTS (vknots->Array1())
#define UFKNOTS (ufknots->Array1())
#define VFKNOTS (vfknots->Array1())
#define FMULTS (BSplCLib::NoMults())

typedef Geom_SurfaceOfLinearExtrusion SurfaceOfLinearExtrusion;
typedef Geom_Curve                    Curve;
typedef gp_Dir                        Dir;
typedef gp_Pnt                        Pnt;
typedef gp_Trsf                       Trsf;
typedef gp_Vec                        Vec;
typedef gp_XYZ                        XYZ;

occ::handle<Geom_Geometry> Geom_SurfaceOfLinearExtrusion::Copy() const
{

  occ::handle<Geom_SurfaceOfLinearExtrusion> Sr;
  Sr = new SurfaceOfLinearExtrusion(basisCurve, direction);
  return Sr;
}

Geom_SurfaceOfLinearExtrusion::Geom_SurfaceOfLinearExtrusion(const occ::handle<Geom_Curve>& C,
                                                             const Dir&                     V)
{
  basisCurve = occ::down_cast<Geom_Curve>(C->Copy());
  direction  = V;
  smooth     = C->Continuity();
}

void Geom_SurfaceOfLinearExtrusion::UReverse()
{

  basisCurve->Reverse();
}

double Geom_SurfaceOfLinearExtrusion::UReversedParameter(const double U) const
{

  return basisCurve->ReversedParameter(U);
}

void Geom_SurfaceOfLinearExtrusion::VReverse()
{
  direction.Reverse();
}

double Geom_SurfaceOfLinearExtrusion::VReversedParameter(const double V) const
{

  return (-V);
}

void Geom_SurfaceOfLinearExtrusion::SetDirection(const Dir& V)
{
  direction = V;
}

void Geom_SurfaceOfLinearExtrusion::SetBasisCurve(const occ::handle<Geom_Curve>& C)
{
  smooth     = C->Continuity();
  basisCurve = occ::down_cast<Geom_Curve>(C->Copy());
}

void Geom_SurfaceOfLinearExtrusion::Bounds(double& U1, double& U2, double& V1, double& V2) const
{

  V1 = -Precision::Infinite();
  V2 = Precision::Infinite();
  U1 = basisCurve->FirstParameter();
  U2 = basisCurve->LastParameter();
}

void Geom_SurfaceOfLinearExtrusion::D0(const double U, const double V, Pnt& P) const
{
  Geom_ExtrusionUtils::D0(U, V, *basisCurve, direction.XYZ(), P);
}

void Geom_SurfaceOfLinearExtrusion::D1(const double U,
                                       const double V,
                                       Pnt&         P,
                                       Vec&         D1U,
                                       Vec&         D1V) const
{
  Geom_ExtrusionUtils::D1(U, V, *basisCurve, direction.XYZ(), P, D1U, D1V);
}

void Geom_SurfaceOfLinearExtrusion::D2(const double U,
                                       const double V,
                                       Pnt&         P,
                                       Vec&         D1U,
                                       Vec&         D1V,
                                       Vec&         D2U,
                                       Vec&         D2V,
                                       Vec&         D2UV) const
{
  Geom_ExtrusionUtils::D2(U, V, *basisCurve, direction.XYZ(), P, D1U, D1V, D2U, D2V, D2UV);
}

void Geom_SurfaceOfLinearExtrusion::D3(const double U,
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
  Geom_ExtrusionUtils::
    D3(U, V, *basisCurve, direction.XYZ(), P, D1U, D1V, D2U, D2V, D2UV, D3U, D3V, D3UUV, D3UVV);
}

Vec Geom_SurfaceOfLinearExtrusion::DN(const double U,
                                      const double,
                                      const int Nu,
                                      const int Nv) const
{
  Standard_RangeError_Raise_if(Nu + Nv < 1 || Nu < 0 || Nv < 0, " ");
  return Geom_ExtrusionUtils::DN(U, *basisCurve, direction.XYZ(), Nu, Nv);
}

occ::handle<Geom_Curve> Geom_SurfaceOfLinearExtrusion::UIso(const double U) const
{

  occ::handle<Geom_Line> L;
  L = new Geom_Line(basisCurve->Value(U), direction);
  return L;
}

occ::handle<Geom_Curve> Geom_SurfaceOfLinearExtrusion::VIso(const double V) const
{

  Vec Vdir(direction);
  Vdir.Multiply(V);
  occ::handle<Geom_Curve> C;
  C = occ::down_cast<Geom_Curve>(basisCurve->Translated(Vdir));
  return C;
}

bool Geom_SurfaceOfLinearExtrusion::IsCNu(const int N) const
{

  Standard_RangeError_Raise_if(N < 0, " ");
  return basisCurve->IsCN(N);
}

bool Geom_SurfaceOfLinearExtrusion::IsCNv(const int) const
{

  return true;
}

void Geom_SurfaceOfLinearExtrusion::Transform(const Trsf& T)
{
  direction.Transform(T);
  basisCurve->Transform(T);
}

bool Geom_SurfaceOfLinearExtrusion::IsUClosed() const
{

  return basisCurve->IsClosed();
}

bool Geom_SurfaceOfLinearExtrusion::IsUPeriodic() const
{

  return basisCurve->IsPeriodic();
}

bool Geom_SurfaceOfLinearExtrusion::IsVClosed() const
{

  return false;
}

bool Geom_SurfaceOfLinearExtrusion::IsVPeriodic() const
{

  return false;
}

void Geom_SurfaceOfLinearExtrusion::TransformParameters(double&        U,
                                                        double&        V,
                                                        const gp_Trsf& T) const
{
  U = basisCurve->TransformedParameter(U, T);
  if (!Precision::IsInfinite(V))
    V *= std::abs(T.ScaleFactor());
}

gp_GTrsf2d Geom_SurfaceOfLinearExtrusion::ParametricTransformation(const gp_Trsf& T) const
{

  gp_GTrsf2d TV;
  gp_Ax2d    Axis(gp::Origin2d(), gp::DX2d());
  TV.SetAffinity(Axis, std::abs(T.ScaleFactor()));

  gp_GTrsf2d TU;
  Axis = gp_Ax2d(gp::Origin2d(), gp::DY2d());
  TU.SetAffinity(Axis, basisCurve->ParametricTransformation(T));

  return TU * TV;
}

void Geom_SurfaceOfLinearExtrusion::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Geom_SweptSurface)
}
