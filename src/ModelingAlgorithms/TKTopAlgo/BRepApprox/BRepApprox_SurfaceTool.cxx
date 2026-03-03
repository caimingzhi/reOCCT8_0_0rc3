#include <BRepApprox_SurfaceTool.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <Geom_BezierSurface.hpp>

int BRepApprox_SurfaceTool::NbSamplesU(const ::model::adapter::BRepAdaptor_Surface&)
{
  return (10);
}

int BRepApprox_SurfaceTool::NbSamplesV(const ::model::adapter::BRepAdaptor_Surface&)
{
  return (10);
}

int BRepApprox_SurfaceTool::NbSamplesU(const ::model::adapter::BRepAdaptor_Surface&, const double, const double)
{
  return (10);
}

int BRepApprox_SurfaceTool::NbSamplesV(const ::model::adapter::BRepAdaptor_Surface&, const double, const double)
{
  return (10);
}
