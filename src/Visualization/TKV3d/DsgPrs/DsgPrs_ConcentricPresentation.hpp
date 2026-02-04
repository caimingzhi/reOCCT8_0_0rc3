#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class gp_Dir;

//! A framework to define display of relations of concentricity.
class DsgPrs_ConcentricPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines the display of elements showing relations of
  //! concentricity between shapes.
  //! These include the center aCenter, the radius
  //! aRadius, the direction aNorm and the point aPoint.
  //! These arguments are added to the presentation
  //! object aPresentation. Their display attributes are
  //! defined by the attribute manager aDrawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          aCenter,
                                  const double                           aRadius,
                                  const gp_Dir&                          aNorm,
                                  const gp_Pnt&                          aPoint);
};

