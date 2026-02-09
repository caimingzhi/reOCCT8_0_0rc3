#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBndLib.hpp>
#include <Message_Msg.hpp>
#include <Message_ProgressScope.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_IndexedMap.hpp>
#include <ShapeAnalysis_Shell.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeFix_Face.hpp>
#include <ShapeFix_Shell.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Sequence.hpp>

#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <algorithm>

IMPLEMENT_STANDARD_RTTIEXT(ShapeFix_Shell, ShapeFix_Root)

namespace
{

  using FaceEdgesMap = NCollection_IndexedDataMap<TopoDS_Face, NCollection_Array1<TopoDS_Edge>>;
  using EdgeFacesAllocator =
    NCollection_Allocator<std::pair<const TopoDS_Edge, NCollection_DynamicArray<TopoDS_Face>>>;
  using EdgeFacesMap = std::unordered_map<TopoDS_Edge,
                                          NCollection_DynamicArray<TopoDS_Face>,
                                          TopTools_ShapeMapHasher,
                                          TopTools_ShapeMapHasher,
                                          EdgeFacesAllocator>;

  constexpr int DEFAULT_EDGE_FACES_INCREMENT = 5;
} // namespace

ShapeFix_Shell::ShapeFix_Shell()
{
  myStatus             = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myFixFaceMode        = -1;
  myFixOrientationMode = -1;
  myFixFace            = new ShapeFix_Face;
  myNbShells           = 0;
  myNonManifold        = false;
}

ShapeFix_Shell::ShapeFix_Shell(const TopoDS_Shell& shape)
{
  myStatus             = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myFixFaceMode        = -1;
  myFixOrientationMode = -1;
  myFixFace            = new ShapeFix_Face;
  Init(shape);
  myNonManifold = false;
}

void ShapeFix_Shell::Init(const TopoDS_Shell& shell)
{
  myShape    = shell;
  myShell    = shell;
  myNbShells = 0;
}

bool ShapeFix_Shell::Perform(const Message_ProgressRange& theProgress)
{
  bool status = false;
  if (Context().IsNull())
    SetContext(new ShapeBuild_ReShape);
  myFixFace->SetContext(Context());

  if (NeedFix(myFixFaceMode))
  {
    TopoDS_Shape S = Context()->Apply(myShell);

    int aNbFaces = S.NbChildren();

    Message_ProgressScope aPS(theProgress, "Fixing face", aNbFaces);

    for (TopoDS_Iterator iter(S); iter.More() && aPS.More(); iter.Next(), aPS.Next())
    {
      TopoDS_Shape sh      = iter.Value();
      TopoDS_Face  tmpFace = TopoDS::Face(sh);
      myFixFace->Init(tmpFace);
      if (myFixFace->Perform())
      {
        status = true;
        myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
      }
    }

    if (!aPS.More())
      return false;
  }

  TopoDS_Shape newsh = Context()->Apply(myShell);
  if (NeedFix(myFixOrientationMode))
    FixFaceOrientation(TopoDS::Shell(newsh), true, myNonManifold);

  TopoDS_Shape        aNewsh = Context()->Apply(newsh);
  ShapeAnalysis_Shell aSas;
  for (TopExp_Explorer aShellExp(aNewsh, TopAbs_SHELL); aShellExp.More(); aShellExp.Next())
  {
    TopoDS_Shell aCurShell = TopoDS::Shell(aShellExp.Current());
    if (aCurShell.Closed())
    {
      aSas.LoadShells(aCurShell);
      aSas.CheckOrientedShells(aCurShell, true);
      if (aSas.HasFreeEdges())
      {
        aCurShell.Closed(false);

        SendWarning(Message_Msg("FixAdvShell.FixClosedFlag.MSG0"));
      }
      aSas.Clear();
    }
  }

  if (status)
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  if (Status(ShapeExtend_DONE2))
    status = true;
  return status;
}

static bool GetFreeEdges(const TopoDS_Shape&                                     aShape,
                         NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& MapEdges)
{
  for (TopExp_Explorer aExpF(aShape, TopAbs_FACE); aExpF.More(); aExpF.Next())
  {
    for (TopExp_Explorer aExpE(aExpF.Current(), TopAbs_EDGE); aExpE.More(); aExpE.Next())
    {
      TopoDS_Edge edge = TopoDS::Edge(aExpE.Current());
      if (!MapEdges.Contains(edge))
        MapEdges.Add(edge);
      else
        MapEdges.Remove(edge);
    }
  }
  return !MapEdges.IsEmpty();
}

