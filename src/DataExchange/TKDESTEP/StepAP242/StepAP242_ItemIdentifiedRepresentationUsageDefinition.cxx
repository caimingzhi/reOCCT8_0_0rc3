// Created on: 2015-07-10
// Created by: Irina KRYLOVA
// Copyright (c) 2015 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <StepAP242_ItemIdentifiedRepresentationUsageDefinition.hpp>
#include <MoniTool_Macros.hpp>
#include <StepAP214_AppliedApprovalAssignment.hpp>
#include <StepAP214_AppliedDateAndTimeAssignment.hpp>
#include <StepAP214_AppliedDateAssignment.hpp>
#include <StepAP214_AppliedDocumentReference.hpp>
#include <StepAP214_AppliedExternalIdentificationAssignment.hpp>
#include <StepAP214_AppliedGroupAssignment.hpp>
#include <StepAP214_AppliedOrganizationAssignment.hpp>
#include <StepAP214_AppliedPersonAndOrganizationAssignment.hpp>
#include <StepAP214_AppliedSecurityClassificationAssignment.hpp>
#include <StepBasic_GeneralProperty.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepDimTol_GeometricTolerance.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_PropertyDefinitionRelationship.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeAspectRelationship.hpp>
#include <StepShape_DimensionalSize.hpp>

//=================================================================================================

StepAP242_ItemIdentifiedRepresentationUsageDefinition::
  StepAP242_ItemIdentifiedRepresentationUsageDefinition() = default;

//=================================================================================================

int StepAP242_ItemIdentifiedRepresentationUsageDefinition::CaseNum(
  const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedApprovalAssignment)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedDateAndTimeAssignment)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedDateAssignment)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedDocumentReference)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedExternalIdentificationAssignment)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedGroupAssignment)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedOrganizationAssignment)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedPersonAndOrganizationAssignment)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedSecurityClassificationAssignment)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepShape_DimensionalSize)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_GeneralProperty)))
    return 11;
  if (ent->IsKind(STANDARD_TYPE(StepDimTol_GeometricTolerance)))
    return 12;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 13;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition)))
    return 14;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinitionRelationship)))
    return 15;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 16;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspectRelationship)))
    return 17;
  return 0;
}

occ::handle<StepAP214_AppliedApprovalAssignment>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::AppliedApprovalAssignment() const
{
  return GetCasted(StepAP214_AppliedApprovalAssignment, Value());
}

occ::handle<StepAP214_AppliedDateAndTimeAssignment>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::AppliedDateAndTimeAssignment() const
{
  return GetCasted(StepAP214_AppliedDateAndTimeAssignment, Value());
}

occ::handle<StepAP214_AppliedDateAssignment> StepAP242_ItemIdentifiedRepresentationUsageDefinition::
  AppliedDateAssignment() const
{
  return GetCasted(StepAP214_AppliedDateAssignment, Value());
}

occ::handle<StepAP214_AppliedDocumentReference>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::AppliedDocumentReference() const
{
  return GetCasted(StepAP214_AppliedDocumentReference, Value());
}

occ::handle<StepAP214_AppliedExternalIdentificationAssignment>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::AppliedExternalIdentificationAssignment()
    const
{
  return GetCasted(StepAP214_AppliedExternalIdentificationAssignment, Value());
}

occ::handle<StepAP214_AppliedGroupAssignment>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::AppliedGroupAssignment() const
{
  return GetCasted(StepAP214_AppliedGroupAssignment, Value());
}

occ::handle<StepAP214_AppliedOrganizationAssignment>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::AppliedOrganizationAssignment() const
{
  return GetCasted(StepAP214_AppliedOrganizationAssignment, Value());
}

occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::AppliedPersonAndOrganizationAssignment()
    const
{
  return GetCasted(StepAP214_AppliedPersonAndOrganizationAssignment, Value());
}

occ::handle<StepAP214_AppliedSecurityClassificationAssignment>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::AppliedSecurityClassificationAssignment()
    const
{
  return GetCasted(StepAP214_AppliedSecurityClassificationAssignment, Value());
}

occ::handle<StepShape_DimensionalSize> StepAP242_ItemIdentifiedRepresentationUsageDefinition::
  DimensionalSize() const
{
  return GetCasted(StepShape_DimensionalSize, Value());
}

occ::handle<StepBasic_GeneralProperty> StepAP242_ItemIdentifiedRepresentationUsageDefinition::
  GeneralProperty() const
{
  return GetCasted(StepBasic_GeneralProperty, Value());
}

occ::handle<StepDimTol_GeometricTolerance> StepAP242_ItemIdentifiedRepresentationUsageDefinition::
  GeometricTolerance() const
{
  return GetCasted(StepDimTol_GeometricTolerance, Value());
}

occ::handle<StepBasic_ProductDefinitionRelationship>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::ProductDefinitionRelationship() const
{
  return GetCasted(StepBasic_ProductDefinitionRelationship, Value());
}

occ::handle<StepRepr_PropertyDefinition> StepAP242_ItemIdentifiedRepresentationUsageDefinition::
  PropertyDefinition() const
{
  return GetCasted(StepRepr_PropertyDefinition, Value());
}

occ::handle<StepRepr_PropertyDefinitionRelationship>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::PropertyDefinitionRelationship() const
{
  return GetCasted(StepRepr_PropertyDefinitionRelationship, Value());
}

occ::handle<StepRepr_ShapeAspect> StepAP242_ItemIdentifiedRepresentationUsageDefinition::
  ShapeAspect() const
{
  return GetCasted(StepRepr_ShapeAspect, Value());
}

occ::handle<StepRepr_ShapeAspectRelationship>
  StepAP242_ItemIdentifiedRepresentationUsageDefinition::ShapeAspectRelationship() const
{
  return GetCasted(StepRepr_ShapeAspectRelationship, Value());
}
