#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_define.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_WireEdgeSet.hpp>
#include <TopOpeBRepDS.hpp>
#include <TopOpeBRepDS_BuildTool.hpp>
#include <TopOpeBRepDS_CurveIterator.hpp>
#include <TopOpeBRepDS_EXPORT.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepTool_2d.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>

#ifdef OCCT_DEBUG
Standard_EXPORT void debfctwes(const int) {}

Standard_EXPORT void debfctwesmess(const int i, const TCollection_AsciiString& s = "")
{
  std::cout << "+ + + debfctwes " << s << "F" << i << std::endl;
  debfctwes(i);
}

extern void debaddpwes(const int                           iFOR,
                       const TopAbs_State                  TB1,
                       const int                           iEG,
                       const TopAbs_Orientation            neworiE,
                       const TopOpeBRepBuild_PBuilder&     PB,
                       const TopOpeBRepBuild_PWireEdgeSet& PWES,
                       const TCollection_AsciiString&      str1,
                       const TCollection_AsciiString&      str2);
#endif

bool TopOpeBRepBuild_FUN_aresamegeom(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

#define M_IN(st) (st == TopAbs_IN)
#define M_OUT(st) (st == TopAbs_OUT)
#define M_FORWARD(st) (st == TopAbs_FORWARD)
#define M_REVERSED(st) (st == TopAbs_REVERSED)
#define M_INTERNAL(st) (st == TopAbs_INTERNAL)
#define M_EXTERNAL(st) (st == TopAbs_EXTERNAL)

void TopOpeBRepBuild_Builder::GFillCurveTopologyWES(const TopoDS_Shape&          F1,
                                                    const TopOpeBRepBuild_GTopo& G1,
                                                    TopOpeBRepBuild_WireEdgeSet& WES)
{
  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);
  TopAbs_ShapeEnum t1, t2, ShapeInterf;
  G1.Type(t1, t2);
  ShapeInterf = t1;

#ifdef OCCT_DEBUG
  int  iF;
  bool tSPS = GtraceSPS(F1, iF);
  if (tSPS)
    GdumpSHASTA(iF, TB1, WES, "--- GFillCurveTopologyWES");
  if (tSPS)
  {
    std::cout << " ShapeInterf ";
    TopAbs::Print(ShapeInterf, std::cout);
    std::cout << std::endl;
  }
  if (tSPS)
  {
    debfctwesmess(iF);
  }
#endif

  TopOpeBRepDS_CurveIterator FCit(myDataStructure->FaceCurves(F1));
  myFaceReference = TopoDS::Face(F1);
  myFaceToFill    = TopoDS::Face(F1);

  bool hsd = myDataStructure->HasSameDomain(F1);
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aSDMap;
  if (hsd)
  {
    NCollection_List<TopoDS_Shape>::Iterator it = myDataStructure->SameDomain(F1);
    for (; it.More(); it.Next())
    {
      const TopoDS_Shape& SDF = it.Value();
      aSDMap.Add(SDF);
    }
  }

  for (; FCit.More(); FCit.Next())
  {
    if (ShapeInterf != TopAbs_SHAPE)
    {
      const occ::handle<TopOpeBRepDS_Interference>& I    = FCit.Value();
      const TopOpeBRepDS_Transition&                T    = I->Transition();
      TopAbs_ShapeEnum                              shab = T.ShapeBefore(), shaa = T.ShapeAfter();
      if ((shaa != ShapeInterf) || (shab != ShapeInterf))
        continue;

      int          si = I->Support();
      TopoDS_Shape SS = myDataStructure->Shape(si);

      if (aSDMap.Contains(SS))
        continue;
    }
    GFillCurveTopologyWES(FCit, G1, WES);
  }

  return;
}

