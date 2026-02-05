#include <IGESDimen_DimensionedGeometry.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_DimensionedGeometry, IGESData_IGESEntity)

IGESDimen_DimensionedGeometry::IGESDimen_DimensionedGeometry() = default;

void IGESDimen_DimensionedGeometry::Init(
  const int                                                                 nbDims,
  const occ::handle<IGESData_IGESEntity>&                                   aDimension,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& entities)
{
  if (entities->Lower() != 1)
    throw Standard_DimensionMismatch("IGESDimen_DimensionedGeometry : Init");
  theNbDimensions     = nbDims;
  theDimension        = aDimension;
  theGeometryEntities = entities;
  InitTypeAndForm(402, 13);
}

int IGESDimen_DimensionedGeometry::NbDimensions() const
{
  return theNbDimensions;
}

int IGESDimen_DimensionedGeometry::NbGeometryEntities() const
{
  return theGeometryEntities->Length();
}

occ::handle<IGESData_IGESEntity> IGESDimen_DimensionedGeometry::DimensionEntity() const
{
  return theDimension;
}

occ::handle<IGESData_IGESEntity> IGESDimen_DimensionedGeometry::GeometryEntity(const int num) const
{
  return theGeometryEntities->Value(num);
}
