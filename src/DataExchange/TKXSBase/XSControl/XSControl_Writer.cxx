

#include <Interface_InterfaceModel.hpp>
#include <TopoDS_Shape.hpp>
#include <XSControl_Controller.hpp>
#include <XSControl_WorkSession.hpp>
#include <XSControl_Writer.hpp>

XSControl_Writer::XSControl_Writer()
{
  SetWS(new XSControl_WorkSession);
}

XSControl_Writer::XSControl_Writer(const char* norm)
{
  SetNorm(norm);
}

XSControl_Writer::XSControl_Writer(const occ::handle<XSControl_WorkSession>& WS, const bool scratch)
{
  SetWS(WS, scratch);
}

bool XSControl_Writer::SetNorm(const char* norm)
{
  if (thesession.IsNull())
    SetWS(new XSControl_WorkSession);
  bool                                  sess  = thesession->SelectNorm(norm);
  occ::handle<Interface_InterfaceModel> model = Model();
  return sess;
}

void XSControl_Writer::SetWS(const occ::handle<XSControl_WorkSession>& WS, const bool scratch)
{
  thesession = WS;

  thesession->InitTransferReader(0);
  occ::handle<Interface_InterfaceModel> model = Model(scratch);
}

occ::handle<XSControl_WorkSession> XSControl_Writer::WS() const
{
  return thesession;
}

occ::handle<Interface_InterfaceModel> XSControl_Writer::Model(const bool newone)
{
  occ::handle<Interface_InterfaceModel> model = thesession->Model();
  if (newone || model.IsNull())
    model = thesession->NewModel();
  return model;
}

IFSelect_ReturnStatus XSControl_Writer::TransferShape(const TopoDS_Shape&          sh,
                                                      const int                    mode,
                                                      const Message_ProgressRange& theProgress)
{
  thesession->TransferWriter()->SetTransferMode(mode);
  return thesession->TransferWriteShape(sh, true, theProgress);
}

IFSelect_ReturnStatus XSControl_Writer::WriteFile(const char* filename)
{
  return thesession->SendAll(filename);
}

void XSControl_Writer::PrintStatsTransfer(const int what, const int mode) const
{
  thesession->TransferWriter()->PrintStats(what, mode);
}
