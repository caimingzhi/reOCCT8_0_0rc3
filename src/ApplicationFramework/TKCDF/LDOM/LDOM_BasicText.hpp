#pragma once

#include <LDOM_BasicNode.hpp>
#include <LDOMBasicString.hpp>

class LDOM_CharacterData;

class LDOM_BasicText : public LDOM_BasicNode
{
public:
  LDOM_BasicText()
      : LDOM_BasicNode(LDOM_Node::UNKNOWN)
  {
  }

  LDOM_BasicText& operator=(const LDOM_NullPtr* aNull);

  const LDOMBasicString& GetData() const { return myValue; }

  void SetData(const LDOMBasicString& aValue, const occ::handle<LDOM_MemManager>& aDoc)
  {
    myValue = LDOMString(aValue, aDoc);
  }

private:
  friend class LDOM_Node;
  friend class LDOMParser;
  friend class LDOM_Document;
  friend class LDOM_BasicElement;

  LDOM_BasicText(const LDOM_Node::NodeType aType, const LDOMBasicString& aData)
      : LDOM_BasicNode(aType),
        myValue(aData)
  {
  }

  LDOM_BasicText(const LDOM_CharacterData& aText);

  static LDOM_BasicText& Create(const LDOM_Node::NodeType           aType,
                                const LDOMBasicString&              aData,
                                const occ::handle<LDOM_MemManager>& aDoc);

private:
  LDOMBasicString myValue;
};
