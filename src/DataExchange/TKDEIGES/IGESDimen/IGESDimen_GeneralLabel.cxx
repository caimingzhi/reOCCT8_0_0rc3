#include <IGESDimen_GeneralLabel.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_GeneralLabel, IGESData_IGESEntity)

IGESDimen_GeneralLabel::IGESDimen_GeneralLabel() = default;

void IGESDimen_GeneralLabel::Init(
  const occ::handle<IGESDimen_GeneralNote>&                                   aNote,
  const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>& someLeaders)
{
  if (someLeaders->Lower() != 1)
    throw Standard_DimensionMismatch("IGESDimen_GeneralLabel : Init");
  theNote    = aNote;
  theLeaders = someLeaders;
  InitTypeAndForm(210, 0);
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_GeneralLabel::Note() const
{
  return theNote;
}

int IGESDimen_GeneralLabel::NbLeaders() const
{
  return theLeaders->Length();
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_GeneralLabel::Leader(const int Index) const
{
  return theLeaders->Value(Index);
}
