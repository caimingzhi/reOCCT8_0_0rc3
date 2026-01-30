// Created on: 2000-05-10
// Created by: Andrey BETENEV
// Copyright (c) 2000-2014 OPEN CASCADE SAS
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

// Generator:	ExpToCas (EXPRESS -> CASCADE/XSTEP Translator) V1.1

#include <Standard_Transient.hpp>
#include <StepBasic_ActionAssignment.hpp>
#include <StepBasic_ActionRequestAssignment.hpp>
#include <StepBasic_ApprovalAssignment.hpp>
#include <StepBasic_ApprovalDateTime.hpp>
#include <StepBasic_CertificationAssignment.hpp>
#include <StepBasic_ContractAssignment.hpp>
#include <StepBasic_DocumentReference.hpp>
#include <StepBasic_EffectivityAssignment.hpp>
#include <StepBasic_GroupAssignment.hpp>
#include <StepBasic_NameAssignment.hpp>
#include <StepBasic_RoleSelect.hpp>
#include <StepBasic_SecurityClassificationAssignment.hpp>

//=================================================================================================

StepBasic_RoleSelect::StepBasic_RoleSelect() = default;

//=================================================================================================

int StepBasic_RoleSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ActionAssignment)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ActionRequestAssignment)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ApprovalAssignment)))
    return 3;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ApprovalDateTime)))
    return 4;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_CertificationAssignment)))
    return 5;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ContractAssignment)))
    return 6;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentReference)))
    return 7;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_EffectivityAssignment)))
    return 8;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_GroupAssignment)))
    return 9;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_NameAssignment)))
    return 10;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_SecurityClassificationAssignment)))
    return 11;
  return 0;
}

//=================================================================================================

occ::handle<StepBasic_ActionAssignment> StepBasic_RoleSelect::ActionAssignment() const
{
  return occ::down_cast<StepBasic_ActionAssignment>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ActionRequestAssignment> StepBasic_RoleSelect::ActionRequestAssignment() const
{
  return occ::down_cast<StepBasic_ActionRequestAssignment>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ApprovalAssignment> StepBasic_RoleSelect::ApprovalAssignment() const
{
  return occ::down_cast<StepBasic_ApprovalAssignment>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ApprovalDateTime> StepBasic_RoleSelect::ApprovalDateTime() const
{
  return occ::down_cast<StepBasic_ApprovalDateTime>(Value());
}

//=================================================================================================

occ::handle<StepBasic_CertificationAssignment> StepBasic_RoleSelect::CertificationAssignment() const
{
  return occ::down_cast<StepBasic_CertificationAssignment>(Value());
}

//=================================================================================================

occ::handle<StepBasic_ContractAssignment> StepBasic_RoleSelect::ContractAssignment() const
{
  return occ::down_cast<StepBasic_ContractAssignment>(Value());
}

//=================================================================================================

occ::handle<StepBasic_DocumentReference> StepBasic_RoleSelect::DocumentReference() const
{
  return occ::down_cast<StepBasic_DocumentReference>(Value());
}

//=================================================================================================

occ::handle<StepBasic_EffectivityAssignment> StepBasic_RoleSelect::EffectivityAssignment() const
{
  return occ::down_cast<StepBasic_EffectivityAssignment>(Value());
}

//=================================================================================================

occ::handle<StepBasic_GroupAssignment> StepBasic_RoleSelect::GroupAssignment() const
{
  return occ::down_cast<StepBasic_GroupAssignment>(Value());
}

//=================================================================================================

occ::handle<StepBasic_NameAssignment> StepBasic_RoleSelect::NameAssignment() const
{
  return occ::down_cast<StepBasic_NameAssignment>(Value());
}

//=================================================================================================

occ::handle<StepBasic_SecurityClassificationAssignment> StepBasic_RoleSelect::
  SecurityClassificationAssignment() const
{
  return occ::down_cast<StepBasic_SecurityClassificationAssignment>(Value());
}
