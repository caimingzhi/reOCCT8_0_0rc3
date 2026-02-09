#pragma once

#include <Standard_TypeDef.hpp>

#include <cctype>

constexpr bool IsEqual(const char One, const char Two)
{
  return One == Two;
}

inline bool IsAlphabetic(const char me)
{
  return std::isalpha((unsigned char)me) != 0;
}

inline bool IsDigit(const char me)
{
  return std::isdigit((unsigned char)me) != 0;
}

inline bool IsXDigit(const char me)
{
  return std::isxdigit((unsigned char)me) != 0;
}

inline bool IsAlphanumeric(const char me)
{
  return (IsAlphabetic(me) || IsDigit(me));
}

inline bool IsControl(const char me)
{
  return std::iscntrl((unsigned char)me) != 0;
}

inline bool IsGraphic(const char me)
{
  return std::isgraph((unsigned char)me) != 0;
}

inline bool IsLowerCase(const char me)
{
  return std::islower((unsigned char)me) != 0;
}

inline bool IsPrintable(const char me)
{
  return std::isprint((unsigned char)me) != 0;
}

inline bool IsPunctuation(const char me)
{
  return (IsGraphic(me) && !IsAlphanumeric(me));
}

inline bool IsSpace(const char me)
{
  return std::isspace((unsigned char)me) != 0;
}

inline bool IsUpperCase(const char me)
{
  return std::isupper((unsigned char)me) != 0;
}

inline char LowerCase(const char me)
{
  return (char)(unsigned char)std::tolower((unsigned char)me);
}

inline char UpperCase(const char me)
{
  return (char)(unsigned char)std::toupper((unsigned char)me);
}
