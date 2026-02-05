#include <Draw_Display.hpp>
#include <Draw_Marker3D.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Marker3D, Draw_Drawable3D)

//=================================================================================================

Draw_Marker3D::Draw_Marker3D(const gp_Pnt&          P,
                             const Draw_MarkerShape T,
                             const Draw_Color&      C,
                             const int              S)
    : myPos(P),
      myCol(C),
      myTyp(T),
      mySiz(S),
      myRSiz(0.0),
      myIsRSiz(false)
{
}

//=================================================================================================

Draw_Marker3D::Draw_Marker3D(const gp_Pnt&          P,
                             const Draw_MarkerShape T,
                             const Draw_Color&      C,
                             const double           RSize)
    : myPos(P),
      myCol(C),
      myTyp(T),
      mySiz(0),
      myRSiz(RSize),
      myIsRSiz(true)
{
}

//=================================================================================================

void Draw_Marker3D::DrawOn(Draw_Display& D) const
{
  D.SetColor(myCol);
  if (myIsRSiz)
    D.DrawMarker(myPos, myTyp, myRSiz);
  else
    D.DrawMarker(myPos, myTyp, mySiz);
}

//=================================================================================================

gp_Pnt& Draw_Marker3D::ChangePos()
{
  return myPos;
}

//=================================================================================================

bool Draw_Marker3D::PickReject(const double, const double, const double) const
{
  return false;
}
