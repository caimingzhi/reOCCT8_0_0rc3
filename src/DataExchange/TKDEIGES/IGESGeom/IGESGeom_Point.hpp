#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESBasic_SubfigureDef;
class gp_Pnt;

//! defines IGESPoint, Type <116> Form <0>
//! in package IGESGeom
class IGESGeom_Point : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Point();

  //! This method is used to set the fields of the class Point
  //! - aPoint  : Coordinates of point
  //! - aSymbol : SubfigureDefinition entity specifying the
  //! display symbol if there exists one, or zero
  Standard_EXPORT void Init(const gp_XYZ&                              aPoint,
                            const occ::handle<IGESBasic_SubfigureDef>& aSymbol);

  //! returns coordinates of the point
  Standard_EXPORT gp_Pnt Value() const;

  //! returns coordinates of the point after applying Transf. Matrix
  Standard_EXPORT gp_Pnt TransformedValue() const;

  //! returns True if symbol exists
  Standard_EXPORT bool HasDisplaySymbol() const;

  //! returns display symbol entity if it exists
  Standard_EXPORT occ::handle<IGESBasic_SubfigureDef> DisplaySymbol() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Point, IGESData_IGESEntity)

private:
  gp_XYZ                              thePoint;
  occ::handle<IGESBasic_SubfigureDef> theSymbol;
};

