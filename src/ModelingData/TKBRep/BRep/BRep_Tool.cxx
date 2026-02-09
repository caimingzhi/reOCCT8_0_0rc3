#include <BRep_Curve3D.hpp>
#include <BRep_CurveOnClosedSurface.hpp>
#include <BRep_CurveOnSurface.hpp>
#include <BRep_CurveRepresentation.hpp>
#include <BRep_Polygon3D.hpp>
#include <BRep_PolygonOnSurface.hpp>
#include <BRep_PolygonOnTriangulation.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_TFace.hpp>
#include <BRep_Tool.hpp>
#include <BRep_TVertex.hpp>
#include <ElSLib.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor.hpp>
#include <Geom_Curve.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomProjLib.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_IncAllocator.hpp>
#include <Poly_Polygon2D.hpp>
#include <Poly_Polygon3D.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Poly_Triangulation.hpp>
#include <Precision.hpp>
#include <ProjLib_ProjectedCurve.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_NullObject.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <BRep_GCurve.hpp>

static bool IsPlane(const occ::handle<Geom_Surface>& aS);

const occ::handle<Geom_Surface>& BRep_Tool::Surface(const TopoDS_Face& F, TopLoc_Location& L)
{
  const BRep_TFace* TF = static_cast<const BRep_TFace*>(F.TShape().get());
  L                    = F.Location() * TF->Location();
  return TF->Surface();
}

occ::handle<Geom_Surface> BRep_Tool::Surface(const TopoDS_Face& F)
{
  const BRep_TFace*                TF = static_cast<const BRep_TFace*>(F.TShape().get());
  const occ::handle<Geom_Surface>& S  = TF->Surface();

  if (S.IsNull())
    return S;

  TopLoc_Location L = F.Location() * TF->Location();
  if (!L.IsIdentity())
  {
    occ::handle<Geom_Geometry> aCopy = S->Transformed(L.Transformation());
    Geom_Surface*              aGS   = static_cast<Geom_Surface*>(aCopy.get());
    return occ::handle<Geom_Surface>(aGS);
  }
  return S;
}

const occ::handle<Poly_Triangulation>& BRep_Tool::Triangulation(
  const TopoDS_Face&     theFace,
  TopLoc_Location&       theLocation,
  const Poly_MeshPurpose theMeshPurpose)
{
  theLocation              = theFace.Location();
  const BRep_TFace* aTFace = static_cast<const BRep_TFace*>(theFace.TShape().get());
  return aTFace->Triangulation(theMeshPurpose);
}

const NCollection_List<occ::handle<Poly_Triangulation>>& BRep_Tool::Triangulations(
  const TopoDS_Face& theFace,
  TopLoc_Location&   theLocation)
{
  theLocation              = theFace.Location();
  const BRep_TFace* aTFace = static_cast<const BRep_TFace*>(theFace.TShape().get());
  return aTFace->Triangulations();
}

double BRep_Tool::Tolerance(const TopoDS_Face& F)
{
  const BRep_TFace* TF   = static_cast<const BRep_TFace*>(F.TShape().get());
  double            p    = TF->Tolerance();
  constexpr double  pMin = Precision::Confusion();
  if (p > pMin)
    return p;
  else
    return pMin;
}

bool BRep_Tool::NaturalRestriction(const TopoDS_Face& F)
{
  const BRep_TFace* TF = static_cast<const BRep_TFace*>(F.TShape().get());
  return TF->NaturalRestriction();
}

static const occ::handle<Geom_Curve> nullCurve;

const occ::handle<Geom_Curve>& BRep_Tool::Curve(const TopoDS_Edge& E,
                                                TopLoc_Location&   L,
                                                double&            First,
                                                double&            Last)
{

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsCurve3D())
    {
      const BRep_Curve3D* GC = static_cast<const BRep_Curve3D*>(cr.get());
      L                      = E.Location() * GC->Location();
      GC->Range(First, Last);
      return GC->Curve3D();
    }
    itcr.Next();
  }
  L.Identity();
  First = Last = 0.;
  return nullCurve;
}

occ::handle<Geom_Curve> BRep_Tool::Curve(const TopoDS_Edge& E, double& First, double& Last)
{
  TopLoc_Location                L;
  const occ::handle<Geom_Curve>& C = Curve(E, L, First, Last);
  if (!C.IsNull())
  {
    if (!L.IsIdentity())
    {
      occ::handle<Geom_Geometry> aCopy = C->Transformed(L.Transformation());
      Geom_Curve*                aGC   = static_cast<Geom_Curve*>(aCopy.get());
      return occ::handle<Geom_Curve>(aGC);
    }
  }
  return C;
}

bool BRep_Tool::IsGeometric(const TopoDS_Face& F)
{
  const BRep_TFace*                TF = static_cast<const BRep_TFace*>(F.TShape().get());
  const occ::handle<Geom_Surface>& S  = TF->Surface();
  return !S.IsNull();
}

bool BRep_Tool::IsGeometric(const TopoDS_Edge& E)
{

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsCurve3D())
    {
      occ::handle<BRep_Curve3D> GC(occ::down_cast<BRep_Curve3D>(cr));
      if (!GC.IsNull() && !GC->Curve3D().IsNull())
        return true;
    }
    else if (cr->IsCurveOnSurface())
      return true;
    itcr.Next();
  }
  return false;
}

