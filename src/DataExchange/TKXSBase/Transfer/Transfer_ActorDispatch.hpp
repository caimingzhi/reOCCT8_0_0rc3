#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Transfer_TransferDispatch.hpp>
#include <Transfer_ActorOfTransientProcess.hpp>
class Interface_InterfaceModel;
class Interface_GeneralLib;
class Interface_Protocol;
class Transfer_Binder;
class Standard_Transient;
class Transfer_TransientProcess;

class Transfer_ActorDispatch : public Transfer_ActorOfTransientProcess
{

public:
  Standard_EXPORT Transfer_ActorDispatch(const occ::handle<Interface_InterfaceModel>& amodel,
                                         const Interface_GeneralLib&                  lib);

  Standard_EXPORT Transfer_ActorDispatch(const occ::handle<Interface_InterfaceModel>& amodel,
                                         const occ::handle<Interface_Protocol>&       protocol);

  Standard_EXPORT Transfer_ActorDispatch(const occ::handle<Interface_InterfaceModel>& amodel);

  Standard_EXPORT void AddActor(const occ::handle<Transfer_ActorOfTransientProcess>& actor);

  Standard_EXPORT Transfer_TransferDispatch& TransferDispatch();

  Standard_EXPORT occ::handle<Transfer_Binder> Transfer(
    const occ::handle<Standard_Transient>&        start,
    const occ::handle<Transfer_TransientProcess>& TP,
    const Message_ProgressRange&                  theProgress = Message_ProgressRange()) override;

  DEFINE_STANDARD_RTTIEXT(Transfer_ActorDispatch, Transfer_ActorOfTransientProcess)

private:
  Transfer_TransferDispatch thetool;
};
