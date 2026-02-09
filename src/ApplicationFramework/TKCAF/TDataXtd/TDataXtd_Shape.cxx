#include <BRep_Builder.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd.hpp>
#include <TDataXtd_Shape.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_Tool.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(TDataXtd_Shape, TDataStd_GenericEmpty)

bool TDataXtd_Shape::Find(const TDF_Label& current, occ::handle<TDataXtd_Shape>& S)
{
  TDF_Label                   L = current;
  occ::handle<TDataXtd_Shape> SA;
  if (L.IsNull())
    return false;
  for (;;)
  {
    if (L.FindAttribute(TDataXtd_Shape::GetID(), SA))
      break;
    L = L.Father();
    if (L.IsNull())
      break;
  }

  if (!SA.IsNull())
  {
    S = SA;
    return true;
  }
  return false;
}

occ::handle<TDataXtd_Shape> TDataXtd_Shape::New(const TDF_Label& label)
{
  if (label.HasAttribute())
  {
    throw Standard_DomainError("TDataXtd_Shape::New : not an empty label");
  }
  occ::handle<TDataXtd_Shape> A = new TDataXtd_Shape();
  label.AddAttribute(A);
  return A;
}

occ::handle<TDataXtd_Shape> TDataXtd_Shape::Set(const TDF_Label& label, const TopoDS_Shape& shape)
{
  occ::handle<TDataXtd_Shape> A;
  if (!label.FindAttribute(TDataXtd_Shape::GetID(), A))
  {
    A = TDataXtd_Shape::New(label);
  }

  occ::handle<TNaming_NamedShape> aNS;
  if (label.FindAttribute(TNaming_NamedShape::GetID(), aNS))
  {
    if (!aNS->Get().IsNull())
      if (aNS->Get() == shape)
        return A;
  }

  TNaming_Builder B(label);
  B.Generated(shape);
  return A;
}

TopoDS_Shape TDataXtd_Shape::Get(const TDF_Label& label)
{
  TopoDS_Shape shape;

  occ::handle<TNaming_NamedShape> NS;
  if (label.FindAttribute(TNaming_NamedShape::GetID(), NS))
  {
    shape = TNaming_Tool::GetShape(NS);
    return shape;
  }

  shape.Nullify();
  return shape;
}

const Standard_GUID& TDataXtd_Shape::GetID()
{
  static Standard_GUID TDataXtd_ShapeID("2a96b620-ec8b-11d0-bee7-080009dc3333");
  return TDataXtd_ShapeID;
}

TDataXtd_Shape::TDataXtd_Shape() = default;

const Standard_GUID& TDataXtd_Shape::ID() const
{
  return GetID();
}

void TDataXtd_Shape::References(const occ::handle<TDF_DataSet>&) const {}

Standard_OStream& TDataXtd_Shape::Dump(Standard_OStream& anOS) const
{
  anOS << "Shape";
  return anOS;
}