static const occ::handle<Poly_Polygon3D> nullPolygon3D;

const occ::handle<Poly_Polygon3D>& BRep_Tool::Polygon3D(const TopoDS_Edge& E, TopLoc_Location& L)
{

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsPolygon3D())
    {
      const BRep_Polygon3D* GC = static_cast<const BRep_Polygon3D*>(cr.get());
      L                        = E.Location() * GC->Location();
      return GC->Polygon3D();
    }
    itcr.Next();
  }
  L.Identity();
  return nullPolygon3D;
}

occ::handle<Geom2d_Curve> BRep_Tool::CurveOnSurface(const TopoDS_Edge& E,
                                                    const TopoDS_Face& F,
                                                    double&            First,
                                                    double&            Last,
                                                    bool*              theIsStored)
{
  TopLoc_Location                  l;
  const occ::handle<Geom_Surface>& S          = BRep_Tool::Surface(F, l);
  TopoDS_Edge                      aLocalEdge = E;
  if (F.Orientation() == TopAbs_REVERSED)
  {
    aLocalEdge.Reverse();
  }
  return CurveOnSurface(aLocalEdge, S, l, First, Last, theIsStored);
}

static const occ::handle<Geom2d_Curve> nullPCurve;

occ::handle<Geom2d_Curve> BRep_Tool::CurveOnSurface(const TopoDS_Edge&               E,
                                                    const occ::handle<Geom_Surface>& S,
                                                    const TopLoc_Location&           L,
                                                    double&                          First,
                                                    double&                          Last,
                                                    bool*                            theIsStored)
{
  TopLoc_Location loc         = L.Predivided(E.Location());
  bool            Eisreversed = (E.Orientation() == TopAbs_REVERSED);
  if (theIsStored)
    *theIsStored = true;

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsCurveOnSurface(S, loc))
    {
      const BRep_GCurve* GC = static_cast<const BRep_GCurve*>(cr.get());
      GC->Range(First, Last);
      if (GC->IsCurveOnClosedSurface() && Eisreversed)
        return GC->PCurve2();
      else
        return GC->PCurve();
    }
    itcr.Next();
  }

  if (theIsStored)
    *theIsStored = false;
  return CurveOnPlane(E, S, L, First, Last);
}

occ::handle<Geom2d_Curve> BRep_Tool::CurveOnPlane(const TopoDS_Edge&               E,
                                                  const occ::handle<Geom_Surface>& S,
                                                  const TopLoc_Location&           L,
                                                  double&                          First,
                                                  double&                          Last)
{
  First = Last = 0.;

  occ::handle<Geom_Plane>                     GP;
  occ::handle<Geom_RectangularTrimmedSurface> GRTS;
  GRTS = occ::down_cast<Geom_RectangularTrimmedSurface>(S);
  if (!GRTS.IsNull())
    GP = occ::down_cast<Geom_Plane>(GRTS->BasisSurface());
  else
    GP = occ::down_cast<Geom_Plane>(S);

  if (GP.IsNull())

    return nullPCurve;

  double                  f, l;
  TopLoc_Location         aCurveLocation;
  occ::handle<Geom_Curve> C3D = BRep_Tool::Curve(E, aCurveLocation, f, l);

  if (C3D.IsNull())

    return nullPCurve;

  aCurveLocation = aCurveLocation.Predivided(L);
  First          = f;
  Last           = l;

  if (!aCurveLocation.IsIdentity())
  {
    const gp_Trsf& aTrsf = aCurveLocation.Transformation();
    C3D                  = occ::down_cast<Geom_Curve>(C3D->Transformed(aTrsf));
    f                    = C3D->TransformedParameter(f, aTrsf);
    l                    = C3D->TransformedParameter(l, aTrsf);
  }

  occ::handle<Geom_Curve> ProjOnPlane =
    GeomProjLib::ProjectOnPlane(new Geom_TrimmedCurve(C3D, f, l, true, false),
                                GP,
                                GP->Position().Direction(),
                                true);

  occ::handle<GeomAdaptor_Surface> HS = new GeomAdaptor_Surface(GP);
  occ::handle<GeomAdaptor_Curve>   HC = new GeomAdaptor_Curve(ProjOnPlane);

  ProjLib_ProjectedCurve    Proj(HS, HC);
  occ::handle<Geom2d_Curve> pc = Geom2dAdaptor::MakeCurve(Proj);

  if (pc->DynamicType() == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    occ::handle<Geom2d_TrimmedCurve> TC = occ::down_cast<Geom2d_TrimmedCurve>(pc);
    pc                                  = TC->BasisCurve();
  }

  return pc;
}

void BRep_Tool::CurveOnSurface(const TopoDS_Edge&         E,
                               occ::handle<Geom2d_Curve>& C,
                               occ::handle<Geom_Surface>& S,
                               TopLoc_Location&           L,
                               double&                    First,
                               double&                    Last)
{

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsCurveOnSurface())
    {
      const BRep_GCurve* GC = static_cast<const BRep_GCurve*>(cr.get());
      C                     = GC->PCurve();
      S                     = GC->Surface();
      L                     = E.Location() * GC->Location();
      GC->Range(First, Last);
      return;
    }
    itcr.Next();
  }

  C.Nullify();
  S.Nullify();
  L.Identity();
  First = Last = 0.;
}

