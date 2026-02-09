#pragma once

#include <LDOMString.hpp>
#include <LDOM_MemManager.hpp>

class LDOM_BasicNode;

class LDOM_Node
{
public:
  enum NodeType
  {
    UNKNOWN            = 0,
    ELEMENT_NODE       = 1,
    ATTRIBUTE_NODE     = 2,
    TEXT_NODE          = 3,
    CDATA_SECTION_NODE = 4,
    COMMENT_NODE       = 8
  };

  LDOM_Node()
      : myOrigin(nullptr),
        myLastChild(nullptr)
  {
  }

  LDOM_Node(const LDOM_Node& anOther)

    = default;

  Standard_EXPORT const LDOM_MemManager& getOwnerDocument() const;

  Standard_EXPORT LDOM_Node& operator=(const LDOM_Node& anOther);

  Standard_EXPORT LDOM_Node& operator=(const LDOM_NullPtr* aNull);

  bool operator==(const LDOM_NullPtr*) const { return isNull(); }

  bool operator!=(const LDOM_NullPtr*) const { return !isNull(); }

  Standard_EXPORT bool operator==(const LDOM_Node& anOther) const;

  Standard_EXPORT bool operator!=(const LDOM_Node& anOther) const;

  Standard_EXPORT bool isNull() const;

  Standard_EXPORT NodeType getNodeType() const;

  Standard_EXPORT LDOMString getNodeName() const;

  Standard_EXPORT LDOMString getNodeValue() const;

  Standard_EXPORT LDOM_Node getFirstChild() const;

  Standard_EXPORT LDOM_Node getLastChild() const;

  Standard_EXPORT LDOM_Node getNextSibling() const;

  Standard_EXPORT void removeChild(const LDOM_Node& aChild);

  Standard_EXPORT void appendChild(const LDOM_Node& aChild);

  Standard_EXPORT bool hasChildNodes() const;

  Standard_EXPORT void SetValueClear() const;

protected:
  friend class LDOM_BasicAttribute;
  friend class LDOM_BasicElement;
  friend class LDOM_BasicText;
  friend class LDOM_NodeList;

  const LDOM_BasicNode& Origin() const;

  LDOM_Node(const LDOM_BasicNode& anOrig, const occ::handle<LDOM_MemManager>& aDoc)
      : myDocument(aDoc),
        myOrigin((LDOM_BasicNode*)&anOrig),
        myLastChild(nullptr)
  {
  }

protected:
  occ::handle<LDOM_MemManager> myDocument;

  LDOM_BasicNode* myOrigin;

  const LDOM_BasicNode* myLastChild;

  friend char* db_pretty_print(const LDOM_Node*, int, char*);
};
