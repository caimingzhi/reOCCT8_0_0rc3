

#include <Interface_IntVal.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_IntVal, Standard_Transient)

Interface_IntVal::Interface_IntVal()
{
  theval = 0;
}

int Interface_IntVal::Value() const
{
  return theval;
}

int& Interface_IntVal::CValue()
{
  return theval;
}