void BRep_Tool::CurveOnSurface(const TopoDS_Edge&         E,
                               occ::handle<Geom2d_Curve>& C,
                               occ::handle<Geom_Surface>& S,
                               TopLoc_Location&           L,
                               double&                    First,
                               double&                    Last,
                               const int                  Index)
{
  if (Index < 1)
    return;

  int i = 0;

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());
  for (; itcr.More(); itcr.Next())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsCurveOnSurface())
    {
      const BRep_GCurve* GC = static_cast<const BRep_GCurve*>(cr.get());
      ++i;

      if (i == Index)
        C = GC->PCurve();
      else if (GC->IsCurveOnClosedSurface() && (++i == Index))
        C = GC->PCurve2();
      else
        continue;

      S = GC->Surface();
      L = E.Location() * GC->Location();
      GC->Range(First, Last);
      return;
    }
  }

  C.Nullify();
  S.Nullify();
  L.Identity();
  First = Last = 0.;
}

occ::handle<Poly_Polygon2D> BRep_Tool::PolygonOnSurface(const TopoDS_Edge& E, const TopoDS_Face& F)
{
  TopLoc_Location                  l;
  const occ::handle<Geom_Surface>& S          = BRep_Tool::Surface(F, l);
  TopoDS_Edge                      aLocalEdge = E;
  if (F.Orientation() == TopAbs_REVERSED)
  {
    aLocalEdge.Reverse();
  }

  return PolygonOnSurface(aLocalEdge, S, l);
}

static const occ::handle<Poly_Polygon2D> nullPolygon2D;

occ::handle<Poly_Polygon2D> BRep_Tool::PolygonOnSurface(const TopoDS_Edge&               E,
                                                        const occ::handle<Geom_Surface>& S,
                                                        const TopLoc_Location&           L)
{
  TopLoc_Location l           = L.Predivided(E.Location());
  bool            Eisreversed = (E.Orientation() == TopAbs_REVERSED);

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsPolygonOnSurface(S, l))
    {
      if (cr->IsPolygonOnClosedSurface() && Eisreversed)
        return cr->Polygon2();
      else
        return cr->Polygon();
    }
    itcr.Next();
  }

  return nullPolygon2D;
}

void BRep_Tool::PolygonOnSurface(const TopoDS_Edge&           E,
                                 occ::handle<Poly_Polygon2D>& P,
                                 occ::handle<Geom_Surface>&   S,
                                 TopLoc_Location&             L)
{

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsPolygonOnSurface())
    {
      const BRep_PolygonOnSurface* PS = static_cast<const BRep_PolygonOnSurface*>(cr.get());
      P                               = PS->Polygon();
      S                               = PS->Surface();
      L                               = E.Location() * PS->Location();
      return;
    }
    itcr.Next();
  }

  L.Identity();
  P.Nullify();
  S.Nullify();
}

void BRep_Tool::PolygonOnSurface(const TopoDS_Edge&           E,
                                 occ::handle<Poly_Polygon2D>& P,
                                 occ::handle<Geom_Surface>&   S,
                                 TopLoc_Location&             L,
                                 const int                    Index)
{
  int i = 0;

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsPolygonOnSurface())
    {
      const BRep_PolygonOnSurface* PS = static_cast<const BRep_PolygonOnSurface*>(cr.get());
      i++;
      if (i > Index)
        break;
      if (i == Index)
      {
        P = PS->Polygon();
        S = PS->Surface();
        L = E.Location() * PS->Location();
        return;
      }
    }
    itcr.Next();
  }

  L.Identity();
  P.Nullify();
  S.Nullify();
}

static const occ::handle<Poly_PolygonOnTriangulation> nullArray;

const occ::handle<Poly_PolygonOnTriangulation>& BRep_Tool::PolygonOnTriangulation(
  const TopoDS_Edge&                     E,
  const occ::handle<Poly_Triangulation>& T,
  const TopLoc_Location&                 L)
{
  TopLoc_Location l           = L.Predivided(E.Location());
  bool            Eisreversed = (E.Orientation() == TopAbs_REVERSED);

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsPolygonOnTriangulation(T, l))
    {
      if (cr->IsPolygonOnClosedTriangulation() && Eisreversed)
        return cr->PolygonOnTriangulation2();
      else
        return cr->PolygonOnTriangulation();
    }
    itcr.Next();
  }

  return nullArray;
}

void BRep_Tool::PolygonOnTriangulation(const TopoDS_Edge&                        E,
                                       occ::handle<Poly_PolygonOnTriangulation>& P,
                                       occ::handle<Poly_Triangulation>&          T,
                                       TopLoc_Location&                          L)
{

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsPolygonOnTriangulation())
    {
      const BRep_PolygonOnTriangulation* PT =
        static_cast<const BRep_PolygonOnTriangulation*>(cr.get());
      P = PT->PolygonOnTriangulation();
      T = PT->Triangulation();
      L = E.Location() * PT->Location();
      return;
    }
    itcr.Next();
  }

  L.Identity();
  P.Nullify();
  T.Nullify();
}

