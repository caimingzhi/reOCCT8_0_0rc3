#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Pnt;
class gp_Circ;

class DsgPrs_RadiusPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint,
                                  const gp_Circ&                         aCircle,
                                  const double                           firstparam,
                                  const double                           lastparam,
                                  const bool                             drawFromCenter = true,
                                  const bool                             reverseArrow   = false);

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
