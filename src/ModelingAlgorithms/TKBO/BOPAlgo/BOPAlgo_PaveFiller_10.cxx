#include <BOPAlgo_PaveFiller.hpp>

#include <Precision.hpp>

#include <gp_Pnt.hpp>
#include <Bnd_Box.hpp>

#include <TopoDS_Iterator.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Edge.hpp>

#include <BRep_Builder.hpp>
#include <BRepBndLib.hpp>

#include <NCollection_Map.hpp>
#include <BOPDS_CommonBlock.hpp>
#include <NCollection_List.hpp>
#include <Standard_Handle.hpp>
#include <BOPDS_DS.hpp>
class BOPDS_PaveBlock;

//=================================================================================================

void BOPAlgo_PaveFiller::SetNonDestructive()
{
  if (!myIsPrimary || myNonDestructive)
  {
    return;
  }
  //
  bool                                     bFlag;
  NCollection_List<TopoDS_Shape>::Iterator aItLS;
  //
  bFlag = false;
  aItLS.Initialize(myArguments);
  for (; aItLS.More() && (!bFlag); aItLS.Next())
  {
    const TopoDS_Shape& aS = aItLS.Value();
    bFlag                  = aS.Locked();
  }
  myNonDestructive = bFlag;
}

//=================================================================================================

void BOPAlgo_PaveFiller::UpdateEdgeTolerance(const int nE, const double theTol)
{
  BOPDS_ShapeInfo&             aSIE = myDS->ChangeShapeInfo(nE);
  const NCollection_List<int>& aLI  = aSIE.SubShapes();

  // For the safe input mode avoid modifying the input shapes
  if (myNonDestructive)
  {
    if (!myDS->IsNewShape(nE))
      return;

    NCollection_List<int>::Iterator itLI(aLI);
    for (; itLI.More(); itLI.Next())
    {
      int nV = itLI.Value(), nVSD;
      if (!myDS->IsNewShape(nV) && !myDS->HasShapeSD(nV, nVSD))
        return;
    }
  }

  // Update edge
  const TopoDS_Edge& aE = *(TopoDS_Edge*)&myDS->Shape(nE);
  BRep_Builder().UpdateEdge(aE, theTol);
  Bnd_Box& aBoxE = aSIE.ChangeBox();
  BRepBndLib::Add(aE, aBoxE);
  aBoxE.SetGap(aBoxE.GetGap() + Precision::Confusion());

  // Update vertices
  NCollection_List<int>::Iterator itLI(aLI);
  for (; itLI.More(); itLI.Next())
  {
    int nV = itLI.Value();
    UpdateVertex(nV, theTol);
  }
}

//=================================================================================================

int BOPAlgo_PaveFiller::UpdateVertex(const int nV, const double aTolNew)
{
  int          nVNew;
  double       aTolV;
  BRep_Builder aBB;

  nVNew = nV;
  if (myDS->IsNewShape(nVNew) || myDS->HasShapeSD(nV, nVNew) || !myNonDestructive)
  {
    // nV is a new vertex, it has SD or non-destructive mode is not in force
    const TopoDS_Vertex& aVSD = *(TopoDS_Vertex*)&myDS->Shape(nVNew);
    aTolV                     = BRep_Tool::Tolerance(aVSD);
    if (aTolV < aTolNew)
    {
      aBB.UpdateVertex(aVSD, aTolNew);
      BOPDS_ShapeInfo& aSIV  = myDS->ChangeShapeInfo(nVNew);
      Bnd_Box&         aBoxV = aSIV.ChangeBox();
      BRepBndLib::Add(aVSD, aBoxV);
      aBoxV.SetGap(aBoxV.GetGap() + Precision::Confusion());
      myIncreasedSS.Add(nV);
    }
    return nVNew;
  }
  //
  // nV is old vertex
  const TopoDS_Vertex& aV = *(TopoDS_Vertex*)&myDS->Shape(nV);
  aTolV                   = BRep_Tool::Tolerance(aV);
  //
  // create new vertex
  TopoDS_Vertex aVNew;
  gp_Pnt        aPV = BRep_Tool::Pnt(aV);
  aBB.MakeVertex(aVNew, aPV, std::max(aTolV, aTolNew));
  //
  // append new vertex to DS
  BOPDS_ShapeInfo aSIV;
  aSIV.SetShapeType(TopAbs_VERTEX);
  aSIV.SetShape(aVNew);
  nVNew = myDS->Append(aSIV);
  //
  // bounding box for the new vertex
  BOPDS_ShapeInfo& aSIDS  = myDS->ChangeShapeInfo(nVNew);
  Bnd_Box&         aBoxDS = aSIDS.ChangeBox();
  BRepBndLib::Add(aVNew, aBoxDS);
  aBoxDS.SetGap(aBoxDS.GetGap() + Precision::Confusion());
  //
  // add vertex to SD map
  myDS->AddShapeSD(nV, nVNew);

  // Add new vertex to map of vertices to avoid further extension
  myVertsToAvoidExtension.Add(nVNew);

  if (aTolV < aTolNew)
    myIncreasedSS.Add(nV);

  return nVNew;
}

