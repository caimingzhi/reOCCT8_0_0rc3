#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepAP214_ApprovalItem.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_ApprovalPersonOrganization;
class StepAP214_AppliedPersonAndOrganizationAssignment;
class StepAP214_AppliedOrganizationAssignment;

class StepAP214_DateAndTimeItem : public StepAP214_ApprovalItem
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a DateAndTimeItem SelectType
  Standard_EXPORT StepAP214_DateAndTimeItem();

  //! Recognizes a DateAndTimeItem Kind Entity that is :
  //! 1 -> ApprovalPersonOrganization
  //! 2 -> AppliedDateAndPersonAssignment
  //! 3 -> AppliedOrganizationAssignment
  //! 4 -> AssemblyComponentUsageSubstitute
  //! 5 -> DocumentFile
  //! 6 -> Effectivity
  //! 7 -> MaterialDesignation
  //! 8 -> MechanicalDesignGeometricPresentationRepresentation
  //! 9 -> PresentationArea
  //! 10 -> Product
  //! 11 -> ProductDefinition
  //! 12 -> ProductDefinitionFormation
  //! 13 -> ProductDefinitionRelationship
  //! 14 -> PropertyDefinition
  //! 15 -> ShapeRepresentation
  //! 16 -> SecurityClassification
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a ApprovalPersonOrganization (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_ApprovalPersonOrganization> ApprovalPersonOrganization()
    const;

  //! returns Value as a AppliedDateAndPersonAssignment (Null if another type)
  Standard_EXPORT occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment>
                  AppliedPersonAndOrganizationAssignment() const;

  //! returns Value as a AppliedOrganizationAssignment (Null if another type)
  Standard_EXPORT occ::handle<StepAP214_AppliedOrganizationAssignment>
                  AppliedOrganizationAssignment() const;
};

