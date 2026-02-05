#include <IGESBasic_ExternalRefFileIndex.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_ExternalRefFileIndex, IGESData_IGESEntity)

IGESBasic_ExternalRefFileIndex::IGESBasic_ExternalRefFileIndex() = default;

void IGESBasic_ExternalRefFileIndex::Init(
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aNameArray,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&      allEntities)
{
  if (aNameArray->Lower() != 1 || allEntities->Lower() != 1
      || aNameArray->Length() != allEntities->Length())
    throw Standard_DimensionMismatch("IGESBasic_ExternalRefFileIndex: Init");

  theNames    = aNameArray;
  theEntities = allEntities;
  InitTypeAndForm(402, 12);
}

int IGESBasic_ExternalRefFileIndex::NbEntries() const
{
  return theNames->Length();
}

occ::handle<TCollection_HAsciiString> IGESBasic_ExternalRefFileIndex::Name(const int Index) const
{
  return theNames->Value(Index);
}

occ::handle<IGESData_IGESEntity> IGESBasic_ExternalRefFileIndex::Entity(const int Index) const
{
  return theEntities->Value(Index);
}
