#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box.hpp>
#include <IntTools_Curve.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
class IntTools_Curve;
class Bnd_Box;
class BOPDS_PaveBlock;

class BOPDS_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  BOPDS_Curve();

  virtual ~BOPDS_Curve();

  BOPDS_Curve(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  void SetCurve(const IntTools_Curve& theC);

  const IntTools_Curve& Curve() const;

  void SetBox(const Bnd_Box& theBox);

  const Bnd_Box& Box() const;

  Bnd_Box& ChangeBox();

  void SetPaveBlocks(const NCollection_List<occ::handle<BOPDS_PaveBlock>>& theLPB);

  const NCollection_List<occ::handle<BOPDS_PaveBlock>>& PaveBlocks() const;

  NCollection_List<occ::handle<BOPDS_PaveBlock>>& ChangePaveBlocks();

  void InitPaveBlock1();

  occ::handle<BOPDS_PaveBlock>& ChangePaveBlock1();

  const NCollection_List<int>& TechnoVertices() const;

  NCollection_List<int>& ChangeTechnoVertices();

  bool HasEdge() const;

  void SetTolerance(const double theTol) { myTolerance = theTol; }

  double Tolerance() const { return myTolerance; }

  double TangentialTolerance() const { return myCurve.TangentialTolerance(); }

protected:
  occ::handle<NCollection_BaseAllocator>         myAllocator;
  IntTools_Curve                                 myCurve;
  NCollection_List<occ::handle<BOPDS_PaveBlock>> myPaveBlocks;
  NCollection_List<int>                          myTechnoVertices;
  Bnd_Box                                        myBox;
  double                                         myTolerance;
};

#include <BOPDS_PaveBlock.hpp>

inline BOPDS_Curve::BOPDS_Curve()
    : myAllocator(NCollection_BaseAllocator::CommonBaseAllocator()),
      myPaveBlocks(myAllocator),
      myTechnoVertices(myAllocator),
      myTolerance(0.)
{
}

inline BOPDS_Curve::BOPDS_Curve(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : myAllocator(theAllocator),
      myPaveBlocks(myAllocator),
      myTechnoVertices(myAllocator),
      myTolerance(0.)
{
}

inline BOPDS_Curve::~BOPDS_Curve() = default;

inline void BOPDS_Curve::SetCurve(const IntTools_Curve& theCurve)
{
  myCurve = theCurve;
}

inline const IntTools_Curve& BOPDS_Curve::Curve() const
{
  return myCurve;
}

inline void BOPDS_Curve::SetPaveBlocks(const NCollection_List<occ::handle<BOPDS_PaveBlock>>& theLPB)
{
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aIt;

  myPaveBlocks.Clear();
  aIt.Initialize(theLPB);
  for (; aIt.More(); aIt.Next())
  {
    myPaveBlocks.Append(aIt.Value());
  }
}

inline const NCollection_List<occ::handle<BOPDS_PaveBlock>>& BOPDS_Curve::PaveBlocks() const
{
  return myPaveBlocks;
}

inline NCollection_List<occ::handle<BOPDS_PaveBlock>>& BOPDS_Curve::ChangePaveBlocks()
{
  return myPaveBlocks;
}

inline void BOPDS_Curve::InitPaveBlock1()
{
  if (!myPaveBlocks.Extent())
  {
    occ::handle<BOPDS_PaveBlock> aPB = new BOPDS_PaveBlock;
    myPaveBlocks.Append(aPB);
  }
}

inline occ::handle<BOPDS_PaveBlock>& BOPDS_Curve::ChangePaveBlock1()
{
  occ::handle<BOPDS_PaveBlock>* pPB = (occ::handle<BOPDS_PaveBlock>*)&myPaveBlocks.First();
  return *pPB;
}

inline const NCollection_List<int>& BOPDS_Curve::TechnoVertices() const
{
  return myTechnoVertices;
}

inline NCollection_List<int>& BOPDS_Curve::ChangeTechnoVertices()
{
  return myTechnoVertices;
}

inline void BOPDS_Curve::SetBox(const Bnd_Box& theBox)
{
  myBox = theBox;
}

inline const Bnd_Box& BOPDS_Curve::Box() const
{
  return myBox;
}

inline Bnd_Box& BOPDS_Curve::ChangeBox()
{
  return myBox;
}

inline bool BOPDS_Curve::HasEdge() const
{
  bool                                                     bFlag;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItPB;

  bFlag = false;
  aItPB.Initialize(myPaveBlocks);
  for (; aItPB.More(); aItPB.Next())
  {
    const occ::handle<BOPDS_PaveBlock>& aPB = aItPB.Value();
    bFlag                                   = aPB->HasEdge();
    if (bFlag)
    {
      break;
    }
  }
  return bFlag;
}
