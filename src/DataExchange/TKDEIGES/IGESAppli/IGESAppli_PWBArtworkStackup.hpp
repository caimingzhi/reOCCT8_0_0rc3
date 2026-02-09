#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESAppli_PWBArtworkStackup : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_PWBArtworkStackup();

  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& anArtIdent,
                            const occ::handle<NCollection_HArray1<int>>& allLevelNums);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Identification() const;

  Standard_EXPORT int NbLevelNumbers() const;

  Standard_EXPORT int LevelNumber(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_PWBArtworkStackup, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> theArtworkStackupIdent;
  occ::handle<NCollection_HArray1<int>> theLevelNumbers;
};
