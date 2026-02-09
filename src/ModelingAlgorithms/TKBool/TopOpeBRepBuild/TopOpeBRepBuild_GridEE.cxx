#include <gp_Pnt.hpp>
#include <TopOpeBRepBuild_define.hpp>
#include <TopOpeBRepBuild_EdgeBuilder.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_PaveSet.hpp>
#include <TopOpeBRepDS_CurveIterator.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_PointIterator.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>

#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_TOOL.hpp>
#include <TopOpeBRepDS_TKI.hpp>
#include <TopOpeBRepDS.hpp>
#include <BRep_Tool.hpp>
#include <TopoDS.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Plane.hpp>
#include <gp_Pnt2d.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <TopOpeBRepTool_2d.hpp>
#include <Standard_ProgramError.hpp>
#include <TopOpeBRepDS_EdgeVertexInterference.hpp>

#ifdef OCCT_DEBUG
Standard_EXPORT bool TopOpeBRepBuild_GetcontextNOSG();
#endif

#define M_FORWARD(st) (st == TopAbs_FORWARD)
#define M_REVERSED(st) (st == TopAbs_REVERSED)
#define M_INTERNAL(st) (st == TopAbs_INTERNAL)
#define M_EXTERNAL(st) (st == TopAbs_EXTERNAL)

bool TopOpeBRepBuild_FUN_aresamegeom(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

void TopOpeBRepBuild_Builder::GMergeEdges(const NCollection_List<TopoDS_Shape>& LE1,
                                          const NCollection_List<TopoDS_Shape>& LE2,
                                          const TopOpeBRepBuild_GTopo&          G1)
{
  if (LE1.IsEmpty())
    return;
  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);

  const TopoDS_Shape& E1 = LE1.First();
#ifdef OCCT_DEBUG
  int  iE;
  bool tSPS1 = GtraceSPS(E1, iE);
  if (tSPS1)
  {
    std::cout << std::endl;
    std::cout << "--- GMergeEdges " << std::endl;
    GdumpEDG(E1);
    GdumpSAMDOM(LE1, (char*)"1 : ");
    GdumpSAMDOM(LE2, (char*)"2 : ");
  }
#endif

  myEdgeReference = TopoDS::Edge(E1);
  TopOpeBRepBuild_PaveSet PVS(E1);

  GFillEdgesPVS(LE1, LE2, G1, PVS);

  TopoDS_Shape E1F = LE1.First();
  E1F.Orientation(TopAbs_FORWARD);
  TopOpeBRepBuild_PaveClassifier VCL(E1F);
  bool                           equalpar = PVS.HasEqualParameters();
  if (equalpar)
    VCL.SetFirstParameter(PVS.EqualParameters());
  TopOpeBRepBuild_EdgeBuilder EDBU(PVS, VCL);

  NCollection_List<TopoDS_Shape> LEM;
  GEDBUMakeEdges(E1F, EDBU, LEM);

  NCollection_List<TopoDS_Shape>::Iterator it1;
  for (it1.Initialize(LE1); it1.More(); it1.Next())
  {
    const TopoDS_Shape& E11 = it1.Value();
    ChangeMerged(E11, TB1)  = LEM;
  }

  NCollection_List<TopoDS_Shape>::Iterator it2;
  for (it2.Initialize(LE2); it2.More(); it2.Next())
  {
    const TopoDS_Shape& E2 = it2.Value();
    ChangeMerged(E2, TB2)  = LEM;
  }
}

