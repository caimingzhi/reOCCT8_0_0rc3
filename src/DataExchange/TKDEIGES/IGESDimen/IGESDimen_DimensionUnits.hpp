#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines Dimension Units, Type <406>, Form <28>
//! in package IGESDimen
//! Describes the units and formatting details of the
//! nominal value of a dimension.
class IGESDimen_DimensionUnits : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_DimensionUnits();

  //! This method is used to set the fields of the class
  //! DimensionUnits
  //! - nbPropVal  : Number of property values, always = 6
  //! - aSecondPos : Secondary Dimension Position
  //! 0 = This is the main text
  //! 1 = Before primary dimension
  //! 2 = After primary dimension
  //! 3 = Above primary dimension
  //! 4 = Below primary dimension
  //! - aUnitsInd  : Units Indicator
  //! - aCharSet   : Character Set used
  //! - aFormat    : Format HAsciiString
  //! 1 = Standard ASCII
  //! 1001 = Symbol Font 1
  //! 1002 = Symbol Font 2
  //! 1003 = Drafting Font
  //! - aFracFlag  : Fraction Flag
  //! 0 = Display values as decimal numbers
  //! 1 = Display values as fractions
  //! - aPrecision : Precision Value
  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const int                                    aSecondPos,
                            const int                                    aUnitsInd,
                            const int                                    aCharSet,
                            const occ::handle<TCollection_HAsciiString>& aFormat,
                            const int                                    aFracFlag,
                            const int                                    aPrecision);

  //! returns the number of property values
  Standard_EXPORT int NbPropertyValues() const;

  //! returns position of secondary dimension w.r.t. primary dimension
  Standard_EXPORT int SecondaryDimenPosition() const;

  //! returns the units indicator
  Standard_EXPORT int UnitsIndicator() const;

  //! returns the character set interpretation
  Standard_EXPORT int CharacterSet() const;

  //! returns the string used in formatting value
  Standard_EXPORT occ::handle<TCollection_HAsciiString> FormatString() const;

  //! returns the fraction flag
  Standard_EXPORT int FractionFlag() const;

  //! returns the precision/denominator
  //! number of decimal places when FractionFlag() = 0
  //! denominator of fraction when FractionFlag() = 1
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
