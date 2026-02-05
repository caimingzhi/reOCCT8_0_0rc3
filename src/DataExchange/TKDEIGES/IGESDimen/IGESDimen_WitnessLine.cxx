#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_WitnessLine, IGESData_IGESEntity)

IGESDimen_WitnessLine::IGESDimen_WitnessLine() = default;

void IGESDimen_WitnessLine::Init(const int                                      dataType,
                                 const double                                   aDisp,
                                 const occ::handle<NCollection_HArray1<gp_XY>>& dataPoints)
{
  if (dataPoints->Lower() != 1)
    throw Standard_DimensionMismatch("IGESDimen_WitnessLine : Init");
  theDatatype      = dataType;
  theZDisplacement = aDisp;
  theDataPoints    = dataPoints;
  InitTypeAndForm(106, 40);
}

int IGESDimen_WitnessLine::Datatype() const
{
  return theDatatype;
}

int IGESDimen_WitnessLine::NbPoints() const
{
  return theDataPoints->Length();
}

double IGESDimen_WitnessLine::ZDisplacement() const
{
  return theZDisplacement;
}

gp_Pnt IGESDimen_WitnessLine::Point(const int Index) const
{
  gp_XY  tempXY = theDataPoints->Value(Index);
  gp_Pnt point(tempXY.X(), tempXY.Y(), theZDisplacement);
  return point;
}

gp_Pnt IGESDimen_WitnessLine::TransformedPoint(const int Index) const
{
  gp_XY  point2d = theDataPoints->Value(Index);
  gp_XYZ point(point2d.X(), point2d.Y(), theZDisplacement);
  if (HasTransf())
    Location().Transforms(point);
  return gp_Pnt(point);
}
