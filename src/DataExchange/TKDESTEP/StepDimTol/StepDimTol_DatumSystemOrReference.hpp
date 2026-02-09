#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepDimTol_DatumSystem;
class StepDimTol_DatumReference;

class StepDimTol_DatumSystemOrReference : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepDimTol_DatumSystemOrReference();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepDimTol_DatumSystem> DatumSystem() const;

  Standard_EXPORT occ::handle<StepDimTol_DatumReference> DatumReference() const;
};
