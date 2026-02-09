#include <DsgPrs_XYZPlanePresentation.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_PlaneAspect.hpp>
#include <Prs3d_Presentation.hpp>

void DsgPrs_XYZPlanePresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const occ::handle<Prs3d_Drawer>&       aDrawer,
                                      const gp_Pnt&                          aPt1,
                                      const gp_Pnt&                          aPt2,
                                      const gp_Pnt&                          aPt3)
{
  occ::handle<Graphic3d_Group> TheGroup = aPresentation->CurrentGroup();
  TheGroup->SetPrimitivesAspect(aDrawer->PlaneAspect()->EdgesAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfPolylines> aPrims = new Graphic3d_ArrayOfPolylines(4);
  aPrims->AddVertex(aPt1);
  aPrims->AddVertex(aPt2);
  aPrims->AddVertex(aPt3);
  aPrims->AddVertex(aPt1);
  TheGroup->AddPrimitiveArray(aPrims);
}
