#include <StepElement_ElementMaterial.hpp>
#include <StepElement_Volume3dElementDescriptor.hpp>
#include <StepFEA_FeaModel3d.hpp>
#include <StepFEA_Volume3dElementRepresentation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_Volume3dElementRepresentation, StepFEA_ElementRepresentation)

//=================================================================================================

StepFEA_Volume3dElementRepresentation::StepFEA_Volume3dElementRepresentation() = default;

//=================================================================================================

void StepFEA_Volume3dElementRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                     aRepresentation_Items,
  const occ::handle<StepRepr_RepresentationContext>& aRepresentation_ContextOfItems,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>&
                                                            aElementRepresentation_NodeList,
  const occ::handle<StepFEA_FeaModel3d>&                    aModelRef,
  const occ::handle<StepElement_Volume3dElementDescriptor>& aElementDescriptor,
  const occ::handle<StepElement_ElementMaterial>&           aMaterial)
{
  StepFEA_ElementRepresentation::Init(aRepresentation_Name,
                                      aRepresentation_Items,
                                      aRepresentation_ContextOfItems,
                                      aElementRepresentation_NodeList);

  theModelRef = aModelRef;

  theElementDescriptor = aElementDescriptor;

  theMaterial = aMaterial;
}

//=================================================================================================

occ::handle<StepFEA_FeaModel3d> StepFEA_Volume3dElementRepresentation::ModelRef() const
{
  return theModelRef;
}

//=================================================================================================

void StepFEA_Volume3dElementRepresentation::SetModelRef(
  const occ::handle<StepFEA_FeaModel3d>& aModelRef)
{
  theModelRef = aModelRef;
}

//=================================================================================================

occ::handle<StepElement_Volume3dElementDescriptor> StepFEA_Volume3dElementRepresentation::
  ElementDescriptor() const
{
  return theElementDescriptor;
}

//=================================================================================================

void StepFEA_Volume3dElementRepresentation::SetElementDescriptor(
  const occ::handle<StepElement_Volume3dElementDescriptor>& aElementDescriptor)
{
  theElementDescriptor = aElementDescriptor;
}

//=================================================================================================

occ::handle<StepElement_ElementMaterial> StepFEA_Volume3dElementRepresentation::Material() const
{
  return theMaterial;
}

//=================================================================================================

void StepFEA_Volume3dElementRepresentation::SetMaterial(
  const occ::handle<StepElement_ElementMaterial>& aMaterial)
{
  theMaterial = aMaterial;
}
