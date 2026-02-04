#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Builder.hpp>

//! Auxiliary class providing API to operate tool arguments.
class BOPAlgo_ToolsProvider : public BOPAlgo_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT BOPAlgo_ToolsProvider();

  Standard_EXPORT BOPAlgo_ToolsProvider(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  //! Clears internal fields and arguments
  Standard_EXPORT void Clear() override;

  //! Adds Tool argument of the operation
  Standard_EXPORT virtual void AddTool(const TopoDS_Shape& theShape);

  //! Adds the Tool arguments of the operation
  Standard_EXPORT virtual void SetTools(const NCollection_List<TopoDS_Shape>& theShapes);

  //! Returns the Tool arguments of the operation
  const NCollection_List<TopoDS_Shape>& Tools() const { return myTools; }

protected:
  NCollection_List<TopoDS_Shape>                         myTools;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMapTools;
};

