#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_define.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_WireEdgeSet.hpp>
#include <TopOpeBRepDS.hpp>
#include <TopOpeBRepDS_EXPORT.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>

#ifdef OCCT_DEBUG
Standard_EXPORT void debfctwesmess(const int i, const TCollection_AsciiString& s = "");
Standard_EXPORT void debffwesON(const int i);

Standard_EXPORT void debffwesk(const int i)
{
  std::cout << "++ debffwesk " << i << std::endl;
}
#endif

bool TopOpeBRepBuild_FUN_aresamegeom(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

#define M_IN(st) (st == TopAbs_IN)
#define M_OUT(st) (st == TopAbs_OUT)
#define M_FORWARD(st) (st == TopAbs_FORWARD)
#define M_REVERSED(st) (st == TopAbs_REVERSED)
#define M_INTERNAL(st) (st == TopAbs_INTERNAL)
#define M_EXTERNAL(st) (st == TopAbs_EXTERNAL)

void TopOpeBRepBuild_Builder::GFillFacesWESK(const NCollection_List<TopoDS_Shape>& LS1,
                                             const NCollection_List<TopoDS_Shape>& LS2,
                                             const TopOpeBRepBuild_GTopo&          G1,
                                             TopOpeBRepBuild_WireEdgeSet&          WES,
                                             const int                             Kfill)
{
  if (LS1.IsEmpty())
    return;
  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);

  const TopOpeBRepDS_DataStructure& BDS = myDataStructure->DS();

  const TopoDS_Shape& F1 = LS1.First();
  myFaceReference        = TopoDS::Face(F1);
#ifdef OCCT_DEBUG
  int iF1 =
#endif
    BDS.Shape(F1);
  int                iref = BDS.SameDomainRef(F1);
  TopAbs_Orientation oref = BDS.Shape(iref).Orientation();

#ifdef OCCT_DEBUG
  bool tSPS = GtraceSPS(F1, iF1);
  if (tSPS)
    std::cout << "\n%%%%%%%%%%%%% K = " << Kfill << " %%%%%%%%%%%%% ";
  if (tSPS)
    GdumpSHASTA(iF1, TB1, WES, "GFillFacesWESK", "myFaceReference");
  if (tSPS)
    debffwesk(iF1);
#endif

  TopAbs_State                             TB;
  TopOpeBRepBuild_GTopo                    G;
  NCollection_List<TopoDS_Shape>::Iterator it;
  bool                                     gistoreverse1;

  G             = G1;
  gistoreverse1 = G.IsToReverse1();
  TB            = TB1;
  it.Initialize(LS1);

#ifdef OCCT_DEBUG
  if (tSPS)
  {
    std::cout << "\n^^^^^^^^ GFillFacesWESK : traitement de 1/2";
    TopAbs_State TB11, TB21;
    G.StatesON(TB11, TB21);
    std::cout << " TB = ";
    TopAbs::Print(TB, std::cout);
    std::cout << " ";
    std::cout << "(TB1 = ";
    TopAbs::Print(TB11, std::cout);
    std::cout << ",";
    std::cout << " TB2 = ";
    TopAbs::Print(TB21, std::cout);
    std::cout << ")\n\n";
  }
#endif

  for (; it.More(); it.Next())
  {
    const TopoDS_Shape& S       = it.Value();
    int                 iS      = myDataStructure->Shape(S);
    bool                tomerge = !IsMerged(S, TB);
    if (!tomerge)
      continue;

    TopAbs_Orientation  oS   = BDS.Shape(iS).Orientation();
    TopOpeBRepDS_Config conf = BDS.SameDomainOri(S);
    bool                b1   = (conf == TopOpeBRepDS_DIFFORIENTED && (oS == oref));
    bool                b2   = (conf == TopOpeBRepDS_SAMEORIENTED && (oS != oref));
    bool                b    = b1 || b2;

    if (b)
      G.SetReverse(!gistoreverse1);

    if (Kfill == 1)
    {
      GFillFaceWES(S, LS2, G, WES);
    }
    else if (Kfill == 2)
    {
#ifdef OCCT_DEBUG
      if (tSPS)
        debfctwesmess(iF1);
#endif
      GFillCurveTopologyWES(S, G, WES);
    }
    else if (Kfill == 3)
    {
#ifdef OCCT_DEBUG
      if (tSPS)
        debffwesON(iF1);
#endif
      GFillONPartsWES(S, G, LS2, WES);
    }
    else
    {
    }
  }

  G             = G1.CopyPermuted();
  gistoreverse1 = G.IsToReverse1();
  TB            = TB2;
  it.Initialize(LS2);

#ifdef OCCT_DEBUG
  if (tSPS)
  {
    std::cout << "\n^^^^^^^^ GFillFacesWESK : traitement de 2/1";
    TopAbs_State TB12, TB22;
    G.StatesON(TB12, TB22);
    std::cout << " TB = ";
    TopAbs::Print(TB, std::cout);
    std::cout << " ";
    std::cout << "(TB1 = ";
    TopAbs::Print(TB12, std::cout);
    std::cout << ",";
    std::cout << " TB2 = ";
    TopAbs::Print(TB22, std::cout);
    std::cout << ")\n\n";
  }
#endif

  for (; it.More(); it.Next())
  {
    const TopoDS_Shape& S       = it.Value();
    int                 iS      = myDataStructure->Shape(S);
    bool                tomerge = !IsMerged(S, TB);
    if (!tomerge)
      continue;

    TopAbs_Orientation  oS   = BDS.Shape(iS).Orientation();
    TopOpeBRepDS_Config conf = BDS.SameDomainOri(S);
    bool                b1   = (conf == TopOpeBRepDS_DIFFORIENTED && (oS == oref));
    bool                b2   = (conf == TopOpeBRepDS_SAMEORIENTED && (oS != oref));
    bool                b    = b1 || b2;

    if (b)
      G.SetReverse(!gistoreverse1);

    if (Kfill == 1)
    {
      GFillFaceWES(S, LS1, G, WES);
    }
    else if (Kfill == 2)
    {
      GFillCurveTopologyWES(S, G, WES);
    }
    else if (Kfill == 3)
    {
#ifdef OCCT_DEBUG
      if (tSPS)
        debffwesON(iF1);
#endif
      GFillONPartsWES(S, G, LS1, WES);
    }
    else
    {
    }
  }
}
