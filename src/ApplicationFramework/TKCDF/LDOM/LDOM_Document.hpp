#pragma once

#include <LDOM_Element.hpp>

#include <LDOM_Text.hpp>

class LDOM_CDATASection : public LDOM_Text
{
public:
  LDOM_CDATASection() = default;

  LDOM_CDATASection(const LDOM_CDATASection& theOther)

    = default;

  LDOM_CDATASection& operator=(const LDOM_NullPtr* theNull)
  {
    return (LDOM_CDATASection&)LDOM_CharacterData::operator=(theNull);
  }

  LDOM_CDATASection& operator=(const LDOM_CDATASection& theOther)
  {
    return (LDOM_CDATASection&)LDOM_CharacterData::operator=(theOther);
  }

protected:
  friend class LDOM_Document;

  LDOM_CDATASection(const LDOM_BasicText& theText, const occ::handle<LDOM_MemManager>& theDoc)
      : LDOM_Text(theText, theDoc)
  {
  }
};

#include <LDOM_CharacterData.hpp>

class LDOM_Comment : public LDOM_CharacterData
{
public:
  LDOM_Comment() = default;

  LDOM_Comment(const LDOM_Comment& theOther)

    = default;

  LDOM_Comment& operator=(const LDOM_NullPtr* theNull)
  {
    return (LDOM_Comment&)LDOM_CharacterData::operator=(theNull);
  }

  LDOM_Comment& operator=(const LDOM_Comment& theOther)
  {
    return (LDOM_Comment&)LDOM_CharacterData::operator=(theOther);
  }

protected:
  friend class LDOM_Document;

  LDOM_Comment(const LDOM_BasicText& theText, const occ::handle<LDOM_MemManager>& theDoc)
      : LDOM_CharacterData(theText, theDoc)
  {
  }
};

class LDOM_Document
{
public:
  Standard_EXPORT LDOM_Document();

  Standard_EXPORT LDOM_Document(const LDOM_MemManager& aMemManager);

  Standard_EXPORT ~LDOM_Document();

  static Standard_EXPORT LDOM_Document createDocument(const LDOMString& theQualifiedName);

  Standard_EXPORT LDOM_Element createElement(const LDOMString& theTagName);

  Standard_EXPORT LDOM_CDATASection createCDATASection(const LDOMString& theData);

  Standard_EXPORT LDOM_Comment createComment(const LDOMString& theData);

  Standard_EXPORT LDOM_Text createTextNode(const LDOMString& theData);

  Standard_EXPORT LDOM_Element getDocumentElement() const;

  Standard_EXPORT LDOM_NodeList getElementsByTagName(const LDOMString& theTagName) const;

  bool operator==(const LDOM_Document& anOther) const
  {
    return myMemManager == anOther.myMemManager;
  }

  bool operator!=(const LDOM_Document& anOther) const
  {
    return myMemManager != anOther.myMemManager;
  }

  bool operator==(const LDOM_NullPtr*) const;
  bool operator!=(const LDOM_NullPtr*) const;

  Standard_EXPORT bool isNull() const;

  Standard_EXPORT LDOM_Document& operator=(const LDOM_NullPtr*);

private:
  friend class LDOM_LDOMImplementation;
  friend class LDOMString;
  friend class LDOM_Node;

  occ::handle<LDOM_MemManager> myMemManager;
};
