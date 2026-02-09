#include <StepFEA_ElementRepresentation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_ElementRepresentation, StepRepr_Representation)

StepFEA_ElementRepresentation::StepFEA_ElementRepresentation() = default;

void StepFEA_ElementRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                     aRepresentation_Items,
  const occ::handle<StepRepr_RepresentationContext>& aRepresentation_ContextOfItems,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodeList)
{
  StepRepr_Representation::Init(aRepresentation_Name,
                                aRepresentation_Items,
                                aRepresentation_ContextOfItems);

  theNodeList = aNodeList;
}

occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>
  StepFEA_ElementRepresentation::NodeList() const
{
  return theNodeList;
}

void StepFEA_ElementRepresentation::SetNodeList(
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodeList)
{
  theNodeList = aNodeList;
}
