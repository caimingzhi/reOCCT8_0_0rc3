#pragma once

#include <NCollection_BaseMap.hpp>
#include <NCollection_TListNode.hpp>
#include <Standard_MultiplyDefined.hpp>
#include <Standard_NoSuchObject.hpp>

#include <NCollection_DefaultHasher.hpp>

template <class TheKey1Type,
          class TheKey2Type,
          class Hasher1 = NCollection_DefaultHasher<TheKey1Type>,
          class Hasher2 = NCollection_DefaultHasher<TheKey2Type>>
class NCollection_DoubleMap : public NCollection_BaseMap
{
public:
  typedef TheKey1Type key1_type;

  typedef TheKey2Type key2_type;

public:
  class DoubleMapNode : public NCollection_TListNode<TheKey2Type>
  {
  public:
    DoubleMapNode(const TheKey1Type&    theKey1,
                  const TheKey2Type&    theKey2,
                  NCollection_ListNode* theNext1,
                  NCollection_ListNode* theNext2)
        : NCollection_TListNode<TheKey2Type>(theKey2, theNext1),
          myKey1(theKey1),
          myNext2((DoubleMapNode*)theNext2)
    {
    }

    const TheKey1Type& Key1() noexcept { return myKey1; }

    const TheKey2Type& Key2() noexcept { return this->myValue; }

    DoubleMapNode*& Next2() noexcept { return myNext2; }

    static void delNode(NCollection_ListNode*                   theNode,
                        occ::handle<NCollection_BaseAllocator>& theAl) noexcept
    {
      ((DoubleMapNode*)theNode)->~DoubleMapNode();
      theAl->Free(theNode);
    }

  private:
    TheKey1Type    myKey1;
    DoubleMapNode* myNext2;
  };

public:
  class Iterator : public NCollection_BaseMap::Iterator
  {
  public:
    Iterator() = default;

    Iterator(const NCollection_DoubleMap& theMap)
        : NCollection_BaseMap::Iterator(theMap)
    {
    }

    bool More() const noexcept { return PMore(); }

    void Next() noexcept { PNext(); }

    const TheKey1Type& Key1() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_DoubleMap::Iterator::Key1");
      return ((DoubleMapNode*)myNode)->Key1();
    }

    const TheKey2Type& Key2() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_DoubleMap::Iterator::Key2");
      return ((DoubleMapNode*)myNode)->Key2();
    }

    const TheKey2Type& Value() const
    {
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_DoubleMap::Iterator::Value");
      return ((DoubleMapNode*)myNode)->Value();
    }
  };

