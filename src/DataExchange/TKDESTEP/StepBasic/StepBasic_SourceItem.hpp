#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepData_SelectMember;
class TCollection_HAsciiString;

class StepBasic_SourceItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepBasic_SourceItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Identifier() const;
};
