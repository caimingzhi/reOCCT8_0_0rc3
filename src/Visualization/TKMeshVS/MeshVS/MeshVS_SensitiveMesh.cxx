#include <MeshVS_SensitiveMesh.hpp>

#include <TColStd_HPackedMapOfInteger.hpp>
#include <Select3D_SensitiveEntity.hpp>
#include <MeshVS_DataSource.hpp>
#include <MeshVS_MeshOwner.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MeshVS_SensitiveMesh, Select3D_SensitiveEntity)

MeshVS_SensitiveMesh::MeshVS_SensitiveMesh(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                           const int                                 theMode)
    : Select3D_SensitiveEntity(theOwnerId)
{
  myMode                                = theMode;
  occ::handle<MeshVS_MeshOwner> anOwner = occ::down_cast<MeshVS_MeshOwner>(OwnerId());
  if (!anOwner.IsNull())
  {
    occ::handle<MeshVS_DataSource> aDS = anOwner->GetDataSource();
    if (!aDS.IsNull())
    {
      Bnd_Box aBox = aDS->GetBoundingBox();
      double  aXMin, aYMin, aZMin;
      double  aXMax, aYMax, aZMax;
      aBox.Get(aXMin, aYMin, aZMin, aXMax, aYMax, aZMax);
      NCollection_Vec3<double> aMinPnt(aXMin, aYMin, aZMin);
      NCollection_Vec3<double> aMaxPnt(aXMax, aYMax, aZMax);
      myBndBox = Select3D_BndBox3d(aMinPnt, aMaxPnt);
    }
  }
}

int MeshVS_SensitiveMesh::GetMode() const
{
  return myMode;
}

occ::handle<Select3D_SensitiveEntity> MeshVS_SensitiveMesh::GetConnected()
{
  occ::handle<MeshVS_SensitiveMesh> aMeshEnt = new MeshVS_SensitiveMesh(myOwnerId);
  return aMeshEnt;
}

int MeshVS_SensitiveMesh::NbSubElements() const
{
  occ::handle<MeshVS_MeshOwner> anOwner = occ::down_cast<MeshVS_MeshOwner>(OwnerId());
  if (anOwner.IsNull())
    return -1;
  occ::handle<MeshVS_DataSource> aDataSource = anOwner->GetDataSource();
  if (aDataSource.IsNull())
    return -1;
  return aDataSource->GetAllNodes().Extent();
}

Select3D_BndBox3d MeshVS_SensitiveMesh::BoundingBox()
{
  return myBndBox;
}

gp_Pnt MeshVS_SensitiveMesh::CenterOfGeometry() const
{
  if (!myBndBox.IsValid())
    return gp_Pnt(0.0, 0.0, 0.0);

  NCollection_Vec3<double> aCenter = (myBndBox.CornerMax() + myBndBox.CornerMin()) * 0.5;
  return gp_Pnt(aCenter.x(), aCenter.y(), aCenter.z());
}
