#include <BOPDS_CommonBlock.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BOPDS_CommonBlock, Standard_Transient)

BOPDS_CommonBlock::BOPDS_CommonBlock()
    : myTolerance(0.0)
{
}

BOPDS_CommonBlock::BOPDS_CommonBlock(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : myPaveBlocks(theAllocator),
      myFaces(theAllocator),
      myTolerance(0.0)
{
}

void BOPDS_CommonBlock::AddPaveBlock(const occ::handle<BOPDS_PaveBlock>& aPB)
{
  if (myPaveBlocks.IsEmpty())
  {
    myPaveBlocks.Append(aPB);
    return;
  }

  if (aPB->OriginalEdge() < myPaveBlocks.First()->OriginalEdge())
  {
    myPaveBlocks.Prepend(aPB);
  }
  else
  {
    myPaveBlocks.Append(aPB);
  }
}

void BOPDS_CommonBlock::SetPaveBlocks(const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB)
{
  myPaveBlocks.Clear();
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aIt(aLPB);
  for (; aIt.More(); aIt.Next())
  {
    AddPaveBlock(aIt.Value());
  }
}

const NCollection_List<occ::handle<BOPDS_PaveBlock>>& BOPDS_CommonBlock::PaveBlocks() const
{
  return myPaveBlocks;
}

void BOPDS_CommonBlock::AddFace(const int aF)
{
  myFaces.Append(aF);
}

void BOPDS_CommonBlock::SetFaces(const NCollection_List<int>& aLF)
{
  myFaces = aLF;
}

void BOPDS_CommonBlock::AppendFaces(NCollection_List<int>& aLF)
{
  myFaces.Append(aLF);
}

const NCollection_List<int>& BOPDS_CommonBlock::Faces() const
{
  return myFaces;
}

const occ::handle<BOPDS_PaveBlock>& BOPDS_CommonBlock::PaveBlock1() const
{
  return myPaveBlocks.First();
}

void BOPDS_CommonBlock::SetRealPaveBlock(const occ::handle<BOPDS_PaveBlock>& thePB)
{
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator it(myPaveBlocks);
  for (; it.More(); it.Next())
  {
    if (it.Value() == thePB)
    {
      myPaveBlocks.Prepend(thePB);
      myPaveBlocks.Remove(it);
      break;
    }
  }
}

occ::handle<BOPDS_PaveBlock>& BOPDS_CommonBlock::PaveBlockOnEdge(const int aIx)
{
  static occ::handle<BOPDS_PaveBlock> aPBs;

  int                                                      aIOr;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator anIt;

  anIt.Initialize(myPaveBlocks);
  for (; anIt.More(); anIt.Next())
  {
    occ::handle<BOPDS_PaveBlock>& aPB = anIt.ChangeValue();
    aIOr                              = aPB->OriginalEdge();
    if (aIOr == aIx)
    {
      return aPB;
    }
  }
  return aPBs;
}

bool BOPDS_CommonBlock::IsPaveBlockOnFace(const int aIx) const
{
  bool                            bFound;
  int                             nF;
  NCollection_List<int>::Iterator anIt;

  bFound = false;
  anIt.Initialize(myFaces);
  for (; anIt.More(); anIt.Next())
  {
    nF = anIt.Value();
    if (nF == aIx)
    {
      return !bFound;
    }
  }
  return bFound;
}

bool BOPDS_CommonBlock::IsPaveBlockOnEdge(const int aIx) const
{
  bool                                                     bFound;
  int                                                      aIOr;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator anIt;

  bFound = false;
  anIt.Initialize(myPaveBlocks);
  for (; anIt.More(); anIt.Next())
  {
    const occ::handle<BOPDS_PaveBlock>& aPB = anIt.Value();
    aIOr                                    = aPB->OriginalEdge();
    if (aIOr == aIx)
    {
      return !bFound;
    }
  }
  return bFound;
}

void BOPDS_CommonBlock::SetEdge(const int theEdge)
{
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator anIt;

  anIt.Initialize(myPaveBlocks);
  for (; anIt.More(); anIt.Next())
  {
    occ::handle<BOPDS_PaveBlock>& aPB = anIt.ChangeValue();
    aPB->SetEdge(theEdge);
  }
}

int BOPDS_CommonBlock::Edge() const
{
  const occ::handle<BOPDS_PaveBlock>& aPB1 = myPaveBlocks.First();
  if (!aPB1.IsNull())
  {
    return aPB1->Edge();
  }
  return -1;
}

bool BOPDS_CommonBlock::Contains(const occ::handle<BOPDS_PaveBlock>& aPBx) const
{
  bool                                                     bFound;
  int                                                      aNb1;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator anIt;

  bFound = false;
  aNb1   = myPaveBlocks.Extent();

  if (!aNb1)
  {
    return bFound;
  }

  anIt.Initialize(myPaveBlocks);
  for (; anIt.More(); anIt.Next())
  {
    const occ::handle<BOPDS_PaveBlock>& aPB = anIt.Value();
    if (aPB == aPBx)
    {
      return !bFound;
    }
  }
  return bFound;
}

bool BOPDS_CommonBlock::Contains(const int theF) const
{
  bool                            bFound;
  NCollection_List<int>::Iterator aIt;

  bFound = false;
  aIt.Initialize(myFaces);
  for (; aIt.More(); aIt.Next())
  {
    if (aIt.Value() == theF)
    {
      return !bFound;
    }
  }
  return bFound;
}

void BOPDS_CommonBlock::Dump() const
{
  int                                                      nF;
  NCollection_List<int>::Iterator                          aIt;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItPB;

  printf(" -- CB:\n");
  aItPB.Initialize(myPaveBlocks);
  for (; aItPB.More(); aItPB.Next())
  {
    const occ::handle<BOPDS_PaveBlock>& aPB = aItPB.Value();
    aPB->Dump();
    printf("\n");
  }

  if (myFaces.Extent())
  {
    printf(" Faces:");
    aIt.Initialize(myFaces);
    for (; aIt.More(); aIt.Next())
    {
      nF = aIt.Value();
      printf(" %d", nF);
    }
    printf("\n");
  }
}
