

#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <Transfer_ActorOfTransientProcess.hpp>
#include <XSControl_SelectForTransfer.hpp>
#include <XSControl_TransferReader.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XSControl_SelectForTransfer, IFSelect_SelectExtract)

XSControl_SelectForTransfer::XSControl_SelectForTransfer() = default;

XSControl_SelectForTransfer::XSControl_SelectForTransfer(
  const occ::handle<XSControl_TransferReader>& TR)
{
  theTR = TR;
}

void XSControl_SelectForTransfer::SetReader(const occ::handle<XSControl_TransferReader>& TR)
{
  theTR = TR;
}

void XSControl_SelectForTransfer::SetActor(const occ::handle<Transfer_ActorOfTransientProcess>& act)
{
  theAC = act;
}

occ::handle<Transfer_ActorOfTransientProcess> XSControl_SelectForTransfer::Actor() const
{
  return theAC;
}

occ::handle<XSControl_TransferReader> XSControl_SelectForTransfer::Reader() const
{
  return theTR;
}

bool XSControl_SelectForTransfer::Sort(const int,
                                       const occ::handle<Standard_Transient>& ent,
                                       const occ::handle<Interface_InterfaceModel>&) const
{
  occ::handle<Transfer_ActorOfTransientProcess> act = theAC;
  if (act.IsNull() && !theTR.IsNull())
    act = theTR->Actor();

  if (!act.IsNull())
    return act->Recognize(ent);

  return false;
}

TCollection_AsciiString XSControl_SelectForTransfer::ExtractLabel() const
{
  if (!theTR.IsNull())
    return TCollection_AsciiString("Recognized for Transfer (current actor)");
  return TCollection_AsciiString("Recognized for Transfer");
}
