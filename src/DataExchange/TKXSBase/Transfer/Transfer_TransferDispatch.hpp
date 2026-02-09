#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_CopyTool.hpp>
class Interface_InterfaceModel;
class Interface_GeneralLib;
class Interface_Protocol;
class Transfer_TransientProcess;
class Standard_Transient;

class Transfer_TransferDispatch : public Interface_CopyTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Transfer_TransferDispatch(const occ::handle<Interface_InterfaceModel>& amodel,
                                            const Interface_GeneralLib&                  lib);

  Standard_EXPORT Transfer_TransferDispatch(const occ::handle<Interface_InterfaceModel>& amodel,
                                            const occ::handle<Interface_Protocol>&       protocol);

  Standard_EXPORT Transfer_TransferDispatch(const occ::handle<Interface_InterfaceModel>& amodel);

  Standard_EXPORT occ::handle<Transfer_TransientProcess> TransientProcess() const;

  Standard_EXPORT bool Copy(const occ::handle<Standard_Transient>& entfrom,
                            occ::handle<Standard_Transient>&       entto,
                            const bool                             mapped,
                            const bool                             errstat) override;
};
