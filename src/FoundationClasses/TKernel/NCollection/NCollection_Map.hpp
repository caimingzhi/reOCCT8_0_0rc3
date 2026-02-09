#pragma once

#include <NCollection_MapAlgo.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_DefaultHasher.hpp>
#include <NCollection_StlIterator.hpp>
#include <NCollection_TListNode.hpp>
#include <Standard_NoSuchObject.hpp>

#include <utility>

template <class TheKeyType, class Hasher = NCollection_DefaultHasher<TheKeyType>>
class NCollection_Map : public NCollection_BaseMap
{
public:
  typedef TheKeyType key_type;
  typedef Hasher     hasher;

public:
  class MapNode : public NCollection_TListNode<TheKeyType>
  {
  public:
    MapNode(const TheKeyType& theKey, NCollection_ListNode* theNext)
        : NCollection_TListNode<TheKeyType>(theKey, theNext)
    {
    }

    MapNode(TheKeyType&& theKey, NCollection_ListNode* theNext)
        : NCollection_TListNode<TheKeyType>(std::forward<TheKeyType>(theKey), theNext)
    {
    }

    const TheKeyType& Key() noexcept { return this->Value(); }
  };

public:
  class Iterator : public NCollection_BaseMap::Iterator
  {
  public:
    Iterator()
        : NCollection_BaseMap::Iterator()
    {
    }

    Iterator(const NCollection_Map& theMap)
        : NCollection_BaseMap::Iterator(theMap)
    {
    }

    bool More() const noexcept { return PMore(); }

    void Next() noexcept { PNext(); }

    const TheKeyType& Value() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_Map::Iterator::Value");
      return ((MapNode*)myNode)->Value();
    }

    const TheKeyType& Key() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_Map::Iterator::Key");
      return ((MapNode*)myNode)->Value();
    }
  };

  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheKeyType, true>
    const_iterator;

  const_iterator cbegin() const noexcept { return Iterator(*this); }

  const_iterator cend() const noexcept { return Iterator(); }

