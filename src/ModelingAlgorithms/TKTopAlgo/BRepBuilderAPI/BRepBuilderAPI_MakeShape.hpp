#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <BRepBuilderAPI_Command.hpp>
#include <Message_ProgressRange.hpp>

//! This is the root class for all shape
//! constructions. It stores the result.
//!
//! It provides deferred methods to trace the history
//! of sub-shapes.
class BRepBuilderAPI_MakeShape : public BRepBuilderAPI_Command
{
public:
  DEFINE_STANDARD_ALLOC

  //! This is called by Shape(). It does nothing but
  //! may be redefined.
  Standard_EXPORT virtual void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange());

  //! Returns a shape built by the shape construction algorithm.
  //! Raises exception StdFail_NotDone if the shape was not built.
  Standard_EXPORT virtual const TopoDS_Shape& Shape();
  Standard_EXPORT                             operator TopoDS_Shape();

  //! Returns the list of shapes generated from the
  //! shape <S>.
  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S);

  //! Returns the list of shapes modified from the shape
  //! <S>.
  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S);

  //! Returns true if the shape S has been deleted.
  Standard_EXPORT virtual bool IsDeleted(const TopoDS_Shape& S);

protected:
  Standard_EXPORT BRepBuilderAPI_MakeShape();

  TopoDS_Shape                   myShape;
  NCollection_List<TopoDS_Shape> myGenerated;
};
