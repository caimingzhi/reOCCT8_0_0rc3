#include <BRep_Tool.hpp>
#include <Standard_ProgramError.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS.hpp>
#include <TopOpeBRepDS_Check.hpp>
#include <TopOpeBRepDS_CurveIterator.hpp>
#include <TopOpeBRepDS_define.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <TopOpeBRepDS_Point.hpp>
#include <TopOpeBRepDS_PointIterator.hpp>
#include <TopOpeBRepDS_Surface.hpp>
#include <TopOpeBRepDS_SurfaceCurveInterference.hpp>
#include <TopOpeBRepDS_SurfaceIterator.hpp>
#include <TopOpeBRepDS_Transition.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_HDataStructure, Standard_Transient)

static void FUN_HDS_data(const occ::handle<TopOpeBRepDS_Interference>& I,
                         TopOpeBRepDS_Kind&                            GT1,
                         int&                                          G1,
                         TopOpeBRepDS_Kind&                            ST1,
                         int&                                          S1)
{
  if (I.IsNull())
    return;
  GT1 = I->GeometryType();
  G1  = I->Geometry();
  ST1 = I->SupportType();
  S1  = I->Support();
}

Standard_EXPORT bool FUN_HDS_FACESINTERFER(const TopoDS_Shape&                             F1,
                                           const TopoDS_Shape&                             F2,
                                           const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  bool                              yainterf = false;
  const TopOpeBRepDS_DataStructure& DS       = HDS->DS();
  bool                              ya       = DS.HasShape(F1);
  if (!ya)
    return false;

  int iF2 = DS.Shape(F2);

  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&    L1 = DS.ShapeInterferences(F1);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itL1(L1);
  for (; itL1.More(); itL1.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I = itL1.Value();
    TopOpeBRepDS_Kind GT = TopOpeBRepDS_UNKNOWN, ST = TopOpeBRepDS_UNKNOWN;
    int               G, S                          = 0;
    FUN_HDS_data(I, GT, G, ST, S);

    bool fef = true;
    fef      = fef && (GT == TopOpeBRepDS_EDGE);
    fef      = fef && (ST == TopOpeBRepDS_FACE);
    fef      = fef && (S == iF2);
    if (fef)
    {
      yainterf = true;
      break;
    }
  }
  return yainterf;
}

TopOpeBRepDS_HDataStructure::TopOpeBRepDS_HDataStructure() = default;

void TopOpeBRepDS_HDataStructure::AddAncestors(const TopoDS_Shape& S)
{
  AddAncestors(S, TopAbs_WIRE, TopAbs_EDGE);
  AddAncestors(S, TopAbs_FACE, TopAbs_WIRE);
  AddAncestors(S, TopAbs_SHELL, TopAbs_FACE);
  AddAncestors(S, TopAbs_SOLID, TopAbs_SHELL);
}

void TopOpeBRepDS_HDataStructure::AddAncestors(const TopoDS_Shape&    S,
                                               const TopAbs_ShapeEnum T1,
                                               const TopAbs_ShapeEnum T2)
{
  TopOpeBRepDS_DataStructure& BDS   = ChangeDS();
  int                         rankS = myDS.AncestorRank(S);

  for (TopOpeBRepTool_ShapeExplorer eT1(S, T1); eT1.More(); eT1.Next())
  {
    const TopoDS_Shape& ST1 = eT1.Current();
    for (TopOpeBRepTool_ShapeExplorer eT2(ST1, T2); eT2.More(); eT2.Next())
    {
      const TopoDS_Shape& ST2 = eT2.Current();
      if (BDS.HasShape(ST2))
      {
        BDS.AddShape(ST1, rankS);
        break;
      }
    }
  }
}

void TopOpeBRepDS_HDataStructure::ChkIntg()
{

  occ::handle<TopOpeBRepDS_Check> chk = new TopOpeBRepDS_Check(this);
  chk->ChkIntg();
}

const TopOpeBRepDS_DataStructure& TopOpeBRepDS_HDataStructure::DS() const
{
  return myDS;
}

TopOpeBRepDS_DataStructure& TopOpeBRepDS_HDataStructure::ChangeDS()
{
  return myDS;
}

int TopOpeBRepDS_HDataStructure::NbSurfaces() const
{
  return myDS.NbSurfaces();
}

int TopOpeBRepDS_HDataStructure::NbCurves() const
{
  return myDS.NbCurves();
}

int TopOpeBRepDS_HDataStructure::NbPoints() const
{
  return myDS.NbPoints();
}

const TopOpeBRepDS_Surface& TopOpeBRepDS_HDataStructure::Surface(const int I) const
{
  return myDS.Surface(I);
}

