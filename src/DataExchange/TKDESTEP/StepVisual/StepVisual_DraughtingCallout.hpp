#pragma once

#include <Standard.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepVisual_DraughtingCalloutElement.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepVisual_DraughtingCallout : public StepGeom_GeometricRepresentationItem
{
public:
  Standard_EXPORT StepVisual_DraughtingCallout();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                 theName,
    const occ::handle<NCollection_HArray1<StepVisual_DraughtingCalloutElement>>& theContents);

  inline occ::handle<NCollection_HArray1<StepVisual_DraughtingCalloutElement>> Contents() const
  {
    return myContents;
  }

  inline void SetContents(
    const occ::handle<NCollection_HArray1<StepVisual_DraughtingCalloutElement>>& theContents)
  {
    myContents = theContents;
  }

  inline int NbContents() const { return (myContents.IsNull() ? 0 : myContents->Length()); }

  inline StepVisual_DraughtingCalloutElement ContentsValue(const int theNum) const
  {
    return myContents->Value(theNum);
  }

  inline void SetContentsValue(const int theNum, const StepVisual_DraughtingCalloutElement& theItem)
  {
    myContents->SetValue(theNum, theItem);
  }

  DEFINE_STANDARD_RTTIEXT(StepVisual_DraughtingCallout, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<NCollection_HArray1<StepVisual_DraughtingCalloutElement>> myContents;
};
