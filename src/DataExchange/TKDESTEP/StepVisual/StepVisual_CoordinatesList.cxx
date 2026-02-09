

#include <StepVisual_CoordinatesList.hpp>
#include <StepVisual_TessellatedItem.hpp>
IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CoordinatesList, StepVisual_TessellatedItem)

StepVisual_CoordinatesList::StepVisual_CoordinatesList() = default;

void StepVisual_CoordinatesList::Init(const occ::handle<TCollection_HAsciiString>&    theName,
                                      const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints)
{
  StepRepr_RepresentationItem::Init(theName);
  myPoints = thePoints;
}

occ::handle<NCollection_HArray1<gp_XYZ>> StepVisual_CoordinatesList::Points() const
{
  return myPoints;
}
