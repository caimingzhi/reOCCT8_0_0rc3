#pragma once

#include <NCollection_BaseAllocator.hpp>
#include <NCollection_DefineAlloc.hpp>

template <class TheObjType, class TheBndType>
class NCollection_UBTree
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

public:
  class Selector
  {
  public:
    Selector()
        : myStop(false)
    {
    }

    virtual bool Reject(const TheBndType&) const = 0;

    virtual bool Accept(const TheObjType&) = 0;

    bool Stop() const noexcept { return myStop; }

    virtual ~Selector() = default;

  protected:
    bool myStop;
  };

  class TreeNode
  {
  public:
    DEFINE_STANDARD_ALLOC
    DEFINE_NCOLLECTION_ALLOC

  public:
    TreeNode(const TheObjType& theObj, const TheBndType& theBnd)
        : myBnd(theBnd),
          myObject(theObj),
          myChildren(nullptr),
          myParent(nullptr)
    {
    }

    bool IsLeaf() const noexcept { return !myChildren; }

    bool IsRoot() const noexcept { return !myParent; }

    const TheBndType& Bnd() const noexcept { return myBnd; }

    TheBndType& ChangeBnd() noexcept { return myBnd; }

    const TheObjType& Object() const noexcept { return myObject; }

    const TreeNode& Child(const int i) const noexcept { return myChildren[i]; }

    TreeNode& ChangeChild(const int i) noexcept { return myChildren[i]; }

    const TreeNode& Parent() const noexcept { return *myParent; }

    TreeNode& ChangeParent() noexcept { return *myParent; }

    void Gemmate(const TheBndType&                             theNewBnd,
                 const TheObjType&                             theObj,
                 const TheBndType&                             theBnd,
                 const occ::handle<NCollection_BaseAllocator>& theAlloc)
    {

      TreeNode* children = (TreeNode*)theAlloc->Allocate(2 * sizeof(TreeNode));
      new (&children[0]) TreeNode;
      new (&children[1]) TreeNode;
      children[0]          = *this;
      children[1].myObject = theObj;
      children[1].myBnd    = theBnd;
      children[0].myParent = children[1].myParent = this;
      if (!IsLeaf())
      {
        myChildren[0].myParent = children;
        myChildren[1].myParent = children;
      }
      myChildren = children;
      myBnd      = theNewBnd;
      myObject   = TheObjType();
    }

    void Kill(const int i, const occ::handle<NCollection_BaseAllocator>& theAlloc)
    {
      if (!IsLeaf())
      {
        TreeNode* oldChildren = myChildren;
        const int iopp        = 1 - i;
        myBnd                 = oldChildren[iopp].myBnd;
        myObject              = oldChildren[iopp].myObject;
        myChildren            = oldChildren[iopp].myChildren;
        if (!IsLeaf())
        {
          myChildren[0].myParent = this;
          myChildren[1].myParent = this;
        }

        oldChildren[iopp].~TreeNode();
        delNode(&oldChildren[i], theAlloc);
        theAlloc->Free(oldChildren);
      }
    }

    ~TreeNode() { myChildren = nullptr; }

    static void delNode(TreeNode* theNode, const occ::handle<NCollection_BaseAllocator>& theAlloc)
    {
      if (theNode)
      {
        if (theNode->myChildren)
        {
          delNode(&theNode->myChildren[0], theAlloc);
          delNode(&theNode->myChildren[1], theAlloc);
          theAlloc->Free(theNode->myChildren);
        }
        theNode->~TreeNode();
      }
    }

  private:
    TreeNode()
        : myChildren(nullptr),
          myParent(nullptr)
    {
    }

    TheBndType myBnd;
    TheObjType myObject;
    TreeNode*  myChildren;
    TreeNode*  myParent;
  };

  NCollection_UBTree()
      : myRoot(nullptr),
        myLastNode(nullptr),
        myAlloc(NCollection_BaseAllocator::CommonBaseAllocator())
  {
  }

  explicit NCollection_UBTree(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : myRoot(nullptr),
        myLastNode(nullptr),
        myAlloc(!theAllocator.IsNull() ? theAllocator
                                       : NCollection_BaseAllocator::CommonBaseAllocator())
  {
  }

  virtual bool Add(const TheObjType& theObj, const TheBndType& theBnd);

  virtual int Select(Selector& theSelector) const
  {
    return (IsEmpty() ? 0 : Select(Root(), theSelector));
  }

  virtual void Clear(const occ::handle<NCollection_BaseAllocator>& aNewAlloc = nullptr)

  {
    if (myRoot)
    {
      TreeNode::delNode(myRoot, this->myAlloc);
      this->myAlloc->Free(myRoot);
      myRoot = nullptr;
    }
    if (!aNewAlloc.IsNull())
      myAlloc = aNewAlloc;
  }

  bool IsEmpty() const noexcept { return !myRoot; }

  const TreeNode& Root() const noexcept { return *myRoot; }

  virtual ~NCollection_UBTree() { Clear(); }

  const occ::handle<NCollection_BaseAllocator>& Allocator() const noexcept { return myAlloc; }

protected:
  TreeNode& ChangeLastNode() noexcept { return *myLastNode; }

  int Select(const TreeNode& theBranch, Selector& theSelector) const;

private:
  NCollection_UBTree(const NCollection_UBTree&) = delete;

  NCollection_UBTree& operator=(const NCollection_UBTree&) = delete;

  TreeNode*                              myRoot;
  TreeNode*                              myLastNode;
  occ::handle<NCollection_BaseAllocator> myAlloc;
};

