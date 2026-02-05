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

//! Used to define a Length Unit attribute containing a length unit info
class XCAFDoc_LengthUnit : public TDF_Attribute
{

public:
  //! Returns the GUID of the attribute.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds or creates a LengthUnit attribute
  //! @param theUnitName - name of the unit: mm, m, cm, km, micron, in, min, nin, ft, stat.mile
  //! @param theUnitValue - length scale factor to meter
  //! The LengthUnit attribute is returned.
  Standard_EXPORT static occ::handle<XCAFDoc_LengthUnit> Set(
    const TDF_Label&               theLabel,
    const TCollection_AsciiString& theUnitName,
    const double                   theUnitValue);

  //! Finds or creates a LengthUnit attribute
  //! @param theUnitValue - length scale factor to meter
  //! The LengthUnit attribute is returned.
  Standard_EXPORT static occ::handle<XCAFDoc_LengthUnit> Set(const TDF_Label& theLabel,
                                                             const double     theUnitValue);

  //! Finds, or creates, a LengthUnit attribute with explicit user defined GUID
  //! @param theUnitName - name of the unit: mm, m, cm, km, micron, in, min, nin, ft, stat.mile
  //! @param theUnitValue - length scale factor to meter
  //! The LengthUnit attribute is returned
  Standard_EXPORT static occ::handle<XCAFDoc_LengthUnit> Set(
    const TDF_Label&               theLabel,
    const Standard_GUID&           theGUID,
    const TCollection_AsciiString& theUnitName,
    const double                   theUnitValue);

  //! Creates a LengthUnit attribute
  //! @param theUnitName - name of the unit: mm, m, cm, km, micron, in, min, nin, ft, stat.mile
  //! @param theUnitValue - length scale factor to meter
  Standard_EXPORT void Set(const TCollection_AsciiString& theUnitName, const double theUnitValue);

  //! Length unit description (could be arbitrary text)
  const TCollection_AsciiString& GetUnitName() const { return myUnitName; }

  //! Returns length unit scale factor to meter
  double GetUnitValue() const { return myUnitScaleValue; }

  Standard_EXPORT bool IsEmpty() const { return myUnitName.IsEmpty(); }

  Standard_EXPORT XCAFDoc_LengthUnit();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_LengthUnit, TDF_Attribute)

private:
  double                  myUnitScaleValue;
  TCollection_AsciiString myUnitName;
};
