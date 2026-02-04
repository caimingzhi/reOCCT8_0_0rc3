#pragma once


#include <Standard_TypeDef.hpp>

// ===============
// inline methods
// ===============

// ------------------------------------------------------------------
// ToExtCharacter : Returns an ExtCharacter from a Character
// ------------------------------------------------------------------
inline char16_t ToExtCharacter(const char achar)
{
  //  extension a zero (partie haute-->octet de gauche) de achar
  return (char16_t)((unsigned char)achar & 0x00ff);
}

// ------------------------------------------------------------------
// ToCharacter : Returns an Character from an ExtCharacter
// ------------------------------------------------------------------
inline char ToCharacter(const char16_t achar)
{
  //  recuperer partie basse(octet de droite) de achar
  return (char)(unsigned char)(achar & 0x00ff);
}

// ------------------------------------------------------------------
// IsAnAscii : Returns True if an ExtCharacter is in the "Ascii Range"
// ------------------------------------------------------------------
inline bool IsAnAscii(const char16_t achar)
{
  return !(achar & 0xff00);
}

// ------------------------------------------------------------------
// IsEqual : Returns true if two characters have the same value
// ------------------------------------------------------------------
inline bool IsEqual(const char16_t One, const char16_t Two)
{
  return One == Two;
}

