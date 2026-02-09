#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <StepVisual_CoordinatesList.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepVisual_TessellatedPointSet : public StepVisual_TessellatedItem
{

public:
  Standard_EXPORT StepVisual_TessellatedPointSet();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepVisual_CoordinatesList>& theCoordinates,
                            const occ::handle<NCollection_HArray1<int>>&   thePointList);

  Standard_EXPORT occ::handle<StepVisual_CoordinatesList> Coordinates() const;

  Standard_EXPORT void SetCoordinates(
    const occ::handle<StepVisual_CoordinatesList>& theCoordinates);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> PointList() const;

  Standard_EXPORT void SetPointList(const occ::handle<NCollection_HArray1<int>>& thePointList);

  Standard_EXPORT int NbPointList() const;

  Standard_EXPORT int PointListValue(const int theNum) const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedPointSet, StepVisual_TessellatedItem)

private:
  occ::handle<StepVisual_CoordinatesList> myCoordinates;
  occ::handle<NCollection_HArray1<int>>   myPointList;
};
