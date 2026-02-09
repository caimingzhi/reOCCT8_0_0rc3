

#include <gp_Pnt.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis_WireOrder.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>

ShapeAnalysis_WireOrder::ShapeAnalysis_WireOrder()
    : myGap(0.0),
      myStat(0),
      myKeepLoops(false),
      myMode(Mode3D)
{
  myTol = Precision::Confusion();
  Clear();
}

ShapeAnalysis_WireOrder::ShapeAnalysis_WireOrder(const bool   theMode3D,
                                                 const double theTolerance,
                                                 const bool   theModeBoth)
    : myTol(theTolerance),
      myGap(0.0),
      myStat(0),
      myKeepLoops(false)
{
  if (theModeBoth)
  {
    myMode = ModeBoth;
  }
  else
  {
    if (theMode3D)
    {
      myMode = Mode3D;
    }
    else
    {
      myMode = Mode2D;
    }
  }
  Clear();
}

void ShapeAnalysis_WireOrder::SetMode(const bool   theMode3D,
                                      const double theTolerance,
                                      const bool   theModeBoth)
{
  ModeType aNewMode;

  if (theModeBoth)
  {
    aNewMode = ModeBoth;
  }
  else
  {
    if (theMode3D)
    {
      aNewMode = Mode3D;
    }
    else
    {
      aNewMode = Mode2D;
    }
  }
  if (myMode != aNewMode)
  {
    Clear();
  }
  myMode = aNewMode;
  myOrd.Nullify();
  myStat = 0;
  myGap  = 0.0;
  myTol  = (theTolerance > 0.0) ? theTolerance : 1.e-08;
}

double ShapeAnalysis_WireOrder::Tolerance() const
{
  return myTol;
}

void ShapeAnalysis_WireOrder::Clear()
{
  myXYZ  = new NCollection_HSequence<gp_XYZ>();
  myXY   = new NCollection_HSequence<gp_XY>();
  myStat = 0;
  myGap  = 0.0;
}

void ShapeAnalysis_WireOrder::Add(const gp_XYZ& theStart3d, const gp_XYZ& theEnd3d)
{
  if (myMode == Mode3D)
  {
    myXYZ->Append(theStart3d);
    myXYZ->Append(theEnd3d);
  }
}

void ShapeAnalysis_WireOrder::Add(const gp_XY& theStart2d, const gp_XY& theEnd2d)
{
  if (myMode == Mode2D)
  {
    gp_XYZ val;
    val.SetCoord(theStart2d.X(), theStart2d.Y(), 0.0);
    myXYZ->Append(val);
    val.SetCoord(theEnd2d.X(), theEnd2d.Y(), 0.0);
    myXYZ->Append(val);
  }
}

void ShapeAnalysis_WireOrder::Add(const gp_XYZ& theStart3d,
                                  const gp_XYZ& theEnd3d,
                                  const gp_XY&  theStart2d,
                                  const gp_XY&  theEnd2d)
{
  if (myMode == ModeBoth)
  {
    myXYZ->Append(theStart3d);
    myXYZ->Append(theEnd3d);

    myXY->Append(theStart2d);
    myXY->Append(theEnd2d);
  }
}

int ShapeAnalysis_WireOrder::NbEdges() const
{
  return myXYZ->Length() / 2;
}

static double DISTABS(const gp_XYZ& v1, const gp_XYZ& v2)
{
  return std::abs(v1.X() - v2.X()) + std::abs(v1.Y() - v2.Y()) + std::abs(v1.Z() - v2.Z());
}

bool& ShapeAnalysis_WireOrder::KeepLoopsMode()
{
  return myKeepLoops;
}

