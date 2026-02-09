#include <StepFEA_DegreeOfFreedomMember.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_DegreeOfFreedomMember, StepData_SelectNamed)

static const char* anEnumeratedCurveElementFreedom     = "ENUMERATED_DEGREE_OF_FREEDOM";
static const char* anApplicationDefinedDegreeOfFreedom = "APPLICATION_DEFINED_DEGREE_OF_FREEDOM";

StepFEA_DegreeOfFreedomMember::StepFEA_DegreeOfFreedomMember()
    : mycase(0)
{
}

bool StepFEA_DegreeOfFreedomMember::HasName() const
{
  return mycase > 0;
}

const char* StepFEA_DegreeOfFreedomMember::Name() const
{
  switch (mycase)
  {
    case 1:
      return anEnumeratedCurveElementFreedom;
    case 2:
      return anApplicationDefinedDegreeOfFreedom;
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
  else if (!strcmp(name, anEnumeratedCurveElementFreedom))
  {
    thecase = 1;
  }
  else if (!strcmp(name, anApplicationDefinedDegreeOfFreedom))
  {
    thecase = 2;
  }

  return thecase;
}

bool StepFEA_DegreeOfFreedomMember::SetName(const char* name)
{
  int numit = 0;
  mycase    = CompareNames(name, numit);
  if (numit)
    SetInteger(numit);
  return (mycase > 0);
}

bool StepFEA_DegreeOfFreedomMember::Matches(const char* name) const
{
  int numit   = 0;
  int thecase = CompareNames(name, numit);
  return (mycase == thecase);
}