static NCollection_List<NCollection_Sequence<TopoDS_Shape>> GetConnectedFaceGroups(
  const FaceEdgesMap& theFaceEdges,
  const EdgeFacesMap& theEdgeFaces)
{
  NCollection_List<NCollection_Sequence<TopoDS_Shape>> aConnectedGroups;

  if (theFaceEdges.IsEmpty())
  {
    return aConnectedGroups;
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aVisitedFaces(
    static_cast<int>(theFaceEdges.Size()));

  for (auto aFaceIter = theFaceEdges.begin(); aFaceIter != theFaceEdges.end(); ++aFaceIter)
  {
    const TopoDS_Face& aStartFace = aFaceIter.ChangeIterator().Key();

    if (aVisitedFaces.Contains(aStartFace))
    {
      continue;
    }

    NCollection_Sequence<TopoDS_Shape> aConnectedGroup;

    using StackAllocator = NCollection_Allocator<TopoDS_Face>;
    std::stack<TopoDS_Face, std::deque<TopoDS_Face, StackAllocator>> aStack;
    aStack.push(aStartFace);
    aVisitedFaces.Add(aStartFace);

    while (!aStack.empty())
    {
      const TopoDS_Face aCurrentFace = aStack.top();
      aStack.pop();
      aConnectedGroup.Append(aCurrentFace);

      auto aFaceEdgesIter = theFaceEdges.Seek(aCurrentFace);
      if (aFaceEdgesIter)
      {
        const NCollection_Array1<TopoDS_Edge>& aFaceEdgesArray = *aFaceEdgesIter;

        for (int anEdgeIdx = aFaceEdgesArray.Lower(); anEdgeIdx <= aFaceEdgesArray.Upper();
             ++anEdgeIdx)
        {
          const TopoDS_Edge& anEdge = aFaceEdgesArray.Value(anEdgeIdx);

          auto anEdgeFacesIter = theEdgeFaces.find(anEdge);
          if (anEdgeFacesIter != theEdgeFaces.end())
          {
            const NCollection_DynamicArray<TopoDS_Face>& aConnectedFaces = anEdgeFacesIter->second;

            for (int aFaceIdx = 0; aFaceIdx < aConnectedFaces.Length(); ++aFaceIdx)
            {
              const TopoDS_Face& aNeighborFace = aConnectedFaces.Value(aFaceIdx);

              if (!aVisitedFaces.Contains(aNeighborFace))
              {
                aVisitedFaces.Add(aNeighborFace);
                aStack.push(aNeighborFace);
              }
            }
          }
        }
      }
    }

    bool anIsInserted = false;

    for (NCollection_List<NCollection_Sequence<TopoDS_Shape>>::Iterator anIter(aConnectedGroups);
         anIter.More();
         anIter.Next())
    {
      if (aConnectedGroup.Length() > anIter.Value().Length())
      {
        aConnectedGroups.InsertBefore(aConnectedGroup, anIter);
        anIsInserted = true;
        break;
      }
    }

    if (!anIsInserted)
    {
      aConnectedGroups.Append(aConnectedGroup);
    }
  }

  return aConnectedGroups;
}

static bool GetShells(
  NCollection_Sequence<TopoDS_Shape>&                                       theLfaces,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&             theMapMultiConnectEdges,
  NCollection_Sequence<TopoDS_Shape>&                                       theSeqShells,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theMapFaceShells,
  NCollection_Sequence<TopoDS_Shape>&                                       theErrFaces)
{
  bool aDone = false;
  if (!theLfaces.Length())
  {
    return false;
  }
  TopoDS_Shell nshell;
  BRep_Builder B;
  B.MakeShell(nshell);
  bool                               anIsMultiConnex = !theMapMultiConnectEdges.IsEmpty();
  int                                aFaceIdx = 1, aFacesInShellCount = 1;
  NCollection_Sequence<TopoDS_Shape> aSeqUnconnectFaces;

  using EdgeMapAllocator =
    NCollection_Allocator<std::pair<const TopoDS_Edge, std::pair<bool, bool>>>;
  using EdgeOrientedMap = std::unordered_map<TopoDS_Edge,
                                             std::pair<bool, bool>,
                                             TopTools_ShapeMapHasher,
                                             TopTools_ShapeMapHasher,
                                             EdgeMapAllocator>;
  using TempProcessedEdges =
    NCollection_DataMap<TopoDS_Edge, std::pair<bool, bool>, TopTools_ShapeMapHasher>;

  FaceEdgesMap aFaceEdges;
  aFaceEdges.ReSize(theLfaces.Length());
  size_t                                aNumberOfEdges = 0;
  NCollection_DynamicArray<TopoDS_Edge> aTempEdges;
  for (NCollection_Sequence<TopoDS_Shape>::Iterator anFaceIter(theLfaces); anFaceIter.More();
       anFaceIter.Next())
  {
    aTempEdges.Clear();
    TopoDS_Face aFace = TopoDS::Face(anFaceIter.Value());
    for (TopExp_Explorer anEdgeExp(aFace, TopAbs_EDGE); anEdgeExp.More(); anEdgeExp.Next())
    {
      aTempEdges.Append(TopoDS::Edge(anEdgeExp.Current()));
      aNumberOfEdges++;
    }
    NCollection_Array1<TopoDS_Edge> aFaceEdgesArray(1, static_cast<int>(aTempEdges.Length()));
    for (int idx = 0; idx < aTempEdges.Length(); ++idx)
    {
      aFaceEdgesArray.SetValue(idx + 1, aTempEdges.Value(idx));
    }
    aFaceEdges.Add(aFace, std::move(aFaceEdgesArray));
  }

  EdgeFacesMap aEdgeFaces;
  aEdgeFaces.reserve(aNumberOfEdges);

  for (int aFaceInd = 1; aFaceInd <= aFaceEdges.Size(); ++aFaceInd)
  {
    const TopoDS_Face&                     aFace           = aFaceEdges.FindKey(aFaceInd);
    const NCollection_Array1<TopoDS_Edge>& aFaceEdgesArray = aFaceEdges.FindFromIndex(aFaceInd);

    for (int anEdgeInd = aFaceEdgesArray.Lower(); anEdgeInd <= aFaceEdgesArray.Upper(); ++anEdgeInd)
    {
      const TopoDS_Edge& anEdge = aFaceEdgesArray.Value(anEdgeInd);

      auto& aFacesArray = aEdgeFaces[anEdge];

      bool aFaceExists = false;
      for (int aFaceCheckIdx = 0; aFaceCheckIdx < aFacesArray.Length(); ++aFaceCheckIdx)
      {
        if (aFacesArray.Value(aFaceCheckIdx).IsSame(aFace))
        {
          aFaceExists = true;
          break;
        }
      }

      if (aFacesArray.IsEmpty())
      {
        aFacesArray.SetIncrement(DEFAULT_EDGE_FACES_INCREMENT);
      }

      if (!aFaceExists)
      {
        aFacesArray.Append(aFace);
      }
    }
  }

  NCollection_List<NCollection_Sequence<TopoDS_Shape>> aConnectedGroups =
    GetConnectedFaceGroups(aFaceEdges, aEdgeFaces);

  if (aConnectedGroups.IsEmpty())
  {
    return false;
  }

  aNumberOfEdges = static_cast<size_t>((aNumberOfEdges / 2) + 1);

  EdgeOrientedMap aProcessedEdges;
  aProcessedEdges.reserve(aNumberOfEdges);

  NCollection_Sequence<TopoDS_Shape> aProcessingFaces = std::move(aConnectedGroups.First());

  TempProcessedEdges aTempProcessedEdges(static_cast<int>(aNumberOfEdges));
  for (; aFaceIdx <= aProcessingFaces.Length(); aFaceIdx++)
  {
    aTempProcessedEdges.Clear();

    int         aBadOrientationCount = 0, aGoodOrientationCount = 0;
    TopoDS_Face F1 = TopoDS::Face(aProcessingFaces.Value(aFaceIdx));

    const NCollection_Array1<TopoDS_Edge>& aFaceEdgesArray = aFaceEdges.FindFromKey(F1);

    for (int anEdgeInd = aFaceEdgesArray.Lower(); anEdgeInd <= aFaceEdgesArray.Upper(); ++anEdgeInd)
    {
      const TopoDS_Edge& edge = aFaceEdgesArray.Value(anEdgeInd);

      if (anIsMultiConnex && theMapMultiConnectEdges.Contains(edge))
        continue;

      auto aProcessedEdgeIt = aProcessedEdges.find(edge);

      if (aProcessedEdgeIt == aProcessedEdges.end())
      {
        std::pair<bool, bool>* aTempProcessedEdgeIt = aTempProcessedEdges.ChangeSeek(edge);
        if (!aTempProcessedEdgeIt)
        {
          std::pair<bool, bool> anEdgeOrientationPair{(edge.Orientation() == TopAbs_FORWARD),
                                                      (edge.Orientation() == TopAbs_REVERSED)};

          aTempProcessedEdges.Bind(edge, anEdgeOrientationPair);
        }
        else
        {
          aTempProcessedEdgeIt->first =
            aTempProcessedEdgeIt->first || (edge.Orientation() == TopAbs_FORWARD);
          aTempProcessedEdgeIt->second =
            aTempProcessedEdgeIt->second || (edge.Orientation() == TopAbs_REVERSED);
        }
        continue;
      }

      auto& aPair = aProcessedEdgeIt->second;

      const bool isDirect   = aPair.first;
      const bool isReversed = aPair.second;

      if ((edge.Orientation() == TopAbs_FORWARD && isDirect)
          || (edge.Orientation() == TopAbs_REVERSED && isReversed))
      {
        aBadOrientationCount++;
      }
      else if ((edge.Orientation() == TopAbs_FORWARD && isReversed)
               || (edge.Orientation() == TopAbs_REVERSED && isDirect))
      {
        aGoodOrientationCount++;
      }

      if (isDirect)
      {
        aPair.first = false;
      }
      else if (isReversed)
      {
        aPair.second = false;
      }

      if (!aPair.first && !aPair.second)
      {

        aProcessedEdges.erase(aProcessedEdgeIt);
      }
    }

    if (!aBadOrientationCount && !aGoodOrientationCount && aTempProcessedEdges.IsEmpty())
      continue;

    if (aGoodOrientationCount != 0 && aBadOrientationCount != 0)
    {
      theErrFaces.Append(F1);
      aProcessingFaces.Remove(aFaceIdx);
      aFacesInShellCount++;
      continue;
    }

    if ((aGoodOrientationCount != 0 || aBadOrientationCount != 0) || aFacesInShellCount == 1)
    {
      if (aBadOrientationCount != 0)
      {
        F1.Reverse();

        for (TempProcessedEdges::Iterator aTempEdgeIter(aTempProcessedEdges); aTempEdgeIter.More();
             aTempEdgeIter.Next())
        {
          const TopoDS_Edge& edge                  = aTempEdgeIter.Key();
          const auto&        anEdgeOrientationPair = aTempEdgeIter.Value();

          std::pair<bool, bool> aRevertedPair{!anEdgeOrientationPair.first,
                                              !anEdgeOrientationPair.second};

          auto aProcessedEdgeIt = aProcessedEdges.find(edge);
          if (aProcessedEdgeIt == aProcessedEdges.end())
          {
            aProcessedEdges.emplace(edge, aRevertedPair);
          }
          else
          {
            auto& aPair = aProcessedEdgeIt->second;
            aPair       = aRevertedPair;
          }
        }
        aDone = true;
      }
      else
      {
        for (TempProcessedEdges::Iterator aTempEdgeIter(aTempProcessedEdges); aTempEdgeIter.More();
             aTempEdgeIter.Next())
        {
          const TopoDS_Edge& edge                  = aTempEdgeIter.Key();
          const auto&        anEdgeOrientationPair = aTempEdgeIter.Value();

          auto aProcessedEdgeIt = aProcessedEdges.find(edge);
          if (aProcessedEdgeIt == aProcessedEdges.end())
          {
            aProcessedEdges.emplace(edge, anEdgeOrientationPair);
          }
          else
          {
            auto& aPair  = aProcessedEdgeIt->second;
            aPair.first  = anEdgeOrientationPair.first;
            aPair.second = anEdgeOrientationPair.second;
          }
        }
      }
      aFacesInShellCount++;
      B.Add(nshell, F1);
      theMapFaceShells.Bind(F1, nshell);
      aProcessingFaces.Remove(aFaceIdx);

      if (anIsMultiConnex && BRep_Tool::IsClosed(nshell))
      {
        nshell.Closed(true);
        theSeqShells.Append(nshell);
        TopoDS_Shell nshellnext;
        B.MakeShell(nshellnext);
        nshell             = nshellnext;
        aFacesInShellCount = 1;
      }

      aFaceIdx = 0;
    }

    if (aProcessingFaces.Length() && aFaceIdx == aProcessingFaces.Length()
        && aFacesInShellCount <= 2)
    {
      TopoDS_Iterator aItf(nshell, false);
      if (aItf.More())
      {
        aSeqUnconnectFaces.Append(aItf.Value());
        theMapFaceShells.UnBind(aItf.Value());
      }
      TopoDS_Shell nshellnext;
      B.MakeShell(nshellnext);
      nshell             = nshellnext;
      aFaceIdx           = 0;
      aFacesInShellCount = 1;
    }
  }
  bool isContains = false;
  for (int k = 1; k <= theSeqShells.Length() && !isContains; k++)
    isContains = nshell.IsSame(theSeqShells.Value(k));
  if (!isContains)
  {
    int          numFace = 0;
    TopoDS_Shape aFace;
    for (TopoDS_Iterator aItf(nshell, false); aItf.More(); aItf.Next())
    {
      aFace = aItf.Value();
      numFace++;
    }
    if (numFace > 1)
    {

      if (!anIsMultiConnex)
        nshell.Closed(BRep_Tool::IsClosed(nshell));
      theSeqShells.Append(nshell);
    }
    else if (numFace == 1)
    {
      if (theMapFaceShells.IsBound(aFace))
        theMapFaceShells.UnBind(aFace);
      aProcessingFaces.Append(aFace);
    }
  }

  int aGroupIndex = 1;
  for (NCollection_List<NCollection_Sequence<TopoDS_Shape>>::Iterator aGroupIter(aConnectedGroups);
       aGroupIter.More();
       aGroupIter.Next(), ++aGroupIndex)
  {
    if (aGroupIndex == 1)
      continue;

    const NCollection_Sequence<TopoDS_Shape>& aUnprocessedGroup = aGroupIter.Value();
    for (int anUnprocFaceIdx = 1; anUnprocFaceIdx <= aUnprocessedGroup.Length(); ++anUnprocFaceIdx)
    {
      aSeqUnconnectFaces.Append(aUnprocessedGroup.Value(anUnprocFaceIdx));
    }
  }

  theLfaces = std::move(aProcessingFaces);

  for (int j1 = 1; j1 <= aSeqUnconnectFaces.Length(); j1++)
  {
    theLfaces.Append(aSeqUnconnectFaces.Value(j1));
  }

  return aDone;
}

static bool AddMultiConexityFaces(
  NCollection_Sequence<TopoDS_Shape>&                           Lface,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapMultiConnectEdges,
  NCollection_Sequence<TopoDS_Shape>&                           SeqShells,
  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& aMapFaceShells,
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>&                      aMapEdgeFaces,
  NCollection_Sequence<TopoDS_Shape>&                                             ErrFaces,
  const bool                                                                      NonManifold)
{
  bool done = false;

  NCollection_Sequence<TopoDS_Shape> llPosibleShells;
  NCollection_Sequence<TopoDS_Shape> AddShapes;
  for (int i1 = 1; i1 <= Lface.Length(); i1++)
  {

    const TopoDS_Shape& aShape = Lface.Value(i1);

    int aNbMultEdges = 0;

    for (TopoDS_Iterator aItWires(aShape, false); aItWires.More(); aItWires.Next())
    {
      int aNbEdges = 0;
      for (TopoDS_Iterator aItEdges(aItWires.Value(), false); aItEdges.More();
           aItEdges.Next(), aNbEdges++)
      {
        const TopoDS_Shape& edge = aItEdges.Value();
        if (!aMapMultiConnectEdges.Contains(edge))
          continue;
        aNbMultEdges++;
      }
      if (!aNbMultEdges)
        continue;

      if (aNbMultEdges == aNbEdges)
        AddShapes.Append(aShape);
      else
        llPosibleShells.Append(aShape);
    }
  }

  NCollection_Sequence<TopoDS_Shape> aTmpShells;
  if (!llPosibleShells.IsEmpty())
  {
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                   aMap;
    NCollection_Sequence<TopoDS_Shape>                                       aTmp;
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aTmpFaceShell;
    if (GetShells(llPosibleShells, aMap, aTmpShells, aTmpFaceShell, aTmp))
    {
      for (int kk = 1; kk <= aTmpShells.Length(); kk++)
      {
        const TopoDS_Shape&                                    aSh = aTmpShells.Value(kk);
        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapEdges;
        if (GetFreeEdges(aSh, mapEdges))
        {
          int nbedge = 0;
          for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator amapIter(mapEdges);
               amapIter.More();
               amapIter.Next())
          {
            if (aMapMultiConnectEdges.Contains(amapIter.Key()))
              nbedge++;
          }
          if (nbedge && nbedge == mapEdges.Extent())
            AddShapes.Append(aSh);
        }
      }
    }
  }

  for (int k1 = 1; k1 <= AddShapes.Length(); k1++)
  {
    NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher> MapOtherShells;
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>          dire, reve;
    const TopoDS_Shape&                                             aSh = AddShapes.Value(k1);
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>          mapEdges;
    if (!GetFreeEdges(aSh, mapEdges))
      continue;
    NCollection_List<TopoDS_Shape> lfaces;

    for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator amapIter(mapEdges);
         amapIter.More();
         amapIter.Next())
    {
      if (!aMapMultiConnectEdges.Contains(amapIter.Key()))
        continue;
      TopoDS_Edge edge = TopoDS::Edge(amapIter.Key());
      if (edge.Orientation() == TopAbs_FORWARD)
        dire.Add(edge);
      else
        reve.Add(edge);
      NCollection_List<TopoDS_Shape> lf;
      lf = aMapEdgeFaces.FindFromKey(edge);
      lfaces.Append(lf);
    }
    for (NCollection_List<TopoDS_Shape>::Iterator aItl(lfaces); aItl.More(); aItl.Next())
    {
      TopoDS_Shape aF = aItl.Value();
      if (!aMapFaceShells.IsBound(aF))
        continue;

      TopoDS_Shape aOthershell;
      aOthershell = aMapFaceShells.Find(aF);
      if (MapOtherShells.IsBound(aOthershell))
        continue;
      if (!NonManifold && BRep_Tool::IsClosed(aOthershell))
        continue;

      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapShellEdges;
      GetFreeEdges(aOthershell, mapShellEdges);
      bool isAdd = true;
      for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator amapIter1(mapEdges);
           amapIter1.More() && isAdd;
           amapIter1.Next())
        isAdd = mapShellEdges.Contains(amapIter1.Key());

      if (!isAdd)
        continue;
      int nbdir = 0, nbrev = 0;

      for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aIte(mapShellEdges);
           aIte.More();
           aIte.Next())
      {
        TopoDS_Edge edgeS = TopoDS::Edge(aIte.Key());
        if (!aMapMultiConnectEdges.Contains(edgeS))
          continue;
        if ((edgeS.Orientation() == TopAbs_FORWARD && dire.Contains(edgeS))
            || (edgeS.Orientation() == TopAbs_REVERSED && reve.Contains(edgeS)))
          nbrev++;
        else if ((edgeS.Orientation() == TopAbs_FORWARD && reve.Contains(edgeS))
                 || (edgeS.Orientation() == TopAbs_REVERSED && dire.Contains(edgeS)))
          nbdir++;
      }
      if (nbdir && nbrev)
      {
        ErrFaces.Append(aSh);
        continue;
      }
      if (nbdir || nbrev)
      {
        int isReverse = (nbrev ? 1 : 0);
        MapOtherShells.Bind(aOthershell, isReverse);
      }
    }
    if (MapOtherShells.IsEmpty())
    {

      continue;
    }

    done         = true;
    int FirstRev = 0, FirstInd = 0;
    int ind = 0;
    for (int l = 1; l <= SeqShells.Length(); l++)
    {
      if (!MapOtherShells.IsBound(SeqShells.Value(l)))
        continue;
      ind++;
      int          isRev     = MapOtherShells.Find(SeqShells.Value(l));
      TopoDS_Shape anewShape = (isRev ? aSh.Reversed() : aSh);

      BRep_Builder aB1;
      TopoDS_Shape aShell = SeqShells.Value(l);
      if (ind == 1 || !NonManifold)
      {
        if (ind == 1)
        {
          FirstRev = isRev;
          FirstInd = l;
        }
        for (TopExp_Explorer aE(anewShape, TopAbs_FACE); aE.More(); aE.Next())
          aB1.Add(aShell, aE.Current());
        SeqShells.ChangeValue(l) = aShell;
      }
      else if (NonManifold)
      {
        bool isReversed = ((isRev) || FirstRev) && (!(isRev) || !FirstRev);
        aShell          = SeqShells.Value(FirstInd);
        for (TopoDS_Iterator aItF(SeqShells.Value(l), false); aItF.More(); aItF.Next())
        {
          TopoDS_Shape nF = (isReversed ? aItF.Value().Reversed() : aItF.Value());
          aB1.Add(aShell, nF);
        }
        SeqShells.ChangeValue(FirstInd) = aShell;
        SeqShells.Remove(l--);
      }
    }

    dire.Clear();
    reve.Clear();
    for (TopExp_Explorer aEt(aSh, TopAbs_FACE); aEt.More(); aEt.Next())
    {
      for (int kk = 1; kk <= Lface.Length(); kk++)
      {
        if (aEt.Current().IsSame(Lface.Value(kk)))
          Lface.Remove(kk--);
      }
    }
  }
  return done;
}

