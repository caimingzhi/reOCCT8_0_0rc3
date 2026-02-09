

#include <IFSelect_ContextModif.hpp>
#include <IGESData_BasicEditor.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESSelect_ComputeStatus.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_ComputeStatus, IGESSelect_ModelModifier)

IGESSelect_ComputeStatus::IGESSelect_ComputeStatus()
    : IGESSelect_ModelModifier(false)
{
}

void IGESSelect_ComputeStatus::Performing(IFSelect_ContextModif&                 ctx,
                                          const occ::handle<IGESData_IGESModel>& target,
                                          Interface_CopyTool&) const
{
  DeclareAndCast(IGESData_Protocol, protocol, ctx.Protocol());
  if (protocol.IsNull())
  {
    ctx.CCheck()->AddFail("IGES Compute Status, Protocol incorrect");
    return;
  }

  IGESData_BasicEditor corrector(target, protocol);
  corrector.ComputeStatus();
}

TCollection_AsciiString IGESSelect_ComputeStatus::Label() const
{
  return TCollection_AsciiString("Compute Status of IGES Entities (Directory Part)");
}
