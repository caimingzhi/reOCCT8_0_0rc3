#include <StepElement_MeasureOrUnspecifiedValueMember.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_MeasureOrUnspecifiedValueMember, StepData_SelectNamed)

static const char* aContextDependedMeasure = "CONTEXT_DEPENDENT_MEASURE";
static const char* anUnspecifiedValue      = "UNSPECIFIED_VALUE";

StepElement_MeasureOrUnspecifiedValueMember::StepElement_MeasureOrUnspecifiedValueMember()
    : mycase(0)
{
}

bool StepElement_MeasureOrUnspecifiedValueMember::HasName() const
{
  return mycase > 0;
}

const char* StepElement_MeasureOrUnspecifiedValueMember::Name() const
{
  switch (mycase)
  {
    case 1:
      return aContextDependedMeasure;
    case 2:
      return anUnspecifiedValue;
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
  else if (!strcmp(name, aContextDependedMeasure))
  {
    thecase = 1;
  }
  else if (!strcmp(name, anUnspecifiedValue))
  {
    thecase = 2;
  }
  return thecase;
}

bool StepElement_MeasureOrUnspecifiedValueMember::SetName(const char* name)
{
  int numit = 0;
  mycase    = CompareNames(name, numit);
  if (numit)
    SetInteger(numit);
  return (mycase > 0);
}

bool StepElement_MeasureOrUnspecifiedValueMember::Matches(const char* name) const
{
  int numit   = 0;
  int thecase = CompareNames(name, numit);
  return (mycase == thecase);
}
