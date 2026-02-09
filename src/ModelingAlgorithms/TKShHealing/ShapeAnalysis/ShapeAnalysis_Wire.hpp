#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Face.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <ShapeExtend_Status.hpp>
class ShapeExtend_WireData;
class ShapeAnalysis_Surface;
class TopoDS_Wire;
class Geom_Surface;
class TopLoc_Location;
class ShapeAnalysis_WireOrder;
class Geom2d_Curve;
class gp_Pnt2d;
class TopoDS_Shape;
class TopoDS_Edge;

#ifdef Status
  #undef Status
#endif

class ShapeAnalysis_Wire : public Standard_Transient
{

public:
  Standard_EXPORT ShapeAnalysis_Wire();

  Standard_EXPORT ShapeAnalysis_Wire(const TopoDS_Wire& wire,
                                     const TopoDS_Face& face,
                                     const double       precision);

  Standard_EXPORT ShapeAnalysis_Wire(const occ::handle<ShapeExtend_WireData>& sbwd,
                                     const TopoDS_Face&                       face,
                                     const double                             precision);

  Standard_EXPORT void Init(const TopoDS_Wire& wire,
                            const TopoDS_Face& face,
                            const double       precision);

  Standard_EXPORT void Init(const occ::handle<ShapeExtend_WireData>& sbwd,
                            const TopoDS_Face&                       face,
                            const double                             precision);

  Standard_EXPORT void Load(const TopoDS_Wire& wire);

  Standard_EXPORT void Load(const occ::handle<ShapeExtend_WireData>& sbwd);

  Standard_EXPORT void SetFace(const TopoDS_Face& face);

  Standard_EXPORT void SetFace(const TopoDS_Face&                        theFace,
                               const occ::handle<ShapeAnalysis_Surface>& theSurfaceAnalysis);

  Standard_EXPORT void SetSurface(const occ::handle<ShapeAnalysis_Surface>& theSurfaceAnalysis);

  Standard_EXPORT void SetSurface(const occ::handle<Geom_Surface>& surface);

  Standard_EXPORT void SetSurface(const occ::handle<Geom_Surface>& surface,
                                  const TopLoc_Location&           location);

  Standard_EXPORT void SetPrecision(const double precision);

  Standard_EXPORT void ClearStatuses();

  bool IsLoaded() const;

  bool IsReady() const;

  double Precision() const;

  const occ::handle<ShapeExtend_WireData>& WireData() const;

  int NbEdges() const;

  const TopoDS_Face& Face() const;

  const occ::handle<ShapeAnalysis_Surface>& Surface() const;

  Standard_EXPORT bool Perform();

  Standard_EXPORT bool CheckOrder(const bool isClosed = true, const bool mode3d = true);

  Standard_EXPORT bool CheckConnected(const double prec = 0.0);

  Standard_EXPORT bool CheckSmall(const double precsmall = 0.0);

  Standard_EXPORT bool CheckEdgeCurves();

  Standard_EXPORT bool CheckDegenerated();

  Standard_EXPORT bool CheckClosed(const double prec = 0.0);

  Standard_EXPORT bool CheckSelfIntersection();

  Standard_EXPORT bool CheckLacking();

  Standard_EXPORT bool CheckGaps3d();

  Standard_EXPORT bool CheckGaps2d();

  Standard_EXPORT bool CheckCurveGaps();

  Standard_EXPORT bool CheckOrder(ShapeAnalysis_WireOrder& sawo,
                                  bool                     isClosed    = true,
                                  bool                     theMode3D   = true,
                                  bool                     theModeBoth = false);

  Standard_EXPORT bool CheckConnected(const int num, const double prec = 0.0);

  Standard_EXPORT bool CheckSmall(const int num, const double precsmall = 0.0);

  Standard_EXPORT bool CheckSeam(const int                  num,
                                 occ::handle<Geom2d_Curve>& C1,
                                 occ::handle<Geom2d_Curve>& C2,
                                 double&                    cf,
                                 double&                    cl);

