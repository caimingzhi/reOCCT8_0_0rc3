

#include <Interface_GeneralLib.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Transfer_DispatchControl.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <Transfer_TransferDispatch.hpp>
#include <Transfer_TransientProcess.hpp>

Transfer_TransferDispatch::Transfer_TransferDispatch(
  const occ::handle<Interface_InterfaceModel>& amodel,
  const Interface_GeneralLib&                  lib)
    : Interface_CopyTool(amodel, lib)
{
  SetControl(
    new Transfer_DispatchControl(amodel, new Transfer_TransientProcess(amodel->NbEntities())));
}

Transfer_TransferDispatch::Transfer_TransferDispatch(
  const occ::handle<Interface_InterfaceModel>& amodel,
  const occ::handle<Interface_Protocol>&       protocol)
    : Interface_CopyTool(amodel, protocol)
{
  SetControl(
    new Transfer_DispatchControl(amodel, new Transfer_TransientProcess(amodel->NbEntities())));
}

Transfer_TransferDispatch::Transfer_TransferDispatch(
  const occ::handle<Interface_InterfaceModel>& amodel)
    : Interface_CopyTool(amodel)
{
  SetControl(
    new Transfer_DispatchControl(amodel, new Transfer_TransientProcess(amodel->NbEntities())));
}

occ::handle<Transfer_TransientProcess> Transfer_TransferDispatch::TransientProcess() const
{
  return occ::down_cast<Transfer_DispatchControl>(Control())->TransientProcess();
}

bool Transfer_TransferDispatch::Copy(const occ::handle<Standard_Transient>& entfrom,
                                     occ::handle<Standard_Transient>&       entto,
                                     const bool                             mapped,
                                     const bool                             errstat)
{
  occ::handle<Transfer_Binder> result = TransientProcess()->Transferring(entfrom);
  if (result.IsNull())
    return Interface_CopyTool::Copy(entfrom, entto, mapped, errstat);

  if (!result->IsKind(STANDARD_TYPE(Transfer_SimpleBinderOfTransient)))
    return false;
  entto = GetCasted(Transfer_SimpleBinderOfTransient, result)->Result();
  return true;
}
