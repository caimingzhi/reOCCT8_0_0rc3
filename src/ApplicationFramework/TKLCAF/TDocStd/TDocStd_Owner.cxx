#include <TDocStd_Owner.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Data.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDocStd_Document.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDocStd_Owner, TDF_Attribute)

const Standard_GUID& TDocStd_Owner::GetID()
{
  static Standard_GUID TDocStd_OwnerID("2a96b617-ec8b-11d0-bee7-080009dc3333");
  return TDocStd_OwnerID;
}

void TDocStd_Owner::SetDocument(const occ::handle<TDF_Data>&         indata,
                                const occ::handle<TDocStd_Document>& doc)
{
  occ::handle<TDocStd_Owner> A;
  if (!indata->Root().FindAttribute(TDocStd_Owner::GetID(), A))
  {
    A = new TDocStd_Owner();
    A->SetDocument(doc);
    indata->Root().AddAttribute(A);
  }
  else
  {
    throw Standard_DomainError("TDocStd_Owner::SetDocument : already called");
  }
}

void TDocStd_Owner::SetDocument(const occ::handle<TDF_Data>& indata, TDocStd_Document* doc)
{
  occ::handle<TDocStd_Owner> A;
  if (!indata->Root().FindAttribute(TDocStd_Owner::GetID(), A))
  {
    A = new TDocStd_Owner();
    A->SetDocument(doc);
    indata->Root().AddAttribute(A);
  }
  else
  {
    throw Standard_DomainError("TDocStd_Owner::SetDocument : already called");
  }
}

occ::handle<TDocStd_Document> TDocStd_Owner::GetDocument(const occ::handle<TDF_Data>& ofdata)
{
  occ::handle<TDocStd_Owner> A;
  if (!ofdata->Root().FindAttribute(TDocStd_Owner::GetID(), A))
  {
    throw Standard_DomainError("TDocStd_Owner::GetDocument : document not found");
  }
  return A->GetDocument();
}

TDocStd_Owner::TDocStd_Owner() = default;

void TDocStd_Owner::SetDocument(const occ::handle<TDocStd_Document>& document)
{
  myDocument = document.get();
}

void TDocStd_Owner::SetDocument(TDocStd_Document* document)
{
  myDocument = document;
}

occ::handle<TDocStd_Document> TDocStd_Owner::GetDocument() const
{
  return occ::handle<TDocStd_Document>(myDocument);
}

const Standard_GUID& TDocStd_Owner::ID() const
{
  return GetID();
}

occ::handle<TDF_Attribute> TDocStd_Owner::NewEmpty() const
{
  occ::handle<TDF_Attribute> dummy;
  return dummy;
}

void TDocStd_Owner::Restore(const occ::handle<TDF_Attribute>&) {}

void TDocStd_Owner::Paste(const occ::handle<TDF_Attribute>&,
                          const occ::handle<TDF_RelocationTable>&) const
{
}

Standard_OStream& TDocStd_Owner::Dump(Standard_OStream& anOS) const
{
  anOS << "Owner";
  return anOS;
}

void TDocStd_Owner::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myDocument)
}