void TopOpeBRepBuild_Builder::GFillEdgesPVS(const NCollection_List<TopoDS_Shape>& LE1,
                                            const NCollection_List<TopoDS_Shape>& LE2,
                                            const TopOpeBRepBuild_GTopo&          G1,
                                            TopOpeBRepBuild_PaveSet&              PVS)
{
  if (LE1.IsEmpty())
    return;
  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);

  const TopoDS_Shape& E1 = LE1.First();
  myEdgeReference        = TopoDS::Edge(E1);

  NCollection_List<TopoDS_Shape>::Iterator it1;
  for (it1.Initialize(LE1); it1.More(); it1.Next())
  {
    const TopoDS_Shape& E11      = it1.Value();
    bool                ismerged = IsMerged(E11, TB1);

#ifdef OCCT_DEBUG
    int  i1;
    bool tSPS1 = GtraceSPS(E11, i1);
    if (tSPS1)
    {
      std::cout << std::endl;
      std::cout << "--- GFillEdgesPVS ";
      GdumpSHA(E11);
      std::cout << " ismerged : " << ismerged << " ";
      TopAbs::Print(TB1, std::cout);
      std::cout << std::endl;
    }
#endif

    if (!ismerged)
      GFillEdgePVS(E11, LE2, G1, PVS);
  }

  TopOpeBRepBuild_GTopo G2 = G1.CopyPermuted();

  NCollection_List<TopoDS_Shape>::Iterator it2;
  for (it2.Initialize(LE2); it2.More(); it2.Next())
  {
    const TopoDS_Shape& E2       = it2.Value();
    bool                ismerged = IsMerged(E2, TB2);

#ifdef OCCT_DEBUG
    int  i2;
    bool tSPS2 = GtraceSPS(E2, i2);
    if (tSPS2)
    {
      std::cout << std::endl;
      std::cout << "--- GFillEdgesPVS ";
      GdumpSHA(E2);
      std::cout << " ismerged : " << ismerged << " ";
      TopAbs::Print(TB2, std::cout);
      std::cout << std::endl;
    }
#endif

    if (!ismerged)
      GFillEdgePVS(E2, LE1, G2, PVS);
  }
}

void TopOpeBRepBuild_Builder::GFillEdgePVS(const TopoDS_Shape& E,
                                           const NCollection_List<TopoDS_Shape>&,
                                           const TopOpeBRepBuild_GTopo& G,
                                           TopOpeBRepBuild_PaveSet&     PVS)
{
  TopAbs_ShapeEnum t1, t2;
  G.Type(t1, t2);
  TopAbs_State TB1, TB2;
  G.StatesON(TB1, TB2);

  TopoDS_Shape EF = E;
  EF.Orientation(TopAbs_FORWARD);

  GFillPointTopologyPVS(EF, G, PVS);
}

static bool FUN_MoreSHAINT(TopOpeBRepDS_PointIterator& EPit, const TopAbs_ShapeEnum SHA)
{
  bool more = false;
  while (EPit.More())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I = EPit.Value();
    const TopOpeBRepDS_Transition&                T = I->Transition();
    TopOpeBRepDS_Kind                             GT, ST;
    int                                           G, S;
    FDS_data(I, GT, G, ST, S);
    TopAbs_ShapeEnum SB, SA;
    int              IB, IA;
    FDS_Tdata(I, SB, IB, SA, IA);

    TopAbs_ShapeEnum b = T.ShapeBefore(), a = T.ShapeAfter();
    bool             rejet = ((b != SHA) || (a != SHA));
    if (rejet)
      EPit.Next();
    else
    {
      more = true;
      break;
    }
  }
  return more;
}

#ifdef OCCT_DEBUG
void debfillp(const int i)
{
  std::cout << "+ + debfillp " << i << std::endl;
}

void debfillpon(const int i)
{
  std::cout << "+ + debfillpon " << i << std::endl;
}

void debfillpin(const int i)
{
  std::cout << "+ + debfillpin " << i << std::endl;
}

void debfillpou(const int i)
{
  std::cout << "+ + debfillpou " << i << std::endl;
}

void debfillp2(const int i)
{
  std::cout << "+ + debfillp2 " << i << std::endl;
}
#endif

extern bool GLOBAL_faces2d;

Standard_EXPORT bool FDS_SIisGIofIofSBAofTofI(const TopOpeBRepDS_DataStructure&             BDS,
                                              const int                                     SI,
                                              const occ::handle<TopOpeBRepDS_Interference>& I);

