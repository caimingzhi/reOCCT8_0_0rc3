#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class gp_Dir;

//! defines Cylinder, Type <154> Form Number <0>
//! in package IGESSolid
//! This defines a solid cylinder
class IGESSolid_Cylinder : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Cylinder();

  //! This method is used to set the fields of the class
  //! Cylinder
  //! - aHeight : Cylinder height
  //! - aRadius : Cylinder radius
  //! - aCenter : First face center coordinates (default (0,0,0))
  //! - anAxis  : Unit vector in axis direction (default (0,0,1))
  Standard_EXPORT void Init(const double  aHeight,
                            const double  aRadius,
                            const gp_XYZ& aCenter,
                            const gp_XYZ& anAxis);

  //! returns the cylinder height
  Standard_EXPORT double Height() const;

  //! returns the cylinder radius
  Standard_EXPORT double Radius() const;

  //! returns the first face center coordinates.
  Standard_EXPORT gp_Pnt FaceCenter() const;

  //! returns the first face center after applying TransformationMatrix
  Standard_EXPORT gp_Pnt TransformedFaceCenter() const;

  //! returns the vector in axis direction
  Standard_EXPORT gp_Dir Axis() const;

  //! returns the vector in axis direction after applying
  //! TransformationMatrix
  Standard_EXPORT gp_Dir TransformedAxis() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Cylinder, IGESData_IGESEntity)

private:
  double theHeight;
  double theRadius;
  gp_XYZ theFaceCenter;
  gp_XYZ theAxis;
};
