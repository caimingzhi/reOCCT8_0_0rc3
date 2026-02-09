#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESDraw_CircArraySubfigure.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_CircArraySubfigure, IGESData_IGESEntity)

IGESDraw_CircArraySubfigure::IGESDraw_CircArraySubfigure() = default;

void IGESDraw_CircArraySubfigure::Init(const occ::handle<IGESData_IGESEntity>&      aBase,
                                       const int                                    aNumLocs,
                                       const gp_XYZ&                                aCenter,
                                       const double                                 aRadius,
                                       const double                                 aStAngle,
                                       const double                                 aDelAngle,
                                       const int                                    aFlag,
                                       const occ::handle<NCollection_HArray1<int>>& allNumPos)
{
  if (!allNumPos.IsNull())
    if (allNumPos->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDraw_CircArraySubfigure : Init");
  theBaseEntity  = aBase;
  theNbLocations = aNumLocs;
  theCenter      = aCenter;
  theRadius      = aRadius;
  theStartAngle  = aStAngle;
  theDeltaAngle  = aDelAngle;
  theDoDontFlag  = aFlag != 0;
  thePositions   = allNumPos;
  InitTypeAndForm(414, 0);
}

occ::handle<IGESData_IGESEntity> IGESDraw_CircArraySubfigure::BaseEntity() const
{
  return theBaseEntity;
}

int IGESDraw_CircArraySubfigure::NbLocations() const
{
  return theNbLocations;
}

gp_Pnt IGESDraw_CircArraySubfigure::CenterPoint() const
{
  gp_Pnt tempCenterPoint(theCenter);
  return tempCenterPoint;
}

gp_Pnt IGESDraw_CircArraySubfigure::TransformedCenterPoint() const
{
  gp_XYZ tempCenterPoint = theCenter;
  if (HasTransf())
    Location().Transforms(tempCenterPoint);
  gp_Pnt tempRes(tempCenterPoint);

  return tempRes;
}

double IGESDraw_CircArraySubfigure::CircleRadius() const
{
  return theRadius;
}

double IGESDraw_CircArraySubfigure::StartAngle() const
{
  return theStartAngle;
}

double IGESDraw_CircArraySubfigure::DeltaAngle() const
{
  return theDeltaAngle;
}

bool IGESDraw_CircArraySubfigure::DisplayFlag() const
{
  return (thePositions.IsNull());
}

int IGESDraw_CircArraySubfigure::ListCount() const
{
  return (thePositions.IsNull() ? 0 : thePositions->Length());
}

bool IGESDraw_CircArraySubfigure::DoDontFlag() const
{
  return theDoDontFlag;
}

bool IGESDraw_CircArraySubfigure::PositionNum(const int Index) const
{

  if (thePositions.IsNull())
    return theDoDontFlag;

  else
  {
    int I;
    int up = thePositions->Upper();
    for (I = 1; I <= up; I++)
    {
      if (thePositions->Value(I) == Index)
        return theDoDontFlag;
    }
    return (!theDoDontFlag);
  }
}

int IGESDraw_CircArraySubfigure::ListPosition(const int Index) const
{
  return thePositions->Value(Index);
}
