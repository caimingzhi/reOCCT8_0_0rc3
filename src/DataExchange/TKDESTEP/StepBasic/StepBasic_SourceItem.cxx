#include <Standard_Transient.hpp>
#include <StepBasic_SourceItem.hpp>
#include <StepData_SelectNamed.hpp>
#include <TCollection_HAsciiString.hpp>

//=================================================================================================

StepBasic_SourceItem::StepBasic_SourceItem() = default;

//=================================================================================================

int StepBasic_SourceItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepData_SelectNamed)))
    return 1;
  return 0;
}

//=================================================================================================

occ::handle<StepData_SelectMember> StepBasic_SourceItem::NewMember() const
{
  occ::handle<StepData_SelectNamed> member = new StepData_SelectNamed;
  return member;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_SourceItem::Identifier() const
{
  return occ::down_cast<TCollection_HAsciiString>(Value());
}
