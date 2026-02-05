#include <StepVisual_DraughtingCallout.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_DraughtingCallout, StepGeom_GeometricRepresentationItem)

//=================================================================================================

StepVisual_DraughtingCallout::StepVisual_DraughtingCallout() = default;

//=================================================================================================

void StepVisual_DraughtingCallout::Init(
  const occ::handle<TCollection_HAsciiString>&                                 theName,
  const occ::handle<NCollection_HArray1<StepVisual_DraughtingCalloutElement>>& theContents)
{
  StepGeom_GeometricRepresentationItem::Init(theName);
  myContents = theContents;
}
