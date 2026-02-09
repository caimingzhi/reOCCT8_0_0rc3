#include <Graphic3d_AspectLine3d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_AspectLine3d, Graphic3d_Aspects)

Graphic3d_AspectLine3d::Graphic3d_AspectLine3d()
{
  myShadingModel = Graphic3d_TypeOfShadingModel_Unlit;
  myInteriorColor.SetRGB(Quantity_NOC_YELLOW);
  myLineType  = Aspect_TOL_SOLID;
  myLineWidth = 1.0f;
}

Graphic3d_AspectLine3d::Graphic3d_AspectLine3d(const Quantity_Color& theColor,
                                               Aspect_TypeOfLine     theType,
                                               double                theWidth)
{
  myShadingModel = Graphic3d_TypeOfShadingModel_Unlit;
  myInteriorColor.SetRGB(theColor);
  SetLineType(theType);
  SetLineWidth((float)theWidth);
}
