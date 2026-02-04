#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_Group;

//! Representation of STEP entity GroupRelationship
class StepBasic_GroupRelationship : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_GroupRelationship();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepBasic_Group>&          aRelatingGroup,
                            const occ::handle<StepBasic_Group>&          aRelatedGroup);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns True if optional field Description is defined
  Standard_EXPORT bool HasDescription() const;

  //! Returns field RelatingGroup
  Standard_EXPORT occ::handle<StepBasic_Group> RelatingGroup() const;

  //! Set field RelatingGroup
  Standard_EXPORT void SetRelatingGroup(const occ::handle<StepBasic_Group>& RelatingGroup);

  //! Returns field RelatedGroup
  Standard_EXPORT occ::handle<StepBasic_Group> RelatedGroup() const;

  //! Set field RelatedGroup
  Standard_EXPORT void SetRelatedGroup(const occ::handle<StepBasic_Group>& RelatedGroup);

  DEFINE_STANDARD_RTTIEXT(StepBasic_GroupRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<StepBasic_Group>          theRelatingGroup;
  occ::handle<StepBasic_Group>          theRelatedGroup;
  bool                                  defDescription;
};

