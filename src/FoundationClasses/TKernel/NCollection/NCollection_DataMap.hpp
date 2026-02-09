#pragma once

#include <NCollection_BaseMap.hpp>
#include <NCollection_TListNode.hpp>
#include <NCollection_StlIterator.hpp>
#include <NCollection_DefaultHasher.hpp>

#include <Standard_TypeMismatch.hpp>
#include <Standard_NoSuchObject.hpp>
#include <utility>

#include <Message.hpp>

template <class TheKeyType, class TheItemType, class Hasher = NCollection_DefaultHasher<TheKeyType>>
class NCollection_DataMap : public NCollection_BaseMap
{
public:
  typedef TheKeyType key_type;

  typedef TheItemType value_type;

public:
  class DataMapNode : public NCollection_TListNode<TheItemType>
  {
  public:
    DataMapNode(const TheKeyType& theKey, const TheItemType& theItem, NCollection_ListNode* theNext)
        : NCollection_TListNode<TheItemType>(theItem, theNext),
          myKey(theKey)
    {
    }

    DataMapNode(const TheKeyType& theKey, TheItemType&& theItem, NCollection_ListNode* theNext)
        : NCollection_TListNode<TheItemType>(std::forward<TheItemType>(theItem), theNext),
          myKey(theKey)
    {
    }

    DataMapNode(TheKeyType&& theKey, const TheItemType& theItem, NCollection_ListNode* theNext)
        : NCollection_TListNode<TheItemType>(theItem, theNext),
          myKey(std::forward<TheKeyType>(theKey))
    {
    }

    DataMapNode(TheKeyType&& theKey, TheItemType&& theItem, NCollection_ListNode* theNext)
        : NCollection_TListNode<TheItemType>(std::forward<TheItemType>(theItem), theNext),
          myKey(std::forward<TheKeyType>(theKey))
    {
    }

    const TheKeyType& Key() const noexcept { return myKey; }

    static void delNode(NCollection_ListNode*                   theNode,
                        occ::handle<NCollection_BaseAllocator>& theAl) noexcept
    {
      ((DataMapNode*)theNode)->~DataMapNode();
      theAl->Free(theNode);
    }

  private:
    TheKeyType myKey;
  };

public:
  class Iterator : public NCollection_BaseMap::Iterator
  {
  public:
    Iterator()
        : NCollection_BaseMap::Iterator()
    {
    }

    Iterator(const NCollection_DataMap& theMap)
        : NCollection_BaseMap::Iterator(theMap)
    {
    }

    bool More() const noexcept { return PMore(); }

    void Next() noexcept { PNext(); }

    const TheItemType& Value() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_DataMap::Iterator::Value");
      return ((DataMapNode*)myNode)->Value();
    }

    TheItemType& ChangeValue() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_DataMap::Iterator::ChangeValue");
      return ((DataMapNode*)myNode)->ChangeValue();
    }

    const TheKeyType& Key() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_DataMap::Iterator::Key");
      return ((DataMapNode*)myNode)->Key();
    }
  };

  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheItemType, false> iterator;

  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheItemType, true>
    const_iterator;

  iterator begin() const noexcept { return Iterator(*this); }

  iterator end() const noexcept { return Iterator(); }

  const_iterator cbegin() const noexcept { return Iterator(*this); }

  const_iterator cend() const noexcept { return Iterator(); }

