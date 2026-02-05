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

//! Attribute Storage/Retrieval Driver.
class XmlMDF_ADriver : public Standard_Transient
{

public:
  //! Returns the version number from which the driver
  //! is available.
  Standard_EXPORT virtual int VersionNumber() const;

  //! Creates a new attribute from TDF.
  Standard_EXPORT virtual occ::handle<TDF_Attribute> NewEmpty() const = 0;

  //! Returns the type of source object,
  //! inheriting from Attribute from TDF.
  Standard_EXPORT virtual occ::handle<Standard_Type> SourceType() const;

  //! Returns the full XML tag name (including NS prefix)
  Standard_EXPORT const TCollection_AsciiString& TypeName() const;

  //! Returns the namespace string
  const TCollection_AsciiString& Namespace() const { return myNamespace; }

  //! Translate the contents of <aSource> and put it
  //! into <aTarget>, using the relocation table
  //! <aRelocTable> to keep the sharings.
  Standard_EXPORT virtual bool Paste(const XmlObjMgt_Persistent&       aSource,
                                     const occ::handle<TDF_Attribute>& aTarget,
                                     XmlObjMgt_RRelocationTable&       aRelocTable) const = 0;

  //! Translate the contents of <aSource> and put it
  //! into <aTarget>, using the relocation table
  //! <aRelocTable> to keep the sharings.
  Standard_EXPORT virtual void Paste(const occ::handle<TDF_Attribute>& aSource,
                                     XmlObjMgt_Persistent&             aTarget,
                                     XmlObjMgt_SRelocationTable&       aRelocTable) const = 0;

  //! Returns the current message driver of this driver
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
