#include <BOPAlgo_Builder.hpp>
#include <BOPDS_DS.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <TopExp.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

const NCollection_List<TopoDS_Shape>& BOPAlgo_Builder::LocGenerated(const TopoDS_Shape& theS)
{

  myHistShapes.Clear();

  if (theS.IsNull())
    return myHistShapes;

  TopAbs_ShapeEnum aType = theS.ShapeType();
  if (aType != TopAbs_EDGE && aType != TopAbs_FACE)

    return myHistShapes;

  int nS = myDS->Index(theS);
  if (nS < 0)

    return myHistShapes;

  const BOPDS_ShapeInfo& aSI = myDS->ShapeInfo(nS);
  if (!aSI.HasReference())

    return myHistShapes;

  NCollection_Vector<BOPDS_InterfEE>& aEEs = myDS->InterfEE();
  NCollection_Vector<BOPDS_InterfEF>& aEFs = myDS->InterfEF();

  NCollection_Map<int> aMFence;

  bool isFace = (aType == TopAbs_FACE);

  for (int k = (isFace ? 1 : 0); k < 2; ++k)
  {
    int aNbLines = !k ? aEEs.Length() : aEFs.Length();
    for (int i = 0; i < aNbLines; ++i)
    {
      BOPDS_Interf* aInt = !k ? (BOPDS_Interf*)(&aEEs(i)) : (BOPDS_Interf*)(&aEFs(i));
      if (!aInt->HasIndexNew())

        continue;

      if (!aInt->Contains(nS))
        continue;

      int nVNew = aInt->IndexNew();
      myDS->HasShapeSD(nVNew, nVNew);
      if (!aMFence.Add(nVNew))
        continue;

      const TopoDS_Shape& aVNew = myDS->Shape(nVNew);

      if (myMapShape.Contains(aVNew))

        myHistShapes.Append(aVNew);
    }
  }

  if (!isFace)
    return myHistShapes;

  const BOPDS_FaceInfo& aFI = myDS->FaceInfo(nS);

  const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& aMPBSc = aFI.PaveBlocksSc();

  int aNb = aMPBSc.Extent();
  for (int i = 1; i <= aNb; ++i)
  {
    const TopoDS_Shape& aENew = myDS->Shape(aMPBSc(i)->Edge());
    if (myMapShape.Contains(aENew))
      myHistShapes.Append(aENew);
  }

  const NCollection_Map<int>& aMVSc = aFI.VerticesSc();

  NCollection_Map<int>::Iterator aItM(aMVSc);
  for (; aItM.More(); aItM.Next())
  {
    const TopoDS_Shape& aVNew = myDS->Shape(aItM.Value());
    if (myMapShape.Contains(aVNew))
      myHistShapes.Append(aVNew);
  }

  return myHistShapes;
}

const NCollection_List<TopoDS_Shape>* BOPAlgo_Builder::LocModified(const TopoDS_Shape& theS)
{
  return myImages.Seek(theS);
}

void BOPAlgo_Builder::PrepareHistory(const Message_ProgressRange& theRange)
{
  if (!HasHistory())
    return;

  myHistory = new BRepTools_History;

  myMapShape.Clear();
  TopExp::MapShapes(myShape, myMapShape);

  int                   aNbS = myDS->NbSourceShapes();
  Message_ProgressScope aPS(theRange, "Preparing history information", aNbS);
  for (int i = 0; i < aNbS; ++i, aPS.Next())
  {
    const TopoDS_Shape& aS = myDS->Shape(i);

    if (!BRepTools_History::IsSupportedType(aS))
      continue;

    if (UserBreak(aPS))
    {
      return;
    }

    bool isModified = false;

    const NCollection_List<TopoDS_Shape>* pLSp = LocModified(aS);
    if (pLSp)
    {

      NCollection_List<TopoDS_Shape>::Iterator aIt(*pLSp);
      for (; aIt.More(); aIt.Next())
      {
        TopoDS_Shape aSp = aIt.Value();

        if (myMapShape.Contains(aSp))
        {

          TopAbs_ShapeEnum aType = aSp.ShapeType();
          if (aType == TopAbs_VERTEX || aType == TopAbs_SOLID)
            aSp.Orientation(aS.Orientation());
          else if (BOPTools_AlgoTools::IsSplitToReverse(aSp, aS, myContext))
            aSp.Reverse();

          myHistory->AddModified(aS, aSp);
          isModified = true;
        }
      }
    }

    const NCollection_List<TopoDS_Shape>&    aGenShapes = LocGenerated(aS);
    NCollection_List<TopoDS_Shape>::Iterator aIt(aGenShapes);
    for (; aIt.More(); aIt.Next())
    {
      const TopoDS_Shape& aG = aIt.Value();
      if (myMapShape.Contains(aG))
        myHistory->AddGenerated(aS, aG);
    }

    if (!isModified && !myMapShape.Contains(aS))
      myHistory->Remove(aS);
  }
}
