#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinitionRelationship;
class StepBasic_ProductDefinition;

class StepAP214_PresentedItemSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a PresentedItemSelect SelectType
  Standard_EXPORT StepAP214_PresentedItemSelect();

  //! Recognizes a PresentedItemSelect Kind Entity that is :
  //! 1 -> ProductDefinition,
  //! 2 -> ProductDefinitionRelationship,
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a ProductDefinitionRelationship (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  //! returns Value as a ProductDefinition (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;
};

