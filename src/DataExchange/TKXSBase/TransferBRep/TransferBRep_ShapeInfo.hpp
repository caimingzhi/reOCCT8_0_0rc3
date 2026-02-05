#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Type.hpp>
class TopoDS_Shape;

//! Gives information on an object, see template DataInfo
//! This class is for Shape
class TransferBRep_ShapeInfo
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the Type attached to an object
  //! Here, TShape (Shape has no Dynamic Type)
  Standard_EXPORT static occ::handle<Standard_Type> Type(const TopoDS_Shape& ent);

  //! Returns Type Name (string)
  //! Here, the true name of the Type of a Shape
  Standard_EXPORT static const char* TypeName(const TopoDS_Shape& ent);
};
