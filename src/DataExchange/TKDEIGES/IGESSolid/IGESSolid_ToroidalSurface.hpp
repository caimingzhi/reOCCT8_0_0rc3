#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Point;
class IGESGeom_Direction;
class gp_Pnt;

class IGESSolid_ToroidalSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_ToroidalSurface();

  Standard_EXPORT void Init(const occ::handle<IGESGeom_Point>&     aCenter,
                            const occ::handle<IGESGeom_Direction>& anAxis,
                            const double                           majRadius,
                            const double                           minRadius,
                            const occ::handle<IGESGeom_Direction>& Refdir);

  Standard_EXPORT occ::handle<IGESGeom_Point> Center() const;

  Standard_EXPORT gp_Pnt TransformedCenter() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> Axis() const;

  Standard_EXPORT double MajorRadius() const;

  Standard_EXPORT double MinorRadius() const;

  Standard_EXPORT occ::handle<IGESGeom_Direction> ReferenceDir() const;

  Standard_EXPORT bool IsParametrised() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_ToroidalSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Point>     theCenter;
  occ::handle<IGESGeom_Direction> theAxis;
  double                          theMajorRadius;
  double                          theMinorRadius;
  occ::handle<IGESGeom_Direction> theRefDir;
};
