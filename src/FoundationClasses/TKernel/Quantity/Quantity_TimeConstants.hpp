#pragma once


//! @file Quantity_TimeConstants.hpp
//! Internal header providing shared time conversion constants and helper functions
//! for Quantity_Date and Quantity_Period classes.

#include <Standard_Integer.hpp>

namespace
{

//! Time conversion constants
constexpr int SECONDS_PER_MINUTE = 60;
constexpr int SECONDS_PER_HOUR   = 3600;  // 60 * 60
constexpr int SECONDS_PER_DAY    = 86400; // 24 * 3600

//! Microsecond conversion constants
constexpr int USECS_PER_MSEC = 1000;    // microseconds per millisecond
constexpr int USECS_PER_SEC  = 1000000; // microseconds per second

//! Extracts milliseconds and remaining microseconds from total microseconds
//! @param theUSec total microseconds
//! @param theMis output: milliseconds part
//! @param theMics output: remaining microseconds part
inline void extractMillisAndMicros(const int theUSec, int& theMis, int& theMics) noexcept
{
  theMis  = theUSec / USECS_PER_MSEC;
  theMics = theUSec - (theMis * USECS_PER_MSEC);
}

//! Extracts hours, minutes, and seconds from remaining seconds in a day
//! @param theCarry input/output: seconds to extract from, updated with remainder
//! @param theHH output: hours
//! @param theMN output: minutes
//! @param theSS output: seconds
inline void extractTimeComponents(int& theCarry, int& theHH, int& theMN, int& theSS) noexcept
{
  theHH = theCarry / SECONDS_PER_HOUR;
  theCarry -= SECONDS_PER_HOUR * theHH;
  theMN = theCarry / SECONDS_PER_MINUTE;
  theCarry -= theMN * SECONDS_PER_MINUTE;
  theSS = theCarry;
}

//! Normalizes time values when microseconds overflow into seconds
//! (handles addition overflow: myUSec >= 1000000)
//! Uses division for O(1) complexity
//! @param theSec input/output: seconds, incremented if overflow occurs
//! @param theUSec input/output: microseconds, normalized to 0..999999
inline void normalizeAdditionOverflow(int& theSec, int& theUSec) noexcept
{
  if (theUSec >= USECS_PER_SEC)
  {
    const int overflow = theUSec / USECS_PER_SEC;
    theSec += overflow;
    theUSec -= overflow * USECS_PER_SEC;
  }
}

//! Normalizes time values when microseconds require borrowing from seconds
//! (handles subtraction borrow: myUSec < 0)
//! Uses ceiling division for O(1) complexity
//! @param theSec input/output: seconds, decremented if borrow occurs
//! @param theUSec input/output: microseconds, normalized to 0..999999
inline void normalizeSubtractionBorrow(int& theSec, int& theUSec) noexcept
{
  if (theUSec < 0)
  {
    const int borrow = (-theUSec + USECS_PER_SEC - 1) / USECS_PER_SEC;
    theSec -= borrow;
    theUSec += borrow * USECS_PER_SEC;
  }
}

} // anonymous namespace