Standard_IMPORT bool GLOBAL_IEtoMERGE;

extern int GLOBAL_issp;

Standard_IMPORT int GLOBAL_hassd;

static bool FUN_isonbound(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                          const occ::handle<TopOpeBRepDS_Interference>&   I)
{
  int               G   = I->Geometry();
  TopOpeBRepDS_Kind KG  = I->GeometryType();
  bool              Gb1 = (KG == TopOpeBRepDS_VERTEX);
  if (Gb1)
  {
    occ::handle<TopOpeBRepDS_EdgeVertexInterference> EVI =
      occ::down_cast<TopOpeBRepDS_EdgeVertexInterference>(I);
    bool vhassd = HDS->HasSameDomain(HDS->DS().Shape(G));
    Gb1         = (EVI.IsNull()) ? false : EVI->GBound();
    Gb1         = Gb1 && !vhassd;
  }
  return Gb1;
}

#define TheIN (1)
#define TheON (2)
#define TheOUT (3)
#define HASSD2d (2)
#define HASSD3d (3)
#define FIRST (1)
#define LAST (2)

void TopOpeBRepBuild_Builder::GFillPointTopologyPVS(const TopoDS_Shape&          E,
                                                    const TopOpeBRepBuild_GTopo& G,
                                                    TopOpeBRepBuild_PaveSet&     PVS)
{
#ifdef OCCT_DEBUG

#endif
  TopAbs_ShapeEnum t1, t2, ShapeInterf;
  G.Type(t1, t2);
  ShapeInterf                            = t1;
  const TopOpeBRepDS_DataStructure& BDS  = myDataStructure->DS();
  const int                         iEDS = BDS.Shape(E);
#ifdef OCCT_DEBUG

#endif
  bool isSE = BDS.IsSectionEdge(TopoDS::Edge(E));
  bool dgE  = BRep_Tool::Degenerated(TopoDS::Edge(E));
  bool isEd;

  isEd = BRep_Tool::Degenerated(TopoDS::Edge(E));
#ifdef OCCT_DEBUG

#endif
  bool isfafa = BDS.Isfafa();

#ifdef OCCT_DEBUG
  bool                    tSPSE = GtraceSPS(iEDS);
  TCollection_AsciiString striE = TopOpeBRepDS::SPrint(TopAbs_EDGE, iEDS);
  const TopoDS_Shape&     EPVS  = PVS.Edge();
  int                     iEPVS;
  bool                    tSPSEPVS = GtraceSPS(EPVS, iEPVS);
  bool                    tSPS     = tSPSE || tSPSEPVS;
  if (tSPS)
  {
    std::cout << std::endl;
    std::cout << "--- GFillPointTopologyPVS : ShapeInterf ";
    TopAbs::Print(ShapeInterf, std::cout);
    std::cout << ",efil ";
    GdumpSHA(E);
    std::cout << ",eref ";
    GdumpSHA(myEdgeReference);
    std::cout << ",ffil ";
    GdumpSHA(myFaceToFill);
    std::cout << ",fref ";
    GdumpSHA(myFaceReference);
    std::cout << std::endl;
    debfillp(iEDS);
  }
#endif

  bool isspin = (GLOBAL_issp == TheIN), isspou = (GLOBAL_issp == TheOUT),
       isspon = (GLOBAL_issp == TheON);
  if (isSE && (GLOBAL_issp == 0))
    return;

#ifdef OCCT_DEBUG

  if (tSPS)
  {
    if (isspon)
      debfillpon(iEDS);
    if (isspin)
      debfillpin(iEDS);
    if (isspou)
      debfillpou(iEDS);
  }
#endif

  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lIE = BDS.ShapeInterferences(E);

  bool scanall = (isspin || isspou || isspon);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> loiSHAINT;
  if (scanall)
    FDS_assign(lIE, loiSHAINT);
  else
  {
    TopOpeBRepDS_PointIterator EPit(lIE);
    EPit.Init(BDS.ShapeInterferences(E));
    bool addi = FUN_MoreSHAINT(EPit, ShapeInterf);
    while (addi)
    {
      const occ::handle<TopOpeBRepDS_Interference>& II = EPit.Value();
      loiSHAINT.Append(II);
      EPit.Next();
      addi = FUN_MoreSHAINT(EPit, ShapeInterf);
    }
  }

  TopOpeBRepDS_TKI tki;
  tki.FillOnGeometry(loiSHAINT);

  TopoDS_Vertex vclo;
  bool          closedE = TopOpeBRepTool_TOOL::ClosedE(TopoDS::Edge(E), vclo);
  int           kp1     = 0;
  if (closedE)
  {
    tki.Init();
    int nG = 0;
    while (tki.More())
    {
      nG++;
      TopOpeBRepDS_Kind Kcur;
      int               Gcur;
      tki.Value(Kcur, Gcur);
      if (Kcur == TopOpeBRepDS_POINT)
      {
        tki.Next();
        continue;
      }
      const TopoDS_Shape& v = BDS.Shape(Gcur);
      TopoDS_Shape        oov;
      FUN_ds_getoov(v, myDataStructure, oov);
      bool samev = v.IsSame(vclo), sameoov = oov.IsSame(vclo);
      if (samev || sameoov)
      {
        kp1 = Gcur;
      }
      tki.Next();
    }
    if (nG == 1)
      kp1 = 0;
  }

  bool kp6 = (!isSE);
  if (kp6)
  {
    kp6 = false;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(loiSHAINT);
    for (; it.More(); it.Next())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I  = it.Value();
      TopOpeBRepDS_Kind                             ST = I->SupportType();
      if (ST != TopOpeBRepDS_FACE)
        continue;
      TopAbs_Orientation O      = I->Transition().Orientation(TopAbs_IN);
      bool               FORREV = (O == TopAbs_FORWARD) || (O == TopAbs_REVERSED);
      if (!FORREV)
        continue;
      bool Gb1 = ::FUN_isonbound(myDataStructure, I);
      if (!Gb1)
      {
        kp6 = true;
        break;
      }
    }
  }

  tki.Init();
  while (tki.More())
  {

    TopOpeBRepDS_Kind                                               Kcur;
    int                                                             Gcur;
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LICur = tki.Value(Kcur, Gcur);
    bool         point  = (Kcur == TopOpeBRepDS_POINT);
    bool         vertex = (Kcur == TopOpeBRepDS_VERTEX);
    TopoDS_Shape vGsd;
    if (vertex)
      FUN_ds_getoov(BDS.Shape(Gcur), myDataStructure, vGsd);

    if ((Kcur == TopOpeBRepDS_VERTEX) && (kp1 == Gcur))
    {
      tki.Next();
      continue;
    }
    const occ::handle<TopOpeBRepDS_Interference>&            I     = LICur.First();
    double                                                   parSE = FDS_Parameter(I);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> LICurcopy;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l3dFcur;
    FDS_assign(LICur, LICurcopy);
    int n3d = FUN_selectSKinterference(LICurcopy, TopOpeBRepDS_FACE, l3dFcur);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l2dFEcur;
    FDS_assign(LICur, LICurcopy);
    int n2d = FUN_ds_hasI2d(iEDS, LICurcopy, l2dFEcur);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l1dEcur;
    FDS_assign(LICur, LICurcopy);
    FUN_selectTRASHAinterference(LICurcopy, TopAbs_EDGE, l1dEcur);

    TopAbs_State stb;
    int          isb;
    int          bdim;
    TopAbs_State sta;
    int          isa;
    int          adim;
    FUN_ds_GetTr(BDS, iEDS, Gcur, LICur, stb, isb, bdim, sta, isa, adim);
    if (isSE)
    {

      bool bIN1d = (stb == TopAbs_IN) && (bdim == 1);
      bool bIN2d = (stb == TopAbs_IN) && (bdim == 2);
      bool bIN3d = (stb == TopAbs_IN) && (bdim == 3);

      bool bOUT2d = (stb == TopAbs_OUT) && (bdim == 2);
      bool bOUT3d = (stb == TopAbs_OUT) && (bdim == 3);

      bool aIN1d = (sta == TopAbs_IN) && (adim == 1);
      bool aIN2d = (sta == TopAbs_IN) && (adim == 2);
      bool aIN3d = (sta == TopAbs_IN) && (adim == 3);

      bool aOUT2d = (sta == TopAbs_OUT) && (adim == 2);
      bool aOUT3d = (sta == TopAbs_OUT) && (adim == 3);

      TopOpeBRepDS_Transition newT;
      bool                    INb = false, INa = false;
      if (isfafa)
      {
        if (isspon)
        {
          if ((stb == TopAbs_OUT) && (sta == TopAbs_OUT))
          {
            tki.Next();
            continue;
          }
          INb = bIN1d;
          INa = aIN1d;
          newT.Index(isb);
          newT.ShapeBefore(TopAbs_EDGE);
          newT.ShapeAfter(TopAbs_EDGE);
        }
        else if (isspin)
        {
          INb = bIN2d;
          INa = aIN2d;
          newT.ShapeBefore(TopAbs_FACE);
          newT.ShapeAfter(TopAbs_FACE);
        }
        else if (isspou)
        {
          INb = !bOUT2d;
          INa = !aOUT2d;
          newT.ShapeBefore(TopAbs_FACE);
          newT.ShapeAfter(TopAbs_FACE);
        }
      }
      else
      {
        if (isspon)
        {
          if ((stb == TopAbs_OUT) && (sta == TopAbs_OUT))
          {
            tki.Next();
            continue;
          }
          INb = bIN1d || bIN2d;
          INa = aIN1d || aIN2d;
          newT.Index(isb);
          newT.ShapeBefore(TopAbs_EDGE);
          newT.ShapeAfter(TopAbs_EDGE);
        }
        else if (isspin)
        {
          if ((stb == TopAbs_OUT) && (sta == TopAbs_OUT))
          {
            tki.Next();
            continue;
          }
          INb = bIN3d;
          INa = aIN3d;
          if (INb)
            newT.Index(isb);
          else
            newT.Index(isa);
          newT.ShapeBefore(TopAbs_FACE);
          newT.ShapeAfter(TopAbs_FACE);
        }
        else if (isspou)
        {
          if ((stb == TopAbs_IN) && (sta == TopAbs_IN))
          {
            tki.Next();
            continue;
          }
          INb = !bOUT3d;
          INa = !aOUT3d;
          if (bOUT3d)
            newT.Index(isb);
          else
            newT.Index(isa);
          newT.ShapeBefore(TopAbs_FACE);
          newT.ShapeAfter(TopAbs_FACE);
        }
      }
      TopAbs_State sb = INb ? TopAbs_IN : TopAbs_OUT;
      TopAbs_State sa = INa ? TopAbs_IN : TopAbs_OUT;
      newT.StateBefore(sb);
      newT.StateAfter(sa);
      int                                    S = 0;
      bool                                   B = (Kcur == TopOpeBRepDS_POINT)
                                                   ? false
                                                   : (occ::down_cast<TopOpeBRepDS_EdgeVertexInterference>(I)->GBound());
      occ::handle<TopOpeBRepDS_Interference> newI =
        MakeEPVInterference(newT, S, Gcur, parSE, Kcur, B);

      NCollection_List<occ::handle<TopOpeBRepDS_Interference>> li;
      li.Append(newI);
      TopOpeBRepDS_PointIterator itCur(li);
      GFillPointTopologyPVS(E, itCur, G, PVS);
      {
        tki.Next();
        continue;
      }
    }

    bool kp3 = (n2d > 0) && point;
    if (kp3)
      l2dFEcur.First()->Transition().Orientation(TopAbs_IN);

    TopOpeBRepDS_PointIterator itCur(LICur);
    while (itCur.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I1 = itCur.Value();
      const TopOpeBRepDS_Transition&                T1 = I1->Transition();
      T1.Orientation(TopAbs_IN);
      TopAbs_ShapeEnum  SB1, SA1;
      int               IB1, IA1;
      TopOpeBRepDS_Kind GT1, ST1;
      int               G1, S1;
      FDS_Idata(I1, SB1, IB1, SA1, IA1, GT1, G1, ST1, S1);

      bool keepinterf1 = false;
      if (isEd)
      {
        keepinterf1 = true;
      }
      else
      {
        if (GLOBAL_faces2d)
        {
          bool has2d3d = (n2d > 0 && n3d > 0);

          if (has2d3d && !isSE)
          {
#ifdef OCCT_DEBUG
            const occ::handle<TopOpeBRepDS_Interference>& i2d =
#endif
              l2dFEcur.First();
            const occ::handle<TopOpeBRepDS_Interference>& i3d  = l3dFcur.First();
            bool                                          id3d = (I1 == i3d);
            keepinterf1                                        = id3d;
#ifdef OCCT_DEBUG
            bool id2d = (I1 == i2d);
            if (tSPS)
            {
              std::cout << "DEB : GFillPointTopologyPVS E" << iEDS << " has2d3d" << std::endl;
              if (id3d)
                std::cout << "--> Interference 3d ";
              if (id2d)
                std::cout << "--> Interference 2d ";
              if (keepinterf1)
                std::cout << " traitee" << std::endl;
              else
                std::cout << " non traitee" << std::endl;
              std::cout << std::endl;
            }
#endif
          }
          else
          {
            keepinterf1 = true;
          }
        }
        else
        {
          keepinterf1 = (ST1 == TopOpeBRepDS_FACE);
        }
      }
      if (keepinterf1)
      {
        if (kp6)
        {
          bool Gb1 = ::FUN_isonbound(myDataStructure, I1);
          if (!Gb1)
            GFillPointTopologyPVS(E, itCur, G, PVS);
        }
        else
        {
          GFillPointTopologyPVS(E, itCur, G, PVS);
        }
        if (!dgE)
          break;
      }
      itCur.Next();
    }

    tki.Next();
  }
}

