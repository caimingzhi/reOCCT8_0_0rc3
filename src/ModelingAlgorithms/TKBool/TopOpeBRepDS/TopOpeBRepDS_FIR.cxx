

#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopOpeBRepDS_FaceInterferenceTool.hpp>
#include <TopOpeBRepDS_FIR.hpp>
#include <TopOpeBRepDS_ListOfShapeOn1State.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>
#include <TopOpeBRepDS_ShapeData.hpp>
#include <TopOpeBRepDS_ShapeShapeInterference.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_SC.hpp>

#define MDSke TopOpeBRepDS_EDGE
#define MDSkf TopOpeBRepDS_FACE

Standard_EXPORT bool FUN_Parameters(const gp_Pnt& Pnt, const TopoDS_Shape& F, double& u, double& v);
Standard_EXPORT bool FUN_edgeofface(const TopoDS_Shape& E, const TopoDS_Shape& F);

bool FUN_isPonF(const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LIF,
                const gp_Pnt&                                                   P,
                const TopOpeBRepDS_DataStructure&                               BDS,
                const TopoDS_Edge&                                              E)
{
  bool              Pok = true;
  TopOpeBRepDS_Kind GT1, ST1;
  int               G1, S1;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itF(LIF);
  for (; itF.More(); itF.Next())
  {
    occ::handle<TopOpeBRepDS_Interference> IF = itF.Value();
    FDS_data(IF, GT1, G1, ST1, S1);
    const TopoDS_Face& F = TopoDS::Face(BDS.Shape(S1));
    TopAbs_Orientation oEinF;
    bool               edonfa = FUN_tool_orientEinFFORWARD(E, F, oEinF);
    if (edonfa)
      Pok = true;
    else
    {

      double u, v;
      Pok = FUN_Parameters(P, F, u, v);
      if (!Pok)
        break;
    }
  }
  return Pok;
}

bool FUN_findPonF(const TopoDS_Edge&                                              E,
                  const TopOpeBRepDS_DataStructure&                               BDS,
                  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LIF,
                  gp_Pnt&                                                         P,
                  double&                                                         par)
{
  bool                                                            Pok = false;
  BRepAdaptor_Curve                                               BAC(E);
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LIE = BDS.ShapeInterferences(E);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itI;
  itI.Initialize(LIE);

  if (!itI.More())
  {
    Pok = FUN_tool_findPinBAC(BAC, P, par);
    Pok = FUN_isPonF(LIF, P, BDS, E);
    return Pok;
  }

  TopOpeBRepDS_Kind GT1, ST1;
  int               G1, S1;
  for (; itI.More(); itI.Next())
  {
    bool pardef = false;

    occ::handle<TopOpeBRepDS_Interference>& I = itI.ChangeValue();
    FDS_data(I, GT1, G1, ST1, S1);
    occ::handle<TopOpeBRepDS_CurvePointInterference> CPI(
      occ::down_cast<TopOpeBRepDS_CurvePointInterference>(I));
    occ::handle<TopOpeBRepDS_ShapeShapeInterference> SSI(
      occ::down_cast<TopOpeBRepDS_ShapeShapeInterference>(I));
    if (!CPI.IsNull())
    {
      par    = CPI->Parameter();
      pardef = true;
    }
    else if (!SSI.IsNull())
    {
      bool gb = SSI->GBound();
      if (gb)
      {
        const TopoDS_Vertex& V = TopoDS::Vertex(BDS.Shape(G1));
        P                      = BRep_Tool::Pnt(V);
        par                    = BRep_Tool::Parameter(V, E);
        pardef                 = true;
      }
      else
      {
        pardef = false;
        if (GT1 == TopOpeBRepDS_POINT)
          P = BDS.Point(G1).Point();
        else if (GT1 == TopOpeBRepDS_VERTEX)
          P = BRep_Tool::Pnt(TopoDS::Vertex(BDS.Shape(G1)));
        if (pardef)
        {
          double dist;
          pardef = FUN_tool_projPonC(P, BAC, par, dist);
        }
      }
    }
    else
    {
      continue;
    }

    if (!pardef)
    {
      continue;
    }

    BAC.D0(par, P);
    Pok = FUN_isPonF(LIF, P, BDS, E);

    if (Pok)
    {
      break;
    }
  }
  return Pok;
}

