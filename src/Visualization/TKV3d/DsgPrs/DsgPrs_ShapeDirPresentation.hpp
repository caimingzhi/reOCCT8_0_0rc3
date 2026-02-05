#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class TopoDS_Shape;

//! A framework to define display of the normal to the
//! surface of a shape.
class DsgPrs_ShapeDirPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the shape shape and the mode mode to the
  //! presentation object prs.
  //! The display attributes of the normal are defined by the
  //! attribute manager aDrawer.
  //! mode determines whether the first or the last point of
  //! the normal is given to the presentation object. If the
  //! first point: 0; if the last point, 1.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& prs,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TopoDS_Shape&                    shape,
                                  const int                              mode);
};
