#pragma once


#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>

//! defines required type for LevelList in directory part
//! an effective LevelList entity must inherits it
class IGESData_LevelListEntity : public IGESData_IGESEntity
{

public:
  //! Must return the count of levels
  Standard_EXPORT virtual int NbLevelNumbers() const = 0;

  //! returns the Level Number of <me>, indicated by <num>
  //! raises an exception if num is out of range
  Standard_EXPORT virtual int LevelNumber(const int num) const = 0;

  //! returns True if <level> is in the list
  Standard_EXPORT bool HasLevelNumber(const int level) const;

  DEFINE_STANDARD_RTTIEXT(IGESData_LevelListEntity, IGESData_IGESEntity)
};

