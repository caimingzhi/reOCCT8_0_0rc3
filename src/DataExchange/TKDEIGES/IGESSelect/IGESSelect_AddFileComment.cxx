#include <IFSelect_ContextWrite.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESSelect_AddFileComment.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_AddFileComment, IGESSelect_FileModifier)

IGESSelect_AddFileComment::IGESSelect_AddFileComment()
{
  thelist = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
}

void IGESSelect_AddFileComment::Clear()
{
  thelist->Clear();
}

void IGESSelect_AddFileComment::AddLine(const char* line)
{
  thelist->Append(new TCollection_HAsciiString(line));
}

void IGESSelect_AddFileComment::AddLines(
  const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& lines)
{
  thelist->Append(lines);
}

int IGESSelect_AddFileComment::NbLines() const
{
  return thelist->Length();
}

const char* IGESSelect_AddFileComment::Line(const int num) const
{
  return thelist->Value(num)->ToCString();
}

occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
  IGESSelect_AddFileComment::Lines() const
{
  return thelist;
}

void IGESSelect_AddFileComment::Perform(IFSelect_ContextWrite&, IGESData_IGESWriter& writer) const
{
  int i, nb = NbLines();
  for (i = 1; i <= nb; i++)
  {
    writer.SendStartLine(Line(i));
  }
}

TCollection_AsciiString IGESSelect_AddFileComment::Label() const
{
  int  nb = NbLines();
  char labl[80];
  Sprintf(labl, "Add %d Comment Lines (Start Section)", nb);
  return TCollection_AsciiString(labl);
}
