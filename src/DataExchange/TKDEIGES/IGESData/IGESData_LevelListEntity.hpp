#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>

class IGESData_LevelListEntity : public IGESData_IGESEntity
{

public:
  Standard_EXPORT virtual int NbLevelNumbers() const = 0;

  Standard_EXPORT virtual int LevelNumber(const int num) const = 0;

  Standard_EXPORT bool HasLevelNumber(const int level) const;

  DEFINE_STANDARD_RTTIEXT(IGESData_LevelListEntity, IGESData_IGESEntity)
};
