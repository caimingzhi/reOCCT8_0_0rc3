#include <V3d_Plane.hpp>

#include <Graphic3d_Group.hpp>
#include <Graphic3d_AspectFillArea3d.hpp>
#include <Graphic3d_ArrayOfQuadrangles.hpp>
#include <gp_Pln.hpp>
#include <V3d_Viewer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(V3d_Plane, Standard_Transient)

V3d_Plane::V3d_Plane(const double theA, const double theB, const double theC, const double theD)
    : myPlane(new Graphic3d_ClipPlane(gp_Pln(theA, theB, theC, theD)))
{
}

void V3d_Plane::SetPlane(const double theA, const double theB, const double theC, const double theD)
{
  myPlane->SetEquation(gp_Pln(theA, theB, theC, theD));
  if (IsDisplayed())
  {
    Update();
  }
}

void V3d_Plane::Display(const occ::handle<V3d_View>& theView, const Quantity_Color& theColor)
{
  occ::handle<V3d_Viewer> aViewer = theView->Viewer();
  if (!myGraphicStructure.IsNull())
  {
    myGraphicStructure->Clear();
  }

  myGraphicStructure = new Graphic3d_Structure(aViewer->StructureManager());
  occ::handle<Graphic3d_Group>            aGroup = myGraphicStructure->NewGroup();
  occ::handle<Graphic3d_AspectFillArea3d> anAsp  = new Graphic3d_AspectFillArea3d();
  Graphic3d_MaterialAspect                aPlastic(Graphic3d_NameOfMaterial_Plastified);
  aPlastic.SetColor(theColor);
  aPlastic.SetTransparency(0.5);
  anAsp->SetFrontMaterial(aPlastic);
  anAsp->SetInteriorStyle(Aspect_IS_HATCH);
  anAsp->SetHatchStyle(new Graphic3d_HatchStyle(Aspect_HS_GRID_DIAGONAL_WIDE));
  aGroup->SetGroupPrimitivesAspect(anAsp);

  const float aSize    = (float)(0.5 * aViewer->DefaultViewSize());
  const float anOffset = aSize / 5000.0f;

  occ::handle<Graphic3d_ArrayOfQuadrangles> aPrims = new Graphic3d_ArrayOfQuadrangles(4);
  aPrims->AddVertex(-aSize, -aSize, anOffset);
  aPrims->AddVertex(-aSize, aSize, anOffset);
  aPrims->AddVertex(aSize, aSize, anOffset);
  aPrims->AddVertex(aSize, -aSize, anOffset);
  aGroup->AddPrimitiveArray(aPrims);

  myGraphicStructure->SetDisplayPriority(Graphic3d_DisplayPriority_Bottom);
  myGraphicStructure->Display();
  Update();
}

void V3d_Plane::Erase()
{
  if (!myGraphicStructure.IsNull())
  {
    myGraphicStructure->Erase();
  }
}

void V3d_Plane::Plane(double& theA, double& theB, double& theC, double& theD) const
{
  const Graphic3d_ClipPlane::Equation& anEquation = myPlane->GetEquation();
  theA                                            = anEquation[0];
  theB                                            = anEquation[1];
  theC                                            = anEquation[2];
  theD                                            = anEquation[3];
}

bool V3d_Plane::IsDisplayed() const
{
  if (myGraphicStructure.IsNull())
  {
    return false;
  }

  return myGraphicStructure->IsDisplayed();
}

void V3d_Plane::Update()
{
  if (myGraphicStructure.IsNull())
  {
    return;
  }

  const gp_Pln aGeomPln = myPlane->ToPlane();
  gp_Trsf      aTransform;
  aTransform.SetTransformation(aGeomPln.Position());
  aTransform.Invert();
  myGraphicStructure->SetTransformation(new TopLoc_Datum3D(aTransform));
}
