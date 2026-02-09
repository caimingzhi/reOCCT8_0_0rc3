#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Builder.hpp>

class BOPAlgo_ToolsProvider : public BOPAlgo_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_ToolsProvider();

  Standard_EXPORT BOPAlgo_ToolsProvider(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void Clear() override;

  Standard_EXPORT virtual void AddTool(const TopoDS_Shape& theShape);

  Standard_EXPORT virtual void SetTools(const NCollection_List<TopoDS_Shape>& theShapes);

  const NCollection_List<TopoDS_Shape>& Tools() const { return myTools; }

protected:
  NCollection_List<TopoDS_Shape>                         myTools;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMapTools;
};
