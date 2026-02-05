#pragma once

#include <Prs3d_Presentation.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class TopoDS_Shape;
class Prs3d_Drawer;
class Graphic3d_Camera;

//! Computes the presentation of objects with removal of their hidden lines for a specific
//! projector.
class StdPrs_HLRShapeI : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(StdPrs_HLRShapeI, Standard_Transient)
public:
  //! Compute presentation for specified shape.
  virtual void ComputeHLR(const occ::handle<Prs3d_Presentation>& thePrs,
                          const TopoDS_Shape&                    theShape,
                          const occ::handle<Prs3d_Drawer>&       theDrawer,
                          const occ::handle<Graphic3d_Camera>&   theProjector) const = 0;
};
