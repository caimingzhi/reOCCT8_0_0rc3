#include <gp_XYZ.hpp>

#include <Select3D_InteriorSensitivePointSet.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_InteriorSensitivePointSet, Select3D_SensitiveSet)

namespace
{

  class Select3D_Plane
  {
  public:
    Select3D_Plane()
        : myPlane(0.0),
          myIsInitialized(false)
    {
    }

    bool Contains(const gp_Pnt& thePnt) const
    {
      if (!myIsInitialized)
        return false;

      double aRes = myPlane.x() * thePnt.X() + myPlane.y() * thePnt.Y() + myPlane.z() * thePnt.Z()
                    + myPlane.w();

      return aRes < Precision::Confusion();
    }

    void MakePlane(const gp_Pnt& thePnt1, const gp_Pnt& thePnt2, const gp_Pnt& thePnt3)
    {
      const gp_XYZ& aVec1 = thePnt2.XYZ() - thePnt1.XYZ();
      const gp_XYZ& aVec2 = thePnt3.XYZ() - thePnt1.XYZ();
      const gp_XYZ& aDir  = aVec1.Crossed(aVec2);
      double        aD    = aDir.Dot(thePnt1.XYZ().Reversed());
      myPlane             = NCollection_Vec4<double>(aDir.X(), aDir.Y(), aDir.Z(), aD);
      myIsInitialized     = true;
    }

    void Invalidate() { myIsInitialized = false; }

    bool IsValid() const { return myIsInitialized; }

  private:
    NCollection_Vec4<double> myPlane;
    bool                     myIsInitialized;
  };

} // namespace

Select3D_InteriorSensitivePointSet::Select3D_InteriorSensitivePointSet(
  const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
  const NCollection_Array1<gp_Pnt>&         thePoints)
    : Select3D_SensitiveSet(theOwnerId)
{
  Select3D_Plane    aPlane;
  int               aLowerIdx  = thePoints.Lower();
  int               anUpperIdx = thePoints.Upper();
  int               aStartIdx = aLowerIdx, anEndIdx = 0;
  Select3D_BndBox3d aBndBox;
  gp_XYZ            aPntSum(0.0, 0.0, 0.0);
  for (int aPntIter = aLowerIdx; aPntIter <= anUpperIdx; ++aPntIter)
  {
    gp_Pnt        aPnt1, aPnt2;
    const gp_Pnt& aPnt3 = thePoints.Value(aPntIter);
    aPntSum += aPnt3.XYZ();
    NCollection_Vec3<double> aCurrPnt(aPnt3.X(), aPnt3.Y(), aPnt3.Z());
    aBndBox.Add(aCurrPnt);
    if (aPntIter - aLowerIdx >= 2)
    {
      aPnt1 = thePoints.Value(aPntIter - 2);
      aPnt2 = thePoints.Value(aPntIter - 1);
    }
    if (aPntIter - aStartIdx == 2 && !aPlane.IsValid())
    {
      aPlane.MakePlane(aPnt1, aPnt2, aPnt3);
      aStartIdx = aPntIter - 2;
      anEndIdx  = aPntIter;

      if (anEndIdx == anUpperIdx)
      {
        occ::handle<NCollection_HArray1<gp_Pnt>> aPointsArray =
          new NCollection_HArray1<gp_Pnt>(0, anEndIdx - aStartIdx);
        for (int aIdx = aStartIdx; aIdx <= anEndIdx; ++aIdx)
        {
          aPointsArray->SetValue(aIdx - aStartIdx, thePoints.Value(aIdx));
        }
        occ::handle<Select3D_SensitivePoly> aPlanarPolyg =
          new Select3D_SensitivePoly(theOwnerId, aPointsArray, false);
        myPlanarPolygons.Append(aPlanarPolyg);
      }
    }
    else if (aPlane.IsValid())
    {
      const gp_XYZ& aVec1   = aPnt1.XYZ() - aPnt2.XYZ();
      const gp_XYZ& aVec2   = aPnt3.XYZ() - aPnt2.XYZ();
      double        anAngle = aVec1.Dot(aVec2);
      if (!aPlane.Contains(thePoints.Value(aPntIter)) || anAngle > Precision::Confusion())
      {

        int                                      anUpperBound = aPntIter - aStartIdx - 1;
        occ::handle<NCollection_HArray1<gp_Pnt>> aPointsArray =
          new NCollection_HArray1<gp_Pnt>(0, anUpperBound);
        for (int aIdx = aStartIdx; aIdx <= aStartIdx + anUpperBound; ++aIdx)
        {
          aPointsArray->SetValue(aIdx - aStartIdx, thePoints.Value(aIdx));
        }
        occ::handle<Select3D_SensitivePoly> aPlanarPolyg =
          new Select3D_SensitivePoly(theOwnerId, aPointsArray, true);
        myPlanarPolygons.Append(aPlanarPolyg);
        aStartIdx = aPntIter;
        anEndIdx  = aPntIter;
        aPlane.Invalidate();
      }
      else
      {
        anEndIdx++;
        if (anEndIdx == anUpperIdx)
        {
          occ::handle<NCollection_HArray1<gp_Pnt>> aPointsArray =
            new NCollection_HArray1<gp_Pnt>(0, anEndIdx - aStartIdx);
          for (int aIdx = aStartIdx; aIdx <= anEndIdx; ++aIdx)
          {
            aPointsArray->SetValue(aIdx - aStartIdx, thePoints.Value(aIdx));
          }
          occ::handle<Select3D_SensitivePoly> aPlanarPolyg =
            new Select3D_SensitivePoly(theOwnerId, aPointsArray, true);
          myPlanarPolygons.Append(aPlanarPolyg);
        }
      }
    }
  }

  myCOG    = aPntSum / thePoints.Length();
  myBndBox = aBndBox;

  myPolygonsIdxs = new NCollection_HArray1<int>(0, myPlanarPolygons.Length() - 1);
  for (int aIdx = 0; aIdx < myPlanarPolygons.Length(); ++aIdx)
  {
    myPolygonsIdxs->SetValue(aIdx, aIdx);
  }
}

