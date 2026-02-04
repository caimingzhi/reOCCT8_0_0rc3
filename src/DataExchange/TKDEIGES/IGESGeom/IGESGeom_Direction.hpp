#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Vec;

//! defines IGESDirection, Type <123> Form <0>
//! in package IGESGeom
//! A direction entity is a non-zero vector in Euclidean 3-space
//! that is defined by its three components (direction ratios)
//! with respect to the coordinate axes. If x, y, z are the
//! direction ratios then (x^2 + y^2 + z^2) > 0
class IGESGeom_Direction : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Direction();

  //! This method is used to set the fields of the class
  //! Direction
  //! - aDirection : Direction ratios, Z is 0 by default
  Standard_EXPORT void Init(const gp_XYZ& aDirection);

  Standard_EXPORT gp_Vec Value() const;

  //! returns the Direction value after applying Transformation matrix
  Standard_EXPORT gp_Vec TransformedValue() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Direction, IGESData_IGESEntity)

private:
  gp_XYZ theDirection;
};

