#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <ShapeFix_Root.hpp>
#include <TopoDS_Wire.hpp>
#include <ShapeExtend_Status.hpp>
#include <ShapeAnalysis_Surface.hpp>

class ShapeFix_Edge;
class ShapeAnalysis_Wire;
class TopoDS_Wire;
class TopoDS_Face;
class ShapeExtend_WireData;
class Geom_Surface;
class TopLoc_Location;
class ShapeAnalysis_WireOrder;

class ShapeFix_Wire : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_Wire();

  Standard_EXPORT ShapeFix_Wire(const TopoDS_Wire& wire,
                                const TopoDS_Face& face,
                                const double       prec);

  Standard_EXPORT void ClearModes();

  Standard_EXPORT void ClearStatuses();

  Standard_EXPORT void Init(const TopoDS_Wire& wire, const TopoDS_Face& face, const double prec);

  Standard_EXPORT void Init(const occ::handle<ShapeAnalysis_Wire>& saw);

  Standard_EXPORT void Load(const TopoDS_Wire& wire);

  Standard_EXPORT void Load(const occ::handle<ShapeExtend_WireData>& sbwd);

  void SetFace(const TopoDS_Face& face);

  void SetFace(const TopoDS_Face&                        theFace,
               const occ::handle<ShapeAnalysis_Surface>& theSurfaceAnalysis);

  void SetSurface(const occ::handle<ShapeAnalysis_Surface>& theSurfaceAnalysis);

  void SetSurface(const occ::handle<Geom_Surface>& surf);

  void SetSurface(const occ::handle<Geom_Surface>& surf, const TopLoc_Location& loc);

  Standard_EXPORT void SetPrecision(const double prec) override;

  Standard_EXPORT void SetMaxTailAngle(const double theMaxTailAngle);

  Standard_EXPORT void SetMaxTailWidth(const double theMaxTailWidth);

  bool IsLoaded() const;

  bool IsReady() const;

  Standard_EXPORT int NbEdges() const;

  TopoDS_Wire Wire() const;

  TopoDS_Wire WireAPIMake() const;

  occ::handle<ShapeAnalysis_Wire> Analyzer() const;

  const occ::handle<ShapeExtend_WireData>& WireData() const;

  const TopoDS_Face& Face() const;

  bool& ModifyTopologyMode();

  bool& ModifyGeometryMode();

  int& ModifyRemoveLoopMode();

  bool& ClosedWireMode();

  bool& PreferencePCurveMode();

  bool& FixGapsByRangesMode();

  int& FixReorderMode();

  int& FixSmallMode();

  int& FixConnectedMode();

  int& FixEdgeCurvesMode();

  int& FixDegeneratedMode();

  int& FixSelfIntersectionMode();

  int& FixLackingMode();

  int& FixGaps3dMode();

  int& FixGaps2dMode();

  int& FixReversed2dMode();

  int& FixRemovePCurveMode();

  int& FixAddPCurveMode();

  int& FixRemoveCurve3dMode();

  int& FixAddCurve3dMode();

  int& FixSeamMode();

  int& FixShiftedMode();

  int& FixSameParameterMode();

  int& FixVertexToleranceMode();

  int& FixNotchedEdgesMode();

  int& FixSelfIntersectingEdgeMode();

  int& FixIntersectingEdgesMode();

  int& FixNonAdjacentIntersectingEdgesMode();

  int& FixTailMode();

  Standard_EXPORT bool Perform();

  Standard_EXPORT bool FixReorder(bool theModeBoth = false);

  Standard_EXPORT int FixSmall(const bool lockvtx, const double precsmall = 0.0);

  Standard_EXPORT bool FixConnected(const double prec = -1.0);

  Standard_EXPORT bool FixEdgeCurves();

  Standard_EXPORT bool FixDegenerated();

  Standard_EXPORT bool FixSelfIntersection();

  Standard_EXPORT bool FixLacking(const bool force = false);

  Standard_EXPORT bool FixClosed(const double prec = -1.0);

  Standard_EXPORT bool FixGaps3d();

  Standard_EXPORT bool FixGaps2d();

  Standard_EXPORT bool FixReorder(const ShapeAnalysis_WireOrder& wi);

  Standard_EXPORT bool FixSmall(const int num, const bool lockvtx, const double precsmall);

  Standard_EXPORT bool FixConnected(const int num, const double prec);

  Standard_EXPORT bool FixSeam(const int num);

  Standard_EXPORT bool FixShifted();

  Standard_EXPORT bool FixDegenerated(const int num);

  Standard_EXPORT bool FixLacking(const int num, const bool force = false);

  Standard_EXPORT bool FixNotchedEdges();

  Standard_EXPORT bool FixGap3d(const int num, const bool convert = false);

  Standard_EXPORT bool FixGap2d(const int num, const bool convert = false);

  Standard_EXPORT bool FixTails();

  bool StatusReorder(const ShapeExtend_Status status) const;

  bool StatusSmall(const ShapeExtend_Status status) const;

  bool StatusConnected(const ShapeExtend_Status status) const;

  bool StatusEdgeCurves(const ShapeExtend_Status status) const;

  bool StatusDegenerated(const ShapeExtend_Status status) const;

  bool StatusSelfIntersection(const ShapeExtend_Status status) const;

  bool StatusLacking(const ShapeExtend_Status status) const;

  bool StatusClosed(const ShapeExtend_Status status) const;

  bool StatusGaps3d(const ShapeExtend_Status status) const;

  bool StatusGaps2d(const ShapeExtend_Status status) const;

  bool StatusNotches(const ShapeExtend_Status status) const;

  bool StatusRemovedSegment() const;

  bool StatusFixTails(const ShapeExtend_Status status) const;

  bool LastFixStatus(const ShapeExtend_Status status) const;

  occ::handle<ShapeFix_Edge> FixEdgeTool() const;

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Wire, ShapeFix_Root)

