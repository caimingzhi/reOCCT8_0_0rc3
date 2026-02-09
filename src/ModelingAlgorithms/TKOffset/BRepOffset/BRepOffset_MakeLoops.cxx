#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRep_TVertex.hpp>
#include <BRepAlgo_AsDes.hpp>
#include <BRepAlgo_Loop.hpp>
#include <BRepOffset_Analyse.hpp>
#include <BRepOffset_MakeLoops.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

#include <cstdio>

BRepOffset_MakeLoops::BRepOffset_MakeLoops() = default;

void BRepOffset_MakeLoops::Build(const NCollection_List<TopoDS_Shape>& LF,
                                 const occ::handle<BRepAlgo_AsDes>&    AsDes,
                                 BRepAlgo_Image&                       Image,
                                 BRepAlgo_Image&                       theImageVV,
                                 const Message_ProgressRange&          theRange)
{
  NCollection_List<TopoDS_Shape>::Iterator it(LF);
  NCollection_List<TopoDS_Shape>::Iterator itl, itLCE;
  BRepAlgo_Loop                            Loops;
  Loops.VerticesForSubstitute(myVerVerMap);
  Loops.SetImageVV(theImageVV);
  Message_ProgressScope aPSOuter(theRange, nullptr, 2);
  Message_ProgressScope aPS1(aPSOuter.Next(), "Init loops", LF.Size());
  for (; it.More(); it.Next(), aPS1.Next())
  {
    if (!aPS1.More())
    {
      return;
    }
    const TopoDS_Face& F = TopoDS::Face(it.Value());

    Loops.Init(F);

    const NCollection_List<TopoDS_Shape>& LE = AsDes->Descendant(F);
    NCollection_List<TopoDS_Shape>        AddedEdges;

    for (itl.Initialize(LE); itl.More(); itl.Next())
    {
      TopoDS_Edge E = TopoDS::Edge(itl.Value());
      if (Image.HasImage(E))
      {

        const NCollection_List<TopoDS_Shape>& LCE = Image.Image(E);
        for (itLCE.Initialize(LCE); itLCE.More(); itLCE.Next())
        {
          TopoDS_Shape CE = itLCE.Value().Oriented(E.Orientation());
          Loops.AddConstEdge(TopoDS::Edge(CE));
        }
      }
      else
      {
        Loops.AddEdge(E, AsDes->Descendant(E));
        AddedEdges.Append(E);
      }
    }

    Loops.Perform();
    Loops.WiresToFaces();

    const NCollection_List<TopoDS_Shape>& NF = Loops.NewFaces();

    Image.Bind(F, NF);

    NCollection_List<TopoDS_Shape>::Iterator itAdded;
    for (itAdded.Initialize(AddedEdges); itAdded.More(); itAdded.Next())
    {
      const TopoDS_Edge& E = TopoDS::Edge(itAdded.Value());

      const NCollection_List<TopoDS_Shape>& LoopNE = Loops.NewEdges(E);
      if (Image.HasImage(E))
      {
        Image.Add(E, LoopNE);
      }
      else
      {
        Image.Bind(E, LoopNE);
      }
    }
  }
  Loops.GetVerticesForSubstitute(myVerVerMap);
  if (myVerVerMap.IsEmpty())
    return;
  BRep_Builder          BB;
  Message_ProgressScope aPS2(aPSOuter.Next(), "Building loops", LF.Size());
  for (it.Initialize(LF); it.More(); it.Next(), aPS2.Next())
  {
    if (!aPS2.More())
    {
      return;
    }
    TopoDS_Shape                   F = it.Value();
    NCollection_List<TopoDS_Shape> LIF;
    Image.LastImage(F, LIF);
    for (itl.Initialize(LIF); itl.More(); itl.Next())
    {
      const TopoDS_Shape& IF = itl.Value();
      TopExp_Explorer     EdExp(IF, TopAbs_EDGE);
      for (; EdExp.More(); EdExp.Next())
      {
        TopoDS_Shape                   E = EdExp.Current();
        NCollection_List<TopoDS_Shape> VList;
        TopoDS_Iterator                VerExp(E);
        for (; VerExp.More(); VerExp.Next())
          VList.Append(VerExp.Value());
        NCollection_List<TopoDS_Shape>::Iterator itlv(VList);
        for (; itlv.More(); itlv.Next())
        {
          const TopoDS_Shape& V = itlv.Value();
          if (myVerVerMap.IsBound(V))
          {
            TopoDS_Shape NewV = myVerVerMap(V);
            E.Free(true);
            NewV.Orientation(V.Orientation());
            occ::handle<BRep_TVertex>& TV    = *((occ::handle<BRep_TVertex>*)&V.TShape());
            occ::handle<BRep_TVertex>& NewTV = *((occ::handle<BRep_TVertex>*)&NewV.TShape());
            if (TV->Tolerance() > NewTV->Tolerance())
              NewTV->Tolerance(TV->Tolerance());
            NewTV->ChangePoints().Append(TV->ChangePoints());
            AsDes->Replace(V, NewV);
            BB.Remove(E, V);
            BB.Add(E, NewV);
          }
        }
      }
    }
  }
}

