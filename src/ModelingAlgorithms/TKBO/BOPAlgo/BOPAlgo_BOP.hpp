#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <BOPAlgo_ToolsProvider.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <TopAbs_ShapeEnum.hpp>
class BOPAlgo_PaveFiller;

class BOPAlgo_BOP : public BOPAlgo_ToolsProvider
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_BOP();
  Standard_EXPORT ~BOPAlgo_BOP() override;

  Standard_EXPORT BOPAlgo_BOP(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void Clear() override;

  Standard_EXPORT void SetOperation(const BOPAlgo_Operation theOperation);

  Standard_EXPORT BOPAlgo_Operation Operation() const;

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

protected:
  Standard_EXPORT void CheckData() override;

  Standard_EXPORT void PerformInternal1(const BOPAlgo_PaveFiller&    thePF,
                                        const Message_ProgressRange& theRange) override;

  Standard_EXPORT void BuildResult(const TopAbs_ShapeEnum theType) override;

  Standard_EXPORT void BuildShape(const Message_ProgressRange& theRange);

  Standard_EXPORT void BuildRC(const Message_ProgressRange& theRange);

  Standard_EXPORT void BuildSolid(const Message_ProgressRange& theRange);

  Standard_EXPORT bool TreatEmptyShape();

  Standard_EXPORT virtual bool CheckArgsForOpenSolid();

protected:
  enum BOPAlgo_PIOperation
  {
    PIOperation_BuildShape = BOPAlgo_ToolsProvider::PIOperation_Last,
    PIOperation_Last
  };

  Standard_EXPORT void fillPIConstants(const double     theWhole,
                                       BOPAlgo_PISteps& theSteps) const override;

protected:
  BOPAlgo_Operation myOperation;
  int               myDims[2];
  TopoDS_Shape      myRC;
};
