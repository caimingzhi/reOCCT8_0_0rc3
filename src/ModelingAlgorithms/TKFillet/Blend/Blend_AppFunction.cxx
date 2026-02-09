

#include <Blend_AppFunction.hpp>
#include <Blend_Point.hpp>

double Blend_AppFunction::Parameter(const Blend_Point& P) const
{
  return P.Parameter();
}
