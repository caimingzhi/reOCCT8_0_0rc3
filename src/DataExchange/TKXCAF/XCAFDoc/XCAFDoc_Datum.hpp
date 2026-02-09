#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_Attribute.hpp>
class TCollection_HAsciiString;
class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;
class XCAFDimTolObjects_DatumObject;

#ifdef GetObject
  #undef GetObject
#endif

class XCAFDoc_Datum : public TDF_Attribute
{

public:
  Standard_EXPORT XCAFDoc_Datum();

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_Datum> Set(
    const TDF_Label&                             label,
    const occ::handle<TCollection_HAsciiString>& aName,
    const occ::handle<TCollection_HAsciiString>& aDescription,
    const occ::handle<TCollection_HAsciiString>& anIdentification);

  Standard_EXPORT static occ::handle<XCAFDoc_Datum> Set(const TDF_Label& theLabel);

  Standard_EXPORT void Set(const occ::handle<TCollection_HAsciiString>& aName,
                           const occ::handle<TCollection_HAsciiString>& aDescription,
                           const occ::handle<TCollection_HAsciiString>& anIdentification);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetDescription() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetIdentification() const;

  Standard_EXPORT occ::handle<XCAFDimTolObjects_DatumObject> GetObject() const;

  Standard_EXPORT void SetObject(const occ::handle<XCAFDimTolObjects_DatumObject>& theDatumObject);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(XCAFDoc_Datum, TDF_Attribute)

private:
  occ::handle<TCollection_HAsciiString> myName;
  occ::handle<TCollection_HAsciiString> myDescription;
  occ::handle<TCollection_HAsciiString> myIdentification;
};
