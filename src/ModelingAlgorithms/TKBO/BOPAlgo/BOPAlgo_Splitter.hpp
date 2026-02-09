#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_ToolsProvider.hpp>

class BOPAlgo_Splitter : public BOPAlgo_ToolsProvider
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_Splitter();
  Standard_EXPORT ~BOPAlgo_Splitter() override;

  Standard_EXPORT BOPAlgo_Splitter(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

protected:
  Standard_EXPORT void CheckData() override;

  Standard_EXPORT void BuildResult(const TopAbs_ShapeEnum theType) override;
};
