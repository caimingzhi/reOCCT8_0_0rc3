#include <Draw_Display.hpp>
#include <Draw_Segment2D.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Segment2D, Draw_Drawable2D)

//=================================================================================================

Draw_Segment2D::Draw_Segment2D(const gp_Pnt2d& p1, const gp_Pnt2d& p2, const Draw_Color& col)
    : myFirst(p1),
      myLast(p2),
      myColor(col)
{
}

//=================================================================================================

void Draw_Segment2D::DrawOn(Draw_Display& dis) const
{
  dis.SetColor(myColor);
  dis.Draw(myFirst, myLast);
}

//=================================================================================================

const gp_Pnt2d& Draw_Segment2D::First() const
{
  return myFirst;
}

//=================================================================================================

void Draw_Segment2D::First(const gp_Pnt2d& P)
{
  myFirst = P;
}

//=================================================================================================

const gp_Pnt2d& Draw_Segment2D::Last() const
{
  return myLast;
}

//=================================================================================================

void Draw_Segment2D::Last(const gp_Pnt2d& P)
{
  myLast = P;
}

//=================================================================================================

void Draw_Segment2D::Whatis(Draw_Interpretor& S) const
{
  S << "segment 2d";
}

//=================================================================================================

void Draw_Segment2D::Dump(Standard_OStream& S) const
{
  S << std::setw(17) << myFirst.X() << " " << std::setw(17) << myFirst.Y() << " - " << std::setw(17)
    << myLast.X() << " " << std::setw(17) << myLast.Y() << "\n";
}
