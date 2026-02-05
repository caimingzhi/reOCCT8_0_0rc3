#include <StepFEA_FeaModel.hpp>
#include <StepFEA_NodeRepresentation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_NodeRepresentation, StepRepr_Representation)

//=================================================================================================

StepFEA_NodeRepresentation::StepFEA_NodeRepresentation() = default;

//=================================================================================================

void StepFEA_NodeRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                     aRepresentation_Items,
  const occ::handle<StepRepr_RepresentationContext>& aRepresentation_ContextOfItems,
  const occ::handle<StepFEA_FeaModel>&               aModelRef)
{
  StepRepr_Representation::Init(aRepresentation_Name,
                                aRepresentation_Items,
                                aRepresentation_ContextOfItems);

  theModelRef = aModelRef;
}

//=================================================================================================

occ::handle<StepFEA_FeaModel> StepFEA_NodeRepresentation::ModelRef() const
{
  return theModelRef;
}

//=================================================================================================

void StepFEA_NodeRepresentation::SetModelRef(const occ::handle<StepFEA_FeaModel>& aModelRef)
{
  theModelRef = aModelRef;
}
