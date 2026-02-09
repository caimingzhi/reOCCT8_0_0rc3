

#include <Graphic3d_Text.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_Text, Standard_Transient)

Graphic3d_Text::Graphic3d_Text(const float theHeight)
    : myHeight(theHeight),
      myHAlign(Graphic3d_HTA_LEFT),
      myVAlign(Graphic3d_VTA_BOTTOM),
      myHasPlane(false),
      myHasOwnAnchor(true)
{
}

void Graphic3d_Text::SetOrientation(const gp_Ax2& theOrientation)
{
  myOrientation = theOrientation;
  myHasPlane    = true;
}

void Graphic3d_Text::ResetOrientation()
{
  myOrientation = gp_Ax2();
  myHasPlane    = false;
}
