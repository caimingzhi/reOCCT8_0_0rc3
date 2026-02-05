#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_LevelListEntity.hpp>

//! defines IGESDefinitionLevel, Type <406> Form <1>
//! in package IGESGraph
//!
//! Indicates the no. of levels on which an entity is
//! defined
class IGESGraph_DefinitionLevel : public IGESData_LevelListEntity
{

public:
  Standard_EXPORT IGESGraph_DefinitionLevel();

  //! This method is used to set the fields of the class
  //! DefinitionLevel
  //! - allLevelNumbers : Values of Level Numbers
  Standard_EXPORT void Init(const occ::handle<NCollection_HArray1<int>>& allLevelNumbers);

  //! returns the number of property values in <me>
  Standard_EXPORT int NbPropertyValues() const;

  //! Must return the count of levels (== NbPropertyValues)
  Standard_EXPORT int NbLevelNumbers() const override;

  //! returns the Level Number of <me> indicated by <LevelIndex>
  //! raises an exception if LevelIndex is <= 0 or
  //! LevelIndex > NbPropertyValues
  Standard_EXPORT int LevelNumber(const int LevelIndex) const override;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_DefinitionLevel, IGESData_LevelListEntity)

private:
  occ::handle<NCollection_HArray1<int>> theLevelNumbers;
};