  Standard_EXPORT bool CheckSeam(const int num);

  Standard_EXPORT bool CheckDegenerated(const int num, gp_Pnt2d& dgnr1, gp_Pnt2d& dgnr2);

  Standard_EXPORT bool CheckDegenerated(const int num);

  Standard_EXPORT bool CheckGap3d(const int num = 0);

  Standard_EXPORT bool CheckGap2d(const int num = 0);

  Standard_EXPORT bool CheckCurveGap(const int num = 0);

  Standard_EXPORT bool CheckSelfIntersectingEdge(
    const int                                         num,
    NCollection_Sequence<IntRes2d_IntersectionPoint>& points2d,
    NCollection_Sequence<gp_Pnt>&                     points3d);

  Standard_EXPORT bool CheckSelfIntersectingEdge(const int num);

  Standard_EXPORT bool CheckIntersectingEdges(
    const int                                         num,
    NCollection_Sequence<IntRes2d_IntersectionPoint>& points2d,
    NCollection_Sequence<gp_Pnt>&                     points3d,
    NCollection_Sequence<double>&                     errors);

  Standard_EXPORT bool CheckIntersectingEdges(const int num);

  Standard_EXPORT bool CheckIntersectingEdges(
    const int                                         num1,
    const int                                         num2,
    NCollection_Sequence<IntRes2d_IntersectionPoint>& points2d,
    NCollection_Sequence<gp_Pnt>&                     points3d,
    NCollection_Sequence<double>&                     errors);

  Standard_EXPORT bool CheckIntersectingEdges(const int num1, const int num2);

  Standard_EXPORT bool CheckLacking(const int    num,
                                    const double Tolerance,
                                    gp_Pnt2d&    p2d1,
                                    gp_Pnt2d&    p2d2);

  Standard_EXPORT bool CheckLacking(const int num, const double Tolerance = 0.0);

  Standard_EXPORT bool CheckOuterBound(const bool APIMake = true);

  Standard_EXPORT bool CheckNotchedEdges(const int    num,
                                         int&         shortNum,
                                         double&      param,
                                         const double Tolerance = 0.0);

  Standard_EXPORT bool CheckSmallArea(const TopoDS_Wire& theWire);

  Standard_EXPORT bool CheckShapeConnect(const TopoDS_Shape& shape, const double prec = 0.0);

  Standard_EXPORT bool CheckShapeConnect(double&             tailhead,
                                         double&             tailtail,
                                         double&             headtail,
                                         double&             headhead,
                                         const TopoDS_Shape& shape,
                                         const double        prec = 0.0);

  Standard_EXPORT bool CheckLoop(
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapLoopVertices,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                            aMapVertexEdges,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapSmallEdges,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapSeemEdges);

  Standard_EXPORT bool CheckTail(const TopoDS_Edge& theEdge1,
                                 const TopoDS_Edge& theEdge2,
                                 const double       theMaxSine,
                                 const double       theMaxWidth,
                                 const double       theMaxTolerance,
                                 TopoDS_Edge&       theEdge11,
                                 TopoDS_Edge&       theEdge12,
                                 TopoDS_Edge&       theEdge21,
                                 TopoDS_Edge&       theEdge22);

  bool StatusOrder(const ShapeExtend_Status Status) const;

  bool StatusConnected(const ShapeExtend_Status Status) const;

  bool StatusEdgeCurves(const ShapeExtend_Status Status) const;

  bool StatusDegenerated(const ShapeExtend_Status Status) const;

  bool StatusClosed(const ShapeExtend_Status Status) const;

  bool StatusSmall(const ShapeExtend_Status Status) const;

  bool StatusSelfIntersection(const ShapeExtend_Status Status) const;

  bool StatusLacking(const ShapeExtend_Status Status) const;

  bool StatusGaps3d(const ShapeExtend_Status Status) const;

  bool StatusGaps2d(const ShapeExtend_Status Status) const;

