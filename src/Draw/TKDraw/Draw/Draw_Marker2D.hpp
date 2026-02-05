#pragma once

#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <Draw_Color.hpp>
#include <Draw_MarkerShape.hpp>
#include <Standard_Integer.hpp>
#include <Draw_Drawable2D.hpp>
class Draw_Display;

class Draw_Marker2D : public Draw_Drawable2D
{

public:
  Standard_EXPORT Draw_Marker2D(const gp_Pnt2d&        P,
                                const Draw_MarkerShape T,
                                const Draw_Color&      C,
                                const int              Size = 5);

  Standard_EXPORT Draw_Marker2D(const gp_Pnt2d&        P,
                                const Draw_MarkerShape T,
                                const Draw_Color&      C,
                                const double           RSize);

  //! myPos field
  Standard_EXPORT gp_Pnt2d& ChangePos();

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  //! Returns always false
  Standard_EXPORT bool PickReject(const double X, const double Y, const double Prec) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Marker2D, Draw_Drawable2D)

private:
  gp_Pnt2d         myPos;
  Draw_Color       myCol;
  Draw_MarkerShape myTyp;
  int              mySiz;
};
