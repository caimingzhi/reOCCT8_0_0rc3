#include <StepSelect_ModelModifier.hpp>

#include <Standard_Type.hpp>

#include <StepData_StepModel.hpp>
#include <StepData_Protocol.hpp>
#include <IFSelect_ContextModif.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_Check.hpp>

StepSelect_ModelModifier::StepSelect_ModelModifier(const bool grf)
    : IFSelect_Modifier(grf)
{
}

void StepSelect_ModelModifier::Perform(IFSelect_ContextModif&                       ctx,
                                       const occ::handle<Interface_InterfaceModel>& target,
                                       const occ::handle<Interface_Protocol>&       protocol,
                                       Interface_CopyTool&                          TC) const
{
  ctx.TraceModifier(this);
  occ::handle<StepData_StepModel> targ = occ::down_cast<StepData_StepModel>(target);
  occ::handle<StepData_Protocol>  prot = occ::down_cast<StepData_Protocol>(protocol);
  if (targ.IsNull())
  {
    ctx.CCheck()->AddFail("Model to Modify : unproper type");
    return;
  }
  PerformProtocol(ctx, targ, prot, TC);
}

void StepSelect_ModelModifier::PerformProtocol(IFSelect_ContextModif&                 ctx,
                                               const occ::handle<StepData_StepModel>& target,
                                               const occ::handle<StepData_Protocol>&  protocol,
                                               Interface_CopyTool&                    TC) const
{
  ctx.SetProtocol(protocol);
  Performing(ctx, target, TC);
}