static int BoxIn(const Bnd_Box& theBox1, const Bnd_Box& theBox2)
{
  int    aNumIn = 0;
  double aXmin1, aYmin1, aXmax1, aYmax1, aXmin2, aYmin2, aXmax2, aYmax2, aZmin1, aZmax1, aZmin2,
    aZmax2;
  theBox1.Get(aXmin1, aYmin1, aZmin1, aXmax1, aYmax1, aZmax1);
  theBox2.Get(aXmin2, aYmin2, aZmin2, aXmax2, aYmax2, aZmax2);
  if (aXmin1 == aXmin2 && aXmax1 == aXmax2 && aYmin1 == aYmin2 && aYmax1 == aYmax2
      && aZmin1 == aZmin2 && aZmax1 == aZmax2)
    aNumIn = 0;
  else if (aXmin1 >= aXmin2 && aXmax1 <= aXmax2 && aYmin1 >= aYmin2 && aYmax1 <= aYmax2
           && aZmin1 >= aZmin2 && aZmax1 <= aZmax2)
    aNumIn = 1;
  else if (aXmin1 <= aXmin2 && aXmax1 >= aXmax2 && aYmin1 <= aYmin2 && aYmax1 >= aYmax2
           && aZmin1 <= aZmin2 && aZmax1 >= aZmax2)
    aNumIn = 2;
  return aNumIn;
}

