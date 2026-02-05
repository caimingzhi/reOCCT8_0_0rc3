#include <Draw_Display.hpp>
#include <Draw_Text2D.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Text2D, Draw_Drawable2D)

//=================================================================================================

Draw_Text2D::Draw_Text2D(const gp_Pnt2d& p, const char* T, const Draw_Color& col)
    : myPoint(p),
      myColor(col),
      myText(T),
      mymoveX(0),
      mymoveY(0)
{
}

//=================================================================================================

Draw_Text2D::Draw_Text2D(const gp_Pnt2d&   p,
                         const char*       T,
                         const Draw_Color& col,
                         const int         moveX,
                         const int         moveY)
    : myPoint(p),
      myColor(col),
      myText(T),
      mymoveX(moveX),
      mymoveY(moveY)
{
}

//=================================================================================================

void Draw_Text2D::SetPnt2d(const gp_Pnt2d& p)
{
  myPoint = p;
}

//=================================================================================================

void Draw_Text2D::DrawOn(Draw_Display& dis) const
{
  dis.SetColor(myColor);
  dis.DrawString(myPoint, myText.ToCString(), (double)mymoveX, (double)mymoveY);
}
