#include <TDF_LabelNode.hpp>

#include <TDF_Data.hpp>
#include <TDF_Label.hpp>

TDF_LabelNode::TDF_LabelNode(TDF_Data* aDataPtr)
    : myFather(nullptr),
#ifdef KEEP_LOCAL_ROOT
      myBrother(nullptr),
#else
      myBrother((TDF_LabelNode*)aDataPtr),
#endif
      myFirstChild(nullptr),
      myLastFoundChild(nullptr),
      myTag(0),
      myFlags(0),
#ifdef KEEP_LOCAL_ROOT
      myData(aDataPtr)
#endif
{
#ifdef OCCT_DEBUG
  myDebugEntry = '0';
#endif
}

TDF_LabelNode::TDF_LabelNode(const int aTag, TDF_LabelNode* aFather)
    : myFather(aFather),
      myBrother(nullptr),
      myFirstChild(nullptr),
      myLastFoundChild(nullptr),
      myTag(aTag),
      myFlags(0),
#ifdef KEEP_LOCAL_ROOT
      myData(nullptr)
#endif
{
  if (aFather != nullptr)
  {
    Depth(aFather->Depth() + 1);
#ifdef KEEP_LOCAL_ROOT
    myData = aFather->Data();
#endif
  }
#ifdef OCCT_DEBUG
  myDebugEntry = myFather->myDebugEntry;
  myDebugEntry += ':';
  myDebugEntry += aTag;
#endif
}

void TDF_LabelNode::Destroy(const TDF_HAllocator& theAllocator)
{

  while (myFirstChild != nullptr)
  {
    TDF_LabelNode* aSecondChild = myFirstChild->Brother();
    myFirstChild->Destroy(theAllocator);
    myFirstChild = aSecondChild;
  }
  this->~TDF_LabelNode();
  myFather = myBrother = myFirstChild = myLastFoundChild = nullptr;
  myTag = myFlags = 0;

  theAllocator->Free(this);
}

void TDF_LabelNode::AddAttribute(const occ::handle<TDF_Attribute>& afterAtt,
                                 const occ::handle<TDF_Attribute>& newAtt)
{
  newAtt->myFlags     = 1;
  newAtt->myLabelNode = this;
  if (afterAtt.IsNull())
  {
    newAtt->myNext   = myFirstAttribute;
    myFirstAttribute = newAtt;
  }
  else
  {
    newAtt->myNext   = afterAtt->myNext;
    afterAtt->myNext = newAtt;
  }
}

void TDF_LabelNode::RemoveAttribute(const occ::handle<TDF_Attribute>& afterAtt,
                                    const occ::handle<TDF_Attribute>& oldAtt)
{
  oldAtt->myFlags     = 0;
  oldAtt->myLabelNode = nullptr;
  if (afterAtt.IsNull())
  {
    myFirstAttribute = oldAtt->myNext;
  }
  else
  {
    afterAtt->myNext = oldAtt->myNext;
  }
}

TDF_LabelNode* TDF_LabelNode::RootNode()
{
#ifdef KEEP_LOCAL_ROOT
  return myData ? myData->myRoot : nullptr;
#else
  TDF_LabelNode* lp = this;
  while (lp->myFather != NULL)
    lp = lp->myFather;
  return lp;
#endif
}

const TDF_LabelNode* TDF_LabelNode::RootNode() const
{
#ifdef KEEP_LOCAL_ROOT
  return myData ? myData->myRoot : nullptr;
#else
  const TDF_LabelNode* lp = this;
  while (lp->myFather != NULL)
    lp = lp->myFather;
  return lp;
#endif
}

TDF_Data* TDF_LabelNode::Data() const
{
#ifdef KEEP_LOCAL_ROOT
  return myData;
#else
  const TDF_LabelNode* ln = RootNode()->myBrother;
  return ((TDF_Data*)ln);
#endif
}

void TDF_LabelNode::AllMayBeModified()
{
  MayBeModified(true);
  if (myFather && !myFather->MayBeModified())
    myFather->AllMayBeModified();
}