static void GetClosedShells(NCollection_Sequence<TopoDS_Shape>& Shells,
                            NCollection_Sequence<TopoDS_Shape>& aRemainShells)
{
  NCollection_Array1<Bnd_Box> aBoxes(1, Shells.Length());
  for (int i = 1; i <= Shells.Length(); i++)
  {
    Bnd_Box Box;
    BRepBndLib::AddClose(Shells.Value(i), Box);
    aBoxes.SetValue(i, Box);
  }
  NCollection_Map<int> aMapNum;
  for (int j = 1; j <= aBoxes.Length(); j++)
  {
    for (int k = j + 1; k <= aBoxes.Length(); k++)
    {
      int NumIn = BoxIn(aBoxes.Value(j), aBoxes.Value(k));
      switch (NumIn)
      {
        case 1:
          aMapNum.Add(k);
          break;
        case 2:
          aMapNum.Add(j);
          break;
        default:
          break;
      }
    }
  }
  for (int i1 = 1; i1 <= Shells.Length(); i1++)
  {
    if (!aMapNum.Contains(i1))
      aRemainShells.Append(Shells.Value(i1));
  }
}

static void GlueClosedCandidate(
  NCollection_Sequence<TopoDS_Shape>&                           OpenShells,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapMultiConnectEdges,
  NCollection_Sequence<TopoDS_Shape>&                           aSeqNewShells)
{

  for (int i = 1; i < OpenShells.Length(); i++)
  {
    TopoDS_Shape                                           aShell = OpenShells.Value(i);
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapEdges1;
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> dire, reve;
    if (!GetFreeEdges(aShell, mapEdges1))
      continue;

    for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aIte(mapEdges1);
         aIte.More();
         aIte.Next())
    {
      TopoDS_Edge edge1 = TopoDS::Edge(aIte.Key());
      if (!aMapMultiConnectEdges.Contains(edge1))
        break;
      if (edge1.Orientation() == TopAbs_FORWARD)
        dire.Add(edge1);
      else if (edge1.Orientation() == TopAbs_REVERSED)
        reve.Add(edge1);
    }
    if (mapEdges1.Extent() > (dire.Extent() + reve.Extent()))
      continue;

    NCollection_DataMap<TopoDS_Shape, bool, TopTools_ShapeMapHasher> MapOtherShells;
    for (int j = i + 1; j <= OpenShells.Length(); j++)
    {
      bool                                                   isAddShell = true;
      bool                                                   isReversed = false;
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapEdges2;
      const TopoDS_Shape&                                    aShell2 = OpenShells.Value(j);
      if (!GetFreeEdges(aShell2, mapEdges2))
        continue;
      for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aIte2(mapEdges2);
           aIte2.More() && isAddShell;
           aIte2.Next())
      {
        TopoDS_Edge edge2 = TopoDS::Edge(aIte2.Key());
        if (!aMapMultiConnectEdges.Contains(edge2))
        {
          isAddShell = false;
          break;
        }
        isAddShell = (dire.Contains(edge2) || reve.Contains(edge2));
        if ((edge2.Orientation() == TopAbs_FORWARD && dire.Contains(edge2))
            || (edge2.Orientation() == TopAbs_REVERSED && reve.Contains(edge2)))
          isReversed = true;
      }

      if (!isAddShell)
        continue;
      MapOtherShells.Bind(OpenShells.Value(j), isReversed);
    }
    if (MapOtherShells.IsEmpty())
      continue;

    if (!MapOtherShells.IsEmpty())
    {

      NCollection_Sequence<TopoDS_Shape> aSeqCandidate;
      aSeqCandidate.Append(OpenShells.Value(i));

      for (NCollection_DataMap<TopoDS_Shape, bool, TopTools_ShapeMapHasher>::Iterator aIt(
             MapOtherShells);
           aIt.More();
           aIt.Next())
      {
        aSeqCandidate.Append(aIt.Key());
      }

      NCollection_Sequence<TopoDS_Shape> aTmpSeq;
      for (int k = 1; k <= aSeqCandidate.Length(); k++)
      {

        for (int l = k + 1; l <= aSeqCandidate.Length(); l++)
        {
          TopoDS_Shell aNewSh;
          BRep_Builder aB;
          aB.MakeShell(aNewSh);
          for (TopoDS_Iterator aIt1(aSeqCandidate.Value(k), false); aIt1.More(); aIt1.Next())
            aB.Add(aNewSh, aIt1.Value());
          bool isRev = MapOtherShells.Find(aSeqCandidate.Value(l));
          if (k != 1)
          {
            isRev = (isRev == MapOtherShells.Find(aSeqCandidate.Value(k)));
          }
          for (TopExp_Explorer aExp(aSeqCandidate.Value(l), TopAbs_FACE); aExp.More(); aExp.Next())
          {
            TopoDS_Shape aFace = (isRev ? aExp.Current().Reversed() : aExp.Current());
            aB.Add(aNewSh, aFace);
          }
          aTmpSeq.Append(aNewSh);
        }
      }

      NCollection_Sequence<TopoDS_Shape> aRemainShells;
      GetClosedShells(aTmpSeq, aRemainShells);
      aSeqNewShells.Append(aRemainShells);

      for (int j1 = i + 1; j1 <= OpenShells.Length(); j1++)
      {
        if (!MapOtherShells.IsBound(OpenShells.Value(j1)))
          continue;
        OpenShells.Remove(j1--);
      }
    }
    else
    {
      BRep_Builder aB;
      TopoDS_Shape aNewShell = aShell;
      TopoDS_Shape addShell;
      bool         isReversed = false;
      for (int j1 = i + 1; j1 <= OpenShells.Length(); j1++)
      {
        if (!MapOtherShells.Find(OpenShells.Value(j1), isReversed))
          continue;
        addShell = OpenShells.Value(j1);
        OpenShells.Remove(j1);
        break;
      }

      for (TopExp_Explorer aExpF(addShell, TopAbs_FACE); aExpF.More(); aExpF.Next())
      {
        TopoDS_Shape aFace = aExpF.Current();
        if (isReversed)
          aFace.Reverse();
        aB.Add(aNewShell, aFace);
      }
      aSeqNewShells.Append(aNewShell);
    }

    OpenShells.Remove(i--);
  }
}

