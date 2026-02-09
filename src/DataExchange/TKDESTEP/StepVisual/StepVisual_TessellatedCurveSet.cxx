

#include <StepVisual_TessellatedCurveSet.hpp>
#include <StepVisual_TessellatedItem.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedCurveSet, StepVisual_TessellatedItem)

StepVisual_TessellatedCurveSet::StepVisual_TessellatedCurveSet() = default;

void StepVisual_TessellatedCurveSet::Init(
  const occ::handle<TCollection_HAsciiString>&   theName,
  const occ::handle<StepVisual_CoordinatesList>& theCoordList,
  const NCollection_Handle<NCollection_Vector<occ::handle<NCollection_HSequence<int>>>>& theCurves)
{
  StepRepr_RepresentationItem::Init(theName);
  myCoordList = theCoordList;
  myCurves    = theCurves;
}

NCollection_Handle<NCollection_Vector<occ::handle<NCollection_HSequence<int>>>>
  StepVisual_TessellatedCurveSet::Curves() const
{
  return myCurves;
}

occ::handle<StepVisual_CoordinatesList> StepVisual_TessellatedCurveSet::CoordList() const
{
  return myCoordList;
}
