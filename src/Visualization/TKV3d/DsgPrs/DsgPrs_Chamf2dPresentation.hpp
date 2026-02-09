#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Drawer.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class TCollection_ExtendedString;

class DsgPrs_Chamf2dPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          aPntAttach,
                                  const gp_Pnt&                          aPntEnd,
                                  const TCollection_ExtendedString&      aText);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          aPntAttach,
                                  const gp_Pnt&                          aPntEnd,
                                  const TCollection_ExtendedString&      aText,
                                  const DsgPrs_ArrowSide                 ArrowSide);
};
