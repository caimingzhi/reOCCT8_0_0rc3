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

//! This class implements the transfer of Shape Entities from Geom
//! To IGES. These can be:
//! . Vertex
//! . Edge
//! . Wire
class BRepToIGES_BRSolid : public BRepToIGES_BREntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepToIGES_BRSolid();

  Standard_EXPORT BRepToIGES_BRSolid(const BRepToIGES_BREntity& BR);

  //! Transfer a Shape entity from TopoDS to IGES
  //! this entity must be a Solid or a CompSolid or a Compound.
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferSolid(
    const TopoDS_Shape&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfer a Solid entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferSolid(
    const TopoDS_Solid&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfer an CompSolid entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCompSolid(
    const TopoDS_CompSolid&      start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfer a Compound entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCompound(
    const TopoDS_Compound&       start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());
};

