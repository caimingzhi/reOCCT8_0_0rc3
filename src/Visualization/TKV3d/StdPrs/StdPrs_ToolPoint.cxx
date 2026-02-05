#include <Geom_Point.hpp>
#include <StdPrs_ToolPoint.hpp>

void StdPrs_ToolPoint::Coord(const occ::handle<Geom_Point>& aPoint, double& X, double& Y, double& Z)
{
  aPoint->Coord(X, Y, Z);
}
