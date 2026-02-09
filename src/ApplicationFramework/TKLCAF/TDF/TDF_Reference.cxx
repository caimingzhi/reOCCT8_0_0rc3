#include <TDF_Reference.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_Reference, TDF_Attribute)

const Standard_GUID& TDF_Reference::GetID()
{
  static Standard_GUID TDF_ReferenceID("2a96b610-ec8b-11d0-bee7-080009dc3333");
  return TDF_ReferenceID;
}

occ::handle<TDF_Reference> TDF_Reference::Set(const TDF_Label& L, const TDF_Label& Origin)
{
  occ::handle<TDF_Reference> A;
  if (!L.FindAttribute(TDF_Reference::GetID(), A))
  {
    A = new TDF_Reference();
    L.AddAttribute(A);
  }
  A->Set(Origin);
  return A;
}

TDF_Reference::TDF_Reference() = default;

void TDF_Reference::Set(const TDF_Label& Origin)
{

  if (myOrigin == Origin)
    return;

  Backup();
  myOrigin = Origin;
}

TDF_Label TDF_Reference::Get() const
{
  return myOrigin;
}

const Standard_GUID& TDF_Reference::ID() const
{
  return GetID();
}

occ::handle<TDF_Attribute> TDF_Reference::NewEmpty() const
{
  return new TDF_Reference();
}

void TDF_Reference::Restore(const occ::handle<TDF_Attribute>& With)
{
  myOrigin = occ::down_cast<TDF_Reference>(With)->Get();
}

void TDF_Reference::Paste(const occ::handle<TDF_Attribute>&       Into,
                          const occ::handle<TDF_RelocationTable>& RT) const
{
  TDF_Label tLab;
  if (!myOrigin.IsNull())
  {
    if (!RT->HasRelocation(myOrigin, tLab))
      tLab = myOrigin;
  }
  occ::down_cast<TDF_Reference>(Into)->Set(tLab);
}

void TDF_Reference::References(const occ::handle<TDF_DataSet>& aDataSet) const
{

  if (!Label().IsImported())
    aDataSet->AddLabel(myOrigin);
}

Standard_OStream& TDF_Reference::Dump(Standard_OStream& anOS) const
{
  anOS << "Reference";
  return anOS;
}

void TDF_Reference::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  TCollection_AsciiString aLabel;
  TDF_Tool::Entry(myOrigin, aLabel);
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, aLabel)
}
