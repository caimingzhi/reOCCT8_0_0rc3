#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Point;
class IGESGeom_Direction;

//! defines CylindricalSurface, Type <192> Form Number <0,1>
//! in package IGESSolid
class IGESSolid_CylindricalSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_CylindricalSurface();

  //! This method is used to set the fields of the class
  //! CylindricalSurface
  //! - aLocation : the location of the point on axis
  //! - anAxis    : the direction of the axis
  //! - aRadius   : the radius at the axis point
  //! - aRefdir   : the reference direction (parametrised surface)
  //! default NULL (unparametrised surface)
  Standard_EXPORT void Init(const occ::handle<IGESGeom_Point>&     aLocation,
                            const occ::handle<IGESGeom_Direction>& anAxis,
                            const double                           aRadius,
                            const occ::handle<IGESGeom_Direction>& aRefdir);

  //! returns the point on the axis
  Standard_EXPORT occ::handle<IGESGeom_Point> LocationPoint() const;

  //! returns the direction on the axis
  Standard_EXPORT occ::handle<IGESGeom_Direction> Axis() const;

  //! returns the radius at the axis point
  Standard_EXPORT double Radius() const;

  //! returns whether the surface is parametrised or not
  Standard_EXPORT bool IsParametrised() const;

  //! returns the reference direction only for parametrised surface
  //! else returns NULL
  Standard_EXPORT occ::handle<IGESGeom_Direction> ReferenceDir() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_CylindricalSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Point>     theLocationPoint;
  occ::handle<IGESGeom_Direction> theAxis;
  double                          theRadius;
  occ::handle<IGESGeom_Direction> theRefDir;
};