void ShapeAnalysis_WireOrder::Perform(const bool)
{
  myStat       = 0;
  int aNbEdges = NbEdges();

  if (aNbEdges == 0)
  {
    return;
  }
  myOrd = new NCollection_HArray1<int>(1, aNbEdges);
  myOrd->Init(0);

  occ::handle<NCollection_HSequence<int>> anEdgeSeq = new NCollection_HSequence<int>;
  NCollection_Sequence<occ::handle<NCollection_HSequence<int>>> aLoops;

  NCollection_Array1<gp_XYZ> aBegins3D(1, aNbEdges);
  NCollection_Array1<gp_XYZ> anEnds3D(1, aNbEdges);
  NCollection_Array1<gp_XY>  aBegins2D(1, aNbEdges);
  NCollection_Array1<gp_XY>  anEnds2D(1, aNbEdges);
  for (int i = 1; i <= aNbEdges; i++)
  {
    aBegins3D(i) = myXYZ->Value(2 * i - 1);
    anEnds3D(i)  = myXYZ->Value(2 * i);
    if (myMode == ModeBoth)
    {
      aBegins2D(i) = myXY->Value(2 * i - 1);
      anEnds2D(i)  = myXY->Value(2 * i);
    }
  }

  NCollection_Array1<bool> isEdgeUsed(1, aNbEdges);
  isEdgeUsed.Init(false);

  constexpr double aTol2  = Precision::SquareConfusion();
  constexpr double aTolP2 = Precision::SquarePConfusion();

  isEdgeUsed(1)        = true;
  gp_Pnt   aFirstPnt3D = aBegins3D(1);
  gp_Pnt   aLastPnt3D  = anEnds3D(1);
  gp_Pnt2d aFirstPnt2D;
  gp_Pnt2d aLastPnt2D;
  if (myMode == ModeBoth)
  {
    aFirstPnt2D = aBegins2D(1);
    aLastPnt2D  = anEnds2D(1);
  }
  anEdgeSeq->Append(1);

  for (;;)
  {

    int aBestJointType = 3;

    double aBestMin3D = RealLast();

    int aBestEdgeNum = 0;

    bool isFound     = false;
    bool isConnected = false;

    for (int i = 1; i <= aNbEdges; i++)
    {
      if (isEdgeUsed(i))
      {
        continue;
      }

      int    aCurJointType;
      double aCurMin;

      double aSeqTailEdgeHead = aLastPnt3D.SquareDistance(aBegins3D(i));
      double aSeqTailEdgeTail = aLastPnt3D.SquareDistance(anEnds3D(i));
      double aSeqHeadEdgeTail = aFirstPnt3D.SquareDistance(anEnds3D(i));
      double aSeqHeadEdgeHead = aFirstPnt3D.SquareDistance(aBegins3D(i));

      double aMinDistToTail, aMinDistToHead;
      int    aTailJoinType, aHeadJointType;
      if (aSeqTailEdgeHead <= aSeqTailEdgeTail)
      {
        aTailJoinType  = 0;
        aMinDistToTail = aSeqTailEdgeHead;
      }
      else
      {
        aTailJoinType  = 2;
        aMinDistToTail = aSeqTailEdgeTail;
      }
      if (aSeqHeadEdgeTail <= aSeqHeadEdgeHead)
      {
        aHeadJointType = 1;
        aMinDistToHead = aSeqHeadEdgeTail;
      }
      else
      {
        aHeadJointType = 3;
        aMinDistToHead = aSeqHeadEdgeHead;
      }

      if (fabs(aMinDistToTail - aMinDistToHead) < aTol2)
      {
        if (aTailJoinType < aHeadJointType)
        {
          aCurJointType = aTailJoinType;
          aCurMin       = aMinDistToTail;
        }
        else
        {
          aCurJointType = aHeadJointType;
          aCurMin       = aMinDistToHead;
        }
      }
      else
      {
        if (aMinDistToTail <= aMinDistToHead)
        {
          aCurJointType = aTailJoinType;
          aCurMin       = aMinDistToTail;
        }
        else
        {
          aCurJointType = aHeadJointType;
          aCurMin       = aMinDistToHead;
        }
      }

      if (myMode == ModeBoth)
      {

        int aJointMask3D = 0, aJointMask2D = 0;
        if (aSeqTailEdgeHead < aTol2)
        {
          aJointMask3D |= (1 << 0);
        }
        if (aSeqTailEdgeTail < aTol2)
        {
          aJointMask3D |= (1 << 2);
        }
        if (aSeqHeadEdgeTail < aTol2)
        {
          aJointMask3D |= (1 << 1);
        }
        if (aSeqHeadEdgeHead < aTol2)
        {
          aJointMask3D |= (1 << 3);
        }
        double aSeqTailEdgeHead2D = aLastPnt2D.SquareDistance(aBegins2D(i));
        double aSeqTailEdgeTail2D = aLastPnt2D.SquareDistance(anEnds2D(i));
        double aSeqHeadEdgeTail2D = aFirstPnt2D.SquareDistance(anEnds2D(i));
        double aSeqHeadEdgeHead2D = aFirstPnt2D.SquareDistance(aBegins2D(i));
        if (aSeqTailEdgeHead2D < aTolP2)
        {
          aJointMask2D |= (1 << 0);
        }
        if (aSeqTailEdgeTail2D < aTolP2)
        {
          aJointMask2D |= (1 << 2);
        }
        if (aSeqHeadEdgeTail2D < aTolP2)
        {
          aJointMask2D |= (1 << 1);
        }
        if (aSeqHeadEdgeHead2D < aTolP2)
        {
          aJointMask2D |= (1 << 3);
        }

        int aFullMask = aJointMask3D & aJointMask2D;
        if (aFullMask != 0)
        {

          aCurJointType = 3;
          for (int j = 0; j < 4; j++)
          {
            if (aFullMask & (1 << j))
            {
              aCurJointType = j;
              break;
            }
          }
          if (!isConnected || aCurJointType < aBestJointType)
          {
            isFound     = true;
            isConnected = true;
            switch (aCurJointType)
            {
              case 0:
                aBestMin3D = aSeqTailEdgeHead;
                break;
              case 1:
                aBestMin3D = aSeqHeadEdgeTail;
                break;
              case 2:
                aBestMin3D = aSeqTailEdgeTail;
                break;
              case 3:
                aBestMin3D = aSeqHeadEdgeHead;
                break;
            }
            aBestJointType = aCurJointType;
            aBestEdgeNum   = i;
          }
        }

        if (isConnected)
        {
          continue;
        }
      }

      if (aBestMin3D > aTol2 || aCurJointType < aBestJointType)
      {

        if (aCurMin < aBestMin3D
            || ((aCurMin == aBestMin3D || aCurMin < aTol2) && (aCurJointType < aBestJointType)))
        {
          isFound        = true;
          aBestMin3D     = aCurMin;
          aBestJointType = aCurJointType;
          aBestEdgeNum   = i;
        }
      }
    }

    if (isFound)
    {

      double aCloseDist = aFirstPnt3D.SquareDistance(aLastPnt3D);

      if (aBestMin3D <= RealSmall() || aBestMin3D < aCloseDist)
      {
        switch (aBestJointType)
        {
          case 0:
            anEdgeSeq->Append(aBestEdgeNum);
            aLastPnt3D = anEnds3D(aBestEdgeNum);
            break;
          case 1:
            anEdgeSeq->Prepend(aBestEdgeNum);
            aFirstPnt3D = aBegins3D(aBestEdgeNum);
            break;
          case 2:
            anEdgeSeq->Append(-aBestEdgeNum);
            aLastPnt3D = aBegins3D(aBestEdgeNum);
            break;
          case 3:
            anEdgeSeq->Prepend(-aBestEdgeNum);
            aFirstPnt3D = anEnds3D(aBestEdgeNum);
            break;
        }
        if (myMode == ModeBoth)
        {
          switch (aBestJointType)
          {
            case 0:
              aLastPnt2D = anEnds2D(aBestEdgeNum);
              break;
            case 1:
              aFirstPnt2D = aBegins2D(aBestEdgeNum);
              break;
            case 2:
              aLastPnt2D = aBegins2D(aBestEdgeNum);
              break;
            case 3:
              aFirstPnt2D = anEnds2D(aBestEdgeNum);
              break;
          }
        }
      }

      else
      {
        aLoops.Append(anEdgeSeq);
        anEdgeSeq   = new NCollection_HSequence<int>;
        aFirstPnt3D = aBegins3D(aBestEdgeNum);
        aLastPnt3D  = anEnds3D(aBestEdgeNum);
        if (myMode == ModeBoth)
        {
          aFirstPnt2D = aBegins2D(aBestEdgeNum);
          aLastPnt2D  = anEnds2D(aBestEdgeNum);
        }
        anEdgeSeq->Append(aBestEdgeNum);
      }

      isEdgeUsed(aBestEdgeNum) = true;
    }
    else
    {

      break;
    }
  }

  aLoops.Append(anEdgeSeq);

  occ::handle<NCollection_HSequence<int>> aMainLoop;
  if (myKeepLoops)
  {

    aMainLoop = new NCollection_HSequence<int>;
    for (int i = 1; i <= aLoops.Length(); i++)
    {
      const occ::handle<NCollection_HSequence<int>>& aCurLoop = aLoops(i);
      aMainLoop->Append(aCurLoop);
    }
  }
  else
  {

    aMainLoop = aLoops.First();
    aLoops.Remove(1);
    while (aLoops.Length())
    {

      double aMinDist1    = RealLast();
      int    aLoopNum1    = 0;
      int    aCurLoopIt1  = 0;
      bool   aDirect1     = false;
      int    aMainLoopIt1 = 0;
      for (int aLoopIt = 1; aLoopIt <= aLoops.Length(); aLoopIt++)
      {
        const occ::handle<NCollection_HSequence<int>>& aCurLoop = aLoops.Value(aLoopIt);

        int    aCurLoopIt2    = 0;
        int    aMainLoopIt2   = 0;
        bool   aDirect2       = false;
        double aMinDist2      = RealLast();
        int    aCurLoopLength = aCurLoop->Length();
        for (int aCurEdgeIt = 1; aCurEdgeIt <= aCurLoopLength; aCurEdgeIt++)
        {

          int    aPrevEdgeIt   = aCurEdgeIt == 1 ? aCurLoopLength : aCurEdgeIt - 1;
          int    aCurEdgeIdx   = aCurLoop->Value(aCurEdgeIt);
          int    aPrevEdgeIdx  = aCurLoop->Value(aPrevEdgeIt);
          gp_Pnt aCurLoopFirst = aCurEdgeIdx > 0 ? aBegins3D(aCurEdgeIdx) : anEnds3D(-aCurEdgeIdx);
          gp_Pnt aCurLoopLast =
            aPrevEdgeIdx > 0 ? anEnds3D(aPrevEdgeIdx) : aBegins3D(-aPrevEdgeIdx);

          double aMinDist3       = RealLast();
          int    aMainLoopIt3    = 0;
          bool   aDirect3        = false;
          int    aMainLoopLength = aMainLoop->Length();
          for (int aCurEdgeIt2 = 1; (aCurEdgeIt2 <= aMainLoopLength) && aMinDist3 != 0.0;
               aCurEdgeIt2++)
          {

            int    aNextEdgeIt2  = aCurEdgeIt2 == aMainLoopLength ? 1 : aCurEdgeIt2 + 1;
            int    aCurEdgeIdx2  = aMainLoop->Value(aCurEdgeIt2);
            int    aNextEdgeIdx2 = aMainLoop->Value(aNextEdgeIt2);
            gp_Pnt aMainLoopFirst =
              (aCurEdgeIdx2 > 0 ? anEnds3D(aCurEdgeIdx2) : aBegins3D(-aCurEdgeIdx2));
            gp_Pnt aMainLoopLast =
              (aNextEdgeIdx2 > 0 ? aBegins3D(aNextEdgeIdx2) : anEnds3D(-aNextEdgeIdx2));

            double aDirectDist = aCurLoopFirst.SquareDistance(aMainLoopFirst)
                                 + aCurLoopLast.SquareDistance(aMainLoopLast);
            double aReverseDist = aCurLoopFirst.SquareDistance(aMainLoopLast)
                                  + aCurLoopLast.SquareDistance(aMainLoopFirst);

            double aJoinDist;
            if ((aDirectDist < aTol2) || (aDirectDist < 2.0 * aReverseDist))
            {
              aJoinDist    = aDirectDist;
              aReverseDist = aDirectDist;
            }
            else
            {
              aJoinDist = aReverseDist;
            }

            if (aJoinDist < aMinDist3 && std::abs(aMinDist3 - aJoinDist) > aTol2)
            {
              aMinDist3    = aJoinDist;
              aDirect3     = (aDirectDist <= aReverseDist);
              aMainLoopIt3 = aCurEdgeIt2;
            }
          }

          if (aMinDist3 < aMinDist2 && std::abs(aMinDist2 - aMinDist3) > aTol2)
          {
            aMinDist2    = aMinDist3;
            aDirect2     = aDirect3;
            aMainLoopIt2 = aMainLoopIt3;
            aCurLoopIt2  = aCurEdgeIt;
          }
        }

        if (aMinDist2 < aMinDist1 && std::abs(aMinDist1 - aMinDist2) > aTol2)
        {
          aMinDist1    = aMinDist2;
          aLoopNum1    = aLoopIt;
          aDirect1     = aDirect2;
          aMainLoopIt1 = aMainLoopIt2;
          aCurLoopIt1  = aCurLoopIt2;
        }
      }

      occ::handle<NCollection_HSequence<int>> aLoop   = aLoops.Value(aLoopNum1);
      int                                     aFactor = (aDirect1 ? 1 : -1);
      for (int i = 0; i < aLoop->Length(); i++)
      {
        int anIdx =
          (aCurLoopIt1 + i > aLoop->Length() ? aCurLoopIt1 + i - aLoop->Length() : aCurLoopIt1 + i);
        aMainLoop->InsertAfter(aMainLoopIt1 + i, aLoop->Value(anIdx) * aFactor);
      }
      aLoops.Remove(aLoopNum1);
    }
  }

  int aTempStatus = 0;
  for (int i = 1; i <= aMainLoop->Length(); i++)
  {
    if (i != aMainLoop->Value(i) && aTempStatus >= 0)
    {
      aTempStatus = (aMainLoop->Value(i) > 0 ? 1 : -1);
    }
    myOrd->SetValue(i, aMainLoop->Value(i));
  }
  if (aTempStatus == 0)
  {
    myStat = aTempStatus;
    return;
  }
  else
  {

    bool isShiftReverse = true;
    bool isShiftForward = true;
    int  aFirstIdx, aSecondIdx;
    int  aLength = aMainLoop->Length();
    for (int i = 1; i <= aLength - 1; i++)
    {
      aFirstIdx  = aMainLoop->Value(i);
      aSecondIdx = aMainLoop->Value(i + 1);
      if (aSecondIdx - aFirstIdx != 1 && (aFirstIdx != aLength || aSecondIdx != 1))
      {
        isShiftForward = false;
      }
      if (aFirstIdx - aSecondIdx != 1 && (aSecondIdx != aLength || aFirstIdx != 1))
      {
        isShiftReverse = false;
      }
    }
    aFirstIdx  = aMainLoop->Value(aLength);
    aSecondIdx = aMainLoop->Value(1);
    if (aSecondIdx - aFirstIdx != 1 && (aFirstIdx != aLength || aSecondIdx != 1))
    {
      isShiftForward = false;
    }
    if (aFirstIdx - aSecondIdx != 1 && (aSecondIdx != aLength || aFirstIdx != 1))
    {
      isShiftReverse = false;
    }
    if (isShiftForward || isShiftReverse)
    {
      aTempStatus = 3;
    }
    myStat = aTempStatus;
    return;
  }
}

