#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

//! defines Sphere, Type <158> Form Number <0>
//! in package IGESSolid
//! This defines a sphere with a center and radius
class IGESSolid_Sphere : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Sphere();

  //! This method is used to set the fields of the class Sphere
  //! - aRadius : the radius of the sphere
  //! - aCenter : the center point coordinates (default (0,0,0))
  Standard_EXPORT void Init(const double aRadius, const gp_XYZ& aCenter);

  //! returns the radius of the sphere
  Standard_EXPORT double Radius() const;

  //! returns the center of the sphere
  Standard_EXPORT gp_Pnt Center() const;

  //! returns the center of the sphere after applying
  //! TransformationMatrix
  Standard_EXPORT gp_Pnt TransformedCenter() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Sphere, IGESData_IGESEntity)

private:
  double theRadius;
  gp_XYZ theCenter;
};

