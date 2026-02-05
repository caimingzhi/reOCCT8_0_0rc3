#include <IGESBasic_ExternalReferenceFile.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_ExternalReferenceFile, IGESData_IGESEntity)

IGESBasic_ExternalReferenceFile::IGESBasic_ExternalReferenceFile() = default;

void IGESBasic_ExternalReferenceFile::Init(
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aNameArray)
{
  if (aNameArray->Lower() != 1)
    throw Standard_DimensionMismatch("IGESBasic_ExternalReferenceFile : Init");
  theNames = aNameArray;
  InitTypeAndForm(406, 12);
}

int IGESBasic_ExternalReferenceFile::NbListEntries() const
{
  return theNames->Length();
}

occ::handle<TCollection_HAsciiString> IGESBasic_ExternalReferenceFile::Name(const int Index) const
{
  return theNames->Value(Index);
}
