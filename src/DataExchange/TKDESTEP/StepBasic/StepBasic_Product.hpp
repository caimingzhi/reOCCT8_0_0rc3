#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ProductContext.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductContext;

class StepBasic_Product : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_Product();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aId,
    const occ::handle<TCollection_HAsciiString>& aName,
    const occ::handle<TCollection_HAsciiString>& aDescription,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>>&
      aFrameOfReference);

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& aId);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetFrameOfReference(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>>&
      aFrameOfReference);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>>
                  FrameOfReference() const;

  Standard_EXPORT occ::handle<StepBasic_ProductContext> FrameOfReferenceValue(const int num) const;

  Standard_EXPORT int NbFrameOfReference() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_Product, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                                   id;
  occ::handle<TCollection_HAsciiString>                                   name;
  occ::handle<TCollection_HAsciiString>                                   description;
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>> frameOfReference;
};
