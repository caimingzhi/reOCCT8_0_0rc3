

#include <Prs3d_ShadingAspect.hpp>

#include <Graphic3d_AspectFillArea3d.hpp>
#include <Graphic3d_MaterialAspect.hpp>
#include <Quantity_Color.hpp>
#include <Standard_Type.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Prs3d_ShadingAspect, Prs3d_BasicAspect)

Prs3d_ShadingAspect::Prs3d_ShadingAspect()
{
  const Graphic3d_MaterialAspect aMat(Graphic3d_NameOfMaterial_Brass);
  const Quantity_Color           aColor = aMat.AmbientColor();
  myAspect                              = new Graphic3d_AspectFillArea3d(Aspect_IS_SOLID,
                                            aColor,
                                            aColor,
                                            Aspect_TOL_SOLID,
                                            1.0,
                                            aMat,
                                            aMat);
}

void Prs3d_ShadingAspect::SetColor(const Quantity_Color&          theColor,
                                   const Aspect_TypeOfFacingModel theModel)
{
  if (theModel != Aspect_TOFM_BOTH_SIDE)
  {
    myAspect->SetDistinguishOn();
  }

  if (theModel == Aspect_TOFM_FRONT_SIDE || theModel == Aspect_TOFM_BOTH_SIDE)
  {
    myAspect->ChangeFrontMaterial().SetColor(theColor);
    myAspect->SetInteriorColor(theColor);
  }

  if (theModel == Aspect_TOFM_BACK_SIDE || theModel == Aspect_TOFM_BOTH_SIDE)
  {
    myAspect->ChangeBackMaterial().SetColor(theColor);
    myAspect->SetBackInteriorColor(theColor);
  }
}

const Quantity_Color& Prs3d_ShadingAspect::Color(const Aspect_TypeOfFacingModel theModel) const
{
  switch (theModel)
  {
    default:
    case Aspect_TOFM_BOTH_SIDE:
    case Aspect_TOFM_FRONT_SIDE:
      return myAspect->FrontMaterial().MaterialType() == Graphic3d_MATERIAL_ASPECT
               ? myAspect->InteriorColor()
               : myAspect->FrontMaterial().Color();
    case Aspect_TOFM_BACK_SIDE:
      return myAspect->BackMaterial().MaterialType() == Graphic3d_MATERIAL_ASPECT
               ? myAspect->BackInteriorColor()
               : myAspect->BackMaterial().Color();
  }
}

void Prs3d_ShadingAspect::SetMaterial(const Graphic3d_MaterialAspect& theMaterial,
                                      const Aspect_TypeOfFacingModel  theModel)
{
  if (theModel != Aspect_TOFM_BOTH_SIDE)
  {
    myAspect->SetDistinguishOn();
  }
  if (theModel == Aspect_TOFM_FRONT_SIDE || theModel == Aspect_TOFM_BOTH_SIDE)
  {
    myAspect->SetFrontMaterial(theMaterial);
  }

  if (theModel == Aspect_TOFM_BACK_SIDE || theModel == Aspect_TOFM_BOTH_SIDE)
  {
    myAspect->SetBackMaterial(theMaterial);
  }
}

const Graphic3d_MaterialAspect& Prs3d_ShadingAspect::Material(
  const Aspect_TypeOfFacingModel theModel) const
{
  switch (theModel)
  {
    default:
    case Aspect_TOFM_BOTH_SIDE:
    case Aspect_TOFM_FRONT_SIDE:
      return myAspect->FrontMaterial();
    case Aspect_TOFM_BACK_SIDE:
      return myAspect->BackMaterial();
  }
}

void Prs3d_ShadingAspect::SetTransparency(const double                   theValue,
                                          const Aspect_TypeOfFacingModel theModel)
{
  if (theModel != Aspect_TOFM_BOTH_SIDE)
  {
    myAspect->SetDistinguishOn();
  }

  if (theModel == Aspect_TOFM_FRONT_SIDE || theModel == Aspect_TOFM_BOTH_SIDE)
  {
    myAspect->ChangeFrontMaterial().SetTransparency(float(theValue));
    myAspect->SetInteriorColor(
      Quantity_ColorRGBA(myAspect->InteriorColor(), 1.0f - float(theValue)));
  }

  if (theModel == Aspect_TOFM_BACK_SIDE || theModel == Aspect_TOFM_BOTH_SIDE)
  {
    myAspect->ChangeBackMaterial().SetTransparency(float(theValue));
    myAspect->SetBackInteriorColor(
      Quantity_ColorRGBA(myAspect->BackInteriorColor(), 1.0f - float(theValue)));
  }
}

double Prs3d_ShadingAspect::Transparency(const Aspect_TypeOfFacingModel theModel) const
{
  switch (theModel)
  {
    case Aspect_TOFM_BOTH_SIDE:
    case Aspect_TOFM_FRONT_SIDE:
      return myAspect->FrontMaterial().Transparency();
    case Aspect_TOFM_BACK_SIDE:
      return myAspect->BackMaterial().Transparency();
  }
  return 0.0;
}

void Prs3d_ShadingAspect::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myAspect.get())
}
