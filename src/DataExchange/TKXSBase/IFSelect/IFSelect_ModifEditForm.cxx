

#include <IFSelect_ContextModif.hpp>
#include <IFSelect_EditForm.hpp>
#include <IFSelect_ModifEditForm.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_ModifEditForm, IFSelect_Modifier)

IFSelect_ModifEditForm::IFSelect_ModifEditForm(const occ::handle<IFSelect_EditForm>& editform)
    : IFSelect_Modifier(false)
{
  theedit = editform;
}

occ::handle<IFSelect_EditForm> IFSelect_ModifEditForm::EditForm() const
{
  return theedit;
}

void IFSelect_ModifEditForm::Perform(IFSelect_ContextModif&                       ctx,
                                     const occ::handle<Interface_InterfaceModel>& target,
                                     const occ::handle<Interface_Protocol>&,
                                     Interface_CopyTool&) const
{
  for (ctx.Start(); ctx.More(); ctx.Next())
  {
    bool done = theedit->ApplyData(ctx.ValueResult(), target);
    if (done)
      ctx.Trace();
    else
      ctx.AddWarning(ctx.ValueResult(), "EditForm could not be applied");
  }
}

TCollection_AsciiString IFSelect_ModifEditForm::Label() const
{
  const char*             editlab = theedit->Label();
  TCollection_AsciiString lab("Apply EditForm");
  if (editlab && editlab[0] != '\0')
  {
    lab.AssignCat(" : ");
    lab.AssignCat(editlab);
  }
  return lab;
}
