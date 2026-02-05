#include <BRep_Tool.hpp>
#include <Draw_Display.hpp>
#include <DrawDim.hpp>
#include <DrawDim_PlanarDistance.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawDim_PlanarDistance, DrawDim_PlanarDimension)

//=================================================================================================

void DrawDim_PlanarDistance::Draw(const gp_Pnt&      point,
                                  const TopoDS_Edge& edge,
                                  Draw_Display&      dis) const
{
  double                      f, l;
  occ::handle<Geom_Curve>     line = BRep_Tool::Curve(edge, f, l);
  GeomAPI_ProjectPointOnCurve pj(point, line);
  if (pj.NbPoints() == 1)
  {
    gp_Pnt first = point;
    gp_Pnt last  = pj.Point(1);
    dis.Draw(first, last);

    gp_Pnt p((first.X() + last.X()) / 2, (first.Y() + last.Y()) / 2, (first.Z() + last.Z()) / 2);
    DrawText(p, dis);
  }
}

//=================================================================================================

DrawDim_PlanarDistance::DrawDim_PlanarDistance(const TopoDS_Face&  face,
                                               const TopoDS_Shape& geom1,
                                               const TopoDS_Shape& geom2)
{
  myPlane = face;
  myGeom1 = geom1;
  myGeom2 = geom2;
}

//=================================================================================================

DrawDim_PlanarDistance::DrawDim_PlanarDistance(const TopoDS_Shape& geom1, const TopoDS_Shape& geom2)
{
  myGeom1 = geom1;
  myGeom2 = geom2;
}

//=================================================================================================

void DrawDim_PlanarDistance::DrawOn(Draw_Display& dis) const
{
  if (myGeom1.ShapeType() == TopAbs_VERTEX && myGeom2.ShapeType() == TopAbs_VERTEX)
  {
    gp_Pnt first = BRep_Tool::Pnt(TopoDS::Vertex(myGeom1));
    gp_Pnt last  = BRep_Tool::Pnt(TopoDS::Vertex(myGeom2));
    dis.Draw(first, last);

    gp_Pnt p((first.X() + last.X()) / 2, (first.Y() + last.Y()) / 2, (first.Z() + last.Z()) / 2);
    DrawText(p, dis);
    return;
  }

  else if (myGeom1.ShapeType() == TopAbs_VERTEX && myGeom2.ShapeType() == TopAbs_EDGE)
  {
    gp_Pnt point = BRep_Tool::Pnt(TopoDS::Vertex(myGeom1));
    Draw(point, TopoDS::Edge(myGeom2), dis);
    return;
  }

  else if (myGeom1.ShapeType() == TopAbs_EDGE && myGeom2.ShapeType() == TopAbs_VERTEX)
  {
    gp_Pnt point = BRep_Tool::Pnt(TopoDS::Vertex(myGeom2));
    Draw(point, TopoDS::Edge(myGeom1), dis);
    return;
  }

  else if (myGeom1.ShapeType() == TopAbs_EDGE && myGeom2.ShapeType() == TopAbs_EDGE)
  {
    double                  f, l;
    occ::handle<Geom_Curve> C = BRep_Tool::Curve(TopoDS::Edge(myGeom1), f, l);
    if (!C.IsNull())
    {
      occ::handle<Geom_Line> L = occ::down_cast<Geom_Line>(C);
      if (!L.IsNull())
      {
        gp_Pnt      point = L->Lin().Location();
        TopoDS_Edge edge  = TopoDS::Edge(myGeom2);
        Draw(point, edge, dis);
        return;
      }
    }
  }
#ifdef OCCT_DEBUG
  std::cout << " DrawDim_PlanarDistance::DrawOn : dimension error" << std::endl;
#endif
}
