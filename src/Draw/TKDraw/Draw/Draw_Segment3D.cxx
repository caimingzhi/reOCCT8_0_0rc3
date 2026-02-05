#include <Draw_Display.hpp>
#include <Draw_Segment3D.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Segment3D, Draw_Drawable3D)

//=================================================================================================

Draw_Segment3D::Draw_Segment3D(const gp_Pnt& p1, const gp_Pnt& p2, const Draw_Color& col)
    : myFirst(p1),
      myLast(p2),
      myColor(col)
{
}

//=================================================================================================

void Draw_Segment3D::DrawOn(Draw_Display& dis) const
{
  dis.SetColor(myColor);
  dis.Draw(myFirst, myLast);
}

//=================================================================================================

const gp_Pnt& Draw_Segment3D::First() const
{
  return myFirst;
}

//=================================================================================================

void Draw_Segment3D::First(const gp_Pnt& P)
{
  myFirst = P;
}

//=================================================================================================

const gp_Pnt& Draw_Segment3D::Last() const
{
  return myLast;
}

//=================================================================================================

void Draw_Segment3D::Last(const gp_Pnt& P)
{
  myLast = P;
}