template <class TheObjType, class TheBndType>
bool NCollection_UBTree<TheObjType, TheBndType>::Add(const TheObjType& theObj,
                                                     const TheBndType& theBnd)
{
  if (IsEmpty())
  {

    myRoot     = new (this->myAlloc) TreeNode(theObj, theBnd);
    myLastNode = myRoot;
    return true;
  }

  TreeNode* pBranch       = myRoot;
  bool      isOutOfBranch = pBranch->Bnd().IsOut(theBnd);

  for (;;)
  {

    if (isOutOfBranch || pBranch->IsLeaf())
    {
      TheBndType aNewBnd = theBnd;
      aNewBnd.Add(pBranch->Bnd());

      pBranch->Gemmate(aNewBnd, theObj, theBnd, this->myAlloc);
      myLastNode = &pBranch->ChangeChild(1);
      break;
    }

    pBranch->ChangeBnd().Add(theBnd);

    int  iBest   = 0;
    bool isOut[] = {pBranch->Child(0).Bnd().IsOut(theBnd), pBranch->Child(1).Bnd().IsOut(theBnd)};
    if (isOut[0] != isOut[1])
      iBest = (isOut[0] ? 1 : 0);
    else
    {
      TheBndType aUnion[] = {theBnd, theBnd};
      aUnion[0].Add(pBranch->Child(0).Bnd());
      aUnion[1].Add(pBranch->Child(1).Bnd());
      const double d1 = aUnion[0].SquareExtent();
      const double d2 = aUnion[1].SquareExtent();
      if (d1 > d2)
        iBest = 1;
    }

    isOutOfBranch = isOut[iBest];
    pBranch       = &pBranch->ChangeChild(iBest);
  }
  return true;
}

template <class TheObjType, class TheBndType>
int NCollection_UBTree<TheObjType, TheBndType>::Select(const TreeNode& theBranch,
                                                       Selector&       theSelector) const
{

  if (theSelector.Reject(theBranch.Bnd()))
    return 0;

  int nSel = 0;

  if (theBranch.IsLeaf())
  {

    if (theSelector.Accept(theBranch.Object()))
      nSel++;
  }
  else
  {

    nSel += Select(theBranch.Child(0), theSelector);
    if (!theSelector.Stop())
      nSel += Select(theBranch.Child(1), theSelector);
  }

  return nSel;
}

#define DEFINE_HUBTREE(_HUBTREE, _OBJTYPE, _BNDTYPE, _HPARENT)                                     \
  class _HUBTREE : public _HPARENT                                                                 \
  {                                                                                                \
  public:                                                                                          \
    typedef NCollection_UBTree<_OBJTYPE, _BNDTYPE> UBTree;                                         \
                                                                                                   \
    _HUBTREE()                                                                                     \
        : myTree(new UBTree)                                                                       \
    {                                                                                              \
    }                                                                                              \
                                                                                                   \
    _HUBTREE(const occ::handle<NCollection_BaseAllocator>& theAlloc)                               \
        : myTree(new UBTree(theAlloc))                                                             \
    {                                                                                              \
    }                                                                                              \
                                                                                                   \
    bool Add(const _OBJTYPE& theObj, const _BNDTYPE& theBnd)                                       \
    {                                                                                              \
      return ChangeTree().Add(theObj, theBnd);                                                     \
    }                                                                                              \
                                                                                                   \
    int Select(UBTree::Selector& theSelector) const                                                \
    {                                                                                              \
      return Tree().Select(theSelector);                                                           \
    }                                                                                              \
                                                                                                   \
    void Clear()                                                                                   \
    {                                                                                              \
      ChangeTree().Clear();                                                                        \
    }                                                                                              \
                                                                                                   \
    bool IsEmpty() const noexcept                                                                  \
    {                                                                                              \
      return Tree().IsEmpty();                                                                     \
    }                                                                                              \
                                                                                                   \
    const UBTree::TreeNode& Root() const                                                           \
    {                                                                                              \
      return Tree().Root();                                                                        \
    }                                                                                              \
                                                                                                   \
    const UBTree& Tree() const noexcept                                                            \
    {                                                                                              \
      return *myTree;                                                                              \
    }                                                                                              \
    UBTree& ChangeTree() noexcept                                                                  \
    {                                                                                              \
      return *myTree;                                                                              \
    }                                                                                              \
                                                                                                   \
    ~_HUBTREE()                                                                                    \
    {                                                                                              \
      delete myTree;                                                                               \
    }                                                                                              \
                                                                                                   \
    DEFINE_STANDARD_RTTI_INLINE(_HUBTREE, _HPARENT)                                                \
                                                                                                   \
  private:                                                                                         \
    _HUBTREE(UBTree*);                                                                             \
    _HUBTREE(const _HUBTREE&);                                                                     \
    void operator=(const _HUBTREE&);                                                               \
                                                                                                   \
  private:                                                                                         \
    UBTree* myTree;                                                                                \
  };                                                                                               \
  DEFINE_STANDARD_HANDLE(_HUBTREE, _HPARENT)

#define IMPLEMENT_HUBTREE(_HUBTREE, _HPARENT)
