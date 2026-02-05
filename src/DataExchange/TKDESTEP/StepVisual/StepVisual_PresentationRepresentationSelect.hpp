#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_PresentationRepresentation;
class StepVisual_PresentationSet;

class StepVisual_PresentationRepresentationSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a PresentationRepresentationSelect SelectType
  Standard_EXPORT StepVisual_PresentationRepresentationSelect();

  //! Recognizes a PresentationRepresentationSelect Kind Entity that is :
  //! 1 -> PresentationRepresentation
  //! 2 -> PresentationSet
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a PresentationRepresentation (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PresentationRepresentation> PresentationRepresentation()
    const;

  //! returns Value as a PresentationSet (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PresentationSet> PresentationSet() const;
};
