#include <Bnd_Box.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Tools.hpp>
#include <BOPAlgo_Alerts.hpp>
#include <BOPDS_DS.hpp>
#include <BOPDS_Iterator.hpp>
#include <BOPDS_ShapeInfo.hpp>
#include <NCollection_Vector.hpp>
#include <BOPDS_Interf.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BRep_Builder.hpp>
#include <BRep_TVertex.hpp>
#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <IntTools_Context.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Precision.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

void BOPAlgo_PaveFiller::PerformVV(const Message_ProgressRange& theRange)
{
  int                                    n1, n2, iFlag, aSize;
  occ::handle<NCollection_BaseAllocator> aAllocator;

  myIterator->Initialize(TopAbs_VERTEX, TopAbs_VERTEX);
  aSize = myIterator->ExpectedLength();
  Message_ProgressScope aPS(theRange, nullptr, 2.);
  if (!aSize)
  {
    return;
  }

  NCollection_Vector<BOPDS_InterfVV>& aVVs = myDS->InterfVV();
  aVVs.SetIncrement(aSize);

  aAllocator = NCollection_BaseAllocator::CommonBaseAllocator();
  NCollection_IndexedDataMap<int, NCollection_List<int>> aMILI(100, aAllocator);
  NCollection_List<NCollection_List<int>>                aMBlocks(aAllocator);

  Message_ProgressScope aPSLoop(aPS.Next(1.), "Performing Vertex-Vertex intersection", aSize);
  for (; myIterator->More(); myIterator->Next(), aPSLoop.Next())
  {
    if (UserBreak(aPS))
    {
      return;
    }
    myIterator->Value(n1, n2);

    if (myDS->HasInterf(n1, n2))
    {
      BOPAlgo_Tools::FillMap(n1, n2, aMILI, aAllocator);
      continue;
    }

    int n1SD = n1;
    myDS->HasShapeSD(n1, n1SD);

    int n2SD = n2;
    myDS->HasShapeSD(n2, n2SD);

    const TopoDS_Vertex& aV1 = (*(TopoDS_Vertex*)(&myDS->Shape(n1SD)));
    const TopoDS_Vertex& aV2 = (*(TopoDS_Vertex*)(&myDS->Shape(n2SD)));

    iFlag = BOPTools_AlgoTools::ComputeVV(aV1, aV2, myFuzzyValue);
    if (!iFlag)
    {
      BOPAlgo_Tools::FillMap(n1, n2, aMILI, aAllocator);
    }
  }

  BOPAlgo_Tools::MakeBlocks(aMILI, aMBlocks, aAllocator);

  NCollection_List<NCollection_List<int>>::Iterator aItB(aMBlocks);
  for (; aItB.More(); aItB.Next())
  {
    if (UserBreak(aPS))
    {
      return;
    }
    const NCollection_List<int>& aLI = aItB.Value();
    MakeSDVertices(aLI);
  }

  NCollection_DataMap<int, int>::Iterator aItDMII;

  NCollection_DataMap<int, int>& aDMII = myDS->ShapesSD();
  aItDMII.Initialize(aDMII);
  for (; aItDMII.More(); aItDMII.Next())
  {
    if (UserBreak(aPS))
    {
      return;
    }
    n1 = aItDMII.Key();
    myDS->InitPaveBlocksForVertex(n1);
  }

  aMBlocks.Clear();
  aMILI.Clear();
}

int BOPAlgo_PaveFiller::MakeSDVertices(const NCollection_List<int>& theVertIndices,
                                       const bool                   theAddInterfs)
{
  TopoDS_Vertex                   aVSD, aVn;
  int                             nSD = -1;
  NCollection_List<int>::Iterator aItLI(theVertIndices);
  NCollection_List<TopoDS_Shape>  aLV;
  for (; aItLI.More(); aItLI.Next())
  {
    int nX = aItLI.Value(), nSD1;
    if (myDS->HasShapeSD(nX, nSD1))
    {
      const TopoDS_Shape& aVSD1 = myDS->Shape(nSD1);
      if (nSD == -1)
      {
        aVSD = TopoDS::Vertex(aVSD1);
        nSD  = nSD1;
      }
      else
      {
        aLV.Append(aVSD1);
      }
    }
    const TopoDS_Shape& aV = myDS->Shape(nX);
    aLV.Append(aV);
  }
  BOPTools_AlgoTools::MakeVertex(aLV, aVn);
  int nV;
  if (nSD != -1)
  {

    BRep_TVertex* aTVertex = static_cast<BRep_TVertex*>(aVSD.TShape().get());
    aTVertex->Pnt(BRep_Tool::Pnt(aVn));
    aTVertex->Tolerance(BRep_Tool::Tolerance(aVn));
    aVn = aVSD;
    nV  = nSD;
  }
  else
  {

    BOPDS_ShapeInfo aSIn;
    aSIn.SetShapeType(TopAbs_VERTEX);
    aSIn.SetShape(aVn);
    nV = myDS->Append(aSIn);
  }
  BOPDS_ShapeInfo& aSIDS = myDS->ChangeShapeInfo(nV);
  Bnd_Box&         aBox  = aSIDS.ChangeBox();
  aBox.Add(BRep_Tool::Pnt(aVn));
  aBox.SetGap(BRep_Tool::Tolerance(aVn) + Precision::Confusion());

  NCollection_Vector<BOPDS_InterfVV>& aVVs = myDS->InterfVV();
  if (theAddInterfs)
    aVVs.SetIncrement(theVertIndices.Extent());

  aItLI.Initialize(theVertIndices);
  for (; aItLI.More(); aItLI.Next())
  {
    int n1 = aItLI.Value();
    myDS->AddShapeSD(n1, nV);

    int                 iR1 = myDS->Rank(n1);
    const TopoDS_Shape& aV1 = myDS->Shape(n1);

    NCollection_List<int>::Iterator aItLI2 = aItLI;
    aItLI2.Next();
    for (; aItLI2.More(); aItLI2.Next())
    {
      int n2 = aItLI2.Value();

      if (iR1 >= 0 && iR1 == myDS->Rank(n2))
      {

        const TopoDS_Shape& aV2 = myDS->Shape(n2);

        TopoDS_Compound aWC;
        BRep_Builder().MakeCompound(aWC);
        BRep_Builder().Add(aWC, aV1);
        BRep_Builder().Add(aWC, aV2);

        AddWarning(new BOPAlgo_AlertSelfInterferingShape(aWC));
      }

      if (theAddInterfs)
      {
        if (myDS->AddInterf(n1, n2))
        {
          BOPDS_InterfVV& aVV = aVVs.Appended();
          aVV.SetIndices(n1, n2);
          aVV.SetIndexNew(nV);
        }
      }
    }
  }
  return nV;
}
