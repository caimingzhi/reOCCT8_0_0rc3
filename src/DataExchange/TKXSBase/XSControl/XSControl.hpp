#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class XSControl_WorkSession;
class IFSelect_SessionPilot;
class XSControl_Vars;

class XSControl
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<XSControl_WorkSession> Session(
    const occ::handle<IFSelect_SessionPilot>& pilot);

  Standard_EXPORT static occ::handle<XSControl_Vars> Vars(
    const occ::handle<IFSelect_SessionPilot>& pilot);
};
