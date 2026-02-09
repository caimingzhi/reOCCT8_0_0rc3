#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Message_ProgressRange.hpp>

class Transfer_TransientProcess;
class Interface_InterfaceModel;
class Transfer_ActorOfTransientProcess;
class Standard_Transient;
class Interface_Protocol;
class Interface_Graph;
class Interface_EntityIterator;

class Transfer_TransferOutput
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Transfer_TransferOutput(
    const occ::handle<Transfer_ActorOfTransientProcess>& actor,
    const occ::handle<Interface_InterfaceModel>&         amodel);

  Standard_EXPORT Transfer_TransferOutput(const occ::handle<Transfer_TransientProcess>& proc,
                                          const occ::handle<Interface_InterfaceModel>&  amodel);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT occ::handle<Transfer_TransientProcess> TransientProcess() const;

  Standard_EXPORT void Transfer(const occ::handle<Standard_Transient>& obj,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void TransferRoots(
    const occ::handle<Interface_Protocol>& protocol,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  Standard_EXPORT void TransferRoots(
    const Interface_Graph&       G,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void TransferRoots(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT Interface_EntityIterator ListForStatus(const bool normal,
                                                         const bool roots = true) const;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> ModelForStatus(
    const occ::handle<Interface_Protocol>& protocol,
    const bool                             normal,
    const bool                             roots = true) const;

private:
  occ::handle<Transfer_TransientProcess> theproc;
  occ::handle<Interface_InterfaceModel>  themodel;
};
