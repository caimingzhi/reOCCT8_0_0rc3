#include <BRepPrim_OneAxis.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>

//=================================================================================================

const TopoDS_Face& BRepPrimAPI_MakeOneAxis::Face()
{
  Build();
  return ((BRepPrim_OneAxis*)OneAxis())->LateralFace();
}

//=================================================================================================

const TopoDS_Shell& BRepPrimAPI_MakeOneAxis::Shell()
{
  Build();
  return ((BRepPrim_OneAxis*)OneAxis())->Shell();
}

//=================================================================================================

void BRepPrimAPI_MakeOneAxis::Build(const Message_ProgressRange& /*theRange*/)
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(myShape));
  B.Add(myShape, ((BRepPrim_OneAxis*)OneAxis())->Shell());
  Done();
}

//=================================================================================================

const TopoDS_Solid& BRepPrimAPI_MakeOneAxis::Solid()
{
  Build();
  return TopoDS::Solid(myShape);
}

//=================================================================================================

BRepPrimAPI_MakeOneAxis::operator TopoDS_Face()
{
  return Face();
}

//=================================================================================================

BRepPrimAPI_MakeOneAxis::operator TopoDS_Shell()
{
  return Shell();
}

//=================================================================================================

BRepPrimAPI_MakeOneAxis::operator TopoDS_Solid()
{
  return Solid();
}
