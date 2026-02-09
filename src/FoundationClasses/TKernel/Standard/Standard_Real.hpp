#pragma once

#include <algorithm>
#include <cmath>
#include <climits>
#include <float.h>

#ifdef _MSC_VER
  #ifndef _USE_MATH_DEFINES
    #define _USE_MATH_DEFINES
  #endif
  #include <math.h>
#endif

#include <Standard_TypeDef.hpp>

Standard_DEPRECATED("This function duplicates std::acos and will be removed in future releases. "
                    "Use std::acos instead.")

inline double ACos(const double theValue)
{
  return std::acos(theValue);
}

Standard_DEPRECATED("Deprecated, use std::acos instead")
Standard_EXPORT double ACosApprox(const double theValue);

Standard_DEPRECATED("This function duplicates std::asin and will be removed in future releases. "
                    "Use std::asin instead.")

inline double ASin(const double theValue)
{
  return std::asin(theValue);
}

Standard_DEPRECATED("This function duplicates std::atan2 and will be removed in future releases. "
                    "Use std::atan2 instead.")

inline double ATan2(const double theX, const double theY)
{
  return std::atan2(theX, theY);
}

Standard_DEPRECATED("This function duplicates std::atanh and will be removed in future releases. "
                    "Use std::atanh instead.")

inline double ATanh(const double theValue)
{
  return std::atanh(theValue);
}

Standard_DEPRECATED("This function duplicates std::acosh and will be removed in future releases. "
                    "Use std::acosh instead.")

inline double ACosh(const double theValue)
{
  return std::acosh(theValue);
}

Standard_DEPRECATED("This function duplicates std::cosh and will be removed in future releases. "
                    "Use std::cosh instead.")

inline double Cosh(const double theValue)
{
  return std::cosh(theValue);
}

Standard_DEPRECATED("This function duplicates std::sinh and will be removed in future releases. "
                    "Use std::sinh instead.")

inline double Sinh(const double theValue)
{
  return std::sinh(theValue);
}

Standard_DEPRECATED("This function duplicates std::log and will be removed in future releases. "
                    "Use std::log instead.")

inline double Log(const double theValue)
{
  return std::log(theValue);
}

Standard_DEPRECATED("This function duplicates std::sqrt and will be removed in future releases. "
                    "Use std::sqrt instead.")

inline double Sqrt(const double theValue)
{
  return std::sqrt(theValue);
}

Standard_DEPRECATED(
  "This function duplicates std::nextafter and will be removed in future releases. "
  "Use std::nextafter instead.")

inline double NextAfter(const double theValue, const double theDirection)
{
  return std::nextafter(theValue, theDirection);
}

Standard_DEPRECATED(
  "This function duplicates std::copysign and will be removed in future releases. "
  "Use std::copysign instead.")

inline double Sign(const double theMagnitude, const double theSign)
{
  return std::copysign(theMagnitude, theSign);
}

[[nodiscard]] constexpr double RealSmall()
{
  return DBL_MIN;
}

Standard_DEPRECATED("This function duplicates std::abs and will be removed in future releases. "
                    "Use std::abs instead.")

inline double Abs(const double theValue)
{
  return std::abs(theValue);
}

[[nodiscard]] inline bool IsEqual(const double theValue1, const double theValue2)
{
  return std::abs(theValue1 - theValue2) < RealSmall();
}

[[nodiscard]] constexpr int RealDigits()
{
  return DBL_DIG;
}

[[nodiscard]] constexpr double RealEpsilon()
{
  return DBL_EPSILON;
}

[[nodiscard]] constexpr double RealFirst()
{
  return -DBL_MAX;
}

[[nodiscard]] constexpr int RealFirst10Exp()
{
  return DBL_MIN_10_EXP;
}

[[nodiscard]] constexpr double RealLast()
{
  return DBL_MAX;
}

[[nodiscard]] constexpr int RealLast10Exp()
{
  return DBL_MAX_10_EXP;
}

[[nodiscard]] constexpr int RealMantissa()
{
  return DBL_MANT_DIG;
}

[[nodiscard]] constexpr int RealRadix()
{
  return FLT_RADIX;
}

[[nodiscard]] constexpr int RealSize()
{
  return CHAR_BIT * sizeof(double);
}

