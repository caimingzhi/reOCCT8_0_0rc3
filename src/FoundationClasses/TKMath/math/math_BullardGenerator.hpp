#pragma once


#include <Standard_Real.hpp>

//! Fast random number generator (the algorithm proposed by Ian C. Bullard).
class math_BullardGenerator
{
public:
  //! Creates new Xorshift 64-bit RNG.
  math_BullardGenerator(unsigned int theSeed = 1)
      : myStateHi(theSeed)
  {
    SetSeed(theSeed);
  }

  //! Setup new seed / reset defaults.
  void SetSeed(unsigned int theSeed = 1)
  {
    myStateHi = theSeed;
    myStateLo = theSeed ^ 0x49616E42;
  }

  //! Generates new 64-bit integer value.
  unsigned int NextInt()
  {
    myStateHi = (myStateHi >> 2) + (myStateHi << 2);

    myStateHi += myStateLo;
    myStateLo += myStateHi;

    return myStateHi;
  }

  //! Generates new floating-point value.
  double NextReal() { return NextInt() / static_cast<double>(0xFFFFFFFFu); }

private:
  unsigned int myStateHi;
  unsigned int myStateLo;
};

