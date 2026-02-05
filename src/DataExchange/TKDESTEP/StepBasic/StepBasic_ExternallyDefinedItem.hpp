#pragma once

#include <Standard.hpp>

#include <StepBasic_SourceItem.hpp>
#include <Standard_Transient.hpp>
class StepBasic_ExternalSource;

//! Representation of STEP entity ExternallyDefinedItem
class StepBasic_ExternallyDefinedItem : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ExternallyDefinedItem();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepBasic_SourceItem&                  aItemId,
                            const occ::handle<StepBasic_ExternalSource>& aSource);

  //! Returns field ItemId
  Standard_EXPORT StepBasic_SourceItem ItemId() const;

  //! Set field ItemId
  Standard_EXPORT void SetItemId(const StepBasic_SourceItem& ItemId);

  //! Returns field Source
  Standard_EXPORT occ::handle<StepBasic_ExternalSource> Source() const;

  //! Set field Source
  Standard_EXPORT void SetSource(const occ::handle<StepBasic_ExternalSource>& Source);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ExternallyDefinedItem, Standard_Transient)

private:
  StepBasic_SourceItem                  theItemId;
  occ::handle<StepBasic_ExternalSource> theSource;
};
