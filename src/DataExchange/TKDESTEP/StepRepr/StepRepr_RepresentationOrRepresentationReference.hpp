#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepRepr_Representation;
class StepRepr_RepresentationReference;

class StepRepr_RepresentationOrRepresentationReference : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepRepr_RepresentationOrRepresentationReference();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT occ::handle<StepRepr_RepresentationReference> RepresentationReference() const;
};
