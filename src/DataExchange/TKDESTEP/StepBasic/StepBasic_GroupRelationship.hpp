#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_Group;

class StepBasic_GroupRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_GroupRelationship();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepBasic_Group>&          aRelatingGroup,
                            const occ::handle<StepBasic_Group>&          aRelatedGroup);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  Standard_EXPORT occ::handle<StepBasic_Group> RelatingGroup() const;

  Standard_EXPORT void SetRelatingGroup(const occ::handle<StepBasic_Group>& RelatingGroup);

  Standard_EXPORT occ::handle<StepBasic_Group> RelatedGroup() const;

  Standard_EXPORT void SetRelatedGroup(const occ::handle<StepBasic_Group>& RelatedGroup);

  DEFINE_STANDARD_RTTIEXT(StepBasic_GroupRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<StepBasic_Group>          theRelatingGroup;
  occ::handle<StepBasic_Group>          theRelatedGroup;
  bool                                  defDescription;
};
