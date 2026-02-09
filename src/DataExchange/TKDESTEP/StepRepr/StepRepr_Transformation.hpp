#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepRepr_ItemDefinedTransformation;
class StepRepr_FunctionallyDefinedTransformation;

class StepRepr_Transformation : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepRepr_Transformation();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepRepr_ItemDefinedTransformation> ItemDefinedTransformation() const;

  Standard_EXPORT occ::handle<StepRepr_FunctionallyDefinedTransformation>
                  FunctionallyDefinedTransformation() const;
};
