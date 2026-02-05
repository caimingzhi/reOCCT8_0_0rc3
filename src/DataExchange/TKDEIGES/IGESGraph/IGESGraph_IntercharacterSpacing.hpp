#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines IGESIntercharacterSpacing, Type <406> Form <18>
//! in package IGESGraph
//!
//! Specifies the gap between letters when fixed-pitch
//! spacing is used
class IGESGraph_IntercharacterSpacing : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_IntercharacterSpacing();

  //! This method is used to set the fields of the class
  //! IntercharacterSpacing
  //! - nbProps  : Number of property values (NP = 1)
  //! - anISpace : Intercharacter spacing percentage
  Standard_EXPORT void Init(const int nbProps, const double anISpace);

  //! returns the number of property values in <me>
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the Intercharacter Space of <me> in percentage
  //! of the text height (Range = 0..100)
  Standard_EXPORT double ISpace() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_IntercharacterSpacing, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  double theISpace;
};
