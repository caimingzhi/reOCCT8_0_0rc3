#pragma once

#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <TDocStd_XLinkPtr.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class TDF_Reference;
class Standard_GUID;
class TDF_AttributeDelta;
class TDF_RelocationTable;

class TDocStd_XLink : public TDF_Attribute
{

public:
  Standard_EXPORT static occ::handle<TDocStd_XLink> Set(const TDF_Label& atLabel);

  Standard_EXPORT TDocStd_XLink();

  Standard_EXPORT occ::handle<TDF_Reference> Update();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT void DocumentEntry(const TCollection_AsciiString& aDocEntry);

  Standard_EXPORT const TCollection_AsciiString& DocumentEntry() const;

  Standard_EXPORT void LabelEntry(const TDF_Label& aLabel);

  Standard_EXPORT void LabelEntry(const TCollection_AsciiString& aLabEntry);

  Standard_EXPORT const TCollection_AsciiString& LabelEntry() const;

  Standard_EXPORT void AfterAddition() override;

  Standard_EXPORT void BeforeRemoval() override;

  Standard_EXPORT bool BeforeUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                  const bool                             forceIt = false) override;

  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                 const bool                             forceIt = false) override;

  Standard_EXPORT occ::handle<TDF_Attribute> BackupCopy() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& anAttribute) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocationTable) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  friend class TDocStd_XLinkRoot;
  friend class TDocStd_XLinkIterator;

  DEFINE_STANDARD_RTTIEXT(TDocStd_XLink, TDF_Attribute)

private:
  void Next(const TDocStd_XLinkPtr& anXLinkPtr);

  TDocStd_XLinkPtr Next() const;

  TCollection_AsciiString myDocEntry;
  TCollection_AsciiString myLabelEntry;
  TDocStd_XLinkPtr        myNext;
};

inline void TDocStd_XLink::Next(const TDocStd_XLinkPtr& anXLinkPtr)
{
  myNext = anXLinkPtr;
}

inline TDocStd_XLinkPtr TDocStd_XLink::Next() const
{
  return myNext;
}
