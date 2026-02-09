#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Point;
class IGESGeom_Direction;

class IGESSolid_ConicalSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_ConicalSurface();

  Standard_EXPORT void Init(const occ::handle<IGESGeom_Point>&     aLocation,
                            const occ::handle<IGESGeom_Direction>& anAxis,
                            const double                           aRadius,
                            const double                           anAngle,
                            const occ::handle<IGESGeom_Direction>& aRefdir);

  Standard_EXPORT occ::handle<IGESGeom_Point> LocationPoint() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> Axis() const;

  Standard_EXPORT double Radius() const;

  Standard_EXPORT double SemiAngle() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> ReferenceDir() const;

  Standard_EXPORT bool IsParametrised() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_ConicalSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Point>     theLocationPoint;
  occ::handle<IGESGeom_Direction> theAxis;
  double                          theRadius;
  double                          theAngle;
  occ::handle<IGESGeom_Direction> theRefDir;
};
