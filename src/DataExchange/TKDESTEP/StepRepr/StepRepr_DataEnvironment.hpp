#pragma once

#include <Standard.hpp>

#include <StepRepr_PropertyDefinitionRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepRepr_DataEnvironment : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_DataEnvironment();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aName,
    const occ::handle<TCollection_HAsciiString>& aDescription,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_PropertyDefinitionRepresentation>>>&
      aElements);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepRepr_PropertyDefinitionRepresentation>>>
    Elements() const;

  Standard_EXPORT void SetElements(
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_PropertyDefinitionRepresentation>>>&
      Elements);

  DEFINE_STANDARD_RTTIEXT(StepRepr_DataEnvironment, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_PropertyDefinitionRepresentation>>>
    theElements;
};
