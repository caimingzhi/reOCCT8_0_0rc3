

#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_CompSolid.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TransferBRep_ShapeBinder.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TransferBRep_ShapeBinder, TransferBRep_BinderOfShape)

TransferBRep_ShapeBinder::TransferBRep_ShapeBinder() = default;

TransferBRep_ShapeBinder::TransferBRep_ShapeBinder(const TopoDS_Shape& shape)
    : TransferBRep_BinderOfShape(shape)
{
}

TopAbs_ShapeEnum TransferBRep_ShapeBinder::ShapeType() const
{
  if (!HasResult())
    return TopAbs_SHAPE;
  return Result().ShapeType();
}

TopoDS_Vertex TransferBRep_ShapeBinder::Vertex() const
{
  return TopoDS::Vertex(Result());
}

TopoDS_Edge TransferBRep_ShapeBinder::Edge() const
{
  return TopoDS::Edge(Result());
}

TopoDS_Wire TransferBRep_ShapeBinder::Wire() const
{
  return TopoDS::Wire(Result());
}

TopoDS_Face TransferBRep_ShapeBinder::Face() const
{
  return TopoDS::Face(Result());
}

TopoDS_Shell TransferBRep_ShapeBinder::Shell() const
{
  return TopoDS::Shell(Result());
}

TopoDS_Solid TransferBRep_ShapeBinder::Solid() const
{
  return TopoDS::Solid(Result());
}

TopoDS_CompSolid TransferBRep_ShapeBinder::CompSolid() const
{
  return TopoDS::CompSolid(Result());
}

TopoDS_Compound TransferBRep_ShapeBinder::Compound() const
{
  return TopoDS::Compound(Result());
}
