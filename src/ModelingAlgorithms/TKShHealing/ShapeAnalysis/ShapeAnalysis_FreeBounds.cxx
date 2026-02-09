#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_Sewing.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_UBTreeFiller.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis.hpp>
#include <ShapeAnalysis_BoxBndTree.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeAnalysis_FreeBounds.hpp>
#include <ShapeAnalysis_Shell.hpp>
#include <ShapeAnalysis_Wire.hpp>
#include <ShapeBuild_Edge.hpp>
#include <ShapeBuild_Vertex.hpp>
#include <ShapeExtend_Explorer.hpp>
#include <ShapeExtend_WireData.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_HArray1.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

ShapeAnalysis_FreeBounds::ShapeAnalysis_FreeBounds() = default;

ShapeAnalysis_FreeBounds::ShapeAnalysis_FreeBounds(const TopoDS_Shape& shape,
                                                   const double        toler,
                                                   const bool          splitclosed,
                                                   const bool          splitopen)
    : myTolerance(toler),
      myShared(false),
      mySplitClosed(splitclosed),
      mySplitOpen(splitopen)
{
  BRepBuilderAPI_Sewing Sew(toler, false, false);
  for (TopoDS_Iterator S(shape); S.More(); S.Next())
    Sew.Add(S.Value());
  Sew.Perform();

  int                                              nbedge = Sew.NbFreeEdges();
  occ::handle<NCollection_HSequence<TopoDS_Shape>> edges  = new NCollection_HSequence<TopoDS_Shape>;
  occ::handle<NCollection_HSequence<TopoDS_Shape>> wires;
  TopoDS_Edge                                      anEdge;
  for (int iedge = 1; iedge <= nbedge; iedge++)
  {
    anEdge = TopoDS::Edge(Sew.FreeEdge(iedge));
    if (!BRep_Tool::Degenerated(anEdge))
      edges->Append(anEdge);
  }

  ConnectEdgesToWires(edges, toler, false, wires);
  DispatchWires(wires, myWires, myEdges);
  SplitWires();

  return;
}

ShapeAnalysis_FreeBounds::ShapeAnalysis_FreeBounds(const TopoDS_Shape& shape,
                                                   const bool          splitclosed,
                                                   const bool          splitopen,
                                                   const bool          checkinternaledges)
    : myTolerance(0.),
      myShared(true),
      mySplitClosed(splitclosed),
      mySplitOpen(splitopen)
{
  TopoDS_Shell aTmpShell;
  BRep_Builder aB;
  aB.MakeShell(aTmpShell);
  for (TopExp_Explorer aExpFace(shape, TopAbs_FACE); aExpFace.More(); aExpFace.Next())
    aB.Add(aTmpShell, aExpFace.Current());

  ShapeAnalysis_Shell sas;
  sas.CheckOrientedShells(aTmpShell, true, checkinternaledges);

  if (sas.HasFreeEdges())
  {
    ShapeExtend_Explorer                             see;
    occ::handle<NCollection_HSequence<TopoDS_Shape>> edges =
      see.SeqFromCompound(sas.FreeEdges(), false);

    occ::handle<NCollection_HSequence<TopoDS_Shape>> wires;
    ConnectEdgesToWires(edges, Precision::Confusion(), true, wires);
    DispatchWires(wires, myWires, myEdges);
    SplitWires();
  }
}

void ShapeAnalysis_FreeBounds::ConnectEdgesToWires(
  occ::handle<NCollection_HSequence<TopoDS_Shape>>& edges,
  const double                                      toler,
  const bool                                        shared,
  occ::handle<NCollection_HSequence<TopoDS_Shape>>& wires)
{
  occ::handle<NCollection_HSequence<TopoDS_Shape>> iwires = new NCollection_HSequence<TopoDS_Shape>;
  BRep_Builder                                     B;

  int i;
  for (i = 1; i <= edges->Length(); i++)
  {
    TopoDS_Wire wire;
    B.MakeWire(wire);
    B.Add(wire, edges->Value(i));
    iwires->Append(wire);
  }

  ConnectWiresToWires(iwires, toler, shared, wires);

  for (i = 1; i <= edges->Length(); i++)
    if (iwires->Value(i).Orientation() == TopAbs_REVERSED)
      edges->ChangeValue(i).Reverse();
}

void ShapeAnalysis_FreeBounds::ConnectWiresToWires(
  occ::handle<NCollection_HSequence<TopoDS_Shape>>& iwires,
  const double                                      toler,
  const bool                                        shared,
  occ::handle<NCollection_HSequence<TopoDS_Shape>>& owires)
{
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> map;
  ConnectWiresToWires(iwires, toler, shared, owires, map);
}