public:
  NCollection_DataMap()
      : NCollection_BaseMap(1, true, occ::handle<NCollection_BaseAllocator>())
  {
  }

  explicit NCollection_DataMap(const int                                     theNbBuckets,
                               const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
      : NCollection_BaseMap(theNbBuckets, true, theAllocator)
  {
  }

  NCollection_DataMap(const NCollection_DataMap& theOther)
      : NCollection_BaseMap(theOther.NbBuckets(), true, theOther.myAllocator)
  {
    const int anExt = theOther.Extent();
    if (anExt <= 0)
      return;
    ReSize(anExt - 1);
    for (Iterator anIter(theOther); anIter.More(); anIter.Next())
      Bind(anIter.Key(), anIter.Value());
  }

  NCollection_DataMap(NCollection_DataMap&& theOther) noexcept
      : NCollection_BaseMap(std::forward<NCollection_BaseMap>(theOther))
  {
  }

  void Exchange(NCollection_DataMap& theOther) noexcept { this->exchangeMapsData(theOther); }

  NCollection_DataMap& Assign(const NCollection_DataMap& theOther)
  {
    if (this == &theOther)
      return *this;

    Clear();
    int anExt = theOther.Extent();
    if (anExt)
    {
      ReSize(anExt - 1);
      Iterator anIter(theOther);
      for (; anIter.More(); anIter.Next())
        Bind(anIter.Key(), anIter.Value());
    }
    return *this;
  }

  NCollection_DataMap& operator=(const NCollection_DataMap& theOther) { return Assign(theOther); }

  NCollection_DataMap& operator=(NCollection_DataMap&& theOther) noexcept
  {
    if (this == &theOther)
      return *this;
    exchangeMapsData(theOther);
    return *this;
  }

  void ReSize(const int N)
  {
    NCollection_ListNode** newdata = nullptr;
    NCollection_ListNode** dummy   = nullptr;
    int                    newBuck;
    if (BeginResize(N, newBuck, newdata, dummy))
    {
      if (myData1)
      {
        DataMapNode** olddata = (DataMapNode**)myData1;
        DataMapNode * p, *q;
        for (int i = 0; i <= NbBuckets(); i++)
        {
          if (olddata[i])
          {
            p = olddata[i];
            while (p)
            {
              const size_t k = HashCode(p->Key(), newBuck);
              q              = (DataMapNode*)p->Next();
              p->Next()      = newdata[k];
              newdata[k]     = p;
              p              = q;
            }
          }
        }
      }
      EndResize(N, newBuck, newdata, dummy);
    }
  }

  bool Bind(const TheKeyType& theKey, const TheItemType& theItem)
  {
    if (Resizable())
      ReSize(Extent());
    size_t       aHash;
    DataMapNode* aNode;
    if (lookup(theKey, aNode, aHash))
    {
      aNode->ChangeValue() = theItem;
      return false;
    }
    DataMapNode** data = (DataMapNode**)myData1;
    data[aHash]        = new (this->myAllocator) DataMapNode(theKey, theItem, data[aHash]);
    Increment();
    return true;
  }

  bool Bind(TheKeyType&& theKey, const TheItemType& theItem)
  {
    if (Resizable())
      ReSize(Extent());
    size_t       aHash;
    DataMapNode* aNode;
    if (lookup(theKey, aNode, aHash))
    {
      aNode->ChangeValue() = theItem;
      return false;
    }
    DataMapNode** data = (DataMapNode**)myData1;
    data[aHash] =
      new (this->myAllocator) DataMapNode(std::forward<TheKeyType>(theKey), theItem, data[aHash]);
    Increment();
    return true;
  }

  bool Bind(const TheKeyType& theKey, TheItemType&& theItem)
  {
    if (Resizable())
      ReSize(Extent());
    size_t       aHash;
    DataMapNode* aNode;
    if (lookup(theKey, aNode, aHash))
    {
      aNode->ChangeValue() = std::forward<TheItemType>(theItem);
      return false;
    }
    DataMapNode** data = (DataMapNode**)myData1;
    data[aHash] =
      new (this->myAllocator) DataMapNode(theKey, std::forward<TheItemType>(theItem), data[aHash]);
    Increment();
    return true;
  }

  bool Bind(TheKeyType&& theKey, TheItemType&& theItem)
  {
    if (Resizable())
      ReSize(Extent());
    size_t       aHash;
    DataMapNode* aNode;
    if (lookup(theKey, aNode, aHash))
    {
      aNode->ChangeValue() = theItem;
      return false;
    }
    DataMapNode** data = (DataMapNode**)myData1;
    data[aHash]        = new (this->myAllocator) DataMapNode(std::forward<TheKeyType>(theKey),
                                                      std::forward<TheItemType>(theItem),
                                                      data[aHash]);
    Increment();
    return true;
  }

  TheItemType* Bound(const TheKeyType& theKey, const TheItemType& theItem)
  {
    if (Resizable())
      ReSize(Extent());
    size_t       aHash;
    DataMapNode* aNode;
    if (lookup(theKey, aNode, aHash))
    {
      aNode->ChangeValue() = theItem;
      return &aNode->ChangeValue();
    }
    DataMapNode** data = (DataMapNode**)myData1;
    data[aHash]        = new (this->myAllocator) DataMapNode(theKey, theItem, data[aHash]);
    Increment();
    return &data[aHash]->ChangeValue();
  }

  TheItemType* Bound(TheKeyType&& theKey, const TheItemType& theItem)
  {
    if (Resizable())
      ReSize(Extent());
    size_t       aHash;
    DataMapNode* aNode;
    if (lookup(theKey, aNode, aHash))
    {
      aNode->ChangeValue() = theItem;
      return &aNode->ChangeValue();
    }
    DataMapNode** data = (DataMapNode**)myData1;
    data[aHash] =
      new (this->myAllocator) DataMapNode(std::forward<TheKeyType>(theKey), theItem, data[aHash]);
    Increment();
    return &data[aHash]->ChangeValue();
  }

  TheItemType* Bound(const TheKeyType& theKey, TheItemType&& theItem)
  {
    if (Resizable())
      ReSize(Extent());
    size_t       aHash;
    DataMapNode* aNode;
    if (lookup(theKey, aNode, aHash))
    {
      aNode->ChangeValue() = std::forward<TheItemType>(theItem);
      return &aNode->ChangeValue();
    }
    DataMapNode** data = (DataMapNode**)myData1;
    data[aHash] =
      new (this->myAllocator) DataMapNode(theKey, std::forward<TheItemType>(theItem), data[aHash]);
    Increment();
    return &data[aHash]->ChangeValue();
  }

  TheItemType* Bound(TheKeyType&& theKey, TheItemType&& theItem)
  {
    if (Resizable())
      ReSize(Extent());
    size_t       aHash;
    DataMapNode* aNode;
    if (lookup(theKey, aNode, aHash))
    {
      aNode->ChangeValue() = std::forward<TheItemType>(theItem);
      return &aNode->ChangeValue();
    }
    DataMapNode** data = (DataMapNode**)myData1;
    data[aHash]        = new (this->myAllocator) DataMapNode(std::forward<TheKeyType>(theKey),
                                                      std::forward<TheItemType>(theItem),
                                                      data[aHash]);
    Increment();
    return &data[aHash]->ChangeValue();
  }

  bool IsBound(const TheKeyType& theKey) const
  {
    DataMapNode* p;
    return lookup(theKey, p);
  }

  bool UnBind(const TheKeyType& theKey)
  {
    if (IsEmpty())
      return false;
    DataMapNode** data = (DataMapNode**)myData1;
    const size_t  k    = HashCode(theKey, NbBuckets());
    DataMapNode*  p    = data[k];
    DataMapNode*  q    = nullptr;
    while (p)
    {
      if (IsEqual(p->Key(), theKey))
      {
        Decrement();
        if (q)
          q->Next() = p->Next();
        else
          data[k] = (DataMapNode*)p->Next();
        p->~DataMapNode();
        this->myAllocator->Free(p);
        return true;
      }
      q = p;
      p = (DataMapNode*)p->Next();
    }
    return false;
  }

  const TheItemType* Seek(const TheKeyType& theKey) const
  {
    DataMapNode* p = nullptr;
    if (!lookup(theKey, p))
      return nullptr;
    return &p->Value();
  }

  const TheItemType& Find(const TheKeyType& theKey) const
  {
    DataMapNode* p = nullptr;
    if (!lookup(theKey, p))
      throw Standard_NoSuchObject("NCollection_DataMap::Find");
    return p->Value();
  }

  bool Find(const TheKeyType& theKey, TheItemType& theValue) const
  {
    DataMapNode* p = nullptr;
    if (!lookup(theKey, p))
      return false;

    theValue = p->Value();
    return true;
  }

  const TheItemType& operator()(const TheKeyType& theKey) const { return Find(theKey); }

  TheItemType* ChangeSeek(const TheKeyType& theKey)
  {
    DataMapNode* p = nullptr;
    if (!lookup(theKey, p))
      return nullptr;
    return &p->ChangeValue();
  }

  TheItemType& ChangeFind(const TheKeyType& theKey)
  {
    DataMapNode* p = nullptr;
    if (!lookup(theKey, p))
      throw Standard_NoSuchObject("NCollection_DataMap::Find");
    return p->ChangeValue();
  }

  TheItemType& operator()(const TheKeyType& theKey) { return ChangeFind(theKey); }

  void Clear(const bool doReleaseMemory = false) { Destroy(DataMapNode::delNode, doReleaseMemory); }

  void Clear(const occ::handle<NCollection_BaseAllocator>& theAllocator)
  {
    Clear(theAllocator != this->myAllocator);
    this->myAllocator =
      (!theAllocator.IsNull() ? theAllocator : NCollection_BaseAllocator::CommonBaseAllocator());
  }

  ~NCollection_DataMap() override { Clear(true); }

  int Size() const noexcept { return Extent(); }

protected:
  bool lookup(const TheKeyType& theKey, DataMapNode*& theNode) const
  {
    if (IsEmpty())
      return false;
    for (theNode = (DataMapNode*)myData1[HashCode(theKey, NbBuckets())]; theNode;
         theNode = (DataMapNode*)theNode->Next())
    {
      if (IsEqual(theNode->Key(), theKey))
        return true;
    }
    return false;
  }

  bool lookup(const TheKeyType& theKey, DataMapNode*& theNode, size_t& theHash) const
  {
    theHash = HashCode(theKey, NbBuckets());
    if (IsEmpty())
      return false;
    for (theNode = (DataMapNode*)myData1[theHash]; theNode; theNode = (DataMapNode*)theNode->Next())
    {
      if (IsEqual(theNode->Key(), theKey))
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

private:
  Hasher myHasher;
};