static void CreateNonManifoldShells(
  NCollection_Sequence<TopoDS_Shape>&                           SeqShells,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapMultiConnectEdges)
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMap;
  for (int i = 1; i <= SeqShells.Length(); i++)
  {
    const TopoDS_Shape&                                           aShell = SeqShells.Value(i);
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> medeg;
    TopExp::MapShapes(aShell, TopAbs_EDGE, medeg);
    for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator mit(
           aMapMultiConnectEdges);
         mit.More();
         mit.Next())
    {

      const TopoDS_Shape& ae = mit.Key();

      if (medeg.Contains(ae))
      {
        if (aMap.Contains(ae))
          aMap.ChangeFromKey(ae).Append(aShell);
        else
        {
          NCollection_List<TopoDS_Shape> al;
          al.Append(aShell);
          aMap.Add(ae, al);
        }
      }
    }
  }
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aMapShells;
  for (int j = 1; j <= aMap.Extent(); j++)
  {
    const NCollection_List<TopoDS_Shape>& LShells = aMap.FindFromIndex(j);
    TopoDS_Shell                          aNewShell;
    BRep_Builder                          aB;
    aB.MakeShell(aNewShell);
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapmerge;
    bool                                                   ismerged = false;
    int                                                    num      = 1;
    for (NCollection_List<TopoDS_Shape>::Iterator alit(LShells); alit.More(); alit.Next(), num++)
    {
      if (!aMapShells.Contains(alit.Value()))
      {
        for (TopExp_Explorer aEf(alit.Value(), TopAbs_FACE); aEf.More(); aEf.Next())
        {
          aB.Add(aNewShell, aEf.Current());
        }
        ismerged = true;
        mapmerge.Add(alit.Value());
      }
      else if (ismerged)
      {
        TopoDS_Shape arshell = aMapShells.FindFromKey(alit.Value());
        while (aMapShells.Contains(arshell))
        {
          const TopoDS_Shape& ss = aMapShells.FindFromKey(arshell);
          if (ss.IsSame(arshell))
            break;
          arshell = ss;
        }

        if (!mapmerge.Contains(arshell))
        {
          for (TopExp_Explorer aEf(arshell, TopAbs_FACE); aEf.More(); aEf.Next())
          {
            aB.Add(aNewShell, aEf.Current());
          }
          mapmerge.Add(arshell);
        }
      }
      else
      {
        TopoDS_Shape arshell = aMapShells.FindFromKey(alit.Value());
        while (aMapShells.Contains(arshell))
        {
          const TopoDS_Shape& ss = aMapShells.FindFromKey(arshell);
          if (ss.IsSame(arshell))
            break;
          arshell = ss;
        }
        if (num == 1)
        {
          for (TopExp_Explorer aEf(arshell, TopAbs_FACE); aEf.More(); aEf.Next())
            aB.Add(aNewShell, aEf.Current());

          mapmerge.Add(arshell);
        }
        else if (!mapmerge.Contains(arshell))
        {
          for (TopExp_Explorer aEf(arshell, TopAbs_FACE); aEf.More(); aEf.Next())
          {
            aB.Add(aNewShell, aEf.Current());
          }
          mapmerge.Add(arshell);
        }
      }
    }
    if (mapmerge.Extent() > 1 || ismerged)
    {
      for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator alit1(mapmerge);
           alit1.More();
           alit1.Next())
      {
        const TopoDS_Shape& oldShell = alit1.Key();

        aMapShells.Add(oldShell, aNewShell);
      }
    }
  }
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MapNewShells;
  for (int nn = 1; nn <= SeqShells.Length(); nn++)
  {
    if (aMapShells.Contains(SeqShells.Value(nn)))
    {
      TopoDS_Shape aNewShell = aMapShells.FindFromKey(SeqShells.Value(nn));
      while (aMapShells.Contains(aNewShell))
      {
        const TopoDS_Shape& ss = aMapShells.FindFromKey(aNewShell);
        if (ss.IsSame(aNewShell))
          break;
        aNewShell = ss;
      }
      MapNewShells.Add(aNewShell);

      SeqShells.Remove(nn--);
    }
  }
  for (int ii = 1; ii <= MapNewShells.Extent(); ii++)
    SeqShells.Append(MapNewShells.FindKey(ii));
}

