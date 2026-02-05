#include <StepVisual_BoxCharacteristicSelect.hpp>

StepVisual_BoxCharacteristicSelect::StepVisual_BoxCharacteristicSelect() = default;

void StepVisual_BoxCharacteristicSelect::SetTypeOfContent(const int aType)
{
  theTypeOfContent = aType;
}

int StepVisual_BoxCharacteristicSelect::TypeOfContent() const
{
  return theTypeOfContent;
}

double StepVisual_BoxCharacteristicSelect::RealValue() const
{
  return theRealValue;
}

void StepVisual_BoxCharacteristicSelect::SetRealValue(const double aValue)
{
  theRealValue = aValue;
}
