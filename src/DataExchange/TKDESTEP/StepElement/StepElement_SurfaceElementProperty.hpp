#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepElement_SurfaceSectionField;

class StepElement_SurfaceElementProperty : public Standard_Transient
{

public:
  Standard_EXPORT StepElement_SurfaceElementProperty();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&        aPropertyId,
                            const occ::handle<TCollection_HAsciiString>&        aDescription,
                            const occ::handle<StepElement_SurfaceSectionField>& aSection);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PropertyId() const;

  Standard_EXPORT void SetPropertyId(const occ::handle<TCollection_HAsciiString>& PropertyId);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT occ::handle<StepElement_SurfaceSectionField> Section() const;

  Standard_EXPORT void SetSection(const occ::handle<StepElement_SurfaceSectionField>& Section);

  DEFINE_STANDARD_RTTIEXT(StepElement_SurfaceElementProperty, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>        thePropertyId;
  occ::handle<TCollection_HAsciiString>        theDescription;
  occ::handle<StepElement_SurfaceSectionField> theSection;
};
