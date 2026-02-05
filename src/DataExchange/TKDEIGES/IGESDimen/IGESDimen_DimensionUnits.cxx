#include <IGESDimen_DimensionUnits.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_DimensionUnits, IGESData_IGESEntity)

IGESDimen_DimensionUnits::IGESDimen_DimensionUnits() = default;

void IGESDimen_DimensionUnits::Init(const int                                    nbPropVal,
                                    const int                                    aSecondPos,
                                    const int                                    aUnitsInd,
                                    const int                                    aCharSet,
                                    const occ::handle<TCollection_HAsciiString>& aFormat,
                                    const int                                    aFracFlag,
                                    const int                                    aPrecision)
{
  theNbPropertyValues       = nbPropVal;
  theSecondaryDimenPosition = aSecondPos;
  theUnitsIndicator         = aUnitsInd;
  theCharacterSet           = aCharSet;
  theFormatString           = aFormat;
  theFractionFlag           = aFracFlag;
  thePrecision              = aPrecision;
  InitTypeAndForm(406, 28);
}

int IGESDimen_DimensionUnits::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESDimen_DimensionUnits::SecondaryDimenPosition() const
{
  return theSecondaryDimenPosition;
}

int IGESDimen_DimensionUnits::UnitsIndicator() const
{
  return theUnitsIndicator;
}

int IGESDimen_DimensionUnits::CharacterSet() const
{
  return theCharacterSet;
}

occ::handle<TCollection_HAsciiString> IGESDimen_DimensionUnits::FormatString() const
{
  return theFormatString;
}

int IGESDimen_DimensionUnits::FractionFlag() const
{
  return theFractionFlag;
}

int IGESDimen_DimensionUnits::PrecisionOrDenominator() const
{
  return thePrecision;
}
