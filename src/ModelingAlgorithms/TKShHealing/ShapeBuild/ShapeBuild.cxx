#include <ShapeBuild.hpp>

#include <Geom_Plane.hpp>

occ::handle<Geom_Plane> ShapeBuild::PlaneXOY()
{
  static occ::handle<Geom_Plane> xoy;
  if (xoy.IsNull())
    xoy = new Geom_Plane(0, 0, 1, 0);
  return xoy;
}
