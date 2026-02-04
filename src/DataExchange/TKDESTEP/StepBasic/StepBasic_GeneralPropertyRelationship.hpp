#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

class TCollection_HAsciiString;
class StepBasic_GeneralProperty;

//! Representation of STEP entity GeneralPropertyRelationship
class StepBasic_GeneralPropertyRelationship : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_GeneralPropertyRelationship();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&  aName,
                            const bool                                    hasDescription,
                            const occ::handle<TCollection_HAsciiString>&  aDescription,
                            const occ::handle<StepBasic_GeneralProperty>& aRelatingGeneralProperty,
                            const occ::handle<StepBasic_GeneralProperty>& aRelatedGeneralProperty);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  //! Returns True if optional field Description is defined
  Standard_EXPORT bool HasDescription() const;

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns field RelatingGeneralProperty
  Standard_EXPORT occ::handle<StepBasic_GeneralProperty> RelatingGeneralProperty() const;

  //! Set field RelatingGeneralProperty
  Standard_EXPORT void SetRelatingGeneralProperty(
    const occ::handle<StepBasic_GeneralProperty>& RelatingGeneralProperty);

  //! Returns field RelatedGeneralProperty
  Standard_EXPORT occ::handle<StepBasic_GeneralProperty> RelatedGeneralProperty() const;

  //! Set field RelatedGeneralProperty
  Standard_EXPORT void SetRelatedGeneralProperty(
    const occ::handle<StepBasic_GeneralProperty>& RelatedGeneralProperty);

  DEFINE_STANDARD_RTTIEXT(StepBasic_GeneralPropertyRelationship, Standard_Transient)

private:
  bool                                   defDescription;
  occ::handle<TCollection_HAsciiString>  theName;
  occ::handle<TCollection_HAsciiString>  theDescription;
  occ::handle<StepBasic_GeneralProperty> theRelatingGeneralProperty;
  occ::handle<StepBasic_GeneralProperty> theRelatedGeneralProperty;
};

