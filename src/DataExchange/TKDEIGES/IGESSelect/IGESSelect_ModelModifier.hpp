#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Modifier.hpp>
class IGESData_IGESModel;
class IGESData_Protocol;
class IFSelect_ContextModif;
class Interface_InterfaceModel;
class Interface_Protocol;
class Interface_CopyTool;

class IGESSelect_ModelModifier : public IFSelect_Modifier
{

public:
  //! The inherited Perform does the required cast (and refuses to
  //! go further if cast has failed) then calls the instantiated
  //! Performing
  Standard_EXPORT void Perform(IFSelect_ContextModif&                       ctx,
                               const occ::handle<Interface_InterfaceModel>& target,
                               const occ::handle<Interface_Protocol>&       protocol,
                               Interface_CopyTool&                          TC) const override;

  //! Specific Perform with Protocol. It is defined to let the
  //! Protocol unused and to call Performing without Protocol
  //! (most current case). It can be redefined if specific action
  //! requires Protocol.
  Standard_EXPORT virtual void PerformProtocol(IFSelect_ContextModif&                 ctx,
                                               const occ::handle<IGESData_IGESModel>& target,
                                               const occ::handle<IGESData_Protocol>&  proto,
                                               Interface_CopyTool&                    TC) const;

  //! Specific Perform, without Protocol. If Performing with
  //! Protocol is redefined, Performing without Protocol must
  //! though be defined to do nothing (not called, but demanded
  //! by the linker)
  Standard_EXPORT virtual void Performing(IFSelect_ContextModif&                 ctx,
                                          const occ::handle<IGESData_IGESModel>& target,
                                          Interface_CopyTool&                    TC) const = 0;

  DEFINE_STANDARD_RTTI_INLINE(IGESSelect_ModelModifier, IFSelect_Modifier)

protected:
  //! Calls inherited Initialize, transmits to it the information
  //! <maychangegraph>
  Standard_EXPORT IGESSelect_ModelModifier(const bool maychangegraph);
};
