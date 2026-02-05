#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>

class StepVisual_BoxCharacteristicSelect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_BoxCharacteristicSelect();

  Standard_EXPORT int TypeOfContent() const;

  Standard_EXPORT void SetTypeOfContent(const int aType);

  Standard_EXPORT double RealValue() const;

  Standard_EXPORT void SetRealValue(const double aValue);

private:
  double theRealValue;
  int    theTypeOfContent;
};