static void CreateClosedShell(
  NCollection_Sequence<TopoDS_Shape>&                           OpenShells,
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapMultiConnectEdges)
{
  NCollection_Sequence<TopoDS_Shape> aNewShells;

  GlueClosedCandidate(OpenShells, aMapMultiConnectEdges, aNewShells);

  for (int i = 1; i < OpenShells.Length(); i++)
  {
    bool         isAddShell = false;
    TopoDS_Shape aShell     = OpenShells.Value(i);
    bool         isReversed = false;
    for (int j = i + 1; j <= OpenShells.Length(); j++)
    {
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapEdges1;
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> dire, reve;
      if (!GetFreeEdges(aShell, mapEdges1))
        break;
      for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aIte(mapEdges1);
           aIte.More();
           aIte.Next())
      {
        TopoDS_Edge edge1 = TopoDS::Edge(aIte.Key());
        if (!aMapMultiConnectEdges.Contains(edge1))
          continue;
        if (edge1.Orientation() == TopAbs_FORWARD)
          dire.Add(edge1);
        else if (edge1.Orientation() == TopAbs_REVERSED)
          reve.Add(edge1);
      }
      if (dire.IsEmpty() && reve.IsEmpty())
        break;
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapEdges2;
      TopoDS_Shape                                           aShell2 = OpenShells.Value(j);
      if (!GetFreeEdges(aShell2, mapEdges2))
        continue;
      for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aIte2(mapEdges2);
           aIte2.More();
           aIte2.Next())
      {
        TopoDS_Edge edge2 = TopoDS::Edge(aIte2.Key());
        if (!aMapMultiConnectEdges.Contains(edge2))
          continue;
        if (!dire.Contains(edge2) && !reve.Contains(edge2))
          continue;
        isAddShell = true;
        if ((edge2.Orientation() == TopAbs_FORWARD && dire.Contains(edge2))
            || (edge2.Orientation() == TopAbs_REVERSED && reve.Contains(edge2)))
          isReversed = true;
      }

      if (!isAddShell)
        continue;
      BRep_Builder aB;

      for (TopExp_Explorer aExpF21(OpenShells.Value(j), TopAbs_FACE); aExpF21.More();
           aExpF21.Next())
      {
        TopoDS_Shape aFace = aExpF21.Current();
        if (isReversed)
          aFace.Reverse();
        aB.Add(aShell, aFace);
      }

      OpenShells.ChangeValue(i) = aShell;
      OpenShells.Remove(j--);
    }
  }

  OpenShells.Append(aNewShells);
}

