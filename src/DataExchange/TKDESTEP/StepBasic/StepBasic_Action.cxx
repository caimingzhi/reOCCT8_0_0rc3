#include <StepBasic_Action.hpp>
#include <StepBasic_ActionMethod.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Action, Standard_Transient)

//=================================================================================================

StepBasic_Action::StepBasic_Action()
{
  defDescription = false;
}

//=================================================================================================

void StepBasic_Action::Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepBasic_ActionMethod>&   aChosenMethod)
{

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theChosenMethod = aChosenMethod;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_Action::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_Action::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_Action::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_Action::SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

bool StepBasic_Action::HasDescription() const
{
  return defDescription;
}

//=================================================================================================

occ::handle<StepBasic_ActionMethod> StepBasic_Action::ChosenMethod() const
{
  return theChosenMethod;
}

//=================================================================================================

void StepBasic_Action::SetChosenMethod(const occ::handle<StepBasic_ActionMethod>& aChosenMethod)
{
  theChosenMethod = aChosenMethod;
}
