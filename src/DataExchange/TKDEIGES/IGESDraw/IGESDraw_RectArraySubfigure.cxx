#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESDraw_RectArraySubfigure.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_RectArraySubfigure, IGESData_IGESEntity)

IGESDraw_RectArraySubfigure::IGESDraw_RectArraySubfigure() = default;

void IGESDraw_RectArraySubfigure::Init(const occ::handle<IGESData_IGESEntity>&      aBase,
                                       const double                                 aScale,
                                       const gp_XYZ&                                aCorner,
                                       const int                                    nbCols,
                                       const int                                    nbRows,
                                       const double                                 hDisp,
                                       const double                                 vtDisp,
                                       const double                                 rotationAngle,
                                       const int                                    doDont,
                                       const occ::handle<NCollection_HArray1<int>>& allNumPos)
{
  if (!allNumPos.IsNull())
    if (allNumPos->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDraw_RectArraySubfigure : Init");
  theBaseEntity       = aBase;
  theScaleFactor      = aScale;
  theLowerLeftCorner  = aCorner;
  theNbColumns        = nbCols;
  theNbRows           = nbRows;
  theColumnSeparation = hDisp;
  theRowSeparation    = vtDisp;
  theRotationAngle    = rotationAngle;
  theDoDontFlag       = doDont != 0;
  thePositions        = allNumPos;
  InitTypeAndForm(412, 0);
}

occ::handle<IGESData_IGESEntity> IGESDraw_RectArraySubfigure::BaseEntity() const
{
  return theBaseEntity;
}

double IGESDraw_RectArraySubfigure::ScaleFactor() const
{
  return theScaleFactor;
}

gp_Pnt IGESDraw_RectArraySubfigure::LowerLeftCorner() const
{
  gp_Pnt tempLowerLeftCorner(theLowerLeftCorner);
  return tempLowerLeftCorner;
}

gp_Pnt IGESDraw_RectArraySubfigure::TransformedLowerLeftCorner() const
{
  gp_XYZ tempLowerLeftCorner = theLowerLeftCorner;
  if (HasTransf())
    Location().Transforms(tempLowerLeftCorner);
  gp_Pnt tempRes(tempLowerLeftCorner);

  return (tempRes);
}

int IGESDraw_RectArraySubfigure::NbColumns() const
{
  return theNbColumns;
}

int IGESDraw_RectArraySubfigure::NbRows() const
{
  return theNbRows;
}

double IGESDraw_RectArraySubfigure::ColumnSeparation() const
{
  return theColumnSeparation;
}

double IGESDraw_RectArraySubfigure::RowSeparation() const
{
  return theRowSeparation;
}

double IGESDraw_RectArraySubfigure::RotationAngle() const
{
  return theRotationAngle;
}

bool IGESDraw_RectArraySubfigure::DisplayFlag() const
{
  return (thePositions.IsNull());
}

int IGESDraw_RectArraySubfigure::ListCount() const
{
  return (thePositions.IsNull() ? 0 : thePositions->Length());
}

bool IGESDraw_RectArraySubfigure::DoDontFlag() const
{
  return (theDoDontFlag);
}

bool IGESDraw_RectArraySubfigure::PositionNum(const int Index) const
{

  if (thePositions.IsNull())
    return theDoDontFlag;

  int I;
  int up = thePositions->Upper();
  for (I = 1; I <= up; I++)
  {
    if (thePositions->Value(I) == Index)
      return theDoDontFlag;
  }
  return (!theDoDontFlag);
}

int IGESDraw_RectArraySubfigure::ListPosition(const int Index) const
{
  return thePositions->Value(Index);
}
