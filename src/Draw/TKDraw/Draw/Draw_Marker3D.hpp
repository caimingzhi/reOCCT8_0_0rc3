#pragma once


#include <Standard.hpp>

#include <gp_Pnt.hpp>
#include <Draw_Color.hpp>
#include <Draw_MarkerShape.hpp>
#include <Standard_Integer.hpp>
#include <Draw_Drawable3D.hpp>
class Draw_Display;

class Draw_Marker3D : public Draw_Drawable3D
{

public:
  Standard_EXPORT Draw_Marker3D(const gp_Pnt&          P,
                                const Draw_MarkerShape T,
                                const Draw_Color&      C,
                                const int              ISize = 5);

  Standard_EXPORT Draw_Marker3D(const gp_Pnt&          P,
                                const Draw_MarkerShape T,
                                const Draw_Color&      C,
                                const double           RSize);

  //! myPos field
  Standard_EXPORT gp_Pnt& ChangePos();

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  //! Returns always false
  Standard_EXPORT bool PickReject(const double X, const double Y, const double Prec) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Marker3D, Draw_Drawable3D)

private:
  gp_Pnt           myPos;
  Draw_Color       myCol;
  Draw_MarkerShape myTyp;
  int              mySiz;
  double           myRSiz;
  bool             myIsRSiz;
};

