#include <BRep_Tool.hpp>
#include <Draw_Display.hpp>
#include <DrawDim_PlanarDiameter.hpp>
#include <ElCLib.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Curve.hpp>
#include <gp_Circ.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawDim_PlanarDiameter, DrawDim_PlanarDimension)

//=================================================================================================

DrawDim_PlanarDiameter::DrawDim_PlanarDiameter(const TopoDS_Face& face, const TopoDS_Shape& c)
{
  myPlane  = face;
  myCircle = c;
}

//=================================================================================================

DrawDim_PlanarDiameter::DrawDim_PlanarDiameter(const TopoDS_Shape& c)
{
  myCircle = c;
}

//=================================================================================================

void DrawDim_PlanarDiameter::DrawOn(Draw_Display& dis) const
{
  if (myCircle.ShapeType() == TopAbs_EDGE)
  {
    double                  f, l;
    occ::handle<Geom_Curve> curve = BRep_Tool::Curve(TopoDS::Edge(myCircle), f, l);
    if (curve->IsKind(STANDARD_TYPE(Geom_Circle)))
    {
      gp_Circ       circle = occ::down_cast<Geom_Circle>(curve)->Circ();
      TopoDS_Vertex vf, vl;
      TopExp::Vertices(TopoDS::Edge(myCircle), vf, vl);
      const gp_Pnt first    = BRep_Tool::Pnt(vf);
      double       parfirst = ElCLib::Parameter(circle, first);
      double       parlast  = (parfirst + M_PI);
      gp_Pnt       last     = ElCLib::Value(parlast, circle);
      //
      dis.Draw(first, last);
      gp_Pnt p((first.X() + last.X()) / 2, (first.Y() + last.Y()) / 2, (first.Z() + last.Z()) / 2);
      DrawText(p, dis);
      return;
    }
  }
#ifdef OCCT_DEBUG
  std::cout << " DrawDim_PlanarDiameter::DrawOn : dimension error" << std::endl;
#endif
}