void BRep_Tool::PolygonOnTriangulation(const TopoDS_Edge&                        E,
                                       occ::handle<Poly_PolygonOnTriangulation>& P,
                                       occ::handle<Poly_Triangulation>&          T,
                                       TopLoc_Location&                          L,
                                       const int                                 Index)
{
  int i = 0;

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsPolygonOnTriangulation())
    {
      const BRep_PolygonOnTriangulation* PT =
        static_cast<const BRep_PolygonOnTriangulation*>(cr.get());
      i++;
      if (i > Index)
        break;
      if (i == Index)
      {
        T = PT->Triangulation();
        P = PT->PolygonOnTriangulation();
        L = E.Location() * PT->Location();
        return;
      }
    }
    itcr.Next();
  }

  L.Identity();
  P.Nullify();
  T.Nullify();
}

bool BRep_Tool::IsClosed(const TopoDS_Edge& E, const TopoDS_Face& F)
{
  TopLoc_Location                  l;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(F, l);
  if (IsClosed(E, S, l))
    return true;
  const occ::handle<Poly_Triangulation>& T = BRep_Tool::Triangulation(F, l);
  return IsClosed(E, T, l);
}

bool BRep_Tool::IsClosed(const TopoDS_Edge&               E,
                         const occ::handle<Geom_Surface>& S,
                         const TopLoc_Location&           L)
{

  if (IsPlane(S))
  {
    return false;
  }

  TopLoc_Location l = L.Predivided(E.Location());

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsCurveOnSurface(S, l) && cr->IsCurveOnClosedSurface())
      return true;
    itcr.Next();
  }
  return false;
}

bool BRep_Tool::IsClosed(const TopoDS_Edge&                     E,
                         const occ::handle<Poly_Triangulation>& T,
                         const TopLoc_Location&                 L)
{
  if (T.IsNull())
  {
    return false;
  }

  TopLoc_Location l = L.Predivided(E.Location());

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsPolygonOnTriangulation(T, l) && cr->IsPolygonOnClosedTriangulation())
      return true;
    itcr.Next();
  }
  return false;
}

double BRep_Tool::Tolerance(const TopoDS_Edge& E)
{
  const BRep_TEdge* TE   = static_cast<const BRep_TEdge*>(E.TShape().get());
  double            p    = TE->Tolerance();
  constexpr double  pMin = Precision::Confusion();
  if (p > pMin)
    return p;
  else
    return pMin;
}

bool BRep_Tool::SameParameter(const TopoDS_Edge& E)
{
  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  return TE->SameParameter();
}

bool BRep_Tool::SameRange(const TopoDS_Edge& E)
{
  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  return TE->SameRange();
}

bool BRep_Tool::Degenerated(const TopoDS_Edge& E)
{
  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  return TE->Degenerated();
}

void BRep_Tool::Range(const TopoDS_Edge& E, double& First, double& Last)
{

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsCurve3D())
    {
      const BRep_Curve3D* CR = static_cast<const BRep_Curve3D*>(cr.get());
      if (!CR->Curve3D().IsNull())
      {
        First = CR->First();
        Last  = CR->Last();
        return;
      }
    }
    else if (cr->IsCurveOnSurface())
    {
      const BRep_GCurve* CR = static_cast<const BRep_GCurve*>(cr.get());
      First                 = CR->First();
      Last                  = CR->Last();
      return;
    }
    itcr.Next();
  }
  First = Last = 0.;
}

void BRep_Tool::Range(const TopoDS_Edge&               E,
                      const occ::handle<Geom_Surface>& S,
                      const TopLoc_Location&           L,
                      double&                          First,
                      double&                          Last)
{
  TopLoc_Location l = L.Predivided(E.Location());

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsCurveOnSurface(S, l))
    {
      const BRep_CurveOnSurface* CR = static_cast<const BRep_CurveOnSurface*>(cr.get());
      CR->Range(First, Last);
      break;
    }
    itcr.Next();
  }
  if (!itcr.More())
  {
    Range(E, First, Last);
  }
  E.TShape()->Modified(true);
}

void BRep_Tool::Range(const TopoDS_Edge& E, const TopoDS_Face& F, double& First, double& Last)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(F, L);
  Range(E, S, L, First, Last);
}

