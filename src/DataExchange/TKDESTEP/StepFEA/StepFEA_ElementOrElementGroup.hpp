#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepFEA_ElementRepresentation;
class StepFEA_ElementGroup;

class StepFEA_ElementOrElementGroup : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepFEA_ElementOrElementGroup();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepFEA_ElementRepresentation> ElementRepresentation() const;

  Standard_EXPORT occ::handle<StepFEA_ElementGroup> ElementGroup() const;
};
