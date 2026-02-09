#pragma once

#include <LDOM_Node.hpp>

class LDOM_BasicNode;
class LDOM_BasicNodeSequence;

class LDOM_NodeList
{
public:
  Standard_EXPORT LDOM_NodeList();

  Standard_EXPORT LDOM_NodeList(const LDOM_NodeList& theOther);

  Standard_EXPORT LDOM_NodeList& operator=(const LDOM_NodeList& theOther);

  Standard_EXPORT ~LDOM_NodeList();

  Standard_EXPORT LDOM_NodeList& operator=(const LDOM_NullPtr*);

  Standard_EXPORT bool operator==(const LDOM_NullPtr*) const;

  Standard_EXPORT bool operator!=(const LDOM_NullPtr*) const;

  Standard_EXPORT LDOM_Node item(const int) const;

  Standard_EXPORT int getLength() const;

private:
  friend class LDOM_Document;
  friend class LDOM_Element;
  friend class LDOM_BasicElement;

  Standard_EXPORT LDOM_NodeList(const occ::handle<LDOM_MemManager>& aDoc);

  Standard_EXPORT void Append(const LDOM_BasicNode& aNode) const;

  occ::handle<LDOM_MemManager> myDoc;
  LDOM_BasicNodeSequence*      mySeq;
};
