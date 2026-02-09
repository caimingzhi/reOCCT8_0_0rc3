

#include <IFSelect_ContextModif.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_UpdateFileName.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_UpdateFileName, IGESSelect_ModelModifier)

IGESSelect_UpdateFileName::IGESSelect_UpdateFileName()
    : IGESSelect_ModelModifier(false)
{
}

void IGESSelect_UpdateFileName::Performing(IFSelect_ContextModif&                 ctx,
                                           const occ::handle<IGESData_IGESModel>& target,
                                           Interface_CopyTool&) const
{
  if (!ctx.HasFileName())
  {
    ctx.CCheck(0)->AddWarning("New File Name unknown, former one is kept");
    return;
  }
  IGESData_GlobalSection GS = target->GlobalSection();
  GS.SetFileName(new TCollection_HAsciiString(ctx.FileName()));
  target->SetGlobalSection(GS);
  occ::handle<Interface_Check> check = new Interface_Check;
  target->VerifyCheck(check);
  ctx.AddCheck(check);
}

TCollection_AsciiString IGESSelect_UpdateFileName::Label() const
{
  return TCollection_AsciiString("Updates IGES File Name to new current one");
}
