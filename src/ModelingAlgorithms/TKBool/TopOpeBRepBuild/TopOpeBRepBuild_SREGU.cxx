#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>
#include <TopOpeBRepBuild_PaveSet.hpp>
#include <TopOpeBRepBuild_ShellFaceSet.hpp>
#include <TopOpeBRepBuild_ShellToSolid.hpp>
#include <TopOpeBRepDS_define.hpp>
#include <TopOpeBRepTool.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>

#ifdef OCCT_DEBUG
extern bool TopOpeBRepBuild_GetcontextNOREGUSO();
extern bool TopOpeBRepBuild_GetcontextREGUXPU();
extern bool TopOpeBRepBuild_GettraceSAVSREGU();

Standard_EXPORT void debreguso(const int iS)
{
  std::cout << "++ debreguso " << iS << std::endl;
}
#endif

void TopOpeBRepBuild_Builder::RegularizeSolids(const TopoDS_Shape&                   SO,
                                               const NCollection_List<TopoDS_Shape>& lnewSolid,
                                               NCollection_List<TopoDS_Shape>&       LOSO)
{
  LOSO.Clear();
  myMemoSplit.Clear();

  NCollection_List<TopoDS_Shape>::Iterator itl(lnewSolid);
  for (; itl.More(); itl.Next())
  {
    const TopoDS_Shape&            newSolid = itl.Value();
    NCollection_List<TopoDS_Shape> newSolidLOSO;
    RegularizeSolid(SO, newSolid, newSolidLOSO);
#ifdef OCCT_DEBUG

#endif
    LOSO.Append(newSolidLOSO);
  }
#ifdef OCCT_DEBUG

#endif
  int nr = myMemoSplit.Extent();
  if (nr == 0)
    return;

  NCollection_List<TopoDS_Shape> lsosdSO, lsosdSO1, lsosdSO2;
  GFindSamDom(SO, lsosdSO1, lsosdSO2);
  lsosdSO.Append(lsosdSO1);
  lsosdSO.Append(lsosdSO2);

  NCollection_List<TopoDS_Shape>::Iterator itlsosdSO(lsosdSO);
  for (; itlsosdSO.More(); itlsosdSO.Next())
  {
    const TopoDS_Shape& sosdSO = itlsosdSO.Value();

    TopExp_Explorer x;
    for (x.Init(sosdSO, TopAbs_FACE); x.More(); x.Next())
    {

      const TopoDS_Shape& f        = x.Current();
      int                 rankf    = GShapeRank(f);
      TopAbs_State        staf     = (rankf == 1) ? myState1 : myState2;
      bool                issplitf = IsSplit(f, staf);
      if (!issplitf)
        continue;

      NCollection_List<TopoDS_Shape>  newlspf;
      NCollection_List<TopoDS_Shape>& lspf = ChangeSplit(f, staf);
#ifdef OCCT_DEBUG

#endif
      for (NCollection_List<TopoDS_Shape>::Iterator itl1(lspf); itl1.More(); itl1.Next())
      {
        const TopoDS_Shape& fsp     = itl1.Value();
        bool                fspmemo = myMemoSplit.Contains(fsp);
        if (!fspmemo)
          newlspf.Append(fsp);
        else
        {
          NCollection_List<TopoDS_Shape>& lspfsp = ChangeSplit(fsp, staf);
          GCopyList(lspfsp, newlspf);
        }
      }
      lspf.Clear();
      GCopyList(newlspf, lspf);
    }
  }
}

