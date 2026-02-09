

#include <MoniTool_DataInfo.hpp>
#include <MoniTool_TransientElem.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MoniTool_TransientElem, MoniTool_Element)

MoniTool_TransientElem::MoniTool_TransientElem(const occ::handle<Standard_Transient>& akey)
    : theval(akey)
{
  SetHashCode(std::hash<occ::handle<Standard_Transient>>{}(akey));
}

const occ::handle<Standard_Transient>& MoniTool_TransientElem::Value() const
{
  return theval;
}

bool MoniTool_TransientElem::Equates(const occ::handle<MoniTool_Element>& other) const
{
  if (other.IsNull())
    return false;
  if (GetHashCode() != other->GetHashCode())
    return false;
  if (other->DynamicType() != DynamicType())
    return false;
  occ::handle<MoniTool_TransientElem> another = occ::down_cast<MoniTool_TransientElem>(other);

  return theval == another->Value();
}

occ::handle<Standard_Type> MoniTool_TransientElem::ValueType() const
{
  return MoniTool_DataInfo::Type(theval);
}

const char* MoniTool_TransientElem::ValueTypeName() const
{
  return MoniTool_DataInfo::TypeName(theval);
}
