#pragma once

#include <algorithm>
#include <cmath>
#include <climits>
#include <float.h>

#include <Standard_TypeDef.hpp>

[[nodiscard]] constexpr float ShortRealSmall()
{
  return FLT_MIN;
}

Standard_DEPRECATED("This function duplicates std::abs and will be removed in future releases. "
                    "Use std::abs instead.")

inline float Abs(const float theValue)
{
  return std::abs(theValue);
}

[[nodiscard]] constexpr int ShortRealDigits()
{
  return FLT_DIG;
}

[[nodiscard]] constexpr float ShortRealEpsilon()
{
  return FLT_EPSILON;
}

[[nodiscard]] constexpr float ShortRealFirst()
{
  return -FLT_MAX;
}

[[nodiscard]] constexpr int ShortRealFirst10Exp()
{
  return FLT_MIN_10_EXP;
}

[[nodiscard]] constexpr float ShortRealLast()
{
  return FLT_MAX;
}

[[nodiscard]] constexpr int ShortRealLast10Exp()
{
  return FLT_MAX_10_EXP;
}

[[nodiscard]] constexpr int ShortRealMantissa()
{
  return FLT_MANT_DIG;
}

[[nodiscard]] constexpr int ShortRealRadix()
{
  return FLT_RADIX;
}

[[nodiscard]] constexpr int ShortRealSize()
{
  return CHAR_BIT * sizeof(float);
}

Standard_DEPRECATED("This function duplicates std::max and will be removed in future releases. "
                    "Use std::max instead.")

constexpr float Max(const float theValue1, const float theValue2)
{
  return (std::max)(theValue1, theValue2);
}

Standard_DEPRECATED("This function duplicates std::min and will be removed in future releases. "
                    "Use std::min instead.")

constexpr float Min(const float theValue1, const float theValue2)
{
  return (std::min)(theValue1, theValue2);
}
