

#include <HeaderSection_FileSchema.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <RWHeaderSection_RWFileSchema.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWHeaderSection_RWFileSchema::RWHeaderSection_RWFileSchema() = default;

void RWHeaderSection_RWFileSchema::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<HeaderSection_FileSchema>& ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "file_schema has not 1 parameter(s)"))
    return;

  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> aSchemaIdentifiers;
  occ::handle<TCollection_HAsciiString>                                   aSchemaIdentifiersItem;
  int                                                                     nsub1;
  nsub1 = data->SubListNumber(num, 1, false);
  if (nsub1 != 0)
  {
    int nb1            = data->NbParams(nsub1);
    aSchemaIdentifiers = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {
      bool stat1 = data->ReadString(nsub1, i1, "schema_identifiers", ach, aSchemaIdentifiersItem);
      if (stat1)
        aSchemaIdentifiers->SetValue(i1, aSchemaIdentifiersItem);
    }
  }
  else
  {
    ach->AddFail("Parameter #1 (schema_identifiers) is not a LIST");
  }

  if (!ach->HasFailed())
    ent->Init(aSchemaIdentifiers);
}

void RWHeaderSection_RWFileSchema::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<HeaderSection_FileSchema>& ent) const
{

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbSchemaIdentifiers(); i1++)
  {
    SW.Send(ent->SchemaIdentifiersValue(i1));
  }
  SW.CloseSub();
}
