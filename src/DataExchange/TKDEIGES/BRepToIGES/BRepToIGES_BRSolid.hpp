#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepToIGES_BREntity.hpp>
class IGESData_IGESEntity;
class TopoDS_Shape;
class TopoDS_Solid;
class TopoDS_CompSolid;
class TopoDS_Compound;

class BRepToIGES_BRSolid : public BRepToIGES_BREntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepToIGES_BRSolid();

  Standard_EXPORT BRepToIGES_BRSolid(const BRepToIGES_BREntity& BR);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferSolid(
    const TopoDS_Shape&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferSolid(
    const TopoDS_Solid&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCompSolid(
    const TopoDS_CompSolid&      start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCompound(
    const TopoDS_Compound&       start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());
};
