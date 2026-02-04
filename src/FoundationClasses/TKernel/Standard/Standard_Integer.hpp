#pragma once


#include <Standard_Std.hpp>
#include <Standard_TypeDef.hpp>

#include <algorithm>
#include <climits>
#include <cmath>

//! Returns the absolute value of a int @p Value.
//! Equivalent to std::abs.
[[nodiscard]] constexpr int Abs(const int theValue)
{
  return theValue < 0 ? -theValue : theValue;
}

//! Returns true if @p theValue is even.
[[nodiscard]] constexpr bool IsEven(const int theValue)
{
  return theValue % 2 == 0;
}

//! Returns true if @p theValue is odd.
[[nodiscard]] constexpr bool IsOdd(const int theValue)
{
  return theValue % 2 == 1;
}

//! Returns the maximum value of two integers.
//! Equivalent to std::max.
Standard_DEPRECATED("This function duplicates std::max and will be removed in future releases. "
                    "Use std::max instead.")
constexpr int Max(const int theValue1, const int theValue2)
{
  return (std::max)(theValue1, theValue2);
}

//! Returns the minimum value of two integers.
//! Equivalent to std::min.
Standard_DEPRECATED("This function duplicates std::min and will be removed in future releases. "
                    "Use std::min instead.")
constexpr int Min(const int theValue1, const int theValue2)
{
  return (std::min)(theValue1, theValue2);
}

//! Returns the modulus of @p theValue by @p theDivisor.
[[nodiscard]] constexpr int Modulus(const int theValue, const int theDivisor)
{
  return theValue % theDivisor;
}

//! Returns the square of a int @p theValue.
//! Note that behavior is undefined in case of overflow.
[[nodiscard]] constexpr int Square(const int theValue)
{
  return theValue * theValue;
}

//! Returns the minimum value of an integer.
[[nodiscard]] constexpr int IntegerFirst()
{
  return INT_MIN;
}

//! Returns the maximum value of an integer.
[[nodiscard]] constexpr int IntegerLast()
{
  return INT_MAX;
}

//! Returns the size in bits of an integer.
[[nodiscard]] constexpr int IntegerSize()
{
  return CHAR_BIT * sizeof(int);
}
