

#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
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
#include <TransferBRep_ShapeListBinder.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TransferBRep_ShapeListBinder, Transfer_Binder)

TransferBRep_ShapeListBinder::TransferBRep_ShapeListBinder()
{
  theres = new NCollection_HSequence<TopoDS_Shape>();
}

TransferBRep_ShapeListBinder::TransferBRep_ShapeListBinder(
  const occ::handle<NCollection_HSequence<TopoDS_Shape>>& list)
{
  theres = list;
}

bool TransferBRep_ShapeListBinder::IsMultiple() const
{
  return (NbShapes() > 1);
}

occ::handle<Standard_Type> TransferBRep_ShapeListBinder::ResultType() const
{
  return STANDARD_TYPE(TransferBRep_ShapeListBinder);
}

const char* TransferBRep_ShapeListBinder::ResultTypeName() const
{
  return "list(TopoDS_Shape)";
}

void TransferBRep_ShapeListBinder::AddResult(const TopoDS_Shape& shape)
{
  theres->Append(shape);
}

occ::handle<NCollection_HSequence<TopoDS_Shape>> TransferBRep_ShapeListBinder::Result() const
{
  return theres;
}

void TransferBRep_ShapeListBinder::SetResult(const int num, const TopoDS_Shape& shape)
{
  theres->SetValue(num, shape);
}

int TransferBRep_ShapeListBinder::NbShapes() const
{
  return theres->Length();
}

const TopoDS_Shape& TransferBRep_ShapeListBinder::Shape(const int num) const
{
  return theres->Value(num);
}

TopAbs_ShapeEnum TransferBRep_ShapeListBinder::ShapeType(const int num) const
{
  return theres->Value(num).ShapeType();
}

TopoDS_Vertex TransferBRep_ShapeListBinder::Vertex(const int num) const
{
  return TopoDS::Vertex(theres->Value(num));
}

TopoDS_Edge TransferBRep_ShapeListBinder::Edge(const int num) const
{
  return TopoDS::Edge(theres->Value(num));
}

TopoDS_Wire TransferBRep_ShapeListBinder::Wire(const int num) const
{
  return TopoDS::Wire(theres->Value(num));
}

TopoDS_Face TransferBRep_ShapeListBinder::Face(const int num) const
{
  return TopoDS::Face(theres->Value(num));
}

TopoDS_Shell TransferBRep_ShapeListBinder::Shell(const int num) const
{
  return TopoDS::Shell(theres->Value(num));
}

TopoDS_Solid TransferBRep_ShapeListBinder::Solid(const int num) const
{
  return TopoDS::Solid(theres->Value(num));
}

TopoDS_CompSolid TransferBRep_ShapeListBinder::CompSolid(const int num) const
{
  return TopoDS::CompSolid(theres->Value(num));
}

TopoDS_Compound TransferBRep_ShapeListBinder::Compound(const int num) const
{
  return TopoDS::Compound(theres->Value(num));
}
