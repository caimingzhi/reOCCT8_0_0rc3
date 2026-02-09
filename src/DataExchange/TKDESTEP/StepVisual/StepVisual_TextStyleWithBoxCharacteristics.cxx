

#include <StepVisual_TextStyleForDefinedFont.hpp>
#include <StepVisual_TextStyleWithBoxCharacteristics.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TextStyleWithBoxCharacteristics, StepVisual_TextStyle)

StepVisual_TextStyleWithBoxCharacteristics::StepVisual_TextStyleWithBoxCharacteristics() = default;

void StepVisual_TextStyleWithBoxCharacteristics::Init(
  const occ::handle<TCollection_HAsciiString>&                                aName,
  const occ::handle<StepVisual_TextStyleForDefinedFont>&                      aCharacterAppearance,
  const occ::handle<NCollection_HArray1<StepVisual_BoxCharacteristicSelect>>& aCharacteristics)
{

  characteristics = aCharacteristics;

  StepVisual_TextStyle::Init(aName, aCharacterAppearance);
}

void StepVisual_TextStyleWithBoxCharacteristics::SetCharacteristics(
  const occ::handle<NCollection_HArray1<StepVisual_BoxCharacteristicSelect>>& aCharacteristics)
{
  characteristics = aCharacteristics;
}

occ::handle<NCollection_HArray1<StepVisual_BoxCharacteristicSelect>>
  StepVisual_TextStyleWithBoxCharacteristics::Characteristics() const
{
  return characteristics;
}

StepVisual_BoxCharacteristicSelect StepVisual_TextStyleWithBoxCharacteristics::CharacteristicsValue(
  const int num) const
{
  return characteristics->Value(num);
}

int StepVisual_TextStyleWithBoxCharacteristics::NbCharacteristics() const
{
  return characteristics->Length();
}
