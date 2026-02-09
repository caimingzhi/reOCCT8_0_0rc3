

#include <IFSelect_ContextModif.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_SetLabel.hpp>
#include <Interface_CopyTool.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SetLabel, IGESSelect_ModelModifier)

IGESSelect_SetLabel::IGESSelect_SetLabel(const int mode, const bool enforce)
    : IGESSelect_ModelModifier(false),
      themode(mode),
      theforce(enforce)
{
}

void IGESSelect_SetLabel::Performing(IFSelect_ContextModif&                 ctx,
                                     const occ::handle<IGESData_IGESModel>& target,
                                     Interface_CopyTool&) const
{
  occ::handle<TCollection_HAsciiString> lab;
  for (ctx.Start(); ctx.More(); ctx.Next())
  {
    DeclareAndCast(IGESData_IGESEntity, iges, ctx.ValueResult());
    if (iges.IsNull())
      continue;
    if (themode == 0)
    {
      iges->SetLabel(lab);
      continue;
    }

    lab = iges->ShortLabel();
    if (theforce)
      lab.Nullify();
    if (!lab.IsNull())
    {
      if (lab->Length() > 2)
      {
        if (lab->Value(1) == 'D' && lab->Value(2) == 'E' && atoi(&(lab->ToCString())[2]) > 0)
          lab.Nullify();
      }
    }

    if (lab.IsNull())
    {
      lab = new TCollection_HAsciiString(target->Number(iges) * 2 - 1);
      lab->Insert(1, "DE");
    }
    iges->SetLabel(lab);
  }
}

TCollection_AsciiString IGESSelect_SetLabel::Label() const
{
  TCollection_AsciiString lab;
  if (themode == 0)
    lab.AssignCat("Clear Short Label");
  if (themode == 1)
    lab.AssignCat("Set Short Label to DE Number");
  if (theforce)
    lab.AssignCat(" (enforced)");
  return lab;
}
