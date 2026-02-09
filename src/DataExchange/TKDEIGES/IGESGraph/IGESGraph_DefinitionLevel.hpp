#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_LevelListEntity.hpp>

class IGESGraph_DefinitionLevel : public IGESData_LevelListEntity
{

public:
  Standard_EXPORT IGESGraph_DefinitionLevel();

  Standard_EXPORT void Init(const occ::handle<NCollection_HArray1<int>>& allLevelNumbers);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int NbLevelNumbers() const override;

  Standard_EXPORT int LevelNumber(const int LevelIndex) const override;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_DefinitionLevel, IGESData_LevelListEntity)

private:
  occ::handle<NCollection_HArray1<int>> theLevelNumbers;
};