TopOpeBRepDS_CurveIterator TopOpeBRepDS_HDataStructure::SurfaceCurves(const int I) const
{
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L = myDS.SurfaceInterferences(I);
  return TopOpeBRepDS_CurveIterator(L);
}

const TopOpeBRepDS_Curve& TopOpeBRepDS_HDataStructure::Curve(const int I) const
{
  return myDS.Curve(I);
}

TopOpeBRepDS_Curve& TopOpeBRepDS_HDataStructure::ChangeCurve(const int I)
{
  return myDS.ChangeCurve(I);
}

TopOpeBRepDS_PointIterator TopOpeBRepDS_HDataStructure::CurvePoints(const int I) const
{
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L = myDS.CurveInterferences(I);
  return TopOpeBRepDS_PointIterator(L);
}

const TopOpeBRepDS_Point& TopOpeBRepDS_HDataStructure::Point(const int I) const
{
  return myDS.Point(I);
}

bool TopOpeBRepDS_HDataStructure::HasGeometry(const TopoDS_Shape& S) const
{
  bool b = myDS.HasGeometry(S);
  return b;
}

bool TopOpeBRepDS_HDataStructure::HasShape(const TopoDS_Shape& S, const bool FindKeep) const
{
  bool b = myDS.HasShape(S, FindKeep);
  return b;
}

bool TopOpeBRepDS_HDataStructure::HasSameDomain(const TopoDS_Shape& S, const bool FindKeep) const
{
  if (!HasShape(S, FindKeep))
    return false;
  const NCollection_List<TopoDS_Shape>& l   = myDS.ShapeSameDomain(S);
  bool                                  res = !l.IsEmpty();
  return res;
}

NCollection_List<TopoDS_Shape>::Iterator TopOpeBRepDS_HDataStructure::SameDomain(
  const TopoDS_Shape& S) const
{
  const NCollection_List<TopoDS_Shape>& L = myDS.ShapeSameDomain(S);
  return NCollection_List<TopoDS_Shape>::Iterator(L);
}

TopOpeBRepDS_Config TopOpeBRepDS_HDataStructure::SameDomainOrientation(const TopoDS_Shape& S) const
{
  if (!HasShape(S))
    return TopOpeBRepDS_UNSHGEOMETRY;
  return myDS.SameDomainOri(S);
}

int TopOpeBRepDS_HDataStructure::SameDomainReference(const TopoDS_Shape& S) const
{
  if (!HasShape(S))
    return 0;
  return myDS.SameDomainRef(S);
}

int TopOpeBRepDS_HDataStructure::NbShapes() const
{
  return myDS.NbShapes();
}

const TopoDS_Shape& TopOpeBRepDS_HDataStructure::Shape(const int I, const bool FindKeep) const
{
  return myDS.Shape(I, FindKeep);
}

int TopOpeBRepDS_HDataStructure::Shape(const TopoDS_Shape& S, const bool FindKeep) const
{
  return myDS.Shape(S, FindKeep);
}

TopOpeBRepDS_SurfaceIterator TopOpeBRepDS_HDataStructure::SolidSurfaces(const TopoDS_Shape& S) const
{
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L = myDS.ShapeInterferences(S);
  return TopOpeBRepDS_SurfaceIterator(L);
}

TopOpeBRepDS_SurfaceIterator TopOpeBRepDS_HDataStructure::SolidSurfaces(const int I) const
{
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L = myDS.ShapeInterferences(I);
  return TopOpeBRepDS_SurfaceIterator(L);
}

TopOpeBRepDS_CurveIterator TopOpeBRepDS_HDataStructure::FaceCurves(const TopoDS_Shape& F) const
{
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L = myDS.ShapeInterferences(F);
  return TopOpeBRepDS_CurveIterator(L);
}

TopOpeBRepDS_CurveIterator TopOpeBRepDS_HDataStructure::FaceCurves(const int I) const
{
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L = myDS.ShapeInterferences(I);
  return TopOpeBRepDS_CurveIterator(L);
}

TopOpeBRepDS_PointIterator TopOpeBRepDS_HDataStructure::EdgePoints(const TopoDS_Shape& E) const
{
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L = myDS.ShapeInterferences(E);
  return TopOpeBRepDS_PointIterator(L);
}

