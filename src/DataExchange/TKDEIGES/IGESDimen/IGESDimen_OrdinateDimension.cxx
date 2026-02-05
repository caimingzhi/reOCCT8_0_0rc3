#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_OrdinateDimension.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_OrdinateDimension, IGESData_IGESEntity)

IGESDimen_OrdinateDimension::IGESDimen_OrdinateDimension() = default;

void IGESDimen_OrdinateDimension::Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                                       const bool                                isLine,
                                       const occ::handle<IGESDimen_WitnessLine>& aLine,
                                       const occ::handle<IGESDimen_LeaderArrow>& anArrow)
{
  theNote        = aNote;
  isItLine       = isLine;
  theWitnessLine = aLine;
  theLeader      = anArrow;
  if ((aLine.IsNull()) || (anArrow.IsNull()))
    InitTypeAndForm(218, 0);
  else
    InitTypeAndForm(218, 1);
}

occ::handle<IGESDimen_GeneralNote> IGESDimen_OrdinateDimension::Note() const
{
  return theNote;
}

occ::handle<IGESDimen_WitnessLine> IGESDimen_OrdinateDimension::WitnessLine() const
{
  return theWitnessLine;
}

occ::handle<IGESDimen_LeaderArrow> IGESDimen_OrdinateDimension::Leader() const
{
  return theLeader;
}

bool IGESDimen_OrdinateDimension::IsLine() const
{
  return isItLine;
}

bool IGESDimen_OrdinateDimension::IsLeader() const
{
  return !isItLine;
}
