#pragma once


#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_TextAspect.hpp>

class TCollection_ExtendedString;
class gp_Pnt;

//! A framework to define the display of texts.
class Prs3d_Text
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines the display of the text.
  //! @param theGroup  group to add primitives
  //! @param theAspect presentation attributes
  //! @param theText   text to draw
  //! @param theAttachmentPoint attachment point
  //! @return text to draw
  Standard_EXPORT static occ::handle<Graphic3d_Text> Draw(
    const occ::handle<Graphic3d_Group>&  theGroup,
    const occ::handle<Prs3d_TextAspect>& theAspect,
    const TCollection_ExtendedString&    theText,
    const gp_Pnt&                        theAttachmentPoint);

  //! Draws the text label.
  //! @param theGroup       group to add primitives
  //! @param theAspect      presentation attributes
  //! @param theText        text to draw
  //! @param theOrientation location and orientation specified in the model 3D space
  //! @param theHasOwnAnchor
  //! @return text to draw
  Standard_EXPORT static occ::handle<Graphic3d_Text> Draw(
    const occ::handle<Graphic3d_Group>&  theGroup,
    const occ::handle<Prs3d_TextAspect>& theAspect,
    const TCollection_ExtendedString&    theText,
    const gp_Ax2&                        theOrientation,
    const bool                           theHasOwnAnchor = true);
};

