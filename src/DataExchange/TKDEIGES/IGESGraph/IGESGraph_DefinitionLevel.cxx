#include <IGESGraph_DefinitionLevel.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_DefinitionLevel, IGESData_LevelListEntity)

IGESGraph_DefinitionLevel::IGESGraph_DefinitionLevel() = default;

void IGESGraph_DefinitionLevel::Init(const occ::handle<NCollection_HArray1<int>>& allLevelNumbers)
{
  if (allLevelNumbers->Lower() != 1)
    throw Standard_DimensionMismatch("IGESGraph_DefinitionLevel : Init");
  theLevelNumbers = allLevelNumbers;
  InitTypeAndForm(406, 1);
}

int IGESGraph_DefinitionLevel::NbPropertyValues() const
{
  return (theLevelNumbers->Length());
}

int IGESGraph_DefinitionLevel::NbLevelNumbers() const
{
  return (theLevelNumbers->Length());
}

int IGESGraph_DefinitionLevel::LevelNumber(const int LevelIndex) const
{
  return (theLevelNumbers->Value(LevelIndex));
}
