#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Activator.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <Standard_Integer.hpp>
class IFSelect_SessionPilot;

class IGESSelect_Activator : public IFSelect_Activator
{

public:
  Standard_EXPORT IGESSelect_Activator();

  Standard_EXPORT IFSelect_ReturnStatus
    Do(const int number, const occ::handle<IFSelect_SessionPilot>& pilot) override;

  Standard_EXPORT const char* Help(const int number) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_Activator, IFSelect_Activator)
};
