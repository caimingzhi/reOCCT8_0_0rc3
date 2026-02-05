#include <DsgPrs_PerpenPresentation.hpp>
#include <ElCLib.hpp>
#include <gce_MakeDir.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>

void DsgPrs_PerpenPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                    const occ::handle<Prs3d_Drawer>&       aDrawer,
                                    const gp_Pnt&                          pAx1,
                                    const gp_Pnt&                          pAx2,
                                    const gp_Pnt&                          pnt1,
                                    const gp_Pnt&                          pnt2,
                                    const gp_Pnt&                          OffsetPoint,
                                    const bool                             intOut1,
                                    const bool                             intOut2)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  LA->LineAspect()->SetTypeOfLine(Aspect_TOL_SOLID); // ou DOT ou DOTDASH
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  // segments
  occ::handle<Graphic3d_ArrayOfPrimitives> aPrims = new Graphic3d_ArrayOfPolylines(6, 2);

  aPrims->AddBound(3);
  aPrims->AddVertex(OffsetPoint);
  aPrims->AddVertex(pAx1);
  aPrims->AddVertex(pAx2);

  // Symbol
  gp_Vec vec1(gce_MakeDir(OffsetPoint, pAx1));
  gp_Vec vec2(gce_MakeDir(OffsetPoint, pAx2));
  vec1 *= .2 * OffsetPoint.Distance(pAx1);
  vec2 *= .2 * OffsetPoint.Distance(pAx2);

  gp_Pnt pAx11  = OffsetPoint.Translated(vec1);
  gp_Pnt pAx22  = OffsetPoint.Translated(vec2);
  gp_Pnt p_symb = pAx22.Translated(vec1);

  aPrims->AddBound(3);
  aPrims->AddVertex(pAx11);
  aPrims->AddVertex(p_symb);
  aPrims->AddVertex(pAx22);

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  // points attache
  if (intOut1 || intOut2)
  {
    LA->LineAspect()->SetTypeOfLine(Aspect_TOL_DOT); // ou DOT ou DOTDASH
    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    if (intOut1)
    {
      aPrims = new Graphic3d_ArrayOfSegments(2);
      aPrims->AddVertex(pAx1);
      aPrims->AddVertex(pnt1);
      aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
    }
    if (intOut2)
    {
      aPrims = new Graphic3d_ArrayOfSegments(2);
      aPrims->AddVertex(pAx2);
      aPrims->AddVertex(pnt2);
      aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
    }
  }
}
