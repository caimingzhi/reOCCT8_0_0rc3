#pragma once


#include <Standard.hpp>

#include <StepBasic_SourceItem.hpp>
#include <Standard_Transient.hpp>

//! Representation of STEP entity ExternalSource
class StepBasic_ExternalSource : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ExternalSource();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepBasic_SourceItem& aSourceId);

  //! Returns field SourceId
  Standard_EXPORT StepBasic_SourceItem SourceId() const;

  //! Set field SourceId
  Standard_EXPORT void SetSourceId(const StepBasic_SourceItem& SourceId);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ExternalSource, Standard_Transient)

private:
  StepBasic_SourceItem theSourceId;
};

