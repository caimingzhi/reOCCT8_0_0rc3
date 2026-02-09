

#include <Interface_Check.hpp>
#include "RWStepBasic_RWPerson.hpp"
#include <StepBasic_Person.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWPerson::RWStepBasic_RWPerson() = default;

void RWStepBasic_RWPerson::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                    const int                                   num,
                                    occ::handle<Interface_Check>&               ach,
                                    const occ::handle<StepBasic_Person>&        ent) const
{

  if (!data->CheckNbParams(num, 6, ach, "person"))
    return;

  occ::handle<TCollection_HAsciiString> aId;

  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aLastName;
  bool                                  hasAlastName = true;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "last_name", ach, aLastName);
  }
  else
  {
    hasAlastName = false;
    aLastName.Nullify();
  }

  occ::handle<TCollection_HAsciiString> aFirstName;
  bool                                  hasAfirstName = true;
  if (data->IsParamDefined(num, 3))
  {

    data->ReadString(num, 3, "first_name", ach, aFirstName);
  }
  else
  {
    hasAfirstName = false;
    aFirstName.Nullify();
  }

  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> aMiddleNames;
  bool                                                                    hasAmiddleNames = true;
  if (data->IsParamDefined(num, 4))
  {
    occ::handle<TCollection_HAsciiString> aMiddleNamesItem;
    int                                   nsub4;
    if (data->ReadSubList(num, 4, "middle_names", ach, nsub4))
    {
      int nb4      = data->NbParams(nsub4);
      aMiddleNames = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nb4);
      for (int i4 = 1; i4 <= nb4; i4++)
      {

        if (data->ReadString(nsub4, i4, "middle_names", ach, aMiddleNamesItem))
          aMiddleNames->SetValue(i4, aMiddleNamesItem);
      }
    }
  }
  else
  {
    hasAmiddleNames = false;
    aMiddleNames.Nullify();
  }

  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> aPrefixTitles;
  bool                                                                    hasAprefixTitles = true;
  if (data->IsParamDefined(num, 5))
  {
    occ::handle<TCollection_HAsciiString> aPrefixTitlesItem;
    int                                   nsub5;
    if (data->ReadSubList(num, 5, "prefix_titles", ach, nsub5))
    {
      int nb5       = data->NbParams(nsub5);
      aPrefixTitles = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nb5);
      for (int i5 = 1; i5 <= nb5; i5++)
      {

        if (data->ReadString(nsub5, i5, "prefix_titles", ach, aPrefixTitlesItem))
          aPrefixTitles->SetValue(i5, aPrefixTitlesItem);
      }
    }
  }
  else
  {
    hasAprefixTitles = false;
    aPrefixTitles.Nullify();
  }

  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> aSuffixTitles;
  bool                                                                    hasAsuffixTitles = true;
  if (data->IsParamDefined(num, 6))
  {
    occ::handle<TCollection_HAsciiString> aSuffixTitlesItem;
    int                                   nsub6;
    if (data->ReadSubList(num, 6, "suffix_titles", ach, nsub6))
    {
      int nb6       = data->NbParams(nsub6);
      aSuffixTitles = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nb6);
      for (int i6 = 1; i6 <= nb6; i6++)
      {

        if (data->ReadString(nsub6, i6, "suffix_titles", ach, aSuffixTitlesItem))
          aSuffixTitles->SetValue(i6, aSuffixTitlesItem);
      }
    }
  }
  else
  {
    hasAsuffixTitles = false;
    aSuffixTitles.Nullify();
  }

  ent->Init(aId,
            hasAlastName,
            aLastName,
            hasAfirstName,
            aFirstName,
            hasAmiddleNames,
            aMiddleNames,
            hasAprefixTitles,
            aPrefixTitles,
            hasAsuffixTitles,
            aSuffixTitles);
}

void RWStepBasic_RWPerson::WriteStep(StepData_StepWriter&                 SW,
                                     const occ::handle<StepBasic_Person>& ent) const
{

  SW.Send(ent->Id());

  bool hasAlastName = ent->HasLastName();
  if (hasAlastName)
  {
    SW.Send(ent->LastName());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAfirstName = ent->HasFirstName();
  if (hasAfirstName)
  {
    SW.Send(ent->FirstName());
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAmiddleNames = ent->HasMiddleNames();
  if (hasAmiddleNames)
  {
    SW.OpenSub();
    for (int i4 = 1; i4 <= ent->NbMiddleNames(); i4++)
    {
      SW.Send(ent->MiddleNamesValue(i4));
    }
    SW.CloseSub();
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAprefixTitles = ent->HasPrefixTitles();
  if (hasAprefixTitles)
  {
    SW.OpenSub();
    for (int i5 = 1; i5 <= ent->NbPrefixTitles(); i5++)
    {
      SW.Send(ent->PrefixTitlesValue(i5));
    }
    SW.CloseSub();
  }
  else
  {
    SW.SendUndef();
  }

  bool hasAsuffixTitles = ent->HasSuffixTitles();
  if (hasAsuffixTitles)
  {
    SW.OpenSub();
    for (int i6 = 1; i6 <= ent->NbSuffixTitles(); i6++)
    {
      SW.Send(ent->SuffixTitlesValue(i6));
    }
    SW.CloseSub();
  }
  else
  {
    SW.SendUndef();
  }
}
