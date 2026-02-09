#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Pnt;
class gp_Ax2;
class gp_Elips;

class DsgPrs_IdenticPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          aPntAttach,
                                  const gp_Pnt&                          aPntOffset);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          aFAttach,
                                  const gp_Pnt&                          aSAttach,
                                  const gp_Pnt&                          aPntOffset);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Ax2&                          aAx2,
                                  const gp_Pnt&                          aCenter,
                                  const gp_Pnt&                          aFAttach,
                                  const gp_Pnt&                          aSAttach,
                                  const gp_Pnt&                          aPntOffset);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Ax2&                          aAx2,
                                  const gp_Pnt&                          aCenter,
                                  const gp_Pnt&                          aFAttach,
                                  const gp_Pnt&                          aSAttach,
                                  const gp_Pnt&                          aPntOffset,
                                  const gp_Pnt&                          aPntOnCirc);

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Elips&                        anEllipse,
                                  const gp_Pnt&                          aFAttach,
                                  const gp_Pnt&                          aSAttach,
                                  const gp_Pnt&                          aPntOffset,
                                  const gp_Pnt&                          aPntOnElli);
};
