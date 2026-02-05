#pragma once

#include <StdPrs_HLRShapeI.hpp>

//! Instantiates Prs3d_PolyHLRShape to define a display of a shape where hidden
//! and visible lines are identified with respect to a given projection.
//! StdPrs_HLRPolyShape works with a polyhedral simplification of the shape whereas
//! StdPrs_HLRShape takes the shape itself into account.
//! When you use StdPrs_HLRShape, you obtain an exact result, whereas, when you use
//! StdPrs_HLRPolyShape, you reduce computation time but obtain polygonal segments. The polygonal
//! algorithm is used.
class StdPrs_HLRPolyShape : public StdPrs_HLRShapeI
{
  DEFINE_STANDARD_RTTIEXT(StdPrs_HLRPolyShape, StdPrs_HLRShapeI)
public:
  //! Compute presentation for specified shape.
  Standard_EXPORT void ComputeHLR(const occ::handle<Prs3d_Presentation>& thePrs,
                                  const TopoDS_Shape&                    theShape,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer,
                                  const occ::handle<Graphic3d_Camera>& theProjector) const override;
};
