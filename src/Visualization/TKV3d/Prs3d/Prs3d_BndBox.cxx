#include <Prs3d_BndBox.hpp>

#include <Prs3d_LineAspect.hpp>

//=================================================================================================

void Prs3d_BndBox::Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                       const Bnd_Box&                         theBndBox,
                       const occ::handle<Prs3d_Drawer>&       theDrawer)
{
  if (!theBndBox.IsVoid())
  {
    occ::handle<Graphic3d_Group> aGroup = thePresentation->CurrentGroup();
    aGroup->SetGroupPrimitivesAspect(
      new Graphic3d_AspectLine3d(theDrawer->LineAspect()->Aspect()->Color(),
                                 Aspect_TOL_DOTDASH,
                                 theDrawer->LineAspect()->Aspect()->Width()));
    aGroup->AddPrimitiveArray(FillSegments(theBndBox));
  }
}

//=================================================================================================

void Prs3d_BndBox::Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                       const Bnd_OBB&                         theBndBox,
                       const occ::handle<Prs3d_Drawer>&       theDrawer)
{
  if (!theBndBox.IsVoid())
  {
    occ::handle<Graphic3d_Group> aGroup = thePresentation->CurrentGroup();
    aGroup->SetGroupPrimitivesAspect(
      new Graphic3d_AspectLine3d(theDrawer->LineAspect()->Aspect()->Color(),
                                 Aspect_TOL_DOTDASH,
                                 theDrawer->LineAspect()->Aspect()->Width()));
    aGroup->AddPrimitiveArray(FillSegments(theBndBox));
  }
}
