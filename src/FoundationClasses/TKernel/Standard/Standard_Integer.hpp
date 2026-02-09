#pragma once

#include <Standard_Std.hpp>
#include <Standard_TypeDef.hpp>

#include <algorithm>
#include <climits>
#include <cmath>

[[nodiscard]] constexpr int Abs(const int theValue)
{
  return theValue < 0 ? -theValue : theValue;
}

[[nodiscard]] constexpr bool IsEven(const int theValue)
{
  return theValue % 2 == 0;
}

[[nodiscard]] constexpr bool IsOdd(const int theValue)
{
  return theValue % 2 == 1;
}

Standard_DEPRECATED("This function duplicates std::max and will be removed in future releases. "
                    "Use std::max instead.")

constexpr int Max(const int theValue1, const int theValue2)
{
  return (std::max)(theValue1, theValue2);
}

Standard_DEPRECATED("This function duplicates std::min and will be removed in future releases. "
                    "Use std::min instead.")

constexpr int Min(const int theValue1, const int theValue2)
{
  return (std::min)(theValue1, theValue2);
}

[[nodiscard]] constexpr int Modulus(const int theValue, const int theDivisor)
{
  return theValue % theDivisor;
}

[[nodiscard]] constexpr int Square(const int theValue)
{
  return theValue * theValue;
}

[[nodiscard]] constexpr int IntegerFirst()
{
  return INT_MIN;
}

[[nodiscard]] constexpr int IntegerLast()
{
  return INT_MAX;
}

[[nodiscard]] constexpr int IntegerSize()
{
  return CHAR_BIT * sizeof(int);
}
