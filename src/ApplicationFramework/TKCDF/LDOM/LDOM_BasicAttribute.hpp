#pragma once

#include <LDOM_BasicNode.hpp>
#include <LDOMBasicString.hpp>

class LDOM_Attr;

class LDOM_BasicAttribute : public LDOM_BasicNode
{
public:
  LDOM_BasicAttribute()
      : LDOM_BasicNode(LDOM_Node::UNKNOWN),
        myName(nullptr)
  {
  }

  LDOM_BasicAttribute& operator=(const LDOM_NullPtr* aNull);

  const char* GetName() const { return myName; }

  const LDOMBasicString& GetValue() const { return myValue; }

  void SetValue(const LDOMBasicString& aValue, const occ::handle<LDOM_MemManager>& aDoc)
  {
    myValue = LDOMString(aValue, aDoc);
  }

private:
  friend class LDOM_Node;
  friend class LDOM_Attr;
  friend class LDOM_Element;
  friend class LDOM_BasicElement;
  friend class LDOM_XmlReader;

  LDOM_BasicAttribute(const LDOMBasicString& aName)
      : LDOM_BasicNode(LDOM_Node::ATTRIBUTE_NODE),
        myName(aName.GetString())
  {
  }

  static LDOM_BasicAttribute& Create(const LDOMBasicString&              theName,
                                     const occ::handle<LDOM_MemManager>& theDoc,
                                     int&                                theHashIndex);

  LDOM_BasicAttribute(const LDOM_Attr& anAttr);

private:
  const char*     myName;
  LDOMBasicString myValue;
};
