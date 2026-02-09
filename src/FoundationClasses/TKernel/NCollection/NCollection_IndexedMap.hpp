#pragma once

#include <NCollection_BaseMap.hpp>
#include <NCollection_TListNode.hpp>
#include <NCollection_StlIterator.hpp>
#include <Standard_NoSuchObject.hpp>

#include <NCollection_DefaultHasher.hpp>

#include <Standard_OutOfRange.hpp>

template <class TheKeyType, class Hasher = NCollection_DefaultHasher<TheKeyType>>
class NCollection_IndexedMap : public NCollection_BaseMap
{
public:
  typedef TheKeyType key_type;

protected:
  class IndexedMapNode : public NCollection_TListNode<TheKeyType>
  {
  public:
    IndexedMapNode(const TheKeyType& theKey1, const int theIndex, NCollection_ListNode* theNext1)
        : NCollection_TListNode<TheKeyType>(theKey1, theNext1),
          myIndex(theIndex)
    {
    }

    IndexedMapNode(TheKeyType&& theKey1, const int theIndex, NCollection_ListNode* theNext1)
        : NCollection_TListNode<TheKeyType>(std::forward<TheKeyType>(theKey1), theNext1),
          myIndex(theIndex)
    {
    }

    TheKeyType& Key1() noexcept { return this->ChangeValue(); }

    int& Index() noexcept { return myIndex; }

    static void delNode(NCollection_ListNode*                   theNode,
                        occ::handle<NCollection_BaseAllocator>& theAl) noexcept
    {
      ((IndexedMapNode*)theNode)->~IndexedMapNode();
      theAl->Free(theNode);
    }

  private:
    int myIndex;
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

    Iterator(const NCollection_IndexedMap& theMap)
        : myMap((NCollection_IndexedMap*)&theMap),
          myIndex(1)
    {
    }

    bool More() const noexcept { return (myMap != nullptr) && (myIndex <= myMap->Extent()); }

    void Next() noexcept { myIndex++; }

    const TheKeyType& Value() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_IndexedMap::Iterator::Value");
      return myMap->FindKey(myIndex);
    }

    bool IsEqual(const Iterator& theOther) const noexcept
    {
      return myMap == theOther.myMap && myIndex == theOther.myIndex;
    }

  private:
    NCollection_IndexedMap* myMap;
    int                     myIndex;
  };

  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheKeyType, true>
    const_iterator;

  const_iterator cbegin() const noexcept { return Iterator(*this); }

  const_iterator cend() const noexcept { return Iterator(); }

