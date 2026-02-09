#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomFill_ApproxStyle.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <BRepFill_TransitionStyle.hpp>
class BRepFill_LocationLaw;
class BRepFill_SectionLaw;
class TopoDS_Edge;

class BRepFill_Sweep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_Sweep(const occ::handle<BRepFill_SectionLaw>&  Section,
                                 const occ::handle<BRepFill_LocationLaw>& Location,
                                 const bool                               WithKPart);

  Standard_EXPORT void SetBounds(const TopoDS_Wire& FirstShape, const TopoDS_Wire& LastShape);

  Standard_EXPORT void SetTolerance(const double Tol3d,
                                    const double BoundTol   = 1.0,
                                    const double Tol2d      = 1.0e-5,
                                    const double TolAngular = 1.0e-2);

  Standard_EXPORT void SetAngularControl(const double AngleMin = 0.01, const double AngleMax = 6.0);

  Standard_EXPORT void SetForceApproxC1(const bool ForceApproxC1);

  Standard_EXPORT void Build(NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& ReversedEdges,
                             NCollection_DataMap<TopoDS_Shape,
                                                 occ::handle<NCollection_HArray2<TopoDS_Shape>>,
                                                 TopTools_ShapeMapHasher>&           Tapes,
                             NCollection_DataMap<TopoDS_Shape,
                                                 occ::handle<NCollection_HArray2<TopoDS_Shape>>,
                                                 TopTools_ShapeMapHasher>&           Rails,
                             const BRepFill_TransitionStyle Transition = BRepFill_Modified,
                             const GeomAbs_Shape            Continuity = GeomAbs_C2,
                             const GeomFill_ApproxStyle     Approx     = GeomFill_Location,
                             const int                      Degmax     = 11,
                             const int                      Segmax     = 30);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT TopoDS_Shape Shape() const;

  Standard_EXPORT double ErrorOnSurface() const;

  Standard_EXPORT occ::handle<NCollection_HArray2<TopoDS_Shape>> SubShape() const;

  Standard_EXPORT occ::handle<NCollection_HArray2<TopoDS_Shape>> InterFaces() const;

  Standard_EXPORT occ::handle<NCollection_HArray2<TopoDS_Shape>> Sections() const;

  Standard_EXPORT TopoDS_Shape Tape(const int Index) const;

protected:
  Standard_EXPORT bool CorrectApproxParameters();

  Standard_EXPORT bool BuildWire(const BRepFill_TransitionStyle Transition);

  Standard_EXPORT bool BuildShell(
    const BRepFill_TransitionStyle                          Transition,
    const int                                               Vf,
    const int                                               Vl,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& ReversedEdges,
    NCollection_DataMap<TopoDS_Shape,
                        occ::handle<NCollection_HArray2<TopoDS_Shape>>,
                        TopTools_ShapeMapHasher>&           Tapes,
    NCollection_DataMap<TopoDS_Shape,
                        occ::handle<NCollection_HArray2<TopoDS_Shape>>,
                        TopTools_ShapeMapHasher>&           Rails,
    const double                                            ExtendFirst = 0.0,
    const double                                            ExtendLast  = 0.0);

  Standard_EXPORT bool PerformCorner(const int                      Index,
                                     const BRepFill_TransitionStyle Transition,
                                     const occ::handle<NCollection_HArray2<TopoDS_Shape>>& Bounds);

  Standard_EXPORT double EvalExtrapol(const int                      Index,
                                      const BRepFill_TransitionStyle Transition) const;

  Standard_EXPORT bool MergeVertex(const TopoDS_Shape& V1, TopoDS_Shape& V2) const;

  Standard_EXPORT void UpdateVertex(const int     Ipath,
                                    const int     Isec,
                                    const double  Error,
                                    const double  Param,
                                    TopoDS_Shape& V) const;

  Standard_EXPORT void RebuildTopOrBottomEdge(
    const TopoDS_Edge&                                      aNewEdge,
    TopoDS_Edge&                                            anEdge,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& ReversedEdges) const;

private:
  bool                                                                     isDone;
  bool                                                                     KPart;
  double                                                                   myTol3d;
  double                                                                   myBoundTol;
  double                                                                   myTol2d;
  double                                                                   myTolAngular;
  double                                                                   myAngMin;
  double                                                                   myAngMax;
  GeomFill_ApproxStyle                                                     myApproxStyle;
  GeomAbs_Shape                                                            myContinuity;
  int                                                                      myDegmax;
  int                                                                      mySegmax;
  bool                                                                     myForceApproxC1;
  TopoDS_Shape                                                             myShape;
  occ::handle<BRepFill_LocationLaw>                                        myLoc;
  occ::handle<BRepFill_SectionLaw>                                         mySec;
  occ::handle<NCollection_HArray2<TopoDS_Shape>>                           myUEdges;
  occ::handle<NCollection_HArray2<TopoDS_Shape>>                           myVEdges;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVEdgesModified;
  occ::handle<NCollection_HArray2<TopoDS_Shape>>                           myFaces;
  NCollection_List<TopoDS_Shape>                                           myAuxShape;
  occ::handle<NCollection_HArray1<TopoDS_Shape>>                           myTapes;
  double                                                                   Error;
  TopoDS_Wire                                                              FirstShape;
  TopoDS_Wire                                                              LastShape;
};
