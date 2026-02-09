#pragma once

#include <Select3D_SensitivePoly.hpp>
#include <Select3D_SensitiveSet.hpp>

class SelectMgr_EntityOwner;

class Select3D_InteriorSensitivePointSet : public Select3D_SensitiveSet
{
public:
  Standard_EXPORT Select3D_InteriorSensitivePointSet(
    const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
    const NCollection_Array1<gp_Pnt>&         thePoints);

  Standard_EXPORT virtual void GetPoints(occ::handle<NCollection_HArray1<gp_Pnt>>& theHArrayOfPnt);

  Standard_EXPORT int Size() const override;

  Standard_EXPORT Select3D_BndBox3d Box(const int theIdx) const override;

  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Select3D_InteriorSensitivePointSet, Select3D_SensitiveSet)

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
  NCollection_Vector<occ::handle<Select3D_SensitivePoly>> myPlanarPolygons;
  occ::handle<NCollection_HArray1<int>>                   myPolygonsIdxs;
  gp_Pnt                                                  myCOG;
  Select3D_BndBox3d                                       myBndBox;
};
