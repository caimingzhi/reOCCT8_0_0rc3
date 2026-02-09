#pragma once

#include <BOPDS_PaveBlock.hpp>

class BOPDS_CoupleOfPaveBlocks
{
public:
  BOPDS_CoupleOfPaveBlocks()
      : myIndexInterf(-1),
        myIndex(-1),
        myTolerance(0)
  {
  }

  BOPDS_CoupleOfPaveBlocks(const occ::handle<BOPDS_PaveBlock>& thePB1,
                           const occ::handle<BOPDS_PaveBlock>& thePB2)
      : myIndexInterf(-1),
        myIndex(-1),
        myTolerance(0)
  {
    SetPaveBlocks(thePB1, thePB2);
  }

  ~BOPDS_CoupleOfPaveBlocks() = default;

  void SetIndex(const int theIndex) { myIndex = theIndex; }

  int Index() const { return myIndex; }

  void SetIndexInterf(const int theIndex) { myIndexInterf = theIndex; }

  int IndexInterf() const { return myIndexInterf; }

  void SetPaveBlocks(const occ::handle<BOPDS_PaveBlock>& thePB1,
                     const occ::handle<BOPDS_PaveBlock>& thePB2)
  {
    myPB[0] = thePB1;
    myPB[1] = thePB2;
  }

  void PaveBlocks(occ::handle<BOPDS_PaveBlock>& thePB1, occ::handle<BOPDS_PaveBlock>& thePB2) const
  {
    thePB1 = myPB[0];
    thePB2 = myPB[1];
  }

  void SetPaveBlock1(const occ::handle<BOPDS_PaveBlock>& thePB) { myPB[0] = thePB; }

  const occ::handle<BOPDS_PaveBlock>& PaveBlock1() const { return myPB[0]; }

  void SetPaveBlock2(const occ::handle<BOPDS_PaveBlock>& thePB) { myPB[1] = thePB; }

  const occ::handle<BOPDS_PaveBlock>& PaveBlock2() const { return myPB[1]; }

  void SetTolerance(const double theTol) { myTolerance = theTol; }

  double Tolerance() const { return myTolerance; }

protected:
  int                          myIndexInterf;
  int                          myIndex;
  occ::handle<BOPDS_PaveBlock> myPB[2];
  double                       myTolerance;
};
