#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDocStd_XLinkPtr.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Data;
class TDF_RelocationTable;

//! This attribute is the root of all external
//! references contained in a Data from TDF. Only one
//! instance of this class is added to the TDF_Data
//! root label. Starting from this attribute all the
//! Reference are linked together, to be found easily.
class TDocStd_XLinkRoot : public TDF_Attribute
{

public:
  //! Returns the ID: 2a96b61d-ec8b-11d0-bee7-080009dc3333
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Sets an empty XLinkRoot to Root or gets the
  //! existing one. Only one attribute per TDF_Data.
  Standard_EXPORT static occ::handle<TDocStd_XLinkRoot> Set(const occ::handle<TDF_Data>& aDF);

  //! Inserts <anXLinkPtr> at the beginning of the XLink chain.
  Standard_EXPORT static void Insert(const TDocStd_XLinkPtr& anXLinkPtr);

  //! Removes <anXLinkPtr> from the XLink chain, if it exists.
  Standard_EXPORT static void Remove(const TDocStd_XLinkPtr& anXLinkPtr);

  //! Returns the ID of the attribute.
  Standard_EXPORT const Standard_GUID& ID() const override;

  //! Returns a null handle.
  Standard_EXPORT occ::handle<TDF_Attribute> BackupCopy() const override;

  //! Does nothing.
  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& anAttribute) override;

  //! Returns a null handle.
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  //! Does nothing.
  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocationTable) const override;

  //! Dumps the attribute on <aStream>.
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  friend class TDocStd_XLinkIterator;

  DEFINE_STANDARD_RTTIEXT(TDocStd_XLinkRoot, TDF_Attribute)

private:
  //! Initializes fields.
  Standard_EXPORT TDocStd_XLinkRoot();

  //! Sets the field <myFirst> with <anXLinkPtr>.
  void First(const TDocStd_XLinkPtr& anXLinkPtr);

  //! Returns the contents of the field <myFirst>.
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
