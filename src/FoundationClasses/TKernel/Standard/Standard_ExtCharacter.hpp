#pragma once

#include <Standard_TypeDef.hpp>

inline char16_t ToExtCharacter(const char achar)
{

  return (char16_t)((unsigned char)achar & 0x00ff);
}

inline char ToCharacter(const char16_t achar)
{

  return (char)(unsigned char)(achar & 0x00ff);
}

inline bool IsAnAscii(const char16_t achar)
{
  return !(achar & 0xff00);
}

inline bool IsEqual(const char16_t One, const char16_t Two)
{
  return One == Two;
}
