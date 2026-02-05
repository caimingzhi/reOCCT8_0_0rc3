#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_AnalysisItemWithinRepresentation, Standard_Transient)

//=================================================================================================

StepElement_AnalysisItemWithinRepresentation::StepElement_AnalysisItemWithinRepresentation() =
  default;

//=================================================================================================

void StepElement_AnalysisItemWithinRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>&    aName,
  const occ::handle<TCollection_HAsciiString>&    aDescription,
  const occ::handle<StepRepr_RepresentationItem>& aItem,
  const occ::handle<StepRepr_Representation>&     aRep)
{

  theName = aName;

  theDescription = aDescription;

  theItem = aItem;

  theRep = aRep;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepElement_AnalysisItemWithinRepresentation::Name() const
{
  return theName;
}

//=================================================================================================

void StepElement_AnalysisItemWithinRepresentation::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepElement_AnalysisItemWithinRepresentation::Description()
  const
{
  return theDescription;
}

//=================================================================================================

void StepElement_AnalysisItemWithinRepresentation::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

occ::handle<StepRepr_RepresentationItem> StepElement_AnalysisItemWithinRepresentation::Item() const
{
  return theItem;
}

//=================================================================================================

void StepElement_AnalysisItemWithinRepresentation::SetItem(
  const occ::handle<StepRepr_RepresentationItem>& aItem)
{
  theItem = aItem;
}

//=================================================================================================

occ::handle<StepRepr_Representation> StepElement_AnalysisItemWithinRepresentation::Rep() const
{
  return theRep;
}

//=================================================================================================

void StepElement_AnalysisItemWithinRepresentation::SetRep(
  const occ::handle<StepRepr_Representation>& aRep)
{
  theRep = aRep;
}
