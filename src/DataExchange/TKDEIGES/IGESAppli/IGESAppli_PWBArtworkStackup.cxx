#include <IGESAppli_PWBArtworkStackup.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_PWBArtworkStackup, IGESData_IGESEntity)

IGESAppli_PWBArtworkStackup::IGESAppli_PWBArtworkStackup() = default;

void IGESAppli_PWBArtworkStackup::Init(const int                                    nbPropVal,
                                       const occ::handle<TCollection_HAsciiString>& anArtIdent,
                                       const occ::handle<NCollection_HArray1<int>>& allLevelNums)
{
  if (allLevelNums->Lower() != 1)
    throw Standard_DimensionMismatch("IGESAppli_PWBArtworkStackup : Init");
  theNbPropertyValues    = nbPropVal;
  theArtworkStackupIdent = anArtIdent;
  theLevelNumbers        = allLevelNums;
  InitTypeAndForm(406, 25);
}

int IGESAppli_PWBArtworkStackup::NbPropertyValues() const
{
  return theNbPropertyValues;
}

occ::handle<TCollection_HAsciiString> IGESAppli_PWBArtworkStackup::Identification() const
{
  return theArtworkStackupIdent;
}

int IGESAppli_PWBArtworkStackup::NbLevelNumbers() const
{
  return theLevelNumbers->Length();
}

int IGESAppli_PWBArtworkStackup::LevelNumber(const int Index) const
{
  return theLevelNumbers->Value(Index);
}
