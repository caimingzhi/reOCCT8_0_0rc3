#include <Adaptor2d_Curve2d.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor.hpp>
#include <gp_Hypr2d.hpp>

occ::handle<Geom2d_Curve> Geom2dAdaptor::MakeCurve(const Adaptor2d_Curve2d& HC)
{
  occ::handle<Geom2d_Curve> C2D;
  switch (HC.GetType())
  {

    case GeomAbs_Line:
    {
      occ::handle<Geom2d_Line> GL = new Geom2d_Line(HC.Line());
      C2D                         = GL;
    }
    break;

    case GeomAbs_Circle:
    {
      occ::handle<Geom2d_Circle> GL = new Geom2d_Circle(HC.Circle());
      C2D                           = GL;
    }
    break;

    case GeomAbs_Ellipse:
    {
      occ::handle<Geom2d_Ellipse> GL = new Geom2d_Ellipse(HC.Ellipse());
      C2D                            = GL;
    }
    break;

    case GeomAbs_Parabola:
    {
      occ::handle<Geom2d_Parabola> GL = new Geom2d_Parabola(HC.Parabola());
      C2D                             = GL;
    }
    break;

    case GeomAbs_Hyperbola:
    {
      occ::handle<Geom2d_Hyperbola> GL = new Geom2d_Hyperbola(HC.Hyperbola());
      C2D                              = GL;
    }
    break;

    case GeomAbs_BezierCurve:
    {
      C2D = HC.Bezier();
    }
    break;

    case GeomAbs_BSplineCurve:
    {
      C2D = HC.BSpline();
    }
    break;

    case GeomAbs_OffsetCurve:
    {
      const Geom2dAdaptor_Curve* pGAC = dynamic_cast<const Geom2dAdaptor_Curve*>(&HC);
      if (pGAC != nullptr)
      {
        C2D = pGAC->Curve();
      }
      else
      {
        throw Standard_DomainError("Geom2dAdaptor::MakeCurve, Not Geom2dAdaptor_Curve");
      }
    }
    break;

    default:
      throw Standard_DomainError("Geom2dAdaptor::MakeCurve, OtherCurve");
  }

  if (!C2D.IsNull()
      && ((HC.FirstParameter() != C2D->FirstParameter())
          || (HC.LastParameter() != C2D->LastParameter())))
  {

    if (C2D->IsPeriodic()
        || (HC.FirstParameter() >= C2D->FirstParameter()
            && HC.LastParameter() <= C2D->LastParameter()))
    {
      C2D = new Geom2d_TrimmedCurve(C2D, HC.FirstParameter(), HC.LastParameter());
    }
    else
    {
      double tf = std::max(HC.FirstParameter(), C2D->FirstParameter());
      double tl = std::min(HC.LastParameter(), C2D->LastParameter());
      C2D       = new Geom2d_TrimmedCurve(C2D, tf, tl);
    }
  }

  return C2D;
}