static void FDS_ADDEDGE(const bool,
                        const TCollection_AsciiString&,
                        const int,
                        TopOpeBRepDS_FaceInterferenceTool&            FITool,
                        const TopoDS_Shape&                           FI,
                        const TopoDS_Shape&                           F,
                        const TopoDS_Shape&                           Ecpx,
                        const bool                                    isEGsp,
                        const occ::handle<TopOpeBRepDS_Interference>& I)
{
  FITool.Add(FI, F, Ecpx, isEGsp, I);
}

void FUN_reduceEDGEgeometry1(NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                             const TopOpeBRepDS_DataStructure&                         BDS,
                             const int                                                 iFI,
                             const int                                                 iEG,
                             const TopoDS_Shape&                                       EGsp,

                             const NCollection_DataMap<TopoDS_Shape,
                                                       TopOpeBRepDS_ListOfShapeOn1State,
                                                       TopTools_ShapeMapHasher>&)
{
  bool                                                               TRCF = false;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator ili(LI);
  if (!ili.More())
    return;

  const TopoDS_Face& FI     = TopoDS::Face(BDS.Shape(iFI));
  bool               isEGsp = (!EGsp.IsNull());
  TopoDS_Edge        Ecpx;
  if (isEGsp)
    Ecpx = TopoDS::Edge(EGsp);
  else
    Ecpx = TopoDS::Edge(BDS.Shape(iEG));

  TopOpeBRepDS_PDataStructure       pbds = (TopOpeBRepDS_PDataStructure)(void*)&BDS;
  TopOpeBRepDS_FaceInterferenceTool FITool(pbds);
  gp_Pnt                            Pok;
  bool                              isPok = false;
  double                            parPok;
  if (LI.Extent() >= 2)
  {
    if (isEGsp)
      isPok = FUN_tool_findPinE(Ecpx, Pok, parPok);
    else
      isPok = FUN_findPonF(Ecpx, BDS, LI, Pok, parPok);
    if (!isPok)
    {
      LI.Clear();
      return;
    }
    FITool.SetEdgePntPar(Pok, parPok);
  }

  occ::handle<TopOpeBRepDS_Interference>                             I1, I2;
  TopOpeBRepDS_Kind                                                  GT1, ST1, GT2, ST2;
  int                                                                G1, S1, G2, S2;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1;
  it1.Initialize(LI);
  while (it1.More())
  {
    bool u1 = FDS_data(it1, I1, GT1, G1, ST1, S1);
    if (u1)
    {
      it1.Next();
      continue;
    }
    bool ya1 = (GT1 == MDSke);
    if (!ya1)
    {
      it1.Next();
      continue;
    }

    bool               isComplex = false;
    const TopoDS_Face& F1        = TopoDS::Face(BDS.Shape(S1));

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(it1);
    it2.Next();
    while (it2.More())
    {
      bool u2 = FDS_data(it2, I2, GT2, G2, ST2, S2);
      if (u2)
      {
        it2.Next();
        continue;
      }
      bool ya2 = (GT2 == GT1 && G2 == G1 && ST2 == ST1);
      if (!ya2)
      {
        it2.Next();
        continue;
      }
      const TopoDS_Face& F2 = TopoDS::Face(BDS.Shape(S2));
      if (!isComplex)
      {
        isComplex = true;

        FITool.Init(FI, Ecpx, isEGsp, I1);
        FDS_ADDEDGE(TRCF, "\ninit transition complexe F", iFI, FITool, FI, F1, Ecpx, isEGsp, I1);
      }

      FDS_ADDEDGE(TRCF, "add transition complexe F", iFI, FITool, FI, F2, Ecpx, isEGsp, I2);

      LI.Remove(it2);
    }
    if (isComplex)
    {
      FITool.Transition(I1);
    }
    it1.Next();
  }
}

