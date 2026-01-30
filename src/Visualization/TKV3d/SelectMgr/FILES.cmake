# Source files for SelectMgr package
set(OCCT_SelectMgr_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_SelectMgr_FILES
  SelectMgr.cxx
  SelectMgr.hpp
  SelectMgr_AndFilter.cxx
  SelectMgr_AndFilter.hpp
  SelectMgr_AndOrFilter.cxx
  SelectMgr_AndOrFilter.hpp
  SelectMgr_AxisIntersector.cxx
  SelectMgr_AxisIntersector.hpp
  SelectMgr_BaseIntersector.cxx
  SelectMgr_BaseIntersector.hpp
  SelectMgr_BaseFrustum.cxx
  SelectMgr_BaseFrustum.hpp
  SelectMgr_BVHThreadPool.cxx
  SelectMgr_BVHThreadPool.hpp
  SelectMgr_CompositionFilter.cxx
  SelectMgr_CompositionFilter.hpp
  SelectMgr_EntityOwner.cxx
  SelectMgr_EntityOwner.hpp
  SelectMgr_Filter.cxx
  SelectMgr_Filter.hpp
  SelectMgr_FilterType.hpp
  SelectMgr_Frustum.hpp
  SelectMgr_Frustum_1.hpp
  SelectMgr_FrustumBuilder.cxx
  SelectMgr_FrustumBuilder.hpp


  SelectMgr_OrFilter.cxx
  SelectMgr_OrFilter.hpp
  SelectMgr_PickingStrategy.hpp
  SelectMgr_RectangularFrustum.cxx
  SelectMgr_RectangularFrustum.hpp
  SelectMgr_SelectableObject.cxx
  SelectMgr_SelectableObject.hpp
  SelectMgr_SelectableObjectSet.cxx
  SelectMgr_SelectableObjectSet.hpp
  SelectMgr_SelectingVolumeManager.cxx
  SelectMgr_SelectingVolumeManager.hpp
  SelectMgr_Selection.cxx
  SelectMgr_Selection.hpp
  SelectMgr_SelectionImageFiller.cxx
  SelectMgr_SelectionImageFiller.hpp
  SelectMgr_SelectionManager.cxx
  SelectMgr_SelectionManager.hpp
  SelectMgr_SelectionType.hpp
  SelectMgr_SensitiveEntity.cxx
  SelectMgr_SensitiveEntity.hpp
  SelectMgr_SensitiveEntitySet.cxx
  SelectMgr_SensitiveEntitySet.hpp

  SelectMgr_SortCriterion.hpp
  SelectMgr_StateOfSelection.hpp
  SelectMgr_ToleranceMap.hpp
  SelectMgr_ToleranceMap.cxx
  SelectMgr_TriangularFrustum.cxx
  SelectMgr_TriangularFrustum.hpp
  SelectMgr_TriangularFrustumSet.cxx
  SelectMgr_TriangularFrustumSet.hpp
  SelectMgr_TypeOfBVHUpdate.hpp
  SelectMgr_TypeOfDepthTolerance.hpp
  SelectMgr_TypeOfUpdate.hpp

  SelectMgr_ViewClipRange.cxx
  SelectMgr_ViewClipRange.hpp
  SelectMgr_ViewerSelector.cxx
  SelectMgr_ViewerSelector.hpp

)
