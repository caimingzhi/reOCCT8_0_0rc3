

#include <TransferBRep_BinderOfShape.hpp>
#include <TransferBRep_ShapeInfo.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TransferBRep_BinderOfShape, Transfer_Binder)

TransferBRep_BinderOfShape::TransferBRep_BinderOfShape() = default;

TransferBRep_BinderOfShape::TransferBRep_BinderOfShape(const TopoDS_Shape& res)
    : theres(res)
{
  SetResultPresent();
}

occ::handle<Standard_Type> TransferBRep_BinderOfShape::ResultType() const

{
  return TransferBRep_ShapeInfo::Type(theres);
}

const char* TransferBRep_BinderOfShape::ResultTypeName() const
{
  return TransferBRep_ShapeInfo::TypeName(theres);
}

void TransferBRep_BinderOfShape::SetResult(const TopoDS_Shape& res)
{
  SetResultPresent();
  theres = res;
}

const TopoDS_Shape& TransferBRep_BinderOfShape::Result() const
{
  return theres;
}

TopoDS_Shape& TransferBRep_BinderOfShape::CResult()
{
  SetResultPresent();
  return theres;
}
