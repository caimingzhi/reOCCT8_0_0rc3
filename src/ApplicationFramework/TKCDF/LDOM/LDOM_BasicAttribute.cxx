#include <LDOM_BasicAttribute.hpp>
#include <LDOM_MemManager.hpp>
#include <LDOM_Attr.hpp>

//=================================================================================================

LDOM_BasicAttribute::LDOM_BasicAttribute(const LDOM_Attr& anAttr)
    : LDOM_BasicNode(anAttr.Origin()),
      myName(anAttr.getName().GetString()),
      myValue(anAttr.getValue())
{
}

//=======================================================================
// function : Create
// purpose  : construction in the Document's data pool
//=======================================================================

LDOM_BasicAttribute& LDOM_BasicAttribute::Create(const LDOMBasicString&              theName,
                                                 const occ::handle<LDOM_MemManager>& theDoc,
                                                 int&                                theHash)
{
  void*                aMem    = theDoc->Allocate(sizeof(LDOM_BasicAttribute));
  LDOM_BasicAttribute* aNewAtt = new (aMem) LDOM_BasicAttribute;

  const char* aString = theName.GetString();
  aNewAtt->myName     = theDoc->HashedAllocate(aString, (int)strlen(aString), theHash);

  aNewAtt->myNodeType = LDOM_Node::ATTRIBUTE_NODE;
  return *aNewAtt;
}

//=======================================================================
// function : operator =
// purpose  : Assignment to NULL
//=======================================================================

LDOM_BasicAttribute& LDOM_BasicAttribute::operator=(const LDOM_NullPtr* aNull)
{
  myName  = nullptr;
  myValue = aNull;
  LDOM_BasicNode::operator=(aNull);
  return *this;
}
