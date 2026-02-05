#include <GeomAdaptor.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Line.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <Geom_TrimmedCurve.hpp>

//=================================================================================================

occ::handle<Geom_Curve> GeomAdaptor::MakeCurve(const Adaptor3d_Curve& HC)
{
  occ::handle<Geom_Curve> C;

  switch (HC.GetType())
  {
    case GeomAbs_Line:
      C = new Geom_Line(HC.Line());
      break;

    case GeomAbs_Circle:
      C = new Geom_Circle(HC.Circle());
      break;

    case GeomAbs_Ellipse:
      C = new Geom_Ellipse(HC.Ellipse());
      break;

    case GeomAbs_Parabola:
      C = new Geom_Parabola(HC.Parabola());
      break;

    case GeomAbs_Hyperbola:
      C = new Geom_Hyperbola(HC.Hyperbola());
      break;

    case GeomAbs_BezierCurve:
      C = occ::down_cast<Geom_BezierCurve>(HC.Bezier()->Copy());
      break;

    case GeomAbs_BSplineCurve:
      C = occ::down_cast<Geom_BSplineCurve>(HC.BSpline()->Copy());
      break;

    default:
      throw Standard_DomainError("GeomAdaptor::MakeCurve : OtherCurve");
  }

  // trim the curve if necassary.
  if ((!C.IsNull() && (HC.FirstParameter() != C->FirstParameter()))
      || (HC.LastParameter() != C->LastParameter()))
  {

    C = new Geom_TrimmedCurve(C, HC.FirstParameter(), HC.LastParameter());
  }

  return C;
}

//=================================================================================================

occ::handle<Geom_Surface> GeomAdaptor::MakeSurface(const Adaptor3d_Surface& HS,
                                                   const bool               theTrimFlag)
{
  occ::handle<Geom_Surface> S;

  switch (HS.GetType())
  {
    case GeomAbs_Plane:
      S = new Geom_Plane(HS.Plane());
      break;

    case GeomAbs_Cylinder:
      S = new Geom_CylindricalSurface(HS.Cylinder());
      break;

    case GeomAbs_Cone:
      S = new Geom_ConicalSurface(HS.Cone());
      break;

    case GeomAbs_Sphere:
      S = new Geom_SphericalSurface(HS.Sphere());
      break;

    case GeomAbs_Torus:
      S = new Geom_ToroidalSurface(HS.Torus());
      break;

    case GeomAbs_BezierSurface:
      S = occ::down_cast<Geom_BezierSurface>(HS.Bezier()->Copy());
      break;

    case GeomAbs_BSplineSurface:
      S = occ::down_cast<Geom_BSplineSurface>(HS.BSpline()->Copy());
      break;

    case GeomAbs_SurfaceOfRevolution:
      S = new Geom_SurfaceOfRevolution(GeomAdaptor::MakeCurve(*HS.BasisCurve()),
                                       HS.AxeOfRevolution());
      break;

    case GeomAbs_SurfaceOfExtrusion:
      S =
        new Geom_SurfaceOfLinearExtrusion(GeomAdaptor::MakeCurve(*HS.BasisCurve()), HS.Direction());
      break;

    case GeomAbs_OffsetSurface:
      S = new Geom_OffsetSurface(GeomAdaptor::MakeSurface(*HS.BasisSurface()), HS.OffsetValue());
      break;

    case GeomAbs_OtherSurface:
      throw Standard_DomainError("GeomAdaptor::MakeSurface : OtherSurface");
      break;
  }

  if (S.IsNull() || !theTrimFlag)
    return S;

  // trim the surface if necassary.
  double U1, U2, V1, V2;
  S->Bounds(U1, U2, V1, V2);
  if ((HS.FirstUParameter() != U1) || (HS.LastUParameter() != U2) || (HS.FirstVParameter() != V1)
      || (HS.LastVParameter() != V2))
  {

    S = new Geom_RectangularTrimmedSurface(S,
                                           HS.FirstUParameter(),
                                           HS.LastUParameter(),
                                           HS.FirstVParameter(),
                                           HS.LastVParameter());
  }

  return S;
}
