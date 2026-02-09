#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepAP214_AppliedApprovalAssignment;
class StepAP214_AppliedDateAndTimeAssignment;
class StepAP214_AppliedDateAssignment;
class StepAP214_AppliedDocumentReference;
class StepAP214_AppliedExternalIdentificationAssignment;
class StepAP214_AppliedGroupAssignment;
class StepAP214_AppliedOrganizationAssignment;
class StepAP214_AppliedPersonAndOrganizationAssignment;
class StepAP214_AppliedSecurityClassificationAssignment;
class StepShape_DimensionalSize;
class StepBasic_GeneralProperty;
class StepDimTol_GeometricTolerance;
class StepBasic_ProductDefinitionRelationship;
class StepRepr_PropertyDefinition;
class StepRepr_PropertyDefinitionRelationship;
class StepRepr_ShapeAspect;
class StepRepr_ShapeAspectRelationship;

class StepAP242_ItemIdentifiedRepresentationUsageDefinition : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP242_ItemIdentifiedRepresentationUsageDefinition();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepAP214_AppliedApprovalAssignment> AppliedApprovalAssignment()
    const;

  Standard_EXPORT occ::handle<StepAP214_AppliedDateAndTimeAssignment> AppliedDateAndTimeAssignment()
    const;

  Standard_EXPORT occ::handle<StepAP214_AppliedDateAssignment> AppliedDateAssignment() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedDocumentReference> AppliedDocumentReference() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedExternalIdentificationAssignment>
                  AppliedExternalIdentificationAssignment() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedGroupAssignment> AppliedGroupAssignment() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedOrganizationAssignment>
                  AppliedOrganizationAssignment() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment>
                  AppliedPersonAndOrganizationAssignment() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedSecurityClassificationAssignment>
                  AppliedSecurityClassificationAssignment() const;

  Standard_EXPORT occ::handle<StepShape_DimensionalSize> DimensionalSize() const;

  Standard_EXPORT occ::handle<StepBasic_GeneralProperty> GeneralProperty() const;

  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> GeometricTolerance() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship>
                  ProductDefinitionRelationship() const;

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinition> PropertyDefinition() const;

  Standard_EXPORT occ::handle<StepRepr_PropertyDefinitionRelationship>
                  PropertyDefinitionRelationship() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspectRelationship> ShapeAspectRelationship() const;
};
