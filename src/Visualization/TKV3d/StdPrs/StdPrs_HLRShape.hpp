#pragma once

#include <StdPrs_HLRShapeI.hpp>

//! Computes the presentation of objects with removal of their hidden lines for a specific
//! projector. The exact algorithm is used.
class StdPrs_HLRShape : public StdPrs_HLRShapeI
{
  DEFINE_STANDARD_RTTIEXT(StdPrs_HLRShape, StdPrs_HLRShapeI)
public:
  //! Compute presentation for specified shape.
  Standard_EXPORT void ComputeHLR(const occ::handle<Prs3d_Presentation>& thePrs,
                                  const TopoDS_Shape&                    theShape,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer,
                                  const occ::handle<Graphic3d_Camera>& theProjector) const override;
};
