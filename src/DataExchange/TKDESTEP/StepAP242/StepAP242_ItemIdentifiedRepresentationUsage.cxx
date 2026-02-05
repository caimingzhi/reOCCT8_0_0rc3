#include <StepAP242_ItemIdentifiedRepresentationUsage.hpp>

#include <StepAP242_ItemIdentifiedRepresentationUsageDefinition.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepAP242_ItemIdentifiedRepresentationUsage, Standard_Transient)

//=================================================================================================

StepAP242_ItemIdentifiedRepresentationUsage::StepAP242_ItemIdentifiedRepresentationUsage() =
  default;

//=================================================================================================

void StepAP242_ItemIdentifiedRepresentationUsage::Init(
  const occ::handle<TCollection_HAsciiString>&                 theName,
  const occ::handle<TCollection_HAsciiString>&                 theDescription,
  const StepAP242_ItemIdentifiedRepresentationUsageDefinition& theDefinition,
  const occ::handle<StepRepr_Representation>&                  theUsedRepresentation,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
    theIdentifiedItem)
{
  // --- classe own fields ---
  name               = theName;
  description        = theDescription;
  definition         = theDefinition;
  usedRepresentation = theUsedRepresentation;
  identifiedItem     = theIdentifiedItem;
}
