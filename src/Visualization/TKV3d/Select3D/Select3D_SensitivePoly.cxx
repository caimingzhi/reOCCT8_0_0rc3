

#include <Select3D_SensitivePoly.hpp>

#include <ElCLib.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitivePoly, Select3D_SensitiveSet)

namespace
{
  static int GetCircleNbPoints(const gp_Circ& theCircle,
                               const int      theNbPnts,
                               const double   theU1,
                               const double   theU2,
                               const bool     theIsFilled)
  {

    if (theNbPnts <= 0)
    {
      return 0;
    }

    if (theCircle.Radius() > Precision::Confusion())
    {
      const bool isSector =
        theIsFilled && std::abs(std::abs(theU2 - theU1) - 2.0 * M_PI) > gp::Resolution();
      return 2 * theNbPnts + 1 + (isSector ? 2 : 0);
    }

    return 1;
  }

  static void initCircle(Select3D_PointData& thePolygon,
                         const gp_Circ&      theCircle,
                         const double        theU1,
                         const double        theU2,
                         const bool          theIsFilled,
                         const int           theNbPnts)
  {
    const double aStep   = (theU2 - theU1) / theNbPnts;
    const double aRadius = theCircle.Radius();
    int          aPntIdx = 0;
    double       aCurU   = theU1;
    gp_Pnt       aP1;
    gp_Vec       aV1;

    const bool isSector = std::abs(theU2 - theU1 - 2.0 * M_PI) > gp::Resolution();

    if (isSector && theIsFilled)
    {
      thePolygon.SetPnt(aPntIdx++, theCircle.Location());
    }

    for (int anIndex = 1; anIndex <= theNbPnts; ++anIndex, aCurU += aStep)
    {
      ElCLib::CircleD1(aCurU, theCircle.Position(), theCircle.Radius(), aP1, aV1);
      thePolygon.SetPnt(aPntIdx++, aP1);

      aV1.Normalize();
      const gp_Pnt aP2 = aP1.XYZ() + aV1.XYZ() * std::tan(aStep * 0.5) * aRadius;
      thePolygon.SetPnt(aPntIdx++, aP2);
    }
    aP1 = ElCLib::CircleValue(theU2, theCircle.Position(), theCircle.Radius());
    thePolygon.SetPnt(aPntIdx++, aP1);

    if (isSector && theIsFilled)
    {
      thePolygon.SetPnt(aPntIdx++, theCircle.Location());
    }
  }
} // namespace

Select3D_SensitivePoly::Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                               const NCollection_Array1<gp_Pnt>&         thePoints,
                                               const bool theIsBVHEnabled)
    : Select3D_SensitiveSet(theOwnerId),
      myPolyg(thePoints.Upper() - thePoints.Lower() + 1),
      mySensType(Select3D_TOS_BOUNDARY)
{
  int    aLowerIdx  = thePoints.Lower();
  int    anUpperIdx = thePoints.Upper();
  gp_XYZ aPntSum(0.0, 0.0, 0.0);

  Select3D_BndBox3d aBndBox;
  for (int aIdx = aLowerIdx; aIdx <= anUpperIdx; ++aIdx)
  {
    aPntSum += thePoints.Value(aIdx).XYZ();
    const NCollection_Vec3<double> aPnt(thePoints.Value(aIdx).X(),
                                        thePoints.Value(aIdx).Y(),
                                        thePoints.Value(aIdx).Z());
    aBndBox.Add(aPnt);
    myPolyg.SetPnt(aIdx - aLowerIdx, thePoints.Value(aIdx));
  }

  myBndBox = aBndBox;
  myCOG    = aPntSum / myPolyg.Size();

  if (theIsBVHEnabled)
  {
    const int aPntsNum = myPolyg.Size();
    mySegmentIndexes   = new NCollection_HArray1<int>(0, aPntsNum - 2);
    for (int aSegmIter = 0; aSegmIter < aPntsNum - 1; ++aSegmIter)
    {
      mySegmentIndexes->SetValue(aSegmIter, aSegmIter);
    }
  }

  myIsComputed = true;
}