bool ShapeAnalysis_WireOrder::IsDone() const
{
  return !myOrd.IsNull();
}

int ShapeAnalysis_WireOrder::Status() const
{
  return myStat;
}

int ShapeAnalysis_WireOrder::Ordered(const int theIdx) const
{
  if (myOrd.IsNull() || myOrd->Upper() < theIdx)
    return theIdx;
  int anOldIdx = myOrd->Value(theIdx);
  return (anOldIdx == 0 ? theIdx : anOldIdx);
}

void ShapeAnalysis_WireOrder::XYZ(const int theIdx, gp_XYZ& theStart3D, gp_XYZ& theEnd3D) const
{
  theStart3D = myXYZ->Value((theIdx > 0 ? 2 * theIdx - 1 : -2 * theIdx));
  theEnd3D   = myXYZ->Value((theIdx > 0 ? 2 * theIdx : -2 * theIdx - 1));
}

void ShapeAnalysis_WireOrder::XY(const int theIdx, gp_XY& theStart2D, gp_XY& theEnd2D) const
{
  if (myMode == ModeBoth)
  {
    theStart2D = myXY->Value((theIdx > 0 ? 2 * theIdx - 1 : -2 * theIdx));
    theEnd2D   = myXY->Value((theIdx > 0 ? 2 * theIdx : -2 * theIdx - 1));
  }
  else
  {
    const gp_XYZ& aStart3d = myXYZ->Value((theIdx > 0 ? 2 * theIdx - 1 : -2 * theIdx));
    theStart2D.SetCoord(aStart3d.X(), aStart3d.Y());
    const gp_XYZ& anEnd3d = myXYZ->Value((theIdx > 0 ? 2 * theIdx : -2 * theIdx - 1));
    theEnd2D.SetCoord(anEnd3d.X(), anEnd3d.Y());
  }
}

