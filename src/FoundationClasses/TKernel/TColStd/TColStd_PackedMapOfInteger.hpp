#pragma once

#include <Standard.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Integer.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_OStream.hpp>
#include <Standard_Handle.hpp>

class TColStd_PackedMapOfInteger
{
public:
  DEFINE_STANDARD_ALLOC

private:
  static const unsigned int MASK_LOW = 0x001f;

  static const unsigned int MASK_HIGH = ~MASK_LOW;

  class TColStd_intMapNode
  {
  public:
    TColStd_intMapNode(TColStd_intMapNode* thePtr = nullptr)
        : myNext(thePtr),
          myMask(0),
          myData(0)
    {
    }

    TColStd_intMapNode(int theValue, TColStd_intMapNode*& thePtr)
        : myNext(thePtr),
          myMask((unsigned int)(theValue & MASK_HIGH)),
          myData(1 << (theValue & MASK_LOW))
    {
    }

    TColStd_intMapNode(unsigned int theMask, unsigned int theData, TColStd_intMapNode* thePtr)
        : myNext(thePtr),
          myMask(theMask),
          myData(theData)
    {
    }

    unsigned int Mask() const { return myMask; }

    unsigned int Data() const { return myData; }

    unsigned int& ChangeMask() { return myMask; }

    unsigned int& ChangeData() { return myData; }

    int Key() const { return int(myMask & MASK_HIGH); }

    size_t NbValues() const { return size_t(myMask & MASK_LOW) + 1; }

    bool HasValues() const { return (myData != 0); }

    int HasValue(int theValue) const { return (myData & (1 << (theValue & MASK_LOW))); }

    bool AddValue(int theValue)
    {
      const int aValInt = (1 << (theValue & MASK_LOW));
      if ((myData & aValInt) == 0)
      {
        myData ^= aValInt;
        ++myMask;
        return true;
      }
      return false;
    }

    bool DelValue(int theValue)
    {
      const int aValInt = (1 << (theValue & MASK_LOW));
      if ((myData & aValInt) != 0)
      {
        myData ^= aValInt;
        myMask--;
        return true;
      }
      return false;
    }

    int FindNext(unsigned int& theMask) const;

    TColStd_intMapNode* Next() const { return myNext; }

    void SetNext(TColStd_intMapNode* theNext) { myNext = theNext; }

  public:
    int HashCode(int theUpper) const { return (myMask >> 5) % theUpper + 1; }

    bool IsEqual(int theOther) const { return ((myMask >> 5) == (unsigned)theOther); }

  private:
    TColStd_intMapNode* myNext;
    unsigned int        myMask;
    unsigned int        myData;
  };

public:
  class Iterator
  {
  public:
    Iterator()
        : myBuckets(nullptr),
          myNode(nullptr),
          myNbBuckets(-1),
          myBucket(-1),
          myIntMask(~0U),
          myKey(0)
    {
    }

    Iterator(const TColStd_PackedMapOfInteger& theMap)
        : myBuckets(theMap.myData1),
          myNode(nullptr),
          myNbBuckets(theMap.myData1 != nullptr ? theMap.myNbBuckets : -1),
          myBucket(-1),
          myIntMask(~0U)
    {
      next();
      myKey = myNode != nullptr ? TColStd_intMapNode_findNext(myNode, myIntMask) : 0;
    }

    void Initialize(const TColStd_PackedMapOfInteger& theMap)
    {
      myBuckets   = theMap.myData1;
      myBucket    = -1;
      myNode      = nullptr;
      myNbBuckets = theMap.myData1 != nullptr ? theMap.myNbBuckets : -1;
      next();

      myIntMask = ~0U;
      myKey     = myNode != nullptr ? TColStd_intMapNode_findNext(myNode, myIntMask) : 0;
    }

    void Reset()
    {
      myBucket = -1;
      myNode   = nullptr;
      next();

      myIntMask = ~0U;
      myKey     = myNode != nullptr ? TColStd_intMapNode_findNext(myNode, myIntMask) : 0;
    }

    int Key() const
    {
      Standard_NoSuchObject_Raise_if((myIntMask == ~0U),
                                     "TColStd_MapIteratorOfPackedMapOfInteger::Key");
      return myKey;
    }

    bool More() const { return myNode != nullptr; }

    void Next()
    {
      for (; myNode != nullptr; next())
      {
        myKey = TColStd_intMapNode_findNext(myNode, myIntMask);
        if (myIntMask != ~0u)
        {
          break;
        }
      }
    }

  private:
    void next()
    {
      if (myBuckets == nullptr)
      {
        return;
      }

      if (myNode != nullptr)
      {
        myNode = myNode->Next();
      }

      while (myNode == nullptr)
      {
        ++myBucket;
        if (myBucket > myNbBuckets)
        {
          return;
        }
        myNode = myBuckets[myBucket];
      }
    }

  private:
    TColStd_intMapNode** myBuckets;
    TColStd_intMapNode*  myNode;
    int                  myNbBuckets;
    int                  myBucket;

