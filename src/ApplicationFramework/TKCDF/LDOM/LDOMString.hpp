#pragma once

#include <LDOMBasicString.hpp>

class LDOM_MemManager;

class LDOMString : public LDOMBasicString
{
public:
  LDOMString()
      : myPtrDoc(nullptr)
  {
  }

  LDOMString(const LDOMString& anOther)

    = default;

  LDOMString(const int aValue)
      : LDOMBasicString(aValue),
        myPtrDoc(nullptr)
  {
  }

  LDOMString(const char* aValue)
      : LDOMBasicString(aValue),
        myPtrDoc(nullptr)
  {
  }

  const LDOM_MemManager& getOwnerDocument() const { return *myPtrDoc; }

  LDOMString& operator=(const LDOM_NullPtr* aNull)
  {
    LDOMBasicString::operator=(aNull);
    return *this;
  }

  LDOMString& operator=(const LDOMString& anOther) = default;

private:
  friend class LDOM_Document;
  friend class LDOM_Node;
  friend class LDOM_Element;
  friend class LDOM_BasicElement;
  friend class LDOM_BasicAttribute;
  friend class LDOM_BasicText;

  static LDOMString CreateDirectString(const char* aValue, const LDOM_MemManager& aDoc);

  LDOMString(const LDOMBasicString& anOther, const LDOM_MemManager& aDoc)
      : LDOMBasicString(anOther),
        myPtrDoc(&aDoc)
  {
  }

  LDOMString(const LDOMBasicString& anOther, const occ::handle<LDOM_MemManager>& aDoc);

private:
  const LDOM_MemManager* myPtrDoc;
};
