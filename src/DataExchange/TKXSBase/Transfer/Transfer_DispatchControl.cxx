

#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Transfer_DispatchControl.hpp>
#include <Transfer_TransientProcess.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_DispatchControl, Interface_CopyControl)

Transfer_DispatchControl::Transfer_DispatchControl(
  const occ::handle<Interface_InterfaceModel>&  model,
  const occ::handle<Transfer_TransientProcess>& TP)
{
  themodel = model;
  theTP    = TP;
}

const occ::handle<Transfer_TransientProcess>& Transfer_DispatchControl::TransientProcess() const
{
  return theTP;
}

const occ::handle<Interface_InterfaceModel>& Transfer_DispatchControl::StartingModel() const
{
  return themodel;
}

void Transfer_DispatchControl::Clear()
{
  theTP->Clear();
}

void Transfer_DispatchControl::Bind(const occ::handle<Standard_Transient>& ent,
                                    const occ::handle<Standard_Transient>& res)
{
  theTP->BindTransient(ent, res);
}

bool Transfer_DispatchControl::Search(const occ::handle<Standard_Transient>& ent,
                                      occ::handle<Standard_Transient>&       res) const
{
  res = theTP->FindTransient(ent);
  return !res.IsNull();
}
