#include <Draw_Circle3D.hpp>
#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <gp_Circ.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Circle3D, Draw_Drawable3D)

//=================================================================================================

Draw_Circle3D::Draw_Circle3D(const gp_Circ&    C,
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

void Draw_Circle3D::DrawOn(Draw_Display& d) const
{
  d.SetColor(myColor);
  d.Draw(myCirc, myA1, myA2);
}
