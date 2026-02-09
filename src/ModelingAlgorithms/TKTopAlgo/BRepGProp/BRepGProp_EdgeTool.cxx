

#include <BRepAdaptor_Curve.hpp>
#include <BRepGProp_EdgeTool.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

double BRepGProp_EdgeTool::FirstParameter(const BRepAdaptor_Curve& C)
{
  return C.FirstParameter();
}

double BRepGProp_EdgeTool::LastParameter(const BRepAdaptor_Curve& C)
{
  return C.LastParameter();
}

int BRepGProp_EdgeTool::IntegrationOrder(const BRepAdaptor_Curve& BAC)
{
  switch (BAC.GetType())
  {

    case GeomAbs_Line:
      return 2;

    case GeomAbs_Parabola:
      return 5;

    case GeomAbs_BezierCurve:
    {
      const GeomAdaptor_Curve&       GAC = BAC.Curve();
      const occ::handle<Geom_Curve>& GC  = GAC.Curve();
      occ::handle<Geom_BezierCurve>  GBZC(occ::down_cast<Geom_BezierCurve>(GC));
      int                            n = 2 * (GBZC->NbPoles()) - 1;
      return n;
    }
    break;
    case GeomAbs_BSplineCurve:
    {
      const GeomAdaptor_Curve&       GAC = BAC.Curve();
      const occ::handle<Geom_Curve>& GC  = GAC.Curve();
      occ::handle<Geom_BSplineCurve> GBSC(occ::down_cast<Geom_BSplineCurve>(GC));
      int                            n = 2 * (GBSC->NbPoles()) - 1;
      return n;
    }
    break;

    default:
      return 10;
  }
}

gp_Pnt BRepGProp_EdgeTool::Value(const BRepAdaptor_Curve& C, const double U)
{
  return C.Value(U);
}

void BRepGProp_EdgeTool::D1(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V1)
{
  C.D1(U, P, V1);
}

int BRepGProp_EdgeTool::NbIntervals(const BRepAdaptor_Curve& C, const GeomAbs_Shape S)
{

  BRepAdaptor_Curve* pC = (BRepAdaptor_Curve*)&C;

  return pC->NbIntervals(S);
}

void BRepGProp_EdgeTool::Intervals(const BRepAdaptor_Curve&    C,
                                   NCollection_Array1<double>& T,
                                   const GeomAbs_Shape         S)
{
  BRepAdaptor_Curve* pC = (BRepAdaptor_Curve*)&C;

  pC->Intervals(T, S);
}
