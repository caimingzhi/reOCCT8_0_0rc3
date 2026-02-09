#include <StepElement_ElementMaterial.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_ElementMaterial, Standard_Transient)

StepElement_ElementMaterial::StepElement_ElementMaterial() = default;

void StepElement_ElementMaterial::Init(
  const occ::handle<TCollection_HAsciiString>& aMaterialId,
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>&
    aProperties)
{

  theMaterialId = aMaterialId;

  theDescription = aDescription;

  theProperties = aProperties;
}

occ::handle<TCollection_HAsciiString> StepElement_ElementMaterial::MaterialId() const
{
  return theMaterialId;
}

void StepElement_ElementMaterial::SetMaterialId(
  const occ::handle<TCollection_HAsciiString>& aMaterialId)
{
  theMaterialId = aMaterialId;
}

occ::handle<TCollection_HAsciiString> StepElement_ElementMaterial::Description() const
{
  return theDescription;
}

void StepElement_ElementMaterial::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

occ::handle<NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>
  StepElement_ElementMaterial::Properties() const
{
  return theProperties;
}

void StepElement_ElementMaterial::SetProperties(
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>&
    aProperties)
{
  theProperties = aProperties;
}
