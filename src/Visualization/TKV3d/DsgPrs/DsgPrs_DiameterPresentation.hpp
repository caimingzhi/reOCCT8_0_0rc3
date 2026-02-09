#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Pnt;
class gp_Circ;

class DsgPrs_DiameterPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          AttachmentPoint,
                                  const gp_Circ&                         aCircle,
                                  const DsgPrs_ArrowSide                 ArrowSide,
                                  const bool                             IsDiamSymbol);

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