void BRep_Tool::UVPoints(const TopoDS_Edge&               E,
                         const occ::handle<Geom_Surface>& S,
                         const TopLoc_Location&           L,
                         gp_Pnt2d&                        PFirst,
                         gp_Pnt2d&                        PLast)
{
  TopLoc_Location l           = L.Predivided(E.Location());
  bool            Eisreversed = (E.Orientation() == TopAbs_REVERSED);

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsCurveOnSurface(S, l))
    {
      if (cr->IsCurveOnClosedSurface() && Eisreversed)
      {
        const BRep_CurveOnClosedSurface* CR =
          static_cast<const BRep_CurveOnClosedSurface*>(cr.get());
        CR->UVPoints2(PFirst, PLast);
      }
      else
      {
        const BRep_CurveOnSurface* CR = static_cast<const BRep_CurveOnSurface*>(cr.get());
        CR->UVPoints(PFirst, PLast);
      }
      return;
    }
    itcr.Next();
  }

  occ::handle<Geom_Plane>                     GP;
  occ::handle<Geom_RectangularTrimmedSurface> GRTS;
  GRTS = occ::down_cast<Geom_RectangularTrimmedSurface>(S);
  if (!GRTS.IsNull())
    GP = occ::down_cast<Geom_Plane>(GRTS->BasisSurface());
  else
    GP = occ::down_cast<Geom_Plane>(S);

  if (!GP.IsNull())
  {

    TopoDS_Vertex Vf, Vl;
    TopExp::Vertices(E, Vf, Vl);

    TopLoc_Location Linverted = L.Inverted();
    Vf.Move(Linverted, false);
    Vl.Move(Linverted, false);
    double u, v;
    gp_Pln pln = GP->Pln();

    u = v = 0.;
    if (!Vf.IsNull())
    {
      gp_Pnt PF = BRep_Tool::Pnt(Vf);
      ElSLib::Parameters(pln, PF, u, v);
    }
    PFirst.SetCoord(u, v);

    u = v = 0.;
    if (!Vl.IsNull())
    {
      gp_Pnt PL = BRep_Tool::Pnt(Vl);
      ElSLib::Parameters(pln, PL, u, v);
    }
    PLast.SetCoord(u, v);
  }
  else
  {
    PFirst.SetCoord(0., 0.);
    PLast.SetCoord(0., 0.);
  }
}

void BRep_Tool::UVPoints(const TopoDS_Edge& E,
                         const TopoDS_Face& F,
                         gp_Pnt2d&          PFirst,
                         gp_Pnt2d&          PLast)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S          = BRep_Tool::Surface(F, L);
  TopoDS_Edge                      aLocalEdge = E;
  if (F.Orientation() == TopAbs_REVERSED)
  {
    aLocalEdge.Reverse();
  }

  UVPoints(aLocalEdge, S, L, PFirst, PLast);
}

void BRep_Tool::SetUVPoints(const TopoDS_Edge&               E,
                            const occ::handle<Geom_Surface>& S,
                            const TopLoc_Location&           L,
                            const gp_Pnt2d&                  PFirst,
                            const gp_Pnt2d&                  PLast)
{
  TopLoc_Location l           = L.Predivided(E.Location());
  bool            Eisreversed = (E.Orientation() == TopAbs_REVERSED);

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    occ::handle<BRep_CurveRepresentation> cr = itcr.Value();
    if (cr->IsCurveOnSurface(S, l))
    {
      if (cr->IsCurveOnClosedSurface() && Eisreversed)
      {
        BRep_CurveOnClosedSurface* CS = static_cast<BRep_CurveOnClosedSurface*>(cr.get());
        CS->SetUVPoints2(PFirst, PLast);
      }
      else
      {
        BRep_CurveOnSurface* CS = static_cast<BRep_CurveOnSurface*>(cr.get());
        CS->SetUVPoints(PFirst, PLast);
      }
    }
    itcr.Next();
  }
}

void BRep_Tool::SetUVPoints(const TopoDS_Edge& E,
                            const TopoDS_Face& F,
                            const gp_Pnt2d&    PFirst,
                            const gp_Pnt2d&    PLast)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S          = BRep_Tool::Surface(F, L);
  TopoDS_Edge                      aLocalEdge = E;
  if (F.Orientation() == TopAbs_REVERSED)
  {
    aLocalEdge.Reverse();
  }

  SetUVPoints(aLocalEdge, S, L, PFirst, PLast);
}

bool BRep_Tool::HasContinuity(const TopoDS_Edge& E, const TopoDS_Face& F1, const TopoDS_Face& F2)
{
  TopLoc_Location                  l1, l2;
  const occ::handle<Geom_Surface>& S1 = BRep_Tool::Surface(F1, l1);
  const occ::handle<Geom_Surface>& S2 = BRep_Tool::Surface(F2, l2);
  return HasContinuity(E, S1, S2, l1, l2);
}

GeomAbs_Shape BRep_Tool::Continuity(const TopoDS_Edge& E,
                                    const TopoDS_Face& F1,
                                    const TopoDS_Face& F2)
{
  TopLoc_Location                  l1, l2;
  const occ::handle<Geom_Surface>& S1 = BRep_Tool::Surface(F1, l1);
  const occ::handle<Geom_Surface>& S2 = BRep_Tool::Surface(F2, l2);
  return Continuity(E, S1, S2, l1, l2);
}

bool BRep_Tool::HasContinuity(const TopoDS_Edge&               E,
                              const occ::handle<Geom_Surface>& S1,
                              const occ::handle<Geom_Surface>& S2,
                              const TopLoc_Location&           L1,
                              const TopLoc_Location&           L2)
{
  const TopLoc_Location& Eloc = E.Location();
  TopLoc_Location        l1   = L1.Predivided(Eloc);
  TopLoc_Location        l2   = L2.Predivided(Eloc);

  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsRegularity(S1, S2, l1, l2))
      return true;
    itcr.Next();
  }
  return false;
}