void ShapeAnalysis_FreeBounds::ConnectWiresToWires(
  occ::handle<NCollection_HSequence<TopoDS_Shape>>&                         iwires,
  const double                                                              toler,
  const bool                                                                shared,
  occ::handle<NCollection_HSequence<TopoDS_Shape>>&                         owires,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& vertices)
{
  if (iwires.IsNull() || !iwires->Length())
    return;
  occ::handle<NCollection_HArray1<TopoDS_Shape>> arrwires =
    new NCollection_HArray1<TopoDS_Shape>(1, iwires->Length());

  int i;
  for (i = 1; i <= arrwires->Length(); i++)
    arrwires->SetValue(i, iwires->Value(i));
  owires           = new NCollection_HSequence<TopoDS_Shape>;
  double tolerance = std::max(toler, Precision::Confusion());

  occ::handle<ShapeExtend_WireData> sewd =
    new ShapeExtend_WireData(TopoDS::Wire(arrwires->Value(1)));

  bool isUsedManifoldMode = true;

  if ((sewd->NbEdges() < 1) && (sewd->NbNonManifoldEdges() > 0))
  {
    isUsedManifoldMode = false;
    sewd = new ShapeExtend_WireData(TopoDS::Wire(arrwires->Value(1)), true, isUsedManifoldMode);
  }

  occ::handle<ShapeAnalysis_Wire> saw = new ShapeAnalysis_Wire;
  saw->Load(sewd);
  saw->SetPrecision(tolerance);

  NCollection_UBTree<int, Bnd_Box>       aBBTree;
  NCollection_UBTreeFiller<int, Bnd_Box> aTreeFiller(aBBTree);
  ShapeAnalysis_BoxBndTreeSelector       aSel(arrwires, shared);
  aSel.LoadList(1);

  for (int inbW = 2; inbW <= arrwires->Length(); inbW++)
  {
    TopoDS_Wire   trW = TopoDS::Wire(arrwires->Value(inbW));
    Bnd_Box       aBox;
    TopoDS_Vertex trV1, trV2;
    ShapeAnalysis::FindBounds(trW, trV1, trV2);
    gp_Pnt trP1 = BRep_Tool::Pnt(trV1);
    gp_Pnt trP2 = BRep_Tool::Pnt(trV2);
    aBox.Set(trP1);
    aBox.Add(trP2);
    aBox.SetGap(tolerance);
    aTreeFiller.Add(inbW, aBox);
  }

  aTreeFiller.Fill();
  int nsel;

  ShapeAnalysis_Edge sae;
  bool               done = false;

  while (!done)
  {
    bool found = false, tail = false, direct = false;
    int  lwire = 0;
    aSel.SetStop();
    Bnd_Box       FVBox, LVBox;
    TopoDS_Vertex Vf, Vl;
    Vf = sae.FirstVertex(sewd->Edge(1));
    Vl = sae.LastVertex(sewd->Edge(sewd->NbEdges()));

    gp_Pnt pf, pl;
    pf = BRep_Tool::Pnt(Vf);
    pl = BRep_Tool::Pnt(Vl);
    FVBox.Set(pf);
    FVBox.SetGap(tolerance);
    LVBox.Set(pl);
    LVBox.SetGap(tolerance);

    aSel.DefineBoxes(FVBox, LVBox);

    if (shared)
      aSel.DefineVertexes(Vf, Vl);
    else
    {
      aSel.DefinePnt(pf, pl);
      aSel.SetTolerance(tolerance);
    }

    nsel = aBBTree.Select(aSel);

    if (nsel != 0 && !aSel.LastCheckStatus(ShapeExtend_FAIL))
    {
      found  = true;
      lwire  = aSel.GetNb();
      tail   = aSel.LastCheckStatus(ShapeExtend_DONE1) || aSel.LastCheckStatus(ShapeExtend_DONE2);
      direct = aSel.LastCheckStatus(ShapeExtend_DONE1) || aSel.LastCheckStatus(ShapeExtend_DONE3);
      aSel.LoadList(lwire);
    }

    if (found)
    {
      if (!direct)
        arrwires->ChangeValue(lwire).Reverse();

      TopoDS_Wire                       aCurW = TopoDS::Wire(arrwires->Value(lwire));
      occ::handle<ShapeExtend_WireData> acurwd =
        new ShapeExtend_WireData(TopoDS::Wire(arrwires->Value(lwire)), true, isUsedManifoldMode);
      if (!acurwd->NbEdges())
        continue;
      sewd->Add(acurwd, (tail ? 0 : 1));
    }
    else
    {

      for (i = 1; i <= saw->NbEdges(); i++)
      {
        if (saw->CheckConnected(i))
        {
          int         n2 = i;
          int         n1 = (n2 > 1 ? n2 - 1 : saw->NbEdges());
          TopoDS_Edge E1 = sewd->Edge(n1);
          TopoDS_Edge E2 = sewd->Edge(n2);

          TopoDS_Vertex Vprev, Vfol, V;
          Vprev = sae.LastVertex(E1);
          Vfol  = sae.FirstVertex(E2);

          if (saw->LastCheckStatus(ShapeExtend_DONE1))
            V = Vprev;
          else
          {
            ShapeBuild_Vertex sbv;
            V = sbv.CombineVertex(Vprev, Vfol);
          }
          vertices.Bind(Vprev, V);
          vertices.Bind(Vfol, V);

          ShapeBuild_Edge sbe;
          if (saw->NbEdges() < 2)
            sewd->Set(sbe.CopyReplaceVertices(E2, V, V), n2);
          else
          {
            sewd->Set(sbe.CopyReplaceVertices(E2, V, TopoDS_Vertex()), n2);
            if (!saw->LastCheckStatus(ShapeExtend_DONE1))
              sewd->Set(sbe.CopyReplaceVertices(E1, TopoDS_Vertex(), V), n1);
          }
        }
      }

      TopoDS_Wire wire = sewd->Wire();
      if (isUsedManifoldMode)
      {
        if (!saw->CheckConnected(1) && saw->LastCheckStatus(ShapeExtend_OK))
          wire.Closed(true);
      }
      else
      {

        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> vmap;
        TopoDS_Iterator                                        it(wire);

        for (; it.More(); it.Next())
        {
          const TopoDS_Shape& E = it.Value();
          TopoDS_Iterator     ite(E, false, true);
          for (; ite.More(); ite.Next())
          {
            const TopoDS_Shape& V = ite.Value();
            if (V.Orientation() == TopAbs_FORWARD || V.Orientation() == TopAbs_REVERSED)
            {

              if (!vmap.Add(V))
                vmap.Remove(V);
            }
          }
        }
        if (vmap.IsEmpty())
        {
          wire.Closed(true);
        }
      }

      owires->Append(wire);
      sewd->Clear();
      sewd->ManifoldMode() = isUsedManifoldMode;

      lwire = -1;
      for (i = 1; i <= arrwires->Length(); i++)
      {
        if (!aSel.ContWire(i))
        {
          lwire = i;
          sewd->Add(TopoDS::Wire(arrwires->Value(lwire)));
          aSel.LoadList(lwire);

          if (sewd->NbEdges() > 0)
            break;
          sewd->Clear();
        }
      }

      if (lwire == -1)
        done = true;
    }
  }

  for (i = 1; i <= iwires->Length(); i++)
  {
    iwires->SetValue(i, arrwires->Value(i));
  }
}

