#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepData_SelectMember;
class TCollection_HAsciiString;

//! Representation of STEP SELECT type SourceItem
class StepBasic_SourceItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepBasic_SourceItem();

  //! Recognizes a kind of SourceItem select type
  //! 1 -> HAsciiString from TCollection
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  //! Returns Value as Identifier (or Null if another type)
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Identifier() const;
};
