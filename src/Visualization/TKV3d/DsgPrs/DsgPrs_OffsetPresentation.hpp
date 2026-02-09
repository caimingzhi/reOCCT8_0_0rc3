#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Pnt;
class gp_Dir;

class DsgPrs_OffsetPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint1,
                                  const gp_Pnt&                          AttachmentPoint2,
                                  const gp_Dir&                          aDirection,
                                  const gp_Dir&                          aDirection2,
                                  const gp_Pnt&                          OffsetPoint);

  Standard_EXPORT static void AddAxes(const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const occ::handle<Prs3d_Drawer>&       aDrawer,
                                      const TCollection_ExtendedString&      aText,
                                      const gp_Pnt&                          AttachmentPoint1,
                                      const gp_Pnt&                          AttachmentPoint2,
                                      const gp_Dir&                          aDirection,
                                      const gp_Dir&                          aDirection2,
                                      const gp_Pnt&                          OffsetPoint);
};
