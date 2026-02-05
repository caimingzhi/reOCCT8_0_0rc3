#include <BRepFill_EdgeFaceAndOrder.hpp>
#include <BRepFill_Filling.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

BRepFill_EdgeFaceAndOrder::BRepFill_EdgeFaceAndOrder() = default;

BRepFill_EdgeFaceAndOrder::BRepFill_EdgeFaceAndOrder(const TopoDS_Edge&  anEdge,
                                                     const TopoDS_Face&  aFace,
                                                     const GeomAbs_Shape anOrder)
{
  myEdge  = anEdge;
  myFace  = aFace;
  myOrder = anOrder;
}
