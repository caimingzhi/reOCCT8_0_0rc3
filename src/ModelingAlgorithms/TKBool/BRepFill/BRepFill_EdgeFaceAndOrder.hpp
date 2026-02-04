#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <GeomAbs_Shape.hpp>

class BRepFill_EdgeFaceAndOrder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_EdgeFaceAndOrder();

  Standard_EXPORT BRepFill_EdgeFaceAndOrder(const TopoDS_Edge&  anEdge,
                                            const TopoDS_Face&  aFace,
                                            const GeomAbs_Shape anOrder);

  friend class BRepFill_Filling;

private:
  TopoDS_Edge   myEdge;
  TopoDS_Face   myFace;
  GeomAbs_Shape myOrder;
};

