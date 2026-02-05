#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_SourceItem.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ExternalSource, Standard_Transient)

//=================================================================================================

StepBasic_ExternalSource::StepBasic_ExternalSource() = default;

//=================================================================================================

void StepBasic_ExternalSource::Init(const StepBasic_SourceItem& aSourceId)
{

  theSourceId = aSourceId;
}

//=================================================================================================

StepBasic_SourceItem StepBasic_ExternalSource::SourceId() const
{
  return theSourceId;
}

//=================================================================================================

void StepBasic_ExternalSource::SetSourceId(const StepBasic_SourceItem& aSourceId)
{
  theSourceId = aSourceId;
}
