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
  Standard_EXPORT void Perform(IFSelect_ContextModif&                       ctx,
                               const occ::handle<Interface_InterfaceModel>& target,
                               const occ::handle<Interface_Protocol>&       protocol,
                               Interface_CopyTool&                          TC) const override;

  Standard_EXPORT virtual void PerformProtocol(IFSelect_ContextModif&                 ctx,
                                               const occ::handle<IGESData_IGESModel>& target,
                                               const occ::handle<IGESData_Protocol>&  proto,
                                               Interface_CopyTool&                    TC) const;

  Standard_EXPORT virtual void Performing(IFSelect_ContextModif&                 ctx,
                                          const occ::handle<IGESData_IGESModel>& target,
                                          Interface_CopyTool&                    TC) const = 0;

  DEFINE_STANDARD_RTTI_INLINE(IGESSelect_ModelModifier, IFSelect_Modifier)

protected:
  Standard_EXPORT IGESSelect_ModelModifier(const bool maychangegraph);
};
