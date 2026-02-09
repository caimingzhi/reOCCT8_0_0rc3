#include <LDOM_BasicText.hpp>
#include <LDOM_MemManager.hpp>
#include <LDOM_CharacterData.hpp>

LDOM_BasicText::LDOM_BasicText(const LDOM_CharacterData& aText)
    : LDOM_BasicNode(aText.Origin()),
      myValue(aText.getData())
{
}

LDOM_BasicText& LDOM_BasicText::Create(const LDOM_Node::NodeType           aType,
                                       const LDOMBasicString&              aData,
                                       const occ::handle<LDOM_MemManager>& aDoc)
{
  void*           aMem     = aDoc->Allocate(sizeof(LDOM_BasicText));
  LDOM_BasicText* aNewText = new (aMem) LDOM_BasicText(aType, aData);
  return *aNewText;
}

LDOM_BasicText& LDOM_BasicText::operator=(const LDOM_NullPtr* aNull)
{
  myValue = aNull;
  LDOM_BasicNode::operator=(aNull);
  return *this;
}
