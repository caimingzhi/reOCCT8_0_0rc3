#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepRepr_Representation;
class StepRepr_RepresentationReference;

//! Representation of STEP SELECT type RepresentationOrRepresentationReference
class StepRepr_RepresentationOrRepresentationReference : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepRepr_RepresentationOrRepresentationReference();

  //! Recognizes a kind of RepresentationOrRepresentationReference select type
  //! -- 1 -> Representation
  //! -- 2 -> RepresentationReference
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as Representation (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  //! Returns Value as RepresentationReference (or Null if another type)
  Standard_EXPORT occ::handle<StepRepr_RepresentationReference> RepresentationReference() const;
};
