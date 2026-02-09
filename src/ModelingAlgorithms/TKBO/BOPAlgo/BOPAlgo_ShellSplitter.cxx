#include <BOPAlgo_ShellSplitter.hpp>
#include <BOPTools_AlgoTools.hpp>
#include <BOPTools_CoupleOfShape.hpp>
#include <BOPTools_Parallel.hpp>
#include <BRep_Builder.hpp>
#include <IntTools_Context.hpp>
#include <NCollection_Vector.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>

static void MakeShell(const NCollection_List<TopoDS_Shape>&, TopoDS_Shell&);

static void RefineShell(TopoDS_Shell&                                              theShell,
                        const NCollection_IndexedDataMap<TopoDS_Shape,
                                                         NCollection_List<TopoDS_Shape>,
                                                         TopTools_ShapeMapHasher>& theMEF,
                        NCollection_List<TopoDS_Shape>&                            aLShX);

class BOPAlgo_CBK
{
public:
  BOPAlgo_CBK()
      : myPCB(nullptr)
  {
  }

  ~BOPAlgo_CBK() = default;

  void SetConnexityBlock(const BOPTools_ConnexityBlock& aCB)
  {
    myPCB = (BOPTools_ConnexityBlock*)&aCB;
  }

  BOPTools_ConnexityBlock& ConnexityBlock() { return *myPCB; }

  void SetProgressRange(const Message_ProgressRange& theRange) { myProgressRange = theRange; }

  void Perform()
  {
    Message_ProgressScope aPS(myProgressRange, nullptr, 1);
    if (!aPS.More())
    {
      return;
    }
    BOPAlgo_ShellSplitter::SplitBlock(*myPCB);
  }

protected:
  BOPTools_ConnexityBlock* myPCB;
  Message_ProgressRange    myProgressRange;
};

typedef NCollection_Vector<BOPAlgo_CBK> BOPAlgo_VectorOfCBK;

BOPAlgo_ShellSplitter::BOPAlgo_ShellSplitter()
    : myStartShapes(myAllocator),
      myShells(myAllocator),
      myLCB(myAllocator)
{
}

