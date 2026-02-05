#include <BRep_Tool.hpp>
#include <Draw_Display.hpp>
#include <DrawDim.hpp>
#include <DrawDim_PlanarRadius.hpp>
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

IMPLEMENT_STANDARD_RTTIEXT(DrawDim_PlanarRadius, DrawDim_PlanarDimension)

//=================================================================================================

DrawDim_PlanarRadius::DrawDim_PlanarRadius(const TopoDS_Face& face, const TopoDS_Shape& c)
{
  myPlane  = face;
  myCircle = c;
}

//=================================================================================================

DrawDim_PlanarRadius::DrawDim_PlanarRadius(const TopoDS_Shape& c)
{
  myCircle = c;
}

//=================================================================================================

void DrawDim_PlanarRadius::DrawOn(Draw_Display& dis) const
{
  if (myCircle.ShapeType() == TopAbs_EDGE)
  {
    double                  f, l;
    occ::handle<Geom_Curve> curve = BRep_Tool::Curve(TopoDS::Edge(myCircle), f, l);
    if (curve->IsKind(STANDARD_TYPE(Geom_Circle)))
    {
      gp_Circ       circle = occ::down_cast<Geom_Circle>(curve)->Circ();
      const gp_Pnt& first  = circle.Location();
      TopoDS_Vertex vf, vl;
      TopExp::Vertices(TopoDS::Edge(myCircle), vf, vl);
      const gp_Pnt last = BRep_Tool::Pnt(vf);
      //
      dis.Draw(first, last);
      gp_Pnt p((first.X() + last.X()) / 2, (first.Y() + last.Y()) / 2, (first.Z() + last.Z()) / 2);
      DrawText(p, dis);
      return;
    }
  }
#ifdef OCCT_DEBUG
  std::cout << " DrawDim_PlanarRadius::DrawOn : dimension error" << std::endl;
#endif
}
