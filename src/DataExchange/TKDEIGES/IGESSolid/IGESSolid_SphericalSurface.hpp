#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Point;
class IGESGeom_Direction;
class gp_Pnt;

//! defines SphericalSurface, Type <196> Form Number <0,1>
//! in package IGESSolid
//! Spherical surface is defined by a center and radius.
//! In case of parametrised surface an axis and a
//! reference direction is provided.
class IGESSolid_SphericalSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SphericalSurface();

  //! This method is used to set the fields of the class
  //! SphericalSurface
  //! - aCenter : the coordinates of the center point
  //! - aRadius : value of radius
  //! - anAxis  : the direction of the axis
  //! Null in case of Unparametrised surface
  //! - aRefdir : the reference direction
  //! Null in case of Unparametrised surface
  Standard_EXPORT void Init(const occ::handle<IGESGeom_Point>&     aCenter,
                            const double                           aRadius,
                            const occ::handle<IGESGeom_Direction>& anAxis,
                            const occ::handle<IGESGeom_Direction>& aRefdir);

  //! returns the center of the spherical surface
  Standard_EXPORT occ::handle<IGESGeom_Point> Center() const;

  //! returns the center of the spherical surface after applying
  //! TransformationMatrix
  Standard_EXPORT gp_Pnt TransformedCenter() const;

  //! returns the radius of the spherical surface
  Standard_EXPORT double Radius() const;

  //! returns the direction of the axis (Parametrised surface)
  //! Null is returned if the surface is not parametrised
  Standard_EXPORT occ::handle<IGESGeom_Direction> Axis() const;

  //! returns the reference direction (Parametrised surface)
  //! Null is returned if the surface is not parametrised
  Standard_EXPORT occ::handle<IGESGeom_Direction> ReferenceDir() const;

  //! Returns True if the surface is parametrised, else False
  Standard_EXPORT bool IsParametrised() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SphericalSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Point>     theCenter;
  double                          theRadius;
  occ::handle<IGESGeom_Direction> theAxis;
  occ::handle<IGESGeom_Direction> theRefDir;
};

