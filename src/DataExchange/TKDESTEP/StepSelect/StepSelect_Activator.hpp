#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Activator.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <Standard_Integer.hpp>
class IFSelect_SessionPilot;

//! Performs Actions specific to StepSelect, i.e. creation of
//! Step Selections and Counters, plus dumping specific to Step
class StepSelect_Activator : public IFSelect_Activator
{

public:
  Standard_EXPORT StepSelect_Activator();

  //! Executes a Command Line for StepSelect
  Standard_EXPORT IFSelect_ReturnStatus
    Do(const int number, const occ::handle<IFSelect_SessionPilot>& pilot) override;

  //! Sends a short help message for StepSelect commands
  Standard_EXPORT const char* Help(const int number) const override;

  DEFINE_STANDARD_RTTIEXT(StepSelect_Activator, IFSelect_Activator)
};
