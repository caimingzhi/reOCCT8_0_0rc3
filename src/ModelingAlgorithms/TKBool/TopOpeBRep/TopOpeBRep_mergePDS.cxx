#include <TopoDS.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS_Point.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopOpeBRepDS_CurveExplorer.hpp>
#include <TopOpeBRepDS.hpp>

#include <TopOpeBRep_define.hpp>
#include <TopOpeBRepDS_CurvePointInterference.hpp>

int BREP_findPDSamongIDMOVP(
  const TopOpeBRepDS_Point& PDS,
  const NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_Point, TopTools_ShapeMapHasher>&
    IDMOVP)
{
  int iIDMOVP = 0;
  int i = 1, n = IDMOVP.Extent();
  for (; i <= n; i++)
  {
    const TopOpeBRepDS_Point& PM = IDMOVP.FindFromIndex(i);
    if (PDS.IsEqual(PM))
    {
      iIDMOVP = i;
      break;
    }
  }
  return iIDMOVP;
}

void BREP_makeIDMOVP(
  const TopoDS_Shape&                                                                    S,
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_Point, TopTools_ShapeMapHasher>& IDMOVP)
{
  TopExp_Explorer Ex;
  for (Ex.Init(S, TopAbs_VERTEX); Ex.More(); Ex.Next())
  {
    const TopoDS_Vertex& v = TopoDS::Vertex(Ex.Current());
    TopOpeBRepDS_Point   PDS(v);
    IDMOVP.Add(v, PDS);
  }
}

void BREP_mergePDS(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();
  TopOpeBRepDS_CurveExplorer  cex(BDS);
  if (!cex.More())
    return;

  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_Point, TopTools_ShapeMapHasher> Mvp1;
  NCollection_IndexedDataMap<TopoDS_Shape, TopOpeBRepDS_Point, TopTools_ShapeMapHasher> Mvp2;

  for (; cex.More(); cex.Next())
  {

    const TopOpeBRepDS_Curve&                                          c  = cex.Curve();
    const int                                                          ic = cex.Index();
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itI;
    itI.Initialize(BDS.ChangeCurveInterferences(ic));
    if (!itI.More())
      continue;

    const TopoDS_Face& f1 = TopoDS::Face(c.Shape1());
#ifdef OCCT_DEBUG
    int if1 =
#endif
      BDS.Shape(f1);
    const TopoDS_Face& f2 = TopoDS::Face(c.Shape2());
#ifdef OCCT_DEBUG
    int if2 =
#endif
      BDS.Shape(f2);

    Mvp1.Clear();
    BREP_makeIDMOVP(f1, Mvp1);
    Mvp2.Clear();
    BREP_makeIDMOVP(f2, Mvp2);

    for (; itI.More(); itI.Next())
    {
      occ::handle<TopOpeBRepDS_Interference>           ITF = itI.Value();
      occ::handle<TopOpeBRepDS_CurvePointInterference> CPI =
        occ::down_cast<TopOpeBRepDS_CurvePointInterference>(ITF);
      if (CPI.IsNull())
        continue;
      TopOpeBRepDS_Kind GK = CPI->GeometryType();
      if (GK != TopOpeBRepDS_POINT)
        continue;
      int GI = CPI->Geometry();
      //**!
      if (GI > BDS.NbPoints())
        continue;
      //**!
      const TopOpeBRepDS_Point& PDS = BDS.Point(GI);

      int               ivp1;
      TopoDS_Shape      v1;
      TopOpeBRepDS_Kind k1  = TopOpeBRepDS_UNKNOWN;
      int               iv1 = 0;

      ivp1 = BREP_findPDSamongIDMOVP(PDS, Mvp1);
      if (ivp1)
      {
        v1  = Mvp1.FindKey(ivp1);
        iv1 = BDS.AddShape(v1);
        k1  = TopOpeBRepDS_VERTEX;
      }

      int               ivp2;
      TopoDS_Shape      v2;
      TopOpeBRepDS_Kind k2  = TopOpeBRepDS_UNKNOWN;
      int               iv2 = 0;

      ivp2 = BREP_findPDSamongIDMOVP(PDS, Mvp2);
      if (ivp2)
      {
        v2  = Mvp2.FindKey(ivp2);
        iv2 = BDS.AddShape(v2);
        k2  = TopOpeBRepDS_VERTEX;
      }

      if (ivp1 && ivp2)
        BDS.FillShapesSameDomain(v1, v2);

      bool editITF = (ivp1 || ivp2);
      if (editITF)
      {
        if (ivp1)
        {
          CPI->GeometryType(k1);
          CPI->Geometry(iv1);
        }
        else if (ivp2)
        {
          CPI->GeometryType(k2);
          CPI->Geometry(iv2);
        }
      }

#ifdef OCCT_DEBUG
      if (editITF)
      {
        if (ivp1 != 0)
        {
          std::cout << TopOpeBRepDS::SPrint(TopOpeBRepDS_CURVE, ic, "# BREP_mergePDS ", " : ");
          std::cout << TopOpeBRepDS::SPrint(GK, GI, "", " = ");
          TCollection_AsciiString str(BDS.HasShape(v1) ? "old" : "new ");
          std::cout << TopOpeBRepDS::SPrint(k1, iv1, str);
          std::cout << TopOpeBRepDS::SPrint(TopOpeBRepDS::ShapeToKind(f1.ShapeType()), if1, " de ")
                    << std::endl;
        }
        if (ivp2 != 0)
        {
          std::cout << TopOpeBRepDS::SPrint(TopOpeBRepDS_CURVE, ic, "# BREP_mergePDS ", " : ");
          std::cout << TopOpeBRepDS::SPrint(GK, GI, "", " = ");
          TCollection_AsciiString str(BDS.HasShape(v2) ? "old" : "new ");
          std::cout << TopOpeBRepDS::SPrint(k2, iv2, str);
          std::cout << TopOpeBRepDS::SPrint(TopOpeBRepDS::ShapeToKind(f2.ShapeType()), if2, " de ")
                    << std::endl;
        }
      }
#endif

    } // itI.More()
  }
} // BREP_mergePDS
