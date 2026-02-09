#pragma once

#include <Standard.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <NCollection_ListNode.hpp>

typedef void (*NCollection_DelMapNode)(NCollection_ListNode*,
                                       occ::handle<NCollection_BaseAllocator>& theAl);

class NCollection_BaseMap
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

public:
  class Iterator
  {
  protected:
    Iterator() noexcept
        : myNbBuckets(0),
          myBuckets(nullptr),
          myBucket(0),
          myNode(nullptr)
    {
    }

    Iterator(const NCollection_BaseMap& theMap) noexcept
        : myNbBuckets(theMap.myNbBuckets),
          myBuckets(theMap.myData1),
          myBucket(-1),
          myNode(nullptr)
    {
      if (!myBuckets)
        myNbBuckets = -1;
      else
        do
        {
          myBucket++;
          if (myBucket > myNbBuckets)
            return;
          myNode = myBuckets[myBucket];
        } while (!myNode);
    }

  public:
    void Initialize(const NCollection_BaseMap& theMap) noexcept
    {
      myNbBuckets = theMap.myNbBuckets;
      myBuckets   = theMap.myData1;
      myBucket    = -1;
      myNode      = nullptr;
      if (!myBuckets)
        myNbBuckets = -1;
      PNext();
    }

    void Reset() noexcept
    {
      myBucket = -1;
      myNode   = nullptr;
      PNext();
    }

    bool IsEqual(const Iterator& theOther) const noexcept
    {
      return myBucket == theOther.myBucket && myNode == theOther.myNode;
    }

  protected:
    bool PMore() const noexcept { return (myNode != nullptr); }

    void PNext() noexcept
    {
      if (!myBuckets)
        return;
      if (myNode)
      {
        myNode = myNode->Next();
        if (myNode)
          return;
      }
      while (!myNode)
      {
        myBucket++;
        if (myBucket > myNbBuckets)
          return;
        myNode = myBuckets[myBucket];
      }
    }

  protected:
    int                    myNbBuckets;
    NCollection_ListNode** myBuckets;
    int                    myBucket;
    NCollection_ListNode*  myNode;
  };

public:
  int NbBuckets() const noexcept { return myNbBuckets; }

  int Extent() const noexcept { return mySize; }

  bool IsEmpty() const noexcept { return mySize == 0; }

  Standard_EXPORT void Statistics(Standard_OStream& S) const;

  const occ::handle<NCollection_BaseAllocator>& Allocator() const noexcept { return myAllocator; }

protected:
  NCollection_BaseMap(const int                                     NbBuckets,
                      const bool                                    single,
                      const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : myAllocator(theAllocator.IsNull() ? NCollection_BaseAllocator::CommonBaseAllocator()
                                          : theAllocator),
        myData1(nullptr),
        myData2(nullptr),
        myNbBuckets(NbBuckets),
        mySize(0),
        isDouble(!single)
  {
  }

  NCollection_BaseMap(NCollection_BaseMap&& theOther) noexcept
      : myAllocator(theOther.myAllocator),
        myData1(theOther.myData1),
        myData2(theOther.myData2),
        myNbBuckets(theOther.myNbBuckets),
        mySize(theOther.mySize),
        isDouble(theOther.isDouble)
  {
    theOther.myData1     = nullptr;
    theOther.myData2     = nullptr;
    theOther.mySize      = 0;
    theOther.myNbBuckets = 0;
  }

  virtual ~NCollection_BaseMap() = default;

  Standard_EXPORT bool BeginResize(const int               NbBuckets,
                                   int&                    NewBuckets,
                                   NCollection_ListNode**& data1,
                                   NCollection_ListNode**& data2) const;

  Standard_EXPORT void EndResize(const int              NbBuckets,
                                 const int              NewBuckets,
                                 NCollection_ListNode** data1,
                                 NCollection_ListNode** data2) noexcept;

  bool Resizable() const noexcept { return IsEmpty() || (mySize > myNbBuckets); }

  int Increment() noexcept { return ++mySize; }

  int Decrement() noexcept { return --mySize; }

  Standard_EXPORT void Destroy(NCollection_DelMapNode fDel, bool doReleaseMemory = true);

  Standard_EXPORT int NextPrimeForMap(const int N) const noexcept;

  void exchangeMapsData(NCollection_BaseMap& theOther) noexcept
  {
    std::swap(myAllocator, theOther.myAllocator);
    std::swap(myData1, theOther.myData1);
    std::swap(myData2, theOther.myData2);
    std::swap(myNbBuckets, theOther.myNbBuckets);
    std::swap(mySize, theOther.mySize);
  }

  NCollection_BaseMap& operator=(NCollection_BaseMap&&) noexcept = delete;

  NCollection_BaseMap(const NCollection_BaseMap&) = delete;

  NCollection_BaseMap& operator=(const NCollection_BaseMap&) = delete;

protected:
  occ::handle<NCollection_BaseAllocator> myAllocator;
  NCollection_ListNode**                 myData1;
  NCollection_ListNode**                 myData2;

private:
  int        myNbBuckets;
  int        mySize;
  const bool isDouble;

  friend class Iterator;
};
