#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <NCollection_IndexedMap.hpp>
class Message_Messenger;
class TDF_Attribute;
class BinObjMgt_Persistent;

//! Attribute Storage/Retrieval Driver.
class BinMDF_ADriver : public Standard_Transient
{

public:
  //! Creates a new attribute from TDF.
  Standard_EXPORT virtual occ::handle<TDF_Attribute> NewEmpty() const = 0;

  //! Returns the type of source object,
  //! inheriting from Attribute from TDF.
  Standard_EXPORT virtual const occ::handle<Standard_Type>& SourceType() const;

  //! Returns the type name of the attribute object
  const TCollection_AsciiString& TypeName() const;

  //! Translate the contents of <aSource> and put it
  //! into <aTarget>, using the relocation table
  //! <aRelocTable> to keep the sharings.
  Standard_EXPORT virtual bool Paste(const BinObjMgt_Persistent&       aSource,
                                     const occ::handle<TDF_Attribute>& aTarget,
                                     BinObjMgt_RRelocationTable&       aRelocTable) const = 0;

  //! Translate the contents of <aSource> and put it
  //! into <aTarget>, using the relocation table
  //! <aRelocTable> to keep the sharings.
  Standard_EXPORT virtual void Paste(
    const occ::handle<TDF_Attribute>&                        aSource,
    BinObjMgt_Persistent&                                    aTarget,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& aRelocTable) const = 0;

  //! Returns the current message driver of this driver
  const occ::handle<Message_Messenger>& MessageDriver() const { return myMessageDriver; }

  DEFINE_STANDARD_RTTIEXT(BinMDF_ADriver, Standard_Transient)

protected:
  Standard_EXPORT BinMDF_ADriver(const occ::handle<Message_Messenger>& theMsgDriver,
                                 const char*                           theName = nullptr);

  TCollection_AsciiString myTypeName;

  occ::handle<Message_Messenger> myMessageDriver;
};

#include <TDF_Attribute.hpp>

//=================================================================================================

inline const TCollection_AsciiString& BinMDF_ADriver::TypeName() const
{
  if (myTypeName.Length() == 0)
    (TCollection_AsciiString&)myTypeName += SourceType()->Name();
  return myTypeName;
}
