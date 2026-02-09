

#include <IFSelect_ContextModif.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_UpdateLastChange.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <OSD_Process.hpp>
#include <Quantity_Date.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_UpdateLastChange, IGESSelect_ModelModifier)

IGESSelect_UpdateLastChange::IGESSelect_UpdateLastChange()
    : IGESSelect_ModelModifier(false)
{
}

void IGESSelect_UpdateLastChange::Performing(IFSelect_ContextModif&                 ctx,
                                             const occ::handle<IGESData_IGESModel>& target,
                                             Interface_CopyTool&) const
{
  int           jour, mois, annee, heure, minute, seconde, millisec, microsec;
  OSD_Process   system;
  Quantity_Date ladate = system.SystemDate();
  ladate.Values(mois, jour, annee, heure, minute, seconde, millisec, microsec);

  IGESData_GlobalSection GS = target->GlobalSection();
  if (GS.IGESVersion() < 9)
    GS.SetIGESVersion(9);
  if (annee < 2000)

    GS.SetDate(IGESData_GlobalSection::NewDateString(annee, mois, jour, heure, minute, seconde, 0));
  else

    GS.SetDate(
      IGESData_GlobalSection::NewDateString(annee, mois, jour, heure, minute, seconde, -1));
  target->SetGlobalSection(GS);
  occ::handle<Interface_Check> check = new Interface_Check;
  target->VerifyCheck(check);
  ctx.AddCheck(check);
}

TCollection_AsciiString IGESSelect_UpdateLastChange::Label() const
{
  return TCollection_AsciiString("Update Last Change Date in IGES Global Section");
}
