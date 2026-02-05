#include <Draw_Axis2D.hpp>
#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Axis2D, Draw_Drawable2D)

extern bool Draw_Bounds;

//=================================================================================================

Draw_Axis2D::Draw_Axis2D(const Draw_Color& col, const int Size)
    : myAxes(gp_Pnt2d(0, 0), gp_Dir2d(gp_Dir2d::D::X)),
      myColor(col),
      mySize(Size)
{
}

//=================================================================================================

Draw_Axis2D::Draw_Axis2D(const gp_Pnt2d& p, const Draw_Color& col, const int Size)
    : myAxes(p, gp_Dir2d(gp_Dir2d::D::X)),
      myColor(col),
      mySize(Size)
{
}

//=================================================================================================

Draw_Axis2D::Draw_Axis2D(const gp_Ax22d& a, const Draw_Color& col, const int Size)
    : myAxes(a),
      myColor(col),
      mySize(Size)
{
}

//=================================================================================================

void Draw_Axis2D::DrawOn(Draw_Display& dis) const
{
  Draw_Bounds = false;
  dis.SetColor(myColor);
  double z = dis.Zoom();
  z        = (double)mySize / z;
  gp_Pnt2d P, P0 = myAxes.Location();
  P = P0.Translated(gp_Vec2d(myAxes.XDirection()) * z);
  dis.Draw(P0, P);
  dis.DrawString(P, "X");
  P = P0.Translated(gp_Vec2d(myAxes.YDirection()) * z);
  dis.Draw(P0, P);
  dis.DrawString(P, "Y");
  Draw_Bounds = true;
}
