#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_CheckResult.hpp>
#include <BOPAlgo_Operation.hpp>
#include <BOPAlgo_Options.hpp>
#include <TopoDS_Shape.hpp>
#include <Message_ProgressRange.hpp>

class BRepAlgoAPI_Check : public BOPAlgo_Options
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT BRepAlgoAPI_Check();
  Standard_EXPORT ~BRepAlgoAPI_Check() override;

  Standard_EXPORT BRepAlgoAPI_Check(
    const TopoDS_Shape&          theS,
    const bool                   bTestSE  = true,
    const bool                   bTestSI  = true,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT BRepAlgoAPI_Check(
    const TopoDS_Shape&          theS1,
    const TopoDS_Shape&          theS2,
    const BOPAlgo_Operation      theOp    = BOPAlgo_UNKNOWN,
    const bool                   bTestSE  = true,
    const bool                   bTestSI  = true,
    const Message_ProgressRange& theRange = Message_ProgressRange());

public:
  void SetData(const TopoDS_Shape& theS, const bool bTestSE = true, const bool bTestSI = true)
  {
    myS1     = theS;
    myS2     = TopoDS_Shape();
    myTestSE = bTestSE;
    myTestSI = bTestSI;
    myFaultyShapes.Clear();
  }

  void SetData(const TopoDS_Shape&     theS1,
               const TopoDS_Shape&     theS2,
               const BOPAlgo_Operation theOp   = BOPAlgo_UNKNOWN,
               const bool              bTestSE = true,
               const bool              bTestSI = true)
  {
    myS1        = theS1;
    myS2        = theS2;
    myOperation = theOp;
    myTestSE    = bTestSE;
    myTestSI    = bTestSI;
    myFaultyShapes.Clear();
  }

public:
  Standard_EXPORT void Perform(const Message_ProgressRange& theRange = Message_ProgressRange());

public:
  bool IsValid() { return myFaultyShapes.IsEmpty(); }

  const NCollection_List<BOPAlgo_CheckResult>& Result() { return myFaultyShapes; }

protected:
  TopoDS_Shape myS1;
  TopoDS_Shape myS2;

  bool              myTestSE;
  bool              myTestSI;
  BOPAlgo_Operation myOperation;

  NCollection_List<BOPAlgo_CheckResult> myFaultyShapes;
};
