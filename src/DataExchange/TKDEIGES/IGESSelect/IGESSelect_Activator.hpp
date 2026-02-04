#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Activator.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <Standard_Integer.hpp>
class IFSelect_SessionPilot;

//! Performs Actions specific to IGESSelect, i.e. creation of
//! IGES Selections and Dispatches, plus dumping specific to IGES
class IGESSelect_Activator : public IFSelect_Activator
{

public:
  Standard_EXPORT IGESSelect_Activator();

  //! Executes a Command Line for IGESSelect
  Standard_EXPORT IFSelect_ReturnStatus
    Do(const int number, const occ::handle<IFSelect_SessionPilot>& pilot) override;

  //! Sends a short help message for IGESSelect commands
  Standard_EXPORT const char* Help(const int number) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_Activator, IFSelect_Activator)
};

