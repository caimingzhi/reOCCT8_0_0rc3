

#include <Draw_Drawable2D.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Drawable2D, Draw_Drawable3D)

bool Draw_Drawable2D::Is3D() const
{
  return false;
}
