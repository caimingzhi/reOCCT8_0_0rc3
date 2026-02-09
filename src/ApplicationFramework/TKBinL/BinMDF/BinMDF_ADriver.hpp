#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <NCollection_IndexedMap.hpp>
class Message_Messenger;
class TDF_Attribute;
class BinObjMgt_Persistent;

class BinMDF_ADriver : public Standard_Transient
{

public:
  Standard_EXPORT virtual occ::handle<TDF_Attribute> NewEmpty() const = 0;

  Standard_EXPORT virtual const occ::handle<Standard_Type>& SourceType() const;

  const TCollection_AsciiString& TypeName() const;

  Standard_EXPORT virtual bool Paste(const BinObjMgt_Persistent&       aSource,
                                     const occ::handle<TDF_Attribute>& aTarget,
                                     BinObjMgt_RRelocationTable&       aRelocTable) const = 0;

  Standard_EXPORT virtual void Paste(
    const occ::handle<TDF_Attribute>&                        aSource,
    BinObjMgt_Persistent&                                    aTarget,
    NCollection_IndexedMap<occ::handle<Standard_Transient>>& aRelocTable) const = 0;

  const occ::handle<Message_Messenger>& MessageDriver() const { return myMessageDriver; }

  DEFINE_STANDARD_RTTIEXT(BinMDF_ADriver, Standard_Transient)

protected:
  Standard_EXPORT BinMDF_ADriver(const occ::handle<Message_Messenger>& theMsgDriver,
                                 const char*                           theName = nullptr);

  TCollection_AsciiString myTypeName;

  occ::handle<Message_Messenger> myMessageDriver;
};

#include <TDF_Attribute.hpp>

inline const TCollection_AsciiString& BinMDF_ADriver::TypeName() const
{
  if (myTypeName.Length() == 0)
    (TCollection_AsciiString&)myTypeName += SourceType()->Name();
  return myTypeName;
}
