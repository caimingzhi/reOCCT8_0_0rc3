#include <TransferBRep_ShapeMapper.hpp>

#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <TransferBRep_ShapeInfo.hpp>
#include <Transfer_Finder.hpp>

//=================================================================================================

TransferBRep_ShapeMapper::TransferBRep_ShapeMapper(const TopoDS_Shape& akey)
    : theval(akey)
{
  SetHashCode(TopTools_ShapeMapHasher{}(akey));
}

//=================================================================================================

const TopoDS_Shape& TransferBRep_ShapeMapper::Value() const
{
  return theval;
}

//=================================================================================================

bool TransferBRep_ShapeMapper::Equates(const occ::handle<Transfer_Finder>& other) const
{
  if (other.IsNull())
    return false;
  if (GetHashCode() != other->GetHashCode())
    return false;
  if (other->DynamicType() != DynamicType())
    return false;
  occ::handle<TransferBRep_ShapeMapper> another = occ::down_cast<TransferBRep_ShapeMapper>(other);
  return TopTools_ShapeMapHasher{}(theval, another->Value());
}

//=================================================================================================

occ::handle<Standard_Type> TransferBRep_ShapeMapper::ValueType() const
{
  return TransferBRep_ShapeInfo::Type(theval);
}

//=================================================================================================

const char* TransferBRep_ShapeMapper::ValueTypeName() const
{
  return TransferBRep_ShapeInfo::TypeName(theval);
}
