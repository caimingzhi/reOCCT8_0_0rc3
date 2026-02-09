#pragma once

#include <NCollection_BaseMap.hpp>
#include <NCollection_TListNode.hpp>
#include <Standard_TypeMismatch.hpp>
#include <Standard_NoSuchObject.hpp>
#include <NCollection_StlIterator.hpp>
#include <NCollection_DefaultHasher.hpp>

#include <Standard_OutOfRange.hpp>
#include <utility>

template <class TheKeyType, class TheItemType, class Hasher = NCollection_DefaultHasher<TheKeyType>>
class NCollection_IndexedDataMap : public NCollection_BaseMap
{
public:
  typedef TheKeyType key_type;

  typedef TheItemType value_type;
  typedef Hasher      hasher;

private:
  class IndexedDataMapNode : public NCollection_TListNode<TheItemType>
  {
  public:
    IndexedDataMapNode(const TheKeyType&     theKey1,
                       const int             theIndex,
                       const TheItemType&    theItem,
                       NCollection_ListNode* theNext1)
        : NCollection_TListNode<TheItemType>(theItem, theNext1),
          myKey1(theKey1),
          myIndex(theIndex)
    {
    }

    IndexedDataMapNode(TheKeyType&&          theKey1,
                       const int             theIndex,
                       const TheItemType&    theItem,
                       NCollection_ListNode* theNext1)
        : NCollection_TListNode<TheItemType>(theItem, theNext1),
          myKey1(std::forward<TheKeyType>(theKey1)),
          myIndex(theIndex)
    {
    }

    IndexedDataMapNode(const TheKeyType&     theKey1,
                       const int             theIndex,
                       TheItemType&&         theItem,
                       NCollection_ListNode* theNext1)
        : NCollection_TListNode<TheItemType>(std::forward<TheItemType>(theItem), theNext1),
          myKey1(theKey1),
          myIndex(theIndex)
    {
    }

    IndexedDataMapNode(TheKeyType&&          theKey1,
                       const int             theIndex,
                       TheItemType&&         theItem,
                       NCollection_ListNode* theNext1)
        : NCollection_TListNode<TheItemType>(std::forward<TheItemType>(theItem), theNext1),
          myKey1(std::forward<TheKeyType>(theKey1)),
          myIndex(theIndex)
    {
    }

    TheKeyType& Key1() noexcept { return myKey1; }

    int& Index() noexcept { return myIndex; }

    static void delNode(NCollection_ListNode*                   theNode,
                        occ::handle<NCollection_BaseAllocator>& theAl) noexcept
    {
      ((IndexedDataMapNode*)theNode)->~IndexedDataMapNode();
      theAl->Free(theNode);
    }

  private:
    TheKeyType myKey1;
    int        myIndex;
  };

public:
  class Iterator
  {
  public:
    Iterator()
        : myMap(nullptr),
          myIndex(0)
    {
    }

    Iterator(const NCollection_IndexedDataMap& theMap)
        : myMap((NCollection_IndexedDataMap*)&theMap),
          myIndex(1)
    {
    }

    bool More() const noexcept { return (myMap != nullptr) && (myIndex <= myMap->Extent()); }

    void Next() noexcept { ++myIndex; }

    const TheItemType& Value() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_IndexedDataMap::Iterator::Value");
      return myMap->FindFromIndex(myIndex);
    }

    TheItemType& ChangeValue() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_IndexedDataMap::Iterator::ChangeValue");
      return myMap->ChangeFromIndex(myIndex);
    }

    const TheKeyType& Key() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_IndexedDataMap::Iterator::Key");
      return myMap->FindKey(myIndex);
    }

    bool IsEqual(const Iterator& theOther) const noexcept
    {
      return myMap == theOther.myMap && myIndex == theOther.myIndex;
    }

  private:
    NCollection_IndexedDataMap* myMap;
    int                         myIndex;
  };

  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheItemType, false> iterator;

  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheItemType, true>
    const_iterator;

  iterator begin() const noexcept { return Iterator(*this); }

  iterator end() const noexcept { return Iterator(); }

  const_iterator cbegin() const noexcept { return Iterator(*this); }

  const_iterator cend() const noexcept { return Iterator(); }

