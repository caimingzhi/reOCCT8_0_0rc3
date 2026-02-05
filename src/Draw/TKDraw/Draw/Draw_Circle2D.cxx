#include <Draw_Circle2D.hpp>
#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <gp_Circ2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Circle2D, Draw_Drawable2D)

//=================================================================================================

Draw_Circle2D::Draw_Circle2D(const gp_Circ2d&  C,
                             const double      A1,
                             const double      A2,
                             const Draw_Color& col)
    : myCirc(C),
      myA1(A1),
      myA2(A2),
      myColor(col)
{
}

//=================================================================================================

void Draw_Circle2D::DrawOn(Draw_Display& d) const
{
  d.SetColor(myColor);
  d.Draw(myCirc, myA1, myA2);
}
