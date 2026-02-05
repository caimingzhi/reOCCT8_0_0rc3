#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

//! defines IGESTabulatedCylinder, Type <122> Form <0>
//! in package IGESGeom
//! A tabulated cylinder is a surface formed by moving a line
//! segment called generatrix parallel to itself along a curve
//! called directrix. The curve may be a line, circular arc,
//! conic arc, parametric spline curve, rational B-spline
//! curve or composite curve.
class IGESGeom_TabulatedCylinder : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_TabulatedCylinder();

  //! This method is used to set the fields of the class
  //! TabulatedCylinder
  //! - aDirectrix : Directrix Curve of the tabulated cylinder
  //! - anEnd      : Coordinates of the terminate point of the
  //! generatrix
  //! The start point of the directrix is identical to the start
  //! point of the generatrix
  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& aDirectrix,
                            const gp_XYZ&                           anEnd);

  //! returns the directrix curve of the tabulated cylinder
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Directrix() const;

  //! returns end point of generatrix of the tabulated cylinder
  Standard_EXPORT gp_Pnt EndPoint() const;

  //! returns end point of generatrix of the tabulated cylinder
  //! after applying Transf. Matrix
  Standard_EXPORT gp_Pnt TransformedEndPoint() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_TabulatedCylinder, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theDirectrix;
  gp_XYZ                           theEnd;
};
