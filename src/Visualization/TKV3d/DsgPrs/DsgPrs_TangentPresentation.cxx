#include <DsgPrs_TangentPresentation.hpp>
#include <Geom_CartesianPoint.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <StdPrs_Point.hpp>

void DsgPrs_TangentPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_Drawer>&       aDrawer,
                                     const gp_Pnt&                          OffsetPoint,
                                     const gp_Dir&                          aDirection,
                                     const double                           length)
{
  gp_Vec vec(aDirection);
  gp_Vec vec1 = vec.Multiplied(length);
  gp_Vec vec2 = vec.Multiplied(-length);
  gp_Pnt p1   = OffsetPoint.Translated(vec1);
  gp_Pnt p2   = OffsetPoint.Translated(vec2);

  // Aspect
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  LA->LineAspect()->SetTypeOfLine(Aspect_TOL_SOLID);
  occ::handle<Prs3d_ArrowAspect> ARR1 = LA->ArrowAspect();
  occ::handle<Prs3d_ArrowAspect> ARR2 = LA->ArrowAspect();
  ARR1->SetLength(length / 5);
  ARR2->SetLength(length / 5);

  // Array1OfVertex
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(p1);
  aPrims->AddVertex(p2);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  // fleche 1 :
  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());
  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    p1,
                    aDirection,
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());

  // fleche 2
  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());
  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    p2,
                    aDirection.Reversed(),
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());
}
