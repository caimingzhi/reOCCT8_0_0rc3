

#include <HeaderSection_FileDescription.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <RWHeaderSection_RWFileDescription.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWHeaderSection_RWFileDescription::RWHeaderSection_RWFileDescription() = default;

void RWHeaderSection_RWFileDescription::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<HeaderSection_FileDescription>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "file_description has not 2 parameter(s)"))
    return;

  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> aDescription;
  occ::handle<TCollection_HAsciiString>                                   aDescriptionItem;
  int nsub1 = data->SubListNumber(num, 1, false);
  if (nsub1 != 0)
  {
    int nb1 = data->NbParams(nsub1);
    if (nb1 > 0)
    {
      aDescription = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nb1);
      for (int i1 = 1; i1 <= nb1; i1++)
      {
        bool stat1 = data->ReadString(nsub1, i1, "description", ach, aDescriptionItem);
        if (stat1)
          aDescription->SetValue(i1, aDescriptionItem);
      }
    }
  }
  else
  {
    ach->AddFail("Parameter #1 (description) is not a LIST");
  }

  occ::handle<TCollection_HAsciiString> aImplementationLevel;
  data->ReadString(num, 2, "implementation_level", ach, aImplementationLevel);

  if (!ach->HasFailed())
    ent->Init(aDescription, aImplementationLevel);
}

void RWHeaderSection_RWFileDescription::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<HeaderSection_FileDescription>& ent) const
{

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbDescription(); i1++)
  {
    SW.Send(ent->DescriptionValue(i1));
  }
  SW.CloseSub();

  SW.Send(ent->ImplementationLevel());
}
