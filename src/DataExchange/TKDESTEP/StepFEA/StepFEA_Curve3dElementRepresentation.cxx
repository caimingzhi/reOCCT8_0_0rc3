#include <StepElement_Curve3dElementDescriptor.hpp>
#include <StepElement_ElementMaterial.hpp>
#include <StepFEA_Curve3dElementProperty.hpp>
#include <StepFEA_Curve3dElementRepresentation.hpp>
#include <StepFEA_FeaModel3d.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_Curve3dElementRepresentation, StepFEA_ElementRepresentation)

StepFEA_Curve3dElementRepresentation::StepFEA_Curve3dElementRepresentation() = default;

void StepFEA_Curve3dElementRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                     aRepresentation_Items,
  const occ::handle<StepRepr_RepresentationContext>& aRepresentation_ContextOfItems,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>&
                                                           aElementRepresentation_NodeList,
  const occ::handle<StepFEA_FeaModel3d>&                   aModelRef,
  const occ::handle<StepElement_Curve3dElementDescriptor>& aElementDescriptor,
  const occ::handle<StepFEA_Curve3dElementProperty>&       aProperty,
  const occ::handle<StepElement_ElementMaterial>&          aMaterial)
{
  StepFEA_ElementRepresentation::Init(aRepresentation_Name,
                                      aRepresentation_Items,
                                      aRepresentation_ContextOfItems,
                                      aElementRepresentation_NodeList);

  theModelRef = aModelRef;

  theElementDescriptor = aElementDescriptor;

  theProperty = aProperty;

  theMaterial = aMaterial;
}

occ::handle<StepFEA_FeaModel3d> StepFEA_Curve3dElementRepresentation::ModelRef() const
{
  return theModelRef;
}

void StepFEA_Curve3dElementRepresentation::SetModelRef(
  const occ::handle<StepFEA_FeaModel3d>& aModelRef)
{
  theModelRef = aModelRef;
}

occ::handle<StepElement_Curve3dElementDescriptor> StepFEA_Curve3dElementRepresentation::
  ElementDescriptor() const
{
  return theElementDescriptor;
}

void StepFEA_Curve3dElementRepresentation::SetElementDescriptor(
  const occ::handle<StepElement_Curve3dElementDescriptor>& aElementDescriptor)
{
  theElementDescriptor = aElementDescriptor;
}

occ::handle<StepFEA_Curve3dElementProperty> StepFEA_Curve3dElementRepresentation::Property() const
{
  return theProperty;
}

void StepFEA_Curve3dElementRepresentation::SetProperty(
  const occ::handle<StepFEA_Curve3dElementProperty>& aProperty)
{
  theProperty = aProperty;
}

occ::handle<StepElement_ElementMaterial> StepFEA_Curve3dElementRepresentation::Material() const
{
  return theMaterial;
}

void StepFEA_Curve3dElementRepresentation::SetMaterial(
  const occ::handle<StepElement_ElementMaterial>& aMaterial)
{
  theMaterial = aMaterial;
}
