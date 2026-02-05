#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

//! defines RightAngularWedge, Type <152> Form Number <0>
//! in package IGESSolid
//! A right angular wedge is a triangular/trapezoidal prism
class IGESSolid_RightAngularWedge : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_RightAngularWedge();

  //! This method is used to set the fields of the class
  //! RightAngularWedge
  //! - aSize    : the lengths along the local axes
  //! - lowX     : the length at the smaller X-side
  //! - aCorner  : the corner point coordinates
  //! default (0,0,0)
  //! - anXAxis  : the unit vector defining local X-axis
  //! default (1,0,0)
  //! - anZAxis  : the unit vector defining local Z-axis
  //! default (0,0,1)
  Standard_EXPORT void Init(const gp_XYZ& aSize,
                            const double  lowX,
                            const gp_XYZ& aCorner,
                            const gp_XYZ& anXAxis,
                            const gp_XYZ& anZAxis);

  //! returns the size
  Standard_EXPORT gp_XYZ Size() const;

  //! returns the length along the local X-axis
  Standard_EXPORT double XBigLength() const;

  //! returns the smaller length along the local X-direction at Y=LY
  Standard_EXPORT double XSmallLength() const;

  //! returns the length along the local Y-axis
  Standard_EXPORT double YLength() const;

  //! returns the length along the local Z-axis
  Standard_EXPORT double ZLength() const;

  //! returns the corner point coordinates
  Standard_EXPORT gp_Pnt Corner() const;

  //! returns the corner point coordinates after applying
  //! TransformationMatrix
  Standard_EXPORT gp_Pnt TransformedCorner() const;

  //! returns the direction defining the local X-axis
  Standard_EXPORT gp_Dir XAxis() const;

  //! returns the direction defining the local X-axis
  //! after applying the TransformationMatrix
  Standard_EXPORT gp_Dir TransformedXAxis() const;

  //! returns the direction defining the local Y-axis
  //! it is got by taking the cross product of ZAxis and XAxis
  Standard_EXPORT gp_Dir YAxis() const;

  //! returns the direction defining the local Y-axis
  //! after applying the TransformationMatrix
  Standard_EXPORT gp_Dir TransformedYAxis() const;

  //! returns the direction defining the local Z-axis
  Standard_EXPORT gp_Dir ZAxis() const;

  //! returns the direction defining the local Z-axis
  //! after applying the TransformationMatrix
  Standard_EXPORT gp_Dir TransformedZAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_RightAngularWedge, IGESData_IGESEntity)

private:
  gp_XYZ theSize;
  double theXSmallLength;
  gp_XYZ theCorner;
  gp_XYZ theXAxis;
  gp_XYZ theZAxis;
};
