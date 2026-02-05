#include <IGESGeom_CompositeCurve.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_CompositeCurve, IGESData_IGESEntity)

IGESGeom_CompositeCurve::IGESGeom_CompositeCurve() = default;

void IGESGeom_CompositeCurve::Init(
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities)
{
  if (!allEntities.IsNull() && allEntities->Lower() != 1)
    throw Standard_DimensionMismatch("IGESGeom_CompositeCurve : Init");
  theEntities = allEntities;
  InitTypeAndForm(102, 0);
}

int IGESGeom_CompositeCurve::NbCurves() const
{
  return (theEntities.IsNull() ? 0 : theEntities->Length());
}

occ::handle<IGESData_IGESEntity> IGESGeom_CompositeCurve::Curve(const int Index) const
{
  return theEntities->Value(Index);
}
