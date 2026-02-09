#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_CopyControl.hpp>
class Transfer_TransientProcess;
class Interface_InterfaceModel;
class Standard_Transient;

class Transfer_DispatchControl : public Interface_CopyControl
{

public:
  Standard_EXPORT Transfer_DispatchControl(const occ::handle<Interface_InterfaceModel>&  model,
                                           const occ::handle<Transfer_TransientProcess>& TP);

  Standard_EXPORT const occ::handle<Transfer_TransientProcess>& TransientProcess() const;

  Standard_EXPORT const occ::handle<Interface_InterfaceModel>& StartingModel() const;

  Standard_EXPORT void Clear() override;

  Standard_EXPORT void Bind(const occ::handle<Standard_Transient>& ent,
                            const occ::handle<Standard_Transient>& res) override;

  Standard_EXPORT bool Search(const occ::handle<Standard_Transient>& ent,
                              occ::handle<Standard_Transient>&       res) const override;

  DEFINE_STANDARD_RTTIEXT(Transfer_DispatchControl, Interface_CopyControl)

private:
  occ::handle<Transfer_TransientProcess> theTP;
  occ::handle<Interface_InterfaceModel>  themodel;
};
