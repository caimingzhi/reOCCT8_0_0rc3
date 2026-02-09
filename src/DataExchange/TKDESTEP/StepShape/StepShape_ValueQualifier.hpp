#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_PrecisionQualifier;
class StepShape_TypeQualifier;
class StepShape_ValueFormatTypeQualifier;

class StepShape_ValueQualifier : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_ValueQualifier();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepShape_PrecisionQualifier> PrecisionQualifier() const;

  Standard_EXPORT occ::handle<StepShape_TypeQualifier> TypeQualifier() const;

  Standard_EXPORT occ::handle<StepShape_ValueFormatTypeQualifier> ValueFormatTypeQualifier() const;
};
