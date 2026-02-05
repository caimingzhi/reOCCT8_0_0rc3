#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_NamedUnit;
class StepBasic_DerivedUnit;

//! Implements a select type unit (NamedUnit or DerivedUnit)
class StepBasic_Unit : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates empty object
  Standard_EXPORT StepBasic_Unit();

  //! Recognizes a type of Unit Entity
  //! 1 -> NamedUnit
  //! 2 -> DerivedUnit
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a NamedUnit (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_NamedUnit> NamedUnit() const;

  //! returns Value as a DerivedUnit (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_DerivedUnit> DerivedUnit() const;
};
