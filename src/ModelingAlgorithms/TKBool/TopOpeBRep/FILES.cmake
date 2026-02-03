# Source files for TopOpeBRep package
set(OCCT_TopOpeBRep_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_TopOpeBRep_FILES
  FILES
  TopOpeBRep.cxx
  TopOpeBRep.hpp

  TopOpeBRep_Bipoint.cxx
  TopOpeBRep_Bipoint.hpp

  TopOpeBRep_define.hpp
  TopOpeBRep_DSFiller.cxx
  TopOpeBRep_DSFiller.hpp
  TopOpeBRep_EdgesFiller.cxx
  TopOpeBRep_EdgesFiller.hpp
  TopOpeBRep_EdgesIntersector.cxx
  TopOpeBRep_EdgesIntersector.hpp
  TopOpeBRep_EdgesIntersector_1.cxx
  TopOpeBRep_FaceEdgeFiller.cxx
  TopOpeBRep_FaceEdgeFiller.hpp
  TopOpeBRep_FaceEdgeFiller_DEB.cxx
  TopOpeBRep_FaceEdgeIntersector.cxx
  TopOpeBRep_FaceEdgeIntersector.hpp
  TopOpeBRep_FacesFiller.cxx
  TopOpeBRep_FacesFiller.hpp
  TopOpeBRep_FacesFiller_1.cxx
  TopOpeBRep_FacesIntersector.cxx
  TopOpeBRep_FacesIntersector.hpp
  TopOpeBRep_FFDumper.cxx
  TopOpeBRep_FFDumper.hpp
  TopOpeBRep_FFTransitionTool.cxx
  TopOpeBRep_FFTransitionTool.hpp
  TopOpeBRep_GeomTool.cxx
  TopOpeBRep_GeomTool.hpp

  TopOpeBRep_Hctxee2d.cxx
  TopOpeBRep_Hctxee2d.hpp
  TopOpeBRep_Hctxff2d.cxx
  TopOpeBRep_Hctxff2d.hpp
  TopOpeBRep_kpart.cxx
  TopOpeBRep_LineInter.cxx
  TopOpeBRep_LineInter.hpp

  TopOpeBRep_mergePDS.cxx
  TopOpeBRep_P2Dstatus.hpp
  
  TopOpeBRep_PLineInter.hpp
  TopOpeBRep_Point2d.cxx
  TopOpeBRep_Point2d.hpp
  TopOpeBRep_PointClassifier.cxx
  TopOpeBRep_PointClassifier.hpp
  TopOpeBRep_PointGeomTool.cxx
  TopOpeBRep_PointGeomTool.hpp
  TopOpeBRep_ProcessGR.cxx
  TopOpeBRep_ProcessSectionEdges.cxx

  TopOpeBRep_ShapeIntersector.cxx
  TopOpeBRep_ShapeIntersector.hpp
  TopOpeBRep_ShapeIntersector2d.cxx
  TopOpeBRep_ShapeIntersector2d.hpp
  TopOpeBRep_ShapeScanner.cxx
  TopOpeBRep_ShapeScanner.hpp
  TopOpeBRep_sort.cxx
  TopOpeBRep_trace.cxx
  TopOpeBRep_traceALWL.cxx
  TopOpeBRep_traceBOOPNINT.cxx
  TopOpeBRep_traceSIFF.cxx
  TopOpeBRep_traceSIFF.hpp
  TopOpeBRep_TypeLineCurve.hpp
  TopOpeBRep_VPointInter.cxx
  TopOpeBRep_VPointInter.hpp
  TopOpeBRep_VPointInterClassifier.cxx
  TopOpeBRep_VPointInterClassifier.hpp
  TopOpeBRep_VPointInterIterator.cxx
  TopOpeBRep_VPointInterIterator.hpp
  TopOpeBRep_vpr.cxx
  TopOpeBRep_vprclo.cxx
  TopOpeBRep_vprdeg.cxx
  TopOpeBRep_WPointInter.cxx
  TopOpeBRep_WPointInter.hpp
  TopOpeBRep_WPointInterIterator.cxx
  TopOpeBRep_WPointInterIterator.hpp
)
