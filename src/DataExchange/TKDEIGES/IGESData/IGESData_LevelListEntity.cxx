

#include <IGESData_LevelListEntity.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_LevelListEntity, IGESData_IGESEntity)

bool IGESData_LevelListEntity::HasLevelNumber(const int level) const
{
  int nb = NbLevelNumbers();
  for (int i = 1; i <= nb; i++)
  {
    if (LevelNumber(i) == level)
      return true;
  }
  return false;
}
