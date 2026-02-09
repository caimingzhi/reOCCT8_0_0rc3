

#include <MoniTool_RealVal.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MoniTool_RealVal, Standard_Transient)

MoniTool_RealVal::MoniTool_RealVal(const double val)
{
  theval = val;
}

double MoniTool_RealVal::Value() const
{
  return theval;
}

double& MoniTool_RealVal::CValue()
{
  return theval;
}
