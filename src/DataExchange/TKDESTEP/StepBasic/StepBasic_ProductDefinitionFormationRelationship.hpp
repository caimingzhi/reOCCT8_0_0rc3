#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductDefinitionFormation;

//! Representation of STEP entity ProductDefinitionFormationRelationship
class StepBasic_ProductDefinitionFormationRelationship : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ProductDefinitionFormationRelationship();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&             aId,
    const occ::handle<TCollection_HAsciiString>&             aName,
    const occ::handle<TCollection_HAsciiString>&             aDescription,
    const occ::handle<StepBasic_ProductDefinitionFormation>& aRelatingProductDefinitionFormation,
    const occ::handle<StepBasic_ProductDefinitionFormation>& aRelatedProductDefinitionFormation);

  //! Returns field Id
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  //! Set field Id
  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& Id);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns field RelatingProductDefinitionFormation
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation>
                  RelatingProductDefinitionFormation() const;

  //! Set field RelatingProductDefinitionFormation
  Standard_EXPORT void SetRelatingProductDefinitionFormation(
    const occ::handle<StepBasic_ProductDefinitionFormation>& RelatingProductDefinitionFormation);

  //! Returns field RelatedProductDefinitionFormation
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation>
                  RelatedProductDefinitionFormation() const;

  //! Set field RelatedProductDefinitionFormation
  Standard_EXPORT void SetRelatedProductDefinitionFormation(
    const occ::handle<StepBasic_ProductDefinitionFormation>& RelatedProductDefinitionFormation);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionFormationRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>             theId;
  occ::handle<TCollection_HAsciiString>             theName;
  occ::handle<TCollection_HAsciiString>             theDescription;
  occ::handle<StepBasic_ProductDefinitionFormation> theRelatingProductDefinitionFormation;
  occ::handle<StepBasic_ProductDefinitionFormation> theRelatedProductDefinitionFormation;
};

