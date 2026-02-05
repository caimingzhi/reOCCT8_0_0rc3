#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <QABugs_PresentableObject.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(QABugs_PresentableObject, AIS_InteractiveObject)

QABugs_PresentableObject::QABugs_PresentableObject(
  const PrsMgr_TypeOfPresentation3d theTypeOfPresentation3d)
    : AIS_InteractiveObject(theTypeOfPresentation3d)
{
}

void QABugs_PresentableObject::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                       const occ::handle<Prs3d_Presentation>& thePrs,
                                       const int                              theMode)
{
  const occ::handle<Graphic3d_Structure>& aStructure = thePrs;
  occ::handle<Graphic3d_Group>            aGroup     = aStructure->NewGroup();
  occ::handle<Prs3d_ShadingAspect>        anAspect   = myDrawer->ShadingAspect();
  Graphic3d_MaterialAspect                aMat       = anAspect->Aspect()->FrontMaterial();
  aMat.SetAmbientColor(Quantity_NOC_BLACK);
  aMat.SetDiffuseColor(Quantity_NOC_BLACK);
  aMat.SetSpecularColor(Quantity_NOC_BLACK);
  aMat.SetEmissiveColor(Quantity_NOC_BLACK);
  anAspect->SetMaterial(aMat);
  aGroup->SetPrimitivesAspect(anAspect->Aspect());

  occ::handle<Graphic3d_ArrayOfTriangles> aPrims =
    new Graphic3d_ArrayOfTriangles(6,
                                   0,
                                   theMode == 1, // normals
                                   true);        // color per vertex
  switch (theMode)
  {
    case 0:
    {
      aPrims->AddVertex(gp_Pnt(0.0, 0.0, 0.0), Quantity_Color(Quantity_NOC_RED));
      aPrims->AddVertex(gp_Pnt(0.0, 5.0, 1.0), Quantity_Color(Quantity_NOC_BLUE1));
      aPrims->AddVertex(gp_Pnt(5.0, 0.0, 1.0), Quantity_Color(Quantity_NOC_YELLOW));

      aPrims->AddVertex(gp_Pnt(0.0, 5.0, 1.0), Quantity_Color(Quantity_NOC_BLUE1));
      aPrims->AddVertex(gp_Pnt(5.0, 5.0, -1.0), Quantity_Color(Quantity_NOC_GREEN));
      aPrims->AddVertex(gp_Pnt(5.0, 0.0, 1.0), Quantity_Color(Quantity_NOC_YELLOW));
      break;
    }
    case 1:
    {
      aPrims->AddVertex(gp_Pnt(5.0, 0.0, 0.0),
                        gp_Dir(gp_Dir::D::Z),
                        Quantity_Color(Quantity_NOC_RED));
      aPrims->AddVertex(gp_Pnt(5.0, 5.0, 1.0),
                        gp_Dir(1.0, 1.0, 1.0),
                        Quantity_Color(Quantity_NOC_BLUE1));
      aPrims->AddVertex(gp_Pnt(10.0, 0.0, 1.0),
                        gp_Dir(0.0, 1.0, 1.0),
                        Quantity_Color(Quantity_NOC_YELLOW));

      aPrims->AddVertex(gp_Pnt(5.0, 5.0, 1.0),
                        gp_Dir(1.0, 1.0, 1.0),
                        Quantity_Color(Quantity_NOC_BLUE1));
      aPrims->AddVertex(gp_Pnt(10.0, 5.0, -1.0),
                        gp_Dir(gp_Dir::D::NZ),
                        Quantity_Color(Quantity_NOC_GREEN));
      aPrims->AddVertex(gp_Pnt(10.0, 0.0, 1.0),
                        gp_Dir(0.0, 1.0, 1.0),
                        Quantity_Color(Quantity_NOC_YELLOW));
    }
    break;
  }

  aGroup->AddPrimitiveArray(aPrims);
}

void QABugs_PresentableObject::ComputeSelection(const occ::handle<SelectMgr_Selection>&, const int)
{
}
