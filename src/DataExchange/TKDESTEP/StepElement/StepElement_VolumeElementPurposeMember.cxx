#include <StepElement_VolumeElementPurposeMember.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_VolumeElementPurposeMember, StepData_SelectNamed)

static const char* EVEP = "ENUMERATED_VOLUME_ELEMENT_PURPOSE";
static const char* ADEP = "APPLICATION_DEFINED_ELEMENT_PURPOSE";

//=================================================================================================

StepElement_VolumeElementPurposeMember::StepElement_VolumeElementPurposeMember()
    : mycase(0)
{
}

//=================================================================================================

bool StepElement_VolumeElementPurposeMember::HasName() const
{
  return mycase > 0;
}

//=================================================================================================

const char* StepElement_VolumeElementPurposeMember::Name() const
{
  switch (mycase)
  {
    case 1:
      return EVEP;
    case 2:
      return ADEP;
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
  else if (!strcmp(name, EVEP))
  {
    thecase = 1;
  }
  else if (!strcmp(name, ADEP))
  {
    thecase = 1;
  }
  return thecase;
}

//=================================================================================================

bool StepElement_VolumeElementPurposeMember::SetName(const char* name)
{
  int numit = 0;
  mycase    = CompareNames(name, numit);
  if (numit)
    SetInteger(numit);
  return (mycase > 0);
}

//=================================================================================================

bool StepElement_VolumeElementPurposeMember::Matches(const char* name) const
{
  int numit   = 0;
  int thecase = CompareNames(name, numit);
  return (mycase == thecase);
}
