#pragma once

#include <LDOM_CharacterData.hpp>

class LDOM_Text : public LDOM_CharacterData
{
public:
  LDOM_Text() = default;

  LDOM_Text(const LDOM_Text& anOther)

    = default;

  LDOM_Text& operator=(const LDOM_NullPtr* theNull)
  {
    return (LDOM_Text&)LDOM_CharacterData::operator=(theNull);
  }

  LDOM_Text& operator=(const LDOM_Text& theOther)
  {
    return (LDOM_Text&)LDOM_CharacterData::operator=(theOther);
  }

protected:
  friend class LDOM_Document;

  LDOM_Text(const LDOM_BasicText& theText, const occ::handle<LDOM_MemManager>& theDoc)
      : LDOM_CharacterData(theText, theDoc)
  {
  }
};