void TopOpeBRepBuild_Builder::GFillCurveTopologyWES(const TopOpeBRepDS_CurveIterator& FCit,
                                                    const TopOpeBRepBuild_GTopo&      G1,
                                                    TopOpeBRepBuild_WireEdgeSet&      WES) const
{
  bool more = FCit.More();
  if (!more)
    return;

  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);
  TopOpeBRepDS_Config Conf = G1.Config1();
  TopAbs_State        TB   = TB1;
  if (Conf == TopOpeBRepDS_DIFFORIENTED)
  {
  }

  TopoDS_Face& WESF = *((TopoDS_Face*)((void*)&WES.Face()));
  TopoDS_Face& FTF  = *((TopoDS_Face*)((void*)&myFaceToFill));
#ifdef OCCT_DEBUG

#endif

#ifdef OCCT_DEBUG
  int iWESF = myDataStructure->Shape(WESF);
  int iref  = myDataStructure->Shape(myFaceReference);
  int ifil  = myDataStructure->Shape(myFaceToFill);
#endif

  bool opeCut   = Opec12() || Opec21();
  bool ComOfCut = opeCut && (TB1 == TB2) && (TB1 == TopAbs_IN);

  const TopOpeBRepDS_Transition& T        = FCit.Value()->Transition();
  TopAbs_Orientation             neworiE  = T.Orientation(TB);
  bool                           samegeom = TopOpeBRepBuild_FUN_aresamegeom(FTF, WESF);
  if (!samegeom)
  {
    neworiE = TopAbs::Complement(neworiE);
  }

#ifdef OCCT_DEBUG
  bool tSPS = GtraceSPS(iWESF);
  if (tSPS)
  {
    std::cout << "ifil : " << ifil << " iref : " << iref << " iwes : " << iWESF << std::endl;
    std::cout << "face " << ifil << " is ";
    TopOpeBRepDS::Print(Conf, std::cout);
    std::cout << std::endl;
    std::cout << "ComOfCut " << ComOfCut << std::endl;
    debfctwesmess(iWESF);
  }
#endif

  if (ComOfCut)
    return;

  int                                      iG    = FCit.Current();
  const NCollection_List<TopoDS_Shape>&    LnewE = NewEdges(iG);
  NCollection_List<TopoDS_Shape>::Iterator Iti(LnewE);
  for (; Iti.More(); Iti.Next())
  {
    TopoDS_Shape EE = Iti.Value();
    TopoDS_Edge& E  = TopoDS::Edge(EE);

    if (BRep_Tool::Degenerated(E))
      continue;

    E.Orientation(neworiE);

    const occ::handle<Geom2d_Curve>& PC = FCit.PCurve();

    bool EhasPConFTF =

      FC2D_HasCurveOnSurface(E, FTF);

    if (!EhasPConFTF)
      myBuildTool.PCurve(FTF, E, PC);

    bool EhasPConWESF = FC2D_HasCurveOnSurface(E, WESF);

    if (!EhasPConWESF)
    {

      double                    f2, l2, tolpc;
      occ::handle<Geom2d_Curve> C2D;
      C2D = FC2D_CurveOnSurface(E, WESF, f2, l2, tolpc);
      if (C2D.IsNull())
        throw Standard_ProgramError("GFillCurveTopologyWES");
#ifdef OCCT_DEBUG

#endif

      myBuildTool.PCurve(WESF, E, C2D);

#ifdef OCCT_DEBUG
      EhasPConWESF = FC2D_HasCurveOnSurface(E, WESF);
      if (!EhasPConWESF)
        std::cout << "TopOpeBRepBuild_Builder::GFillCurveTopologyWES : Null PCurve on F" << iWESF
                  << std::endl;
#endif
    }

#ifdef OCCT_DEBUG
    if (tSPS)
      debaddpwes(iWESF,
                 TB,
                 iG,
                 neworiE,
                 (TopOpeBRepBuild_Builder* const)this,
                 &WES,
                 "GFillCurveTopology ",
                 "WES+ EofC ");
#endif

    WES.AddStartElement(E);
  }
}
