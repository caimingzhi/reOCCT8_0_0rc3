#include <LDOM_DeclareSequence.hpp>
#include <LDOM_NodeList.hpp>
#include <LDOM_BasicNode.hpp>

typedef const LDOM_BasicNode* LDOM_BasicNodePtr;

DECLARE_SEQUENCE(LDOM_BasicNodeSequence, LDOM_BasicNodePtr)
IMPLEMENT_SEQUENCE(LDOM_BasicNodeSequence, LDOM_BasicNodePtr)

//=================================================================================================

LDOM_NodeList::LDOM_NodeList()
{
  mySeq = new LDOM_BasicNodeSequence;
}

//=================================================================================================

LDOM_NodeList::LDOM_NodeList(const occ::handle<LDOM_MemManager>& aDoc)
    : myDoc(aDoc)
{
  mySeq = new LDOM_BasicNodeSequence;
}

//=================================================================================================

void LDOM_NodeList::Append(const LDOM_BasicNode& aNode) const
{
  mySeq->Append(&aNode);
}

//=================================================================================================

LDOM_NodeList::LDOM_NodeList(const LDOM_NodeList& theOther)
{
  mySeq  = new LDOM_BasicNodeSequence;
  *mySeq = *theOther.mySeq;
  myDoc  = theOther.myDoc;
}

//=================================================================================================

LDOM_NodeList::~LDOM_NodeList()
{
  delete mySeq;
}

//=======================================================================
// function : operator =
// purpose  : Assignment
//=======================================================================

LDOM_NodeList& LDOM_NodeList::operator=(const LDOM_NodeList& theOther)
{
  myDoc  = theOther.myDoc;
  *mySeq = *theOther.mySeq;
  return *this;
}

//=======================================================================
// function : operator =
// purpose  : Nullify
//=======================================================================

LDOM_NodeList& LDOM_NodeList::operator=(const LDOM_NullPtr*)
{
  myDoc.Nullify();
  mySeq->Clear();
  return *this;
}

//=======================================================================
// function : operator ==
// purpose  :
//=======================================================================

bool LDOM_NodeList::operator==(const LDOM_NullPtr*) const
{
  return myDoc.IsNull() || mySeq->Length() == 0;
}

//=======================================================================
// function : operator !=
// purpose  :
//=======================================================================

bool LDOM_NodeList::operator!=(const LDOM_NullPtr*) const
{
  return !myDoc.IsNull() && mySeq->Length() != 0;
}

//=================================================================================================

LDOM_Node LDOM_NodeList::item(const int anIndex) const
{
  if (myDoc.IsNull() || anIndex < 0 || anIndex >= mySeq->Length())
    return LDOM_Node();
  return LDOM_Node(*mySeq->Value(anIndex + 1), myDoc);
}

//=================================================================================================

int LDOM_NodeList::getLength() const
{
  return mySeq->Length();
}
