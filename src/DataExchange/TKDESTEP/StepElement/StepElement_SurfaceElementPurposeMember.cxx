#include <StepElement_SurfaceElementPurposeMember.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_SurfaceElementPurposeMember, StepData_SelectNamed)

static const char* ESEP = "ENUMERATED_SURFACE_ELEMENT_PURPOSE";
static const char* ADEP = "APPLICATION_DEFINED_ELEMENT_PURPOSE";

StepElement_SurfaceElementPurposeMember::StepElement_SurfaceElementPurposeMember()
    : mycase(0)
{
}

bool StepElement_SurfaceElementPurposeMember::HasName() const
{
  return mycase > 0;
}

const char* StepElement_SurfaceElementPurposeMember::Name() const
{
  switch (mycase)
  {
    case 1:
      return ESEP;
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
  else if (!strcmp(name, ESEP))
  {
    thecase = 1;
  }
  else if (!strcmp(name, ADEP))
  {
    thecase = 1;
  }
  return thecase;
}

bool StepElement_SurfaceElementPurposeMember::SetName(const char* name)
{
  int numit = 0;
  mycase    = CompareNames(name, numit);
  if (numit)
    SetInteger(numit);
  return (mycase > 0);
}

bool StepElement_SurfaceElementPurposeMember::Matches(const char* name) const
{
  int numit   = 0;
  int thecase = CompareNames(name, numit);
  return (mycase == thecase);
}
