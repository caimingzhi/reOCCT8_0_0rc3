#include <Graphic3d_AspectFillArea3d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_AspectFillArea3d, Graphic3d_Aspects)

Graphic3d_AspectFillArea3d::Graphic3d_AspectFillArea3d()
{
  myInteriorStyle = Aspect_IS_EMPTY;
}

Graphic3d_AspectFillArea3d::Graphic3d_AspectFillArea3d(
  const Aspect_InteriorStyle      theInteriorStyle,
  const Quantity_Color&           theInteriorColor,
  const Quantity_Color&           theEdgeColor,
  const Aspect_TypeOfLine         theEdgeLineType,
  const double                    theEdgeLineWidth,
  const Graphic3d_MaterialAspect& theFrontMaterial,
  const Graphic3d_MaterialAspect& theBackMaterial)
{
  myFrontMaterial = theFrontMaterial;
  myBackMaterial  = theBackMaterial;
  myInteriorColor.SetRGB(theInteriorColor);
  myBackInteriorColor.SetRGB(theInteriorColor);
  myEdgeColor.SetRGB(theEdgeColor);
  myInteriorStyle = theInteriorStyle;
  myLineType      = theEdgeLineType;
  SetEdgeWidth((float)theEdgeLineWidth);
}
