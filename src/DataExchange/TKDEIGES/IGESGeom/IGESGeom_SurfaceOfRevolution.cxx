#include <IGESGeom_Line.hpp>
#include <IGESGeom_SurfaceOfRevolution.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_SurfaceOfRevolution, IGESData_IGESEntity)

IGESGeom_SurfaceOfRevolution::IGESGeom_SurfaceOfRevolution() = default;

void IGESGeom_SurfaceOfRevolution::Init(const occ::handle<IGESGeom_Line>&       anAxis,
                                        const occ::handle<IGESData_IGESEntity>& aGeneratrix,
                                        const double                            aStartAngle,
                                        const double                            anEndAngle)
{
  theLine       = anAxis;
  theGeneratrix = aGeneratrix;
  theStartAngle = aStartAngle;
  theEndAngle   = anEndAngle;
  InitTypeAndForm(120, 0);
}

occ::handle<IGESGeom_Line> IGESGeom_SurfaceOfRevolution::AxisOfRevolution() const
{
  return theLine;
}

occ::handle<IGESData_IGESEntity> IGESGeom_SurfaceOfRevolution::Generatrix() const
{
  return theGeneratrix;
}

double IGESGeom_SurfaceOfRevolution::StartAngle() const
{
  return theStartAngle;
}

double IGESGeom_SurfaceOfRevolution::EndAngle() const
{
  return theEndAngle;
}
