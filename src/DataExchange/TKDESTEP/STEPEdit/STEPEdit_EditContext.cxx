

#include <IFSelect_EditForm.hpp>
#include <Interface_TypedValue.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepBasic_ApplicationProtocolDefinition.hpp>
#include <STEPConstruct_ContextTool.hpp>
#include <StepData_StepModel.hpp>
#include <STEPEdit_EditContext.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPEdit_EditContext, IFSelect_Editor)

STEPEdit_EditContext::STEPEdit_EditContext()
    : IFSelect_Editor(5)
{
  occ::handle<Interface_TypedValue> ac_val =
    new Interface_TypedValue("Application Context", Interface_ParamIdent);
  SetValue(1, ac_val, "AC", IFSelect_EditRead);

  occ::handle<Interface_TypedValue> ac_status = new Interface_TypedValue("AppliContext_Status");
  SetValue(2, ac_status, "AC_Status");
  occ::handle<Interface_TypedValue> ac_sche = new Interface_TypedValue("AppliContext_Schema");
  SetValue(3, ac_sche, "AC_Schema");
  occ::handle<Interface_TypedValue> ac_year =
    new Interface_TypedValue("AppliContext_Year", Interface_ParamInteger);
  SetValue(4, ac_year, "AC_Year");
  occ::handle<Interface_TypedValue> ac_name = new Interface_TypedValue("AppliContext_Name");
  SetValue(5, ac_name, "AC_Name");
}

TCollection_AsciiString STEPEdit_EditContext::Label() const
{
  return TCollection_AsciiString("STEP : Product Definition Context");
}

bool STEPEdit_EditContext::Recognize(const occ::handle<IFSelect_EditForm>&) const
{

  return true;
}

occ::handle<TCollection_HAsciiString> STEPEdit_EditContext::StringValue(
  const occ::handle<IFSelect_EditForm>&,
  const int num) const
{
  occ::handle<TCollection_HAsciiString> str;
  switch (num)
  {
    case 2:
      return new TCollection_HAsciiString("DIS");
    case 3:
      return new TCollection_HAsciiString("automotive_design");
    case 4:
      return new TCollection_HAsciiString("1998");
    case 5:
      return new TCollection_HAsciiString("EUCLID");
    case 7:
      return new TCollection_HAsciiString("Undefined Category");
    case 8:
      return new TCollection_HAsciiString("Undefined Description");
    default:
      break;
  }
  return str;
}

bool STEPEdit_EditContext::Load(const occ::handle<IFSelect_EditForm>& form,
                                const occ::handle<Standard_Transient>&,
                                const occ::handle<Interface_InterfaceModel>& model) const
{
  occ::handle<StepData_StepModel> modl = occ::down_cast<StepData_StepModel>(model);
  if (modl.IsNull())
    return false;

  STEPConstruct_ContextTool ctx(modl);
  StepData_Factors          aLocalFactors;
  ctx.SetGlobalFactor(aLocalFactors);

  form->LoadValue(1, modl->StringLabel(ctx.GetAPD()));

  form->LoadValue(2, ctx.GetACstatus());
  form->LoadValue(3, ctx.GetACschemaName());
  form->LoadValue(4, new TCollection_HAsciiString(ctx.GetACyear()));
  form->LoadValue(5, ctx.GetACname());

  return true;
}

bool STEPEdit_EditContext::Apply(const occ::handle<IFSelect_EditForm>& form,
                                 const occ::handle<Standard_Transient>&,
                                 const occ::handle<Interface_InterfaceModel>& model) const
{
  occ::handle<StepData_StepModel> modl = occ::down_cast<StepData_StepModel>(model);
  if (modl.IsNull())
    return false;

  STEPConstruct_ContextTool ctx(modl);
  StepData_Factors          aLocalFactors;
  ctx.SetGlobalFactor(aLocalFactors);

  ctx.AddAPD();

  if (form->IsModified(2))
    ctx.SetACstatus(form->EditedValue(2));
  if (form->IsModified(3))
    ctx.SetACschemaName(form->EditedValue(3));
  if (form->IsModified(4))
    ctx.SetACyear(form->EditedValue(4)->IntegerValue());
  if (form->IsModified(5))
    ctx.SetACname(form->EditedValue(5));

  return true;
}
