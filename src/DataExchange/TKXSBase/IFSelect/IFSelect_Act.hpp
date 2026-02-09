#pragma once

#include <Standard.hpp>

#include <IFSelect_SessionPilot.hpp>
#include <IFSelect_ReturnStatus.hpp>

typedef IFSelect_ReturnStatus (*IFSelect_ActFunc)(const occ::handle<IFSelect_SessionPilot>&);

#include <IFSelect_Activator.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <Standard_Integer.hpp>
class IFSelect_SessionPilot;

class IFSelect_Act : public IFSelect_Activator
{

public:
  Standard_EXPORT IFSelect_Act(const char* name, const char* help, const IFSelect_ActFunc func);

  Standard_EXPORT IFSelect_ReturnStatus
    Do(const int number, const occ::handle<IFSelect_SessionPilot>& pilot) override;

  Standard_EXPORT const char* Help(const int number) const override;

  Standard_EXPORT static void SetGroup(const char* group, const char* file = "");

  Standard_EXPORT static void AddFunc(const char*            name,
                                      const char*            help,
                                      const IFSelect_ActFunc func);

  Standard_EXPORT static void AddFSet(const char*            name,
                                      const char*            help,
                                      const IFSelect_ActFunc func);

  DEFINE_STANDARD_RTTIEXT(IFSelect_Act, IFSelect_Activator)

private:
  TCollection_AsciiString thename;
  TCollection_AsciiString thehelp;
  IFSelect_ActFunc        thefunc;
};
