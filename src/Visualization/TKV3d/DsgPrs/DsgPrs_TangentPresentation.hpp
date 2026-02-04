#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class gp_Dir;

//! A framework to define display of tangents.
class DsgPrs_TangentPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the point OffsetPoint, the direction aDirection
  //! and the length aLength to the presentation object aPresentation.
  //! The display attributes of the tangent are defined by
  //! the attribute manager aDrawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          OffsetPoint,
                                  const gp_Dir&                          aDirection,
                                  const double                           aLength);
};

