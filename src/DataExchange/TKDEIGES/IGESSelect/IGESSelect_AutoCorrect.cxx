

#include <IFSelect_ContextModif.hpp>
#include <IGESData_BasicEditor.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESSelect_AutoCorrect.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_AutoCorrect, IGESSelect_ModelModifier)

IGESSelect_AutoCorrect::IGESSelect_AutoCorrect()
    : IGESSelect_ModelModifier(false)
{
}

void IGESSelect_AutoCorrect::Performing(IFSelect_ContextModif&                 ctx,
                                        const occ::handle<IGESData_IGESModel>& target,
                                        Interface_CopyTool&) const
{
  DeclareAndCast(IGESData_Protocol, protocol, ctx.Protocol());
  if (protocol.IsNull())
  {
    ctx.CCheck()->AddFail("IGES Auto Correct, not called with Protocol");
    return;
  }

  IGESData_BasicEditor corrector(target, protocol);
  for (ctx.Start(); ctx.More(); ctx.Next())
  {
    DeclareAndCast(IGESData_IGESEntity, ent, ctx.ValueResult());
    bool done = corrector.AutoCorrect(ent);
    if (done)
      ctx.Trace();
  }
}

TCollection_AsciiString IGESSelect_AutoCorrect::Label() const
{
  return TCollection_AsciiString("Auto-Correction of IGES Entities");
}
