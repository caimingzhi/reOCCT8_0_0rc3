#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepAP214_ApprovalItem.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepAP214_AppliedOrganizationAssignment;
class StepAP214_AppliedSecurityClassificationAssignment;
class StepBasic_Approval;

class StepAP214_PersonAndOrganizationItem : public StepAP214_ApprovalItem
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a PersonAndOrganizationItem SelectType
  Standard_EXPORT StepAP214_PersonAndOrganizationItem();

  //! Recognizes a APersonAndOrganizationItem Kind Entity that is :
  //! 1 -> AppliedOrganizationAssignment
  //! 2 -> AssemblyComponentUsageSubstitute
  //! 3 -> DocumentFile
  //! 4 -> MaterialDesignation
  //! 5 -> MechanicalDesignGeometricPresentationRepresentation
  //! 6 -> PresentationArea
  //! 7 -> Product
  //! 8 -> ProductDefinition
  //! 9 -> ProductDefinitionFormation
  //! 10 -> ProductDefinitionRelationship
  //! 11 -> PropertyDefinition
  //! 12 -> ShapeRepresentation
  //! 13 -> SecurityClassification
  //! 14 -> AppliedSecurityClassificationAssignment
  //! 15 -> Approval
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a AppliedOrganizationAssignment (Null if another type)
  Standard_EXPORT occ::handle<StepAP214_AppliedOrganizationAssignment>
                  AppliedOrganizationAssignment() const;

  //! returns Value as a AppliedSecurityClassificationAssignment (Null if another type)
  Standard_EXPORT occ::handle<StepAP214_AppliedSecurityClassificationAssignment>
                  AppliedSecurityClassificationAssignment() const;

  //! returns Value as a Approval (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Approval> Approval() const;
};
