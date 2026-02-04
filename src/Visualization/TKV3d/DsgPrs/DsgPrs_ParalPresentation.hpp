#pragma once


#include <Prs3d_Drawer.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Pnt;
class gp_Dir;

//! A framework to define display of relations of parallelism between shapes.
class DsgPrs_ParalPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines the display of elements showing relations of
  //! parallelism between shapes.
  //! These include the two points of attachment
  //! AttachmentPoint1 and AttachmentPoint1, the
  //! direction aDirection, and the offset point OffsetPoint.
  //! These arguments are added to the presentation
  //! object aPresentation. Their display attributes are
  //! defined by the attribute manager aDrawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          aDirection,
                                  const gp_Pnt&                          OffsetPoint);

  //! Defines the display of elements showing relations of
  //! parallelism between shapes.
  //! These include the two points of attachment
  //! AttachmentPoint1 and AttachmentPoint1, the
  //! direction aDirection, the offset point OffsetPoint and
  //! the text aText.
  //! These arguments are added to the presentation
  //! object aPresentation. Their display attributes are
  //! defined by the attribute manager aDrawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          aDirection,
                                  const gp_Pnt&                          OffsetPoint,
                                  const DsgPrs_ArrowSide                 ArrowSide);
};

