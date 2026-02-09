#include <Draw_Display.hpp>
#include <Draw_Marker2D.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Marker2D, Draw_Drawable2D)

Draw_Marker2D::Draw_Marker2D(const gp_Pnt2d&        P,
                             const Draw_MarkerShape T,
                             const Draw_Color&      C,
                             const int              S)
    : myPos(P),
      myCol(C),
      myTyp(T),
      mySiz(S)
{
}

Draw_Marker2D::Draw_Marker2D(const gp_Pnt2d&        P,
                             const Draw_MarkerShape T,
                             const Draw_Color&      C,
                             const double)
    : myPos(P),
      myCol(C),
      myTyp(T),
      mySiz(0)
{
}

void Draw_Marker2D::DrawOn(Draw_Display& D) const
{
  D.SetColor(myCol);
  D.DrawMarker(myPos, myTyp, mySiz);
}

gp_Pnt2d& Draw_Marker2D::ChangePos()
{
  return myPos;
}

bool Draw_Marker2D::PickReject(const double, const double, const double) const
{
  return false;
}
