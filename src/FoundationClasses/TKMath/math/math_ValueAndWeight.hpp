#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class math_ValueAndWeight
{
public:
  DEFINE_STANDARD_ALLOC

  math_ValueAndWeight()
      : myValue(0.),
        myWeight(0.)
  {
  }

  math_ValueAndWeight(double theValue, double theWeight)
      : myValue(theValue),
        myWeight(theWeight)
  {
  }

  double Value() const { return myValue; }

  double Weight() const { return myWeight; }

private:
  double myValue;
  double myWeight;
};

inline bool operator<(const math_ValueAndWeight& theLeft, const math_ValueAndWeight& theRight)
{
  return theLeft.Value() < theRight.Value();
}
