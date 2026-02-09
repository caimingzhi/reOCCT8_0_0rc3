

#include <MoniTool_IntVal.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MoniTool_IntVal, Standard_Transient)

MoniTool_IntVal::MoniTool_IntVal(const int val)
{
  theval = val;
}

int MoniTool_IntVal::Value() const
{
  return theval;
}

int& MoniTool_IntVal::CValue()
{
  return theval;
}
