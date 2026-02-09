#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <IGESDimen_CenterLine.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_CenterLine, IGESData_IGESEntity)

IGESDimen_CenterLine::IGESDimen_CenterLine() = default;

void IGESDimen_CenterLine::Init(const int                                      aDataType,
                                const double                                   aZdisp,
                                const occ::handle<NCollection_HArray1<gp_XY>>& dataPnts)
{
  if (dataPnts->Lower() != 1)
    throw Standard_DimensionMismatch("IGESDimen_CenterLine : Init");
  theDatatype      = aDataType;
  theZDisplacement = aZdisp;
  theDataPoints    = dataPnts;
  InitTypeAndForm(106, FormNumber());
}

void IGESDimen_CenterLine::SetCrossHair(const bool mode)
{
  InitTypeAndForm(106, (mode ? 20 : 21));
}

int IGESDimen_CenterLine::Datatype() const
{
  return theDatatype;
}

int IGESDimen_CenterLine::NbPoints() const
{
  return theDataPoints->Length();
}

double IGESDimen_CenterLine::ZDisplacement() const
{
  return theZDisplacement;
}

gp_Pnt IGESDimen_CenterLine::Point(const int Index) const
{
  gp_XY  tempXY = theDataPoints->Value(Index);
  gp_Pnt point(tempXY.X(), tempXY.Y(), theZDisplacement);
  return point;
}

gp_Pnt IGESDimen_CenterLine::TransformedPoint(const int Index) const
{
  gp_XY  point2d = (theDataPoints->Value(Index));
  gp_XYZ point(point2d.X(), point2d.Y(), theZDisplacement);
  if (HasTransf())
    Location().Transforms(point);
  return gp_Pnt(point);
}

bool IGESDimen_CenterLine::IsCrossHair() const
{
  return (FormNumber() == 20);
}
