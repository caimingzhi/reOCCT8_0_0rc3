

#include <IntSurf_QuadricTool.hpp>

double IntSurf_QuadricTool::Tolerance(const IntSurf_Quadric& Q)
{
  switch (Q.TypeQuadric())
  {
    case GeomAbs_Sphere:
      return 2.e-6 * Q.Sphere().Radius();
    case GeomAbs_Cylinder:
      return 2.e-6 * Q.Cylinder().Radius();
    default:
      break;
  }
  return (1e-6);
}