public:
  NCollection_Map()
      : NCollection_BaseMap(1, true, occ::handle<NCollection_BaseAllocator>())
  {
  }

  explicit NCollection_Map(const int                                     theNbBuckets,
                           const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
      : NCollection_BaseMap(theNbBuckets, true, theAllocator)
  {
  }

  NCollection_Map(const NCollection_Map& theOther)
      : NCollection_BaseMap(theOther.NbBuckets(), true, theOther.myAllocator)
  {
    const int anExt = theOther.Extent();
    if (anExt <= 0)
      return;
    ReSize(anExt - 1);
    for (Iterator anIter(theOther); anIter.More(); anIter.Next())
      Add(anIter.Key());
  }

  NCollection_Map(NCollection_Map&& theOther) noexcept
      : NCollection_BaseMap(std::forward<NCollection_BaseMap>(theOther))
  {
  }

  void Exchange(NCollection_Map& theOther) noexcept { this->exchangeMapsData(theOther); }

  NCollection_Map& Assign(const NCollection_Map& theOther)
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
        Add(anIter.Key());
    }
    return *this;
  }

  NCollection_Map& operator=(const NCollection_Map& theOther) { return Assign(theOther); }

  NCollection_Map& operator=(NCollection_Map&& theOther) noexcept
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
        MapNode** olddata = (MapNode**)myData1;
        MapNode * p, *q;
        for (int i = 0; i <= NbBuckets(); i++)
        {
          if (olddata[i])
          {
            p = olddata[i];
            while (p)
            {
              const size_t k = HashCode(p->Key(), newBuck);
              q              = (MapNode*)p->Next();
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

  bool Add(const TheKeyType& theKey)
  {
    if (Resizable())
      ReSize(Extent());
    MapNode* aNode;
    size_t   aHash;
    if (lookup(theKey, aNode, aHash))
    {
      return false;
    }
    MapNode** data = (MapNode**)myData1;
    data[aHash]    = new (this->myAllocator) MapNode(theKey, data[aHash]);
    Increment();
    return true;
  }

  bool Add(TheKeyType&& theKey)
  {
    if (Resizable())
      ReSize(Extent());
    MapNode* aNode;
    size_t   aHash;
    if (lookup(theKey, aNode, aHash))
    {
      return false;
    }
    MapNode** data = (MapNode**)myData1;
    data[aHash]    = new (this->myAllocator) MapNode(std::forward<TheKeyType>(theKey), data[aHash]);
    Increment();
    return true;
  }

  const TheKeyType& Added(const TheKeyType& theKey)
  {
    if (Resizable())
      ReSize(Extent());
    MapNode* aNode;
    size_t   aHash;
    if (lookup(theKey, aNode, aHash))
    {
      return aNode->Key();
    }
    MapNode** data = (MapNode**)myData1;
    data[aHash]    = new (this->myAllocator) MapNode(theKey, data[aHash]);
    Increment();
    return data[aHash]->Key();
  }

  const TheKeyType& Added(TheKeyType&& theKey)
  {
    if (Resizable())
      ReSize(Extent());
    MapNode* aNode;
    size_t   aHash;
    if (lookup(theKey, aNode, aHash))
    {
      return aNode->Key();
    }
    MapNode** data = (MapNode**)myData1;
    data[aHash]    = new (this->myAllocator) MapNode(std::forward<TheKeyType>(theKey), data[aHash]);
    Increment();
    return data[aHash]->Key();
  }

  bool Contains(const TheKeyType& theKey) const
  {
    MapNode* p;
    return lookup(theKey, p);
  }

  bool Remove(const TheKeyType& K)
  {
    if (IsEmpty())
      return false;
    MapNode**    data = (MapNode**)myData1;
    const size_t k    = HashCode(K, NbBuckets());
    MapNode*     p    = data[k];
    MapNode*     q    = nullptr;
    while (p)
    {
      if (IsEqual(p->Key(), K))
      {
        Decrement();
        if (q)
          q->Next() = p->Next();
        else
          data[k] = (MapNode*)p->Next();
        p->~MapNode();
        this->myAllocator->Free(p);
        return true;
      }
      q = p;
      p = (MapNode*)p->Next();
    }
    return false;
  }

  void Clear(const bool doReleaseMemory = false) { Destroy(MapNode::delNode, doReleaseMemory); }

  void Clear(const occ::handle<NCollection_BaseAllocator>& theAllocator)
  {
    Clear(theAllocator != this->myAllocator);
    this->myAllocator =
      (!theAllocator.IsNull() ? theAllocator : NCollection_BaseAllocator::CommonBaseAllocator());
  }

  ~NCollection_Map() override { Clear(true); }

  int Size() const noexcept { return Extent(); }

public:
  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  bool IsEqual(const NCollection_Map& theOther) const
  {
    return NCollection_MapAlgo::IsEqual<NCollection_Map>(*this, theOther);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  bool Contains(const NCollection_Map& theOther) const
  {
    return NCollection_MapAlgo::Contains<NCollection_Map>(*this, theOther);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  void Union(const NCollection_Map& theLeft, const NCollection_Map& theRight)
  {
    NCollection_MapAlgo::Union<NCollection_Map>(*this, theLeft, theRight);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  bool Unite(const NCollection_Map& theOther)
  {
    return NCollection_MapAlgo::Unite<NCollection_Map>(*this, theOther);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  bool HasIntersection(const NCollection_Map& theMap) const
  {
    return NCollection_MapAlgo::HasIntersection<NCollection_Map>(*this, theMap);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  void Intersection(const NCollection_Map& theLeft, const NCollection_Map& theRight)
  {
    NCollection_MapAlgo::Intersection<NCollection_Map>(*this, theLeft, theRight);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  bool Intersect(const NCollection_Map& theOther)
  {
    return NCollection_MapAlgo::Intersect<NCollection_Map>(*this, theOther);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  void Subtraction(const NCollection_Map& theLeft, const NCollection_Map& theRight)
  {
    NCollection_MapAlgo::Subtraction<NCollection_Map>(*this, theLeft, theRight);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  bool Subtract(const NCollection_Map& theOther)
  {
    return NCollection_MapAlgo::Subtract<NCollection_Map>(*this, theOther);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  void Difference(const NCollection_Map& theLeft, const NCollection_Map& theRight)
  {
    NCollection_MapAlgo::Difference<NCollection_Map>(*this, theLeft, theRight);
  }

  Standard_DEPRECATED("This method will be removed right after 7.9. release. Use methods from "
                      "NCollection_MapAlgo.hpp instead.")

  bool Differ(const NCollection_Map& theOther)
  {
    return NCollection_MapAlgo::Differ<NCollection_Map>(*this, theOther);
  }

protected:
  bool lookup(const TheKeyType& theKey, MapNode*& theNode, size_t& theHash) const
  {
    theHash = HashCode(theKey, NbBuckets());
    if (IsEmpty())
      return false;
    for (theNode = (MapNode*)myData1[theHash]; theNode; theNode = (MapNode*)theNode->Next())
    {
      if (IsEqual(theNode->Key(), theKey))
        return true;
    }
    return false;
  }

  bool lookup(const TheKeyType& theKey, MapNode*& theNode) const
  {
    if (IsEmpty())
      return false;
    for (theNode = (MapNode*)myData1[HashCode(theKey, NbBuckets())]; theNode;
         theNode = (MapNode*)theNode->Next())
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

protected:
  Hasher myHasher;
};
