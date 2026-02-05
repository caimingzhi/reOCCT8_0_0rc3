#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines IGESDrawingSize, Type <406> Form <16>
//! in package IGESGraph
//!
//! Specifies the drawing size in drawing units. The
//! origin of the drawing is defined to be (0,0) in
//! drawing space
class IGESGraph_DrawingSize : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_DrawingSize();

  //! This method is used to set the fields of the class
  //! DrawingSize
  //! - nbProps : Number of property values (NP = 2)
  //! - aXSize  : Extent of Drawing along positive XD axis
  //! - aYSize  : Extent of Drawing along positive YD axis
  Standard_EXPORT void Init(const int nbProps, const double aXSize, const double aYSize);

  //! returns the number of property values in <me> (NP = 2)
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the extent of Drawing along positive XD axis
  Standard_EXPORT double XSize() const;

  //! returns the extent of Drawing along positive YD axis
  Standard_EXPORT double YSize() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_DrawingSize, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  double theXSize;
  double theYSize;
};