[[nodiscard]] constexpr double IntToReal(const int theValue)
{
  return theValue;
}

Standard_DEPRECATED("This function duplicates std::atan and will be removed in future releases. "
                    "Use std::atan instead.")

inline double ATan(const double theValue)
{
  return std::atan(theValue);
}

Standard_DEPRECATED("This function duplicates std::ceil and will be removed in future releases. "
                    "Use std::ceil instead.")

inline double Ceiling(const double theValue)
{
  return std::ceil(theValue);
}

Standard_DEPRECATED("This function duplicates std::cos and will be removed in future releases. "
                    "Use std::cos instead.")

inline double Cos(const double theValue)
{
  return std::cos(theValue);
}

[[nodiscard]] inline double Epsilon(const double theValue)
{
  return theValue >= 0.0 ? (std::nextafter(theValue, RealLast()) - theValue)
                         : (theValue - std::nextafter(theValue, RealFirst()));
}

Standard_DEPRECATED("This function duplicates std::exp and will be removed in future releases. "
                    "Use std::exp instead.")

inline double Exp(const double theValue)
{
  return std::exp(theValue);
}

Standard_DEPRECATED("This function duplicates std::floor and will be removed in future releases. "
                    "Use std::floor instead.")

inline double Floor(const double theValue)
{
  return std::floor(theValue);
}

Standard_DEPRECATED("This function duplicates std::trunc and will be removed in future releases. "
                    "Use std::trunc instead.")

inline double IntegerPart(const double theValue)
{
  return std::trunc(theValue);
}

Standard_DEPRECATED("This function duplicates std::log10 and will be removed in future releases. "
                    "Use std::log10 instead.")

inline double Log10(const double theValue)
{
  return std::log10(theValue);
}

Standard_DEPRECATED("This function duplicates std::max and will be removed in future releases. "
                    "Use std::max instead.")

constexpr double Max(const double theValue1, const double theValue2)
{
  return (std::max)(theValue1, theValue2);
}

Standard_DEPRECATED("This function duplicates std::min and will be removed in future releases. "
                    "Use std::min instead.")

constexpr double Min(const double theValue1, const double theValue2)
{
  return (std::min)(theValue1, theValue2);
}

Standard_DEPRECATED("This function duplicates std::pow and will be removed in future releases. "
                    "Use std::pow instead.")

inline double Pow(const double theValue, const double thePower)
{
  return std::pow(theValue, thePower);
}

[[nodiscard]] inline double RealPart(const double theValue)
{
  return std::abs(std::trunc(theValue) - theValue);
}

[[nodiscard]] constexpr int RealToInt(const double theValue)
{

  return theValue < static_cast<double>(INT_MIN)
           ? static_cast<int>(INT_MIN)
           : (theValue > static_cast<double>(INT_MAX) ? static_cast<int>(INT_MAX)
                                                      : static_cast<int>(theValue));
}

[[nodiscard]] constexpr float RealToShortReal(const double theValue)
{
  return theValue < -FLT_MAX  ? -FLT_MAX
         : theValue > FLT_MAX ? FLT_MAX
                              : static_cast<float>(theValue);
}

Standard_DEPRECATED("This function duplicates std::round and will be removed in future releases. "
                    "Use std::round instead.")

inline double Round(const double theValue)
{
  return std::round(theValue);
}

Standard_DEPRECATED("This function duplicates std::sin and will be removed in future releases. "
                    "Use std::sin instead.")

inline double Sin(const double theValue)
{
  return std::sin(theValue);
}

Standard_DEPRECATED("This function duplicates std::asinh and will be removed in future releases. "
                    "Use std::asinh instead.")

inline double ASinh(const double theValue)
{
  return std::asinh(theValue);
}

[[nodiscard]] constexpr double Square(const double theValue)
{
  return theValue * theValue;
}

Standard_DEPRECATED("This function duplicates std::tan and will be removed in future releases. "
                    "Use std::tan instead.")

inline double Tan(const double theValue)
{
  return std::tan(theValue);
}

Standard_DEPRECATED("This function duplicates std::tanh and will be removed in future releases. "
                    "Use std::tanh instead.")

inline double Tanh(const double theValue)
{
  return std::tanh(theValue);
}
