#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class gp_Dir;
class gp_Lin;
class gp_Circ;

class DsgPrs_SymmetricPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          aDirection1,
                                  const gp_Lin&                          aAxis,
                                  const gp_Pnt&                          OffsetPoint);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Circ&                         aCircle1,
                                  const gp_Lin&                          aAxis,
                                  const gp_Pnt&                          OffsetPoint);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Lin&                          aAxis,
                                  const gp_Pnt&                          OffsetPoint);
};
