#include <DsgPrs.hpp>
#include <DsgPrs_Chamf2dPresentation.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>
#include <TCollection_ExtendedString.hpp>

void DsgPrs_Chamf2dPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_Drawer>&       aDrawer,
                                     const gp_Pnt&                          aPntAttach,
                                     const gp_Pnt&                          aPntEnd,
                                     const TCollection_ExtendedString&      aText)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();

  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(aPntAttach);
  aPrims->AddVertex(aPntEnd);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  gp_Dir ArrowDir(aPntAttach.XYZ() - aPntEnd.XYZ());
  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    aPntAttach,
                    ArrowDir,
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, aPntEnd);
}

void DsgPrs_Chamf2dPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_Drawer>&       aDrawer,
                                     const gp_Pnt&                          aPntAttach,
                                     const gp_Pnt&                          aPntEnd,
                                     const TCollection_ExtendedString&      aText,
                                     const DsgPrs_ArrowSide                 ArrowPrs)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();

  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(aPntAttach);
  aPrims->AddVertex(aPntEnd);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, aPntEnd);

  gp_Dir ArrowDir(aPntAttach.XYZ() - aPntEnd.XYZ());
  gp_Dir ArrowDir1 = ArrowDir;
  ArrowDir1.Reverse();

  DsgPrs::ComputeSymbol(aPresentation, LA, aPntEnd, aPntAttach, ArrowDir1, ArrowDir, ArrowPrs);
}