protected:
  Standard_EXPORT void UpdateWire();

  occ::handle<ShapeFix_Edge>      myFixEdge;
  occ::handle<ShapeAnalysis_Wire> myAnalyzer;
  bool                            myGeomMode;
  bool                            myTopoMode;
  bool                            myClosedMode;
  bool                            myPreference2d;
  bool                            myFixGapsByRanges;
  int                             myFixReversed2dMode;
  int                             myFixRemovePCurveMode;
  int                             myFixAddPCurveMode;
  int                             myFixRemoveCurve3dMode;
  int                             myFixAddCurve3dMode;
  int                             myFixSeamMode;
  int                             myFixShiftedMode;
  int                             myFixSameParameterMode;
  int                             myFixVertexToleranceMode;
  int                             myFixNotchedEdgesMode;
  int                             myFixSelfIntersectingEdgeMode;
  int                             myFixIntersectingEdgesMode;
  int                             myFixNonAdjacentIntersectingEdgesMode;
  int                             myFixTailMode;
  int                             myRemoveLoopMode;
  int                             myFixReorderMode;
  int                             myFixSmallMode;
  int                             myFixConnectedMode;
  int                             myFixEdgeCurvesMode;
  int                             myFixDegeneratedMode;
  int                             myFixSelfIntersectionMode;
  int                             myFixLackingMode;
  int                             myFixGaps3dMode;
  int                             myFixGaps2dMode;
  int                             myLastFixStatus;
  int                             myStatusReorder;
  int                             myStatusSmall;
  int                             myStatusConnected;
  int                             myStatusEdgeCurves;
  int                             myStatusDegenerated;
  int                             myStatusClosed;
  int                             myStatusSelfIntersection;
  int                             myStatusLacking;
  int                             myStatusGaps3d;
  int                             myStatusGaps2d;
  bool                            myStatusRemovedSegment;
  int                             myStatusNotches;
  int                             myStatusFixTails;
  double                          myMaxTailAngleSine;
  double                          myMaxTailWidth;

private:
  Standard_EXPORT bool FixSelfIntersectingEdge(const int num);

  Standard_EXPORT bool FixIntersectingEdges(const int num);

  Standard_EXPORT bool FixIntersectingEdges(const int num1, const int num2);

  Standard_EXPORT void FixDummySeam(const int num);
};

#include <ShapeExtend.hpp>
#include <ShapeExtend_WireData.hpp>
#include <ShapeAnalysis_Wire.hpp>

inline void ShapeFix_Wire::SetFace(const TopoDS_Face& face)
{
  myAnalyzer->SetFace(face);
}

inline void ShapeFix_Wire::SetSurface(const occ::handle<Geom_Surface>& surf)
{
  myAnalyzer->SetSurface(surf);
}

inline void ShapeFix_Wire::SetFace(const TopoDS_Face&                        theFace,
                                   const occ::handle<ShapeAnalysis_Surface>& theSurfaceAnalysis)
{
  myAnalyzer->SetFace(theFace, theSurfaceAnalysis);
}

inline void ShapeFix_Wire::SetSurface(const occ::handle<ShapeAnalysis_Surface>& theSurfaceAnalysis)
{
  myAnalyzer->SetSurface(theSurfaceAnalysis);
}

inline void ShapeFix_Wire::SetSurface(const occ::handle<Geom_Surface>& surf,
                                      const TopLoc_Location&           loc)
{
  myAnalyzer->SetSurface(surf, loc);
}

inline bool ShapeFix_Wire::IsLoaded() const
{
  return myAnalyzer->IsLoaded();
}

inline bool ShapeFix_Wire::IsReady() const
{
  return myAnalyzer->IsReady();
}

inline TopoDS_Wire ShapeFix_Wire::Wire() const
{
  return myAnalyzer->WireData()->Wire();
}

inline TopoDS_Wire ShapeFix_Wire::WireAPIMake() const
{
  return myAnalyzer->WireData()->WireAPIMake();
}

inline occ::handle<ShapeAnalysis_Wire> ShapeFix_Wire::Analyzer() const
{
  return myAnalyzer;
}