void FUN_GmapS(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&                                  LI,
  const TopOpeBRepDS_DataStructure&                                                          BDS,
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeData, TopTools_ShapeMapHasher>& mosd)
{
  mosd.Clear();
  TopOpeBRepDS_Kind GT1, ST1;
  int               G1, S1;
  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(LI); it1.More();
       it1.Next())
  {
    occ::handle<TopOpeBRepDS_Interference>& I1 = it1.ChangeValue();
    FDS_data(I1, GT1, G1, ST1, S1);
    if (GT1 != MDSke || ST1 != MDSkf)
      continue;
    const TopoDS_Shape&    SG1 = BDS.Shape(G1);
    TopOpeBRepDS_ShapeData thedata;
    if (!mosd.Contains(SG1))
      mosd.Add(SG1, thedata);
    mosd.ChangeFromKey(SG1).ChangeInterferences().Append(I1);
  }
}

TopAbs_State FUN_stateedgeface(const TopoDS_Shape& E, const TopoDS_Shape& F, gp_Pnt& P)
{
  TopAbs_State state = TopAbs_UNKNOWN;
  double       par;
  FUN_tool_findPinE(E, P, par);
  double u, v;
  bool   Pok = FUN_Parameters(P, F, u, v);
  if (Pok)
  {
    TopOpeBRepTool_ShapeClassifier& PSC = FSC_GetPSC(F);
    gp_Pnt2d                        Puv(u, v);
    PSC.StateP2DReference(Puv);
    state = PSC.State();
  }
  return state;
}

#define M_IN(ssstate) ((ssstate) == TopAbs_IN)
#define M_ON(ssstate) ((ssstate) == TopAbs_ON)
#define M_OUT(ssstate) ((ssstate) == TopAbs_OUT)
#define M_UNK(ssstate) ((ssstate) == TopAbs_UNK)

