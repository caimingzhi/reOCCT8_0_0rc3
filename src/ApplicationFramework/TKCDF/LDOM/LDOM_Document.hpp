#pragma once

#include <LDOM_Element.hpp>

#include <LDOM_Text.hpp>

//  Class LDOM_CDATASection

class LDOM_CDATASection : public LDOM_Text
{
public:
  // ---------- PUBLIC METHODS ----------

  LDOM_CDATASection() = default;

  // Empty constructor

  LDOM_CDATASection(const LDOM_CDATASection& theOther)

    = default;

  // Copy constructor

  LDOM_CDATASection& operator=(const LDOM_NullPtr* theNull)
  {
    return (LDOM_CDATASection&)LDOM_CharacterData::operator=(theNull);
  }

  // Nullify

  LDOM_CDATASection& operator=(const LDOM_CDATASection& theOther)
  {
    return (LDOM_CDATASection&)LDOM_CharacterData::operator=(theOther);
  }

  // Assignment

protected:
  friend class LDOM_Document;

  LDOM_CDATASection(const LDOM_BasicText& theText, const occ::handle<LDOM_MemManager>& theDoc)
      : LDOM_Text(theText, theDoc)
  {
  }
};

#include <LDOM_CharacterData.hpp>

//  Class LDOM_Comment

class LDOM_Comment : public LDOM_CharacterData
{
public:
  // ---------- PUBLIC METHODS ----------

  LDOM_Comment() = default;

  // Empty constructor

  LDOM_Comment(const LDOM_Comment& theOther)

    = default;

  // Copy constructor

  LDOM_Comment& operator=(const LDOM_NullPtr* theNull)
  {
    return (LDOM_Comment&)LDOM_CharacterData::operator=(theNull);
  }

  // Nullify

  LDOM_Comment& operator=(const LDOM_Comment& theOther)
  {
    return (LDOM_Comment&)LDOM_CharacterData::operator=(theOther);
  }

  // Assignment

protected:
  friend class LDOM_Document;

  // ---------- PROTECTED METHODS ----------

  LDOM_Comment(const LDOM_BasicText& theText, const occ::handle<LDOM_MemManager>& theDoc)
      : LDOM_CharacterData(theText, theDoc)
  {
  }
};

//  Class LDOM_Document

class LDOM_Document
{
public:
  // ---------- PUBLIC METHODS ----------
  Standard_EXPORT LDOM_Document();
  // Empty constructor

  Standard_EXPORT LDOM_Document(const LDOM_MemManager& aMemManager);
  // Called by LDOM_MemManager::Doc()

  //  Standard_EXPORT LDOM_Document (const LDOM_Document& theOther);
  // Copy constructor

  Standard_EXPORT ~LDOM_Document();
  // Destructor

  // ---- CREATE ----

  static Standard_EXPORT LDOM_Document createDocument(const LDOMString& theQualifiedName);
  // Create an empty document

  Standard_EXPORT LDOM_Element createElement(const LDOMString& theTagName);

  //  Standard_EXPORT LDOM_Element
  //                createElementNS         (const LDOMString& theNSuri,
  //                                         const LDOMString& theQualName);

  Standard_EXPORT LDOM_CDATASection createCDATASection(const LDOMString& theData);

  Standard_EXPORT LDOM_Comment createComment(const LDOMString& theData);

  Standard_EXPORT LDOM_Text createTextNode(const LDOMString& theData);

  // ---- GET ----

  Standard_EXPORT LDOM_Element getDocumentElement() const;

  Standard_EXPORT LDOM_NodeList getElementsByTagName(const LDOMString& theTagName) const;

  // ---- COMPARE ----

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

  // ---- UTIL ----

  Standard_EXPORT LDOM_Document& operator=(const LDOM_NullPtr*);

private:
  friend class LDOM_LDOMImplementation;
  friend class LDOMString;
  friend class LDOM_Node;
  // ---------- PRIVATE FIELDS ----------

  occ::handle<LDOM_MemManager> myMemManager;
};
