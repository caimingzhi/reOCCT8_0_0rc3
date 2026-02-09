#pragma once

#include <IntTools_CommonPrt.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <NCollection_Vector.hpp>
#include <BOPDS_Curve.hpp>
#include <BOPDS_Point.hpp>

class BOPDS_Interf
{
public:
  void SetIndices(const int theIndex1, const int theIndex2)
  {
    myIndex1 = theIndex1;
    myIndex2 = theIndex2;
  }

  void Indices(int& theIndex1, int& theIndex2) const
  {
    theIndex1 = myIndex1;
    theIndex2 = myIndex2;
  }

  void SetIndex1(const int theIndex) { myIndex1 = theIndex; }

  void SetIndex2(const int theIndex) { myIndex2 = theIndex; }

  int Index1() const { return myIndex1; }

  int Index2() const { return myIndex2; }

  int OppositeIndex(const int theI) const
  {
    if (theI == myIndex1)
    {
      return myIndex2;
    }
    else if (theI == myIndex2)
    {
      return myIndex1;
    }
    else
    {
      return -1;
    }
  }

  bool Contains(const int theIndex) const { return (myIndex1 == theIndex || myIndex2 == theIndex); }

  void SetIndexNew(const int theIndex) { myIndexNew = theIndex; }

  int IndexNew() const { return myIndexNew; }

  bool HasIndexNew(int& theIndex) const
  {
    theIndex = myIndexNew;
    return (myIndexNew >= 0);
  }

  bool HasIndexNew() const { return (myIndexNew + 1) != 0; }

protected:
  BOPDS_Interf()
      : myIndex1(-1),
        myIndex2(-1),
        myIndexNew(-1),
        myAllocator(NCollection_BaseAllocator::CommonBaseAllocator())
  {
  }

  BOPDS_Interf(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : myIndex1(-1),
        myIndex2(-1),
        myIndexNew(-1),
        myAllocator(theAllocator)
  {
  }

  virtual ~BOPDS_Interf() = default;

protected:
  int                                    myIndex1;
  int                                    myIndex2;
  int                                    myIndexNew;
  occ::handle<NCollection_BaseAllocator> myAllocator;
};

class BOPDS_InterfVV : public BOPDS_Interf
{
public:
  BOPDS_InterfVV()

    = default;

  BOPDS_InterfVV(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPDS_Interf(theAllocator)
  {
  }

  ~BOPDS_InterfVV() override = default;
};

class BOPDS_InterfVE : public BOPDS_Interf
{
public:
  BOPDS_InterfVE()
      : myParameter(0.)
  {
  }

  BOPDS_InterfVE(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPDS_Interf(theAllocator),
        myParameter(0.)
  {
  }

  ~BOPDS_InterfVE() override = default;

  void SetParameter(const double theT) { myParameter = theT; }

  double Parameter() const { return myParameter; }

protected:
  double myParameter;
};

class BOPDS_InterfVF : public BOPDS_Interf
{
public:
  BOPDS_InterfVF()
      : myU(0.),
        myV(0.)
  {
  }

  BOPDS_InterfVF(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPDS_Interf(theAllocator),
        myU(0.),
        myV(0.)
  {
  }

  ~BOPDS_InterfVF() override = default;

  void SetUV(const double theU, const double theV)
  {
    myU = theU;
    myV = theV;
  }

  void UV(double& theU, double& theV) const
  {
    theU = myU;
    theV = myV;
  }

protected:
  double myU;
  double myV;
};

class BOPDS_InterfEE : public BOPDS_Interf
{
public:
  BOPDS_InterfEE()

    = default;

  BOPDS_InterfEE(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPDS_Interf(theAllocator)
  {
  }

  ~BOPDS_InterfEE() override = default;

  void SetCommonPart(const IntTools_CommonPrt& theCP) { myCommonPart = theCP; }

  const IntTools_CommonPrt& CommonPart() const { return myCommonPart; }

protected:
  IntTools_CommonPrt myCommonPart;
};

class BOPDS_InterfEF : public BOPDS_Interf
{
public:
  BOPDS_InterfEF()

    = default;

  BOPDS_InterfEF(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPDS_Interf(theAllocator)
  {
  }

  ~BOPDS_InterfEF() override = default;

  void SetCommonPart(const IntTools_CommonPrt& theCP) { myCommonPart = theCP; }

  const IntTools_CommonPrt& CommonPart() const { return myCommonPart; }

protected:
  IntTools_CommonPrt myCommonPart;
}

;

class BOPDS_InterfFF : public BOPDS_Interf
{
public:
  BOPDS_InterfFF()
      : myTangentFaces(false),
        myCurves(0, myAllocator),
        myPoints(0, myAllocator)
  {
  }

  ~BOPDS_InterfFF() override = default;

  void Init(const int theNbCurves, const int theNbPoints)
  {
    if (theNbCurves > 0)
    {
      myCurves.SetIncrement(theNbCurves);
    }
    if (theNbPoints > 0)
    {
      myPoints.SetIncrement(theNbPoints);
    }
  }

  void SetTangentFaces(const bool theFlag) { myTangentFaces = theFlag; }

  bool TangentFaces() const { return myTangentFaces; }

  const NCollection_Vector<BOPDS_Curve>& Curves() const { return myCurves; }

  NCollection_Vector<BOPDS_Curve>& ChangeCurves() { return myCurves; }

  const NCollection_Vector<BOPDS_Point>& Points() const { return myPoints; }

  NCollection_Vector<BOPDS_Point>& ChangePoints() { return myPoints; }

protected:
  bool                            myTangentFaces;
  NCollection_Vector<BOPDS_Curve> myCurves;
  NCollection_Vector<BOPDS_Point> myPoints;
};

class BOPDS_InterfVZ : public BOPDS_Interf
{
public:
  BOPDS_InterfVZ() = default;

  BOPDS_InterfVZ(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPDS_Interf(theAllocator) {};

  ~BOPDS_InterfVZ() override = default;
};

class BOPDS_InterfEZ : public BOPDS_Interf
{
public:
  BOPDS_InterfEZ() = default;

  BOPDS_InterfEZ(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPDS_Interf(theAllocator) {};

  ~BOPDS_InterfEZ() override = default;
};

class BOPDS_InterfFZ : public BOPDS_Interf
{
public:
  BOPDS_InterfFZ() = default;

  BOPDS_InterfFZ(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPDS_Interf(theAllocator) {};

  ~BOPDS_InterfFZ() override = default;
};

class BOPDS_InterfZZ : public BOPDS_Interf
{
public:
  BOPDS_InterfZZ() = default;

  BOPDS_InterfZZ(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPDS_Interf(theAllocator) {};

  ~BOPDS_InterfZZ() override = default;
};
