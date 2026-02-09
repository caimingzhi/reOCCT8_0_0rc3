#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Point;
class IGESGeom_Direction;

class IGESSolid_CylindricalSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_CylindricalSurface();

  Standard_EXPORT void Init(const occ::handle<IGESGeom_Point>&     aLocation,
                            const occ::handle<IGESGeom_Direction>& anAxis,
                            const double                           aRadius,
                            const occ::handle<IGESGeom_Direction>& aRefdir);

  Standard_EXPORT occ::handle<IGESGeom_Point> LocationPoint() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> Axis() const;

  Standard_EXPORT double Radius() const;

  Standard_EXPORT bool IsParametrised() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> ReferenceDir() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_CylindricalSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Point>     theLocationPoint;
  occ::handle<IGESGeom_Direction> theAxis;
  double                          theRadius;
  occ::handle<IGESGeom_Direction> theRefDir;
};
