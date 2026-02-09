#include <Prs3d_Text.hpp>

#include <gp_Pnt.hpp>
#include <Graphic3d_Group.hpp>
#include <Graphic3d_Text.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_TextAspect.hpp>
#include <TCollection_ExtendedString.hpp>

occ::handle<Graphic3d_Text> Prs3d_Text::Draw(const occ::handle<Graphic3d_Group>&  theGroup,
                                             const occ::handle<Prs3d_TextAspect>& theAspect,
                                             const TCollection_ExtendedString&    theText,
                                             const gp_Pnt& theAttachmentPoint)
{
  theGroup->SetPrimitivesAspect(theAspect->Aspect());

  occ::handle<Graphic3d_Text> aText = new Graphic3d_Text((float)theAspect->Height());
  aText->SetText(theText.ToExtString());
  aText->SetPosition(theAttachmentPoint);
  aText->SetHorizontalAlignment(theAspect->HorizontalJustification());
  aText->SetVerticalAlignment(theAspect->VerticalJustification());
  theGroup->AddText(aText);
  return aText;
}

occ::handle<Graphic3d_Text> Prs3d_Text::Draw(const occ::handle<Graphic3d_Group>&  theGroup,
                                             const occ::handle<Prs3d_TextAspect>& theAspect,
                                             const TCollection_ExtendedString&    theText,
                                             const gp_Ax2&                        theOrientation,
                                             const bool                           theHasOwnAnchor)
{
  theGroup->SetPrimitivesAspect(theAspect->Aspect());

  occ::handle<Graphic3d_Text> aText = new Graphic3d_Text((float)theAspect->Height());
  aText->SetText(theText.ToExtString());
  aText->SetOrientation(theOrientation);
  aText->SetOwnAnchorPoint(theHasOwnAnchor);
  aText->SetHorizontalAlignment(theAspect->HorizontalJustification());
  aText->SetVerticalAlignment(theAspect->VerticalJustification());
  theGroup->AddText(aText);
  return aText;
}
