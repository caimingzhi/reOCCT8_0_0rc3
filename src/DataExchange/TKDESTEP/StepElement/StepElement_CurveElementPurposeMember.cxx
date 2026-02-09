#include <StepElement_CurveElementPurposeMember.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_CurveElementPurposeMember, StepData_SelectNamed)

static const char* ECEP = "ENUMERATED_CURVE_ELEMENT_PURPOSE";
static const char* ADEP = "APPLICATION_DEFINED_ELEMENT_PURPOSE";

StepElement_CurveElementPurposeMember::StepElement_CurveElementPurposeMember()
    : mycase(0)
{
}

bool StepElement_CurveElementPurposeMember::HasName() const
{
  return mycase > 0;
}

const char* StepElement_CurveElementPurposeMember::Name() const
{
  switch (mycase)
  {
    case 1:
      return ECEP;
    case 2:
      return ADEP;
    default:
      break;
  }
  return "";
}

static int CompareNames(const char* name, int&)
{
  int thecase = 0;
  if (!name || name[0] == '\0')
    thecase = 0;
  else if (!strcmp(name, ECEP))
  {
    thecase = 1;
  }
  else if (!strcmp(name, ADEP))
  {
    thecase = 2;
  }
  return thecase;
}

bool StepElement_CurveElementPurposeMember::SetName(const char* name)
{
  int numit = 0;
  mycase    = CompareNames(name, numit);
  if (numit)
    SetInteger(numit);
  return (mycase > 0);
}

bool StepElement_CurveElementPurposeMember::Matches(const char* name) const
{
  int numit   = 0;
  int thecase = CompareNames(name, numit);
  return (mycase == thecase);
}
