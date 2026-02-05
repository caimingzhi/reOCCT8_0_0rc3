#include <StepElement_CurveElementFreedomMember.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_CurveElementFreedomMember, StepData_SelectNamed)

static const char* ECEF = "ENUMERATED_CURVE_ELEMENT_FREEDOM";
static const char* ADDF = "APPLICATION_DEFINED_DEGREE_OF_FREEDOM";

//=================================================================================================

StepElement_CurveElementFreedomMember::StepElement_CurveElementFreedomMember()
    : mycase(0)
{
}

//=================================================================================================

bool StepElement_CurveElementFreedomMember::HasName() const
{
  return mycase > 0;
}

//=================================================================================================

const char* StepElement_CurveElementFreedomMember::Name() const
{
  switch (mycase)
  {
    case 1:
      return ECEF;
    case 2:
      return ADDF;
    default:
      break;
  }
  return "";
}

//=================================================================================================

static int CompareNames(const char* name, int& /*numen*/)
{
  int thecase = 0;
  if (!name || name[0] == '\0')
    thecase = 0;

  else if (!strcmp(name, ECEF))
  {
    thecase = 1;
  }
  else if (!strcmp(name, ADDF))
  {
    thecase = 2;
  }
  return thecase;
}

//=================================================================================================

bool StepElement_CurveElementFreedomMember::SetName(const char* name)
{
  int numit = 0;
  mycase    = CompareNames(name, numit);
  if (numit)
    SetInteger(numit);
  return (mycase > 0);
}

//=================================================================================================

bool StepElement_CurveElementFreedomMember::Matches(const char* name) const
{
  int numit   = 0;
  int thecase = CompareNames(name, numit);
  return (mycase == thecase);
}
