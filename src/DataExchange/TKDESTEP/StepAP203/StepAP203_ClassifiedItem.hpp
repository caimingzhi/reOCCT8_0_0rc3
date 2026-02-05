#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinitionFormation;
class StepRepr_AssemblyComponentUsage;

//! Representation of STEP SELECT type ClassifiedItem
class StepAP203_ClassifiedItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepAP203_ClassifiedItem();

  //! Recognizes a kind of ClassifiedItem select type
  //! 1 -> ProductDefinitionFormation from StepBasic
  //! 2 -> AssemblyComponentUsage from StepRepr
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as ProductDefinitionFormation (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;

  //! Returns Value as AssemblyComponentUsage (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_AssemblyComponentUsage> AssemblyComponentUsage() const;
};
