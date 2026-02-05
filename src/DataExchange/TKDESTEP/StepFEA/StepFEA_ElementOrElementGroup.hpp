#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepFEA_ElementRepresentation;
class StepFEA_ElementGroup;

//! Representation of STEP SELECT type ElementOrElementGroup
class StepFEA_ElementOrElementGroup : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepFEA_ElementOrElementGroup();

  //! Recognizes a kind of ElementOrElementGroup select type
  //! 1 -> ElementRepresentation from StepFEA
  //! 2 -> ElementGroup from StepFEA
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as ElementRepresentation (or Null if another type)
  Standard_EXPORT occ::handle<StepFEA_ElementRepresentation> ElementRepresentation() const;

  //! Returns Value as ElementGroup (or Null if another type)
  Standard_EXPORT occ::handle<StepFEA_ElementGroup> ElementGroup() const;
};
