#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepToIGES_BREntity.hpp>
#include <Message_ProgressRange.hpp>

class IGESData_IGESEntity;
class TopoDS_Shape;
class TopoDS_Shell;
class TopoDS_Face;

//! This class implements the transfer of Shape Entities from Geom
//! To IGES. These can be:
//! . Vertex
//! . Edge
//! . Wire
class BRepToIGES_BRShell : public BRepToIGES_BREntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepToIGES_BRShell();

  Standard_EXPORT BRepToIGES_BRShell(const BRepToIGES_BREntity& BR);

  //! Transfer an Shape entity from TopoDS to IGES
  //! This entity must be a Face or a Shell.
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferShell(
    const TopoDS_Shape&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfer an Shell entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferShell(
    const TopoDS_Shell&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfer a Face entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferFace(
    const TopoDS_Face&           start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());
};
