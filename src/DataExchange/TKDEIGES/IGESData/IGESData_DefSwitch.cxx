

#include <IGESData_DefSwitch.hpp>

IGESData_DefSwitch::IGESData_DefSwitch()
    : theval(0)
{
}

void IGESData_DefSwitch::SetVoid()
{
  theval = 0;
}

void IGESData_DefSwitch::SetReference()
{
  theval = -1;
}

void IGESData_DefSwitch::SetRank(const int theRank)
{
  theval = theRank;
}

IGESData_DefType IGESData_DefSwitch::DefType() const
{
  if (theval < 0)
    return IGESData_DefReference;

  if (theval > 0)
    return IGESData_DefValue;

  return IGESData_DefVoid;
}

int IGESData_DefSwitch::Value() const
{
  return theval;
}
