#include <Transfer_TransientMapper.hpp>

#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>
#include <Transfer_DataInfo.hpp>
#include <Transfer_Finder.hpp>

Transfer_TransientMapper::Transfer_TransientMapper(const occ::handle<Standard_Transient>& akey)
    : theval(akey)
{
  SetHashCode(std::hash<occ::handle<Standard_Transient>>{}(akey));
}

const occ::handle<Standard_Transient>& Transfer_TransientMapper::Value() const
{
  return theval;
}

bool Transfer_TransientMapper::Equates(const occ::handle<Transfer_Finder>& other) const
{
  if (other.IsNull())
    return false;
  if (GetHashCode() != other->GetHashCode())
    return false;
  if (other->DynamicType() != DynamicType())
    return false;
  occ::handle<Transfer_TransientMapper> another = occ::down_cast<Transfer_TransientMapper>(other);
  return theval == another->Value();
}

occ::handle<Standard_Type> Transfer_TransientMapper::ValueType() const
{
  return Transfer_DataInfo::Type(theval);
}

const char* Transfer_TransientMapper::ValueTypeName() const
{
  return Transfer_DataInfo::TypeName(theval);
}
