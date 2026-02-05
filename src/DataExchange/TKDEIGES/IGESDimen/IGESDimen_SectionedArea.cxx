#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESDimen_SectionedArea.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_SectionedArea, IGESData_IGESEntity)

IGESDimen_SectionedArea::IGESDimen_SectionedArea() = default;

void IGESDimen_SectionedArea::Init(
  const occ::handle<IGESData_IGESEntity>&                                   aCurve,
  const int                                                                 aPattern,
  const gp_XYZ&                                                             aPoint,
  const double                                                              aDistance,
  const double                                                              anAngle,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& someIslands)
{
  if (!someIslands.IsNull())
    if (someIslands->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDimen_SectionedArea : Init");
  theExteriorCurve = aCurve;
  thePattern       = aPattern;
  thePassingPoint  = aPoint;
  theDistance      = aDistance;
  theAngle         = anAngle;
  theIslandCurves  = someIslands;
  InitTypeAndForm(230, FormNumber());
}

void IGESDimen_SectionedArea::SetInverted(const bool mode)
{
  InitTypeAndForm(230, (mode ? 1 : 0));
}

bool IGESDimen_SectionedArea::IsInverted() const
{
  return (FormNumber() != 0);
}

occ::handle<IGESData_IGESEntity> IGESDimen_SectionedArea::ExteriorCurve() const
{
  return theExteriorCurve;
}

int IGESDimen_SectionedArea::Pattern() const
{
  return thePattern;
}

gp_Pnt IGESDimen_SectionedArea::PassingPoint() const
{
  return gp_Pnt(thePassingPoint);
}

gp_Pnt IGESDimen_SectionedArea::TransformedPassingPoint() const
{
  gp_XYZ tmpXYZ(thePassingPoint);
  if (HasTransf())
    Location().Transforms(tmpXYZ);
  return gp_Pnt(tmpXYZ);
}

double IGESDimen_SectionedArea::ZDepth() const
{
  return thePassingPoint.Z();
}

double IGESDimen_SectionedArea::Distance() const
{
  return theDistance;
}

double IGESDimen_SectionedArea::Angle() const
{
  return theAngle;
}

int IGESDimen_SectionedArea::NbIslands() const
{
  return (theIslandCurves.IsNull() ? 0 : theIslandCurves->Length());
}

occ::handle<IGESData_IGESEntity> IGESDimen_SectionedArea::IslandCurve(const int num) const
{
  return theIslandCurves->Value(num);
}
