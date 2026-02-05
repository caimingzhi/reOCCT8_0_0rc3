#include <BRepFill_FaceAndOrder.hpp>
#include <BRepFill_Filling.hpp>
#include <TopoDS_Face.hpp>

BRepFill_FaceAndOrder::BRepFill_FaceAndOrder() = default;

BRepFill_FaceAndOrder::BRepFill_FaceAndOrder(const TopoDS_Face& aFace, const GeomAbs_Shape anOrder)
{
  myFace  = aFace;
  myOrder = anOrder;
}
