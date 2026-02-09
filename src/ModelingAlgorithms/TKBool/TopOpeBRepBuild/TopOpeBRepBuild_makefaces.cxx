#include <BRepTools.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Standard_ProgramError.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_define.hpp>
#include <TopOpeBRepBuild_FaceBuilder.hpp>
#include <TopOpeBRepBuild_WireEdgeSet.hpp>
#include <TopOpeBRepDS_BuildTool.hpp>
#include <TopOpeBRepDS_EXPORT.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepTool.hpp>
#include <TopOpeBRepTool_2d.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>

#ifdef OCCT_DEBUG
extern bool TopOpeBRepBuild_GetcontextNOPURGE();
extern bool TopOpeBRepBuild_GetcontextNOCORRISO();
extern bool TopOpeBRepBuild_GettraceCHK();
  #define DEBSHASET(sarg, meth, shaset, str)                                                       \
    TCollection_AsciiString sarg((meth));                                                          \
    (sarg) = (sarg) + (shaset).DEBNumber() + (str);

Standard_EXPORT void debgfabu(const int i)
{
  std::cout << "++ debgfabu " << i << std::endl;
}

Standard_EXPORT void debwesmf(const int i)
{
  std::cout << "++ debwesmf " << i << std::endl;
}

Standard_EXPORT bool DEBpurclo = false;

void debpurclo() {}

void debpurclomess(int i)
{
  std::cout << "++ debpurclo " << i << std::endl;
  debpurclo();
}

Standard_EXPORT void debcorriso(const int i)
{
  std::cout << "++ debcorriso " << i << std::endl;
}

extern void* GFABUMAKEFACEPWES_DEB;
#endif

Standard_EXPORT bool FUN_tool_ClosedW(const TopoDS_Wire& W);