static bool IsBetweenCorks(const TopoDS_Shape&                   E,
                           const occ::handle<BRepAlgo_AsDes>&    AsDes,
                           const NCollection_List<TopoDS_Shape>& LContext)
{
  if (!AsDes->HasAscendant(E))
    return true;
  const NCollection_List<TopoDS_Shape>&    LF = AsDes->Ascendant(E);
  NCollection_List<TopoDS_Shape>::Iterator it;
  for (it.Initialize(LF); it.More(); it.Next())
  {
    const TopoDS_Shape&                      S     = it.Value();
    bool                                     found = false;
    NCollection_List<TopoDS_Shape>::Iterator it2;
    for (it2.Initialize(LContext); it2.More(); it2.Next())
    {
      if (S.IsSame(it2.Value()))
      {
        found = true;
        break;
      }
    }
    if (!found)
      return false;
  }
  return true;
}

void BRepOffset_MakeLoops::BuildOnContext(const NCollection_List<TopoDS_Shape>& LContext,
                                          const BRepOffset_Analyse&             Analyse,
                                          const occ::handle<BRepAlgo_AsDes>&    AsDes,
                                          BRepAlgo_Image&                       Image,
                                          const bool                            InSide,
                                          const Message_ProgressRange&          theRange)
{

  NCollection_List<TopoDS_Shape>::Iterator it(LContext);
  NCollection_List<TopoDS_Shape>::Iterator itl, itLCE;
  BRepAlgo_Loop                            Loops;
  Loops.VerticesForSubstitute(myVerVerMap);
  TopExp_Explorer                                        exp;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> MapExtent;

  Message_ProgressScope aPS(theRange, "Building deepening faces", LContext.Extent());
  for (; it.More(); it.Next(), aPS.Next())
  {
    if (!aPS.More())
    {
      return;
    }
    const TopoDS_Face&                                     F = TopoDS::Face(it.Value());
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> MBound;

    TopoDS_Shape aReversedF = F.Reversed();
    if (InSide)
      Loops.Init(TopoDS::Face(aReversedF));

    else
      Loops.Init(F);

    for (exp.Init(F.Oriented(TopAbs_FORWARD), TopAbs_EDGE); exp.More(); exp.Next())
    {
      TopoDS_Edge CE = TopoDS::Edge(exp.Current());
      MBound.Add(CE);
      if (Analyse.HasAncestor(CE))
      {

        TopoDS_Shape aReversedE = CE.Reversed();
        if (InSide)
          Loops.AddConstEdge(CE);
        else
          Loops.AddConstEdge(TopoDS::Edge(aReversedE));
      }
    }

    const NCollection_List<TopoDS_Shape>& LE = AsDes->Descendant(F);
    NCollection_List<TopoDS_Shape>        AddedEdges;

    for (itl.Initialize(LE); itl.More(); itl.Next())
    {
      TopoDS_Edge E = TopoDS::Edge(itl.Value());
      if (Image.HasImage(E))
      {

        const NCollection_List<TopoDS_Shape>& LCE = Image.Image(E);
        for (itLCE.Initialize(LCE); itLCE.More(); itLCE.Next())
        {
          TopoDS_Shape CE = itLCE.Value().Oriented(E.Orientation());
          if (MapExtent.Contains(E))
          {
            Loops.AddConstEdge(TopoDS::Edge(CE));
            continue;
          }
          if (!MBound.Contains(E))
            CE.Reverse();
          if (InSide)
            Loops.AddConstEdge(TopoDS::Edge(CE));
          else
          {
            TopoDS_Shape aReversedE = CE.Reversed();
            Loops.AddConstEdge(TopoDS::Edge(aReversedE));
          }
        }
      }
      else
      {
        if (IsBetweenCorks(E, AsDes, LContext) && AsDes->HasDescendant(E))
        {

          MapExtent.Add(E);
          NCollection_List<TopoDS_Shape> LV;
          if (InSide)
          {
            for (itLCE.Initialize(AsDes->Descendant(E)); itLCE.More(); itLCE.Next())
            {
              LV.Append(itLCE.Value().Reversed());
            }
            Loops.AddEdge(E, LV);
          }
          else
          {
            Loops.AddEdge(E, AsDes->Descendant(E));
          }
          AddedEdges.Append(E);
        }
        else if (IsBetweenCorks(E, AsDes, LContext))
        {
          TopoDS_Shape aLocalShape = E.Reversed();
          if (InSide)
            Loops.AddConstEdge(E);
          else
            Loops.AddConstEdge(TopoDS::Edge(aLocalShape));
        }
        else
        {
          TopoDS_Shape aLocalShape = E.Reversed();
          if (InSide)
            Loops.AddConstEdge(TopoDS::Edge(aLocalShape));
          else
            Loops.AddConstEdge(E);
        }
      }
    }

    Loops.Perform();
    Loops.WiresToFaces();

    const NCollection_List<TopoDS_Shape>& NF = Loops.NewFaces();

    Image.Bind(F, NF);

    NCollection_List<TopoDS_Shape>::Iterator itAdded;
    for (itAdded.Initialize(AddedEdges); itAdded.More(); itAdded.Next())
    {
      const TopoDS_Edge& E = TopoDS::Edge(itAdded.Value());

      if (Image.HasImage(E))
      {
        Image.Add(E, Loops.NewEdges(E));
      }
      else
      {
        Image.Bind(E, Loops.NewEdges(E));
      }
    }
  }
  Loops.GetVerticesForSubstitute(myVerVerMap);
  if (myVerVerMap.IsEmpty())
    return;
  BRep_Builder BB;
  for (it.Initialize(LContext); it.More(); it.Next())
  {
    TopoDS_Shape                   F = it.Value();
    NCollection_List<TopoDS_Shape> LIF;
    Image.LastImage(F, LIF);
    for (itl.Initialize(LIF); itl.More(); itl.Next())
    {
      const TopoDS_Shape& IF = itl.Value();
      TopExp_Explorer     EdExp(IF, TopAbs_EDGE);
      for (; EdExp.More(); EdExp.Next())
      {
        TopoDS_Shape                   E = EdExp.Current();
        NCollection_List<TopoDS_Shape> VList;
        TopoDS_Iterator                VerExp(E);
        for (; VerExp.More(); VerExp.Next())
          VList.Append(VerExp.Value());
        NCollection_List<TopoDS_Shape>::Iterator itlv(VList);
        for (; itlv.More(); itlv.Next())
        {
          const TopoDS_Shape& V = itlv.Value();
          if (myVerVerMap.IsBound(V))
          {
            TopoDS_Shape NewV = myVerVerMap(V);
            E.Free(true);
            NewV.Orientation(V.Orientation());
            occ::handle<BRep_TVertex>& TV    = *((occ::handle<BRep_TVertex>*)&V.TShape());
            occ::handle<BRep_TVertex>& NewTV = *((occ::handle<BRep_TVertex>*)&NewV.TShape());
            if (TV->Tolerance() > NewTV->Tolerance())
              NewTV->Tolerance(TV->Tolerance());
            NewTV->ChangePoints().Append(TV->ChangePoints());
            AsDes->Replace(V, NewV);
            BB.Remove(E, V);
            BB.Add(E, NewV);
          }
        }
      }
    }
  }
}