GeomAbs_Shape BRep_Tool::Continuity(const TopoDS_Edge&               E,
                                    const occ::handle<Geom_Surface>& S1,
                                    const occ::handle<Geom_Surface>& S2,
                                    const TopLoc_Location&           L1,
                                    const TopLoc_Location&           L2)
{
  TopLoc_Location l1 = L1.Predivided(E.Location());
  TopLoc_Location l2 = L2.Predivided(E.Location());

  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(
    (*((occ::handle<BRep_TEdge>*)&E.TShape()))->ChangeCurves());

  while (itcr.More())
  {
    const occ::handle<BRep_CurveRepresentation>& cr = itcr.Value();
    if (cr->IsRegularity(S1, S2, l1, l2))
      return cr->Continuity();
    itcr.Next();
  }
  return GeomAbs_C0;
}

bool BRep_Tool::HasContinuity(const TopoDS_Edge& E)
{
  const BRep_TEdge* TE = static_cast<const BRep_TEdge*>(E.TShape().get());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());

  for (; itcr.More(); itcr.Next())
  {
    const occ::handle<BRep_CurveRepresentation>& CR = itcr.Value();
    if (CR->IsRegularity())
      return true;
  }
  return false;
}

GeomAbs_Shape BRep_Tool::MaxContinuity(const TopoDS_Edge& theEdge)
{
  GeomAbs_Shape aMaxCont = GeomAbs_C0;
  for (NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator aReprIter(
         (*((occ::handle<BRep_TEdge>*)&theEdge.TShape()))->ChangeCurves());
       aReprIter.More();
       aReprIter.Next())
  {
    const occ::handle<BRep_CurveRepresentation>& aRepr = aReprIter.Value();
    if (aRepr->IsRegularity())
    {
      const GeomAbs_Shape aCont = aRepr->Continuity();
      if ((int)aCont > (int)aMaxCont)
      {
        aMaxCont = aCont;
      }
    }
  }
  return aMaxCont;
}

gp_Pnt BRep_Tool::Pnt(const TopoDS_Vertex& V)
{
  const BRep_TVertex* TV = static_cast<const BRep_TVertex*>(V.TShape().get());

  if (TV == nullptr)
  {
    throw Standard_NullObject("BRep_Tool:: TopoDS_Vertex hasn't gp_Pnt");
  }

  const gp_Pnt& P = TV->Pnt();
  if (V.Location().IsIdentity())
  {
    return P;
  }

  return P.Transformed(V.Location().Transformation());
}

double BRep_Tool::Tolerance(const TopoDS_Vertex& V)
{
  const BRep_TVertex* aTVert = static_cast<const BRep_TVertex*>(V.TShape().get());

  if (aTVert == nullptr)
  {
    throw Standard_NullObject("BRep_Tool:: TopoDS_Vertex hasn't gp_Pnt");
  }

  double           p    = aTVert->Tolerance();
  constexpr double pMin = Precision::Confusion();
  if (p > pMin)
    return p;
  else
    return pMin;
}

bool BRep_Tool::Parameter(const TopoDS_Vertex& theV, const TopoDS_Edge& theE, double& theParam)
{

  bool               rev = false;
  TopoDS_Shape       VF;
  TopAbs_Orientation orient = TopAbs_INTERNAL;

  TopoDS_Iterator itv(theE.Oriented(TopAbs_FORWARD));

  if (!itv.More() && BRep_Tool::Degenerated(theE))
  {
    orient = theV.Orientation();
  }

  while (itv.More())
  {
    const TopoDS_Shape& Vcur = itv.Value();
    if (theV.IsSame(Vcur))
    {
      if (VF.IsNull())
      {
        VF = Vcur;
      }
      else
      {
        rev = theE.Orientation() == TopAbs_REVERSED;
        if (Vcur.Orientation() == theV.Orientation())
        {
          VF = Vcur;
        }
      }
    }
    itv.Next();
  }

  if (!VF.IsNull())
    orient = VF.Orientation();

  double f, l;

  if (orient == TopAbs_FORWARD)
  {
    BRep_Tool::Range(theE, f, l);
    theParam = (rev) ? l : f;
    return true;
  }

  else if (orient == TopAbs_REVERSED)
  {
    BRep_Tool::Range(theE, f, l);
    theParam = (rev) ? f : l;
    return true;
  }

  else
  {
    TopLoc_Location                L;
    const occ::handle<Geom_Curve>& C = BRep_Tool::Curve(theE, L, f, l);
    L                                = L.Predivided(theV.Location());
    if (!C.IsNull() || BRep_Tool::Degenerated(theE))
    {
      const BRep_TVertex* TV = static_cast<const BRep_TVertex*>(theV.TShape().get());
      NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr(TV->Points());

      while (itpr.More())
      {
        const occ::handle<BRep_PointRepresentation>& pr = itpr.Value();
        if (pr->IsPointOnCurve(C, L))
        {
          double p   = pr->Parameter();
          double res = p;
          if (!C.IsNull())
          {

            if (Precision::IsNegativeInfinite(f))
            {
              theParam = pr->Parameter();
              return true;
            };
            if (Precision::IsPositiveInfinite(l))
            {
              theParam = pr->Parameter();
              return true;
            }
            gp_Pnt Pf  = C->Value(f).Transformed(L.Transformation());
            gp_Pnt Pl  = C->Value(l).Transformed(L.Transformation());
            double tol = BRep_Tool::Tolerance(theV);
            if (Pf.Distance(Pl) < tol)
            {
              if (Pf.Distance(BRep_Tool::Pnt(theV)) < tol)
              {
                if (theV.Orientation() == TopAbs_FORWARD)
                  res = f;
                else
                  res = l;
              }
            }
          }
          theParam = res;
          return true;
        }
        itpr.Next();
      }
    }
    else
    {

      occ::handle<Geom2d_Curve> PC;
      occ::handle<Geom_Surface> S;
      BRep_Tool::CurveOnSurface(theE, PC, S, L, f, l);
      L                      = L.Predivided(theV.Location());
      const BRep_TVertex* TV = static_cast<const BRep_TVertex*>(theV.TShape().get());
      NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr(TV->Points());

      while (itpr.More())
      {
        const occ::handle<BRep_PointRepresentation>& pr = itpr.Value();
        if (pr->IsPointOnCurveOnSurface(PC, S, L))
        {
          double p = pr->Parameter();

          if (PC->IsClosed())
          {
            if ((p == PC->FirstParameter()) || (p == PC->LastParameter()))
            {
              if (theV.Orientation() == TopAbs_FORWARD)
                p = PC->FirstParameter();
              else
                p = PC->LastParameter();
            }
          }
          theParam = p;
          return true;
        }
        itpr.Next();
      }
    }
  }

  return false;
}