bool ShapeFix_Shell::FixFaceOrientation(const TopoDS_Shell& shell,
                                        const bool          isAccountMultiConex,
                                        const bool          NonManifold)
{

  bool                                                                     done = false;
  NCollection_Sequence<TopoDS_Shape>                                       aSeqShells;
  NCollection_Sequence<TopoDS_Shape>                                       aErrFaces;
  NCollection_Sequence<TopoDS_Shape>                                       Lface;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aMapFaceShells;
  myShell                                                              = shell;
  myShape                                                              = shell;
  int                                                    aNumMultShell = 0;
  int                                                    nbF           = 0;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMapAdded;
  for (TopoDS_Iterator iter(shell); iter.More(); iter.Next(), nbF++)
  {
    if (aMapAdded.Add(iter.Value()))
      Lface.Append(iter.Value());
  }
  if (Lface.Length() < nbF)
    done = true;

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMapEdgeFaces;
  TopExp::MapShapesAndAncestors(myShell, TopAbs_EDGE, TopAbs_FACE, aMapEdgeFaces);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMapMultiConnectEdges;
  bool                                                   isFreeBoundaries = false;
  for (int k = 1; k <= aMapEdgeFaces.Extent(); k++)
  {
    const int aFaceCount = aMapEdgeFaces.FindFromIndex(k).Extent();
    if (!isFreeBoundaries && aFaceCount == 1)
    {
      TopoDS_Edge E = TopoDS::Edge(aMapEdgeFaces.FindKey(k));
      if (!BRep_Tool::Degenerated(E))
        isFreeBoundaries = true;
    }

    else if (isAccountMultiConex && aFaceCount > 2)
      aMapMultiConnectEdges.Add(aMapEdgeFaces.FindKey(k));
  }
  if (BRep_Tool::IsClosed(myShell) ? isFreeBoundaries : !isFreeBoundaries)
  {
    myShell.Closed(!isFreeBoundaries);

    SendWarning(Message_Msg("FixAdvShell.FixClosedFlag.MSG0"));
  }
  bool isGetShells = true;

  while (isGetShells && Lface.Length())
  {
    NCollection_Sequence<TopoDS_Shape> aTmpSeqShells;
    if (GetShells(Lface, aMapMultiConnectEdges, aTmpSeqShells, aMapFaceShells, aErrFaces))
    {
      done = true;
    }
    isGetShells = !aTmpSeqShells.IsEmpty();
    if (isGetShells)
      aSeqShells.Append(aTmpSeqShells);
  }
  if (!done)
    done = (aSeqShells.Length() > 1);
  bool aIsDone = false;
  if (Lface.Length() > 0 && aSeqShells.Length())
  {
    for (int jj = 1; jj <= Lface.Length(); jj++)
    {
      if (aMapFaceShells.IsBound(Lface.Value(jj)))
        aMapFaceShells.UnBind(Lface.Value(jj));
    }

    aIsDone = AddMultiConexityFaces(Lface,
                                    aMapMultiConnectEdges,
                                    aSeqShells,
                                    aMapFaceShells,
                                    aMapEdgeFaces,
                                    aErrFaces,
                                    NonManifold);
  }
  aNumMultShell = aSeqShells.Length();
  if (!aErrFaces.IsEmpty())
  {

    BRep_Builder B;
    B.MakeCompound(myErrFaces);
    TopoDS_Compound aCompShells;
    B.MakeCompound(aCompShells);
    for (int n = 1; n <= aErrFaces.Length(); n++)
      B.Add(myErrFaces, aErrFaces.Value(n));
    if (aNumMultShell)
    {
      if (aNumMultShell == 1)
      {
        B.Add(aCompShells, aSeqShells.Value(1));
        for (int n1 = 1; n1 <= aErrFaces.Length(); n1++)
        {
          TopoDS_Shell aSh;
          B.MakeShell(aSh);
          B.Add(aSh, aErrFaces.Value(n1));
          B.Add(aCompShells, aSh);
        }
        myShape = aCompShells;
      }
      else
      {
        for (int i = 1; i <= aSeqShells.Length(); i++)
          B.Add(aCompShells, aSeqShells.Value(i));
        for (int n1 = 1; n1 <= aErrFaces.Length(); n1++)
        {
          TopoDS_Shell aSh;
          B.MakeShell(aSh);
          B.Add(aSh, aErrFaces.Value(n1));
          B.Add(aCompShells, aSh);
        }
        myShape = aCompShells;
      }
    }

    done     = true;
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_FAIL);

    SendWarning(Message_Msg("FixAdvShell.FixOrientation.MSG20"));

    return true;
  }
  if (aNumMultShell > 1)
  {
    NCollection_Sequence<TopoDS_Shape> OpenShells;
    for (int i1 = 1; i1 <= aSeqShells.Length(); i1++)
    {
      TopoDS_Shape aShell = aSeqShells.Value(i1);
      if (!BRep_Tool::IsClosed(aShell))
      {
        OpenShells.Append(aShell);
        aSeqShells.Remove(i1--);
      }
    }
    if (OpenShells.Length() > 1)

      CreateClosedShell(OpenShells, aMapMultiConnectEdges);
    aSeqShells.Append(OpenShells);
  }

  if (Lface.Length())
  {

    for (int i = 1; i <= Lface.Length(); i++)
    {
      BRep_Builder aB;
      TopoDS_Shell OneShell;
      aB.MakeShell(OneShell);
      aB.Add(OneShell, Lface.Value(i));
      aSeqShells.Append(OneShell);
    }
  }
  if (NonManifold && aSeqShells.Length() > 1)
  {
    CreateNonManifoldShells(aSeqShells, aMapMultiConnectEdges);
  }
  if (!done)
    done = (aSeqShells.Length() > 1 || aIsDone);
  if (aSeqShells.Length() == 1)
  {
    myShell    = TopoDS::Shell(aSeqShells.Value(1));
    myShape    = myShell;
    myNbShells = 1;
  }
  else
  {
    BRep_Builder    B;
    TopoDS_Compound aCompShells;
    B.MakeCompound(aCompShells);
    for (int i = 1; i <= aSeqShells.Length(); i++)
      B.Add(aCompShells, aSeqShells.Value(i));
    myShape    = aCompShells;
    myNbShells = aSeqShells.Length();
  }
  if (done)
  {
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
    if (!Context().IsNull())
      Context()->Replace(shell, myShape);
    if (myNbShells == 1)

      SendWarning(Message_Msg("FixAdvShell.FixOrientation.MSG0"));
    else
      SendWarning(Message_Msg("FixAdvShell.FixOrientation.MSG30"));

    return true;
  }
  else
    return false;
}

