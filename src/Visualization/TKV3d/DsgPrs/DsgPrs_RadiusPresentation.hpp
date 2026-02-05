#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Pnt;
class gp_Circ;

//! A framework to define display of radii.
class DsgPrs_RadiusPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the point AttachmentPoint, the circle aCircle,
  //! the text aText, and the parameters firstparam and
  //! lastparam to the presentation object aPresentation.
  //! The display attributes of these elements is defined by
  //! the attribute manager aDrawer.
  //! If the Boolean drawFromCenter is false, the
  //! arrowhead will point towards the center of aCircle.
  //! If the Boolean reverseArrow is true, the arrowhead
  //! will point away from the attachment point.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint,
                                  const gp_Circ&                         aCircle,
                                  const double                           firstparam,
                                  const double                           lastparam,
                                  const bool                             drawFromCenter = true,
                                  const bool                             reverseArrow   = false);

  //! Adds the point AttachmentPoint, the circle aCircle,
  //! the text aText, and the parameters firstparam and
  //! lastparam to the presentation object aPresentation.
  //! The display attributes of these elements is defined by
  //! the attribute manager aDrawer.
  //! The value of the enumeration Arrowside determines
  //! the type of arrow displayed: whether there will be
  //! arrowheads at both ends or only one, for example.
  //! If the Boolean drawFromCenter is false, the
  //! arrowhead will point towards the center of aCircle.
  //! If the Boolean reverseArrow is true, the arrowhead
  //! will point away from the attachment point.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint,
                                  const gp_Circ&                         aCircle,
                                  const double                           firstparam,
                                  const double                           lastparam,
                                  const DsgPrs_ArrowSide                 ArrowSide,
                                  const bool                             drawFromCenter = true,
                                  const bool                             reverseArrow   = false);

  //! Adds the circle aCircle, the text aText, the points
  //! AttachmentPoint, Center and EndOfArrow to the
  //! presentation object aPresentation.
  //! The display attributes of these elements is defined by
  //! the attribute manager aDrawer.
  //! The value of the enumeration Arrowside determines
  //! the type of arrow displayed: whether there will be
  //! arrowheads at both ends or only one, for example.
  //! If the Boolean drawFromCenter is false, the
  //! arrowhead will point towards the center of aCircle.
  //! If the Boolean reverseArrow is true, the arrowhead
  //! will point away from the attachment point.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint,
                                  const gp_Pnt&                          Center,
                                  const gp_Pnt&                          EndOfArrow,
                                  const DsgPrs_ArrowSide                 ArrowSide,
                                  const bool                             drawFromCenter = true,
                                  const bool                             reverseArrow   = false);
};