  bool StatusCurveGaps(const ShapeExtend_Status Status) const;

  bool StatusLoop(const ShapeExtend_Status Status) const;

  bool LastCheckStatus(const ShapeExtend_Status Status) const;

  double MinDistance3d() const;

  double MinDistance2d() const;

  double MaxDistance3d() const;

  double MaxDistance2d() const;

  DEFINE_STANDARD_RTTIEXT(ShapeAnalysis_Wire, Standard_Transient)

protected:
  occ::handle<ShapeExtend_WireData>  myWire;
  TopoDS_Face                        myFace;
  occ::handle<ShapeAnalysis_Surface> mySurf;
  double                             myPrecision;
  double                             myMin3d;
  double                             myMin2d;
  double                             myMax3d;
  double                             myMax2d;
  int                                myStatusOrder;
  int                                myStatusConnected;
  int                                myStatusEdgeCurves;
  int                                myStatusDegenerated;
  int                                myStatusClosed;
  int                                myStatusSmall;
  int                                myStatusSelfIntersection;
  int                                myStatusLacking;
  int                                myStatusGaps3d;
  int                                myStatusGaps2d;
  int                                myStatusCurveGaps;
  int                                myStatusLoop;
  int                                myStatus;
};

#include <ShapeExtend.hpp>
#include <ShapeExtend_WireData.hpp>

inline bool ShapeAnalysis_Wire::IsLoaded() const
{
  return !myWire.IsNull() && myWire->NbEdges() > 0;
}

inline bool ShapeAnalysis_Wire::IsReady() const
{
  return IsLoaded() && !myFace.IsNull();
}

inline double ShapeAnalysis_Wire::Precision() const
{
  return myPrecision;
}

inline const occ::handle<ShapeExtend_WireData>& ShapeAnalysis_Wire::WireData() const
{
  return myWire;
}

inline int ShapeAnalysis_Wire::NbEdges() const
{
  return myWire.IsNull() ? 0 : myWire->NbEdges();
}

inline const TopoDS_Face& ShapeAnalysis_Wire::Face() const
{
  return myFace;
}

inline const occ::handle<ShapeAnalysis_Surface>& ShapeAnalysis_Wire::Surface() const
{
  return mySurf;
}

inline bool ShapeAnalysis_Wire::StatusOrder(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusOrder, Status);
}

inline bool ShapeAnalysis_Wire::StatusConnected(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusConnected, Status);
}

inline bool ShapeAnalysis_Wire::StatusEdgeCurves(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusEdgeCurves, Status);
}

inline bool ShapeAnalysis_Wire::StatusDegenerated(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusDegenerated, Status);
}

inline bool ShapeAnalysis_Wire::StatusClosed(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusClosed, Status);
}

inline bool ShapeAnalysis_Wire::StatusSmall(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusSmall, Status);
}

inline bool ShapeAnalysis_Wire::StatusSelfIntersection(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusSelfIntersection, Status);
}

inline bool ShapeAnalysis_Wire::StatusLacking(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusLacking, Status);
}

inline bool ShapeAnalysis_Wire::StatusGaps3d(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusGaps3d, Status);
}

inline bool ShapeAnalysis_Wire::StatusGaps2d(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusGaps2d, Status);
}

inline bool ShapeAnalysis_Wire::StatusCurveGaps(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusCurveGaps, Status);
}

inline bool ShapeAnalysis_Wire::StatusLoop(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatusLoop, Status);
}

inline bool ShapeAnalysis_Wire::LastCheckStatus(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatus, Status);
}

inline double ShapeAnalysis_Wire::MinDistance3d() const
{
  return myMin3d;
}

inline double ShapeAnalysis_Wire::MinDistance2d() const
{
  return myMin2d;
}

inline double ShapeAnalysis_Wire::MaxDistance3d() const
{
  return myMax3d;
}

inline double ShapeAnalysis_Wire::MaxDistance2d() const
{
  return myMax2d;
}
