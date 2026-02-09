#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>

#include <ShapeExtend_BasicMsgRegistrator.hpp>
#include <Message_ProgressRange.hpp>

class TopoDS_Shape;
class ShapeExtend_BasicMsgRegistrator;
class ShapeBuild_ReShape;

class ShapeFix
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool SameParameter(
    const TopoDS_Shape&                                 shape,
    const bool                                          enforce,
    const double                                        preci       = 0.0,
    const Message_ProgressRange&                        theProgress = Message_ProgressRange(),
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& theMsgReg   = nullptr);

  Standard_EXPORT static void EncodeRegularity(const TopoDS_Shape& shape,
                                               const double        tolang = 1.0e-10);

  Standard_EXPORT static TopoDS_Shape RemoveSmallEdges(TopoDS_Shape&                    shape,
                                                       const double                     Tolerance,
                                                       occ::handle<ShapeBuild_ReShape>& context);

  Standard_EXPORT static bool FixVertexPosition(TopoDS_Shape&                          theshape,
                                                const double                           theTolerance,
                                                const occ::handle<ShapeBuild_ReShape>& thecontext);

  Standard_EXPORT static double LeastEdgeSize(TopoDS_Shape& theshape);
};
