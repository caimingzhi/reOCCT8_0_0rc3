#pragma once

#include <Select3D_SensitivePoly.hpp>
#include <Select3D_SensitiveSet.hpp>

class SelectMgr_EntityOwner;

//! This class handles the selection of arbitrary point set with internal type of sensitivity.
//! The main principle is to split the point set given onto planar convex polygons and search
//! for the overlap with one or more of them through traverse of BVH tree.
class Select3D_InteriorSensitivePointSet : public Select3D_SensitiveSet
{
public:
  //! Splits the given point set thePoints onto planar convex polygons
  Standard_EXPORT Select3D_InteriorSensitivePointSet(
    const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
    const NCollection_Array1<gp_Pnt>&         thePoints);

  //! Initializes the given array theHArrayOfPnt by 3d coordinates of vertices of the
  //! whole point set
  Standard_EXPORT virtual void GetPoints(occ::handle<NCollection_HArray1<gp_Pnt>>& theHArrayOfPnt);

  //! Returns the length of vector of planar convex polygons
  Standard_EXPORT int Size() const override;

  //! Returns bounding box of planar convex polygon with index theIdx
  Standard_EXPORT Select3D_BndBox3d Box(const int theIdx) const override;

  //! Returns geometry center of planar convex polygon with index
  //! theIdx in the vector along the given axis theAxis
  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  //! Swaps items with indexes theIdx1 and theIdx2 in the vector
  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  //! Returns bounding box of the point set. If location
  //! transformation is set, it will be applied
  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  //! Returns center of the point set. If location
  //! transformation is set, it will be applied
  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  //! Returns the amount of points in set
  Standard_EXPORT int NbSubElements() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Select3D_InteriorSensitivePointSet, Select3D_SensitiveSet)

protected:
  //! Checks whether the planar convex polygon with index theIdx
  //! in myPlanarPolygons overlaps the current selecting volume
  Standard_EXPORT bool overlapsElement(SelectBasics_PickResult&             thePickResult,
                                       SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  //! Checks whether the entity with index theIdx is inside the current selecting volume
  Standard_EXPORT bool elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  //! Calculates distance from the 3d projection of used-picked
  //! screen point to center of the geometry
  Standard_EXPORT double distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr) override;

protected:
  NCollection_Vector<occ::handle<Select3D_SensitivePoly>>
                                        myPlanarPolygons; //!< Vector of planar polygons
  occ::handle<NCollection_HArray1<int>> myPolygonsIdxs;   //!< Indexes array for BVH calculation
  gp_Pnt                                myCOG;            //!< Center of the point set
  Select3D_BndBox3d                     myBndBox;         //!< Bounding box of the point set
};
