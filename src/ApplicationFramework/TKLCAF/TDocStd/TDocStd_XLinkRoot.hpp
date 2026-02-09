#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDocStd_XLinkPtr.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Data;
class TDF_RelocationTable;

class TDocStd_XLinkRoot : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDocStd_XLinkRoot> Set(const occ::handle<TDF_Data>& aDF);

  Standard_EXPORT static void Insert(const TDocStd_XLinkPtr& anXLinkPtr);

  Standard_EXPORT static void Remove(const TDocStd_XLinkPtr& anXLinkPtr);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT occ::handle<TDF_Attribute> BackupCopy() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& anAttribute) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocationTable) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  friend class TDocStd_XLinkIterator;

  DEFINE_STANDARD_RTTIEXT(TDocStd_XLinkRoot, TDF_Attribute)

private:
  Standard_EXPORT TDocStd_XLinkRoot();

  void First(const TDocStd_XLinkPtr& anXLinkPtr);

  TDocStd_XLinkPtr First() const;

  TDocStd_XLinkPtr myFirst;
};

inline void TDocStd_XLinkRoot::First(const TDocStd_XLinkPtr& anXLinkPtr)
{
  myFirst = anXLinkPtr;
}

inline TDocStd_XLinkPtr TDocStd_XLinkRoot::First() const
{
  return myFirst;
}
