#pragma once

#include <OSD_Chronometer.hpp>
#include <SelectMgr_BVHThreadPool.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_SortCriterion.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <SelectMgr_SelectingVolumeManager.hpp>
#include <SelectMgr_Selection.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <SelectMgr_SelectableObjectSet.hpp>
#include <SelectMgr_StateOfSelection.hpp>
#include <SelectMgr_ToleranceMap.hpp>

enum SelectMgr_TypeOfDepthTolerance
{
  SelectMgr_TypeOfDepthTolerance_Uniform,

  SelectMgr_TypeOfDepthTolerance_UniformPixels,

  SelectMgr_TypeOfDepthTolerance_SensitivityFactor,
};

#include <Standard_OStream.hpp>
#include <Standard_Transient.hpp>
#include <StdSelect_TypeOfSelectionImage.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class SelectMgr_SensitiveEntitySet;
class SelectMgr_EntityOwner;
class Select3D_SensitiveEntity;
class V3d_View;

#ifdef Status
  #undef Status
#endif

class SelectMgr_ViewerSelector : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(SelectMgr_ViewerSelector, Standard_Transient)
  friend class SelectMgr_SelectionManager;

public:
  Standard_EXPORT SelectMgr_ViewerSelector();

  int CustomPixelTolerance() const { return myTolerances.CustomTolerance(); }

  Standard_EXPORT void SetPixelTolerance(const int theTolerance);

  double Sensitivity() const { return myTolerances.Tolerance(); }

  int PixelTolerance() const { return myTolerances.Tolerance(); }

  Standard_EXPORT virtual void SortResult() const;

  occ::handle<SelectMgr_EntityOwner> OnePicked() const
  {
    return mystored.IsEmpty() ? occ::handle<SelectMgr_EntityOwner>() : Picked(1);
  }

  bool ToPickClosest() const { return myToPreferClosest; }

  void SetPickClosest(bool theToPreferClosest) { myToPreferClosest = theToPreferClosest; }

  SelectMgr_TypeOfDepthTolerance DepthToleranceType() const { return myDepthTolType; }

  double DepthTolerance() const { return myDepthTolerance; }

  void SetDepthTolerance(SelectMgr_TypeOfDepthTolerance theType, double theTolerance)
  {
    myDepthTolType   = theType;
    myDepthTolerance = theTolerance;
  }

  int NbPicked() const { return mystored.Extent(); }

  Standard_EXPORT void ClearPicked();

  void Clear() { ClearPicked(); }

  Standard_EXPORT occ::handle<SelectMgr_EntityOwner> Picked(const int theRank) const;

  Standard_EXPORT const SelectMgr_SortCriterion& PickedData(const int theRank) const;

  const occ::handle<Select3D_SensitiveEntity>& PickedEntity(const int theRank) const
  {
    return PickedData(theRank).Entity;
  }

  gp_Pnt PickedPoint(const int theRank) const { return PickedData(theRank).Point; }

  Standard_EXPORT bool RemovePicked(const occ::handle<SelectMgr_SelectableObject>& theObject);

  Standard_EXPORT bool Contains(const occ::handle<SelectMgr_SelectableObject>& theObject) const;

  const occ::handle<Select3D_BVHBuilder3d> EntitySetBuilder() { return myEntitySetBuilder; }

  Standard_EXPORT void SetEntitySetBuilder(const occ::handle<Select3D_BVHBuilder3d>& theBuilder);

  Standard_EXPORT bool Modes(
    const occ::handle<SelectMgr_SelectableObject>& theSelectableObject,
    NCollection_List<int>&                         theModeList,
    const SelectMgr_StateOfSelection               theWantedState = SelectMgr_SOS_Any) const;

  Standard_EXPORT bool IsActive(const occ::handle<SelectMgr_SelectableObject>& theSelectableObject,
                                const int                                      theMode) const;

  Standard_EXPORT bool IsInside(const occ::handle<SelectMgr_SelectableObject>& theSelectableObject,
                                const int                                      theMode) const;

  Standard_EXPORT SelectMgr_StateOfSelection
    Status(const occ::handle<SelectMgr_Selection>& theSelection) const;

  Standard_EXPORT TCollection_AsciiString
    Status(const occ::handle<SelectMgr_SelectableObject>& theSelectableObject) const;

  Standard_EXPORT void ActiveOwners(
    NCollection_List<occ::handle<SelectMgr_EntityOwner>>& theOwners) const;

  Standard_EXPORT void AddSelectableObject(
    const occ::handle<SelectMgr_SelectableObject>& theObject);

  Standard_EXPORT void AddSelectionToObject(
    const occ::handle<SelectMgr_SelectableObject>& theObject,
    const occ::handle<SelectMgr_Selection>&        theSelection);

  Standard_EXPORT void MoveSelectableObject(
    const occ::handle<SelectMgr_SelectableObject>& theObject);

  Standard_EXPORT void RemoveSelectableObject(
    const occ::handle<SelectMgr_SelectableObject>& theObject);

  Standard_EXPORT void RemoveSelectionOfObject(
    const occ::handle<SelectMgr_SelectableObject>& theObject,
    const occ::handle<SelectMgr_Selection>&        theSelection);

  Standard_EXPORT void RebuildObjectsTree(const bool theIsForce = false);

  Standard_EXPORT void RebuildSensitivesTree(
    const occ::handle<SelectMgr_SelectableObject>& theObject,
    const bool                                     theIsForce = false);

  SelectMgr_SelectingVolumeManager& GetManager() { return mySelectingVolumeMgr; }

  const SelectMgr_SelectableObjectSet& SelectableObjects() const { return mySelectableObjects; }

  Standard_EXPORT void ResetSelectionActivationStatus();

  Standard_EXPORT void AllowOverlapDetection(const bool theIsToAllow);

