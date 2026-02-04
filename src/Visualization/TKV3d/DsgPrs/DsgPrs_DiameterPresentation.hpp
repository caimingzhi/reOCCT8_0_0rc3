#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Pnt;
class gp_Circ;

//! A framework for displaying diameters in shapes.
class DsgPrs_DiameterPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Draws the diameter of the circle aCircle displayed in
  //! the presentation aPresentation and with attributes
  //! defined by the attribute manager aDrawer. The point
  //! AttachmentPoint defines the point of contact
  //! between the circle and the diameter presentation.
  //! The value of the enumeration ArrowSide controls
  //! whether arrows will be displayed at either or both
  //! ends of the length. The text aText labels the diameter.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint,
                                  const gp_Circ&                         aCircle,
                                  const DsgPrs_ArrowSide                 ArrowSide,
                                  const bool                             IsDiamSymbol);

  //! Draws the diameter of the arc anArc displayed in the
  //! presentation aPresentation and with attributes
  //! defined by the attribute manager aDrawer. The point
  //! AttachmentPoint defines the point of contact
  //! between the arc and the diameter presentation. The
  //! value of the enumeration ArrowSide controls whether
  //! arrows will be displayed at either or both ends of the
  //! length. The parameters uFirst and uLast define the
  //! first and last points of the arc. The text aText labels the diameter.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint,
                                  const gp_Circ&                         aCircle,
                                  const double                           uFirst,
                                  const double                           uLast,
                                  const DsgPrs_ArrowSide                 ArrowSide,
                                  const bool                             IsDiamSymbol);
};

