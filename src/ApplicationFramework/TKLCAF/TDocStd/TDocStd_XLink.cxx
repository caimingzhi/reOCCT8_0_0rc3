#include <TDocStd_XLink.hpp>

#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_AttributeDelta.hpp>
#include <TDF_DeltaOnAddition.hpp>
#include <TDF_DeltaOnRemoval.hpp>
#include <TDF_Label.hpp>
#include <TDF_Reference.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_Tool.hpp>
#include <TDocStd.hpp>
#include <TDocStd_Document.hpp>
#include <TDocStd_XLinkRoot.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDocStd_XLink, TDF_Attribute)

TDocStd_XLink::TDocStd_XLink()
    : myNext(nullptr)
{
}

occ::handle<TDocStd_XLink> TDocStd_XLink::Set(const TDF_Label& atLabel)
{
  occ::handle<TDocStd_XLink> xRef;
  if (!atLabel.FindAttribute(TDocStd_XLink::GetID(), xRef))
  {
    xRef = new TDocStd_XLink;
    atLabel.AddAttribute(xRef);
  }
  return xRef;
}

occ::handle<TDF_Reference> TDocStd_XLink::Update()
{
  TDF_Label                     reflabel;
  occ::handle<TDocStd_Document> refdoc;
  int                           IEntry = myDocEntry.IntegerValue();
  occ::handle<TDocStd_Document> mydoc  = TDocStd_Document::Get(Label());
  refdoc                               = occ::down_cast<TDocStd_Document>(mydoc->Document(IEntry));
  TDF_Tool::Label(refdoc->GetData(), myLabelEntry, reflabel);

  return TDF_Reference::Set(Label(), reflabel);
}

const Standard_GUID& TDocStd_XLink::ID() const
{
  return GetID();
}

const Standard_GUID& TDocStd_XLink::GetID()
{
  static Standard_GUID myID("5d587400-5690-11d1-8940-080009dc3333");
  return myID;
}

void TDocStd_XLink::DocumentEntry(const TCollection_AsciiString& aDocEntry)
{
  Backup();
  myDocEntry = aDocEntry;
}

const TCollection_AsciiString& TDocStd_XLink::DocumentEntry() const
{
  return myDocEntry;
}

void TDocStd_XLink::LabelEntry(const TDF_Label& aLabel)
{
  Backup();
  TDF_Tool::Entry(aLabel, myLabelEntry);
}

void TDocStd_XLink::LabelEntry(const TCollection_AsciiString& aLabEntry)
{
  Backup();
  myLabelEntry = aLabEntry;
}

const TCollection_AsciiString& TDocStd_XLink::LabelEntry() const
{
  return myLabelEntry;
}

void TDocStd_XLink::AfterAddition()
{
  TDocStd_XLinkRoot::Insert(this);
  Label().Imported(true);
}

void TDocStd_XLink::BeforeRemoval()
{
  if (!IsBackuped())
  {
    TDocStd_XLinkRoot::Remove(this);
    Label().Imported(false);
  }
}

bool TDocStd_XLink::BeforeUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta, const bool)
{
  if (anAttDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition)))
  {
    anAttDelta->Attribute()->BeforeRemoval();
  }
  return true;
}

bool TDocStd_XLink::AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta, const bool)
{
  if (anAttDelta->IsKind(STANDARD_TYPE(TDF_DeltaOnRemoval)))
  {
    anAttDelta->Attribute()->AfterAddition();
  }
  return true;
}

occ::handle<TDF_Attribute> TDocStd_XLink::BackupCopy() const
{
  occ::handle<TDocStd_XLink> xRef = new TDocStd_XLink();
  xRef->DocumentEntry(myDocEntry);
  xRef->LabelEntry(myLabelEntry);
  return xRef;
}

void TDocStd_XLink::Restore(const occ::handle<TDF_Attribute>& anAttribute)
{
  occ::handle<TDocStd_XLink> xRef(occ::down_cast<TDocStd_XLink>(anAttribute));
  if (!xRef.IsNull())
  {
    myDocEntry   = xRef->DocumentEntry();
    myLabelEntry = xRef->LabelEntry();
  }
}

occ::handle<TDF_Attribute> TDocStd_XLink::NewEmpty() const
{
  return new TDocStd_XLink();
}

void TDocStd_XLink::Paste(const occ::handle<TDF_Attribute>& intoAttribute,
                          const occ::handle<TDF_RelocationTable>&) const
{
  occ::handle<TDocStd_XLink> xRef(occ::down_cast<TDocStd_XLink>(intoAttribute));
  if (!xRef.IsNull())
  {
    xRef->DocumentEntry(myDocEntry);
    xRef->LabelEntry(myLabelEntry);
  }
}

Standard_OStream& TDocStd_XLink::Dump(Standard_OStream& anOS) const
{
  return anOS;
}
