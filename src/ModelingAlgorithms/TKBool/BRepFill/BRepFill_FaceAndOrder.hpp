#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Face.hpp>
#include <GeomAbs_Shape.hpp>

//! A structure containing Face and Order of constraint
class BRepFill_FaceAndOrder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_FaceAndOrder();

  Standard_EXPORT BRepFill_FaceAndOrder(const TopoDS_Face& aFace, const GeomAbs_Shape anOrder);

  friend class BRepFill_Filling;

private:
  TopoDS_Face   myFace;
  GeomAbs_Shape myOrder;
};
