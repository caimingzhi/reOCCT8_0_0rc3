#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Standard_Real.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Circ;
class gp_Pnt;
class gp_Dir;
class gp_Ax1;

class DsgPrs_AnglePresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const double                           aVal,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Circ&                         aCircle,
                                  const gp_Pnt&                          aPosition,
                                  const gp_Pnt&                          Apex,
                                  const gp_Circ&                         VminCircle,
                                  const gp_Circ&                         VmaxCircle,
                                  const double                           aArrowSize);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const double                           theval,
                                  const gp_Pnt&                          CenterPoint,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          dir1,
                                  const gp_Dir&                          dir2,
                                  const gp_Pnt&                          OffsetPoint);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const double                           theval,
                                  const TCollection_ExtendedString&      thevalstring,
                                  const gp_Pnt&                          CenterPoint,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          dir1,
                                  const gp_Dir&                          dir2,
                                  const gp_Pnt&                          OffsetPoint);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const double                           theval,
                                  const TCollection_ExtendedString&      thevalstring,
                                  const gp_Pnt&                          CenterPoint,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          dir1,
                                  const gp_Dir&                          dir2,
                                  const gp_Pnt&                          OffsetPoint,
                                  const DsgPrs_ArrowSide                 ArrowSide);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const double                           theval,
                                  const TCollection_ExtendedString&      thevalstring,
                                  const gp_Pnt&                          CenterPoint,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          dir1,
                                  const gp_Dir&                          dir2,
                                  const gp_Dir&                          axisdir,
                                  const gp_Pnt&                          OffsetPoint);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const double                           theval,
                                  const TCollection_ExtendedString&      thevalstring,
                                  const gp_Pnt&                          CenterPoint,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          dir1,
                                  const gp_Dir&                          dir2,
                                  const gp_Dir&                          axisdir,
                                  const bool                             isPlane,
                                  const gp_Ax1&                          AxisOfSurf,
                                  const gp_Pnt&                          OffsetPoint,
                                  const DsgPrs_ArrowSide                 ArrowSide);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const double                           theval,
                                  const gp_Pnt&                          theCenter,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Ax1&                          theAxe,
                                  const DsgPrs_ArrowSide                 ArrowSide);
};