Select3D_SensitivePoly::Select3D_SensitivePoly(
  const occ::handle<SelectMgr_EntityOwner>&       theOwnerId,
  const occ::handle<NCollection_HArray1<gp_Pnt>>& thePoints,
  const bool                                      theIsBVHEnabled)
    : Select3D_SensitiveSet(theOwnerId),
      myPolyg(thePoints->Upper() - thePoints->Lower() + 1),
      mySensType(Select3D_TOS_BOUNDARY)
{
  int    aLowerIdx  = thePoints->Lower();
  int    anUpperIdx = thePoints->Upper();
  gp_XYZ aPntSum(0.0, 0.0, 0.0);

  Select3D_BndBox3d aBndBox;
  for (int aIdx = aLowerIdx; aIdx <= anUpperIdx; ++aIdx)
  {
    aPntSum += thePoints->Value(aIdx).XYZ();
    const NCollection_Vec3<double> aPnt(thePoints->Value(aIdx).X(),
                                        thePoints->Value(aIdx).Y(),
                                        thePoints->Value(aIdx).Z());
    aBndBox.Add(aPnt);
    myPolyg.SetPnt(aIdx - aLowerIdx, thePoints->Value(aIdx));
  }

  myBndBox = aBndBox;
  myCOG    = aPntSum / myPolyg.Size();

  if (theIsBVHEnabled)
  {
    const int aPntsNum = myPolyg.Size();
    mySegmentIndexes   = new NCollection_HArray1<int>(0, aPntsNum - 2);
    for (int aSegmIter = 0; aSegmIter < aPntsNum - 1; ++aSegmIter)
    {
      mySegmentIndexes->SetValue(aSegmIter, aSegmIter);
    }
  }

  myIsComputed = true;
}

Select3D_SensitivePoly::Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                               const bool theIsBVHEnabled,
                                               const int  theNbPnts)
    : Select3D_SensitiveSet(theOwnerId),
      myPolyg(theNbPnts),
      mySensType(Select3D_TOS_BOUNDARY)
{
  if (theIsBVHEnabled)
  {
    mySegmentIndexes = new NCollection_HArray1<int>(0, theNbPnts - 2);
    for (int aIdx = 0; aIdx < theNbPnts - 1; ++aIdx)
    {
      mySegmentIndexes->SetValue(aIdx, aIdx);
    }
  }
  myCOG        = gp_Pnt(RealLast(), RealLast(), RealLast());
  myIsComputed = false;
}

Select3D_SensitivePoly::Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                               const gp_Circ&                            theCircle,
                                               const double                              theU1,
                                               const double                              theU2,
                                               const bool theIsFilled,
                                               const int  theNbPnts)
    : Select3D_SensitivePoly(theOwnerId,
                             !theIsFilled,
                             GetCircleNbPoints(theCircle, theNbPnts, theU1, theU2, theIsFilled))
{
  mySensType = theIsFilled ? Select3D_TOS_INTERIOR : Select3D_TOS_BOUNDARY;

  if (myPolyg.Size() != 1)
  {
    initCircle(myPolyg,
               theCircle,
               std::min(theU1, theU2),
               std::max(theU1, theU2),
               theIsFilled,
               theNbPnts);
  }
  else
  {
    myPolyg.SetPnt(0, theCircle.Position().Location());
  }

  if (!theIsFilled)
  {
    SetSensitivityFactor(6);
  }
}

bool Select3D_SensitivePoly::Matches(SelectBasics_SelectingVolumeManager& theMgr,
                                     SelectBasics_PickResult&             thePickResult)
{
  if (mySensType == Select3D_TOS_BOUNDARY)
  {
    if (!Select3D_SensitiveSet::Matches(theMgr, thePickResult))
    {
      return false;
    }
  }
  else if (mySensType == Select3D_TOS_INTERIOR)
  {
    occ::handle<NCollection_HArray1<gp_Pnt>> anArrayOfPnt;
    Points3D(anArrayOfPnt);
    if (!theMgr.IsOverlapAllowed())
    {
      if (theMgr.GetActiveSelectionType() == SelectMgr_SelectionType_Polyline)
      {
        SelectBasics_PickResult aDummy;
        return theMgr.OverlapsPolygon(anArrayOfPnt->Array1(), mySensType, aDummy);
      }
      for (int aPntIdx = anArrayOfPnt->Lower(); aPntIdx <= anArrayOfPnt->Upper(); ++aPntIdx)
      {
        if (!theMgr.OverlapsPoint(anArrayOfPnt->Value(aPntIdx)))
        {
          return false;
        }
      }
      return true;
    }

    if (!theMgr.OverlapsPolygon(anArrayOfPnt->Array1(), Select3D_TOS_INTERIOR, thePickResult))
    {
      return false;
    }
    thePickResult.SetDistToGeomCenter(distanceToCOG(theMgr));
  }

  return true;
}

Select3D_BndBox3d Select3D_SensitivePoly::BoundingBox()
{
  if (myBndBox.IsValid())
    return myBndBox;

  Select3D_BndBox3d aBndBox;
  for (int aPntIter = 0; aPntIter < myPolyg.Size(); ++aPntIter)
  {
    NCollection_Vec3<double> aPnt(myPolyg.Pnt(aPntIter).x,
                                  myPolyg.Pnt(aPntIter).y,
                                  myPolyg.Pnt(aPntIter).z);
    aBndBox.Add(aPnt);
  }

  myBndBox = aBndBox;

  return myBndBox;
}

int Select3D_SensitivePoly::Size() const
{
  if (!mySegmentIndexes.IsNull())
    return mySegmentIndexes->Length();

  return -1;
}

