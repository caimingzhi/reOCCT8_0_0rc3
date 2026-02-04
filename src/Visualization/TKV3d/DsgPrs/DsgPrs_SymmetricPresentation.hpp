#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class gp_Dir;
class gp_Lin;
class gp_Circ;

//! A framework to define display of symmetry between shapes.
class DsgPrs_SymmetricPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the points OffsetPoint, AttachmentPoint1,
  //! AttachmentPoint2, the direction aDirection1 and the
  //! axis anAxis to the presentation object aPresentation.
  //! The display attributes of the symmetry are defined by
  //! the attribute manager aDrawer.
  //! This syntax is used for display of symmetries between two segments.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          aDirection1,
                                  const gp_Lin&                          aAxis,
                                  const gp_Pnt&                          OffsetPoint);

  //! Adds the points OffsetPoint, AttachmentPoint1,
  //! AttachmentPoint2, the direction aDirection1 the circle
  //! aCircle1 and the axis anAxis to the presentation
  //! object aPresentation.
  //! The display attributes of the symmetry are defined by
  //! the attribute manager aDrawer.
  //! This syntax is used for display of symmetries between two arcs.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Circ&                         aCircle1,
                                  const gp_Lin&                          aAxis,
                                  const gp_Pnt&                          OffsetPoint);

  //! Adds the points OffsetPoint, AttachmentPoint1,
  //! AttachmentPoint2 and the axis anAxis to the
  //! presentation object aPresentation.
  //! The display attributes of the symmetry are defined by
  //! the attribute manager aDrawer.
  //! This syntax is used for display of symmetries between two vertices.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Lin&                          aAxis,
                                  const gp_Pnt&                          OffsetPoint);
};

