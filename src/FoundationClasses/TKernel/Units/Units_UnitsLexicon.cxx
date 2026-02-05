#include <Units_UnitsLexicon.hpp>

#include <OSD_OpenFile.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Units.hpp>
#include <Units_Token.hpp>
#include <Units_UnitsDictionary.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Units_UnitsLexicon, Units_Lexicon)

//=================================================================================================

Units_UnitsLexicon::Units_UnitsLexicon()

  = default;

//=================================================================================================

void Units_UnitsLexicon::Creates(const bool amode)
{
  occ::handle<Units_UnitsDictionary> unitsdictionary;

  Units_Lexicon::Creates();

  if (amode)
    unitsdictionary = Units::DictionaryOfUnits(amode);
}