int TopOpeBRepDS_HDataStructure::MakeCurve(const TopOpeBRepDS_Curve& curC, TopOpeBRepDS_Curve& newC)
{

  const occ::handle<TopOpeBRepDS_Interference>&      I1 = curC.GetSCI1();
  const occ::handle<TopOpeBRepDS_Interference>&      I2 = curC.GetSCI2();
  occ::handle<TopOpeBRepDS_SurfaceCurveInterference> SCI1, SCI2;
  if (!I1.IsNull())
    SCI1 = new TopOpeBRepDS_SurfaceCurveInterference(I1);
  if (!I2.IsNull())
    SCI2 = new TopOpeBRepDS_SurfaceCurveInterference(I2);

  const TopoDS_Shape& S1 = curC.Shape1();
  const TopoDS_Shape& S2 = curC.Shape2();

  if (!SCI1.IsNull())
    myDS.AddShapeInterference(S1, SCI1);
  if (!SCI2.IsNull())
    myDS.AddShapeInterference(S2, SCI2);

  newC.SetShapes(S1, S2);

  newC.SetSCI(SCI1, SCI2);

  newC.ChangeMother(curC.DSIndex());

  int inewC = myDS.AddCurve(newC);

  if (!SCI1.IsNull())
    SCI1->Geometry(inewC);
  if (!SCI2.IsNull())
    SCI2->Geometry(inewC);

  return inewC;
}

void TopOpeBRepDS_HDataStructure::RemoveCurve(const int icurC)
{
  myDS.RemoveCurve(icurC);
}

int TopOpeBRepDS_HDataStructure::NbGeometry(const TopOpeBRepDS_Kind K) const
{
  if (!TopOpeBRepDS::IsGeometry(K))
    return 0;

  int n = 0;
  switch (K)
  {
    case TopOpeBRepDS_POINT:
      n = NbPoints();
      break;
    case TopOpeBRepDS_CURVE:
      n = NbCurves();
      break;
    case TopOpeBRepDS_SURFACE:
      n = NbSurfaces();
      break;
    default:
      n = 0;
      break;
  }
  return n;
}

int TopOpeBRepDS_HDataStructure::NbTopology() const
{
  int n = myDS.NbShapes();
  return n;
}

int TopOpeBRepDS_HDataStructure::NbTopology(const TopOpeBRepDS_Kind K) const
{
  if (!TopOpeBRepDS::IsTopology(K))
    return 0;
  int        res      = 0;
  const bool FindKeep = false;

  TopAbs_ShapeEnum S = TopOpeBRepDS::KindToShape(K);
  for (int i = 1; i <= NbTopology(); i++)
    if (myDS.KeepShape(i, FindKeep))
      if (myDS.Shape(i, FindKeep).ShapeType() == S)
        res++;
  return res;
}

bool TopOpeBRepDS_HDataStructure::EdgesSameParameter() const
{
  int i, n = myDS.NbShapes();
  for (i = 1; i <= n; i++)
  {
    const TopoDS_Shape& s = myDS.Shape(i);
    if (s.ShapeType() == TopAbs_EDGE)
    {
      const TopoDS_Edge& e = TopoDS::Edge(s);
      if (!BRep_Tool::SameParameter(e))
      {
        return false;
      }
    }
  }
  return true;
}

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

Standard_EXPORT void FUN_TopOpeBRepDS_SortOnParameter(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& List,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&       SList)
{

  int iIntf = 0, nIntf = List.Extent();
  if (nIntf == 0)
    return;

  occ::handle<NCollection_HArray1<bool>> HT;
  HT                          = new NCollection_HArray1<bool>(1, nIntf, false);
  NCollection_Array1<bool>& T = HT->ChangeArray1();

  occ::handle<TopOpeBRepDS_Interference> Intf;

  for (int i = 1; i <= nIntf; i++)
  {
    double                     parmin = RealLast();
    TopOpeBRepDS_PointIterator it(List);
    for (int itest = 1; it.More(); it.Next(), itest++)
    {
      if (!T(itest))
      {
        double par = it.Parameter();
        if (par < parmin)
        {
          parmin = par;
          Intf   = it.Value();
          iIntf  = itest;
        }
      }
    }
    SList.Append(Intf);
    T(iIntf) = true;
  }
}

void TopOpeBRepDS_HDataStructure::SortOnParameter(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& List,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&       SList) const
{

  ::FUN_TopOpeBRepDS_SortOnParameter(List, SList);

  bool                                                               found = false;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(SList);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>           L1, L2;

  for (; it.More(); it.Next())
  {
    occ::handle<TopOpeBRepDS_Interference> I = it.Value();
    if (!found)
    {
      TopAbs_Orientation o = I->Transition().Orientation(TopAbs_IN);
      if (o == TopAbs_FORWARD)
      {
        found = true;
        L1.Append(I);
      }
      else
        L2.Append(I);
    }
    else
      L1.Append(I);
  }

  SList.Clear();
  SList.Append(L1);
  SList.Append(L2);
}