static void SplitWire(const TopoDS_Wire&                                wire,
                      const double                                      toler,
                      const bool                                        shared,
                      occ::handle<NCollection_HSequence<TopoDS_Shape>>& closed,
                      occ::handle<NCollection_HSequence<TopoDS_Shape>>& open)
{
  closed           = new NCollection_HSequence<TopoDS_Shape>;
  open             = new NCollection_HSequence<TopoDS_Shape>;
  double tolerance = std::max(toler, Precision::Confusion());

  BRep_Builder       B;
  ShapeAnalysis_Edge sae;

  occ::handle<ShapeExtend_WireData> sewd    = new ShapeExtend_WireData(wire);
  int                               nbedges = sewd->NbEdges();

  NCollection_Sequence<int> ces;

  NCollection_Array1<int> statuses(1, nbedges);
  statuses.Init(0);

  int i;
  for (i = 1; i <= nbedges; i++)
    if (statuses.Value(i) == 0)
    {
      ces.Append(i);
      statuses.SetValue(i, 1);
      bool SearchBackward = true;

      for (;;)
      {
        bool          found;
        TopoDS_Edge   edge;
        TopoDS_Vertex lvertex;
        gp_Pnt        lpoint;

        if (SearchBackward)
        {
          SearchBackward = false;
          found          = false;
          edge           = sewd->Edge(ces.Last());
          lvertex        = sae.LastVertex(edge);
          lpoint         = BRep_Tool::Pnt(lvertex);
          int j;
          for (j = ces.Length(); (j >= 1) && !found; j--)
          {
            TopoDS_Vertex fv = sae.FirstVertex(sewd->Edge(ces.Value(j)));
            gp_Pnt        fp = BRep_Tool::Pnt(fv);
            if ((shared && lvertex.IsSame(fv)) || (!shared && lpoint.IsEqual(fp, tolerance)))
              found = true;
          }

          if (found)
          {
            j++;

            TopoDS_Wire wire1;
            B.MakeWire(wire1);
            for (int cesindex = j; cesindex <= ces.Length(); cesindex++)
            {
              B.Add(wire1, sewd->Edge(ces.Value(cesindex)));
              statuses.SetValue(ces.Value(cesindex), 2);
            }
            wire1.Closed(true);
            closed->Append(wire1);
            ces.Remove(j, ces.Length());
            if (ces.IsEmpty())
              break;
          }
        }

        found   = false;
        edge    = sewd->Edge(ces.Last());
        lvertex = sae.LastVertex(edge);
        lpoint  = BRep_Tool::Pnt(lvertex);
        int j;
        for (j = 1; (j <= nbedges) && !found; j++)
          if (statuses.Value(j) == 0)
          {
            TopoDS_Vertex fv = sae.FirstVertex(sewd->Edge(j));
            gp_Pnt        fp = BRep_Tool::Pnt(fv);
            if ((shared && lvertex.IsSame(fv)) || (!shared && lpoint.IsEqual(fp, tolerance)))
              found = true;
          }

        if (found)
        {
          j--;
          ces.Append(j);
          statuses.SetValue(j, 1);
          SearchBackward = true;
          continue;
        }

        statuses.SetValue(ces.Last(), 3);
        ces.Remove(ces.Length());
        if (ces.IsEmpty())
          break;
      }
    }

  occ::handle<NCollection_HSequence<TopoDS_Shape>> edges = new NCollection_HSequence<TopoDS_Shape>;
  for (i = 1; i <= nbedges; i++)
    if (statuses.Value(i) != 2)
      edges->Append(sewd->Edge(i));

  ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, toler, shared, open);
}

