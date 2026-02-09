#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESDimen_DimensionUnits : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_DimensionUnits();

  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const int                                    aSecondPos,
                            const int                                    aUnitsInd,
                            const int                                    aCharSet,
                            const occ::handle<TCollection_HAsciiString>& aFormat,
                            const int                                    aFracFlag,
                            const int                                    aPrecision);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int SecondaryDimenPosition() const;

  Standard_EXPORT int UnitsIndicator() const;

  Standard_EXPORT int CharacterSet() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FormatString() const;

  Standard_EXPORT int FractionFlag() const;

  Standard_EXPORT int PrecisionOrDenominator() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_DimensionUnits, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  int                                   theSecondaryDimenPosition;
  int                                   theUnitsIndicator;
  int                                   theCharacterSet;
  occ::handle<TCollection_HAsciiString> theFormatString;
  int                                   theFractionFlag;
  int                                   thePrecision;
};
