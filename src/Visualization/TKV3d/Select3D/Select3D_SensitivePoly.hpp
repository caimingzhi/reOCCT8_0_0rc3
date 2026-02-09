#pragma once

#include <gp_Circ.hpp>

#include <gp_Pnt.hpp>

struct Select3D_Pnt
{
  float x, y, z;

  operator gp_Pnt() const { return gp_Pnt(x, y, z); }

  operator gp_XYZ() const { return gp_XYZ(x, y, z); }

  gp_Pnt operator=(const gp_Pnt& thePnt)
  {
    x = RealToShortReal(thePnt.X());
    y = RealToShortReal(thePnt.Y());
    z = RealToShortReal(thePnt.Z());
    return *this;
  }
};

class Select3D_PointData
{

public:
  Select3D_PointData(const int theNbPoints)
      : mynbpoints(theNbPoints)
  {
    if (theNbPoints <= 0)
      throw Standard_ConstructionError("Select3D_PointData");

    mypolyg3d = new Select3D_Pnt[mynbpoints];
  }

  ~Select3D_PointData() { delete[] mypolyg3d; }

  void SetPnt(const int theIndex, const Select3D_Pnt& theValue)
  {
    if (theIndex < 0 || theIndex >= mynbpoints)
      throw Standard_OutOfRange("Select3D_PointData::SetPnt");
    mypolyg3d[theIndex] = theValue;
  }

  void SetPnt(const int theIndex, const gp_Pnt& theValue)
  {
    if (theIndex < 0 || theIndex >= mynbpoints)
      throw Standard_OutOfRange("Select3D_PointData::SetPnt");
    mypolyg3d[theIndex] = theValue;
  }

  const Select3D_Pnt& Pnt(const int theIndex) const
  {
    if (theIndex < 0 || theIndex >= mynbpoints)
      throw Standard_OutOfRange("Select3D_PointData::Pnt");
    return mypolyg3d[theIndex];
  }

  gp_Pnt Pnt3d(const int theIndex) const
  {
    if (theIndex < 0 || theIndex >= mynbpoints)
      throw Standard_OutOfRange("Select3D_PointData::Pnt");
    return mypolyg3d[theIndex];
  }

  int Size() const { return mynbpoints; }

private:
  Select3D_PointData(const Select3D_PointData&)            = delete;
  Select3D_PointData& operator=(const Select3D_PointData&) = delete;

private:
  Select3D_Pnt* mypolyg3d;
  int           mynbpoints;
};

#include <Select3D_SensitiveSet.hpp>
#include <Select3D_TypeOfSensitivity.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>

class Select3D_SensitivePoly : public Select3D_SensitiveSet
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitivePoly, Select3D_SensitiveSet)
public:
  Standard_EXPORT Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                         const NCollection_Array1<gp_Pnt>&         thePoints,
                                         const bool                                theIsBVHEnabled);

  Standard_EXPORT Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>&       theOwnerId,
                                         const occ::handle<NCollection_HArray1<gp_Pnt>>& thePoints,
                                         const bool theIsBVHEnabled);

  Standard_EXPORT Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                         const gp_Circ&                            theCircle,
                                         const double                              theU1,
                                         const double                              theU2,
                                         const bool theIsFilled = false,
                                         const int  theNbPnts   = 12);

  Standard_EXPORT Select3D_SensitivePoly(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                         const bool                                theIsBVHEnabled,
                                         const int                                 theNbPnts = 6);

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT int NbSubElements() const override;

  void Points3D(occ::handle<NCollection_HArray1<gp_Pnt>>& theHArrayOfPnt)
  {
    int aSize      = myPolyg.Size();
    theHArrayOfPnt = new NCollection_HArray1<gp_Pnt>(1, aSize);
    for (int anIndex = 1; anIndex <= aSize; anIndex++)
    {
      theHArrayOfPnt->SetValue(anIndex, myPolyg.Pnt(anIndex - 1));
    }
  }

  void ArrayBounds(int& theLow, int& theUp) const
  {
    theLow = 0;
    theUp  = myPolyg.Size() - 1;
  }

  gp_Pnt GetPoint3d(const int thePntIdx) const
  {
    return (thePntIdx >= 0 && thePntIdx < myPolyg.Size()) ? myPolyg.Pnt(thePntIdx) : gp_Pnt();
  }

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT int Size() const override;

  Standard_EXPORT Select3D_BndBox3d Box(const int theIdx) const override;

  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT bool overlapsElement(SelectBasics_PickResult&             thePickResult,
                                       SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  Standard_EXPORT bool elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  Standard_EXPORT double distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr) override;

protected:
  Select3D_PointData                    myPolyg;
  mutable gp_Pnt                        myCOG;
  occ::handle<NCollection_HArray1<int>> mySegmentIndexes;
  Select3D_BndBox3d                     myBndBox;

  Select3D_TypeOfSensitivity mySensType;
  mutable bool               myIsComputed;
};
