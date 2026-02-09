#pragma once

#include <Standard.hpp>

#include <StepBasic_SourceItem.hpp>
#include <Standard_Transient.hpp>
class StepBasic_ExternalSource;

class StepBasic_ExternallyDefinedItem : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ExternallyDefinedItem();

  Standard_EXPORT void Init(const StepBasic_SourceItem&                  aItemId,
                            const occ::handle<StepBasic_ExternalSource>& aSource);

  Standard_EXPORT StepBasic_SourceItem ItemId() const;

  Standard_EXPORT void SetItemId(const StepBasic_SourceItem& ItemId);

  Standard_EXPORT occ::handle<StepBasic_ExternalSource> Source() const;

  Standard_EXPORT void SetSource(const occ::handle<StepBasic_ExternalSource>& Source);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ExternallyDefinedItem, Standard_Transient)

private:
  StepBasic_SourceItem                  theItemId;
  occ::handle<StepBasic_ExternalSource> theSource;
};
