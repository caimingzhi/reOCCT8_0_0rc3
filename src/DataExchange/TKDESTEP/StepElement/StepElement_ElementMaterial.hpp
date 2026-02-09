#pragma once

#include <Standard.hpp>

#include <StepRepr_MaterialPropertyRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepElement_ElementMaterial : public Standard_Transient
{

public:
  Standard_EXPORT StepElement_ElementMaterial();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aMaterialId,
    const occ::handle<TCollection_HAsciiString>& aDescription,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>&
      aProperties);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> MaterialId() const;

  Standard_EXPORT void SetMaterialId(const occ::handle<TCollection_HAsciiString>& MaterialId);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>
    Properties() const;

  Standard_EXPORT void SetProperties(
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>&
      Properties);

  DEFINE_STANDARD_RTTIEXT(StepElement_ElementMaterial, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theMaterialId;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>
    theProperties;
};
