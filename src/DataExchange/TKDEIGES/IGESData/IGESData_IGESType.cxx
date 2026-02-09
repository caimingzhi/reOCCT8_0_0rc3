

#include <IGESData_IGESType.hpp>

IGESData_IGESType::IGESData_IGESType()
{
  thetype = 0;
  theform = 0;
}

IGESData_IGESType::IGESData_IGESType(const int atype, const int aform)
{
  thetype = atype;
  theform = aform;
}

int IGESData_IGESType::Type() const
{
  return thetype;
}

int IGESData_IGESType::Form() const
{
  return theform;
}

bool IGESData_IGESType::IsEqual(const IGESData_IGESType& other) const
{
  return (thetype == other.Type() && theform == other.Form());
}

void IGESData_IGESType::Nullify()
{
  thetype = 0;
  theform = 0;
}
