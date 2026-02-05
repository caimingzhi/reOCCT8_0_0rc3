#pragma once

#include <Standard.hpp>

#include <Bnd_OBB.hpp>
#include <Draw_Color.hpp>
#include <Draw_Drawable3D.hpp>
class Draw_Display;

//! a 3d box
class Draw_Box : public Draw_Drawable3D
{
public:
  //! Constructor
  Standard_EXPORT Draw_Box(const Bnd_OBB& theOBB, const Draw_Color& theColor);

  //! Draws myOBB
  Standard_EXPORT void DrawOn(Draw_Display& theDis) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Box, Draw_Drawable3D)

protected:
  //! Converts the point (theX, theY, theZ) in local coordinate system to WCS.
  void ToWCS(const double theX, const double theY, const double theZ, gp_Pnt& theP) const;

  //! Moves the point thePt along X-direction of myOBB on the distance theShift.
  void MoveX(const double theShift, gp_Pnt& thePt) const;

  //! Moves the point thePt along Y-direction of myOBB on the distance theShift.
  void MoveY(const double theShift, gp_Pnt& thePt) const;

  //! Moves the point thePt along Z-direction of myOBB on the distance theShift.
  void MoveZ(const double theShift, gp_Pnt& thePt) const;

private:
  //! Oriented bounding box
  Bnd_OBB myOBB;

  //! Color value
  Draw_Color myColor;
};