public:
  Standard_EXPORT void Pick(const int                    theXPix,
                            const int                    theYPix,
                            const occ::handle<V3d_View>& theView);

  Standard_EXPORT void Pick(const int                    theXPMin,
                            const int                    theYPMin,
                            const int                    theXPMax,
                            const int                    theYPMax,
                            const occ::handle<V3d_View>& theView);

  Standard_EXPORT void Pick(const NCollection_Array1<gp_Pnt2d>& thePolyline,
                            const occ::handle<V3d_View>&        theView);

  Standard_EXPORT void Pick(const gp_Ax1& theAxis, const occ::handle<V3d_View>& theView);

  Standard_EXPORT bool ToPixMap(Image_PixMap&                        theImage,
                                const occ::handle<V3d_View>&         theView,
                                const StdSelect_TypeOfSelectionImage theType,
                                const int                            thePickedIndex = 1);

public:
  Standard_EXPORT void DisplaySensitive(const occ::handle<V3d_View>& theView);

  Standard_EXPORT void ClearSensitive(const occ::handle<V3d_View>& theView);

  Standard_EXPORT void DisplaySensitive(const occ::handle<SelectMgr_Selection>& theSel,
                                        const gp_Trsf&                          theTrsf,
                                        const occ::handle<V3d_View>&            theView,
                                        const bool theToClearOthers = true);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  Standard_EXPORT void SetToPrebuildBVH(bool theToPrebuild, int theThreadsNum = -1);

  Standard_EXPORT void QueueBVHBuild(const occ::handle<Select3D_SensitiveEntity>& theEntity);

  Standard_EXPORT void WaitForBVHBuild();

  bool ToPrebuildBVH() const { return myToPrebuildBVH; }

protected:
  Standard_EXPORT void TraverseSensitives(const int theViewId = -1);

  Standard_EXPORT void traverseObject(const occ::handle<SelectMgr_SelectableObject>& theObject,
                                      const SelectMgr_SelectingVolumeManager&        theMgr,
                                      const occ::handle<Graphic3d_Camera>&           theCamera,
                                      const NCollection_Mat4<double>& theProjectionMat,
                                      const NCollection_Mat4<double>& theWorldViewMat,
                                      const NCollection_Vec2<int>&    theWinSize);

  Standard_EXPORT void checkOverlap(const occ::handle<Select3D_SensitiveEntity>& theEntity,
                                    const gp_GTrsf&                              theInversedTrsf,
                                    SelectMgr_SelectingVolumeManager&            theMgr);

  Standard_EXPORT void updateZLayers(const occ::handle<V3d_View>& theView);

private:
  bool isToScaleFrustum(const occ::handle<Select3D_SensitiveEntity>& theEntity);

  int sensitivity(const occ::handle<Select3D_SensitiveEntity>& theEntity) const;

  void Activate(const occ::handle<SelectMgr_Selection>& theSelection);

  void Deactivate(const occ::handle<SelectMgr_Selection>& theSelection);

  void Remove(const occ::handle<SelectMgr_Selection>& aSelection);

  void computeFrustum(const occ::handle<Select3D_SensitiveEntity>&                theEnt,
                      const SelectMgr_SelectingVolumeManager&                     theMgrGlobal,
                      const SelectMgr_SelectingVolumeManager&                     theMgrObject,
                      const gp_GTrsf&                                             theInvTrsf,
                      NCollection_DataMap<int, SelectMgr_SelectingVolumeManager>& theCachedMgrs,
                      SelectMgr_SelectingVolumeManager&                           theResMgr);

private:
  void updatePoint3d(SelectMgr_SortCriterion&                     theCriterion,
                     const SelectBasics_PickResult&               thePickResult,
                     const occ::handle<Select3D_SensitiveEntity>& theEntity,
                     const gp_GTrsf&                              theInversedTrsf,
                     const SelectMgr_SelectingVolumeManager&      theMgr) const;

protected:
  double                         myDepthTolerance;
  SelectMgr_TypeOfDepthTolerance myDepthTolType;
  bool                           myToPreferClosest;
  NCollection_IndexedDataMap<occ::handle<SelectMgr_EntityOwner>, SelectMgr_SortCriterion> mystored;
  SelectMgr_SelectingVolumeManager             mySelectingVolumeMgr;
  mutable SelectMgr_SelectableObjectSet        mySelectableObjects;
  SelectMgr_ToleranceMap                       myTolerances;
  NCollection_DataMap<Graphic3d_ZLayerId, int> myZLayerOrderMap;
  occ::handle<Select3D_BVHBuilder3d>           myEntitySetBuilder;
  gp_Pnt                                       myCameraEye;
  gp_Dir                                       myCameraDir;
  double                                       myCameraScale;

  bool                                 myToPrebuildBVH;
  occ::handle<SelectMgr_BVHThreadPool> myBVHThreadPool;

  mutable NCollection_Array1<int> myIndexes;
  mutable bool                    myIsSorted;
  bool                            myIsLeftChildQueuedFirst;
  NCollection_DataMap<occ::handle<SelectMgr_SelectableObject>,
                      occ::handle<SelectMgr_SensitiveEntitySet>>
    myMapOfObjectSensitives;

  NCollection_Sequence<occ::handle<Graphic3d_Structure>> myStructs;
};
