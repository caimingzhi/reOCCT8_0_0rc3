#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinitionFormation;

//! Representation of STEP SELECT type ContractedItem
class StepAP203_ContractedItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepAP203_ContractedItem();

  //! Recognizes a kind of ContractedItem select type
  //! 1 -> ProductDefinitionFormation from StepBasic
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as ProductDefinitionFormation (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;
};

