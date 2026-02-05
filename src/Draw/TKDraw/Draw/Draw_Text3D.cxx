#include <Draw_Display.hpp>
#include <Draw_Text3D.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Text3D, Draw_Drawable3D)

//=================================================================================================

Draw_Text3D::Draw_Text3D(const gp_Pnt& p, const char* T, const Draw_Color& col)
    : myPoint(p),
      myColor(col),
      myText(T),
      mymoveX(0.0),
      mymoveY(0.0)
{
}

//=================================================================================================

Draw_Text3D::Draw_Text3D(const gp_Pnt&     p,
                         const char*       T,
                         const Draw_Color& col,
                         const double      moveX,
                         const double      moveY)
    : myPoint(p),
      myColor(col),
      myText(T),
      mymoveX(moveX),
      mymoveY(moveY)
{
}

//=================================================================================================

void Draw_Text3D::SetPnt(const gp_Pnt& p)
{
  myPoint = p;
}

//=================================================================================================

void Draw_Text3D::DrawOn(Draw_Display& dis) const
{
  dis.SetColor(myColor);
  dis.DrawString(myPoint, myText.ToCString(), mymoveX, mymoveY);
}
