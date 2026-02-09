#include <TDataStd_NoteBook.hpp>

#include <Standard_DomainError.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_Real.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_TagSource.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(TDataStd_NoteBook, TDataStd_GenericEmpty)

bool TDataStd_NoteBook::Find(const TDF_Label& current, occ::handle<TDataStd_NoteBook>& N)
{
  TDF_Label                      L = current;
  occ::handle<TDataStd_NoteBook> NB;
  if (L.IsNull())
    return false;

  for (;;)
  {
    if (L.FindAttribute(TDataStd_NoteBook::GetID(), NB))
      break;
    L = L.Father();
    if (L.IsNull())
      break;
  }

  if (!NB.IsNull())
  {
    N = NB;
    return true;
  }
  return false;
}

occ::handle<TDataStd_NoteBook> TDataStd_NoteBook::New(const TDF_Label& label)
{
  if (label.HasAttribute())
  {
    throw Standard_DomainError("TDataStd_NoteBook::New : not an empty label");
  }
  occ::handle<TDataStd_NoteBook> NB = new TDataStd_NoteBook();
  label.AddAttribute(NB);
  TDF_TagSource::Set(label);
  return NB;
}

const Standard_GUID& TDataStd_NoteBook::GetID()
{
  static Standard_GUID TDataStd_NoteBookID("2a96b609-ec8b-11d0-bee7-080009dc3333");
  return TDataStd_NoteBookID;
}

TDataStd_NoteBook::TDataStd_NoteBook() = default;

occ::handle<TDataStd_Real> TDataStd_NoteBook::Append(const double value, const bool)
{
  TDF_Label                  newlabel = TDF_TagSource::NewChild(Label());
  occ::handle<TDataStd_Real> variable = TDataStd_Real::Set(newlabel, value);
  return variable;
}

occ::handle<TDataStd_Integer> TDataStd_NoteBook::Append(const int value, const bool)
{
  TDF_Label                     newlabel = TDF_TagSource::NewChild(Label());
  occ::handle<TDataStd_Integer> variable = TDataStd_Integer::Set(newlabel, value);
  return variable;
}

const Standard_GUID& TDataStd_NoteBook::ID() const
{
  return GetID();
}

Standard_OStream& TDataStd_NoteBook::Dump(Standard_OStream& anOS) const
{
  anOS << "NoteBook";
  return anOS;
}
