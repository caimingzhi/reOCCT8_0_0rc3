#include <DsgPrs_ShadedPlanePresentation.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_ArrayOfPolygons.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_PlaneAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_ShadingAspect.hpp>

void DsgPrs_ShadedPlanePresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                         const occ::handle<Prs3d_Drawer>&       aDrawer,
                                         const gp_Pnt&                          aPt1,
                                         const gp_Pnt&                          aPt2,
                                         const gp_Pnt&                          aPt3)
{
  occ::handle<Graphic3d_Group> aGroup = aPresentation->CurrentGroup();
  aGroup->SetPrimitivesAspect(aDrawer->PlaneAspect()->EdgesAspect()->Aspect());
  aGroup->SetPrimitivesAspect(aDrawer->ShadingAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfPolygons> aPrims = new Graphic3d_ArrayOfPolygons(4);
  aPrims->AddVertex(aPt1);
  aPrims->AddVertex(aPt2);
  aPrims->AddVertex(aPt3);
  aPrims->AddVertex(aPt1);
  aGroup->AddPrimitiveArray(aPrims);
}
