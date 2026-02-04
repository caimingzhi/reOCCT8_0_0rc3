#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepAP203_Change;
class StepAP203_StartWork;
class StepAP203_ChangeRequest;
class StepAP203_StartRequest;
class StepRepr_ConfigurationItem;
class StepBasic_Product;
class StepBasic_ProductDefinitionFormation;
class StepBasic_ProductDefinition;
class StepBasic_Contract;
class StepBasic_SecurityClassification;

//! Representation of STEP SELECT type PersonOrganizationItem
class StepAP203_PersonOrganizationItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepAP203_PersonOrganizationItem();

  //! Recognizes a kind of PersonOrganizationItem select type
  //! 1 -> Change from StepAP203
  //! 2 -> StartWork from StepAP203
  //! 3 -> ChangeRequest from StepAP203
  //! 4 -> StartRequest from StepAP203
  //! 5 -> ConfigurationItem from StepRepr
  //! 6 -> Product from StepBasic
  //! 7 -> ProductDefinitionFormation from StepBasic
  //! 8 -> ProductDefinition from StepBasic
  //! 9 -> Contract from StepBasic
  //! 10 -> SecurityClassification from StepBasic
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as Change (or Null if another type)
  Standard_EXPORT occ::handle<StepAP203_Change> Change() const;

  //! Returns Value as StartWork (or Null if another type)
  Standard_EXPORT occ::handle<StepAP203_StartWork> StartWork() const;

  //! Returns Value as ChangeRequest (or Null if another type)
  Standard_EXPORT occ::handle<StepAP203_ChangeRequest> ChangeRequest() const;

  //! Returns Value as StartRequest (or Null if another type)
  Standard_EXPORT occ::handle<StepAP203_StartRequest> StartRequest() const;

  //! Returns Value as ConfigurationItem (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ConfigurationItem> ConfigurationItem() const;

  //! Returns Value as Product (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Product> Product() const;

  //! Returns Value as ProductDefinitionFormation (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> ProductDefinitionFormation()
    const;

  //! Returns Value as ProductDefinition (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! Returns Value as Contract (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Contract> Contract() const;

  //! Returns Value as SecurityClassification (or Null if another type)
  Standard_EXPORT occ::handle<StepBasic_SecurityClassification> SecurityClassification() const;
};