void TopOpeBRepBuild_Builder::GWESMakeFaces(const TopoDS_Shape&             FF,
                                            TopOpeBRepBuild_WireEdgeSet&    WES,
                                            NCollection_List<TopoDS_Shape>& LOF)
{
#ifdef OCCT_DEBUG
  int  iF;
  bool tSPS = GtraceSPS(FF, iF);
  DEBSHASET(s, "#--- GWESMakeFaces ", WES, " ");
  if (tSPS)
  {
    GdumpSHA(FF, (void*)s.ToCString());
    std::cout << std::endl;
    WES.DumpSS();
  }
  if (tSPS)
  {
    debwesmf(iF);
  }
  GFABUMAKEFACEPWES_DEB = (void*)&WES;
#endif

  const bool                  ForceClass = true;
  TopOpeBRepBuild_FaceBuilder FABU;
  FABU.InitFaceBuilder(WES, FF, ForceClass);

  bool topurge = true;
#ifdef OCCT_DEBUG
  if (TopOpeBRepBuild_GetcontextNOPURGE())
    topurge = false;
#endif

  if (topurge)
  {
    TopOpeBRepDS_DataStructure& BDS = myDataStructure->ChangeDS();

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mapPIE;
    FABU.DetectPseudoInternalEdge(mapPIE);

    NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> mapVVsameG,
      mapVon1Edge, mapVVref;
    FABU.DetectUnclosedWire(mapVVsameG, mapVon1Edge);

    int nVV = mapVVsameG.Extent();
    if (nVV > 0)
    {

      for (int i = 1; i <= nVV; i++)
      {
        const TopoDS_Shape& V    = mapVVsameG.FindKey(i);
        bool                hsdm = myDataStructure->HasSameDomain(V);
        if (!hsdm)
        {
          int rankV = BDS.AncestorRank(V);

          const TopoDS_Shape& VsameG = mapVVsameG.FindFromIndex(i);

          int  rankVsameG = BDS.AncestorRank(VsameG);
          bool otherRef   = (rankVsameG != 0 && rankV != 1);

          if (otherRef)
            BDS.FillShapesSameDomain(VsameG, V);
          else
            BDS.FillShapesSameDomain(V, VsameG);

          hsdm = myDataStructure->HasSameDomain(V);
        }
        if (hsdm)
        {
          int                 Iref = myDataStructure->SameDomainReference(V);
          const TopoDS_Shape& Vref = myDataStructure->Shape(Iref);
          mapVVref.Add(V, Vref);
        }
      }
      FABU.CorrectGclosedWire(mapVVref, mapVon1Edge);
      FABU.DetectUnclosedWire(mapVVsameG, mapVon1Edge);
    }
  }

  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher> MWisOld;
  NCollection_IndexedMap<TopoDS_Shape>                            MshNOK;
  GFABUMakeFaces(FF, FABU, LOF, MWisOld);

  if (topurge)
  {

    const TopoDS_Face& FA   = TopoDS::Face(FF);
    bool               puok = TopOpeBRepTool::PurgeClosingEdges(FA, LOF, MWisOld, MshNOK);
    if (!puok)
      throw Standard_Failure("TopOpeBRepBuild::GWESMakeFaces");
    topurge = !MshNOK.IsEmpty();

#ifdef OCCT_DEBUG
    if (tSPS)
      DEBpurclo = false;
#endif
  }

  if (topurge)
  {
    NCollection_List<TopoDS_Shape> LOFF;
    bool puok = TopOpeBRepTool::MakeFaces(TopoDS::Face(FF), LOF, MshNOK, LOFF);
    if (!puok)
      throw Standard_Failure("TopOpeBRepBuild::GWESMakeFaces");
    LOF.Clear();
    LOF.Assign(LOFF);
  }

  bool corronISO = true;
#ifdef OCCT_DEBUG
  if (TopOpeBRepBuild_GetcontextNOCORRISO())
    corronISO = false;
  if (tSPS)
    debcorriso(iF);
#endif
  bool ffcloseds = FUN_tool_closedS(FF);
  corronISO      = corronISO && ffcloseds;
  if (corronISO)
  {
    NCollection_List<TopoDS_Shape>::Iterator itFF(LOF);
    NCollection_List<TopoDS_Shape>           newLOF;
    const TopoDS_Face&                       FFa = TopoDS::Face(FF);
    for (; itFF.More(); itFF.Next())
    {
      TopoDS_Face Fa = TopoDS::Face(itFF.Value());
      TopOpeBRepTool::CorrectONUVISO(FFa, Fa);
      newLOF.Append(Fa);
    }
    LOF.Clear();
    LOF.Assign(newLOF);
  }

  NCollection_List<TopoDS_Shape> newLOF;
  RegularizeFaces(FF, LOF, newLOF);
  LOF.Clear();
  LOF.Assign(newLOF);
}

static bool FUN_purgeFon1nonoriE(const TopoDS_Shape& newFace)
{
  TopExp_Explorer ex(newFace, TopAbs_EDGE);
  int             nE = 0;
  for (; ex.More(); ex.Next())
    nE++;
  if (nE == 1)
  {
    ex.Init(newFace, TopAbs_EDGE);
    const TopoDS_Shape& ed     = ex.Current();
    TopAbs_Orientation  ori    = ed.Orientation();
    bool                hasori = (ori == TopAbs_FORWARD) || (ori == TopAbs_REVERSED);
    if (!hasori)
      return true;

    TopoDS_Edge theEdge = TopoDS::Edge(ed);
    if (BRep_Tool::Degenerated(theEdge))
      return true;
  }
  return false;
}

static TopAbs_Orientation FUN_ReOrientIntExtEdge(const TopoDS_Edge& FRE,
                                                 TopAbs_Orientation OFRE,
                                                 const TopoDS_Edge& INE)
{
  TopAbs_Orientation result = INE.Orientation();
  TopoDS_Vertex      Vf1, Vl1, Vf2, Vl2;

  TopExp::Vertices(FRE, Vf1, Vl1, false);
  TopExp::Vertices(INE, Vf2, Vl2, false);

  if (OFRE == TopAbs_FORWARD)
  {
    if (Vl1.IsSame(Vf2))
      result = TopAbs_FORWARD;
    if (Vl1.IsSame(Vl2))
      result = TopAbs_REVERSED;
    if (Vf1.IsSame(Vf2))
      result = TopAbs_REVERSED;
    if (Vf1.IsSame(Vl2))
      result = TopAbs_FORWARD;
  }
  if (OFRE == TopAbs_REVERSED)
  {
    if (Vl1.IsSame(Vf2))
      result = TopAbs_REVERSED;
    if (Vl1.IsSame(Vl2))
      result = TopAbs_FORWARD;
    if (Vf1.IsSame(Vf2))
      result = TopAbs_FORWARD;
    if (Vf1.IsSame(Vl2))
      result = TopAbs_REVERSED;
  }
  return result;
}