double ShapeAnalysis_WireOrder::Gap(const int num) const
{
  if (num == 0)
    return myGap;
  int n1 = Ordered(num);
  int n0 = Ordered(num == 1 ? NbEdges() : num - 1);

  return DISTABS(myXYZ->Value((n0 > 0 ? 2 * n0 : -2 * n0 - 1)),
                 myXYZ->Value((n1 > 0 ? 2 * n1 - 1 : -2 * n1)));
}

void ShapeAnalysis_WireOrder::SetChains(const double gap)
{
  int n0, n1, n2, nb = NbEdges();
  if (nb == 0)
    return;
  NCollection_Sequence<int> chain;
  n0 = 0;
  chain.Append(1);
  gp_XYZ f3d, l3d, f13d, l13d;
  for (n1 = 1; n1 <= nb; n1++)
  {
    if (n0 == 0)
    {
      n0 = n1;

      XYZ(Ordered(n0), f13d, l13d);
    }

    n2 = (n1 == nb) ? n0 : (n1 + 1);
    XYZ(Ordered(n2), f3d, l3d);
    if (!f3d.IsEqual(l13d, gap))
    {
      chain.Append(n2);
      n0 = 0;
    }
    f13d = f3d;
    l13d = l3d;
  }
  nb = chain.Length();
  if (nb == 0)
    return;
  myChains = new NCollection_HArray1<int>(1, nb);
  for (n1 = 1; n1 <= nb; n1++)
    myChains->SetValue(n1, chain.Value(n1));
}

