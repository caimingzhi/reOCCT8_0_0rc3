#pragma once


#include <LDOM_Node.hpp>

class LDOM_BasicNode;
class LDOM_BasicNodeSequence;

//  Class LDOM_NodeList
//

class LDOM_NodeList
{
public:
  // ---------- PUBLIC METHODS ----------

  Standard_EXPORT LDOM_NodeList();
  // Empty constructor

  Standard_EXPORT LDOM_NodeList(const LDOM_NodeList& theOther);
  // Copy constructor

  Standard_EXPORT LDOM_NodeList& operator=(const LDOM_NodeList& theOther);
  // Copy constructor

  Standard_EXPORT ~LDOM_NodeList();
  // Destructor

  Standard_EXPORT LDOM_NodeList& operator=(const LDOM_NullPtr*);
  // Nullify

  Standard_EXPORT bool operator==(const LDOM_NullPtr*) const;

  Standard_EXPORT bool operator!=(const LDOM_NullPtr*) const;

  Standard_EXPORT LDOM_Node item(const int) const;

  Standard_EXPORT int getLength() const;

private:
  friend class LDOM_Document;
  friend class LDOM_Element;
  friend class LDOM_BasicElement;
  // ---------- PRIVATE FIELDS ----------

  Standard_EXPORT LDOM_NodeList(const occ::handle<LDOM_MemManager>& aDoc);

  Standard_EXPORT void Append(const LDOM_BasicNode& aNode) const;

  occ::handle<LDOM_MemManager> myDoc;
  LDOM_BasicNodeSequence*      mySeq;
};

