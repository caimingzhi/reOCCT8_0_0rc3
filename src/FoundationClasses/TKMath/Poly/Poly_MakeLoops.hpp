#pragma once

#include <NCollection_Sequence.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_List.hpp>
#include <NCollection_OccAllocator.hpp>
#include <Standard_HashUtils.hpp>

class Poly_MakeLoops
{
public:
  enum LinkFlag
  {
    LF_None     = 0,
    LF_Fwd      = 1,
    LF_Rev      = 2,
    LF_Both     = 3,
    LF_Reversed = 4
  };

  struct Link
  {
    int node1, node2;
    int flags;

    Link()
        : node1(0),
          node2(0),
          flags(0)
    {
    }

    Link(int theNode1, int theNode2)
        : node1(theNode1),
          node2(theNode2),
          flags(1)
    {
    }

    void Reverse() { flags ^= Poly_MakeLoops::LF_Reversed; }

    bool IsReversed() const { return (flags & Poly_MakeLoops::LF_Reversed) != 0; }

    void Nullify() { node1 = node2 = 0; }

    bool IsNull() const { return node1 == 0 || node2 == 0; }

    bool operator==(const Link& theOther) const
    {
      return (theOther.node1 == node1 && theOther.node2 == node2)
             || (theOther.node1 == node2 && theOther.node2 == node1);
    }
  };

  struct Hasher
  {
    size_t operator()(const Poly_MakeLoops::Link& theLink) const noexcept
    {

      int aCombination[2]{theLink.node1, theLink.node2};
      if (aCombination[0] > aCombination[1])
      {
        std::swap(aCombination[0], aCombination[1]);
      }
      return opencascade::hashBytes(aCombination, sizeof(aCombination));
    }

    bool operator()(const Poly_MakeLoops::Link& theLink1,
                    const Poly_MakeLoops::Link& theLink2) const noexcept
    {
      return theLink1 == theLink2;
    }
  };

  typedef NCollection_List<Link> ListOfLink;
  typedef ListOfLink             Loop;

  class Helper
  {
  public:
    virtual const ListOfLink& GetAdjacentLinks(int theNode) const = 0;

    virtual void OnAddLink(int, const Link&) const {}
  };

  class HeapOfInteger
  {
  public:
    HeapOfInteger(const int theNbPreAllocated = 1)
        : myMap(theNbPreAllocated),
          myIterReady(false)
    {
    }

    void Clear()
    {
      myMap.Clear();
      myIterReady = false;
    }

    void Add(const int theValue)
    {
      myMap.Add(theValue);
      myIterReady = false;
    }

    int Top()
    {
      if (!myIterReady)
      {
        myIter.Initialize(myMap);
        myIterReady = true;
      }
      return myIter.Key();
    }

    bool Contains(const int theValue) const { return myMap.Contains(theValue); }

    void Remove(const int theValue)
    {
      if (myIterReady && myIter.More() && myIter.Key() == theValue)
        myIter.Next();
      myMap.Remove(theValue);
    }

    bool IsEmpty()
    {
      if (!myIterReady)
      {
        myIter.Initialize(myMap);
        myIterReady = true;
      }
      return !myIter.More();
    }

  private:
    TColStd_PackedMapOfInteger              myMap;
    TColStd_MapIteratorOfPackedMapOfInteger myIter;
    bool                                    myIterReady;
  };

public:
  Standard_EXPORT Poly_MakeLoops(const Helper*                                 theHelper,
                                 const occ::handle<NCollection_BaseAllocator>& theAlloc = nullptr);

  Standard_EXPORT void Reset(const Helper*                                 theHelper,
                             const occ::handle<NCollection_BaseAllocator>& theAlloc = nullptr);

  Standard_EXPORT void AddLink(const Link& theLink);

  Standard_EXPORT void ReplaceLink(const Link& theLink, const Link& theNewLink);

  Standard_EXPORT LinkFlag SetLinkOrientation(const Link& theLink, const LinkFlag theOrient);

  Standard_EXPORT Link FindLink(const Link& theLink) const;

  enum ResultCode
  {
    RC_LoopsDone    = 1,
    RC_HangingLinks = 2,
    RC_Failure      = 4
  };

  Standard_EXPORT int Perform();