void BRepOffset_MakeLoops::BuildFaces(const NCollection_List<TopoDS_Shape>& LF,
                                      const occ::handle<BRepAlgo_AsDes>&    AsDes,
                                      BRepAlgo_Image&                       Image,
                                      const Message_ProgressRange&          theRange)
{
  NCollection_List<TopoDS_Shape>::Iterator itr, itl, itLCE;
  bool                                     ToRebuild;
  BRepAlgo_Loop                            Loops;
  Loops.VerticesForSubstitute(myVerVerMap);
  BRep_Builder B;

  Message_ProgressScope aPS(theRange, "Building faces", LF.Size());
  for (itr.Initialize(LF); itr.More(); itr.Next(), aPS.Next())
  {
    if (!aPS.More())
    {
      return;
    }
    TopoDS_Face F = TopoDS::Face(itr.Value());
    Loops.Init(F);
    ToRebuild = false;
    NCollection_List<TopoDS_Shape> AddedEdges;

    if (!Image.HasImage(F))
    {

      const NCollection_List<TopoDS_Shape>& LE = AsDes->Descendant(F);

      NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> MONV;
      TopoDS_Vertex                                                            OV1, OV2, NV1, NV2;

      for (itl.Initialize(LE); itl.More(); itl.Next())
      {
        TopoDS_Edge E = TopoDS::Edge(itl.Value());
        if (Image.HasImage(E))
        {
          const NCollection_List<TopoDS_Shape>& LCE = Image.Image(E);
          if (LCE.Extent() == 1 && LCE.First().IsSame(E))
          {
            TopoDS_Shape aLocalShape = LCE.First().Oriented(E.Orientation());
            TopoDS_Edge  CE          = TopoDS::Edge(aLocalShape);

            Loops.AddConstEdge(CE);
            continue;
          }

          ToRebuild = true;
          for (itLCE.Initialize(LCE); itLCE.More(); itLCE.Next())
          {
            TopoDS_Shape aLocalShape = itLCE.Value().Oriented(E.Orientation());
            TopoDS_Edge  CE          = TopoDS::Edge(aLocalShape);

            TopExp::Vertices(E, OV1, OV2);
            TopExp::Vertices(CE, NV1, NV2);
            if (!OV1.IsSame(NV1))
              MONV.Bind(OV1, NV1);
            if (!OV2.IsSame(NV2))
              MONV.Bind(OV2, NV2);
            Loops.AddConstEdge(CE);
          }
        }
      }
      if (ToRebuild)
      {

        for (itl.Initialize(LE); itl.More(); itl.Next())
        {
          double      f, l;
          TopoDS_Edge E = TopoDS::Edge(itl.Value());
          BRep_Tool::Range(E, f, l);
          if (!Image.HasImage(E))
          {
            TopExp::Vertices(E, OV1, OV2);
            NCollection_List<TopoDS_Shape> LV;
            if (MONV.IsBound(OV1))
            {
              TopoDS_Vertex VV = TopoDS::Vertex(MONV(OV1));
              VV.Orientation(TopAbs_FORWARD);
              LV.Append(VV);
              TopoDS_Shape aLocalShape = VV.Oriented(TopAbs_INTERNAL);
              B.UpdateVertex(TopoDS::Vertex(aLocalShape), f, E, BRep_Tool::Tolerance(VV));
            }
            if (MONV.IsBound(OV2))
            {
              TopoDS_Vertex VV = TopoDS::Vertex(MONV(OV2));
              VV.Orientation(TopAbs_REVERSED);
              LV.Append(VV);
              TopoDS_Shape aLocalShape = VV.Oriented(TopAbs_INTERNAL);
              B.UpdateVertex(TopoDS::Vertex(aLocalShape), l, E, BRep_Tool::Tolerance(VV));
            }
            if (LV.IsEmpty())
              Loops.AddConstEdge(E);
            else
            {
              Loops.AddEdge(E, LV);
              AddedEdges.Append(E);
            }
          }
        }
      }
    }
    if (ToRebuild)
    {

      Loops.Perform();
      Loops.WiresToFaces();

      const NCollection_List<TopoDS_Shape>& NF = Loops.NewFaces();

      Image.Bind(F, NF);

      NCollection_List<TopoDS_Shape>::Iterator itAdded;
      for (itAdded.Initialize(AddedEdges); itAdded.More(); itAdded.Next())
      {
        const TopoDS_Edge& E = TopoDS::Edge(itAdded.Value());

        if (Image.HasImage(E))
        {
          Image.Add(E, Loops.NewEdges(E));
        }
        else
        {
          Image.Bind(E, Loops.NewEdges(E));
        }
      }
    }
  }
  Loops.GetVerticesForSubstitute(myVerVerMap);
  if (myVerVerMap.IsEmpty())
    return;
  BRep_Builder BB;
  for (itr.Initialize(LF); itr.More(); itr.Next())
  {
    TopoDS_Shape                   F = itr.Value();
    NCollection_List<TopoDS_Shape> LIF;
    Image.LastImage(F, LIF);
    for (itl.Initialize(LIF); itl.More(); itl.Next())
    {
      const TopoDS_Shape& IF = itl.Value();
      TopExp_Explorer     EdExp(IF, TopAbs_EDGE);
      for (; EdExp.More(); EdExp.Next())
      {
        TopoDS_Shape                   E = EdExp.Current();
        NCollection_List<TopoDS_Shape> VList;
        TopoDS_Iterator                VerExp(E);
        for (; VerExp.More(); VerExp.Next())
          VList.Append(VerExp.Value());
        NCollection_List<TopoDS_Shape>::Iterator itlv(VList);
        for (; itlv.More(); itlv.Next())
        {
          const TopoDS_Shape& V = itlv.Value();
          if (myVerVerMap.IsBound(V))
          {
            TopoDS_Shape NewV = myVerVerMap(V);
            E.Free(true);
            NewV.Orientation(V.Orientation());
            occ::handle<BRep_TVertex>& TV    = *((occ::handle<BRep_TVertex>*)&V.TShape());
            occ::handle<BRep_TVertex>& NewTV = *((occ::handle<BRep_TVertex>*)&NewV.TShape());
            if (TV->Tolerance() > NewTV->Tolerance())
              NewTV->Tolerance(TV->Tolerance());
            NewTV->ChangePoints().Append(TV->ChangePoints());
            AsDes->Replace(V, NewV);
            BB.Remove(E, V);
            BB.Add(E, NewV);
          }
        }
      }
    }
  }
}