void FUN_reduceEDGEgeometry(NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                            const TopOpeBRepDS_DataStructure&                         BDS,
                            const int                                                 iFI,
                            const NCollection_DataMap<TopoDS_Shape,
                                                      TopOpeBRepDS_ListOfShapeOn1State,
                                                      TopTools_ShapeMapHasher>&       MEsp)
{
  if (!LI.Extent())
    return;

  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_ShapeData, TopTools_ShapeMapHasher> mosd;
  FUN_GmapS(LI, BDS, mosd);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> LIout;

  int i, aN;
  aN = mosd.Extent();

  for (i = 1; i <= aN; i++)
  {
    const TopoDS_Shape& EG  = mosd.FindKey(i);
    int                 iEG = BDS.Shape(EG);

    const NCollection_List<TopoDS_Shape>& esdeg    = BDS.ShapeSameDomain(iEG);
    bool                                  egissect = BDS.IsSectionEdge(TopoDS::Edge(EG));
    bool                                  eghasesd = (!esdeg.IsEmpty());

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LIEG =
      mosd.ChangeFromKey(EG).ChangeInterferences();
    int nExt = LIEG.Extent();

    if (nExt == 0)
    {
      continue;
    }
    if (nExt == 1)
    {
      LIout.Append(LIEG);
    }

    else if (nExt >= 2)
    {
      bool isEGsp = MEsp.IsBound(EG);

      if (isEGsp)
      {
        const TopOpeBRepDS_ListOfShapeOn1State& los1 = MEsp.Find(EG);
        isEGsp                                       = los1.IsSplit();
      }

      if (isEGsp)
      {
        const NCollection_List<TopoDS_Shape>&    los = MEsp.Find(EG).ListOnState();
        NCollection_List<TopoDS_Shape>::Iterator itlos(los);
        for (; itlos.More(); itlos.Next())
        {

          const TopoDS_Shape& EGsp = itlos.Value();

          NCollection_List<occ::handle<TopOpeBRepDS_Interference>>           LISFIN;
          NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itLIEG(LIEG);
          for (; itLIEG.More(); itLIEG.Next())
          {
            const occ::handle<TopOpeBRepDS_Interference>& ILIEG = itLIEG.Value();
            int                                           iS    = ILIEG->Support();
            TopOpeBRepDS_Kind                             kS    = ILIEG->SupportType();
            if (kS == MDSkf)
            {
              const TopoDS_Shape& SFILIEG = BDS.Shape(iS);
              gp_Pnt              P;
              TopAbs_State        staef = FUN_stateedgeface(EGsp, SFILIEG, P);

              bool Pok = M_IN(staef);
              if (eghasesd || egissect)
              {
                Pok = Pok || M_ON(staef);
              }

              if (Pok)
              {
                LISFIN.Append(ILIEG);
              }
            }
          }

          int nLISFIN = LISFIN.Extent();
          if (nLISFIN >= 2)
          {
            bool gb;
            gb = occ::down_cast<TopOpeBRepDS_ShapeShapeInterference>(LISFIN.First())->GBound();

            if (gb)
            {

              occ::handle<TopOpeBRepDS_Interference> anInterference = LISFIN.First();
              LISFIN.Clear();
              LISFIN.Append(anInterference);
            }
            else
              FUN_reduceEDGEgeometry1(LISFIN, BDS, iFI, iEG, EGsp, MEsp);
          }

          nLISFIN = LISFIN.Extent();
          if (nLISFIN)
            LIout.Append(LISFIN);
        }
      }
      else
      {

        TopoDS_Shape Enull;
        FUN_reduceEDGEgeometry1(LIEG, BDS, iFI, iEG, Enull, MEsp);
        LIout.Append(LIEG);
      }
    }
  }

  LI.Clear();
  LI.Append(LIout);
}

TopOpeBRepDS_FIR::TopOpeBRepDS_FIR(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
    : myHDS(HDS)
{
}

void TopOpeBRepDS_FIR::ProcessFaceInterferences(
  const NCollection_DataMap<TopoDS_Shape,
                            TopOpeBRepDS_ListOfShapeOn1State,
                            TopTools_ShapeMapHasher>& M)
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();
  int                         i, nshape = BDS.NbShapes();
  for (i = 1; i <= nshape; i++)
  {
    const TopoDS_Shape& S = BDS.Shape(i);
    if (S.IsNull())
      continue;
    if (S.ShapeType() == TopAbs_FACE)
    {
      ProcessFaceInterferences(i, M);
    }
  }
}

void TopOpeBRepDS_FIR::ProcessFaceInterferences(
  const int                                           SIX,
  const NCollection_DataMap<TopoDS_Shape,
                            TopOpeBRepDS_ListOfShapeOn1State,
                            TopTools_ShapeMapHasher>& MEsp)
{
  TopOpeBRepDS_DataStructure&                               BDS = myHDS->ChangeDS();
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI  = BDS.ChangeShapeInterferences(SIX);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>  lw, lE, lFE, lFEF, lF;
  lw.Assign(LI);

  ::FUN_selectTRASHAinterference(lw, TopAbs_FACE, lF);
  ::FUN_selectGKinterference(lF, MDSke, lFE);
  ::FUN_selectSKinterference(lFE, MDSkf, lFEF);
  ::FUN_selectTRASHAinterference(lw, TopAbs_EDGE, lE);
  FUN_reduceEDGEgeometry(lFEF, BDS, SIX, MEsp);

  LI.Clear();
  LI.Append(lF);
  LI.Append(lFE);
  LI.Append(lFEF);
  LI.Append(lE);

  ::FUN_reducedoublons(LI, BDS, SIX);
}