void Select3D_InteriorSensitivePointSet::GetPoints(
  occ::handle<NCollection_HArray1<gp_Pnt>>& theHArrayOfPnt)
{
  int aSize = 0;
  for (int anIdx = 0; anIdx < myPlanarPolygons.Length(); ++anIdx)
  {
    const occ::handle<Select3D_SensitivePoly>& aPolygon = myPlanarPolygons.Value(anIdx);
    aSize += aPolygon->NbSubElements();
  }

  theHArrayOfPnt          = new NCollection_HArray1<gp_Pnt>(1, aSize);
  int anOutputPntArrayIdx = 1;

  for (int aPolygIdx = 0; aPolygIdx < myPlanarPolygons.Length(); ++aPolygIdx)
  {
    const occ::handle<Select3D_SensitivePoly>& aPolygon = myPlanarPolygons.Value(aPolygIdx);
    occ::handle<NCollection_HArray1<gp_Pnt>>   aPoints;
    aPolygon->Points3D(aPoints);
    int anUpper =
      aPolygIdx < myPlanarPolygons.Length() - 1 ? aPoints->Upper() : aPoints->Upper() + 1;
    for (int aPntIter = 1; aPntIter < anUpper; ++aPntIter)
    {
      theHArrayOfPnt->SetValue(anOutputPntArrayIdx, aPoints->Value(aPntIter));
      anOutputPntArrayIdx++;
    }
    aPoints.Nullify();
  }
}

int Select3D_InteriorSensitivePointSet::Size() const
{
  return myPlanarPolygons.Length();
}

Select3D_BndBox3d Select3D_InteriorSensitivePointSet::Box(const int theIdx) const
{
  int aPolygIdx = myPolygonsIdxs->Value(theIdx);
  return myPlanarPolygons.Value(aPolygIdx)->BoundingBox();
}

double Select3D_InteriorSensitivePointSet::Center(const int theIdx, const int theAxis) const
{
  const int    aPolygIdx = myPolygonsIdxs->Value(theIdx);
  const gp_Pnt aCOG      = myPlanarPolygons.Value(aPolygIdx)->CenterOfGeometry();
  return aCOG.Coord(theAxis - 1);
}

void Select3D_InteriorSensitivePointSet::Swap(const int theIdx1, const int theIdx2)
{
  int aPolygIdx1 = myPolygonsIdxs->Value(theIdx1);
  int aPolygIdx2 = myPolygonsIdxs->Value(theIdx2);

  myPolygonsIdxs->ChangeValue(theIdx1) = aPolygIdx2;
  myPolygonsIdxs->ChangeValue(theIdx2) = aPolygIdx1;
}

bool Select3D_InteriorSensitivePointSet::overlapsElement(
  SelectBasics_PickResult&             thePickResult,
  SelectBasics_SelectingVolumeManager& theMgr,
  int                                  theElemIdx,
  bool)
{
  int                                        aPolygIdx = myPolygonsIdxs->Value(theElemIdx);
  const occ::handle<Select3D_SensitivePoly>& aPolygon  = myPlanarPolygons.Value(aPolygIdx);
  occ::handle<NCollection_HArray1<gp_Pnt>>   aPoints;
  aPolygon->Points3D(aPoints);
  return theMgr.OverlapsPolygon(aPoints->Array1(), Select3D_TOS_INTERIOR, thePickResult);
}

bool Select3D_InteriorSensitivePointSet::elementIsInside(
  SelectBasics_SelectingVolumeManager& theMgr,
  int                                  theElemIdx,
  bool                                 theIsFullInside)
{
  SelectBasics_PickResult aDummy;
  return overlapsElement(aDummy, theMgr, theElemIdx, theIsFullInside);
}

double Select3D_InteriorSensitivePointSet::distanceToCOG(
  SelectBasics_SelectingVolumeManager& theMgr)
{
  return theMgr.DistToGeometryCenter(myCOG);
}

Select3D_BndBox3d Select3D_InteriorSensitivePointSet::BoundingBox()
{
  return myBndBox;
}

gp_Pnt Select3D_InteriorSensitivePointSet::CenterOfGeometry() const
{
  return myCOG;
}

int Select3D_InteriorSensitivePointSet::NbSubElements() const
{
  return myPlanarPolygons.Length();
}

void Select3D_InteriorSensitivePointSet::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Select3D_SensitiveSet)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myBndBox)
}
