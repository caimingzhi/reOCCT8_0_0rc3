#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ProductDefinition;
class StepBasic_ProductDefinitionReference;
class StepBasic_ProductDefinitionReferenceWithLocalRepresentation;

class StepBasic_ProductDefinitionOrReference : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a ProductDefinitionOrReference SelectType
  Standard_EXPORT StepBasic_ProductDefinitionOrReference();

  //! Recognizes a ProductDefinitionOrReference Kind Entity that is :
  //! 1 -> ProductDefinition
  //! 2 -> ProductDefinitionReference
  //! 3 -> ProductDefinitionReferenceWithLocalPresentation
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a ProductDefinition (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  //! returns Value as a ProductDefinitionReference (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionReference> ProductDefinitionReference()
    const;

  //! returns Value as a ProductDefinitionReferenceWithLocalRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionReferenceWithLocalRepresentation>
                  ProductDefinitionReferenceWithLocalRepresentation() const;
};
