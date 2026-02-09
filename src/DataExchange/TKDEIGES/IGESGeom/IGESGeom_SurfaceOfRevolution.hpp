#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESGeom_Line;

class IGESGeom_SurfaceOfRevolution : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_SurfaceOfRevolution();

  Standard_EXPORT void Init(const occ::handle<IGESGeom_Line>&       anAxis,
                            const occ::handle<IGESData_IGESEntity>& aGeneratrix,
                            const double                            aStartAngle,
                            const double                            anEndAngle);

  Standard_EXPORT occ::handle<IGESGeom_Line> AxisOfRevolution() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Generatrix() const;

  Standard_EXPORT double StartAngle() const;

  Standard_EXPORT double EndAngle() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_SurfaceOfRevolution, IGESData_IGESEntity)

private:
  occ::handle<IGESGeom_Line>       theLine;
  occ::handle<IGESData_IGESEntity> theGeneratrix;
  double                           theStartAngle;
  double                           theEndAngle;
};
