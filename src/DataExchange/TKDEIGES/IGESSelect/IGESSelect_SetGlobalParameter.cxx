

#include <IFSelect_ContextModif.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_SetGlobalParameter.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_FileParameter.hpp>
#include <Interface_ParamSet.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SetGlobalParameter, IGESSelect_ModelModifier)

IGESSelect_SetGlobalParameter::IGESSelect_SetGlobalParameter(const int numpar)
    : IGESSelect_ModelModifier(false)
{
  thenum = numpar;
}

int IGESSelect_SetGlobalParameter::GlobalNumber() const
{
  return thenum;
}

void IGESSelect_SetGlobalParameter::SetValue(const occ::handle<TCollection_HAsciiString>& text)
{
  theval = text;
}

occ::handle<TCollection_HAsciiString> IGESSelect_SetGlobalParameter::Value() const
{
  return theval;
}

void IGESSelect_SetGlobalParameter::Performing(IFSelect_ContextModif&                 ctx,
                                               const occ::handle<IGESData_IGESModel>& target,
                                               Interface_CopyTool&) const
{
  if (theval.IsNull())
  {
    ctx.CCheck()->AddWarning("Set IGES Global Parameter, no value defined, ignored");
    return;
  }
  IGESData_GlobalSection          GS     = target->GlobalSection();
  occ::handle<Interface_ParamSet> oldset = GS.Params();
  if (thenum <= 0 || thenum > oldset->NbParams())
  {
    char mess[80];
    Sprintf(mess, "Set IGES Global Parameter : Number %d incorrect", thenum);
    ctx.CCheck()->AddFail(mess);
    return;
  }
  Interface_FileParameter& FP = oldset->ChangeParam(thenum);
  FP.Init(theval->ToCString(), FP.ParamType());
  occ::handle<Interface_Check> check = new Interface_Check;
  GS.Init(oldset, check);
  ctx.AddCheck(check);
  if (!check->HasFailed())
    target->SetGlobalSection(GS);
}

TCollection_AsciiString IGESSelect_SetGlobalParameter::Label() const
{
  char mess[80];
  if (theval.IsNull())
    Sprintf(mess, "Set IGES Global Parameter (undefined)");
  else
    Sprintf(mess, "Set IGES Global Parameter Number %d to %s", thenum, theval->ToCString());
  return TCollection_AsciiString(mess);
}
