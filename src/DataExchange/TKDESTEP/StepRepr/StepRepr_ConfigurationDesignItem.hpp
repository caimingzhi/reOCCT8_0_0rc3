#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinition;
class StepBasic_ProductDefinitionFormation;

//! Representation of STEP SELECT type ConfigurationDesignItem
class StepRepr_ConfigurationDesignItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepRepr_ConfigurationDesignItem();

  //! Recognizes a kind of ConfigurationDesignItem select type
  //! 1 -> ProductDefinition from StepBasic
  //! 2 -> ProductDefinitionFormation from StepBasic
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as ProductDefinition (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! Returns Value as ProductDefinitionFormation (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;
};
