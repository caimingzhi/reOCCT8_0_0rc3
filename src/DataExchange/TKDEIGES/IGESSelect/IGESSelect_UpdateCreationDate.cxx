

#include <IFSelect_ContextModif.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_UpdateCreationDate.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <OSD_Process.hpp>
#include <Quantity_Date.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_UpdateCreationDate, IGESSelect_ModelModifier)

IGESSelect_UpdateCreationDate::IGESSelect_UpdateCreationDate()
    : IGESSelect_ModelModifier(false)
{
}

void IGESSelect_UpdateCreationDate::Performing(IFSelect_ContextModif&                 ctx,
                                               const occ::handle<IGESData_IGESModel>& target,
                                               Interface_CopyTool&) const
{
  int           jour, mois, annee, heure, minute, seconde, millisec, microsec;
  OSD_Process   system;
  Quantity_Date ladate = system.SystemDate();
  ladate.Values(mois, jour, annee, heure, minute, seconde, millisec, microsec);

  IGESData_GlobalSection GS = target->GlobalSection();
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

TCollection_AsciiString IGESSelect_UpdateCreationDate::Label() const
{
  return TCollection_AsciiString("Update Creation Date in IGES Global Section");
}
