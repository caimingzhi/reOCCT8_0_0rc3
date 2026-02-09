#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TDF_DerivedAttribute.hpp>

#include <TCollection_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;

class XCAFDoc_LengthUnit : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_LengthUnit> Set(
    const TDF_Label&               theLabel,
    const TCollection_AsciiString& theUnitName,
    const double                   theUnitValue);

  Standard_EXPORT static occ::handle<XCAFDoc_LengthUnit> Set(const TDF_Label& theLabel,
                                                             const double     theUnitValue);

  Standard_EXPORT static occ::handle<XCAFDoc_LengthUnit> Set(
    const TDF_Label&               theLabel,
    const Standard_GUID&           theGUID,
    const TCollection_AsciiString& theUnitName,
    const double                   theUnitValue);

  Standard_EXPORT void Set(const TCollection_AsciiString& theUnitName, const double theUnitValue);

  const TCollection_AsciiString& GetUnitName() const { return myUnitName; }

  double GetUnitValue() const { return myUnitScaleValue; }

  Standard_EXPORT bool IsEmpty() const { return myUnitName.IsEmpty(); }

  Standard_EXPORT XCAFDoc_LengthUnit();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_LengthUnit, TDF_Attribute)

private:
  double                  myUnitScaleValue;
  TCollection_AsciiString myUnitName;
};
