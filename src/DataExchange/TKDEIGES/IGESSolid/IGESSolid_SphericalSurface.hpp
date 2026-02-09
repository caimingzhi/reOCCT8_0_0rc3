#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Point;
class IGESGeom_Direction;
class gp_Pnt;

class IGESSolid_SphericalSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SphericalSurface();

  Standard_EXPORT void Init(const occ::handle<IGESGeom_Point>&     aCenter,
                            const double                           aRadius,
                            const occ::handle<IGESGeom_Direction>& anAxis,
                            const occ::handle<IGESGeom_Direction>& aRefdir);

  Standard_EXPORT occ::handle<IGESGeom_Point> Center() const;

  Standard_EXPORT gp_Pnt TransformedCenter() const;

  Standard_EXPORT double Radius() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> Axis() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> ReferenceDir() const;

  Standard_EXPORT bool IsParametrised() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SphericalSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Point>     theCenter;
  double                          theRadius;
  occ::handle<IGESGeom_Direction> theAxis;
  occ::handle<IGESGeom_Direction> theRefDir;
};
