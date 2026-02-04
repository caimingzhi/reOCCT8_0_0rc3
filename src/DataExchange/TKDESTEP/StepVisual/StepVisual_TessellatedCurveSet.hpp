#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepVisual_CoordinatesList.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <NCollection_Vector.hpp>
#include <NCollection_Handle.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

class StepVisual_TessellatedCurveSet : public StepVisual_TessellatedItem
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a DraughtingCalloutElement select type
  Standard_EXPORT StepVisual_TessellatedCurveSet();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&   theName,
    const occ::handle<StepVisual_CoordinatesList>& theCoordList,
    const NCollection_Handle<NCollection_Vector<occ::handle<NCollection_HSequence<int>>>>&
      theCurves);

  Standard_EXPORT occ::handle<StepVisual_CoordinatesList> CoordList() const;
  Standard_EXPORT NCollection_Handle<NCollection_Vector<occ::handle<NCollection_HSequence<int>>>>
                  Curves() const;

private:
  occ::handle<StepVisual_CoordinatesList>                                         myCoordList;
  NCollection_Handle<NCollection_Vector<occ::handle<NCollection_HSequence<int>>>> myCurves;

public:
  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedCurveSet, StepVisual_TessellatedItem)
};
