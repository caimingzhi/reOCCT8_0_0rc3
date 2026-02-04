#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ApplicationContextElement.hpp>
class TCollection_HAsciiString;
class StepBasic_ApplicationContext;

//! Representation of STEP entity ProductConceptContext
class StepBasic_ProductConceptContext : public StepBasic_ApplicationContextElement
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ProductConceptContext();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     aApplicationContextElement_Name,
    const occ::handle<StepBasic_ApplicationContext>& aApplicationContextElement_FrameOfReference,
    const occ::handle<TCollection_HAsciiString>&     aMarketSegmentType);

  //! Returns field MarketSegmentType
  Standard_EXPORT occ::handle<TCollection_HAsciiString> MarketSegmentType() const;

  //! Set field MarketSegmentType
  Standard_EXPORT void SetMarketSegmentType(
    const occ::handle<TCollection_HAsciiString>& MarketSegmentType);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductConceptContext, StepBasic_ApplicationContextElement)

private:
  occ::handle<TCollection_HAsciiString> theMarketSegmentType;
};

