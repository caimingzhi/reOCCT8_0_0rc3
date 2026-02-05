#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <IGESData_TransfEntity.hpp>
#include <IGESDimen_NewDimensionedGeometry.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_NewDimensionedGeometry, IGESData_IGESEntity)

IGESDimen_NewDimensionedGeometry::IGESDimen_NewDimensionedGeometry() = default;

void IGESDimen_NewDimensionedGeometry::Init(
  const int                                                                 nbDimens,
  const occ::handle<IGESData_IGESEntity>&                                   aDimen,
  const int                                                                 anOrientation,
  const double                                                              anAngle,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities,
  const occ::handle<NCollection_HArray1<int>>&                              allLocations,
  const occ::handle<NCollection_HArray1<gp_XYZ>>&                           allPoints)
{
  int num = allEntities->Length();
  if (allEntities->Lower() != 1 || allLocations->Lower() != 1 || allLocations->Length() != num
      || allPoints->Lower() != 1 || allPoints->Length() != num)
    throw Standard_DimensionMismatch("IGESDimen_NewDimensionedGeometry: Init");
  theNbDimensions             = nbDimens;
  theDimensionEntity          = aDimen;
  theDimensionOrientationFlag = anOrientation;
  theAngleValue               = anAngle;
  theGeometryEntities         = allEntities;
  theDimensionLocationFlags   = allLocations;
  thePoints                   = allPoints;
  InitTypeAndForm(402, 21);
}

int IGESDimen_NewDimensionedGeometry::NbDimensions() const
{
  return theNbDimensions;
}

int IGESDimen_NewDimensionedGeometry::NbGeometries() const
{
  return theGeometryEntities->Length();
}

occ::handle<IGESData_IGESEntity> IGESDimen_NewDimensionedGeometry::DimensionEntity() const
{
  return theDimensionEntity;
}

int IGESDimen_NewDimensionedGeometry::DimensionOrientationFlag() const
{
  return theDimensionOrientationFlag;
}

double IGESDimen_NewDimensionedGeometry::AngleValue() const
{
  return theAngleValue;
}

occ::handle<IGESData_IGESEntity> IGESDimen_NewDimensionedGeometry::GeometryEntity(
  const int Index) const
{
  return theGeometryEntities->Value(Index);
}

int IGESDimen_NewDimensionedGeometry::DimensionLocationFlag(const int Index) const
{
  return theDimensionLocationFlags->Value(Index);
}

gp_Pnt IGESDimen_NewDimensionedGeometry::Point(const int Index) const
{
  return gp_Pnt(thePoints->Value(Index));
}

gp_Pnt IGESDimen_NewDimensionedGeometry::TransformedPoint(const int Index) const
{
  gp_XYZ point = thePoints->Value(Index);
  if (HasTransf())
    Location().Transforms(point);
  return gp_Pnt(point);
}