    unsigned int myIntMask;
    int          myKey;
  };

public:
  TColStd_PackedMapOfInteger(const int theNbBuckets = 1)
      : myData1(nullptr),
        myNbBuckets(theNbBuckets),
        myNbPackedMapNodes(0),
        myExtent(0)
  {
  }

  TColStd_PackedMapOfInteger(const TColStd_PackedMapOfInteger& theOther)
      : myData1(nullptr),
        myNbBuckets(1),
        myNbPackedMapNodes(0),
        myExtent(0)
  {
    Assign(theOther);
  }

  inline TColStd_PackedMapOfInteger& operator=(const TColStd_PackedMapOfInteger& Other)
  {
    return Assign(Other);
  }

  Standard_EXPORT TColStd_PackedMapOfInteger& Assign(const TColStd_PackedMapOfInteger&);
  Standard_EXPORT void                        ReSize(const int NbBuckets);
  Standard_EXPORT void                        Clear();

  ~TColStd_PackedMapOfInteger() { Clear(); }

  Standard_EXPORT bool Add(const int aKey);
  Standard_EXPORT bool Contains(const int aKey) const;
  Standard_EXPORT bool Remove(const int aKey);

  int NbBuckets() const { return myNbBuckets; }

  int Extent() const { return int(myExtent); }

  bool IsEmpty() const { return myNbPackedMapNodes == 0; }

  Standard_EXPORT int GetMinimalMapped() const;

  Standard_EXPORT int GetMaximalMapped() const;

  Standard_EXPORT void Statistics(Standard_OStream& theStream) const;

public:
  Standard_EXPORT void Union(const TColStd_PackedMapOfInteger&, const TColStd_PackedMapOfInteger&);

  Standard_EXPORT bool Unite(const TColStd_PackedMapOfInteger&);

  TColStd_PackedMapOfInteger& operator|=(const TColStd_PackedMapOfInteger& MM)
  {
    Unite(MM);
    return *this;
  }

  Standard_EXPORT void Intersection(const TColStd_PackedMapOfInteger&,
                                    const TColStd_PackedMapOfInteger&);

  Standard_EXPORT bool Intersect(const TColStd_PackedMapOfInteger&);

  TColStd_PackedMapOfInteger& operator&=(const TColStd_PackedMapOfInteger& MM)
  {
    Intersect(MM);
    return *this;
  }

  Standard_EXPORT void Subtraction(const TColStd_PackedMapOfInteger&,
                                   const TColStd_PackedMapOfInteger&);

  Standard_EXPORT bool Subtract(const TColStd_PackedMapOfInteger&);

  TColStd_PackedMapOfInteger& operator-=(const TColStd_PackedMapOfInteger& MM)
  {
    Subtract(MM);
    return *this;
  }

  Standard_EXPORT void Difference(const TColStd_PackedMapOfInteger&,
                                  const TColStd_PackedMapOfInteger&);

  Standard_EXPORT bool Differ(const TColStd_PackedMapOfInteger&);

  TColStd_PackedMapOfInteger& operator^=(const TColStd_PackedMapOfInteger& MM)
  {
    Differ(MM);
    return *this;
  }

  Standard_EXPORT bool IsEqual(const TColStd_PackedMapOfInteger&) const;

  bool operator==(const TColStd_PackedMapOfInteger& MM) const { return IsEqual(MM); }

  Standard_EXPORT bool IsSubset(const TColStd_PackedMapOfInteger&) const;

  bool operator<=(const TColStd_PackedMapOfInteger& MM) const { return IsSubset(MM); }

  Standard_EXPORT bool HasIntersection(const TColStd_PackedMapOfInteger&) const;

protected:
  bool Resizable() const { return IsEmpty() || (myNbPackedMapNodes > myNbBuckets); }

  static int packedKeyIndex(int theKey) { return (unsigned)theKey >> 5; }

private:
  Standard_EXPORT static int TColStd_intMapNode_findNext(const TColStd_intMapNode* theNode,
                                                         unsigned int&             theMask);

  Standard_EXPORT static int TColStd_intMapNode_findPrev(const TColStd_intMapNode* theNode,
                                                         unsigned int&             theMask);

  static size_t TColStd_Population(unsigned int& theMask, unsigned int theData)
  {
    unsigned int aRes = theData - ((theData >> 1) & 0x55555555);
    aRes              = (aRes & 0x33333333) + ((aRes >> 2) & 0x33333333);
    aRes              = (aRes + (aRes >> 4)) & 0x0f0f0f0f;
    aRes              = aRes + (aRes >> 8);
    aRes              = aRes + (aRes >> 16);
    theMask           = (theMask & TColStd_PackedMapOfInteger::MASK_HIGH)
              | ((aRes - 1) & TColStd_PackedMapOfInteger::MASK_LOW);
    return size_t(aRes & 0x3f);
  }

private:
  TColStd_intMapNode** myData1;
  int                  myNbBuckets;
  int                  myNbPackedMapNodes;

  size_t myExtent;
};
