#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

//! defines Ellipsoid, Type <168> Form Number <0>
//! in package IGESSolid
//! The ellipsoid is a solid bounded by the surface defined
//! by:
//! X^2       Y^2       Z^2
//! -----  +  -----  +  -----  =  1
//! LX^2      LY^2      LZ^2
class IGESSolid_Ellipsoid : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Ellipsoid();

  //! This method is used to set the fields of the class
  //! Ellipsoid
  //! - aSize      : Lengths in the local X,Y,Z directions
  //! - aCenter    : Center point of ellipsoid (default (0,0,0))
  //! - anXAxis    : Unit vector defining local X-axis
  //! default (1,0,0)
  //! - anZAxis    : Unit vector defining local Z-axis
  //! default (0,0,1)
  Standard_EXPORT void Init(const gp_XYZ& aSize,
                            const gp_XYZ& aCenter,
                            const gp_XYZ& anXAxis,
                            const gp_XYZ& anZAxis);

  //! returns the size
  Standard_EXPORT gp_XYZ Size() const;

  //! returns the length in the local X-direction
  Standard_EXPORT double XLength() const;

  //! returns the length in the local Y-direction
  Standard_EXPORT double YLength() const;

  //! returns the length in the local Z-direction
  Standard_EXPORT double ZLength() const;

  //! returns the center of the ellipsoid
  Standard_EXPORT gp_Pnt Center() const;

  //! returns the center of the ellipsoid after applying
  //! TransformationMatrix
  Standard_EXPORT gp_Pnt TransformedCenter() const;

  //! returns the vector corresponding to the local X-direction
  Standard_EXPORT gp_Dir XAxis() const;

  //! returns the vector corresponding to the local X-direction
  //! after applying TransformationMatrix
  Standard_EXPORT gp_Dir TransformedXAxis() const;

  //! returns the vector corresponding to the local Y-direction
  //! which is got by taking cross product of ZAxis and XAxis
  Standard_EXPORT gp_Dir YAxis() const;

  //! returns the vector corresponding to the local Y-direction
  //! (which is got by taking cross product of ZAxis and XAxis)
  //! after applying TransformationMatrix
  Standard_EXPORT gp_Dir TransformedYAxis() const;

  //! returns the vector corresponding to the local Z-direction
  Standard_EXPORT gp_Dir ZAxis() const;

  //! returns the vector corresponding to the local Z-direction
  //! after applying TransformationMatrix
  Standard_EXPORT gp_Dir TransformedZAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Ellipsoid, IGESData_IGESEntity)

private:
  gp_XYZ theSize;
  gp_XYZ theCenter;
  gp_XYZ theXAxis;
  gp_XYZ theZAxis;
};