public:
  NCollection_IndexedDataMap()
      : NCollection_BaseMap(1, true, occ::handle<NCollection_BaseAllocator>())
  {
  }

  explicit NCollection_IndexedDataMap(
    const int                                     theNbBuckets,
    const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
      : NCollection_BaseMap(theNbBuckets, true, theAllocator)
  {
  }

  NCollection_IndexedDataMap(const NCollection_IndexedDataMap& theOther)
      : NCollection_BaseMap(theOther.NbBuckets(), true, theOther.myAllocator)
  {
    *this = theOther;
  }

  NCollection_IndexedDataMap(NCollection_IndexedDataMap&& theOther) noexcept
      : NCollection_BaseMap(std::forward<NCollection_BaseMap>(theOther))
  {
  }

  void Exchange(NCollection_IndexedDataMap& theOther) noexcept { this->exchangeMapsData(theOther); }

  NCollection_IndexedDataMap& Assign(const NCollection_IndexedDataMap& theOther)
  {
    if (this == &theOther)
      return *this;

    Clear();
    int anExt = theOther.Extent();
    if (anExt)
    {
      ReSize(anExt - 1);
      for (int anIndexIter = 1; anIndexIter <= anExt; ++anIndexIter)
      {
        const TheKeyType&   aKey1  = theOther.FindKey(anIndexIter);
        const TheItemType&  anItem = theOther.FindFromIndex(anIndexIter);
        const size_t        iK1    = HashCode(aKey1, NbBuckets());
        IndexedDataMapNode* pNode =
          new (this->myAllocator) IndexedDataMapNode(aKey1, anIndexIter, anItem, myData1[iK1]);
        myData1[iK1]             = pNode;
        myData2[anIndexIter - 1] = pNode;
        Increment();
      }
    }
    return *this;
  }

  NCollection_IndexedDataMap& operator=(const NCollection_IndexedDataMap& theOther)
  {
    return Assign(theOther);
  }

  NCollection_IndexedDataMap& operator=(NCollection_IndexedDataMap&& theOther) noexcept
  {
    if (this == &theOther)
      return *this;
    exchangeMapsData(theOther);
    return *this;
  }

  void ReSize(const int N)
  {
    NCollection_ListNode** ppNewData1 = nullptr;
    NCollection_ListNode** ppNewData2 = nullptr;
    int                    newBuck;
    if (BeginResize(N, newBuck, ppNewData1, ppNewData2))
    {
      if (myData1)
      {
        for (int aBucketIter = 0; aBucketIter <= NbBuckets(); ++aBucketIter)
        {
          if (myData1[aBucketIter])
          {
            IndexedDataMapNode* p = (IndexedDataMapNode*)myData1[aBucketIter];
            while (p)
            {
              const size_t        iK1 = HashCode(p->Key1(), newBuck);
              IndexedDataMapNode* q   = (IndexedDataMapNode*)p->Next();
              p->Next()               = ppNewData1[iK1];
              ppNewData1[iK1]         = p;
              p                       = q;
            }
          }
        }
      }
      EndResize(N,
                newBuck,
                ppNewData1,
                (NCollection_ListNode**)
                  Standard::Reallocate(myData2, (newBuck + 1) * sizeof(NCollection_ListNode*)));
    }
  }

  int Add(const TheKeyType& theKey1, const TheItemType& theItem)
  {
    if (Resizable())
    {
      ReSize(Extent());
    }
    IndexedDataMapNode* aNode;
    size_t              aHash;
    if (lookup(theKey1, aNode, aHash))
    {
      return aNode->Index();
    }
    const int aNewIndex = Increment();
    aNode = new (this->myAllocator) IndexedDataMapNode(theKey1, aNewIndex, theItem, myData1[aHash]);
    myData1[aHash]         = aNode;
    myData2[aNewIndex - 1] = aNode;
    return aNewIndex;
  }

  int Add(TheKeyType&& theKey1, const TheItemType& theItem)
  {
    if (Resizable())
    {
      ReSize(Extent());
    }
    IndexedDataMapNode* aNode;
    size_t              aHash;
    if (lookup(theKey1, aNode, aHash))
    {
      return aNode->Index();
    }
    const int aNewIndex = Increment();
    aNode               = new (this->myAllocator)
      IndexedDataMapNode(std::forward<TheKeyType>(theKey1), aNewIndex, theItem, myData1[aHash]);
    myData1[aHash]         = aNode;
    myData2[aNewIndex - 1] = aNode;
    return aNewIndex;
  }

  int Add(const TheKeyType& theKey1, TheItemType&& theItem)
  {
    if (Resizable())
    {
      ReSize(Extent());
    }
    IndexedDataMapNode* aNode;
    size_t              aHash;
    if (lookup(theKey1, aNode, aHash))
    {
      return aNode->Index();
    }
    const int aNewIndex = Increment();
    aNode               = new (this->myAllocator)
      IndexedDataMapNode(theKey1, aNewIndex, std::forward<TheItemType>(theItem), myData1[aHash]);
    myData1[aHash]         = aNode;
    myData2[aNewIndex - 1] = aNode;
    return aNewIndex;
  }

  int Add(TheKeyType&& theKey1, TheItemType&& theItem)
  {
    if (Resizable())
    {
      ReSize(Extent());
    }
    IndexedDataMapNode* aNode;
    size_t              aHash;
    if (lookup(theKey1, aNode, aHash))
    {
      return aNode->Index();
    }
    const int aNewIndex = Increment();
    aNode          = new (this->myAllocator) IndexedDataMapNode(std::forward<TheKeyType>(theKey1),
                                                       aNewIndex,
                                                       std::forward<TheItemType>(theItem),
                                                       myData1[aHash]);
    myData1[aHash] = aNode;
    myData2[aNewIndex - 1] = aNode;
    return aNewIndex;
  }

  bool Contains(const TheKeyType& theKey1) const
  {
    IndexedDataMapNode* aNode;
    return static_cast<bool>(lookup(theKey1, aNode));
  }

  void Substitute(const int theIndex, const TheKeyType& theKey1, const TheItemType& theItem)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > Extent(),
                                 "NCollection_IndexedDataMap::Substitute : "
                                 "Index is out of range");

    size_t              aHash;
    IndexedDataMapNode* aNode;
    if (lookup(theKey1, aNode, aHash))
    {
      if (aNode->Index() != theIndex)
      {
        throw Standard_DomainError("NCollection_IndexedDataMap::Substitute : "
                                   "Attempt to substitute existing key");
      }
      aNode->Key1()        = theKey1;
      aNode->ChangeValue() = theItem;
      return;
    }

    aNode = (IndexedDataMapNode*)myData2[theIndex - 1];

    const size_t        iK = HashCode(aNode->Key1(), NbBuckets());
    IndexedDataMapNode* q  = (IndexedDataMapNode*)myData1[iK];
    if (q == aNode)
      myData1[iK] = (IndexedDataMapNode*)aNode->Next();
    else
    {
      while (q->Next() != aNode)
        q = (IndexedDataMapNode*)q->Next();
      q->Next() = aNode->Next();
    }

    aNode->Key1()        = theKey1;
    aNode->ChangeValue() = theItem;
    aNode->Next()        = myData1[aHash];
    myData1[aHash]       = aNode;
  }

  void Swap(const int theIndex1, const int theIndex2)
  {
    Standard_OutOfRange_Raise_if(theIndex1 < 1 || theIndex1 > Extent() || theIndex2 < 1
                                   || theIndex2 > Extent(),
                                 "NCollection_IndexedDataMap::Swap");

    if (theIndex1 == theIndex2)
    {
      return;
    }

    IndexedDataMapNode* aP1 = (IndexedDataMapNode*)myData2[theIndex1 - 1];
    IndexedDataMapNode* aP2 = (IndexedDataMapNode*)myData2[theIndex2 - 1];
    std::swap(aP1->Index(), aP2->Index());
    myData2[theIndex2 - 1] = aP1;
    myData2[theIndex1 - 1] = aP2;
  }

  void RemoveLast()
  {
    const int aLastIndex = Extent();
    Standard_OutOfRange_Raise_if(aLastIndex == 0, "NCollection_IndexedDataMap::RemoveLast");

    IndexedDataMapNode* p   = (IndexedDataMapNode*)myData2[aLastIndex - 1];
    myData2[aLastIndex - 1] = nullptr;

    const size_t        iK1 = HashCode(p->Key1(), NbBuckets());
    IndexedDataMapNode* q   = (IndexedDataMapNode*)myData1[iK1];
    if (q == p)
      myData1[iK1] = (IndexedDataMapNode*)p->Next();
    else
    {
      while (q->Next() != p)
        q = (IndexedDataMapNode*)q->Next();
      q->Next() = p->Next();
    }
    p->~IndexedDataMapNode();
    this->myAllocator->Free(p);
    Decrement();
  }

  void RemoveFromIndex(const int theIndex)
  {
    const int aLastInd = Extent();
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > aLastInd,
                                 "NCollection_IndexedDataMap::Remove");
    if (theIndex != aLastInd)
    {
      Swap(theIndex, aLastInd);
    }
    RemoveLast();
  }

  void RemoveKey(const TheKeyType& theKey1)
  {
    int anIndToRemove = FindIndex(theKey1);
    if (anIndToRemove > 0)
    {
      RemoveFromIndex(anIndToRemove);
    }
  }

  const TheKeyType& FindKey(const int theIndex) const
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > Extent(),
                                 "NCollection_IndexedDataMap::FindKey");
    IndexedDataMapNode* aNode = (IndexedDataMapNode*)myData2[theIndex - 1];
    return aNode->Key1();
  }

  const TheItemType& FindFromIndex(const int theIndex) const
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > Extent(),
                                 "NCollection_IndexedDataMap::FindFromIndex");
    IndexedDataMapNode* aNode = (IndexedDataMapNode*)myData2[theIndex - 1];
    return aNode->Value();
  }

  const TheItemType& operator()(const int theIndex) const { return FindFromIndex(theIndex); }

  TheItemType& ChangeFromIndex(const int theIndex)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > Extent(),
                                 "NCollection_IndexedDataMap::ChangeFromIndex");
    IndexedDataMapNode* aNode = (IndexedDataMapNode*)myData2[theIndex - 1];
    return aNode->ChangeValue();
  }

  TheItemType& operator()(const int theIndex) { return ChangeFromIndex(theIndex); }

  int FindIndex(const TheKeyType& theKey1) const
  {
    IndexedDataMapNode* aNode;
    if (lookup(theKey1, aNode))
    {
      return aNode->Index();
    }
    return 0;
  }

  const TheItemType& FindFromKey(const TheKeyType& theKey1) const
  {
    Standard_NoSuchObject_Raise_if(IsEmpty(), "NCollection_IndexedDataMap::FindFromKey");
    IndexedDataMapNode* aNode;
    if (lookup(theKey1, aNode))
    {
      return aNode->Value();
    }
    throw Standard_NoSuchObject("NCollection_IndexedDataMap::FindFromKey");
  }

  TheItemType& ChangeFromKey(const TheKeyType& theKey1)
  {
    Standard_NoSuchObject_Raise_if(IsEmpty(), "NCollection_IndexedDataMap::ChangeFromKey");
    IndexedDataMapNode* aNode;
    if (lookup(theKey1, aNode))
    {
      return aNode->ChangeValue();
    }
    throw Standard_NoSuchObject("NCollection_IndexedDataMap::ChangeFromKey");
  }

  const TheItemType* Seek(const TheKeyType& theKey1) const
  {
    return const_cast<NCollection_IndexedDataMap*>(this)->ChangeSeek(theKey1);
  }

  TheItemType* ChangeSeek(const TheKeyType& theKey1)
  {
    IndexedDataMapNode* aNode;
    if (lookup(theKey1, aNode))
    {
      return &aNode->ChangeValue();
    }
    return nullptr;
  }

  bool FindFromKey(const TheKeyType& theKey1, TheItemType& theValue) const
  {
    IndexedDataMapNode* aNode;
    if (lookup(theKey1, aNode))
    {
      theValue = aNode->Value();
      return true;
    }
    return false;
  }

  void Clear(const bool doReleaseMemory = false)
  {
    Destroy(IndexedDataMapNode::delNode, doReleaseMemory);
  }

  void Clear(const occ::handle<NCollection_BaseAllocator>& theAllocator)
  {
    Clear(theAllocator != this->myAllocator);
    this->myAllocator =
      (!theAllocator.IsNull() ? theAllocator : NCollection_BaseAllocator::CommonBaseAllocator());
  }

  ~NCollection_IndexedDataMap() override { Clear(true); }

  int Size() const noexcept { return Extent(); }

protected:
  bool lookup(const TheKeyType& theKey, IndexedDataMapNode*& theNode, size_t& theHash) const
  {
    theHash = HashCode(theKey, NbBuckets());
    if (IsEmpty())
      return false;
    for (theNode = (IndexedDataMapNode*)myData1[theHash]; theNode;
         theNode = (IndexedDataMapNode*)theNode->Next())
    {
      if (IsEqual(theNode->Key1(), theKey))
        return true;
    }
    return false;
  }

  bool lookup(const TheKeyType& theKey, IndexedDataMapNode*& theNode) const
  {
    if (IsEmpty())
      return false;
    for (theNode = (IndexedDataMapNode*)myData1[HashCode(theKey, NbBuckets())]; theNode;
         theNode = (IndexedDataMapNode*)theNode->Next())
    {
      if (IsEqual(theNode->Key1(), theKey))
      {
        return true;
      }
    }
    return false;
  }

  bool IsEqual(const TheKeyType& theKey1, const TheKeyType& theKey2) const
  {
    return myHasher(theKey1, theKey2);
  }

  size_t HashCode(const TheKeyType& theKey, const int theUpperBound) const
  {
    return myHasher(theKey) % theUpperBound + 1;
  }

protected:
  Hasher myHasher;
};
