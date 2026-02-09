

#include <XSControl.hpp>

#include <IFSelect_SessionPilot.hpp>
#include <XSControl_Vars.hpp>
#include <XSControl_WorkSession.hpp>

occ::handle<XSControl_WorkSession> XSControl::Session(
  const occ::handle<IFSelect_SessionPilot>& pilot)
{
  return occ::down_cast<XSControl_WorkSession>(pilot->Session());
}

occ::handle<XSControl_Vars> XSControl::Vars(const occ::handle<IFSelect_SessionPilot>& pilot)
{
  occ::handle<XSControl_Vars>        avars;
  occ::handle<XSControl_WorkSession> WS = XSControl::Session(pilot);
  if (!WS.IsNull())
    avars = WS->Vars();
  return avars;
}
