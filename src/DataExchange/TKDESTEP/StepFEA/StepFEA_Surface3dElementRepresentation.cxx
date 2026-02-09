#include <StepElement_ElementMaterial.hpp>
#include <StepElement_Surface3dElementDescriptor.hpp>
#include <StepElement_SurfaceElementProperty.hpp>
#include <StepFEA_FeaModel3d.hpp>
#include <StepFEA_Surface3dElementRepresentation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_Surface3dElementRepresentation, StepFEA_ElementRepresentation)

StepFEA_Surface3dElementRepresentation::StepFEA_Surface3dElementRepresentation() = default;

void StepFEA_Surface3dElementRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                     aRepresentation_Items,
  const occ::handle<StepRepr_RepresentationContext>& aRepresentation_ContextOfItems,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>&
                                                             aElementRepresentation_NodeList,
  const occ::handle<StepFEA_FeaModel3d>&                     aModelRef,
  const occ::handle<StepElement_Surface3dElementDescriptor>& aElementDescriptor,
  const occ::handle<StepElement_SurfaceElementProperty>&     aProperty,
  const occ::handle<StepElement_ElementMaterial>&            aMaterial)
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

occ::handle<StepFEA_FeaModel3d> StepFEA_Surface3dElementRepresentation::ModelRef() const
{
  return theModelRef;
}

void StepFEA_Surface3dElementRepresentation::SetModelRef(
  const occ::handle<StepFEA_FeaModel3d>& aModelRef)
{
  theModelRef = aModelRef;
}

occ::handle<StepElement_Surface3dElementDescriptor> StepFEA_Surface3dElementRepresentation::
  ElementDescriptor() const
{
  return theElementDescriptor;
}

void StepFEA_Surface3dElementRepresentation::SetElementDescriptor(
  const occ::handle<StepElement_Surface3dElementDescriptor>& aElementDescriptor)
{
  theElementDescriptor = aElementDescriptor;
}

occ::handle<StepElement_SurfaceElementProperty> StepFEA_Surface3dElementRepresentation::Property()
  const
{
  return theProperty;
}

void StepFEA_Surface3dElementRepresentation::SetProperty(
  const occ::handle<StepElement_SurfaceElementProperty>& aProperty)
{
  theProperty = aProperty;
}

occ::handle<StepElement_ElementMaterial> StepFEA_Surface3dElementRepresentation::Material() const
{
  return theMaterial;
}

void StepFEA_Surface3dElementRepresentation::SetMaterial(
  const occ::handle<StepElement_ElementMaterial>& aMaterial)
{
  theMaterial = aMaterial;
}
