#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines IGESLineFontPredefined, Type <406> Form <19>
//! in package IGESGraph
//!
//! Provides the ability to specify a line font pattern
//! from a predefined list rather than from
//! Directory Entry Field 4
class IGESGraph_LineFontPredefined : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_LineFontPredefined();

  //! This method is used to set the fields of the class
  //! LineFontPredefined
  //! - nbProps              : Number of property values (NP = 1)
  //! - aLineFontPatternCode : Line Font Pattern Code
  Standard_EXPORT void Init(const int nbProps, const int aLineFontPatternCode);

  //! returns the number of property values in <me>
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the Line Font Pattern Code of <me>
  Standard_EXPORT int LineFontPatternCode() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_LineFontPredefined, IGESData_IGESEntity)

private:
  int theNbPropertyValues;
  int theLineFontPatternCode;
};

