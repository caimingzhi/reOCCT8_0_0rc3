

#include <Interface_Check.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <Transfer_TransientProcess.hpp>
#include <XSControl_SignTransferStatus.hpp>
#include <XSControl_TransferReader.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XSControl_SignTransferStatus, IFSelect_Signature)

static TCollection_AsciiString& themes()
{
  static TCollection_AsciiString tm;
  return tm;
}

XSControl_SignTransferStatus::XSControl_SignTransferStatus()
    : IFSelect_Signature("Transfer Status")
{
}

XSControl_SignTransferStatus::XSControl_SignTransferStatus(
  const occ::handle<XSControl_TransferReader>& TR)
    : IFSelect_Signature("Transfer Status"),
      theTR(TR)
{
}

void XSControl_SignTransferStatus::SetReader(const occ::handle<XSControl_TransferReader>& TR)
{
  theTR = TR;
}

void XSControl_SignTransferStatus::SetMap(const occ::handle<Transfer_TransientProcess>& TP)
{
  theTP = TP;
}

occ::handle<Transfer_TransientProcess> XSControl_SignTransferStatus::Map() const
{
  return theTP;
}

occ::handle<XSControl_TransferReader> XSControl_SignTransferStatus::Reader() const
{
  return theTR;
}

static int BinderStatus(const occ::handle<Transfer_Binder>& binder)
{
  int stat = 0;
  if (binder.IsNull())
    return 0;
  Interface_CheckStatus cst = binder->Check()->Status();
  Transfer_StatusExec   est = binder->StatusExec();
  bool                  res = binder->HasResult();
  if (est == Transfer_StatusRun || est == Transfer_StatusLoop)
    return 20;
  if (cst == Interface_CheckOK)
    stat = (res ? 11 : 1);
  else if (cst == Interface_CheckWarning)
    stat = (res ? 12 : 2);
  else if (cst == Interface_CheckFail)
    stat = (res ? 13 : 3);

  return stat;
}

const char* XSControl_SignTransferStatus::Value(const occ::handle<Standard_Transient>& ent,
                                                const occ::handle<Interface_InterfaceModel>&) const
{
  if (ent.IsNull())
    return "";
  occ::handle<Transfer_TransientProcess> TP = theTP;
  if (TP.IsNull() && !theTR.IsNull())
    TP = theTR->TransientProcess();
  if (TP.IsNull())
    return "";

  occ::handle<Transfer_Binder> binder = TP->Find(ent);

  int stat = BinderStatus(binder);

  if (stat <= 1)
    return "";
  if (stat == 2)
    return "Warning";
  if (stat == 3)
    return "Fail";
  if (stat == 20)
    return "Fail on run";

  themes().Clear();
  if (stat > 10)
  {

    occ::handle<Transfer_Binder> bnd    = binder;
    int                          hasres = false;
    while (!bnd.IsNull())
    {
      if (bnd->Status() != Transfer_StatusVoid)
      {
        if (!hasres)
          themes().AssignCat("Result:");
        else
          themes().AssignCat(",");
        themes().AssignCat(bnd->ResultTypeName());
        hasres = true;
      }
      bnd = bnd->NextResult();
    }

    if (stat == 12)
      themes().AssignCat("/Warning");
    if (stat == 13)
      themes().AssignCat("/Fail");
  }
  return themes().ToCString();
}