void TopOpeBRepBuild_Builder::GFillPointTopologyPVS(const TopoDS_Shape&               E,
                                                    const TopOpeBRepDS_PointIterator& EPit,
                                                    const TopOpeBRepBuild_GTopo&      G1,
                                                    TopOpeBRepBuild_PaveSet&          PVS) const
{
  const TopoDS_Shape& EPVS = PVS.Edge();

  const occ::handle<TopOpeBRepDS_Interference>& I1  = EPit.Value();
  TopOpeBRepDS_Kind                             ST1 = I1->SupportType();

#ifdef OCCT_DEBUG
  int  iE;
  bool tSPSE = GtraceSPS(E, iE);
  int  iEPVS;
  bool tSPSEPVS = GtraceSPS(EPVS, iEPVS);
  bool tSPS     = tSPSE || tSPSEPVS;
  if (tSPS)
    debfillp(iE);
#endif

  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);
  TopOpeBRepDS_Config Conf = G1.Config1();
  TopAbs_State        TB   = TB1;

  int           iG      = EPit.Current();
  bool          ispoint = EPit.IsPoint();
  TopoDS_Vertex VIG;
  if (ispoint)
    VIG = TopoDS::Vertex(NewVertex(iG));
  else
    VIG = TopoDS::Vertex(myDataStructure->Shape(iG));

  if (VIG.IsNull())
    return;

  bool         hasVSD = false;
  int          iVRE   = 0;
  TopoDS_Shape VRE;
  if (!ispoint)
  {
    hasVSD = myDataStructure->HasSameDomain(VIG);
    if (hasVSD)
    {
      iVRE = myDataStructure->SameDomainReference(VIG);
      VRE  = TopoDS::Vertex(myDataStructure->Shape(iVRE));
    }
  }

  TopoDS_Vertex VPV;
  if (hasVSD)
    VPV = TopoDS::Vertex(VRE);
  else
    VPV = VIG;

  double             par = EPit.Parameter();
  TopAbs_Orientation ori = EPit.Orientation(TB);