int ShapeAnalysis_WireOrder::NbChains() const
{
  return (myChains.IsNull() ? 0 : myChains->Length());
}

void ShapeAnalysis_WireOrder::Chain(const int num, int& n1, int& n2) const
{
  n1 = n2 = 0;
  if (myChains.IsNull())
    return;
  int nb = myChains->Upper();
  if (num == 0 || num > nb)
    return;
  n1 = myChains->Value(num);
  if (num == nb)
    n2 = NbEdges();
  else
    n2 = myChains->Value(num + 1) - 1;
}

void ShapeAnalysis_WireOrder::SetCouples(const double)
{
#ifdef OCCT_DEBUG
  std::cout << "ShapeAnalysis_WireOrder:SetCouple not yet implemented" << std::endl;
#endif
}

int ShapeAnalysis_WireOrder::NbCouples() const
{
  return (myCouples.IsNull() ? 0 : myCouples->Length());
}

void ShapeAnalysis_WireOrder::Couple(const int num, int& n1, int& n2) const
{
  n1 = n2 = 0;
  if (myCouples.IsNull())
    return;
  int nb = myCouples->Upper();
  if (num == 0 || num * 2 > nb)
    return;
  n1 = myCouples->Value(2 * num - 1);
  n2 = myCouples->Value(2 * num);
}
