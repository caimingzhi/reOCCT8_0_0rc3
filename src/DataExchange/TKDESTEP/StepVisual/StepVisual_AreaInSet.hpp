#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepVisual_PresentationArea;
class StepVisual_PresentationSet;

class StepVisual_AreaInSet : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_AreaInSet();

  Standard_EXPORT void Init(const occ::handle<StepVisual_PresentationArea>& aArea,
                            const occ::handle<StepVisual_PresentationSet>&  aInSet);

  Standard_EXPORT void SetArea(const occ::handle<StepVisual_PresentationArea>& aArea);

  Standard_EXPORT occ::handle<StepVisual_PresentationArea> Area() const;

  Standard_EXPORT void SetInSet(const occ::handle<StepVisual_PresentationSet>& aInSet);

  Standard_EXPORT occ::handle<StepVisual_PresentationSet> InSet() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_AreaInSet, Standard_Transient)

private:
  occ::handle<StepVisual_PresentationArea> area;
  occ::handle<StepVisual_PresentationSet>  inSet;
};