void ShapeAnalysis_FreeBounds::SplitWires(
  const occ::handle<NCollection_HSequence<TopoDS_Shape>>& wires,
  const double                                            toler,
  const bool                                              shared,
  occ::handle<NCollection_HSequence<TopoDS_Shape>>&       closed,
  occ::handle<NCollection_HSequence<TopoDS_Shape>>&       open)
{
  closed = new NCollection_HSequence<TopoDS_Shape>;
  open   = new NCollection_HSequence<TopoDS_Shape>;

  for (int i = 1; i <= wires->Length(); i++)
  {
    occ::handle<NCollection_HSequence<TopoDS_Shape>> tmpclosed, tmpopen;
    SplitWire(TopoDS::Wire(wires->Value(i)), toler, shared, tmpclosed, tmpopen);
    closed->Append(tmpclosed);
    open->Append(tmpopen);
  }
}

void ShapeAnalysis_FreeBounds::DispatchWires(
  const occ::handle<NCollection_HSequence<TopoDS_Shape>>& wires,
  TopoDS_Compound&                                        closed,
  TopoDS_Compound&                                        open)
{
  BRep_Builder B;
  if (closed.IsNull())
    B.MakeCompound(closed);
  if (open.IsNull())
    B.MakeCompound(open);
  if (wires.IsNull())
    return;

  for (int iw = 1; iw <= wires->Length(); iw++)
    if (wires->Value(iw).Closed())
      B.Add(closed, wires->Value(iw));
    else
      B.Add(open, wires->Value(iw));
}

void ShapeAnalysis_FreeBounds::SplitWires()
{
  if (!mySplitClosed && !mySplitOpen)
    return;

  ShapeExtend_Explorer                             see;
  occ::handle<NCollection_HSequence<TopoDS_Shape>> closedwires, cw1, cw2, openwires, ow1, ow2;
  closedwires = see.SeqFromCompound(myWires, false);
  openwires   = see.SeqFromCompound(myEdges, false);

  if (mySplitClosed)
    SplitWires(closedwires, myTolerance, myShared, cw1, ow1);
  else
  {
    cw1 = closedwires;
    ow1 = new NCollection_HSequence<TopoDS_Shape>;
  }

  if (mySplitOpen)
    SplitWires(openwires, myTolerance, myShared, cw2, ow2);
  else
  {
    cw2 = new NCollection_HSequence<TopoDS_Shape>;
    ow2 = openwires;
  }

  closedwires = cw1;
  closedwires->Append(cw2);
  openwires = ow1;
  openwires->Append(ow2);

  TopoDS_Shape compWires = see.CompoundFromSeq(closedwires);
  TopoDS_Shape compEdges = see.CompoundFromSeq(openwires);
  myWires                = TopoDS::Compound(compWires);
  myEdges                = TopoDS::Compound(compEdges);
}