bool ShapeFix_Shell::Status(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatus, status);
}

TopoDS_Shell ShapeFix_Shell::Shell()
{
  return myShell;
}

TopoDS_Shape ShapeFix_Shell::Shape()
{
  return myShape;
}

TopoDS_Compound ShapeFix_Shell::ErrorFaces() const
{
  return myErrFaces;
}

void ShapeFix_Shell::SetMsgRegistrator(const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg)
{
  ShapeFix_Root::SetMsgRegistrator(msgreg);
  myFixFace->SetMsgRegistrator(msgreg);
}

void ShapeFix_Shell::SetPrecision(const double preci)
{
  ShapeFix_Root::SetPrecision(preci);
  myFixFace->SetPrecision(preci);
}

void ShapeFix_Shell::SetMinTolerance(const double mintol)
{
  ShapeFix_Root::SetMinTolerance(mintol);
  myFixFace->SetMinTolerance(mintol);
}

void ShapeFix_Shell::SetMaxTolerance(const double maxtol)
{
  ShapeFix_Root::SetMaxTolerance(maxtol);
  myFixFace->SetMaxTolerance(maxtol);
}

int ShapeFix_Shell::NbShells() const
{
  return myNbShells;
}

void ShapeFix_Shell::SetNonManifoldFlag(const bool isNonManifold)
{
  myNonManifold = isNonManifold;
}
