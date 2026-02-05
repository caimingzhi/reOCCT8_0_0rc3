#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_PresentationArea;
class StepVisual_PresentationView;

class StepVisual_AreaOrView : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a AreaOrView SelectType
  Standard_EXPORT StepVisual_AreaOrView();

  //! Recognizes a AreaOrView Kind Entity that is :
  //! 1 -> PresentationArea
  //! 2 -> PresentationView
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a PresentationArea (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PresentationArea> PresentationArea() const;

  //! returns Value as a PresentationView (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PresentationView> PresentationView() const;
};
