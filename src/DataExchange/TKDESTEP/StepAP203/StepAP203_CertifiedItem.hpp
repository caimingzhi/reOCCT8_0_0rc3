#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepRepr_SuppliedPartRelationship;

//! Representation of STEP SELECT type CertifiedItem
class StepAP203_CertifiedItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepAP203_CertifiedItem();

  //! Recognizes a kind of CertifiedItem select type
  //! 1 -> SuppliedPartRelationship from StepRepr
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as SuppliedPartRelationship (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_SuppliedPartRelationship> SuppliedPartRelationship() const;
};
