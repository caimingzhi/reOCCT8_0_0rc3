#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines LineWidening, Type <406> Form <5>
//! in package IGESAppli
//! Defines the characteristics of entities when they are
//! used to define locations of items.
class IGESAppli_LineWidening : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_LineWidening();

  //! This method is used to set the fields of the class
  //! LineWidening
  //! - nbPropVal   : Number of property values = 5
  //! - aWidth      : Width of metalization
  //! - aCornering  : Cornering codes
  //! 0 = rounded
  //! 1 = squared
  //! - aExtnFlag   : Extension Flag
  //! 0 = No Extension
  //! 1 = One-half width extension
  //! 2 = Extn set by ExtnVal
  //! - aJustifFlag : Justification flag
  //! 0 = Center justified
  //! 1 = left justified
  //! 2 = right justified
  //! - aExtnVal    : Extension value if aExtnFlag = 2
  Standard_EXPORT void Init(const int    nbPropVal,
                            const double aWidth,
                            const int    aCornering,
                            const int    aExtnFlag,
                            const int    aJustifFlag,
                            const double aExtnVal);

  //! returns the number of property values
  //! is always 5
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the width of metallization
  Standard_EXPORT double WidthOfMetalization() const;

  //! returns the cornering code
  //! 0 = Rounded  / 1 = Squared
  Standard_EXPORT int CorneringCode() const;

  //! returns the extension flag
  //! 0 = No extension
  //! 1 = One-half width extension
  //! 2 = Extension set by theExtnVal
  Standard_EXPORT int ExtensionFlag() const;

  //! returns the justification flag
  //! 0 = Centre justified
  //! 1 = Left justified
  //! 2 = Right justified
  Standard_EXPORT int JustificationFlag() const;

  //! returns the Extension Value
  //! Present only if theExtnFlag = 2
  Standard_EXPORT double ExtensionValue() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_LineWidening, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  double theWidth;
  int    theCorneringCode;
  int    theExtensionFlag;
  int    theJustificationFlag;
  double theExtensionValue;
};