double BRep_Tool::Parameter(const TopoDS_Vertex& V, const TopoDS_Edge& E)
{
  double p;
  if (Parameter(V, E, p))
    return p;
  throw Standard_NoSuchObject("BRep_Tool:: no parameter on edge");
}

double BRep_Tool::Parameter(const TopoDS_Vertex& V, const TopoDS_Edge& E, const TopoDS_Face& F)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(F, L);
  return BRep_Tool::Parameter(V, E, S, L);
}

double BRep_Tool::Parameter(const TopoDS_Vertex&             V,
                            const TopoDS_Edge&               E,
                            const occ::handle<Geom_Surface>& S,
                            const TopLoc_Location&           L)
{

  bool            rev = false;
  TopoDS_Shape    VF;
  TopoDS_Iterator itv(E.Oriented(TopAbs_FORWARD));

  while (itv.More())
  {
    if (V.IsSame(itv.Value()))
    {
      if (VF.IsNull())
        VF = itv.Value();
      else
      {
        rev = E.Orientation() == TopAbs_REVERSED;
        if (itv.Value().Orientation() == V.Orientation())
          VF = itv.Value();
      }
    }
    itv.Next();
  }

  TopAbs_Orientation orient = TopAbs_INTERNAL;
  if (!VF.IsNull())
    orient = VF.Orientation();

  double f, l;

  if (orient == TopAbs_FORWARD)
  {
    BRep_Tool::Range(E, S, L, f, l);
    return (rev) ? l : f;
  }

  else if (orient == TopAbs_REVERSED)
  {
    BRep_Tool::Range(E, S, L, f, l);
    return (rev) ? f : l;
  }

  else
  {
    occ::handle<Geom2d_Curve> PC = BRep_Tool::CurveOnSurface(E, S, L, f, l);
    const BRep_TVertex*       TV = static_cast<const BRep_TVertex*>(V.TShape().get());
    NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr(TV->Points());

    while (itpr.More())
    {
      if (itpr.Value()->IsPointOnCurveOnSurface(PC, S, L))
        return itpr.Value()->Parameter();
      itpr.Next();
    }
  }

  TopLoc_Location                L1;
  const occ::handle<Geom_Curve>& C = BRep_Tool::Curve(E, L1, f, l);
  L1                               = L1.Predivided(V.Location());
  if (!C.IsNull() || Degenerated(E))
  {
    const BRep_TVertex* TV = static_cast<const BRep_TVertex*>(V.TShape().get());
    NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr(TV->Points());

    while (itpr.More())
    {
      const occ::handle<BRep_PointRepresentation>& pr = itpr.Value();
      if (pr->IsPointOnCurve(C, L1))
      {
        double p   = pr->Parameter();
        double res = p;
        if (!C.IsNull())
        {

          if (Precision::IsNegativeInfinite(f))
            return res;
          if (Precision::IsPositiveInfinite(l))
            return res;
          gp_Pnt Pf  = C->Value(f).Transformed(L1.Transformation());
          gp_Pnt Pl  = C->Value(l).Transformed(L1.Transformation());
          double tol = BRep_Tool::Tolerance(V);
          if (Pf.Distance(Pl) < tol)
          {
            if (Pf.Distance(BRep_Tool::Pnt(V)) < tol)
            {
              if (V.Orientation() == TopAbs_FORWARD)
                res = f;
              else
                res = l;
            }
          }
        }
        return res;
      }
      itpr.Next();
    }
  }

  throw Standard_NoSuchObject("BRep_Tool:: no parameter on edge");
}