void TopOpeBRepDS_HDataStructure::SortOnParameter(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& List) const
{
  TopOpeBRepDS_PointIterator it(List);
  if (it.More())
  {
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> SList;
    SortOnParameter(List, SList);
    List.Assign(SList);
  }
}

void TopOpeBRepDS_HDataStructure::MinMaxOnParameter(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& List,
  double&                                                         parmin,
  double&                                                         parmax) const
{
  if (!List.IsEmpty())
  {
    double parline;
    parmin = RealLast();
    parmax = RealFirst();
    TopOpeBRepDS_PointIterator it(List);
    for (; it.More(); it.Next())
    {
      parline = it.Parameter();
      parmin  = std::min(parmin, parline);
      parmax  = std::max(parmax, parline);
    }
  }
}

bool TopOpeBRepDS_HDataStructure::ScanInterfList(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
  const TopOpeBRepDS_Point&                                           PDS) const
{
  for (; IT.More(); IT.Next())
  {
    TopOpeBRepDS_Kind GT = IT.Value()->GeometryType();
    int               G  = IT.Value()->Geometry();
    if (GT == TopOpeBRepDS_POINT)
    {
      const TopOpeBRepDS_Point& OOPDS = myDS.Point(G);
      bool                      iseq  = PDS.IsEqual(OOPDS);
      if (iseq)
        return iseq;
    }
    else if (GT == TopOpeBRepDS_VERTEX)
    {
      TopOpeBRepDS_Point OOPDS(myDS.Shape(G));
      bool               iseq = PDS.IsEqual(OOPDS);
      if (iseq)
        return iseq;
    }
  }
  return false;
}

bool TopOpeBRepDS_HDataStructure::GetGeometry(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
  const TopOpeBRepDS_Point&                                           PDS,
  int&                                                                G,
  TopOpeBRepDS_Kind&                                                  K) const
{
  bool found = ScanInterfList(IT, PDS);
  if (found)
  {
    G = IT.Value()->Geometry();
    K = IT.Value()->GeometryType();
  }
  return found;
}

void TopOpeBRepDS_HDataStructure::StoreInterference(
  const occ::handle<TopOpeBRepDS_Interference>&             I,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const TCollection_AsciiString&)
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
      myDS.ChangeSurfaceInterferences(G).Append(I);
      break;

    case TopOpeBRepDS_CURVE:
      myDS.ChangeCurveInterferences(G).Append(I);
      break;

    case TopOpeBRepDS_POINT:

      break;
    default:
      break;
  }
}

void TopOpeBRepDS_HDataStructure::StoreInterference(const occ::handle<TopOpeBRepDS_Interference>& I,
                                                    const TopoDS_Shape&                           S,
                                                    const TCollection_AsciiString&)
{
  bool h = myDS.HasShape(S);
  if (!h)
  {
    throw Standard_ProgramError("StoreInterference on shape out of DS");
    return;
  }
  StoreInterference(I, myDS.ChangeShapeInterferences(S));
}

void TopOpeBRepDS_HDataStructure::StoreInterference(const occ::handle<TopOpeBRepDS_Interference>& I,
                                                    const int IS,
                                                    const TCollection_AsciiString&)
{
  int n = myDS.NbShapes();
  if (IS < 1 || IS > n)
  {
    throw Standard_ProgramError("StoreInterference on index out of DS");
    return;
  }

  StoreInterference(I, myDS.ChangeShapeInterferences(IS));
}

void TopOpeBRepDS_HDataStructure::StoreInterferences(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const int                                                       IS

  ,
  const TCollection_AsciiString&)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lids =
    myDS.ChangeShapeInterferences(IS);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI);
  for (; it.More(); it.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I = it.Value();
    StoreInterference(I, lids);
  }
}

void TopOpeBRepDS_HDataStructure::StoreInterferences(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const TopoDS_Shape&                                             S

  ,
  const TCollection_AsciiString&)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lids = myDS.ChangeShapeInterferences(S);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI);
  for (; it.More(); it.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I = it.Value();
    StoreInterference(I, lids);
  }
}

void TopOpeBRepDS_HDataStructure::ClearStoreInterferences(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const int                                                       IS

  ,
  const TCollection_AsciiString&)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lids =
    myDS.ChangeShapeInterferences(IS);
  lids.Clear();
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI);
  for (; it.More(); it.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I = it.Value();
    StoreInterference(I, lids);
  }
}

void TopOpeBRepDS_HDataStructure::ClearStoreInterferences(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const TopoDS_Shape&                                             S

  ,
  const TCollection_AsciiString&)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lids = myDS.ChangeShapeInterferences(S);
  lids.Clear();
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI);
  for (; it.More(); it.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I = it.Value();
    StoreInterference(I, lids);
  }
}
