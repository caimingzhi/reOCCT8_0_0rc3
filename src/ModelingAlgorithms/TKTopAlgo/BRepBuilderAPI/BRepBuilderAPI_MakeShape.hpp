#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <BRepBuilderAPI_Command.hpp>
#include <Message_ProgressRange.hpp>

class BRepBuilderAPI_MakeShape : public BRepBuilderAPI_Command
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT virtual const TopoDS_Shape& Shape();
  Standard_EXPORT                             operator TopoDS_Shape();

  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S);

  Standard_EXPORT virtual const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S);

  Standard_EXPORT virtual bool IsDeleted(const TopoDS_Shape& S);

protected:
  Standard_EXPORT BRepBuilderAPI_MakeShape();

  TopoDS_Shape                   myShape;
  NCollection_List<TopoDS_Shape> myGenerated;
};
