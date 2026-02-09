#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <Message_ProgressRange.hpp>

class TopoDS_Shape;
class BRepTools_Modification;
class BRepTools_Modifier;
class ShapeBuild_ReShape;
class ShapeCustom_RestrictionParameters;

class ShapeCustom
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopoDS_Shape ApplyModifier(
    const TopoDS_Shape&                                                       S,
    const occ::handle<BRepTools_Modification>&                                M,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& context,
    BRepTools_Modifier&                                                       MD,
    const Message_ProgressRange&           theProgress = Message_ProgressRange(),
    const occ::handle<ShapeBuild_ReShape>& aReShape    = nullptr);

  Standard_EXPORT static TopoDS_Shape DirectFaces(const TopoDS_Shape& S);

  Standard_EXPORT static TopoDS_Shape ScaleShape(const TopoDS_Shape& S, const double scale);

  Standard_EXPORT static TopoDS_Shape BSplineRestriction(
    const TopoDS_Shape&                                   S,
    const double                                          Tol3d,
    const double                                          Tol2d,
    const int                                             MaxDegree,
    const int                                             MaxNbSegment,
    const GeomAbs_Shape                                   Continuity3d,
    const GeomAbs_Shape                                   Continuity2d,
    const bool                                            Degree,
    const bool                                            Rational,
    const occ::handle<ShapeCustom_RestrictionParameters>& aParameters);

  Standard_EXPORT static TopoDS_Shape ConvertToRevolution(const TopoDS_Shape& S);

  Standard_EXPORT static TopoDS_Shape SweptToElementary(const TopoDS_Shape& S);

  Standard_EXPORT static TopoDS_Shape ConvertToBSpline(const TopoDS_Shape& S,
                                                       const bool          extrMode,
                                                       const bool          revolMode,
                                                       const bool          offsetMode,
                                                       const bool          planeMode = false);
};
