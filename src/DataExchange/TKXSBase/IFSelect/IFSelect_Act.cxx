

#include <IFSelect_Act.hpp>
#include <IFSelect_SessionPilot.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_Act, IFSelect_Activator)

static TCollection_AsciiString thedefgr, thedefil;

IFSelect_Act::IFSelect_Act(const char* name, const char* help, const IFSelect_ActFunc func)
    : thename(name),
      thehelp(help),
      thefunc(func)
{
}

IFSelect_ReturnStatus IFSelect_Act::Do(const int, const occ::handle<IFSelect_SessionPilot>& pilot)
{
  if (!thefunc)
    return IFSelect_RetVoid;
  return thefunc(pilot);
}

const char* IFSelect_Act::Help(const int) const
{
  return thehelp.ToCString();
}

void IFSelect_Act::SetGroup(const char* group, const char* file)
{
  thedefgr.Clear();
  if (group[0] != '\0')
    thedefgr.AssignCat(group);
  thedefil.Clear();
  if (file[0] != '\0')
    thedefil.AssignCat(file);
}

void IFSelect_Act::AddFunc(const char* name, const char* help, const IFSelect_ActFunc func)
{
  occ::handle<IFSelect_Act> act = new IFSelect_Act(name, help, func);
  if (thedefgr.Length() > 0)
    act->SetForGroup(thedefgr.ToCString());
  act->Add(1, name);
}

void IFSelect_Act::AddFSet(const char* name, const char* help, const IFSelect_ActFunc func)
{
  occ::handle<IFSelect_Act> act = new IFSelect_Act(name, help, func);
  if (thedefgr.Length() > 0)
    act->SetForGroup(thedefgr.ToCString(), thedefil.ToCString());
  act->AddSet(1, name);
}