static int FUN_CheckORI(TopAbs_Orientation O1, TopAbs_Orientation O2)
{
  int result;
  if ((O1 == TopAbs_INTERNAL || O1 == TopAbs_EXTERNAL)
      && (O2 == TopAbs_INTERNAL || O2 == TopAbs_EXTERNAL))
    result = 0;
  else if ((O1 == TopAbs_INTERNAL || O1 == TopAbs_EXTERNAL)
           && (O2 == TopAbs_FORWARD || O2 == TopAbs_REVERSED))
    result = 1;
  else if ((O1 == TopAbs_FORWARD || O1 == TopAbs_REVERSED)
           && (O2 == TopAbs_INTERNAL || O2 == TopAbs_EXTERNAL))
    result = 2;
  else
    result = 4;
  return result;
}

void TopOpeBRepBuild_Builder::GFABUMakeFaces(
  const TopoDS_Shape&                                              FF,
  TopOpeBRepBuild_FaceBuilder&                                     FABU,
  NCollection_List<TopoDS_Shape>&                                  LOF,
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& MWisOld)
{
#ifdef OCCT_DEBUG
  int  iF;
  bool tSPS = GtraceSPS(FF, iF);
  if (tSPS)
  {
    std::cout << std::endl;
    GdumpSHA(FF, (char*)"#--- GFABUMakeFaces ");
    std::cout << std::endl;
    GdumpFABU(FABU);
    debgfabu(iF);
  }
#endif

  NCollection_List<TopoDS_Shape> lnewFace;
  TopoDS_Face                    newFace;
  TopoDS_Wire                    newWire;

  TopLoc_Location           Loc;
  occ::handle<Geom_Surface> Surf = BRep_Tool::Surface(TopoDS::Face(FF), Loc);

  double       tolFF = BRep_Tool::Tolerance(TopoDS::Face(FF));
  BRep_Builder BB;

  TopoDS_Compound CmpOfEdges;
  BRep_Builder    BldCmpOfEdges;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
              mapVOE;
  TopoDS_Face tdF = TopoDS::Face(FF);

  FABU.InitFace();
  for (; FABU.MoreFace(); FABU.NextFace())
  {
    int nbnewWwithe = 0;
    int nboldW      = 0;

    BB.MakeFace(newFace, Surf, Loc, tolFF);

    int nbw = FABU.InitWire();
    for (; FABU.MoreWire(); FABU.NextWire())
    {
      int ne         = 0;
      int neINTERNAL = 0;
      int neEXTERNAL = 0;

      bool isold = FABU.IsOldWire();
      if (isold)
      {
        nboldW++;
        newWire = TopoDS::Wire(FABU.OldWire());
      }
      else
      {
        BldCmpOfEdges.MakeCompound(CmpOfEdges);
        myBuildTool.MakeWire(newWire);
        FABU.InitEdge();
        for (; FABU.MoreEdge(); FABU.NextEdge())
        {
          TopoDS_Edge newEdge = TopoDS::Edge(FABU.Edge());

          int nadde = FABU.AddEdgeWire(newEdge, CmpOfEdges);
          ne += nadde;

          TopAbs_Orientation oE = newEdge.Orientation();
          if (oE == TopAbs_INTERNAL)
            neINTERNAL++;
          else if (oE == TopAbs_EXTERNAL)
            neEXTERNAL++;

          bool hasPC = FC2D_HasCurveOnSurface(newEdge, newFace);
          if (!hasPC)
          {
            double                    tolE = BRep_Tool::Tolerance(newEdge);
            double                    f2, l2, tolpc;
            occ::handle<Geom2d_Curve> C2D;

            C2D = FC2D_CurveOnSurface(newEdge, newFace, f2, l2, tolpc, true);
            if (C2D.IsNull())
              throw Standard_ProgramError("TopOpeBRepBuild_Builder::GFABUMakeFaces null PC");
            double       tol = std::max(tolE, tolpc);
            BRep_Builder BB_PC;
            BB_PC.UpdateEdge(newEdge, C2D, newFace, tol);
          }
        }

        if ((neINTERNAL == 0 && neEXTERNAL == 0) || (ne == neINTERNAL || ne == neEXTERNAL))
        {
          TopExp_Explorer EdgeEx;
          if (nbw == 1 && ne == 2)
          {
            EdgeEx.Init(CmpOfEdges, TopAbs_EDGE);
            TopoDS_Edge nEdge1 = TopoDS::Edge(EdgeEx.Current());
            EdgeEx.Next();
            TopoDS_Edge nEdge2 = TopoDS::Edge(EdgeEx.Current());
            if (nEdge1.IsSame(nEdge2))
              return;
          }
          for (EdgeEx.Init(CmpOfEdges, TopAbs_EDGE); EdgeEx.More(); EdgeEx.Next())
          {
            TopoDS_Edge newEdge = TopoDS::Edge(EdgeEx.Current());
            FABU.AddEdgeWire(newEdge, newWire);
          }
        }
        else
        {

          mapVOE.Clear();
          TopExp::MapShapesAndAncestors(CmpOfEdges, TopAbs_VERTEX, TopAbs_EDGE, mapVOE);

          bool WisClsd = true;
          for (int MapStep = 1; MapStep <= mapVOE.Extent(); MapStep++)
          {
            const NCollection_List<TopoDS_Shape>& LofE = mapVOE.FindFromIndex(MapStep);
            if (LofE.Extent() != 2)
            {
              WisClsd = false;
              break;
            }
          }
          if (!WisClsd)
          {

            TopExp_Explorer EdgeEx;
            for (EdgeEx.Init(CmpOfEdges, TopAbs_EDGE); EdgeEx.More(); EdgeEx.Next())
            {
              TopoDS_Edge newEdge = TopoDS::Edge(EdgeEx.Current());
              FABU.AddEdgeWire(newEdge, newWire);
            }
          }
          else
          {

            NCollection_List<TopoDS_Shape> LofAddE;
            int                            naddsame = 0;
            while (ne > (LofAddE.Extent() + naddsame))
            {
              for (int StepMap = 1; StepMap <= mapVOE.Extent(); StepMap++)
              {
                const NCollection_List<TopoDS_Shape>&    LofE = mapVOE.FindFromIndex(StepMap);
                NCollection_List<TopoDS_Shape>::Iterator itLofE(LofE);
                TopoDS_Edge                              E1 = TopoDS::Edge(itLofE.Value());
                itLofE.Next();
                TopoDS_Edge        E2       = TopoDS::Edge(itLofE.Value());
                TopAbs_Orientation O1       = E1.Orientation();
                TopAbs_Orientation O2       = E2.Orientation();
                bool               IsSameE1 = BRep_Tool::IsClosed(E1, tdF);
                bool               IsSameE2 = BRep_Tool::IsClosed(E2, tdF);
                bool               AddE1    = true;
                bool               AddE2    = true;

                NCollection_List<TopoDS_Shape>::Iterator itLofAddE(LofAddE);
                for (; itLofAddE.More(); itLofAddE.Next())
                {
                  const TopoDS_Shape& LE  = itLofAddE.Value();
                  TopAbs_Orientation  OLE = LE.Orientation();
                  if (E1.IsSame(LE) && !IsSameE1)
                  {
                    AddE1 = false;
                    E1.Orientation(OLE);
                    O1 = OLE;
                  }
                  if (E2.IsSame(LE) && !IsSameE2)
                  {
                    AddE2 = false;
                    E2.Orientation(OLE);
                    O2 = OLE;
                  }
                }
                int chkORI = FUN_CheckORI(O1, O2);
                if (chkORI == 0)
                {
                  AddE1 = false;
                  AddE2 = false;
                }
                if (chkORI == 1)
                {
                  TopAbs_Orientation ori = FUN_ReOrientIntExtEdge(E2, O2, E1);
                  if (ori == TopAbs_FORWARD)
                  {
                    E1.Orientation(TopAbs_FORWARD);
                  }
                  if (ori == TopAbs_REVERSED)
                  {
                    E1.Orientation(TopAbs_REVERSED);
                  }
                  if (ori == TopAbs_REVERSED || ori == TopAbs_FORWARD)
                  {
                    if (O1 == TopAbs_INTERNAL)
                      neINTERNAL--;
                    else
                      neEXTERNAL--;
                  }
                }
                if (chkORI == 2)
                {
                  TopAbs_Orientation ori = FUN_ReOrientIntExtEdge(E1, O1, E2);
                  if (ori == TopAbs_FORWARD)
                  {
                    E2.Orientation(TopAbs_FORWARD);
                  }
                  if (ori == TopAbs_REVERSED)
                  {
                    E2.Orientation(TopAbs_REVERSED);
                  }
                  if (ori == TopAbs_REVERSED || ori == TopAbs_FORWARD)
                  {
                    if (O2 == TopAbs_INTERNAL)
                      neINTERNAL--;
                    else
                      neEXTERNAL--;
                  }
                }

                if (AddE1)
                {
                  FABU.AddEdgeWire(E1, newWire);
                  if (!IsSameE1)
                    LofAddE.Append(E1);
                  else
                    naddsame++;
                }
                if (AddE2)
                {
                  FABU.AddEdgeWire(E2, newWire);
                  if (!IsSameE2)
                    LofAddE.Append(E2);
                  else
                    naddsame++;
                }
              }
            }
          }
        }
      }

#ifdef OCCT_DEBUG
      if (tSPS)
        std::cout << "#--- GFABUMakeFaces " << iF << " : " << ne << " edges" << std::endl;
#endif

      if (ne != 0)
      {
        int iow = isold ? 1 : 0;
        MWisOld.Bind(newWire, iow);
      }

      if (!isold)
      {
        if (ne == 0)
          continue;
        else if (nbw == 1 && (ne == neINTERNAL + neEXTERNAL))
          continue;
        else
          nbnewWwithe++;
      }

      if (!isold)
      {
        bool closed = FUN_tool_ClosedW(newWire);
        myBuildTool.Closed(newWire, closed);
      }

      myBuildTool.AddFaceWire(newFace, newWire);
    }

    if (nbnewWwithe == 0 && nboldW == 0)
    {
      continue;
    }

    bool topurge = FUN_purgeFon1nonoriE(newFace);
    if (topurge)
    {
      continue;
    }

    occ::handle<Standard_Type> T      = Surf->DynamicType();
    bool                       istrim = (T == STANDARD_TYPE(Geom_RectangularTrimmedSurface));
    if (istrim)
    {
      occ::handle<Geom_RectangularTrimmedSurface> hrts =
        occ::down_cast<Geom_RectangularTrimmedSurface>(Surf);
      double oumin, oumax, ovmin, ovmax;
      hrts->Bounds(oumin, oumax, ovmin, ovmax);
      double umin, umax, vmin, vmax;
      BRepTools::UVBounds(newFace, umin, umax, vmin, vmax);
      if (umin < oumin)
        oumin = umin;
      if (umax > oumax)
        oumax = umax;
      if (vmin < ovmin)
        ovmin = vmin;
      if (vmax > ovmax)
        ovmax = vmax;
      hrts->SetTrim(oumin, oumax, ovmin, ovmax, true, true);
    }
    lnewFace.Append(newFace);
  }

#ifdef OCCT_DEBUG
  if (tSPS)
  {
    std::cout << std::endl;
    GdumpSHA(FF, (char*)"#--- GFABUMakeFaces avant regularize");
    std::cout << std::endl;
    GdumpFABU(FABU);
    debgfabu(iF);
  }
#endif

  LOF.Append(lnewFace);
}
