#include <StepBasic_ProductConceptContext.hpp>
#include <StepRepr_ProductConcept.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ProductConcept, Standard_Transient)

StepRepr_ProductConcept::StepRepr_ProductConcept()
{
  defDescription = false;
}

void StepRepr_ProductConcept::Init(
  const occ::handle<TCollection_HAsciiString>&        aId,
  const occ::handle<TCollection_HAsciiString>&        aName,
  const bool                                          hasDescription,
  const occ::handle<TCollection_HAsciiString>&        aDescription,
  const occ::handle<StepBasic_ProductConceptContext>& aMarketContext)
{

  theId = aId;

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theMarketContext = aMarketContext;
}

occ::handle<TCollection_HAsciiString> StepRepr_ProductConcept::Id() const
{
  return theId;
}

void StepRepr_ProductConcept::SetId(const occ::handle<TCollection_HAsciiString>& aId)
{
  theId = aId;
}

occ::handle<TCollection_HAsciiString> StepRepr_ProductConcept::Name() const
{
  return theName;
}

void StepRepr_ProductConcept::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_ProductConcept::Description() const
{
  return theDescription;
}

void StepRepr_ProductConcept::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

bool StepRepr_ProductConcept::HasDescription() const
{
  return defDescription;
}

occ::handle<StepBasic_ProductConceptContext> StepRepr_ProductConcept::MarketContext() const
{
  return theMarketContext;
}

void StepRepr_ProductConcept::SetMarketContext(
  const occ::handle<StepBasic_ProductConceptContext>& aMarketContext)
{
  theMarketContext = aMarketContext;
}
