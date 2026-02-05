#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Pnt;
class gp_Dir;

//! A framework to define display of offsets.
class DsgPrs_OffsetPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines the display of elements showing offset shapes.
  //! These include the two points of attachment
  //! AttachmentPoint1 and AttachmentPoint1, the two
  //! directions aDirection and aDirection2, and the offset point OffsetPoint.
  //! These arguments are added to the presentation
  //! object aPresentation. Their display attributes are
  //! defined by the attribute manager aDrawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          aDirection,
                                  const gp_Dir&                          aDirection2,
                                  const gp_Pnt&                          OffsetPoint);

  //! draws the representation of axes alignment Constraint
  //! between the point AttachmentPoint1 and the
  //! point AttachmentPoint2, along direction
  //! aDirection, using the offset point OffsetPoint.
  Standard_EXPORT static void AddAxes(const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const occ::handle<Prs3d_Drawer>&       aDrawer,
                                      const TCollection_ExtendedString&      aText,
                                      const gp_Pnt&                          AttachmentPoint1,
                                      const gp_Pnt&                          AttachmentPoint2,
                                      const gp_Dir&                          aDirection,
                                      const gp_Dir&                          aDirection2,
                                      const gp_Pnt&                          OffsetPoint);
};
