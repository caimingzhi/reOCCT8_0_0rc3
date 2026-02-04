#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt;

//! defines IGESLine, Type <110> Form <0>
//! in package IGESGeom
//! A line is a bounded, connected portion of a parent straight
//! line which consists of more than one point. A line is
//! defined by its end points.
//!
//! From IGES-5.3, two other Forms are admitted (same params) :
//! 0 remains for standard limited line (the default)
//! 1 for semi-infinite line (End is just a passing point)
//! 2 for full infinite Line (both Start and End are arbitrary)
class IGESGeom_Line : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Line();

  //! This method is used to set the fields of the class Line
  //! - aStart : Start point of the line
  //! - anEnd  : End point of the line
  Standard_EXPORT void Init(const gp_XYZ& aStart, const gp_XYZ& anEnd);

  //! Returns the Infinite status i.e. the Form Number : 0 1 2
  Standard_EXPORT int Infinite() const;

  //! Sets the Infinite status
  //! Does nothing if <status> is not 0 1 or 2
  Standard_EXPORT void SetInfinite(const int status);

  //! returns the start point of the line
  Standard_EXPORT gp_Pnt StartPoint() const;

  //! returns the start point of the line after applying Transf. Matrix
  Standard_EXPORT gp_Pnt TransformedStartPoint() const;

  //! returns the end point of the line
  Standard_EXPORT gp_Pnt EndPoint() const;

  //! returns the end point of the line after applying Transf. Matrix
  Standard_EXPORT gp_Pnt TransformedEndPoint() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Line, IGESData_IGESEntity)

private:
  gp_XYZ theStart;
  gp_XYZ theEnd;
};

