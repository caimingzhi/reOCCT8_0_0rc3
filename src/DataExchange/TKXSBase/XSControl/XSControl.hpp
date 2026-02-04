#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class XSControl_WorkSession;
class IFSelect_SessionPilot;
class XSControl_Vars;

//! This package provides complements to IFSelect & Co for
//! control of a session
class XSControl
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the WorkSession of a SessionPilot, but casts it as
  //! from XSControl : it then gives access to Control & Transfers
  Standard_EXPORT static occ::handle<XSControl_WorkSession> Session(
    const occ::handle<IFSelect_SessionPilot>& pilot);

  //! Returns the Vars of a SessionPilot, it is brought by Session
  //! it provides access to external variables
  Standard_EXPORT static occ::handle<XSControl_Vars> Vars(
    const occ::handle<IFSelect_SessionPilot>& pilot);
};

