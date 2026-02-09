#include <gp_Pnt2d.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRep_FaceEdgeFiller.hpp>
#include <TopOpeBRep_FaceEdgeIntersector.hpp>
#include <TopOpeBRep_PointGeomTool.hpp>
#include <TopOpeBRepDS_CurvePointInterference.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_InterferenceTool.hpp>
#include <TopOpeBRepDS_Point.hpp>

#ifdef OCCT_DEBUG
extern void FEINT_DUMPPOINTS(TopOpeBRep_FaceEdgeIntersector&   FEINT,
                             const TopOpeBRepDS_DataStructure& BDS);
#endif

TopOpeBRep_FaceEdgeFiller::TopOpeBRep_FaceEdgeFiller() = default;

void TopOpeBRep_FaceEdgeFiller::Insert(const TopoDS_Shape&                             F,
                                       const TopoDS_Shape&                             E,
                                       TopOpeBRep_FaceEdgeIntersector&                 FEINT,
                                       const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  const TopoDS_Face& FF = TopoDS::Face(F);
  const TopoDS_Edge& EE = TopoDS::Edge(E);

  FEINT.InitPoint();
  if (!FEINT.MorePoint())
    return;

  TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();

  TopAbs_Orientation FFori = FF.Orientation();

  int FFindex = BDS.AddShape(FF, 1);
  BDS.AddShape(EE, 2);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& EIL1 = BDS.ChangeShapeInterferences(FF);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& EIL2 = BDS.ChangeShapeInterferences(EE);

  occ::handle<TopOpeBRepDS_Interference> EPI;
  occ::handle<TopOpeBRepDS_Interference> EVI;

  for (; FEINT.MorePoint(); FEINT.NextPoint())
  {
    gp_Pnt2d pUV;
    FEINT.UVPoint(pUV);
    double parE = FEINT.Parameter();

#ifdef OCCT_DEBUG
    TopAbs_Orientation      EEori = EE.Orientation();
    TopOpeBRepDS_Transition TFF   = FEINT.Transition(1, EEori);
    (void)TFF;
#endif
    TopOpeBRepDS_Transition TEE = FEINT.Transition(2, FFori);
    TEE.Index(FFindex);

    TopoDS_Vertex V1;
    bool          isvertexF = FEINT.IsVertex(1, V1);
    TopoDS_Vertex V2;
    bool          isvertexE = FEINT.IsVertex(2, V2);
    bool          isvertex  = isvertexF || isvertexE;

    int  DSPindex;
    bool EPIfound;

    if (!isvertex)
    {

      NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itEIL1(EIL1);
      EPIfound = GetGeometry(itEIL1, FEINT, DSPindex, BDS);
      if (!EPIfound)
        DSPindex = MakeGeometry(FEINT, BDS);

      EPI = TopOpeBRepDS_InterferenceTool::MakeCurveInterference(TEE,
                                                                 TopOpeBRepDS_FACE,
                                                                 FFindex,
                                                                 TopOpeBRepDS_POINT,
                                                                 DSPindex,
                                                                 parE);
      StoreInterference(EPI, EIL2, BDS);
    }

    else if (isvertexF)
    {

      int Vindex = BDS.AddShape(V1, 1);

      EPI = new TopOpeBRepDS_CurvePointInterference(TEE,
                                                    TopOpeBRepDS_FACE,
                                                    FFindex,
                                                    TopOpeBRepDS_VERTEX,
                                                    Vindex,
                                                    parE);
      StoreInterference(EPI, EIL2, BDS);
    }

    else if (isvertexE)
    {
      int Vindex = BDS.AddShape(V2, 2);

      EPI = new TopOpeBRepDS_CurvePointInterference(TEE,
                                                    TopOpeBRepDS_FACE,
                                                    FFindex,
                                                    TopOpeBRepDS_VERTEX,
                                                    Vindex,
                                                    parE);
      StoreInterference(EPI, EIL2, BDS);
    }
  }
}

bool TopOpeBRep_FaceEdgeFiller::ScanInterfList(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
  const TopOpeBRepDS_Point&                                           DSP,
  const TopOpeBRepDS_DataStructure&                                   BDS) const
{
  for (; IT.More(); IT.Next())
  {
    int                       DSPG     = IT.Value()->Geometry();
    const TopOpeBRepDS_Point& otherDSP = BDS.Point(DSPG);
    if (TopOpeBRep_PointGeomTool::IsEqual(DSP, otherDSP))
      return true;
  }
  return false;
}

bool TopOpeBRep_FaceEdgeFiller::GetGeometry(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
  const TopOpeBRep_FaceEdgeIntersector&                               FEINT,
  int&                                                                G,
  const TopOpeBRepDS_DataStructure&                                   BDS) const
{
  TopOpeBRepDS_Point DSP   = TopOpeBRep_PointGeomTool::MakePoint(FEINT);
  bool               found = ScanInterfList(IT, DSP, BDS);
  if (found)
    G = IT.Value()->Geometry();
  return found;
}

bool TopOpeBRep_FaceEdgeFiller::GetGeometry(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L,
  const TopOpeBRepDS_Point&                                       DSP,
  int&                                                            G,
  TopOpeBRepDS_DataStructure&                                     BDS) const
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itI(L);
  bool Ifound = ScanInterfList(itI, DSP, BDS);
  if (Ifound)
    G = itI.Value()->Geometry();
  else
    G = BDS.AddPoint(DSP);
  return Ifound;
}

void TopOpeBRep_FaceEdgeFiller::StoreInterference(
  const occ::handle<TopOpeBRepDS_Interference>&             I,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  TopOpeBRepDS_DataStructure&                               BDS) const
{

  LI.Append(I);

  int G = I->Geometry();

  switch (I->GeometryType())
  {

    case TopOpeBRepDS_SOLID:
    case TopOpeBRepDS_FACE:
    case TopOpeBRepDS_EDGE:
    case TopOpeBRepDS_VERTEX:

      break;

    case TopOpeBRepDS_SURFACE:
      BDS.ChangeSurfaceInterferences(G).Append(I);
      break;

    case TopOpeBRepDS_CURVE:
      BDS.ChangeCurveInterferences(G).Append(I);
      break;

    case TopOpeBRepDS_POINT:

      break;
    default:
      break;
  }
}

int TopOpeBRep_FaceEdgeFiller::MakeGeometry(TopOpeBRep_FaceEdgeIntersector& FEINT,
                                            TopOpeBRepDS_DataStructure&     BDS) const
{
  int G = 0;

  TopoDS_Vertex V1;
  bool          isvertexF = FEINT.IsVertex(1, V1);
  TopoDS_Vertex V2;
  bool          isvertexE = FEINT.IsVertex(2, V2);
  bool          isvertex  = isvertexF || isvertexE;

  if (isvertex)
  {
    if (isvertexF)
      G = BDS.AddShape(V1, 1);
    else if (isvertexE)
      G = BDS.AddShape(V2, 2);
  }
  else
    G = BDS.AddPoint(TopOpeBRep_PointGeomTool::MakePoint(FEINT));
  return G;
}