#ifdef OCCT_DEBUG
  if (tSPS)
    debfillp(iE);
#endif

  bool samegeom = ::TopOpeBRepBuild_FUN_aresamegeom(E, EPVS);
  if (Conf == TopOpeBRepDS_DIFFORIENTED)
    ori = TopAbs::Complement(ori);
#ifdef OCCT_DEBUG
  if (!TopOpeBRepBuild_GetcontextNOSG())
  {
#endif
    if (!samegeom)
      ori = TopAbs::Complement(ori);
#ifdef OCCT_DEBUG
  }
#endif

  bool lesmemes = E.IsEqual(myEdgeReference);
  if (!lesmemes)
  {
    double             parref = par;
    const TopoDS_Edge& EE     = TopoDS::Edge(E);
    GParamOnReference(VPV, EE, parref);
#ifdef OCCT_DEBUG
    if (tSPS)
    {
      std::cout << "par " << par << " / ";
      GdumpSHA(E);
      std::cout << " --> parref " << parref << " / ";
      GdumpSHA(EPVS);
      std::cout << std::endl;
    }
#endif
    par = parref;
  }

  bool kpbound = false;
  {
    TopoDS_Vertex vclo;
    bool          Eclosed = TopOpeBRepTool_TOOL::ClosedE(myEdgeReference, vclo);
#ifdef OCCT_DEBUG

#endif
    TopAbs_Orientation oriI = EPit.Orientation(TopAbs_IN);

    bool INTEXT = (oriI == TopAbs_INTERNAL) && (TB == TopAbs_IN);
    INTEXT      = INTEXT || ((oriI == TopAbs_EXTERNAL) && (TB == TopAbs_OUT));
    kpbound     = lesmemes && Eclosed && INTEXT;
    if (kpbound)
    {
      kpbound = vclo.IsSame(VIG);
      if (!kpbound)
      {
        TopoDS_Shape VSD;
        bool         ok = FUN_ds_getoov(VIG, myDataStructure->DS(), VSD);
        if (ok)
          kpbound = vclo.IsSame(VSD);
      }
    }
  }

  if (!kpbound)
  {
    VPV.Orientation(ori);
    bool                              vofe = false;
    occ::handle<TopOpeBRepBuild_Pave> PV   = new TopOpeBRepBuild_Pave(VPV, par, vofe);
    if (hasVSD)
    {
      PV->HasSameDomain(true);
      const TopoDS_Shape& VSD  = myDataStructure->DS().ShapeSameDomain(VPV).First();
      int                 iVSD = myDataStructure->Shape(VSD);
      if (iVSD == iVRE)
        PV->SameDomain(VIG);
      else
        PV->SameDomain(VSD);
    }

    PV->InterferenceType() = ST1;
    PVS.Append(PV);

#ifdef OCCT_DEBUG
    gp_Pnt P = BRep_Tool::Pnt(VPV);
    if (tSPS)
    {
      std::cout << "+";
      if (ispoint)
        std::cout << " PDS ";
      else
        std::cout << " VDS ";
    }
    if (tSPS)
    {
      std::cout << iG << " : ";
      GdumpORIPARPNT(ori, par, P);
      std::cout << std::endl;
    }
    if (tSPS)
    {
    }
#endif
  }
  else
  {
    double parf, parl;
    FUN_tool_bounds(myEdgeReference, parf, parl);
    TopAbs_Orientation ovpv;
    ovpv = TopAbs_FORWARD;
    VPV.Orientation(ovpv);
    bool                              vfofe = false;
    occ::handle<TopOpeBRepBuild_Pave> PVF   = new TopOpeBRepBuild_Pave(VPV, parf, vfofe);
    if (hasVSD)
    {
      PVF->HasSameDomain(true);
      const TopoDS_Shape& VSD  = myDataStructure->DS().ShapeSameDomain(VPV).First();
      int                 iVSD = myDataStructure->Shape(VSD);
      if (iVSD == iVRE)
        PVF->SameDomain(VIG);
      else
        PVF->SameDomain(VSD);
    }

    PVF->InterferenceType() = ST1;
    PVS.Append(PVF);

#ifdef OCCT_DEBUG
    gp_Pnt PF = BRep_Tool::Pnt(VPV);
    if (tSPS)
    {
      std::cout << "+";
      if (ispoint)
        std::cout << " PDS ";
      else
        std::cout << " VDS ";
    }
    if (tSPS)
    {
      std::cout << iG << " : ";
      GdumpORIPARPNT(ovpv, parf, PF);
      std::cout << std::endl;
    }
#endif

    ovpv = TopAbs_REVERSED;
    VPV.Orientation(ovpv);
    bool                              vrofe = false;
    occ::handle<TopOpeBRepBuild_Pave> PVR   = new TopOpeBRepBuild_Pave(VPV, parl, vrofe);
    if (hasVSD)
    {
      PVR->HasSameDomain(true);
      const TopoDS_Shape& VSD  = myDataStructure->DS().ShapeSameDomain(VPV).First();
      int                 iVSD = myDataStructure->Shape(VSD);
      if (iVSD == iVRE)
        PVR->SameDomain(VIG);
      else
        PVR->SameDomain(VSD);
    }

    PVR->InterferenceType() = ST1;
    PVS.Append(PVR);
#ifdef OCCT_DEBUG
    gp_Pnt PR = BRep_Tool::Pnt(VPV);
    if (tSPS)
    {
      std::cout << "+";
      if (ispoint)
        std::cout << " PDS ";
      else
        std::cout << " VDS ";
    }
    if (tSPS)
    {
      std::cout << iG << " : ";
      GdumpORIPARPNT(ovpv, parl, PR);
      std::cout << std::endl;
    }
#endif

    PVS.RemovePV(false);
  }
}