inline const occ::handle<ShapeExtend_WireData>& ShapeFix_Wire::WireData() const
{
  return myAnalyzer->WireData();
}

inline const TopoDS_Face& ShapeFix_Wire::Face() const
{
  return myAnalyzer->Face();
}

inline bool& ShapeFix_Wire::ModifyTopologyMode()
{
  return myTopoMode;
}

inline bool& ShapeFix_Wire::ModifyGeometryMode()
{
  return myGeomMode;
}

inline int& ShapeFix_Wire::ModifyRemoveLoopMode()
{
  return myRemoveLoopMode;
}

inline bool& ShapeFix_Wire::ClosedWireMode()
{
  return myClosedMode;
}

inline bool& ShapeFix_Wire::PreferencePCurveMode()
{
  return myPreference2d;
}

inline bool& ShapeFix_Wire::FixGapsByRangesMode()
{
  return myFixGapsByRanges;
}

inline int& ShapeFix_Wire::FixReorderMode()
{
  return myFixReorderMode;
}

inline int& ShapeFix_Wire::FixSmallMode()
{
  return myFixSmallMode;
}

inline int& ShapeFix_Wire::FixConnectedMode()
{
  return myFixConnectedMode;
}

inline int& ShapeFix_Wire::FixEdgeCurvesMode()
{
  return myFixEdgeCurvesMode;
}

inline int& ShapeFix_Wire::FixDegeneratedMode()
{
  return myFixDegeneratedMode;
}

inline int& ShapeFix_Wire::FixReversed2dMode()
{
  return myFixReversed2dMode;
}

inline int& ShapeFix_Wire::FixRemovePCurveMode()
{
  return myFixRemovePCurveMode;
}

inline int& ShapeFix_Wire::FixRemoveCurve3dMode()
{
  return myFixRemoveCurve3dMode;
}

inline int& ShapeFix_Wire::FixAddPCurveMode()
{
  return myFixAddPCurveMode;
}

inline int& ShapeFix_Wire::FixAddCurve3dMode()
{
  return myFixAddCurve3dMode;
}

inline int& ShapeFix_Wire::FixSeamMode()
{
  return myFixSeamMode;
}

inline int& ShapeFix_Wire::FixShiftedMode()
{
  return myFixShiftedMode;
}

inline int& ShapeFix_Wire::FixSameParameterMode()
{
  return myFixSameParameterMode;
}

inline int& ShapeFix_Wire::FixVertexToleranceMode()
{
  return myFixVertexToleranceMode;
}

inline int& ShapeFix_Wire::FixLackingMode()
{
  return myFixLackingMode;
}

inline int& ShapeFix_Wire::FixSelfIntersectionMode()
{
  return myFixSelfIntersectionMode;
}

inline int& ShapeFix_Wire::FixGaps3dMode()
{
  return myFixGaps3dMode;
}

inline int& ShapeFix_Wire::FixGaps2dMode()
{
  return myFixGaps2dMode;
}

inline int& ShapeFix_Wire::FixNotchedEdgesMode()
{
  return myFixNotchedEdgesMode;
}

inline int& ShapeFix_Wire::FixSelfIntersectingEdgeMode()
{
  return myFixSelfIntersectingEdgeMode;
}

inline int& ShapeFix_Wire::FixIntersectingEdgesMode()
{
  return myFixIntersectingEdgesMode;
}

inline int& ShapeFix_Wire::FixNonAdjacentIntersectingEdgesMode()
{
  return myFixNonAdjacentIntersectingEdgesMode;
}

inline int& ShapeFix_Wire::FixTailMode()
{
  return myFixTailMode;
}

inline bool ShapeFix_Wire::StatusReorder(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusReorder, status);
}

inline bool ShapeFix_Wire::StatusSmall(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusSmall, status);
}

inline bool ShapeFix_Wire::StatusConnected(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusConnected, status);
}

inline bool ShapeFix_Wire::StatusEdgeCurves(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusEdgeCurves, status);
}

inline bool ShapeFix_Wire::StatusDegenerated(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusDegenerated, status);
}

inline bool ShapeFix_Wire::StatusLacking(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusLacking, status);
}

inline bool ShapeFix_Wire::StatusSelfIntersection(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusSelfIntersection, status);
}

inline bool ShapeFix_Wire::StatusGaps3d(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusGaps3d, status);
}

inline bool ShapeFix_Wire::StatusGaps2d(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusGaps2d, status);
}

inline bool ShapeFix_Wire::StatusClosed(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusClosed, status);
}

inline bool ShapeFix_Wire::StatusNotches(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusNotches, status);
}

inline bool ShapeFix_Wire::StatusFixTails(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusFixTails, status);
}

inline bool ShapeFix_Wire::LastFixStatus(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myLastFixStatus, status);
}

inline occ::handle<ShapeFix_Edge> ShapeFix_Wire::FixEdgeTool() const
{
  return myFixEdge;
}

inline bool ShapeFix_Wire::StatusRemovedSegment() const
{
  return myStatusRemovedSegment;
}
