#include <MeshVS_SensitivePolyhedron.hpp>

#include <gp_Lin.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <MeshVS_Tool.hpp>
#include <Select3D_SensitiveEntity.hpp>
#include <gp_Pnt.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MeshVS_SensitivePolyhedron, Select3D_SensitiveEntity)

//=================================================================================================

MeshVS_SensitivePolyhedron::MeshVS_SensitivePolyhedron(
  const occ::handle<SelectMgr_EntityOwner>&                          theOwner,
  const NCollection_Array1<gp_Pnt>&                                  theNodes,
  const occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& theTopo)
    : Select3D_SensitiveEntity(theOwner),
      myTopo(theTopo)
{
  int aPlaneLowIdx   = theTopo->Lower();
  int aPlaneUpIdx    = theTopo->Upper();
  int aNodesLowerIdx = theNodes.Lower();
  myNodes            = new NCollection_HArray1<gp_Pnt>(aNodesLowerIdx, theNodes.Upper());
  myCenter           = gp_XYZ(0.0, 0.0, 0.0);

  for (int aPlaneIdx = aPlaneLowIdx; aPlaneIdx <= aPlaneUpIdx; ++aPlaneIdx)
  {
    int                                      aVertNb = theTopo->Value(aPlaneIdx).Length();
    occ::handle<NCollection_HArray1<gp_Pnt>> aVertArray =
      new NCollection_HArray1<gp_Pnt>(0, aVertNb - 1);
    for (int aVertIdx = 1; aVertIdx <= aVertNb; ++aVertIdx)
    {
      int           aNodeIdx = theTopo->Value(aPlaneIdx).Value(aVertIdx);
      const gp_Pnt& aVert    = theNodes.Value(aNodeIdx + aNodesLowerIdx);
      aVertArray->SetValue(aVertIdx - 1, aVert);
      myNodes->SetValue(aNodeIdx + aNodesLowerIdx, aVert);
      myBndBox.Add(NCollection_Vec3<double>(aVert.X(), aVert.Y(), aVert.Z()));
      myCenter += aVert.XYZ();
    }

    myTopology.Append(aVertArray);
  }

  myCenter.Divide(theNodes.Length());
}

//=================================================================================================

occ::handle<Select3D_SensitiveEntity> MeshVS_SensitivePolyhedron::GetConnected()
{
  occ::handle<MeshVS_SensitivePolyhedron> aNewEnt =
    new MeshVS_SensitivePolyhedron(myOwnerId, myNodes->Array1(), myTopo);

  return aNewEnt;
}

//=================================================================================================

bool MeshVS_SensitivePolyhedron::Matches(SelectBasics_SelectingVolumeManager& theMgr,
                                         SelectBasics_PickResult&             thePickResult)
{
  SelectBasics_PickResult aPickResult;
  for (NCollection_List<occ::handle<NCollection_HArray1<gp_Pnt>>>::Iterator aIter(myTopology);
       aIter.More();
       aIter.Next())
  {
    if (theMgr.OverlapsPolygon(aIter.Value()->Array1(), Select3D_TOS_INTERIOR, aPickResult))
    {
      thePickResult = SelectBasics_PickResult::Min(thePickResult, aPickResult);
    }
  }
  if (!thePickResult.IsValid())
  {
    return false;
  }

  thePickResult.SetDistToGeomCenter(theMgr.DistToGeometryCenter(CenterOfGeometry()));
  return true;
}

//=======================================================================
// function : NbSubElements
// purpose  : Returns the amount of nodes of polyhedron
//=======================================================================
int MeshVS_SensitivePolyhedron::NbSubElements() const
{
  return myNodes->Length();
}

//=================================================================================================

Select3D_BndBox3d MeshVS_SensitivePolyhedron::BoundingBox()
{
  return myBndBox;
}

//=================================================================================================

gp_Pnt MeshVS_SensitivePolyhedron::CenterOfGeometry() const
{
  return myCenter;
}
