

#include <IFSelect_ContextModif.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_SetVersion5.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SetVersion5, IGESSelect_ModelModifier)

IGESSelect_SetVersion5::IGESSelect_SetVersion5()
    : IGESSelect_ModelModifier(false)
{
}

void IGESSelect_SetVersion5::Performing(IFSelect_ContextModif&                 ctx,
                                        const occ::handle<IGESData_IGESModel>& target,
                                        Interface_CopyTool&) const
{
  IGESData_GlobalSection GS = target->GlobalSection();
  if (GS.IGESVersion() >= 9)
    return;
  GS.SetIGESVersion(9);
  GS.SetLastChangeDate();
  target->SetGlobalSection(GS);
  occ::handle<Interface_Check> check = new Interface_Check;
  target->VerifyCheck(check);
  if (check->HasFailed())
    ctx.CCheck()->GetMessages(check);
}

TCollection_AsciiString IGESSelect_SetVersion5::Label() const
{
  return TCollection_AsciiString("Update IGES Version in Global Section to 5.1");
}
