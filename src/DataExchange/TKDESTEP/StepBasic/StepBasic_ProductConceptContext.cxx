#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ProductConceptContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductConceptContext, StepBasic_ApplicationContextElement)

StepBasic_ProductConceptContext::StepBasic_ProductConceptContext() = default;

void StepBasic_ProductConceptContext::Init(
  const occ::handle<TCollection_HAsciiString>&     aApplicationContextElement_Name,
  const occ::handle<StepBasic_ApplicationContext>& aApplicationContextElement_FrameOfReference,
  const occ::handle<TCollection_HAsciiString>&     aMarketSegmentType)
{
  StepBasic_ApplicationContextElement::Init(aApplicationContextElement_Name,
                                            aApplicationContextElement_FrameOfReference);

  theMarketSegmentType = aMarketSegmentType;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductConceptContext::MarketSegmentType() const
{
  return theMarketSegmentType;
}

void StepBasic_ProductConceptContext::SetMarketSegmentType(
  const occ::handle<TCollection_HAsciiString>& aMarketSegmentType)
{
  theMarketSegmentType = aMarketSegmentType;
}
