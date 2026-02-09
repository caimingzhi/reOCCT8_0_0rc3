#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <Geom2d_Curve.hpp>
#include <gp.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Map.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS_Association.hpp>
#include <TopOpeBRepDS_connex.hpp>
#include <TopOpeBRepDS_GapFiller.hpp>
#include <TopOpeBRepDS_GapTool.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_Point.hpp>
#include <TopOpeBRepDS_CurvePointInterference.hpp>

TopOpeBRepDS_GapFiller::TopOpeBRepDS_GapFiller(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
    : myHDS(HDS)
{
  myGapTool = new TopOpeBRepDS_GapTool(HDS);
  myAsso    = new TopOpeBRepDS_Association();
}

void TopOpeBRepDS_GapFiller::Perform()
{
  myGapTool->Init(myHDS);
  NCollection_Map<int> View;

  int NbCurves = myHDS->NbCurves();
  for (int i = 1; i <= NbCurves; i++)
  {
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI =
      myHDS->ChangeDS().ChangeCurveInterferences(i);
    for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI); it.More();
         it.Next())
    {
      NCollection_List<occ::handle<TopOpeBRepDS_Interference>> ALI;
      const occ::handle<TopOpeBRepDS_Interference>&            I = it.Value();
      if (I->GeometryType() == TopOpeBRepDS_POINT)
      {
        if (View.Add(I->Geometry()))
        {
          FindAssociatedPoints(I, ALI);
          myAsso->Associate(I, ALI);
        }
      }
    }
  }

  BuildNewGeometries();
}

bool Contains(const TopoDS_Shape& F, const TopoDS_Shape& E)
{
  TopExp_Explorer exp;
  for (exp.Init(F, E.ShapeType()); exp.More(); exp.Next())
  {

    if (exp.Current().IsSame(E))
      return true;
  }
  return false;
}

void TopOpeBRepDS_GapFiller::FindAssociatedPoints(
  const occ::handle<TopOpeBRepDS_Interference>&             I,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itSI(
    myGapTool->SameInterferences(I));
  for (; itSI.More(); itSI.Next())
  {
    if (myAsso->HasAssociation(itSI.Value()))
      return;
  }

  TopoDS_Shape E;
  if (!myGapTool->EdgeSupport(I, E))
  {
    return;
  }
  AddPointsOnShape(E, LI);

  TopoDS_Face F1, F2, F;
  if (!myGapTool->FacesSupport(I, F1, F2))
  {
    LI.Clear();
    return;
  }

  if (!Contains(F1, E))
  {
    F  = F2;
    F2 = F1;
    F1 = F;
  }

  const NCollection_List<TopoDS_Shape>& LF = FDSCNX_EdgeConnexitySameShape(E, myHDS);

  NCollection_List<TopoDS_Shape>::Iterator itLF(LF);
  for (; itLF.More(); itLF.Next())
  {
    if (!itLF.Value().IsSame(F1))
    {
      if (IsOnFace(I, TopoDS::Face(itLF.Value())))
      {
        LI.Clear();
        return;
      }
    }
  }

  for (itLF.Initialize(LF); itLF.More(); itLF.Next())
  {
    if (!itLF.Value().IsSame(F1))
    {
      FilterByFace(TopoDS::Face(itLF.Value()), LI);
    }
  }

  if (!LI.IsEmpty())
    FilterByFace(F2, LI);

  if (!LI.IsEmpty())
    FilterByIncidentDistance(F2, I, LI);

  if (!LI.IsEmpty())
  {
    LI.Append(I);
  }
}

bool TopOpeBRepDS_GapFiller::CheckConnexity(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&)
{
  return true;
}

void TopOpeBRepDS_GapFiller::AddPointsOnShape(
  const TopoDS_Shape&                                       S,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI)
{
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LIOnE =
    myHDS->DS().ShapeInterferences(S);
  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LIOnE); it.More();
       it.Next())
  {
    LI.Append(it.Value());
  }
}

void TopOpeBRepDS_GapFiller::AddPointsOnConnexShape(
  const TopoDS_Shape&,
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&)
{
}

void TopOpeBRepDS_GapFiller::FilterByFace(
  const TopoDS_Face&                                        F,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI)
{

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI);
  while (it.More())
  {
    if (!IsOnFace(it.Value(), F))
    {
      LI.Remove(it);
    }
    else
    {
      it.Next();
    }
  }
}

bool TopOpeBRepDS_GapFiller::IsOnFace(const occ::handle<TopOpeBRepDS_Interference>& I,
                                      const TopoDS_Face&                            F) const
{
  TopOpeBRepDS_Curve C;
  if (myGapTool->Curve(I, C))
  {
    TopoDS_Shape S1, S2;
    C.GetShapes(S1, S2);
    if (S1.IsSame(F))
      return true;
    if (S2.IsSame(F))
      return true;
  }
  return false;
}

void TopOpeBRepDS_GapFiller::FilterByEdge(
  const TopoDS_Edge&                                        E,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI)
{

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI);
  while (it.More())
  {
    if (!IsOnEdge(it.Value(), E))
    {
      LI.Remove(it);
    }
    else
    {
      it.Next();
    }
  }
}

bool TopOpeBRepDS_GapFiller::IsOnEdge(const occ::handle<TopOpeBRepDS_Interference>& I,
                                      const TopoDS_Edge&                            E) const
{
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI =
    myGapTool->SameInterferences(I);
  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI); it.More();
       it.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& IC = it.Value();
    if (IC->SupportType() == TopOpeBRepDS_EDGE)
    {
      const TopoDS_Shape& S1 = myHDS->Shape(IC->Support());
      if (S1.IsSame(E))
        return true;
    }
  }
  return false;
}

