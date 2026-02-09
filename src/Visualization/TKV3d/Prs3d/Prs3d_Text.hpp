#pragma once

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_TextAspect.hpp>

class TCollection_ExtendedString;
class gp_Pnt;

class Prs3d_Text
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Graphic3d_Text> Draw(
    const occ::handle<Graphic3d_Group>&  theGroup,
    const occ::handle<Prs3d_TextAspect>& theAspect,
    const TCollection_ExtendedString&    theText,
    const gp_Pnt&                        theAttachmentPoint);

  Standard_EXPORT static occ::handle<Graphic3d_Text> Draw(
    const occ::handle<Graphic3d_Group>&  theGroup,
    const occ::handle<Prs3d_TextAspect>& theAspect,
    const TCollection_ExtendedString&    theText,
    const gp_Ax2&                        theOrientation,
    const bool                           theHasOwnAnchor = true);
};
