#include <TDataStd_ChildNodeIterator.hpp>

#include <TDataStd_TreeNode.hpp>

#define ChildNodeIterator_UpToBrother                                                              \
  {                                                                                                \
    while (!myNode.IsNull() && (myNode->Depth() > myFirstLevel) && myNode->myNext == NULL)         \
      myNode = myNode->myFather;                                                                   \
    if (!myNode.IsNull() && (myNode->Depth() > myFirstLevel) && myNode->myFather != NULL)          \
      myNode = myNode->myNext;                                                                     \
    else                                                                                           \
      myNode = NULL;                                                                               \
  }

TDataStd_ChildNodeIterator::TDataStd_ChildNodeIterator()
    : myFirstLevel(0)
{
}

TDataStd_ChildNodeIterator::TDataStd_ChildNodeIterator(
  const occ::handle<TDataStd_TreeNode>& aTreeNode,
  const bool                            allLevels)
    : myNode(aTreeNode->myFirst),
      myFirstLevel(allLevels ? aTreeNode->Depth() : -1)
{
}

void TDataStd_ChildNodeIterator::Initialize(const occ::handle<TDataStd_TreeNode>& aTreeNode,
                                            const bool                            allLevels)
{
  myNode       = aTreeNode->myFirst;
  myFirstLevel = allLevels ? aTreeNode->Depth() : -1;
}

void TDataStd_ChildNodeIterator::Next()
{
  if (myFirstLevel == -1)
  {
    myNode = myNode->myNext;
  }
  else
  {
    if (myNode->myFirst != nullptr)
      myNode = myNode->myFirst;
    else
      ChildNodeIterator_UpToBrother;
  }
}

void TDataStd_ChildNodeIterator::NextBrother()
{
  if (myNode->myNext != nullptr)
    myNode = myNode->myNext;
  else
    ChildNodeIterator_UpToBrother;
}