void TopOpeBRepBuild_Builder::RegularizeSolid(const TopoDS_Shape&             SS,
                                              const TopoDS_Shape&             anewSolid,
                                              NCollection_List<TopoDS_Shape>& LOSO)
{
  LOSO.Clear();
  const TopoDS_Solid& newSolid = TopoDS::Solid(anewSolid);
  bool                toregu   = true;
  bool                usestos  = true;

#ifdef OCCT_DEBUG
  int  iS;
  bool tSPS = GtraceSPS(SS, iS);

  if (TopOpeBRepBuild_GetcontextNOREGUSO())
    toregu = false;
  if (TopOpeBRepBuild_GetcontextREGUXPU())
    usestos = false;
  if (tSPS)
    debreguso(iS);
#endif

  if (!toregu)
  {
    LOSO.Append(newSolid);
    return;
  }

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> osns;
  bool rw = false;
  bool rf = false;
  myFSplits.Clear();

  rw = TopOpeBRepTool::RegularizeShells(newSolid, osns, myFSplits);

  if (!rw)
  {
    LOSO.Append(newSolid);
    return;
  }

  NCollection_List<TopoDS_Shape> newSolids;
  if (usestos)
  {
    TopOpeBRepBuild_ShellToSolid stos;
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator itosns(osns);
    for (; itosns.More(); itosns.Next())
    {

      const NCollection_List<TopoDS_Shape>& lns = itosns.Value();
      for (NCollection_List<TopoDS_Shape>::Iterator iw(lns); iw.More(); iw.Next())
      {
        stos.AddShell(TopoDS::Shell(iw.Value()));
      }
    }
    stos.MakeSolids(newSolid, newSolids);
    rf = (newSolids.Extent() != 0);
  }
  else
  {
    rf = false;
  }

  if (!rf)
  {
    LOSO.Append(newSolid);
    return;
  }

#ifdef OCCT_DEBUG
  if (tSPS)
  {
    std::cout << "RegularizeSolid " << iS << std::endl;
    debreguso(iS);
  }
#endif

  NCollection_List<TopoDS_Shape>::Iterator itlnf(newSolids);
  for (; itlnf.More(); itlnf.Next())
    LOSO.Append(TopoDS::Solid(itlnf.Value()));

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mfns;
  TopExp_Explorer                                        x;
  for (x.Init(newSolid, TopAbs_FACE); x.More(); x.Next())
  {
    const TopoDS_Shape& F = x.Current();
    mfns.Add(F);
  }

  NCollection_List<TopoDS_Shape> lssdSS, lssdSS1, lssdSS2;
  GFindSamDom(SS, lssdSS1, lssdSS2);
  lssdSS.Append(lssdSS1);
  lssdSS.Append(lssdSS2);

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> manc;

  NCollection_List<TopoDS_Shape>::Iterator itlssdSS(lssdSS);
  for (; itlssdSS.More(); itlssdSS.Next())
  {
    const TopoDS_Shape& ssdSS = itlssdSS.Value();
#ifdef OCCT_DEBUG

#endif

    int          rankssdSS = GShapeRank(ssdSS);
    TopAbs_State stassdSS  = (rankssdSS == 1) ? myState1 : myState2;
#ifdef OCCT_DEBUG

#endif

    for (x.Init(ssdSS, TopAbs_FACE); x.More(); x.Next())
    {

      const TopoDS_Shape& ssdSSf = x.Current();

#ifdef OCCT_DEBUG
      int  issdSSf    = 0;
      bool tSPSssdSSf = GtraceSPS(ssdSSf, issdSSf);
      if (tSPSssdSSf)
        debreguso(issdSSf);
#endif

      TopAbs_State stassdSSf = stassdSS;

      NCollection_List<TopoDS_Shape>& lspssdSSf = ChangeSplit(ssdSSf, stassdSSf);
#ifdef OCCT_DEBUG

#endif

      NCollection_List<TopoDS_Shape> newlspssdSSf;

      for (NCollection_List<TopoDS_Shape>::Iterator it(lspssdSSf); it.More(); it.Next())
      {
        const TopoDS_Shape& fspssdSSf = it.Value();

        bool inmfns = mfns.Contains(fspssdSSf);
        if (!inmfns)
          continue;

        bool rfsplitloc = myFSplits.IsBound(fspssdSSf);
        if (rfsplitloc)
        {

          const NCollection_List<TopoDS_Shape>& lrfsplit = myFSplits.Find(fspssdSSf);

          myMemoSplit.Add(fspssdSSf);

          NCollection_List<TopoDS_Shape>& lsp = ChangeSplit(fspssdSSf, stassdSSf);
          GCopyList(lrfsplit, lsp);
        }
      }
    }
  }
}
