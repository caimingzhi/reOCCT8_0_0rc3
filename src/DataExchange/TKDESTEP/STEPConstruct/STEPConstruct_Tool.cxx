#include <STEPConstruct_Tool.hpp>
#include <XSControl_TransferReader.hpp>
#include <XSControl_TransferWriter.hpp>
#include <XSControl_WorkSession.hpp>

STEPConstruct_Tool::STEPConstruct_Tool() = default;

STEPConstruct_Tool::STEPConstruct_Tool(const occ::handle<XSControl_WorkSession>& WS)
{
  SetWS(WS);
}

bool STEPConstruct_Tool::SetWS(const occ::handle<XSControl_WorkSession>& WS)
{
  myWS.Nullify();
  myTransientProcess.Nullify();
  myFinderProcess.Nullify();

  if (WS.IsNull())
    return false;
  myWS     = WS;
  myHGraph = myWS->HGraph();

  const occ::handle<XSControl_TransferReader>& TR = WS->TransferReader();
  if (!TR.IsNull())
    myTransientProcess = TR->TransientProcess();

  const occ::handle<XSControl_TransferWriter>& TW = myWS->TransferWriter();
  if (!TW.IsNull())
    myFinderProcess = TW->FinderProcess();

  return !myTransientProcess.IsNull() && !myFinderProcess.IsNull();
}
