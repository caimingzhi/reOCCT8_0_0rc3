#pragma once

#include <NCollection_UBTree.hpp>
#include <NCollection_Vector.hpp>

#include <random>

template <class TheObjType, class TheBndType>
class NCollection_UBTreeFiller
{
public:
  struct ObjBnd
  {
    TheObjType myObj;
    TheBndType myBnd;

    ObjBnd(const TheObjType& theObj, const TheBndType& theBnd)
        : myObj(theObj),
          myBnd(theBnd)
    {
    }

    ObjBnd()
        : myObj(TheObjType()),
          myBnd(TheBndType())
    {
    }
  };

  typedef NCollection_UBTree<TheObjType, TheBndType> UBTree;
  typedef typename UBTree::TreeNode                  UBTreeNode;

  NCollection_UBTreeFiller(UBTree&                                       theTree,
                           const occ::handle<NCollection_BaseAllocator>& theAlloc     = nullptr,
                           const bool                                    isFullRandom = true)
      : myTree(theTree),
        mySeqPtr(256, theAlloc),
        myRandGen(5489u),
        myIsFullRandom(isFullRandom)
  {
  }

  void Add(const TheObjType& theObj, const TheBndType& theBnd)
  {
    mySeqPtr.Append(ObjBnd(theObj, theBnd));
  }

  int Fill();

  void Reset() { mySeqPtr.Clear(); }

  int CheckTree(Standard_OStream& theStream);

  ~NCollection_UBTreeFiller()
  {
    if (mySeqPtr.Length() > 0)
#ifdef OCCT_DEBUG_UBTREE
      std::cout << "~NCollection_UBTreeFiller: " << Fill() << " objects added to the tree"
                << std::endl;
#else
      Fill();
#endif
  }

private:
  NCollection_UBTreeFiller& operator=(const NCollection_UBTreeFiller&) = delete;

  static double checkNode(const UBTreeNode& theNode, const int theLength, int& theNumber);

private:
  UBTree&                    myTree;
  NCollection_Vector<ObjBnd> mySeqPtr;
  std::mt19937               myRandGen;
  bool                       myIsFullRandom;
};

template <class TheObjType, class TheBndType>
int NCollection_UBTreeFiller<TheObjType, TheBndType>::Fill()
{
  int i, nbAdd = mySeqPtr.Length();

  if (myIsFullRandom)
  {
    for (i = nbAdd; i > 0; i--)
    {
      unsigned int ind      = (unsigned int)myRandGen();
      ind                   = ind % i;
      const ObjBnd& aObjBnd = mySeqPtr(ind);
      myTree.Add(aObjBnd.myObj, aObjBnd.myBnd);
      mySeqPtr(ind) = mySeqPtr(i - 1);
    }
  }
  else
  {
    for (i = nbAdd; i > 0; i--)
    {
      unsigned int ind      = (unsigned int)myRandGen();
      ind                   = i - (ind % i) - 1;
      const ObjBnd& aObjBnd = mySeqPtr(ind);
      myTree.Add(aObjBnd.myObj, aObjBnd.myBnd);
      mySeqPtr(ind) = mySeqPtr(i - 1);
    }
  }
  mySeqPtr.Clear();
  return nbAdd;
}

template <class TheObjType, class TheBndType>
int NCollection_UBTreeFiller<TheObjType, TheBndType>::CheckTree(Standard_OStream& theStream)
{
  int          aNumber(0);
  const double aLen  = checkNode(myTree.Root(), 0, aNumber);
  const double num   = (double)aNumber;
  const double aLen1 = sqrt(aLen / num);
  const double aLen0 = log(num) / log(2.);
  char         buf[128];
  Sprintf(buf, "Checking UBTree:%8d leaves, balance =%7.2f", aNumber, aLen1 / aLen0);
  theStream << buf << std::endl;
  return aNumber;
}

template <class TheObjType, class TheBndType>
double NCollection_UBTreeFiller<TheObjType, TheBndType>::checkNode(
  const typename NCollection_UBTree<TheObjType, TheBndType>::TreeNode& theNode,
  const int                                                            theLength,
  int&                                                                 theNumber)
{
  double aLength;
  if (!theNode.IsLeaf())
    aLength = (checkNode(theNode.Child(0), theLength + 1, theNumber)
               + checkNode(theNode.Child(1), theLength + 1, theNumber));
  else
  {
    theNumber++;
    aLength = theLength * theLength;
  }
  return aLength;
}
