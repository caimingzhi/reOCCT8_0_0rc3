// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepAP214_AppliedOrganizationAssignment.hpp>
#include <StepAP214_AppliedSecurityClassificationAssignment.hpp>
#include <StepAP214_PersonAndOrganizationItem.hpp>
#include <StepBasic_Approval.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepRepr_AssemblyComponentUsageSubstitute.hpp>
#include <StepRepr_MaterialDesignation.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepVisual_MechanicalDesignGeometricPresentationRepresentation.hpp>
#include <StepVisual_PresentationArea.hpp>

StepAP214_PersonAndOrganizationItem::StepAP214_PersonAndOrganizationItem() = default;

int StepAP214_PersonAndOrganizationItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedOrganizationAssignment)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_AssemblyComponentUsageSubstitute)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentFile)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MaterialDesignation)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_MechanicalDesignGeometricPresentationRepresentation)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationArea)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Product)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition)))
    return 11;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)))
    return 12;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_SecurityClassification)))
    return 13;
  if (ent->IsKind(STANDARD_TYPE(StepAP214_AppliedSecurityClassificationAssignment)))
    return 14;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Approval)))
    return 15;
  return 0;
}

occ::handle<StepAP214_AppliedOrganizationAssignment> StepAP214_PersonAndOrganizationItem::
  AppliedOrganizationAssignment() const
{
  return GetCasted(StepAP214_AppliedOrganizationAssignment, Value());
}

occ::handle<StepAP214_AppliedSecurityClassificationAssignment> StepAP214_PersonAndOrganizationItem::
  AppliedSecurityClassificationAssignment() const
{
  return GetCasted(StepAP214_AppliedSecurityClassificationAssignment, Value());
}

occ::handle<StepBasic_Approval> StepAP214_PersonAndOrganizationItem::Approval() const
{
  return GetCasted(StepBasic_Approval, Value());
}