public:
  NCollection_IndexedMap()
      : NCollection_BaseMap(1, true, occ::handle<NCollection_BaseAllocator>())
  {
  }

  explicit NCollection_IndexedMap(
    const int                                     theNbBuckets,
    const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
      : NCollection_BaseMap(theNbBuckets, true, theAllocator)
  {
  }

  NCollection_IndexedMap(const NCollection_IndexedMap& theOther)
      : NCollection_BaseMap(theOther.NbBuckets(), true, theOther.myAllocator)
  {
    *this = theOther;
  }

  NCollection_IndexedMap(NCollection_IndexedMap&& theOther) noexcept
      : NCollection_BaseMap(std::forward<NCollection_BaseMap>(theOther))
  {
  }

  void Exchange(NCollection_IndexedMap& theOther) noexcept { this->exchangeMapsData(theOther); }

  NCollection_IndexedMap& Assign(const NCollection_IndexedMap& theOther)
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
        const TheKeyType& aKey1 = theOther.FindKey(anIndexIter);
        const size_t      iK1   = HashCode(aKey1, NbBuckets());
        IndexedMapNode*   pNode =
          new (this->myAllocator) IndexedMapNode(aKey1, anIndexIter, myData1[iK1]);
        myData1[iK1]             = pNode;
        myData2[anIndexIter - 1] = pNode;
        Increment();
      }
    }
    return *this;
  }

  NCollection_IndexedMap& operator=(const NCollection_IndexedMap& theOther)
  {
    return Assign(theOther);
  }

  NCollection_IndexedMap& operator=(NCollection_IndexedMap&& theOther) noexcept
  {
    if (this == &theOther)
      return *this;
    exchangeMapsData(theOther);
    return *this;
  }

  void ReSize(const int theExtent)
  {
    NCollection_ListNode** ppNewData1 = nullptr;
    NCollection_ListNode** ppNewData2 = nullptr;
    int                    newBuck;
    if (BeginResize(theExtent, newBuck, ppNewData1, ppNewData2))
    {
      if (myData1)
      {
        for (int aBucketIter = 0; aBucketIter <= NbBuckets(); ++aBucketIter)
        {
          if (myData1[aBucketIter])
          {
            IndexedMapNode* p = (IndexedMapNode*)myData1[aBucketIter];
            while (p)
            {
              const size_t    iK1 = HashCode(p->Key1(), newBuck);
              IndexedMapNode* q   = (IndexedMapNode*)p->Next();
              p->Next()           = ppNewData1[iK1];
              ppNewData1[iK1]     = p;
              p                   = q;
            }
          }
        }
      }
      EndResize(theExtent,
                newBuck,
                ppNewData1,
                (NCollection_ListNode**)
                  Standard::Reallocate(myData2, (newBuck + 1) * sizeof(NCollection_ListNode*)));
    }
  }

  int Add(const TheKeyType& theKey1)
  {
    if (Resizable())
    {
      ReSize(Extent());
    }
    IndexedMapNode* aNode;
    size_t          aHash;
    if (lookup(theKey1, aNode, aHash))
    {
      return aNode->Index();
    }
    const int aNewIndex = Increment();
    aNode          = new (this->myAllocator) IndexedMapNode(theKey1, aNewIndex, myData1[aHash]);
    myData1[aHash] = aNode;
    myData2[aNewIndex - 1] = aNode;
    return aNewIndex;
  }

  int Add(TheKeyType&& theKey1)
  {
    if (Resizable())
    {
      ReSize(Extent());
    }
    size_t          aHash;
    IndexedMapNode* aNode;
    if (lookup(theKey1, aNode, aHash))
    {
      return aNode->Index();
    }
    const int aNewIndex = Increment();
    aNode               = new (this->myAllocator)
      IndexedMapNode(std::forward<TheKeyType>(theKey1), aNewIndex, myData1[aHash]);
    myData1[aHash]         = aNode;
    myData2[aNewIndex - 1] = aNode;
    return aNewIndex;
  }

  bool Contains(const TheKeyType& theKey1) const
  {
    IndexedMapNode* p;
    return lookup(theKey1, p);
  }

  void Substitute(const int theIndex, const TheKeyType& theKey1)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > Extent(),
                                 "NCollection_IndexedMap::Substitute : "
                                 "Index is out of range");

    IndexedMapNode* aNode;
    size_t          aHash;
    if (lookup(theKey1, aNode, aHash))
    {
      if (aNode->Index() != theIndex)
      {
        throw Standard_DomainError("NCollection_IndexedMap::Substitute : "
                                   "Attempt to substitute existing key");
      }
      aNode->Key1() = theKey1;
      return;
    }

    aNode = (IndexedMapNode*)myData2[theIndex - 1];

    const size_t    iK = HashCode(aNode->Key1(), NbBuckets());
    IndexedMapNode* q  = (IndexedMapNode*)myData1[iK];
    if (q == aNode)
      myData1[iK] = (IndexedMapNode*)aNode->Next();
    else
    {
      while (q->Next() != aNode)
        q = (IndexedMapNode*)q->Next();
      q->Next() = aNode->Next();
    }

    aNode->Key1()  = theKey1;
    aNode->Next()  = myData1[aHash];
    myData1[aHash] = aNode;
  }

  void Swap(const int theIndex1, const int theIndex2)
  {
    Standard_OutOfRange_Raise_if(theIndex1 < 1 || theIndex1 > Extent() || theIndex2 < 1
                                   || theIndex2 > Extent(),
                                 "NCollection_IndexedMap::Swap");

    if (theIndex1 == theIndex2)
    {
      return;
    }

    IndexedMapNode* aP1 = (IndexedMapNode*)myData2[theIndex1 - 1];
    IndexedMapNode* aP2 = (IndexedMapNode*)myData2[theIndex2 - 1];
    std::swap(aP1->Index(), aP2->Index());
    myData2[theIndex2 - 1] = aP1;
    myData2[theIndex1 - 1] = aP2;
  }

  void RemoveLast()
  {
    const int aLastIndex = Extent();
    Standard_OutOfRange_Raise_if(aLastIndex == 0, "NCollection_IndexedMap::RemoveLast");

    IndexedMapNode* p       = (IndexedMapNode*)myData2[aLastIndex - 1];
    myData2[aLastIndex - 1] = nullptr;

    const size_t    iK1 = HashCode(p->Key1(), NbBuckets());
    IndexedMapNode* q   = (IndexedMapNode*)myData1[iK1];
    if (q == p)
      myData1[iK1] = (IndexedMapNode*)p->Next();
    else
    {
      while (q->Next() != p)
        q = (IndexedMapNode*)q->Next();
      q->Next() = p->Next();
    }
    p->~IndexedMapNode();
    this->myAllocator->Free(p);
    Decrement();
  }

  void RemoveFromIndex(const int theIndex)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > Extent(),
                                 "NCollection_IndexedMap::RemoveFromIndex");
    const int aLastInd = Extent();
    if (theIndex != aLastInd)
    {
      Swap(theIndex, aLastInd);
    }
    RemoveLast();
  }

  bool RemoveKey(const TheKeyType& theKey1)
  {
    int anIndToRemove = FindIndex(theKey1);
    if (anIndToRemove < 1)
    {
      return false;
    }

    RemoveFromIndex(anIndToRemove);
    return true;
  }

  const TheKeyType& FindKey(const int theIndex) const
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > Extent(),
                                 "NCollection_IndexedMap::FindKey");
    IndexedMapNode* pNode2 = (IndexedMapNode*)myData2[theIndex - 1];
    return pNode2->Key1();
  }

  const TheKeyType& operator()(const int theIndex) const { return FindKey(theIndex); }

  int FindIndex(const TheKeyType& theKey1) const
  {
    IndexedMapNode* aNode;
    if (lookup(theKey1, aNode))
    {
      return aNode->Index();
    }
    return 0;
  }

  void Clear(const bool doReleaseMemory = false)
  {
    Destroy(IndexedMapNode::delNode, doReleaseMemory);
  }

  void Clear(const occ::handle<NCollection_BaseAllocator>& theAllocator)
  {
    Clear(theAllocator != this->myAllocator);
    this->myAllocator =
      (!theAllocator.IsNull() ? theAllocator : NCollection_BaseAllocator::CommonBaseAllocator());
  }

  ~NCollection_IndexedMap() override { Clear(true); }

  int Size() const noexcept { return Extent(); }

protected:
  bool lookup(const TheKeyType& theKey, IndexedMapNode*& theNode, size_t& theHash) const
  {
    theHash = HashCode(theKey, NbBuckets());
    if (IsEmpty())
      return false;
    for (theNode = (IndexedMapNode*)myData1[theHash]; theNode;
         theNode = (IndexedMapNode*)theNode->Next())
    {
      if (IsEqual(theNode->Key1(), theKey))
        return true;
    }
    return false;
  }

  bool lookup(const TheKeyType& theKey, IndexedMapNode*& theNode) const
  {
    if (IsEmpty())
      return false;
    for (theNode = (IndexedMapNode*)myData1[HashCode(theKey, NbBuckets())]; theNode;
         theNode = (IndexedMapNode*)theNode->Next())
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
