#include <IGESDraw_Planar.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_Planar, IGESData_IGESEntity)

IGESDraw_Planar::IGESDraw_Planar() = default;

void IGESDraw_Planar::Init(
  const int                                                                 nbMats,
  const occ::handle<IGESGeom_TransformationMatrix>&                         aTransformationMatrix,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities)
{
  if (!allEntities.IsNull())
    if (allEntities->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDraw_Planar : Init");
  theNbMatrices           = nbMats;
  theTransformationMatrix = aTransformationMatrix;
  theEntities             = allEntities;
  InitTypeAndForm(402, 16);
}

int IGESDraw_Planar::NbMatrices() const
{
  return theNbMatrices;
}

int IGESDraw_Planar::NbEntities() const
{
  return (theEntities.IsNull() ? 0 : theEntities->Length());
}

bool IGESDraw_Planar::IsIdentityMatrix() const
{
  return (theTransformationMatrix.IsNull());
}

occ::handle<IGESGeom_TransformationMatrix> IGESDraw_Planar::TransformMatrix() const
{
  return theTransformationMatrix;
}

occ::handle<IGESData_IGESEntity> IGESDraw_Planar::Entity(const int EntityIndex) const
{
  return (theEntities->Value(EntityIndex));
}
