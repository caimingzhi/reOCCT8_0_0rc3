#pragma once

#include <Standard_Real.hpp>

class math_BullardGenerator
{
public:
  math_BullardGenerator(unsigned int theSeed = 1)
      : myStateHi(theSeed)
  {
    SetSeed(theSeed);
  }

  void SetSeed(unsigned int theSeed = 1)
  {
    myStateHi = theSeed;
    myStateLo = theSeed ^ 0x49616E42;
  }

  unsigned int NextInt()
  {
    myStateHi = (myStateHi >> 2) + (myStateHi << 2);

    myStateHi += myStateLo;
    myStateLo += myStateHi;

    return myStateHi;
  }

  double NextReal() { return NextInt() / static_cast<double>(0xFFFFFFFFu); }

private:
  unsigned int myStateHi;
  unsigned int myStateLo;
};
