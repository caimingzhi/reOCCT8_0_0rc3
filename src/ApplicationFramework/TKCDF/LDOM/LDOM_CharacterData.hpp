#pragma once

#include <LDOM_Node.hpp>

class LDOM_BasicText;

class LDOM_CharacterData : public LDOM_Node
{
public:
  LDOM_CharacterData()
      : myLength(-1)
  {
  }

  LDOM_CharacterData(const LDOM_CharacterData& theOther)
      : LDOM_Node(theOther),
        myLength(-1)
  {
  }

  Standard_EXPORT LDOM_CharacterData& operator=(const LDOM_NullPtr* aNull);

  Standard_EXPORT LDOM_CharacterData& operator=(const LDOM_CharacterData& anOther);

  LDOMString getData() const { return getNodeValue(); }

  Standard_EXPORT void setData(const LDOMString& aValue);

  Standard_EXPORT int getLength() const;

protected:
  LDOM_CharacterData(const LDOM_BasicText& aText, const occ::handle<LDOM_MemManager>& aDoc);

private:
  int myLength;
};