gp_Pnt2d BRep_Tool::Parameters(const TopoDS_Vertex& V, const TopoDS_Face& F)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(F, L);
  L                                  = L.Predivided(V.Location());
  const BRep_TVertex* TV             = static_cast<const BRep_TVertex*>(V.TShape().get());
  NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr(TV->Points());

  while (itpr.More())
  {
    if (itpr.Value()->IsPointOnSurface(S, L))
    {
      return gp_Pnt2d(itpr.Value()->Parameter(), itpr.Value()->Parameter2());
    }
    itpr.Next();
  }

  TopoDS_Vertex Vf, Vl;
  TopoDS_Edge   E;

  TopExp_Explorer exp;
  for (exp.Init(F, TopAbs_EDGE); exp.More(); exp.Next())
  {
    E = TopoDS::Edge(exp.Current());
    TopExp::Vertices(E, Vf, Vl);
    if ((V.IsSame(Vf)) || (V.IsSame(Vl)))
    {
      gp_Pnt2d Pf, Pl;
      UVPoints(E, F, Pf, Pl);
      if (V.IsSame(Vf))
        return Pf;
      else
        return Pl;
    }
  }
  throw Standard_NoSuchObject("BRep_Tool:: no parameters on surface");
}

bool BRep_Tool::IsClosed(const TopoDS_Shape& theShape)
{
  if (theShape.ShapeType() == TopAbs_SHELL)
  {
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMap(101, new NCollection_IncAllocator);
    TopExp_Explorer exp(theShape.Oriented(TopAbs_FORWARD), TopAbs_EDGE);
    bool            hasBound = false;
    for (; exp.More(); exp.Next())
    {
      const TopoDS_Edge& E = TopoDS::Edge(exp.Current());
      if (BRep_Tool::Degenerated(E) || E.Orientation() == TopAbs_INTERNAL
          || E.Orientation() == TopAbs_EXTERNAL)
        continue;
      hasBound = true;
      if (!aMap.Add(E))
        aMap.Remove(E);
    }
    return hasBound && aMap.IsEmpty();
  }
  else if (theShape.ShapeType() == TopAbs_WIRE)
  {
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMap(101, new NCollection_IncAllocator);
    TopExp_Explorer exp(theShape.Oriented(TopAbs_FORWARD), TopAbs_VERTEX);
    bool            hasBound = false;
    for (; exp.More(); exp.Next())
    {
      const TopoDS_Shape& V = exp.Current();
      if (V.Orientation() == TopAbs_INTERNAL || V.Orientation() == TopAbs_EXTERNAL)
        continue;
      hasBound = true;
      if (!aMap.Add(V))
        aMap.Remove(V);
    }
    return hasBound && aMap.IsEmpty();
  }
  else if (theShape.ShapeType() == TopAbs_EDGE)
  {
    TopoDS_Vertex aVFirst, aVLast;
    TopExp::Vertices(TopoDS::Edge(theShape), aVFirst, aVLast);
    return !aVFirst.IsNull() && aVFirst.IsSame(aVLast);
  }
  return theShape.Closed();
}

bool IsPlane(const occ::handle<Geom_Surface>& aS)
{
  bool                                        bRet;
  occ::handle<Geom_Plane>                     aGP;
  occ::handle<Geom_RectangularTrimmedSurface> aGRTS;
  occ::handle<Geom_OffsetSurface>             aGOFS;

  aGRTS = occ::down_cast<Geom_RectangularTrimmedSurface>(aS);
  aGOFS = occ::down_cast<Geom_OffsetSurface>(aS);

  if (!aGOFS.IsNull())
  {
    aGP = occ::down_cast<Geom_Plane>(aGOFS->BasisSurface());
  }
  else if (!aGRTS.IsNull())
  {
    aGP = occ::down_cast<Geom_Plane>(aGRTS->BasisSurface());
  }
  else
  {
    aGP = occ::down_cast<Geom_Plane>(aS);
  }

  bRet = !aGP.IsNull();

  return bRet;
}

double BRep_Tool::MaxTolerance(const TopoDS_Shape& theShape, const TopAbs_ShapeEnum theSubShape)
{
  double aTol = 0.0;

  TopExp_Explorer anExpSS(theShape, theSubShape);
  if (theSubShape == TopAbs_FACE)
  {
    for (; anExpSS.More(); anExpSS.Next())
    {
      const TopoDS_Shape& aCurrentSubShape = anExpSS.Current();
      aTol = std::max(aTol, Tolerance(TopoDS::Face(aCurrentSubShape)));
    }
  }
  else if (theSubShape == TopAbs_EDGE)
  {
    for (; anExpSS.More(); anExpSS.Next())
    {
      const TopoDS_Shape& aCurrentSubShape = anExpSS.Current();
      aTol = std::max(aTol, Tolerance(TopoDS::Edge(aCurrentSubShape)));
    }
  }
  else if (theSubShape == TopAbs_VERTEX)
  {
    for (; anExpSS.More(); anExpSS.Next())
    {
      const TopoDS_Shape& aCurrentSubShape = anExpSS.Current();
      aTol = std::max(aTol, Tolerance(TopoDS::Vertex(aCurrentSubShape)));
    }
  }

  return aTol;
}