//=================================================================================================

void BOPAlgo_PaveFiller::UpdatePaveBlocksWithSDVertices()
{
  myDS->UpdatePaveBlocksWithSDVertices();
}

//=================================================================================================

void BOPAlgo_PaveFiller::UpdateCommonBlocksWithSDVertices()
{
  if (!myNonDestructive)
  {
    UpdatePaveBlocksWithSDVertices();
    return;
  }
  int aNbPBP;
  //
  NCollection_Vector<NCollection_List<occ::handle<BOPDS_PaveBlock>>>& aPBP =
    myDS->ChangePaveBlocksPool();
  aNbPBP = aPBP.Length();
  if (!aNbPBP)
  {
    return;
  }
  //
  int                                                      i, nV1, nV2;
  double                                                   aTolV;
  NCollection_Map<occ::handle<BOPDS_CommonBlock>>          aMCB;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItPB;
  occ::handle<BOPDS_PaveBlock>                             aPB;
  //
  aTolV = Precision::Confusion();
  //
  for (i = 0; i < aNbPBP; ++i)
  {
    NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB = aPBP(i);
    aItPB.Initialize(aLPB);
    for (; aItPB.More(); aItPB.Next())
    {
      aPB                                       = aItPB.Value();
      const occ::handle<BOPDS_CommonBlock>& aCB = myDS->CommonBlock(aPB);
      if (aCB.IsNull())
      {
        continue;
      }
      //
      if (aMCB.Add(aCB))
      {
        aPB->Indices(nV1, nV2);
        UpdateVertex(nV1, aTolV);
        UpdateVertex(nV2, aTolV);
        myDS->UpdateCommonBlockWithSDVertices(aCB);
      }
    }
  }
  UpdatePaveBlocksWithSDVertices();
}

namespace
{
  //=================================================================================================

  template <class InterfType>
  void UpdateIntfsWithSDVertices(BOPDS_PDS theDS, NCollection_Vector<InterfType>& theInterfs)
  {
    for (int i = 0; i < theInterfs.Length(); i++)
    {
      InterfType& anIntf = theInterfs(i);
      int         anInd;
      if (anIntf.HasIndexNew(anInd))
      {
        int anIndSD;
        if (theDS->HasShapeSD(anInd, anIndSD))
        {
          anIntf.SetIndexNew(anIndSD);
        }
      }
    }
  }
} // namespace

//=================================================================================================

void BOPAlgo_PaveFiller::UpdateInterfsWithSDVertices()
{
  UpdateIntfsWithSDVertices(myDS, myDS->InterfVV());
  UpdateIntfsWithSDVertices(myDS, myDS->InterfVE());
  UpdateIntfsWithSDVertices(myDS, myDS->InterfVF());
  UpdateIntfsWithSDVertices(myDS, myDS->InterfEE());
  UpdateIntfsWithSDVertices(myDS, myDS->InterfEF());
}