BOPAlgo_ShellSplitter::BOPAlgo_ShellSplitter(
  const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_Algo(theAllocator),
      myStartShapes(theAllocator),
      myShells(theAllocator),
      myLCB(myAllocator)
{
}

BOPAlgo_ShellSplitter::~BOPAlgo_ShellSplitter() = default;

void BOPAlgo_ShellSplitter::AddStartElement(const TopoDS_Shape& aE)
{
  myStartShapes.Append(aE);
}

const NCollection_List<TopoDS_Shape>& BOPAlgo_ShellSplitter::StartElements() const
{
  return myStartShapes;
}

const NCollection_List<TopoDS_Shape>& BOPAlgo_ShellSplitter::Shells() const
{
  return myShells;
}

void BOPAlgo_ShellSplitter::Perform(const Message_ProgressRange& theRange)
{
  GetReport()->Clear();
  Message_ProgressScope aPS(theRange, "Building shells", 1);

  BOPTools_AlgoTools::MakeConnexityBlocks(myStartShapes, TopAbs_EDGE, TopAbs_FACE, myLCB);
  if (UserBreak(aPS))
  {
    return;
  }

  MakeShells(aPS.Next());
}

void BOPAlgo_ShellSplitter::SplitBlock(BOPTools_ConnexityBlock& aCB)
{
  int                                      aNbLF, aNbOff, aNbFP;
  int                                      i;
  TopAbs_Orientation                       anOr;
  TopoDS_Edge                              aEL;
  BRep_Builder                             aBB;
  TopoDS_Iterator                          aItS;
  TopExp_Explorer                          aExp;
  NCollection_List<TopoDS_Shape>::Iterator aItF;
  BOPTools_CoupleOfShape                   aCSOff;
  NCollection_Map<TopoDS_Shape>            AddedFacesMap;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                aEFMap, aMEFP;
  occ::handle<IntTools_Context> aContext;

  aContext = new IntTools_Context;

  const NCollection_List<TopoDS_Shape>& myShapes = aCB.Shapes();

  NCollection_List<TopoDS_Shape>& myLoops = aCB.ChangeLoops();
  myLoops.Clear();

  NCollection_Map<TopoDS_Shape> aMFaces;
  aItF.Initialize(myShapes);
  for (; aItF.More(); aItF.Next())
  {
    aMFaces.Add(aItF.Value());
  }

  for (;;)
  {

    aEFMap.Clear();
    aItF.Initialize(myShapes);
    for (; aItF.More(); aItF.Next())
    {
      const TopoDS_Shape& aF = aItF.Value();
      if (aMFaces.Contains(aF))
      {
        TopExp::MapShapesAndAncestors(aF, TopAbs_EDGE, TopAbs_FACE, aEFMap);
      }
    }

    int aNbBegin = aMFaces.Extent();

    int aNbE = aEFMap.Extent();
    for (i = 1; i <= aNbE; ++i)
    {
      const TopoDS_Edge& aE = TopoDS::Edge(aEFMap.FindKey(i));
      if (!BRep_Tool::Degenerated(aE) && aE.Orientation() != TopAbs_INTERNAL)
      {
        const NCollection_List<TopoDS_Shape>& aLF = aEFMap(i);
        if (aLF.Extent() == 1)
        {

          aMFaces.Remove(aLF.First());
        }
      }
    }

    int aNbEnd = aMFaces.Extent();
    if ((aNbEnd == aNbBegin) || (aNbEnd == 0))
    {
      break;
    }
  }

  if (aMFaces.IsEmpty())
  {
    return;
  }

  NCollection_List<TopoDS_Shape> aLFConnected;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aBoundaryFaces;
  aItF.Initialize(myShapes);
  for (; aItF.More(); aItF.Next())
  {
    const TopoDS_Shape& aF = aItF.Value();
    if (aMFaces.Contains(aF))
    {
      aLFConnected.Append(aF);
      if (!aBoundaryFaces.Add(aF))
        aBoundaryFaces.Remove(aF);
    }
  }

  const int aNbShapes      = aLFConnected.Extent();
  bool      bAllFacesTaken = false;

  aItF.Initialize(aLFConnected);
  for (i = 1; aItF.More() && !bAllFacesTaken; aItF.Next(), ++i)
  {
    const TopoDS_Shape& aFF = aItF.Value();
    if (!AddedFacesMap.Add(aFF))
    {
      continue;
    }

    TopoDS_Shell aShell;
    aBB.MakeShell(aShell);
    aBB.Add(aShell, aFF);

    aMEFP.Clear();
    TopExp::MapShapesAndAncestors(aShell, TopAbs_EDGE, TopAbs_FACE, aMEFP);

    aItS.Initialize(aShell);
    for (; aItS.More(); aItS.Next())
    {
      const TopoDS_Face& aF         = (*(TopoDS_Face*)(&aItS.Value()));
      bool               isBoundary = aBoundaryFaces.Contains(aF);

      aExp.Init(aF, TopAbs_EDGE);
      for (; aExp.More(); aExp.Next())
      {
        const TopoDS_Edge& aE = (*(TopoDS_Edge*)(&aExp.Current()));

        if (aMEFP.Contains(aE))
        {
          const NCollection_List<TopoDS_Shape>& aLFP = aMEFP.FindFromKey(aE);
          aNbFP                                      = aLFP.Extent();
          if (aNbFP > 1)
          {
            continue;
          }
        }

        anOr = aE.Orientation();
        if (anOr == TopAbs_INTERNAL)
        {
          continue;
        }

        if (BRep_Tool::Degenerated(aE))
        {
          continue;
        }

        const NCollection_List<TopoDS_Shape>& aLF = aEFMap.FindFromKey(aE);
        aNbLF                                     = aLF.Extent();
        if (!aNbLF)
        {
          continue;
        }

        NCollection_List<BOPTools_CoupleOfShape> aLCSOff;

        int                                      aNbWaysInside = 0;
        TopoDS_Face                              aSelF;
        NCollection_List<TopoDS_Shape>::Iterator aItLF(aLF);
        for (; aItLF.More(); aItLF.Next())
        {
          const TopoDS_Face& aFL = (*(TopoDS_Face*)(&aItLF.Value()));
          if (aF.IsSame(aFL) || AddedFacesMap.Contains(aFL))
          {
            continue;
          }

          if (!BOPTools_AlgoTools::GetEdgeOff(aE, aFL, aEL))
          {
            continue;
          }

          if (isBoundary && !aBoundaryFaces.Contains(aFL))
          {
            ++aNbWaysInside;
            aSelF = aFL;
          }
          aCSOff.SetShape1(aEL);
          aCSOff.SetShape2(aFL);
          aLCSOff.Append(aCSOff);
        }

        aNbOff = aLCSOff.Extent();
        if (!aNbOff)
        {
          continue;
        }

        if (!isBoundary || aNbWaysInside != 1)
        {
          if (aNbOff == 1)
          {
            aSelF = (*(TopoDS_Face*)(&aLCSOff.First().Shape2()));
          }
          else if (aNbOff > 1)
          {
            BOPTools_AlgoTools::GetFaceOff(aE, aF, aLCSOff, aSelF, aContext);
          }
        }

        if (!aSelF.IsNull() && AddedFacesMap.Add(aSelF))
        {
          aBB.Add(aShell, aSelF);
          TopExp::MapShapesAndAncestors(aSelF, TopAbs_EDGE, TopAbs_FACE, aMEFP);
        }
      }
    }

    NCollection_List<TopoDS_Shape> aLShSp;
    RefineShell(aShell, aMEFP, aLShSp);

    NCollection_List<TopoDS_Shape> aLShNC;

    NCollection_List<TopoDS_Shape>::Iterator aItLShSp(aLShSp);
    for (; aItLShSp.More(); aItLShSp.Next())
    {
      TopoDS_Shell& aShSp = *((TopoDS_Shell*)&aItLShSp.Value());

      if (BRep_Tool::IsClosed(aShSp))
      {
        aShSp.Closed(true);
        myLoops.Append(aShSp);
      }
      else
      {
        aLShNC.Append(aShSp);
      }
    }

    bAllFacesTaken = (AddedFacesMap.Extent() == aNbShapes);
    if (bAllFacesTaken)
    {
      break;
    }

    if (aLShSp.Extent() == 1)
    {

      continue;
    }

    NCollection_List<TopoDS_Shape>::Iterator aItLShNC(aLShNC);
    for (; aItLShNC.More(); aItLShNC.Next())
    {
      TopoDS_Iterator aItNC(aItLShNC.Value());
      for (; aItNC.More(); aItNC.Next())
      {
        AddedFacesMap.Remove(aItNC.Value());
      }
    }
  }
}

TopoDS_Shape FindShape(const TopoDS_Shape& theShapeToFind, const TopoDS_Shape& theShape)
{
  TopoDS_Shape    aRes;
  TopExp_Explorer anExp(theShape, theShapeToFind.ShapeType());
  for (; anExp.More(); anExp.Next())
  {
    const TopoDS_Shape& aShape = anExp.Current();
    if (aShape.IsSame(theShapeToFind))
    {
      aRes = aShape;
      break;
    }
  }
  return aRes;
}

void RefineShell(TopoDS_Shell&                                              theShell,
                 const NCollection_IndexedDataMap<TopoDS_Shape,
                                                  NCollection_List<TopoDS_Shape>,
                                                  TopTools_ShapeMapHasher>& theMEF,
                 NCollection_List<TopoDS_Shape>&                            theLShSp)
{
  TopoDS_Iterator aIt(theShell);
  if (!aIt.More())
  {
    return;
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMEStop;

  int i, aNbMEF = theMEF.Extent();
  for (i = 1; i <= aNbMEF; ++i)
  {
    const TopoDS_Edge&                    aE  = TopoDS::Edge(theMEF.FindKey(i));
    const NCollection_List<TopoDS_Shape>& aLF = theMEF(i);
    if (aLF.Extent() > 2)
    {
      aMEStop.Add(aE);
      continue;
    }

    if (aLF.Extent() == 2)
    {
      const TopoDS_Face& aF1 = TopoDS::Face(aLF.First());
      const TopoDS_Face& aF2 = TopoDS::Face(aLF.Last());

      TopoDS_Shape aE1 = FindShape(aE, aF1);
      TopoDS_Shape aE2 = FindShape(aE, aF2);

      if (aE1.Orientation() == aE2.Orientation())
      {
        aMEStop.Add(aE);
        continue;
      }
    }

    int                                      aNbF = 0;
    NCollection_List<TopoDS_Shape>::Iterator aItLF(aLF);
    for (; aItLF.More() && aNbF <= 2; aItLF.Next())
    {
      const TopoDS_Face& aF = TopoDS::Face(aItLF.Value());
      ++aNbF;
      TopExp_Explorer aExp(aF, TopAbs_EDGE);
      for (; aExp.More(); aExp.Next())
      {
        const TopoDS_Shape& aEF = aExp.Current();
        if (aEF.IsSame(aE))
        {
          if (aEF.Orientation() == TopAbs_INTERNAL)
          {
            ++aNbF;
          }
          break;
        }
      }
    }

    if (aNbF > 2)
    {
      aMEStop.Add(aE);
    }
  }

  if (aMEStop.IsEmpty())
  {
    theLShSp.Append(theShell);
    return;
  }

  TopoDS_Builder                                                aBB;
  TopExp_Explorer                                               aExp;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMFB;
  NCollection_Map<TopoDS_Shape>                                 aMFProcessed;
  NCollection_List<TopoDS_Shape>                                aLFP, aLFP1;
  NCollection_List<TopoDS_Shape>::Iterator                      aItLF, aItLFP;

  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aF1 = aIt.Value();
    if (!aMFProcessed.Add(aF1))
    {
      continue;
    }

    aMFB.Clear();
    aLFP.Clear();

    aMFB.Add(aF1);
    aLFP.Append(aF1);

    for (;;)
    {
      aItLFP.Initialize(aLFP);
      for (; aItLFP.More(); aItLFP.Next())
      {
        const TopoDS_Shape& aFP = aItLFP.Value();

        aExp.Init(aFP, TopAbs_EDGE);
        for (; aExp.More(); aExp.Next())
        {
          const TopoDS_Edge& aE = (*(TopoDS_Edge*)(&aExp.Current()));
          if (aMEStop.Contains(aE))
          {
            continue;
          }

          if (aE.Orientation() == TopAbs_INTERNAL)
          {
            continue;
          }

          if (BRep_Tool::Degenerated(aE))
          {
            continue;
          }

          const NCollection_List<TopoDS_Shape>& aLF = theMEF.FindFromKey(aE);

          aItLF.Initialize(aLF);
          for (; aItLF.More(); aItLF.Next())
          {
            const TopoDS_Shape& aFP1 = aItLF.Value();
            if (aFP1.IsSame(aFP))
            {
              continue;
            }
            if (aMFB.Contains(aFP1))
            {
              continue;
            }

            if (aMFProcessed.Add(aFP1))
            {
              aMFB.Add(aFP1);
              aLFP1.Append(aFP1);
            }
          }
        }
      }

      if (aLFP1.IsEmpty())
      {
        break;
      }

      aLFP.Clear();
      aLFP.Append(aLFP1);
    }

    int aNbMFB = aMFB.Extent();
    if (aNbMFB)
    {
      TopoDS_Shell aShSp;
      aBB.MakeShell(aShSp);

      for (i = 1; i <= aNbMFB; ++i)
      {
        const TopoDS_Shape& aFB = aMFB(i);
        aBB.Add(aShSp, aFB);
      }
      theLShSp.Append(aShSp);
    }
  }
}

void BOPAlgo_ShellSplitter::MakeShells(const Message_ProgressRange& theRange)
{
  bool                                                bIsRegular;
  int                                                 aNbVCBK, k;
  NCollection_List<BOPTools_ConnexityBlock>::Iterator aItCB;
  NCollection_List<TopoDS_Shape>::Iterator            aIt;
  BOPAlgo_VectorOfCBK                                 aVCBK;

  Message_ProgressScope aPSOuter(theRange, nullptr, 1);
  myShells.Clear();

  aItCB.Initialize(myLCB);
  for (; aItCB.More(); aItCB.Next())
  {
    if (UserBreak(aPSOuter))
    {
      return;
    }
    BOPTools_ConnexityBlock& aCB = aItCB.ChangeValue();
    bIsRegular                   = aCB.IsRegular();
    if (bIsRegular)
    {
      TopoDS_Shell aShell;

      const NCollection_List<TopoDS_Shape>& aLF = aCB.Shapes();
      MakeShell(aLF, aShell);
      aShell.Closed(true);
      myShells.Append(aShell);
    }
    else
    {
      BOPAlgo_CBK& aCBK = aVCBK.Appended();
      aCBK.SetConnexityBlock(aCB);
    }
  }

  aNbVCBK = aVCBK.Length();
  Message_ProgressScope aPSParallel(aPSOuter.Next(), nullptr, aNbVCBK);
  for (int iS = 0; iS < aNbVCBK; ++iS)
  {
    aVCBK.ChangeValue(iS).SetProgressRange(aPSParallel.Next());
  }

  BOPTools_Parallel::Perform(myRunParallel, aVCBK);

  for (k = 0; k < aNbVCBK; ++k)
  {
    BOPAlgo_CBK&                          aCBK = aVCBK(k);
    const BOPTools_ConnexityBlock&        aCB  = aCBK.ConnexityBlock();
    const NCollection_List<TopoDS_Shape>& aLS  = aCB.Loops();
    aIt.Initialize(aLS);
    for (; aIt.More(); aIt.Next())
    {
      TopoDS_Shape& aShell = aIt.ChangeValue();
      aShell.Closed(true);
      myShells.Append(aShell);
    }
  }
}

void MakeShell(const NCollection_List<TopoDS_Shape>& aLS, TopoDS_Shell& aShell)
{
  BRep_Builder                             aBB;
  NCollection_List<TopoDS_Shape>::Iterator aIt;

  aBB.MakeShell(aShell);

  aIt.Initialize(aLS);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aF = aIt.Value();
    aBB.Add(aShell, aF);
  }

  BOPTools_AlgoTools::OrientFacesOnShell(aShell);
}
