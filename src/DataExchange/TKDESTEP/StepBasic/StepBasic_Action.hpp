#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ActionMethod;

class StepBasic_Action : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_Action();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepBasic_ActionMethod>&   aChosenMethod);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  Standard_EXPORT occ::handle<StepBasic_ActionMethod> ChosenMethod() const;

  Standard_EXPORT void SetChosenMethod(const occ::handle<StepBasic_ActionMethod>& ChosenMethod);

  DEFINE_STANDARD_RTTIEXT(StepBasic_Action, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<StepBasic_ActionMethod>   theChosenMethod;
  bool                                  defDescription;
};
