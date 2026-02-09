#include <BRepBuilderAPI.hpp>

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepLib.hpp>
#include <BRepTools.hpp>
#include <Geom_Plane.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

void BRepBuilderAPI::Plane(const occ::handle<Geom_Plane>& P)
{
  BRepLib::Plane(P);
}

const occ::handle<Geom_Plane>& BRepBuilderAPI::Plane()
{
  return BRepLib::Plane();
}

void BRepBuilderAPI::Precision(const double P)
{
  BRepLib::Precision(P);
}

double BRepBuilderAPI::Precision()
{
  return BRepLib::Precision();
}
