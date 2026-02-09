#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Point;
class IGESGeom_Direction;

class IGESSolid_PlaneSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_PlaneSurface();

  Standard_EXPORT void Init(const occ::handle<IGESGeom_Point>&     aLocation,
                            const occ::handle<IGESGeom_Direction>& aNormal,
                            const occ::handle<IGESGeom_Direction>& refdir);

  Standard_EXPORT occ::handle<IGESGeom_Point> LocationPoint() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> Normal() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> ReferenceDir() const;

  Standard_EXPORT bool IsParametrised() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_PlaneSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Point>     theLocationPoint;
  occ::handle<IGESGeom_Direction> theNormal;
  occ::handle<IGESGeom_Direction> theRefDir;
};
