#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Point;
class IGESGeom_Direction;

//! defines PlaneSurface, Type <190> Form Number <0,1>
//! in package IGESSolid
//! A plane surface entity is defined by a point on the
//! surface and a normal to it.
class IGESSolid_PlaneSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_PlaneSurface();

  //! This method is used to set the fields of the class
  //! PlaneSurface
  //! - aLocation : the point on the surface
  //! - aNormal   : the surface normal direction
  //! - refdir    : the reference direction (default NULL) for
  //! unparameterised curves
  Standard_EXPORT void Init(const occ::handle<IGESGeom_Point>&     aLocation,
                            const occ::handle<IGESGeom_Direction>& aNormal,
                            const occ::handle<IGESGeom_Direction>& refdir);

  //! returns the point on the surface
  Standard_EXPORT occ::handle<IGESGeom_Point> LocationPoint() const;

  //! returns the normal to the surface
  Standard_EXPORT occ::handle<IGESGeom_Direction> Normal() const;

  //! returns the reference direction (for parameterised curve)
  //! returns NULL for unparameterised curve
  Standard_EXPORT occ::handle<IGESGeom_Direction> ReferenceDir() const;

  //! returns True if parameterised, else False
  Standard_EXPORT bool IsParametrised() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_PlaneSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Point>     theLocationPoint;
  occ::handle<IGESGeom_Direction> theNormal;
  occ::handle<IGESGeom_Direction> theRefDir;
};

