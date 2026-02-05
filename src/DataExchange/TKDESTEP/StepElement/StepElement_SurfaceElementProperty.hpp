#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepElement_SurfaceSectionField;

//! Representation of STEP entity SurfaceElementProperty
class StepElement_SurfaceElementProperty : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_SurfaceElementProperty();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&        aPropertyId,
                            const occ::handle<TCollection_HAsciiString>&        aDescription,
                            const occ::handle<StepElement_SurfaceSectionField>& aSection);

  //! Returns field PropertyId
  Standard_EXPORT occ::handle<TCollection_HAsciiString> PropertyId() const;

  //! Set field PropertyId
  Standard_EXPORT void SetPropertyId(const occ::handle<TCollection_HAsciiString>& PropertyId);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns field Section
  Standard_EXPORT occ::handle<StepElement_SurfaceSectionField> Section() const;

  //! Set field Section
  Standard_EXPORT void SetSection(const occ::handle<StepElement_SurfaceSectionField>& Section);

  DEFINE_STANDARD_RTTIEXT(StepElement_SurfaceElementProperty, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>        thePropertyId;
  occ::handle<TCollection_HAsciiString>        theDescription;
  occ::handle<StepElement_SurfaceSectionField> theSection;
};
