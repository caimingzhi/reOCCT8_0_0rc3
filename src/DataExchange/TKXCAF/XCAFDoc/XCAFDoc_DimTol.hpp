#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TDF_Attribute.hpp>
class TCollection_HAsciiString;
class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;

//! attribute to store dimension and tolerance
class XCAFDoc_DimTol : public TDF_Attribute
{

public:
  Standard_EXPORT XCAFDoc_DimTol();

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_DimTol> Set(
    const TDF_Label&                                label,
    const int                                       kind,
    const occ::handle<NCollection_HArray1<double>>& aVal,
    const occ::handle<TCollection_HAsciiString>&    aName,
    const occ::handle<TCollection_HAsciiString>&    aDescription);

  Standard_EXPORT void Set(const int                                       kind,
                           const occ::handle<NCollection_HArray1<double>>& aVal,
                           const occ::handle<TCollection_HAsciiString>&    aName,
                           const occ::handle<TCollection_HAsciiString>&    aDescription);

  Standard_EXPORT int GetKind() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> GetVal() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetDescription() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(XCAFDoc_DimTol, TDF_Attribute)

private:
  int                                      myKind;
  occ::handle<NCollection_HArray1<double>> myVal;
  occ::handle<TCollection_HAsciiString>    myName;
  occ::handle<TCollection_HAsciiString>    myDescription;
};
