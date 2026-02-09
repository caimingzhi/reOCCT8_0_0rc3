#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Interface_EntityIterator;
class Transfer_TransferIterator;
class Transfer_TransientProcess;
class Interface_InterfaceModel;
class Interface_Protocol;
class Transfer_FinderProcess;

class Transfer_TransferInput
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Transfer_TransferInput();

  Standard_EXPORT Interface_EntityIterator Entities(Transfer_TransferIterator& list) const;

  Standard_EXPORT void FillModel(const occ::handle<Transfer_TransientProcess>& proc,
                                 const occ::handle<Interface_InterfaceModel>&  amodel) const;

  Standard_EXPORT void FillModel(const occ::handle<Transfer_TransientProcess>& proc,
                                 const occ::handle<Interface_InterfaceModel>&  amodel,
                                 const occ::handle<Interface_Protocol>&        proto,
                                 const bool                                    roots = true) const;

  Standard_EXPORT void FillModel(const occ::handle<Transfer_FinderProcess>&   proc,
                                 const occ::handle<Interface_InterfaceModel>& amodel) const;

  Standard_EXPORT void FillModel(const occ::handle<Transfer_FinderProcess>&   proc,
                                 const occ::handle<Interface_InterfaceModel>& amodel,
                                 const occ::handle<Interface_Protocol>&       proto,
                                 const bool                                   roots = true) const;
};
