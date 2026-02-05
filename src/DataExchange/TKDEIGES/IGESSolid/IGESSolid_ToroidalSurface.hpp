#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Point;
class IGESGeom_Direction;
class gp_Pnt;

//! defines ToroidalSurface, Type <198> Form Number <0,1>
//! in package IGESSolid
//! This entity is defined by the center point, the axis
//! direction and the major and minor radii. In case of
//! parametrised surface a reference direction is provided.
class IGESSolid_ToroidalSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_ToroidalSurface();

  //! This method is used to set the fields of the class
  //! ToroidalSurface
  //! - aCenter   : the center point coordinates
  //! - anAxis    : the direction of the axis
  //! - majRadius : the major radius
  //! - minRadius : the minor radius
  //! - Refdir    : the reference direction (parametrised)
  //! default Null for unparametrised surface
  Standard_EXPORT void Init(const occ::handle<IGESGeom_Point>&     aCenter,
                            const occ::handle<IGESGeom_Direction>& anAxis,
                            const double                           majRadius,
                            const double                           minRadius,
                            const occ::handle<IGESGeom_Direction>& Refdir);

  //! returns the center point coordinates of the surface
  Standard_EXPORT occ::handle<IGESGeom_Point> Center() const;

  //! returns the center point coordinates of the surface
  //! after applying TransformationMatrix
  Standard_EXPORT gp_Pnt TransformedCenter() const;

  //! returns the direction of the axis
  Standard_EXPORT occ::handle<IGESGeom_Direction> Axis() const;

  //! returns the major radius of the surface
  Standard_EXPORT double MajorRadius() const;

  //! returns the minor radius of the surface
  Standard_EXPORT double MinorRadius() const;

  //! returns the reference direction (parametrised surface)
  //! Null is returned if the surface is not parametrised
  Standard_EXPORT occ::handle<IGESGeom_Direction> ReferenceDir() const;

  //! Returns True if the surface is parametrised, else False
  Standard_EXPORT bool IsParametrised() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_ToroidalSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Point>     theCenter;
  occ::handle<IGESGeom_Direction> theAxis;
  double                          theMajorRadius;
  double                          theMinorRadius;
  occ::handle<IGESGeom_Direction> theRefDir;
};
