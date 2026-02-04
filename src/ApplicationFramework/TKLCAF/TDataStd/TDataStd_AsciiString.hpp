#pragma once


#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;

//! Used to define an AsciiString attribute containing a TCollection_AsciiString
class TDataStd_AsciiString : public TDF_Attribute
{

public:
  //! class methods
  //! =============
  //! Returns the GUID of the attribute.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds, or creates an AsciiString attribute and sets the string.
  //! the AsciiString attribute is returned.
  //! AsciiString methods
  //! ===================
  Standard_EXPORT static occ::handle<TDataStd_AsciiString> Set(
    const TDF_Label&               label,
    const TCollection_AsciiString& string);

  //! Finds, or creates, an AsciiString attribute with explicit user defined <guid> and sets
  //! <string>. The Name attribute is returned.
  Standard_EXPORT static occ::handle<TDataStd_AsciiString> Set(
    const TDF_Label&               label,
    const Standard_GUID&           guid,
    const TCollection_AsciiString& string);

  Standard_EXPORT TDataStd_AsciiString();

  Standard_EXPORT void Set(const TCollection_AsciiString& S);

  //! Sets the explicit user defined GUID to the attribute.
  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  //! Sets default GUID for the attribute.
  Standard_EXPORT void SetID() override;

  Standard_EXPORT const TCollection_AsciiString& Get() const;

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_AsciiString, TDF_Attribute)

private:
  TCollection_AsciiString myString;
  Standard_GUID           myID;
};

