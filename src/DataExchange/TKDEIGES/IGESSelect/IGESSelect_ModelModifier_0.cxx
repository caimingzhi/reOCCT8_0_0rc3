#include <IGESSelect_ModelModifier.hpp>

#include <Standard_Type.hpp>

#include <IGESData_IGESModel.hpp>
#include <IGESData_Protocol.hpp>
#include <IFSelect_ContextModif.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_Check.hpp>

IGESSelect_ModelModifier::IGESSelect_ModelModifier(const bool grf)
    : IFSelect_Modifier(grf)
{
}

void IGESSelect_ModelModifier::Perform(IFSelect_ContextModif&                       ctx,
                                       const occ::handle<Interface_InterfaceModel>& target,
                                       const occ::handle<Interface_Protocol>&       protocol,
                                       Interface_CopyTool&                          TC) const
{
  ctx.TraceModifier(this);
  occ::handle<IGESData_IGESModel> targ = occ::down_cast<IGESData_IGESModel>(target);
  occ::handle<IGESData_Protocol>  prot = occ::down_cast<IGESData_Protocol>(protocol);
  if (targ.IsNull())
  {
    ctx.CCheck()->AddFail("Model to Modify : unproper type");
    return;
  }
  PerformProtocol(ctx, targ, prot, TC);
}

void IGESSelect_ModelModifier::PerformProtocol(IFSelect_ContextModif&                 ctx,
                                               const occ::handle<IGESData_IGESModel>& target,
                                               const occ::handle<IGESData_Protocol>&  protocol,
                                               Interface_CopyTool&                    TC) const
{
  ctx.SetProtocol(protocol);
  Performing(ctx, target, TC);
}
