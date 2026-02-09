#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Builder.hpp>
#include <NCollection_BaseAllocator.hpp>
class BOPAlgo_PaveFiller;

class BOPAlgo_Section : public BOPAlgo_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_Section();
  Standard_EXPORT ~BOPAlgo_Section() override;

  Standard_EXPORT BOPAlgo_Section(const occ::handle<NCollection_BaseAllocator>& theAllocator);

protected:
  Standard_EXPORT void CheckData() override;

  Standard_EXPORT virtual void BuildSection(const Message_ProgressRange& theRange);

  Standard_EXPORT void PerformInternal1(const BOPAlgo_PaveFiller&    thePF,
                                        const Message_ProgressRange& theRange) override;

protected:
  enum BOPAlgo_PIOperation
  {
    PIOperation_TreatVertices = 0,
    PIOperation_TreatEdges,
    PIOperation_BuildSection,
    PIOperation_FillHistory,
    PIOperation_PostTreat,
    PIOperation_Last
  };

  Standard_EXPORT void fillPIConstants(const double     theWhole,
                                       BOPAlgo_PISteps& theSteps) const override;

  Standard_EXPORT void fillPISteps(BOPAlgo_PISteps& theSteps) const override;
};
