#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepAlgoAPI_BuilderAlgo.hpp>

class BRepAlgoAPI_Splitter : public BRepAlgoAPI_BuilderAlgo
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT BRepAlgoAPI_Splitter();

  Standard_EXPORT BRepAlgoAPI_Splitter(const BOPAlgo_PaveFiller& thePF);

public:
  void SetTools(const NCollection_List<TopoDS_Shape>& theLS) { myTools = theLS; }

  const NCollection_List<TopoDS_Shape>& Tools() const { return myTools; }

public:
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

protected:
  NCollection_List<TopoDS_Shape> myTools;
};
