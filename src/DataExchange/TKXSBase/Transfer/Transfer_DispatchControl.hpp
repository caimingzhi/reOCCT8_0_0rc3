#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_CopyControl.hpp>
class Transfer_TransientProcess;
class Interface_InterfaceModel;
class Standard_Transient;

//! This is an auxiliary class for TransferDispatch, which allows
//! to record simple copies, as CopyControl from Interface, but
//! based on a TransientProcess. Hence, it allows in addition
//! more actions (such as recording results of adaptations)
class Transfer_DispatchControl : public Interface_CopyControl
{

public:
  //! Creates the DispatchControl, ready for use
  Standard_EXPORT Transfer_DispatchControl(const occ::handle<Interface_InterfaceModel>&  model,
                                           const occ::handle<Transfer_TransientProcess>& TP);

  //! Returns the content of the DispatchControl : it can be used
  //! for a direct call, if the basic methods do not suffice
  Standard_EXPORT const occ::handle<Transfer_TransientProcess>& TransientProcess() const;

  //! Returns the Model from which the transfer is to be done
  Standard_EXPORT const occ::handle<Interface_InterfaceModel>& StartingModel() const;

  //! Clears the List of Copied Results
  Standard_EXPORT void Clear() override;

  //! Binds a (Transient) Result to a (Transient) Starting Entity
  Standard_EXPORT void Bind(const occ::handle<Standard_Transient>& ent,
                            const occ::handle<Standard_Transient>& res) override;

  //! Searches for the Result bound to a Starting Entity
  //! If Found, returns True and fills <res>
  //! Else, returns False and nullifies <res>
  Standard_EXPORT bool Search(const occ::handle<Standard_Transient>& ent,
                              occ::handle<Standard_Transient>&       res) const override;

  DEFINE_STANDARD_RTTIEXT(Transfer_DispatchControl, Interface_CopyControl)

private:
  occ::handle<Transfer_TransientProcess> theTP;
  occ::handle<Interface_InterfaceModel>  themodel;
};

