#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Type.hpp>
class TopoDS_Shape;

class TransferBRep_ShapeInfo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Standard_Type> Type(const TopoDS_Shape& ent);

  Standard_EXPORT static const char* TypeName(const TopoDS_Shape& ent);
};