Select3D_BndBox3d Select3D_SensitivePoly::Box(const int theIdx) const
{
  if (mySegmentIndexes.IsNull())
    return Select3D_BndBox3d(NCollection_Vec3<double>(RealLast()));

  const int aSegmentIdx = mySegmentIndexes->Value(theIdx);
  gp_Pnt    aPnt1       = myPolyg.Pnt3d(aSegmentIdx);
  gp_Pnt    aPnt2       = myPolyg.Pnt3d(aSegmentIdx + 1);

  const NCollection_Vec3<double> aMinPnt(std::min(aPnt1.X(), aPnt2.X()),
                                         std::min(aPnt1.Y(), aPnt2.Y()),
                                         std::min(aPnt1.Z(), aPnt2.Z()));
  const NCollection_Vec3<double> aMaxPnt(std::max(aPnt1.X(), aPnt2.X()),
                                         std::max(aPnt1.Y(), aPnt2.Y()),
                                         std::max(aPnt1.Z(), aPnt2.Z()));

  return Select3D_BndBox3d(aMinPnt, aMaxPnt);
}

double Select3D_SensitivePoly::Center(const int theIdx, const int theAxis) const
{
  if (mySegmentIndexes.IsNull())
    return RealLast();

  const Select3D_BndBox3d        aBndBox = Box(theIdx);
  const NCollection_Vec3<double> aCenter = (aBndBox.CornerMin() + aBndBox.CornerMax()) * 0.5;
  return theAxis == 0 ? aCenter.x() : (theAxis == 1 ? aCenter.y() : aCenter.z());
}

void Select3D_SensitivePoly::Swap(const int theIdx1, const int theIdx2)
{
  if (mySegmentIndexes.IsNull())
    return;

  const int aSegmentIdx1                 = mySegmentIndexes->Value(theIdx1);
  const int aSegmentIdx2                 = mySegmentIndexes->Value(theIdx2);
  mySegmentIndexes->ChangeValue(theIdx1) = aSegmentIdx2;
  mySegmentIndexes->ChangeValue(theIdx2) = aSegmentIdx1;
}

bool Select3D_SensitivePoly::overlapsElement(SelectBasics_PickResult&             thePickResult,
                                             SelectBasics_SelectingVolumeManager& theMgr,
                                             int                                  theElemIdx,
                                             bool                                 theIsFullInside)
{
  if (mySegmentIndexes.IsNull())
  {
    return false;
  }
  else if (theIsFullInside)
  {
    return true;
  }

  const int aSegmentIdx = mySegmentIndexes->Value(theElemIdx);
  gp_Pnt    aPnt1       = myPolyg.Pnt3d(aSegmentIdx);
  gp_Pnt    aPnt2       = myPolyg.Pnt3d(aSegmentIdx + 1);
  return theMgr.OverlapsSegment(aPnt1, aPnt2, thePickResult);
}

bool Select3D_SensitivePoly::elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                                             int                                  theElemIdx,
                                             bool                                 theIsFullInside)
{
  if (theIsFullInside)
  {
    return true;
  }

  const int aSegmentIdx = mySegmentIndexes->Value(theElemIdx);
  if (theMgr.GetActiveSelectionType() == SelectMgr_SelectionType_Polyline)
  {
    SelectBasics_PickResult aDummy;
    return theMgr.OverlapsSegment(myPolyg.Pnt3d(aSegmentIdx + 0),
                                  myPolyg.Pnt3d(aSegmentIdx + 1),
                                  aDummy);
  }
  return theMgr.OverlapsPoint(myPolyg.Pnt3d(aSegmentIdx + 0))
         && theMgr.OverlapsPoint(myPolyg.Pnt3d(aSegmentIdx + 1));
}

double Select3D_SensitivePoly::distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr)
{
  if (!myIsComputed)
  {
    gp_XYZ aCenter(0.0, 0.0, 0.0);
    for (int aIdx = 0; aIdx < myPolyg.Size(); ++aIdx)
    {
      aCenter += myPolyg.Pnt(aIdx);
    }
    myCOG        = aCenter / myPolyg.Size();
    myIsComputed = true;
  }

  return theMgr.DistToGeometryCenter(myCOG);
}

int Select3D_SensitivePoly::NbSubElements() const
{
  return myPolyg.Size();
}

gp_Pnt Select3D_SensitivePoly::CenterOfGeometry() const
{
  if (!myIsComputed)
  {
    gp_XYZ aCenter(0.0, 0.0, 0.0);
    for (int aIdx = 0; aIdx < myPolyg.Size(); ++aIdx)
    {
      aCenter += myPolyg.Pnt(aIdx);
    }
    myCOG        = aCenter / myPolyg.Size();
    myIsComputed = true;
  }

  return myCOG;
}

void Select3D_SensitivePoly::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Select3D_SensitiveSet)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myBndBox)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsComputed)
}
