#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Drawer.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class TCollection_ExtendedString;

//! Framework for display of 2D chamfers.
class DsgPrs_Chamf2dPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines the display of elements showing 2D chamfers on shapes.
  //! These include the text aText, the point of attachment,
  //! aPntAttach and the end point aPntEnd.
  //! These arguments are added to the presentation
  //! object aPresentation. Their display attributes are
  //! defined by the attribute manager aDrawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          aPntAttach,
                                  const gp_Pnt&                          aPntEnd,
                                  const TCollection_ExtendedString&      aText);

  //! Defines the display of texts, symbols and icons used
  //! to present 2D chamfers.
  //! These include the text aText, the point of attachment,
  //! aPntAttach and the end point aPntEnd.
  //! These arguments are added to the presentation
  //! object aPresentation. Their display attributes are
  //! defined by the attribute manager aDrawer. The arrow
  //! at the point of attachment has a display defined by a
  //! value of the enumeration DsgPrs_Arrowside.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          aPntAttach,
                                  const gp_Pnt&                          aPntEnd,
                                  const TCollection_ExtendedString&      aText,
                                  const DsgPrs_ArrowSide                 ArrowSide);
};
