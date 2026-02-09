#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Operation.hpp>
#include <BRepAlgoAPI_BuilderAlgo.hpp>
class BOPAlgo_PaveFiller;
class TopoDS_Shape;

class BRepAlgoAPI_BooleanOperation : public BRepAlgoAPI_BuilderAlgo
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT BRepAlgoAPI_BooleanOperation();

  Standard_EXPORT BRepAlgoAPI_BooleanOperation(const BOPAlgo_PaveFiller& thePF);

public:
  const TopoDS_Shape& Shape1() const { return myArguments.First(); }

  const TopoDS_Shape& Shape2() const { return myTools.First(); }

  void SetTools(const NCollection_List<TopoDS_Shape>& theLS) { myTools = theLS; }

  const NCollection_List<TopoDS_Shape>& Tools() const { return myTools; }

public:
  void SetOperation(const BOPAlgo_Operation theBOP) { myOperation = theBOP; }

  BOPAlgo_Operation Operation() const { return myOperation; }

public:
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

protected:
  Standard_EXPORT BRepAlgoAPI_BooleanOperation(const TopoDS_Shape&     theS1,
                                               const TopoDS_Shape&     theS2,
                                               const BOPAlgo_Operation theOperation);

  Standard_EXPORT BRepAlgoAPI_BooleanOperation(const TopoDS_Shape&       theS1,
                                               const TopoDS_Shape&       theS2,
                                               const BOPAlgo_PaveFiller& thePF,
                                               const BOPAlgo_Operation   theOperation);

protected:
  NCollection_List<TopoDS_Shape> myTools;
  BOPAlgo_Operation              myOperation;
};
