#pragma once

#include <Standard.hpp>

#include <StepShape_GeometricSetSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_GeometricSetSelect;

class StepShape_GeometricSet : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a GeometricSet
  Standard_EXPORT StepShape_GeometricSet();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                          aName,
    const occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>>& aElements);

  Standard_EXPORT void SetElements(
    const occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>>& aElements);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>> Elements() const;

  Standard_EXPORT StepShape_GeometricSetSelect ElementsValue(const int num) const;

  Standard_EXPORT int NbElements() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_GeometricSet, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>> elements;
};
