

#include <Interface_GeneralLib.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Transfer_ActorDispatch.hpp>
#include <Transfer_ActorOfTransientProcess.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_TransferDispatch.hpp>
#include <Transfer_TransientProcess.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_ActorDispatch, Transfer_ActorOfTransientProcess)

Transfer_ActorDispatch::Transfer_ActorDispatch(const occ::handle<Interface_InterfaceModel>& amodel,
                                               const Interface_GeneralLib&                  lib)
    : thetool(amodel, lib)
{
  SetLast(true);
  thetool.TransientProcess()->SetActor(this);
}

Transfer_ActorDispatch::Transfer_ActorDispatch(const occ::handle<Interface_InterfaceModel>& amodel,
                                               const occ::handle<Interface_Protocol>& protocol)
    : thetool(amodel, protocol)
{
  SetLast(true);
  thetool.TransientProcess()->SetActor(this);
}

Transfer_ActorDispatch::Transfer_ActorDispatch(const occ::handle<Interface_InterfaceModel>& amodel)
    : thetool(amodel)
{
  SetLast(true);
  thetool.TransientProcess()->SetActor(this);
}

void Transfer_ActorDispatch::AddActor(const occ::handle<Transfer_ActorOfTransientProcess>& actor)
{
  thetool.TransientProcess()->SetActor(actor);
}

Transfer_TransferDispatch& Transfer_ActorDispatch::TransferDispatch()
{
  return thetool;
}

occ::handle<Transfer_Binder> Transfer_ActorDispatch::Transfer(
  const occ::handle<Standard_Transient>& start,
  const occ::handle<Transfer_TransientProcess>&,
  const Message_ProgressRange&)
{
  thetool.TransferEntity(start);
  return thetool.TransientProcess()->Find(start);
}
