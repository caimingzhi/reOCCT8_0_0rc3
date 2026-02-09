#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_DocumentFile;
class StepAP214_AppliedOrganizationAssignment;
class StepAP214_AppliedPersonAndOrganizationAssignment;
class StepAP214_ExternallyDefinedClass;
class StepAP214_ExternallyDefinedGeneralProperty;
class StepBasic_Approval;
class StepBasic_ApprovalStatus;
class StepBasic_ExternalSource;
class StepBasic_OrganizationalAddress;
class StepBasic_ProductDefinition;
class StepBasic_SecurityClassification;
class StepBasic_VersionedActionRequest;
class StepGeom_TrimmedCurve;
class StepBasic_DateAndTimeAssignment;
class StepBasic_DateAssignment;

class StepAP214_ExternalIdentificationItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_ExternalIdentificationItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_DocumentFile> DocumentFile() const;

  Standard_EXPORT occ::handle<StepAP214_ExternallyDefinedClass> ExternallyDefinedClass() const;

  Standard_EXPORT occ::handle<StepAP214_ExternallyDefinedGeneralProperty>
                  ExternallyDefinedGeneralProperty() const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProductDefinition() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedOrganizationAssignment>
                  AppliedOrganizationAssignment() const;

  Standard_EXPORT occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment>
                  AppliedPersonAndOrganizationAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_Approval> Approval() const;

  Standard_EXPORT occ::handle<StepBasic_ApprovalStatus> ApprovalStatus() const;

  Standard_EXPORT occ::handle<StepBasic_ExternalSource> ExternalSource() const;

  Standard_EXPORT occ::handle<StepBasic_OrganizationalAddress> OrganizationalAddress() const;

  Standard_EXPORT occ::handle<StepBasic_SecurityClassification> SecurityClassification() const;

  Standard_EXPORT occ::handle<StepGeom_TrimmedCurve> TrimmedCurve() const;

  Standard_EXPORT occ::handle<StepBasic_VersionedActionRequest> VersionedActionRequest() const;

  Standard_EXPORT occ::handle<StepBasic_DateAndTimeAssignment> DateAndTimeAssignment() const;

  Standard_EXPORT occ::handle<StepBasic_DateAssignment> DateAssignment() const;
};
