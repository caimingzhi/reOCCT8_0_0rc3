#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>
class Message_Messenger;
class TDF_Attribute;
class XmlObjMgt_Persistent;

class XmlMDF_ADriver : public Standard_Transient
{

public:
  Standard_EXPORT virtual int VersionNumber() const;

  Standard_EXPORT virtual occ::handle<TDF_Attribute> NewEmpty() const = 0;

  Standard_EXPORT virtual occ::handle<Standard_Type> SourceType() const;

  Standard_EXPORT const TCollection_AsciiString& TypeName() const;

  const TCollection_AsciiString& Namespace() const { return myNamespace; }

  Standard_EXPORT virtual bool Paste(const XmlObjMgt_Persistent&       aSource,
                                     const occ::handle<TDF_Attribute>& aTarget,
                                     XmlObjMgt_RRelocationTable&       aRelocTable) const = 0;

  Standard_EXPORT virtual void Paste(const occ::handle<TDF_Attribute>& aSource,
                                     XmlObjMgt_Persistent&             aTarget,
                                     XmlObjMgt_SRelocationTable&       aRelocTable) const = 0;

  const occ::handle<Message_Messenger>& MessageDriver() const { return myMessageDriver; }

  DEFINE_STANDARD_RTTIEXT(XmlMDF_ADriver, Standard_Transient)

protected:
  Standard_EXPORT XmlMDF_ADriver(const occ::handle<Message_Messenger>& theMessageDriver,
                                 const char*                           theNamespace,
                                 const char*                           theName = nullptr);

  TCollection_AsciiString        myTypeName;
  TCollection_AsciiString        myNamespace;
  occ::handle<Message_Messenger> myMessageDriver;

private:
  friend class XmlMDF;
};
