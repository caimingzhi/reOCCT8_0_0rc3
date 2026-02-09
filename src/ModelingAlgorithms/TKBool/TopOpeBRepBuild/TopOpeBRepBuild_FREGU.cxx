#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>
#include <TopOpeBRepBuild_PaveSet.hpp>
#include <TopOpeBRepBuild_WireToFace.hpp>
#include <TopOpeBRepTool.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>

#ifdef OCCT_DEBUG
extern bool TopOpeBRepBuild_GetcontextNOREGUFA();
extern bool TopOpeBRepBuild_GetcontextREGUXPU();
extern bool TopOpeBRepBuild_GettraceSAVFREGU();

void debregufa(const int) {}
#endif

#define M_FORWARD(O) (O == TopAbs_FORWARD)
#define M_REVERSED(O) (O == TopAbs_REVERSED)

void TopOpeBRepBuild_Builder::RegularizeFaces(const TopoDS_Shape&                   FF,
                                              const NCollection_List<TopoDS_Shape>& lnewFace,
                                              NCollection_List<TopoDS_Shape>&       LOF)
{
  LOF.Clear();
  myMemoSplit.Clear();

  NCollection_List<TopoDS_Shape>::Iterator itl(lnewFace);
  for (; itl.More(); itl.Next())
  {
    const TopoDS_Shape&            newFace = itl.Value();
    NCollection_List<TopoDS_Shape> newFaceLOF;
    RegularizeFace(FF, newFace, newFaceLOF);
#ifdef OCCT_DEBUG

#endif
    LOF.Append(newFaceLOF);
  }
#ifdef OCCT_DEBUG

#endif

  int nr = myMemoSplit.Extent();
  if (nr == 0)
    return;

  NCollection_List<TopoDS_Shape> lfsdFF, lfsdFF1, lfsdFF2;
  GFindSamDom(FF, lfsdFF1, lfsdFF2);
  lfsdFF.Append(lfsdFF1);
  lfsdFF.Append(lfsdFF2);

  NCollection_List<TopoDS_Shape>::Iterator itlfsdFF(lfsdFF);
  for (; itlfsdFF.More(); itlfsdFF.Next())
  {
    const TopoDS_Shape& fsdFF = itlfsdFF.Value();

    TopExp_Explorer x;
    for (x.Init(fsdFF, TopAbs_EDGE); x.More(); x.Next())
    {

      const TopoDS_Shape& e = x.Current();
#ifdef OCCT_DEBUG

#endif

      int          ranke   = GShapeRank(e);
      TopAbs_State staeope = (ranke == 1) ? myState1 : myState2;

      for (int iiista = 1; iiista <= 2; iiista++)
      {

        TopAbs_State stae = staeope;
        if (iiista == 2)
          stae = TopAbs_ON;

        bool issplite = IsSplit(e, stae);
        if (!issplite)
          continue;

        NCollection_List<TopoDS_Shape>& lspe = ChangeSplit(e, stae);
#ifdef OCCT_DEBUG

#endif
        NCollection_List<TopoDS_Shape> newlspe;
        for (NCollection_List<TopoDS_Shape>::Iterator itl1(lspe); itl1.More(); itl1.Next())
        {
          const TopoDS_Shape& esp     = itl1.Value();
          bool                espmemo = myMemoSplit.Contains(esp);
          if (!espmemo)
            newlspe.Append(esp);
          else
          {
            const NCollection_List<TopoDS_Shape>& lspesp = Splits(esp, stae);
            GCopyList(lspesp, newlspe);
          }
        }
        lspe.Clear();
        GCopyList(newlspe, lspe);
      }
    }
  }
}

