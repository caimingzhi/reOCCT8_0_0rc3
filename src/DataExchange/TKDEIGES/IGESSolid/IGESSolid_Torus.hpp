#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

//! defines Torus, Type <160> Form Number <0>
//! in package IGESSolid
//! A Torus is a solid formed by revolving a circular disc
//! about a specified coplanar axis.
class IGESSolid_Torus : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Torus();

  //! This method is used to set the fields of the class Torus
  //! - R1     : distance from center of torus to center
  //! of circular disc to be revolved
  //! - R2     : radius of circular disc
  //! - aPoint : center point coordinates (default (0,0,0))
  //! - anAxis : unit vector in axis direction (default (0,0,1))
  Standard_EXPORT void Init(const double  R1,
                            const double  R2,
                            const gp_XYZ& aPoint,
                            const gp_XYZ& anAxisdir);

  //! returns the distance from the center of torus to the center of
  //! the disc to be revolved
  Standard_EXPORT double MajorRadius() const;

  //! returns the radius of the disc to be revolved
  Standard_EXPORT double DiscRadius() const;

  //! returns the center of torus
  Standard_EXPORT gp_Pnt AxisPoint() const;

  //! returns the center of torus after applying TransformationMatrix
  Standard_EXPORT gp_Pnt TransformedAxisPoint() const;

  //! returns direction of the axis
  Standard_EXPORT gp_Dir Axis() const;

  //! returns direction of the axis after applying TransformationMatrix
  Standard_EXPORT gp_Dir TransformedAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Torus, IGESData_IGESEntity)

private:
  double theR1;
  double theR2;
  gp_XYZ thePoint;
  gp_XYZ theAxis;
};
