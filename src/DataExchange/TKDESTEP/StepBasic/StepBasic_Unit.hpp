#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_NamedUnit;
class StepBasic_DerivedUnit;

class StepBasic_Unit : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepBasic_Unit();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_NamedUnit> NamedUnit() const;

  Standard_EXPORT occ::handle<StepBasic_DerivedUnit> DerivedUnit() const;
};
