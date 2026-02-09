#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Select3D_SensitiveSet.hpp>

class Poly_Triangle;
class Poly_Triangulation;

class Select3D_SensitiveTriangulation : public Select3D_SensitiveSet
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveTriangulation, Select3D_SensitiveSet)
public:
  Standard_EXPORT Select3D_SensitiveTriangulation(
    const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
    const occ::handle<Poly_Triangulation>&    theTrg,
    const TopLoc_Location&                    theInitLoc,
    const bool                                theIsInterior = true);

  Standard_EXPORT Select3D_SensitiveTriangulation(
    const occ::handle<SelectMgr_EntityOwner>&    theOwnerId,
    const occ::handle<Poly_Triangulation>&       theTrg,
    const TopLoc_Location&                       theInitLoc,
    const occ::handle<NCollection_HArray1<int>>& theFreeEdges,
    const gp_Pnt&                                theCOG,
    const bool                                   theIsInterior);

public:
  Standard_EXPORT bool LastDetectedTriangle(Poly_Triangle& theTriangle) const;

  Standard_EXPORT bool LastDetectedTriangle(Poly_Triangle& theTriangle,
                                            gp_Pnt         theTriNodes[3]) const;

  int LastDetectedTriangleIndex() const
  {
    return (myDetectedIdx != -1 && mySensType == Select3D_TOS_INTERIOR
            && !myBVHPrimIndexes.IsNull())
             ? myBVHPrimIndexes->Value(myDetectedIdx) + 1
             : -1;
  }

public:
  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  const occ::handle<Poly_Triangulation>& Triangulation() const { return myTriangul; }

  Standard_EXPORT int Size() const override;

  Standard_EXPORT Select3D_BndBox3d Box(const int theIdx) const override;

  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT bool HasInitLocation() const override;

  Standard_EXPORT gp_GTrsf InvInitLocation() const override;

  const TopLoc_Location& GetInitLocation() const { return myInitLocation; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

protected:
  void computeBoundingBox();

  Select3D_BndBox3d applyTransformation();

private:
  Standard_EXPORT bool overlapsElement(SelectBasics_PickResult&             thePickResult,
                                       SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  Standard_EXPORT double distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr) override;

  Standard_EXPORT bool elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

protected:
  occ::handle<Poly_Triangulation>       myTriangul;
  TopLoc_Location                       myInitLocation;
  gp_Pnt                                myCDG3D;
  occ::handle<NCollection_HArray1<int>> myFreeEdges;

  bool                                  mySensType;
  int                                   myPrimitivesNb;
  occ::handle<NCollection_HArray1<int>> myBVHPrimIndexes;
  mutable Select3D_BndBox3d             myBndBox;

  gp_GTrsf myInvInitLocation;
};
