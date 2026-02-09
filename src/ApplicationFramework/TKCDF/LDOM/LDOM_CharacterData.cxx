#include <LDOM_CharacterData.hpp>
#include <LDOM_BasicText.hpp>

LDOM_CharacterData::LDOM_CharacterData(const LDOM_BasicText&               aText,
                                       const occ::handle<LDOM_MemManager>& aDoc)
    : LDOM_Node(aText, aDoc),
      myLength(-1)
{
}

LDOM_CharacterData& LDOM_CharacterData::operator=(const LDOM_NullPtr* theNull)
{
  LDOM_Node::operator=(theNull);
  myLength = -1;
  return *this;
}

LDOM_CharacterData& LDOM_CharacterData::operator=(const LDOM_CharacterData& theOther) = default;

void LDOM_CharacterData::setData(const LDOMString& theValue)
{
  LDOM_BasicText& aText = (LDOM_BasicText&)Origin();
  aText.SetData(theValue, myDocument);
  myLength = -1;
}

int LDOM_CharacterData::getLength() const
{
  if (myLength < 0)
    (int&)myLength = (int)strlen(getNodeValue().GetString());
  return myLength;
}
