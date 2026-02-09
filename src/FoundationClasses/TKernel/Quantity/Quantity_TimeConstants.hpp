#pragma once

#include <Standard_Integer.hpp>

namespace
{

  constexpr int SECONDS_PER_MINUTE = 60;
  constexpr int SECONDS_PER_HOUR   = 3600;
  constexpr int SECONDS_PER_DAY    = 86400;

  constexpr int USECS_PER_MSEC = 1000;
  constexpr int USECS_PER_SEC  = 1000000;

  inline void extractMillisAndMicros(const int theUSec, int& theMis, int& theMics) noexcept
  {
    theMis  = theUSec / USECS_PER_MSEC;
    theMics = theUSec - (theMis * USECS_PER_MSEC);
  }

  inline void extractTimeComponents(int& theCarry, int& theHH, int& theMN, int& theSS) noexcept
  {
    theHH = theCarry / SECONDS_PER_HOUR;
    theCarry -= SECONDS_PER_HOUR * theHH;
    theMN = theCarry / SECONDS_PER_MINUTE;
    theCarry -= theMN * SECONDS_PER_MINUTE;
    theSS = theCarry;
  }

  inline void normalizeAdditionOverflow(int& theSec, int& theUSec) noexcept
  {
    if (theUSec >= USECS_PER_SEC)
    {
      const int overflow = theUSec / USECS_PER_SEC;
      theSec += overflow;
      theUSec -= overflow * USECS_PER_SEC;
    }
  }

  inline void normalizeSubtractionBorrow(int& theSec, int& theUSec) noexcept
  {
    if (theUSec < 0)
    {
      const int borrow = (-theUSec + USECS_PER_SEC - 1) / USECS_PER_SEC;
      theSec -= borrow;
      theUSec += borrow * USECS_PER_SEC;
    }
  }

} // namespace