static bool Normal(const occ::handle<TopOpeBRepDS_GapTool>&        A,
                   const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                   const occ::handle<TopOpeBRepDS_Interference>&   I,
                   const TopoDS_Face&                              F,
                   gp_Dir&                                         D)

{
  TopOpeBRepDS_Kind GK, SK;
  int               IG, IS;
  gp_Pnt            PS;
  gp_Vec            TU, TV, N;
  gp_Pnt2d          P2d;

  BRepAdaptor_Surface S(F);
  if (S.GetType() == GeomAbs_Plane)
  {
    D = S.Plane().Axis().Direction();
    return true;
  }

  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI = A->SameInterferences(I);
  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI); it.More();
       it.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& IC = it.Value();
    IC->GKGSKS(GK, IG, SK, IS);
    if (SK == TopOpeBRepDS_CURVE)
    {
      const TopOpeBRepDS_Curve& C = HDS->Curve(IS);
      double P = occ::down_cast<TopOpeBRepDS_CurvePointInterference>(IC)->Parameter();

      TopoDS_Shape S1, S2;
      C.GetShapes(S1, S2);
      if (F.IsSame(S1))
      {
        if (C.Curve1().IsNull())
          return false;
        P2d = C.Curve1()->Value(P);
      }
      else
      {
        if (C.Curve2().IsNull())
          return false;
        P2d = C.Curve2()->Value(P);
      }

      if (S.UContinuity() >= GeomAbs_C1 && S.VContinuity() >= GeomAbs_C1)
      {
        S.D1(P2d.X(), P2d.Y(), PS, TU, TV);
        N = TU ^ TV;

        if (N.SquareMagnitude() >= gp::Resolution())
        {
          D = gp_Dir(N);
          return true;
        }
      }
      return false;
    }
  }
  return false;
}

void TopOpeBRepDS_GapFiller::FilterByIncidentDistance(
  const TopoDS_Face&                                        F,
  const occ::handle<TopOpeBRepDS_Interference>&             I,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI)
{
  double                                 DistMin = Precision::Infinite();
  occ::handle<TopOpeBRepDS_Interference> ISol;

  const TopOpeBRepDS_Point& PI1 = myHDS->Point(I->Geometry());
  const gp_Pnt              GPI = PI1.Point();

  BRepAdaptor_Surface S(F, false);

  double TolDef  = 0.94;
  double TolDist = 20 * PI1.Tolerance();
  gp_Dir N1, N2;
  bool   Ok1 = Normal(myGapTool, myHDS, I, F, N1);

  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI); it.More();
       it.Next())
  {

    const occ::handle<TopOpeBRepDS_Interference>& CI = it.Value();

    if (CI->HasSameGeometry(I))
      continue;

    bool                      Ok2  = Normal(myGapTool, myHDS, CI, F, N2);
    const TopOpeBRepDS_Point& P    = myHDS->Point((CI->Geometry()));
    const gp_Pnt              GP   = P.Point();
    double                    Dist = GP.Distance(GPI);

    if (Dist > TolDist)
    {
      if (Ok1 && Ok2)
      {
        if (N1.Dot(N2) < TolDef)
        {
          continue;
        }
      }
      continue;
    }

    if (Dist < DistMin)
    {
      DistMin = Dist;
      ISol    = it.Value();
    }
  }

  LI.Clear();
  if (!ISol.IsNull())
  {
    LI.Append(ISol);
  }
}

void TopOpeBRepDS_GapFiller::ReBuildGeom(const occ::handle<TopOpeBRepDS_Interference>& I,
                                         NCollection_Map<int>&                         View)
{
  if (!myAsso->HasAssociation(I))
    return;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&          LI = myAsso->Associated(I);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI);

  double      TolMax = 0, UMin = Precision::Infinite();
  double      UMax = -UMin, U;
  TopoDS_Edge E, CE;
  myGapTool->EdgeSupport(I, E);

  for (it.Initialize(LI); it.More(); it.Next())
  {
    TopOpeBRepDS_Point PP = myHDS->Point(it.Value()->Geometry());
    TolMax                = std::max(TolMax, PP.Tolerance());
    if (myGapTool->ParameterOnEdge(it.Value(), E, U))
    {
      UMin = std::min(UMin, U);
      UMax = std::max(UMax, U);
    }
    myGapTool->EdgeSupport(it.Value(), CE);
    if (!CE.IsSame(E))
    {
      return;
    }
  }
  U = (UMax + UMin) * 0.5;
  BRepAdaptor_Curve  C(E);
  gp_Pnt             GP = C.Value(U);
  TopOpeBRepDS_Point P(GP, TolMax);

  int IP = myHDS->ChangeDS().AddPoint(P);
  for (it.Initialize(LI); it.More(); it.Next())
  {
    View.Add(it.Value()->Geometry());
    myGapTool->SetParameterOnEdge(it.Value(), E, U);
    myGapTool->SetPoint(it.Value(), IP);
  }
  myGapTool->SetParameterOnEdge(I, E, U);
  myGapTool->SetPoint(I, IP);
  View.Add(IP);
}

void TopOpeBRepDS_GapFiller::BuildNewGeometries()
{
  NCollection_Map<int> View;
  int                  NbCurves = myHDS->NbCurves();
  int                  NbPoints = myHDS->NbPoints();
  for (int i = 1; i <= NbCurves; i++)
  {
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI =
      myHDS->ChangeDS().ChangeCurveInterferences(i);
    for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI); it.More();
         it.Next())
    {
      occ::handle<TopOpeBRepDS_Interference> I  = it.Value();
      int                                    IP = I->Geometry();
      if (View.Add(IP) && IP <= NbPoints)
        ReBuildGeom(I, View);
    }
  }
}
