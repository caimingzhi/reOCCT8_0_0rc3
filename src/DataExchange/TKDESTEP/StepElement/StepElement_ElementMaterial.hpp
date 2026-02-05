#pragma once

#include <Standard.hpp>

#include <StepRepr_MaterialPropertyRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity ElementMaterial
class StepElement_ElementMaterial : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_ElementMaterial();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aMaterialId,
    const occ::handle<TCollection_HAsciiString>& aDescription,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>&
      aProperties);

  //! Returns field MaterialId
  Standard_EXPORT occ::handle<TCollection_HAsciiString> MaterialId() const;

  //! Set field MaterialId
  Standard_EXPORT void SetMaterialId(const occ::handle<TCollection_HAsciiString>& MaterialId);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns field Properties
  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>
    Properties() const;

  //! Set field Properties
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
