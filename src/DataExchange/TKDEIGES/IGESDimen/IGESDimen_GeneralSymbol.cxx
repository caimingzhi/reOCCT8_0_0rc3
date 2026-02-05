#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_GeneralSymbol.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_GeneralSymbol, IGESData_IGESEntity)

IGESDimen_GeneralSymbol::IGESDimen_GeneralSymbol() = default;

void IGESDimen_GeneralSymbol::Init(
  const occ::handle<IGESDimen_GeneralNote>&                                   aNote,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&   allGeoms,
  const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>& allLeaders)
{
  if (!allGeoms.IsNull() && allGeoms->Lower() != 1)
    throw Standard_DimensionMismatch("IGESDimen_GeneralSymbol : Init");
  if (!allLeaders.IsNull())
    if (allLeaders->Lower() != 1)
      throw Standard_DimensionMismatch("$");
  theNote    = aNote;
  theGeoms   = allGeoms;
  theLeaders = allLeaders;
  InitTypeAndForm(228, FormNumber());
  //  FormNumber specifies the Nature of the Symbol, see G.14 (0-3 or > 5000)
}

void IGESDimen_GeneralSymbol::SetFormNumber(const int form)
{
  if ((form < 0 || form > 3) && form < 5000)
    throw Standard_OutOfRange("IGESDimen_GeneralSymbol : SetFormNumber");
  InitTypeAndForm(228, form);
}

bool IGESDimen_GeneralSymbol::HasNote() const
{
  return (!theNote.IsNull());
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_GeneralSymbol::Note() const
{
  return theNote;
}

int IGESDimen_GeneralSymbol::NbGeomEntities() const
{
  return theGeoms->Length();
}

occ::handle<IGESData_IGESEntity> IGESDimen_GeneralSymbol::GeomEntity(const int Index) const
{
  return theGeoms->Value(Index);
}

int IGESDimen_GeneralSymbol::NbLeaders() const
{
  return (theLeaders.IsNull() ? 0 : theLeaders->Length());
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_GeneralSymbol::LeaderArrow(const int Index) const
{
  return theLeaders->Value(Index);
}
