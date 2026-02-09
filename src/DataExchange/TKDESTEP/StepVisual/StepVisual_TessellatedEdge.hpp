#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedStructuredItem.hpp>

#include <StepVisual_CoordinatesList.hpp>
#include <StepVisual_EdgeOrCurve.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepVisual_TessellatedEdge : public StepVisual_TessellatedStructuredItem
{

public:
  Standard_EXPORT StepVisual_TessellatedEdge();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepVisual_CoordinatesList>& theCoordinates,
                            const bool                                     theHasGeometricLink,
                            const StepVisual_EdgeOrCurve&                  theGeometricLink,
                            const occ::handle<NCollection_HArray1<int>>&   theLineStrip);

  Standard_EXPORT occ::handle<StepVisual_CoordinatesList> Coordinates() const;

  Standard_EXPORT void SetCoordinates(
    const occ::handle<StepVisual_CoordinatesList>& theCoordinates);

  Standard_EXPORT StepVisual_EdgeOrCurve GeometricLink() const;

  Standard_EXPORT void SetGeometricLink(const StepVisual_EdgeOrCurve& theGeometricLink);

  Standard_EXPORT bool HasGeometricLink() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> LineStrip() const;

  Standard_EXPORT void SetLineStrip(const occ::handle<NCollection_HArray1<int>>& theLineStrip);

  Standard_EXPORT int NbLineStrip() const;

  Standard_EXPORT int LineStripValue(const int theNum) const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedEdge, StepVisual_TessellatedStructuredItem)

private:
  occ::handle<StepVisual_CoordinatesList> myCoordinates;
  StepVisual_EdgeOrCurve                  myGeometricLink;
  occ::handle<NCollection_HArray1<int>>   myLineStrip;
  bool                                    myHasGeometricLink;
};
