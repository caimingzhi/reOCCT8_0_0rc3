#pragma once

#include <LDOM_CharacterData.hpp>

//  Class LDOM_Text

class LDOM_Text : public LDOM_CharacterData
{
public:
  // ---------- PUBLIC METHODS ----------

  LDOM_Text() = default;

  // Empty constructor

  LDOM_Text(const LDOM_Text& anOther)

    = default;

  // Copy constructor

  LDOM_Text& operator=(const LDOM_NullPtr* theNull)
  {
    return (LDOM_Text&)LDOM_CharacterData::operator=(theNull);
  }

  // Nullify

  LDOM_Text& operator=(const LDOM_Text& theOther)
  {
    return (LDOM_Text&)LDOM_CharacterData::operator=(theOther);
  }

  // Assignment

protected:
  friend class LDOM_Document;

  // ---------- PROTECTED METHODS ----------

  LDOM_Text(const LDOM_BasicText& theText, const occ::handle<LDOM_MemManager>& theDoc)
      : LDOM_CharacterData(theText, theDoc)
  {
  }
};