public:
  NCollection_DoubleMap()
      : NCollection_BaseMap(1, false, occ::handle<NCollection_BaseAllocator>())
  {
  }

  explicit NCollection_DoubleMap(
    const int                                     theNbBuckets,
    const occ::handle<NCollection_BaseAllocator>& theAllocator = nullptr)
      : NCollection_BaseMap(theNbBuckets, false, theAllocator)
  {
  }

  NCollection_DoubleMap(const NCollection_DoubleMap& theOther)
      : NCollection_BaseMap(theOther.NbBuckets(), false, theOther.myAllocator)
  {
    *this = theOther;
  }

  void Exchange(NCollection_DoubleMap& theOther) noexcept { this->exchangeMapsData(theOther); }

  NCollection_DoubleMap& Assign(const NCollection_DoubleMap& theOther)
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
      {
        TheKey1Type    aKey1 = anIter.Key1();
        TheKey2Type    aKey2 = anIter.Key2();
        const size_t   iK1   = HashCode1(aKey1, NbBuckets());
        const size_t   iK2   = HashCode2(aKey2, NbBuckets());
        DoubleMapNode* pNode =
          new (this->myAllocator) DoubleMapNode(aKey1, aKey2, myData1[iK1], myData2[iK2]);
        myData1[iK1] = pNode;
        myData2[iK2] = pNode;
        Increment();
      }
    }
    return *this;
  }

  NCollection_DoubleMap& operator=(const NCollection_DoubleMap& theOther)
  {
    return Assign(theOther);
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
        DoubleMapNode *p, *q;
        for (int i = 0; i <= NbBuckets(); i++)
        {
          if (myData1[i])
          {
            p = (DoubleMapNode*)myData1[i];
            while (p)
            {
              const size_t iK1 = HashCode1(p->Key1(), newBuck);
              const size_t iK2 = HashCode2(p->Key2(), newBuck);
              q                = (DoubleMapNode*)p->Next();
              p->Next()        = ppNewData1[iK1];
              p->Next2()       = (DoubleMapNode*)ppNewData2[iK2];
              ppNewData1[iK1]  = p;
              ppNewData2[iK2]  = p;
              p                = q;
            }
          }
        }
      }
      EndResize(N, newBuck, ppNewData1, ppNewData2);
    }
  }

  void Bind(const TheKey1Type& theKey1, const TheKey2Type& theKey2)
  {
    if (Resizable())
      ReSize(Extent());
    const size_t   iK1 = HashCode1(theKey1, NbBuckets());
    const size_t   iK2 = HashCode2(theKey2, NbBuckets());
    DoubleMapNode* pNode;
    pNode = (DoubleMapNode*)myData1[iK1];
    while (pNode)
    {
      if (IsEqual1(pNode->Key1(), theKey1))
        throw Standard_MultiplyDefined("NCollection_DoubleMap:Bind");
      pNode = (DoubleMapNode*)pNode->Next();
    }
    pNode = (DoubleMapNode*)myData2[iK2];
    while (pNode)
    {
      if (IsEqual2(pNode->Key2(), theKey2))
        throw Standard_MultiplyDefined("NCollection_DoubleMap:Bind");
      pNode = (DoubleMapNode*)pNode->Next();
    }
    pNode = new (this->myAllocator) DoubleMapNode(theKey1, theKey2, myData1[iK1], myData2[iK2]);
    myData1[iK1] = pNode;
    myData2[iK2] = pNode;
    Increment();
  }

  bool AreBound(const TheKey1Type& theKey1, const TheKey2Type& theKey2) const
  {
    if (IsEmpty())
      return false;
    const size_t   iK1 = HashCode1(theKey1, NbBuckets());
    const size_t   iK2 = HashCode2(theKey2, NbBuckets());
    DoubleMapNode *pNode1, *pNode2;
    pNode1 = (DoubleMapNode*)myData1[iK1];
    while (pNode1)
    {
      if (IsEqual1(pNode1->Key1(), theKey1))
        break;
      pNode1 = (DoubleMapNode*)pNode1->Next();
    }
    if (pNode1 == NULL)
      return false;
    pNode2 = (DoubleMapNode*)myData2[iK2];
    while (pNode2)
    {
      if (IsEqual2(pNode2->Key2(), theKey2))
        break;
      pNode2 = (DoubleMapNode*)pNode2->Next();
    }
    if (pNode2 == NULL)
      return false;

    return (pNode1 == pNode2);
  }

  bool IsBound1(const TheKey1Type& theKey1) const
  {
    if (IsEmpty())
      return false;
    const size_t   iK1 = HashCode1(theKey1, NbBuckets());
    DoubleMapNode* pNode1;
    pNode1 = (DoubleMapNode*)myData1[iK1];
    while (pNode1)
    {
      if (IsEqual1(pNode1->Key1(), theKey1))
        return true;
      pNode1 = (DoubleMapNode*)pNode1->Next();
    }
    return false;
  }

  bool IsBound2(const TheKey2Type& theKey2) const
  {
    if (IsEmpty())
      return false;
    const size_t   iK2 = HashCode2(theKey2, NbBuckets());
    DoubleMapNode* pNode2;
    pNode2 = (DoubleMapNode*)myData2[iK2];
    while (pNode2)
    {
      if (IsEqual2(pNode2->Key2(), theKey2))
        return true;
      pNode2 = (DoubleMapNode*)pNode2->Next2();
    }
    return false;
  }

  bool UnBind1(const TheKey1Type& theKey1)
  {
    if (IsEmpty())
      return false;
    const size_t   iK1 = HashCode1(theKey1, NbBuckets());
    DoubleMapNode *p1, *p2, *q1, *q2;
    q1 = q2 = nullptr;
    p1      = (DoubleMapNode*)myData1[iK1];
    while (p1)
    {
      if (IsEqual1(p1->Key1(), theKey1))
      {

        if (q1)
          q1->Next() = p1->Next();
        else
          myData1[iK1] = (DoubleMapNode*)p1->Next();
        const size_t iK2 = HashCode2(p1->Key2(), NbBuckets());
        p2               = (DoubleMapNode*)myData2[iK2];
        while (p2)
        {
          if (p2 == p1)
          {

            if (q2)
              q2->Next2() = p2->Next2();
            else
              myData2[iK2] = (DoubleMapNode*)p2->Next2();
            break;
          }
          q2 = p2;
          p2 = (DoubleMapNode*)p2->Next2();
        }
        p1->~DoubleMapNode();
        this->myAllocator->Free(p1);
        Decrement();
        return true;
      }
      q1 = p1;
      p1 = (DoubleMapNode*)p1->Next();
    }
    return false;
  }

  bool UnBind2(const TheKey2Type& theKey2)
  {
    if (IsEmpty())
      return false;
    const size_t   iK2 = HashCode2(theKey2, NbBuckets());
    DoubleMapNode *p1, *p2, *q1, *q2;
    q1 = q2 = nullptr;
    p2      = (DoubleMapNode*)myData2[iK2];
    while (p2)
    {
      if (IsEqual2(p2->Key2(), theKey2))
      {

        if (q2)
        {
          q2->Next2() = p2->Next2();
        }
        else
          myData2[iK2] = (DoubleMapNode*)p2->Next2();
        const size_t iK1 = HashCode1(p2->Key1(), NbBuckets());
        p1               = (DoubleMapNode*)myData1[iK1];
        while (p1)
        {
          if (p1 == p2)
          {

            if (q1)
              q1->Next() = p1->Next();
            else
              myData1[iK1] = (DoubleMapNode*)p1->Next();
            break;
          }
          q1 = p1;
          p1 = (DoubleMapNode*)p1->Next();
        }
        p2->~DoubleMapNode();
        this->myAllocator->Free(p2);
        Decrement();
        return true;
      }
      q2 = p2;
      p2 = (DoubleMapNode*)p2->Next2();
    }
    return false;
  }

  const TheKey2Type& Find1(const TheKey1Type& theKey1) const
  {
    if (const TheKey2Type* aKey2 = Seek1(theKey1))
    {
      return *aKey2;
    }
    throw Standard_NoSuchObject("NCollection_DoubleMap::Find1");
  }

  bool Find1(const TheKey1Type& theKey1, TheKey2Type& theKey2) const
  {
    if (const TheKey2Type* aKey2 = Seek1(theKey1))
    {
      theKey2 = *aKey2;
      return true;
    }
    return false;
  }

  const TheKey2Type* Seek1(const TheKey1Type& theKey1) const
  {
    for (DoubleMapNode* aNode1 =
           !IsEmpty() ? (DoubleMapNode*)myData1[HashCode1(theKey1, NbBuckets())] : nullptr;
         aNode1 != nullptr;
         aNode1 = (DoubleMapNode*)aNode1->Next())
    {
      if (IsEqual1(aNode1->Key1(), theKey1))
      {
        return &aNode1->Key2();
      }
    }
    return nullptr;
  }

  const TheKey1Type& Find2(const TheKey2Type& theKey2) const
  {
    if (const TheKey1Type* aVal1 = Seek2(theKey2))
    {
      return *aVal1;
    }
    throw Standard_NoSuchObject("NCollection_DoubleMap::Find2");
  }

  bool Find2(const TheKey2Type& theKey2, TheKey1Type& theKey1) const
  {
    if (const TheKey1Type* aVal1 = Seek2(theKey2))
    {
      theKey1 = *aVal1;
      return true;
    }
    return false;
  }

  const TheKey1Type* Seek2(const TheKey2Type& theKey2) const
  {
    for (DoubleMapNode* aNode2 =
           !IsEmpty() ? (DoubleMapNode*)myData2[HashCode2(theKey2, NbBuckets())] : nullptr;
         aNode2 != nullptr;
         aNode2 = (DoubleMapNode*)aNode2->Next2())
    {
      if (IsEqual2(aNode2->Key2(), theKey2))
      {
        return &aNode2->Key1();
      }
    }
    return nullptr;
  }

  void Clear(const bool doReleaseMemory = false)
  {
    Destroy(DoubleMapNode::delNode, doReleaseMemory);
  }

  void Clear(const occ::handle<NCollection_BaseAllocator>& theAllocator)
  {
    Clear(true);
    this->myAllocator =
      (!theAllocator.IsNull() ? theAllocator : NCollection_BaseAllocator::CommonBaseAllocator());
  }

  ~NCollection_DoubleMap() override { Clear(true); }

  int Size() const noexcept { return Extent(); }

protected:
  bool IsEqual1(const TheKey1Type& theKey1, const TheKey1Type& theKey2) const
  {
    return myHasher1(theKey1, theKey2);
  }

  size_t HashCode1(const TheKey1Type& theKey, const int theUpperBound) const
  {
    return myHasher1(theKey) % theUpperBound + 1;
  }

  bool IsEqual2(const TheKey2Type& theKey1, const TheKey2Type& theKey2) const
  {
    return myHasher2(theKey1, theKey2);
  }

  size_t HashCode2(const TheKey2Type& theKey, const int theUpperBound) const
  {
    return myHasher2(theKey) % theUpperBound + 1;
  }

protected:
  Hasher1 myHasher1;
  Hasher2 myHasher2;
};
