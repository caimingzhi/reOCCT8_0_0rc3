#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;

//! defines IGESDrawingUnits, Type <406> Form <17>
//! in package IGESGraph
//!
//! Specifies the drawing space units as outlined
//! in the Drawing entity
class IGESGraph_DrawingUnits : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_DrawingUnits();

  //! This method is used to set the fields of the class
  //! DrawingUnits
  //! - nbProps : Number of property values (NP = 2)
  //! - aFlag   : DrawingUnits Flag
  //! - aUnit   : DrawingUnits Name
  Standard_EXPORT void Init(const int                                    nbProps,
                            const int                                    aFlag,
                            const occ::handle<TCollection_HAsciiString>& aUnit);

  //! returns the number of property values in <me>
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the drawing space units of <me>
  Standard_EXPORT int Flag() const;

  //! returns the name of the drawing space units of <me>
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Unit() const;

  //! Computes the value of the unit, in meters, according Flag
  //! (same values as for GlobalSection from IGESData)
  Standard_EXPORT double UnitValue() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_DrawingUnits, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  int                                   theFlag;
  occ::handle<TCollection_HAsciiString> theUnit;
};

