

#include <StepShape_GeometricSet.hpp>
#include <StepShape_GeometricSetSelect.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_GeometricSet, StepGeom_GeometricRepresentationItem)

StepShape_GeometricSet::StepShape_GeometricSet() = default;

void StepShape_GeometricSet::Init(
  const occ::handle<TCollection_HAsciiString>&                          aName,
  const occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>>& aElements)
{

  elements = aElements;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_GeometricSet::SetElements(
  const occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>>& aElements)
{
  elements = aElements;
}

occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>> StepShape_GeometricSet::Elements()
  const
{
  return elements;
}

StepShape_GeometricSetSelect StepShape_GeometricSet::ElementsValue(const int num) const
{
  return elements->Value(num);
}

int StepShape_GeometricSet::NbElements() const
{
  if (elements.IsNull())
    return 0;
  return elements->Length();
}
