#pragma once

#include <Standard.hpp>

#include <StepBasic_SourceItem.hpp>
#include <Standard_Transient.hpp>

class StepBasic_ExternalSource : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ExternalSource();

  Standard_EXPORT void Init(const StepBasic_SourceItem& aSourceId);

  Standard_EXPORT StepBasic_SourceItem SourceId() const;

  Standard_EXPORT void SetSourceId(const StepBasic_SourceItem& SourceId);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ExternalSource, Standard_Transient)

private:
  StepBasic_SourceItem theSourceId;
};
