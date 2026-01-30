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
#include <StepAP214_AutoDesignReferencingItem.hpp>
#include <StepBasic_Approval.hpp>
#include <StepBasic_DocumentRelationship.hpp>
#include <StepBasic_ProductCategory.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <StepRepr_ExternallyDefinedRepresentation.hpp>
#include <StepRepr_MappedItem.hpp>
#include <StepRepr_MaterialDesignation.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationRelationship.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepVisual_PresentationArea.hpp>
#include <StepVisual_PresentationView.hpp>

StepAP214_AutoDesignReferencingItem::StepAP214_AutoDesignReferencingItem() = default;

int StepAP214_AutoDesignReferencingItem::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;

  if (ent->IsKind(STANDARD_TYPE(StepBasic_Approval)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentRelationship)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ExternallyDefinedRepresentation)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MappedItem)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MaterialDesignation)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationArea)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationView)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductCategory)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition)))
    return 11;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_Representation)))
    return 12;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_RepresentationRelationship)))
    return 13;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_ShapeAspect)))
    return 14;
  return 0;
}

occ::handle<StepBasic_Approval> StepAP214_AutoDesignReferencingItem::Approval() const
{
  return GetCasted(StepBasic_Approval, Value());
}

occ::handle<StepBasic_DocumentRelationship> StepAP214_AutoDesignReferencingItem::
  DocumentRelationship() const
{
  return GetCasted(StepBasic_DocumentRelationship, Value());
}

occ::handle<StepRepr_ExternallyDefinedRepresentation> StepAP214_AutoDesignReferencingItem::
  ExternallyDefinedRepresentation() const
{
  return GetCasted(StepRepr_ExternallyDefinedRepresentation, Value());
}

occ::handle<StepRepr_MappedItem> StepAP214_AutoDesignReferencingItem::MappedItem() const
{
  return GetCasted(StepRepr_MappedItem, Value());
}

occ::handle<StepRepr_MaterialDesignation> StepAP214_AutoDesignReferencingItem::MaterialDesignation()
  const
{
  return GetCasted(StepRepr_MaterialDesignation, Value());
}

occ::handle<StepVisual_PresentationArea> StepAP214_AutoDesignReferencingItem::PresentationArea()
  const
{
  return GetCasted(StepVisual_PresentationArea, Value());
}

occ::handle<StepVisual_PresentationView> StepAP214_AutoDesignReferencingItem::PresentationView()
  const
{
  return GetCasted(StepVisual_PresentationView, Value());
}

occ::handle<StepBasic_ProductCategory> StepAP214_AutoDesignReferencingItem::ProductCategory() const
{
  return GetCasted(StepBasic_ProductCategory, Value());
}

occ::handle<StepBasic_ProductDefinition> StepAP214_AutoDesignReferencingItem::ProductDefinition()
  const
{
  return GetCasted(StepBasic_ProductDefinition, Value());
}

occ::handle<StepBasic_ProductDefinitionRelationship> StepAP214_AutoDesignReferencingItem::
  ProductDefinitionRelationship() const
{
  return GetCasted(StepBasic_ProductDefinitionRelationship, Value());
}

occ::handle<StepRepr_PropertyDefinition> StepAP214_AutoDesignReferencingItem::PropertyDefinition()
  const
{
  return GetCasted(StepRepr_PropertyDefinition, Value());
}

occ::handle<StepRepr_Representation> StepAP214_AutoDesignReferencingItem::Representation() const
{
  return GetCasted(StepRepr_Representation, Value());
}

occ::handle<StepRepr_RepresentationRelationship> StepAP214_AutoDesignReferencingItem::
  RepresentationRelationship() const
{
  return GetCasted(StepRepr_RepresentationRelationship, Value());
}

occ::handle<StepRepr_ShapeAspect> StepAP214_AutoDesignReferencingItem::ShapeAspect() const
{
  return GetCasted(StepRepr_ShapeAspect, Value());
}
