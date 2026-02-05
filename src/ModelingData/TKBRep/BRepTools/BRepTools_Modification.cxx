#include <BRepTools_Modification.hpp>

#include <Poly_Triangulation.hpp>
#include <TopoDS_Face.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepTools_Modification, Standard_Transient)

bool BRepTools_Modification::NewTriangulation(const TopoDS_Face&, occ::handle<Poly_Triangulation>&)
{
  return false;
}

bool BRepTools_Modification::NewPolygon(const TopoDS_Edge&, occ::handle<Poly_Polygon3D>&)
{
  return false;
}

bool BRepTools_Modification::NewPolygonOnTriangulation(const TopoDS_Edge&,
                                                       const TopoDS_Face&,
                                                       occ::handle<Poly_PolygonOnTriangulation>&)
{
  return false;
}