void TopOpeBRepBuild_Builder::RegularizeFace(const TopoDS_Shape&             FF,
                                             const TopoDS_Shape&             anewFace,
                                             NCollection_List<TopoDS_Shape>& LOF)
{
  LOF.Clear();
  const TopoDS_Face& newFace = TopoDS::Face(anewFace);
  bool               toregu  = true;
  bool               usewtof = true;

#ifdef OCCT_DEBUG
  int  iF;
  bool tSPSFF = GtraceSPS(FF, iF);

  if (TopOpeBRepBuild_GetcontextNOREGUFA())
    toregu = false;
  if (TopOpeBRepBuild_GetcontextREGUXPU())
    usewtof = false;
  if (tSPSFF)
    debregufa(iF);
#endif

  if (!toregu)
  {
    LOF.Append(newFace);
    return;
  }

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> ownw;
  bool rw = false;
  bool rf = false;
  myESplits.Clear();

  rw = TopOpeBRepTool::RegularizeWires(newFace, ownw, myESplits);

  if (!rw)
  {
    LOF.Append(newFace);
    return;
  }

  NCollection_List<TopoDS_Shape> newfaces;
  if (usewtof)
  {
    TopOpeBRepBuild_WireToFace wtof;
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator itownw(ownw);
    for (; itownw.More(); itownw.Next())
    {
      const NCollection_List<TopoDS_Shape>& lw = itownw.Value();

      bool kept = lw.IsEmpty();
      if (kept)
      {
        const TopoDS_Wire& ow = TopoDS::Wire(itownw.Key());
        wtof.AddWire(ow);
      }
      for (NCollection_List<TopoDS_Shape>::Iterator iw(lw); iw.More(); iw.Next())
      {
        const TopoDS_Wire& w = TopoDS::Wire(iw.Value());
        wtof.AddWire(w);
      }
    }
    wtof.MakeFaces(newFace, newfaces);
#ifdef OCCT_DEBUG

#endif
    rf = (newfaces.Extent() != 0);
  }
  else
  {
    rf = TopOpeBRepTool::RegularizeFace(newFace, ownw, newfaces);
  }

  if (!rf)
  {
    LOF.Append(newFace);
    return;
  }

#ifdef OCCT_DEBUG
  if (tSPSFF)
  {
    std::cout << "RegularizeFace " << iF << std::endl;
    debregufa(iF);
  }
#endif

  NCollection_List<TopoDS_Shape>::Iterator itlnf(newfaces);
  for (; itlnf.More(); itlnf.Next())
    LOF.Append(TopoDS::Face(itlnf.Value()));

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> menf;
  TopExp_Explorer                                        x;
  for (x.Init(newFace, TopAbs_EDGE); x.More(); x.Next())
  {
    const TopoDS_Shape& E = x.Current();
    menf.Add(E);
  }

  NCollection_List<TopoDS_Shape> lfsdFF, lfsdFF1, lfsdFF2;
  GFindSamDom(FF, lfsdFF1, lfsdFF2);
  lfsdFF.Append(lfsdFF1);
  lfsdFF.Append(lfsdFF2);

  NCollection_List<TopoDS_Shape>::Iterator itlfsdFF(lfsdFF);
  for (; itlfsdFF.More(); itlfsdFF.Next())
  {
    const TopoDS_Shape& fsdFF = itlfsdFF.Value();

#ifdef OCCT_DEBUG
    int  ifsdFF    = 0;
    bool tSPSfsdFF = GtraceSPS(fsdFF, ifsdFF);
    if (tSPSfsdFF)
      debregufa(ifsdFF);
#endif

    int          rankfsdFF = GShapeRank(fsdFF);
    TopAbs_State stafsdFF  = (rankfsdFF == 1) ? myState1 : myState2;
#ifdef OCCT_DEBUG

#endif

    for (x.Init(fsdFF, TopAbs_EDGE); x.More(); x.Next())
    {

      const TopoDS_Shape& fsdFFe = x.Current();

#ifdef OCCT_DEBUG
      int  ifsdFFe    = 0;
      bool tSPSfsdFFe = GtraceSPS(fsdFFe, ifsdFFe);
      if (tSPSfsdFFe)
        debregufa(ifsdFFe);
#endif

      for (int iiista = 1; iiista <= 2; iiista++)
      {
        TopAbs_State stafsdFFe = stafsdFF;
        if (iiista == 2)
          stafsdFFe = TopAbs_ON;

        NCollection_List<TopoDS_Shape>& lspfsdFFe = ChangeSplit(fsdFFe, stafsdFFe);
#ifdef OCCT_DEBUG

#endif

        for (NCollection_List<TopoDS_Shape>::Iterator it(lspfsdFFe); it.More(); it.Next())
        {

          const TopoDS_Shape& espfsdFFe = it.Value();
          bool                inmenf    = menf.Contains(espfsdFFe);
          if (!inmenf)
            continue;

          bool resplitloc = myESplits.IsBound(espfsdFFe);
          if (resplitloc)
          {

            const NCollection_List<TopoDS_Shape>& lresplit = myESplits.Find(espfsdFFe);

            myMemoSplit.Add(espfsdFFe);

            NCollection_List<TopoDS_Shape>& lsp = ChangeSplit(espfsdFFe, stafsdFFe);
            GCopyList(lresplit, lsp);
          }
        }
      }
    }
  }
}
