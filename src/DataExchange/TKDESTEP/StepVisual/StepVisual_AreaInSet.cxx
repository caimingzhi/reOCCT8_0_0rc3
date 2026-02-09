

#include <Standard_Type.hpp>
#include <StepVisual_AreaInSet.hpp>
#include <StepVisual_PresentationArea.hpp>
#include <StepVisual_PresentationSet.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_AreaInSet, Standard_Transient)

StepVisual_AreaInSet::StepVisual_AreaInSet() = default;

void StepVisual_AreaInSet::Init(const occ::handle<StepVisual_PresentationArea>& aArea,
                                const occ::handle<StepVisual_PresentationSet>&  aInSet)
{

  area  = aArea;
  inSet = aInSet;
}

void StepVisual_AreaInSet::SetArea(const occ::handle<StepVisual_PresentationArea>& aArea)
{
  area = aArea;
}

occ::handle<StepVisual_PresentationArea> StepVisual_AreaInSet::Area() const
{
  return area;
}

void StepVisual_AreaInSet::SetInSet(const occ::handle<StepVisual_PresentationSet>& aInSet)
{
  inSet = aInSet;
}

occ::handle<StepVisual_PresentationSet> StepVisual_AreaInSet::InSet() const
{
  return inSet;
}
