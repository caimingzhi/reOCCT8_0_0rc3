#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <BRepMAT2d_BisectingLocus.hpp>
#include <BRepMAT2d_LinkTopoBilo.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
class Bisector_Bisec;
class BRepFill_TrimEdgeTool;

class BRepFill_OffsetWire
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_OffsetWire();

  Standard_EXPORT BRepFill_OffsetWire(const TopoDS_Face&     Spine,
                                      const GeomAbs_JoinType Join         = GeomAbs_Arc,
                                      const bool             IsOpenResult = false);

  Standard_EXPORT void Init(const TopoDS_Face&     Spine,
                            const GeomAbs_JoinType Join         = GeomAbs_Arc,
                            const bool             IsOpenResult = false);

  Standard_EXPORT void Perform(const double Offset, const double Alt = 0.0);

  Standard_EXPORT void PerformWithBiLo(const TopoDS_Face&              WSP,
                                       const double                    Offset,
                                       const BRepMAT2d_BisectingLocus& Locus,
                                       BRepMAT2d_LinkTopoBilo&         Link,
                                       const GeomAbs_JoinType          Join = GeomAbs_Arc,
                                       const double                    Alt  = 0.0);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const TopoDS_Face& Spine() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GeneratedShapes(
    const TopoDS_Shape& SpineShape);

  Standard_EXPORT GeomAbs_JoinType JoinType() const;

private:
  Standard_EXPORT NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>>&
                  Generated();

  Standard_EXPORT void PrepareSpine();

  Standard_EXPORT void Add(const BRepFill_OffsetWire& Other);

  Standard_EXPORT void UpdateDetromp(
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>>& Detromp,
    const TopoDS_Shape&                                                Shape1,
    const TopoDS_Shape&                                                Shape2,
    const NCollection_Sequence<TopoDS_Shape>&                          Vertices,
    const NCollection_Sequence<gp_Pnt>&                                Params,
    const Bisector_Bisec&                                              Bisec,
    const bool                                                         SOnE,
    const bool                                                         EOnE,
    const BRepFill_TrimEdgeTool&                                       Trim) const;

  Standard_EXPORT void MakeWires();

  Standard_EXPORT void FixHoles();

  TopoDS_Face                                                              mySpine;
  TopoDS_Face                                                              myWorkSpine;
  double                                                                   myOffset;
  bool                                                                     myIsOpenResult;
  TopoDS_Shape                                                             myShape;
  bool                                                                     myIsDone;
  GeomAbs_JoinType                                                         myJoinType;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>> myMap;
  BRepMAT2d_BisectingLocus                                                 myBilo;
  BRepMAT2d_LinkTopoBilo                                                   myLink;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMapSpine;
  bool                                                                     myCallGen;
};