bool TopOpeBRepBuild_Builder::GParamOnReference(const TopoDS_Vertex& V,
                                                const TopoDS_Edge&,
                                                double& P) const
{
  occ::handle<Geom_Surface> su     = BRep_Tool::Surface(myFaceReference);
  occ::handle<Geom_Plane>   suplan = occ::down_cast<Geom_Plane>(su);
  if (suplan.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "NYI : GParamOnReference : not planar" << std::endl;
#endif
    return false;
  }

  gp_Pln pln = suplan->Pln();
  gp_Pnt p3  = BRep_Tool::Pnt(V);
  double u, v;
  ElSLib::Parameters(pln, p3, u, v);
  gp_Pnt2d                  p2(u, v);
  double                    f, l, tolpc;
  occ::handle<Geom2d_Curve> C2D;
  C2D = FC2D_CurveOnSurface(myEdgeReference, myFaceReference, f, l, tolpc);
  if (C2D.IsNull())
    throw Standard_ProgramError("TopOpeBRepBuild_Builder::GParamOnReference");

  Geom2dAdaptor_Curve AC(C2D);
  switch (AC.GetType())
  {
    case GeomAbs_Line:
      P = ElCLib::Parameter(AC.Line(), p2);
      break;
    case GeomAbs_Circle:
      P = ElCLib::Parameter(AC.Circle(), p2);
      break;
    case GeomAbs_Ellipse:
      P = ElCLib::Parameter(AC.Ellipse(), p2);
      break;
    case GeomAbs_Hyperbola:
      P = ElCLib::Parameter(AC.Hyperbola(), p2);
      break;
    case GeomAbs_Parabola:
      P = ElCLib::Parameter(AC.Parabola(), p2);
      break;
    default:
#ifdef OCCT_DEBUG
      std::cout << "NYI : GParamOnReference : OtherCurve on planar surface" << std::endl;
#endif
      return false;
  }

  return true;
}