  int GetNbLoops() const { return myLoops.Length(); }

  const Loop& GetLoop(int theIndex) const { return myLoops.Value(theIndex); }

  int GetNbHanging() const { return myHangIndices.Extent(); }

  Standard_EXPORT void GetHangingLinks(ListOfLink& theLinks) const;

protected:
  virtual int chooseLeftWay(const int                    theNode,
                            const int                    theSegIndex,
                            const NCollection_List<int>& theLstIndS) const = 0;

  const Helper* getHelper() const { return myHelper; }

  Link getLink(const int theSegIndex) const
  {
    Link aLink = myMapLink(std::abs(theSegIndex));
    if (theSegIndex < 0)
      aLink.Reverse();
    return aLink;
  }
#ifdef OCCT_DEBUG
  void showBoundaryBreaks() const;
#endif

private:
  int  findContour(int                                           theIndexS,
                   NCollection_IndexedMap<int>&                  theContour,
                   const occ::handle<NCollection_BaseAllocator>& theTempAlloc,
                   const occ::handle<NCollection_IncAllocator>&  theTempAlloc1) const;
  void acceptContour(const NCollection_IndexedMap<int>& theContour, int theStartNumber);
  int  getFirstNode(int theIndexS) const;
  int  getLastNode(int theIndexS) const;
  void markHangChain(int theNode, int theIndexS);
  bool canLinkBeTaken(int theIndexS) const;

  const Helper*                          myHelper;
  occ::handle<NCollection_BaseAllocator> myAlloc;
  NCollection_IndexedMap<Link, Hasher>   myMapLink;
  NCollection_Sequence<Loop>             myLoops;
  HeapOfInteger                          myStartIndices;
  TColStd_PackedMapOfInteger             myHangIndices;
};

class gp_Dir;

class Poly_MakeLoops3D : public Poly_MakeLoops
{
public:
  class Helper : public Poly_MakeLoops::Helper
  {
  public:
    virtual bool GetFirstTangent(const Link& theLink, gp_Dir& theDir) const = 0;

    virtual bool GetLastTangent(const Link& theLink, gp_Dir& theDir) const = 0;

    virtual bool GetNormal(int theNode, gp_Dir& theDir) const = 0;
  };

  Standard_EXPORT Poly_MakeLoops3D(const Helper*                                 theHelper,
                                   const occ::handle<NCollection_BaseAllocator>& theAlloc);

protected:
  Standard_EXPORT int chooseLeftWay(const int                    theNode,
                                    const int                    theSegIndex,
                                    const NCollection_List<int>& theLstIndS) const override;

  const Helper* getHelper() const
  {
    return static_cast<const Poly_MakeLoops3D::Helper*>(Poly_MakeLoops::getHelper());
  }
};

class gp_Dir2d;

class Poly_MakeLoops2D : public Poly_MakeLoops
{
public:
  class Helper : public Poly_MakeLoops::Helper
  {
  public:
    virtual bool GetFirstTangent(const Link& theLink, gp_Dir2d& theDir) const = 0;

    virtual bool GetLastTangent(const Link& theLink, gp_Dir2d& theDir) const = 0;
  };

  Standard_EXPORT Poly_MakeLoops2D(const bool                                    theLeftWay,
                                   const Helper*                                 theHelper,
                                   const occ::handle<NCollection_BaseAllocator>& theAlloc);

protected:
  Standard_EXPORT int chooseLeftWay(const int                    theNode,
                                    const int                    theSegIndex,
                                    const NCollection_List<int>& theLstIndS) const override;

  const Helper* getHelper() const
  {
    return static_cast<const Poly_MakeLoops2D::Helper*>(Poly_MakeLoops::getHelper());
  }

private:
  bool myRightWay;
};

namespace std
{
  template <>
  struct hash<Poly_MakeLoops::Link>
  {
    size_t operator()(const Poly_MakeLoops::Link& theLink) const noexcept
    {
      return Poly_MakeLoops::Hasher{}(theLink);
    }
  };

  template <>
  struct equal_to<Poly_MakeLoops::Link>
  {
    bool operator()(const Poly_MakeLoops::Link& theLink1,
                    const Poly_MakeLoops::Link& theLink2) const noexcept
    {
      return theLink1 == theLink2;
    }
  };
} // namespace std
