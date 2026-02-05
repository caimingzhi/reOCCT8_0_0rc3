#include <DsgPrs_XYZAxisPresentation.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_Text.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_ArrowAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_TextAspect.hpp>

//=================================================================================================

void DsgPrs_XYZAxisPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_LineAspect>&   aLineAspect,
                                     const gp_Dir&                          aDir,
                                     const double                           aVal,
                                     const char*                            theText,
                                     const gp_Pnt&                          aPfirst,
                                     const gp_Pnt&                          aPlast)
{
  occ::handle<Graphic3d_Group> G = aPresentation->CurrentGroup();
  G->SetPrimitivesAspect(aLineAspect->Aspect());

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(aPfirst);
  aPrims->AddVertex(aPlast);
  G->AddPrimitiveArray(aPrims);

  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(), aPlast, aDir, M_PI / 180. * 10., aVal / 10.);

  if (*theText != '\0')
  {
    occ::handle<Graphic3d_Text> aText = new Graphic3d_Text(1.0f / 81.0f);
    aText->SetText(theText);
    aText->SetPosition(aPlast);
    aPresentation->CurrentGroup()->AddText(aText);
  }
}

void DsgPrs_XYZAxisPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_LineAspect>&   aLineAspect,
                                     const occ::handle<Prs3d_ArrowAspect>&  anArrowAspect,
                                     const occ::handle<Prs3d_TextAspect>&   aTextAspect,
                                     const gp_Dir&                          aDir,
                                     const double                           aVal,
                                     const char*                            theText,
                                     const gp_Pnt&                          aPfirst,
                                     const gp_Pnt&                          aPlast)
{
  occ::handle<Graphic3d_Group> G = aPresentation->CurrentGroup();
  G->SetPrimitivesAspect(aLineAspect->Aspect());

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(aPfirst);
  aPrims->AddVertex(aPlast);
  G->AddPrimitiveArray(aPrims);

  G->SetPrimitivesAspect(anArrowAspect->Aspect());
  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    aPlast,
                    aDir,
                    anArrowAspect->Angle(),
                    aVal / 10.);

  G->SetPrimitivesAspect(aTextAspect->Aspect());

  if (*theText != '\0')
  {
    occ::handle<Graphic3d_Text> aText = new Graphic3d_Text(1.0f / 81.0f);
    aText->SetText(theText);
    aText->SetPosition(aPlast);
    aPresentation->CurrentGroup()->AddText(aText);
  }
}
