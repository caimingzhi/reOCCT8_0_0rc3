#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Shape;
class ShapeProcess_ShapeContext;
class BRepTools_Modification;
class ShapeExtend_MsgRegistrator;

//! Provides a set of following operators
//!
//! DirectFaces
//! FixShape
//! SameParameter
//! SetTolerance
//! SplitAngle
//! BSplineRestriction
//! ElementaryToRevolution
//! SurfaceToBSpline
//! ToBezier
//! SplitContinuity
//! SplitClosedFaces
//! FixWireGaps
//! FixFaceSize
//! DropSmallEdges
//! FixShape
//! SplitClosedEdges
class ShapeProcess_OperLibrary
{
public:
  DEFINE_STANDARD_ALLOC

  //! Registers all the operators
  Standard_EXPORT static void Init();

  //! Applies BRepTools_Modification to a shape,
  //! taking into account sharing of components of compounds.
  //! if theMutableInput vat is set to true then input shape S
  //! can be modified during the modification process.
  Standard_EXPORT static TopoDS_Shape ApplyModifier(
    const TopoDS_Shape&                                                       S,
    const occ::handle<ShapeProcess_ShapeContext>&                             context,
    const occ::handle<BRepTools_Modification>&                                M,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& map,
    const occ::handle<ShapeExtend_MsgRegistrator>&                            msg = nullptr,
    bool theMutableInput                                                          = false);
};
