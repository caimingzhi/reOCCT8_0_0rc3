#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepRepr_Representation;
class StepRepr_RepresentationItem;
class StepVisual_PresentationSet;

class StepVisual_StyleContextSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a StyleContextSelect SelectType
  Standard_EXPORT StepVisual_StyleContextSelect();

  //! Recognizes a StyleContextSelect Kind Entity that is :
  //! 1 -> Representation
  //! 2 -> RepresentationItem
  //! 3 -> PresentationSet
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Representation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  //! returns Value as a RepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> RepresentationItem() const;

  //! returns Value as a PresentationSet (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PresentationSet> PresentationSet() const;
};

