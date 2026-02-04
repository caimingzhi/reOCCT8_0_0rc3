#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines IGESNominalSize, Type <406> Form <13>
//! in package IGESGraph
//!
//! Specifies a value, a name, and optionally a
//! reference to an engineering standard
class IGESGraph_NominalSize : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_NominalSize();

  //! This method is used to set the fields of the class
  //! NominalSize
  //! - nbProps           : Number of property values (2 or 3)
  //! - aNominalSizeValue : NominalSize Value
  //! - aNominalSizeName  : NominalSize Name
  //! - aStandardName     : Name of relevant engineering standard
  Standard_EXPORT void Init(const int                                    nbProps,
                            const double                                 aNominalSizeValue,
                            const occ::handle<TCollection_HAsciiString>& aNominalSizeName,
                            const occ::handle<TCollection_HAsciiString>& aStandardName);

  //! returns the number of property values in <me>
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the value of <me>
  Standard_EXPORT double NominalSizeValue() const;

  //! returns the name of <me>
  Standard_EXPORT occ::handle<TCollection_HAsciiString> NominalSizeName() const;

  //! returns True if an engineering Standard is defined for <me>
  //! else, returns False
  Standard_EXPORT bool HasStandardName() const;

  //! returns the name of the relevant engineering standard of <me>
  Standard_EXPORT occ::handle<TCollection_HAsciiString> StandardName() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_NominalSize, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  double                                theNominalSizeValue;
  occ::handle<TCollection_HAsciiString> theNominalSizeName;
  occ::handle<TCollection_HAsciiString> theStandardName;
};

