

#include <Adaptor3d_Curve.hpp>
#include <BRep_Builder.hpp>
#include <BRep_GCurve.hpp>
#include <BRepLib_ValidateEdge.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepExtrema_DistShapeShape.hpp>
#include <Extrema_LocateExtPC.hpp>
#include <GCPnts_AbscissaPoint.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeExtend.hpp>
#include <Standard_ErrorHandler.hpp>
#include <TopExp.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

ShapeAnalysis_Edge::ShapeAnalysis_Edge()
{
  myStatus = 0;
}

bool ShapeAnalysis_Edge::BoundUV(const TopoDS_Edge& edge,
                                 const TopoDS_Face& face,
                                 gp_Pnt2d&          first,
                                 gp_Pnt2d&          last) const
{
  TopLoc_Location                 L;
  const occ::handle<Geom_Surface> S = BRep_Tool::Surface(face, L);
  return BoundUV(edge, S, L, first, last);
}

bool ShapeAnalysis_Edge::BoundUV(const TopoDS_Edge&               edge,
                                 const occ::handle<Geom_Surface>& surface,
                                 const TopLoc_Location&           location,
                                 gp_Pnt2d&                        first,
                                 gp_Pnt2d&                        last) const
{
  occ::handle<Geom2d_Curve> c2d;
  double                    uf, ul;
  if (!PCurve(edge, surface, location, c2d, uf, ul))
    return false;
  first = c2d->Value(uf);
  last  = c2d->Value(ul);
  return true;
}

bool ShapeAnalysis_Edge::HasCurve3d(const TopoDS_Edge& edge) const
{
  double                  cf, cl;
  occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(edge, cf, cl);
  return !c3d.IsNull();
}

bool ShapeAnalysis_Edge::Curve3d(const TopoDS_Edge&       edge,
                                 occ::handle<Geom_Curve>& C3d,
                                 double&                  cf,
                                 double&                  cl,
                                 const bool               orient) const
{
  TopLoc_Location L;
  C3d = BRep_Tool::Curve(edge, L, cf, cl);
  if (!C3d.IsNull() && !L.IsIdentity())
  {
    C3d = occ::down_cast<Geom_Curve>(C3d->Transformed(L.Transformation()));
    cf  = C3d->TransformedParameter(cf, L.Transformation());
    cl  = C3d->TransformedParameter(cl, L.Transformation());
  }
  if (orient)
  {
    if (edge.Orientation() == TopAbs_REVERSED)
    {
      double tmp = cf;
      cf         = cl;
      cl         = tmp;
    }
  }
  return !C3d.IsNull();
}

bool ShapeAnalysis_Edge::IsClosed3d(const TopoDS_Edge& edge) const
{
  double                  cf, cl;
  occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(edge, cf, cl);
  if (c3d.IsNull())
    return false;
  if (!c3d->IsClosed())
    return false;
  return FirstVertex(edge).IsSame(LastVertex(edge));
}

bool ShapeAnalysis_Edge::HasPCurve(const TopoDS_Edge& edge, const TopoDS_Face& face) const
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(face, L);
  return HasPCurve(edge, S, L);
}

bool ShapeAnalysis_Edge::HasPCurve(const TopoDS_Edge&               edge,
                                   const occ::handle<Geom_Surface>& surface,
                                   const TopLoc_Location&           location) const
{

  double                    cf, cl;
  occ::handle<Geom2d_Curve> c2d = BRep_Tool::CurveOnSurface(edge, surface, location, cf, cl);
  return !c2d.IsNull();
}

bool ShapeAnalysis_Edge::PCurve(const TopoDS_Edge&         edge,
                                const TopoDS_Face&         face,
                                occ::handle<Geom2d_Curve>& C2d,
                                double&                    cf,
                                double&                    cl,
                                const bool                 orient) const
{

  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(face, L);
  return PCurve(edge, S, L, C2d, cf, cl, orient);
}

bool ShapeAnalysis_Edge::PCurve(const TopoDS_Edge&               edge,
                                const occ::handle<Geom_Surface>& surface,
                                const TopLoc_Location&           location,
                                occ::handle<Geom2d_Curve>&       C2d,
                                double&                          cf,
                                double&                          cl,
                                const bool                       orient) const
{
  C2d = BRep_Tool::CurveOnSurface(edge, surface, location, cf, cl);
  if (orient && edge.Orientation() == TopAbs_REVERSED)
  {
    double tmp = cf;
    cf         = cl;
    cl         = tmp;
  }
  return !C2d.IsNull();
}

bool ShapeAnalysis_Edge::IsSeam(const TopoDS_Edge& edge, const TopoDS_Face& face) const
{
  return BRep_Tool::IsClosed(edge, face);
}

bool ShapeAnalysis_Edge::IsSeam(const TopoDS_Edge&               edge,
                                const occ::handle<Geom_Surface>& surface,
                                const TopLoc_Location&           location) const
{
  return BRep_Tool::IsClosed(edge, surface, location);
}

TopoDS_Vertex ShapeAnalysis_Edge::FirstVertex(const TopoDS_Edge& edge) const
{
  TopoDS_Vertex V;
  if (edge.Orientation() == TopAbs_REVERSED)
  {
    V = TopExp::LastVertex(edge);
    V.Reverse();
  }
  else
  {
    V = TopExp::FirstVertex(edge);
  }
  return V;
}

TopoDS_Vertex ShapeAnalysis_Edge::LastVertex(const TopoDS_Edge& edge) const
{
  TopoDS_Vertex V;
  if (edge.Orientation() == TopAbs_REVERSED)
  {
    V = TopExp::FirstVertex(edge);
    V.Reverse();
  }
  else
  {
    V = TopExp::LastVertex(edge);
  }
  return V;
}

bool ShapeAnalysis_Edge::Status(const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus(myStatus, Status);
}

bool ShapeAnalysis_Edge::GetEndTangent2d(const TopoDS_Edge& edge,
                                         const TopoDS_Face& face,
                                         const bool         atend1,
                                         gp_Pnt2d&          pnt,
                                         gp_Vec2d&          v,
                                         const double       dparam) const
{
  TopLoc_Location                 L;
  const occ::handle<Geom_Surface> S = BRep_Tool::Surface(face, L);
  return GetEndTangent2d(edge, S, L, atend1, pnt, v, dparam);
}

bool ShapeAnalysis_Edge::GetEndTangent2d(const TopoDS_Edge&               edge,
                                         const occ::handle<Geom_Surface>& S,
                                         const TopLoc_Location&           L,
                                         const bool                       atend2,
                                         gp_Pnt2d&                        pnt,
                                         gp_Vec2d&                        v,
                                         const double                     dparam) const
{
  double                    cf, cl;
  occ::handle<Geom2d_Curve> c2d;
  if (!PCurve(edge, S, L, c2d, cf, cl))
  {
    v = gp_Vec2d(0, 0);
    return false;
  }
  double dpnew = dparam;

  if (dpnew > Precision::Confusion())
  {
    gp_Pnt2d ptmp;
    double   par1, par2, delta = (cl - cf) * dpnew;
    if (std::abs(delta) < Precision::PConfusion())
    {
      dpnew = 0.0;
    }
    else
    {
      if (atend2)
      {
        par1 = cl;
        par2 = cl - delta;
        c2d->D0(par1, pnt);
        c2d->D0(par2, ptmp);
        v = pnt.XY() - ptmp.XY();
      }
      else
      {
        par1 = cf;
        par2 = cf + delta;
        c2d->D0(par1, pnt);
        c2d->D0(par2, ptmp);
        v = ptmp.XY() - pnt.XY();
      }
      if (v.SquareMagnitude() < Precision::PConfusion() * Precision::PConfusion())
      {
        dpnew = 0.0;
      }
    }
  }

  if (dpnew <= Precision::Confusion())
  {

    double par = (atend2 ? cl : cf);
    c2d->D1(par, pnt, v);
    if (v.SquareMagnitude() < Precision::PConfusion() * Precision::PConfusion())
    {
      gp_Vec2d d1;
      c2d->D2(par, pnt, d1, v);
      if (v.SquareMagnitude() < Precision::PConfusion() * Precision::PConfusion())
      {
        gp_Vec2d d2;
        c2d->D3(par, pnt, d1, d2, v);
        if (v.SquareMagnitude() < Precision::PConfusion() * Precision::PConfusion())
        {
          gp_Pnt2d p2;
          c2d->D0((atend2 ? cf : cl), p2);
          v = p2.XY() - pnt.XY();
          if (v.SquareMagnitude() < Precision::PConfusion() * Precision::PConfusion())
            return false;
        }
      }
    }
    if (edge.Orientation() == TopAbs_REVERSED)
      v.Reverse();
  }

  return true;
}

bool ShapeAnalysis_Edge::CheckCurve3dWithPCurve(const TopoDS_Edge& edge, const TopoDS_Face& face)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(face, L);
  return CheckCurve3dWithPCurve(edge, S, L);
}

bool ShapeAnalysis_Edge::CheckCurve3dWithPCurve(const TopoDS_Edge&               edge,
                                                const occ::handle<Geom_Surface>& surface,
                                                const TopLoc_Location&           location)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);

  if (surface->IsKind(STANDARD_TYPE(Geom_Plane)))
    return false;

  occ::handle<Geom2d_Curve> c2d;
  double                    f2d, l2d;
  if (!PCurve(edge, surface, location, c2d, f2d, l2d, false))
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
    return false;
  }

  occ::handle<Geom_Curve> c3d;
  double                  f3d, l3d;
  if (!Curve3d(edge, c3d, f3d, l3d, false))
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);
    return false;
  }

  TopoDS_Vertex aFirstVert = FirstVertex(edge);
  TopoDS_Vertex aLastVert  = LastVertex(edge);

  if (aFirstVert.IsNull() || aLastVert.IsNull())
    return false;

  double preci1 = BRep_Tool::Tolerance(aFirstVert), preci2 = BRep_Tool::Tolerance(aLastVert);

  gp_Pnt2d p2d1 = c2d->Value(f2d), p2d2 = c2d->Value(l2d);

  return CheckPoints(c3d->Value(f3d),
                     c3d->Value(l3d),
                     surface->Value(p2d1.X(), p2d1.Y()).Transformed(location.Transformation()),
                     surface->Value(p2d2.X(), p2d2.Y()).Transformed(location.Transformation()),
                     preci1,
                     preci2);
}

bool ShapeAnalysis_Edge::CheckPoints(const gp_Pnt& P1A,
                                     const gp_Pnt& P1B,
                                     const gp_Pnt& P2A,
                                     const gp_Pnt& P2B,
                                     const double  preci1,
                                     const double  preci2)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  if (P1A.SquareDistance(P2A) <= preci1 * preci1 && P1B.SquareDistance(P2B) <= preci2 * preci2)
    return false;
  else if (P1A.Distance(P2B) + (P1B.Distance(P2A)) < P1A.Distance(P2A) + (P1B.Distance(P2B)))
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  return true;
}

bool ShapeAnalysis_Edge::CheckVerticesWithCurve3d(const TopoDS_Edge& edge,
                                                  const double       preci,
                                                  const int          vtx)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);

  TopoDS_Vertex V1  = FirstVertex(edge);
  TopoDS_Vertex V2  = LastVertex(edge);
  gp_Pnt        p1v = BRep_Tool::Pnt(V1);
  gp_Pnt        p2v = BRep_Tool::Pnt(V2);

  double                  cf, cl;
  occ::handle<Geom_Curve> c3d;
  if (!Curve3d(edge, c3d, cf, cl))
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
    return false;
  }

  if (vtx != 2)
  {

    gp_Pnt p13d = c3d->Value(cf);

    if (p1v.Distance(p13d) > (preci < 0 ? BRep_Tool::Tolerance(V1) : preci))
      myStatus |= ShapeExtend_DONE1;
  }

  if (vtx != 1)
  {

    gp_Pnt p23d = c3d->Value(cl);

    if (p2v.Distance(p23d) > (preci < 0 ? BRep_Tool::Tolerance(V2) : preci))
      myStatus |= ShapeExtend_DONE2;
  }

  return Status(ShapeExtend_DONE);
}

bool ShapeAnalysis_Edge::CheckVerticesWithPCurve(const TopoDS_Edge& edge,
                                                 const TopoDS_Face& face,
                                                 const double       preci,
                                                 const int          vtx)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(face, L);

  return CheckVerticesWithPCurve(edge, S, L, preci, vtx);
}

bool ShapeAnalysis_Edge::CheckVerticesWithPCurve(const TopoDS_Edge&               edge,
                                                 const occ::handle<Geom_Surface>& surf,
                                                 const TopLoc_Location&           loc,
                                                 const double                     preci,
                                                 const int                        vtx)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);

  TopoDS_Vertex V1  = FirstVertex(edge);
  TopoDS_Vertex V2  = LastVertex(edge);
  gp_Pnt        p1v = BRep_Tool::Pnt(V1);
  gp_Pnt        p2v = BRep_Tool::Pnt(V2);

  double                    cf, cl;
  occ::handle<Geom2d_Curve> c2d;
  if (!PCurve(edge, surf, loc, c2d, cf, cl))
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
    return false;
  }

  if (vtx != 2)
  {
    gp_Pnt2d p1uv = c2d->Value(cf);
    gp_Pnt   p12d = surf->Value(p1uv.X(), p1uv.Y());
    if (!loc.IsIdentity())
      p12d.Transform(loc.Transformation());

    if (p1v.Distance(p12d) > (preci < 0 ? BRep_Tool::Tolerance(V1) : preci))
      myStatus |= ShapeExtend_DONE1;
  }

  if (vtx != 1)
  {
    gp_Pnt2d p2uv = c2d->Value(cl);
    gp_Pnt   p22d = surf->Value(p2uv.X(), p2uv.Y());
    if (!loc.IsIdentity())
      p22d.Transform(loc.Transformation());

    if (p2v.Distance(p22d) > (preci < 0 ? BRep_Tool::Tolerance(V2) : preci))
      myStatus |= ShapeExtend_DONE2;
  }

  return Status(ShapeExtend_DONE);
}

static int CheckVertexTolerance(const TopoDS_Edge& edge,
                                const TopoDS_Face& face,
                                const bool         checkAll,
                                double&            toler1,
                                double&            toler2)
{
  int Status = ShapeExtend::EncodeStatus(ShapeExtend_OK);

  ShapeAnalysis_Edge sae;
  TopoDS_Vertex      V1 = sae.FirstVertex(edge);
  TopoDS_Vertex      V2 = sae.LastVertex(edge);
  if (V1.IsNull() || V2.IsNull())
  {
    Status |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
    return Status;
  }

  double old1 = BRep_Tool::Tolerance(V1);
  double old2 = BRep_Tool::Tolerance(V2);
  gp_Pnt pnt1 = BRep_Tool::Pnt(V1);
  gp_Pnt pnt2 = BRep_Tool::Pnt(V2);

  double                  a, b;
  occ::handle<Geom_Curve> c3d;
  if (!sae.Curve3d(edge, c3d, a, b, true))
  {
    if (!BRep_Tool::Degenerated(edge))
      Status |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);
    toler1 = toler2 = 0.;
  }
  else
  {
    toler1 = pnt1.SquareDistance(c3d->Value(a));
    toler2 = pnt2.SquareDistance(c3d->Value(b));
  }

  if (checkAll)
  {
    occ::handle<BRep_TEdge>& TE = *((occ::handle<BRep_TEdge>*)&edge.TShape());
    for (NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());
         itcr.More();
         itcr.Next())
    {
      occ::handle<BRep_GCurve> GC = occ::down_cast<BRep_GCurve>(itcr.Value());
      if (GC.IsNull() || !GC->IsCurveOnSurface())
        continue;
      occ::handle<Geom2d_Curve> pcurve;
      occ::handle<Geom_Surface> S = GC->Surface();
      TopLoc_Location           L = edge.Location() * GC->Location();
      sae.PCurve(edge, S, L, pcurve, a, b, true);
      gp_Pnt2d p1 = pcurve->Value(a);
      gp_Pnt2d p2 = pcurve->Value(b);
      gp_Pnt   P1 = S->Value(p1.X(), p1.Y()).Transformed(L.Transformation());
      gp_Pnt   P2 = S->Value(p2.X(), p2.Y()).Transformed(L.Transformation());
      toler1      = std::max(toler1, pnt1.SquareDistance(P1));
      toler2      = std::max(toler2, pnt2.SquareDistance(P2));
    }
  }

  else if (!face.IsNull())
  {
    occ::handle<Geom2d_Curve>        pcurve;
    TopLoc_Location                  L;
    const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(face, L);
    if (sae.PCurve(edge, S, L, pcurve, a, b, true))
    {
      gp_Pnt2d p1 = pcurve->Value(a);
      gp_Pnt2d p2 = pcurve->Value(b);
      gp_Pnt   P1 = S->Value(p1.X(), p1.Y()).Transformed(L.Transformation());
      gp_Pnt   P2 = S->Value(p2.X(), p2.Y()).Transformed(L.Transformation());
      toler1      = std::max(toler1, pnt1.SquareDistance(P1));
      toler2      = std::max(toler2, pnt2.SquareDistance(P2));
    }
    else
      Status |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL3);
  }

  double tole = BRep_Tool::Tolerance(edge);
  toler1      = std::max(1.0000001 * std::sqrt(toler1), tole);
  toler2      = std::max(1.0000001 * std::sqrt(toler2), tole);
  if (toler1 > old1)
    Status |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  if (toler2 > old2)
    Status |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);

  return Status;
}

bool ShapeAnalysis_Edge::CheckVertexTolerance(const TopoDS_Edge& edge,
                                              const TopoDS_Face& face,
                                              double&            toler1,
                                              double&            toler2)
{
  myStatus = ::CheckVertexTolerance(edge, face, false, toler1, toler2);
  return Status(ShapeExtend_DONE);
}

bool ShapeAnalysis_Edge::CheckVertexTolerance(const TopoDS_Edge& edge,
                                              double&            toler1,
                                              double&            toler2)
{
  TopoDS_Face F;
  myStatus = ::CheckVertexTolerance(edge, F, true, toler1, toler2);
  return Status(ShapeExtend_DONE);
}

bool ShapeAnalysis_Edge::CheckSameParameter(const TopoDS_Edge& edge,
                                            double&            maxdev,
                                            const int          NbControl)
{
  TopoDS_Face anEmptyFace;
  return CheckSameParameter(edge, anEmptyFace, maxdev, NbControl);
}

bool ShapeAnalysis_Edge::CheckSameParameter(const TopoDS_Edge& edge,
                                            const TopoDS_Face& face,
                                            double&            maxdev,
                                            const int          NbControl)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  if (BRep_Tool::Degenerated(edge))
    return false;

  maxdev = 0;

  occ::handle<BRep_TEdge>& TE            = *((occ::handle<BRep_TEdge>*)&edge.TShape());
  bool                     SameParameter = TE->SameParameter();

  double                  aFirst, aLast;
  TopLoc_Location         aCurveLoc;
  occ::handle<Geom_Curve> aC3D = BRep_Tool::Curve(edge, aCurveLoc, aFirst, aLast);
  if (aC3D.IsNull())
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
    return false;
  }

  if (!aCurveLoc.IsIdentity())
  {
    const gp_Trsf& aTrsf = aCurveLoc.Transformation();
    aC3D                 = occ::down_cast<Geom_Curve>(aC3D->Transformed(aTrsf));
    aFirst               = aC3D->TransformedParameter(aFirst, aTrsf);
    aLast                = aC3D->TransformedParameter(aLast, aTrsf);
  }

  occ::handle<GeomAdaptor_Curve> aGAC = new GeomAdaptor_Curve(aC3D, aFirst, aLast);

  occ::handle<Geom_Surface> aFaceSurf;
  TopLoc_Location           aFaceLoc;
  if (!face.IsNull())
    aFaceSurf = BRep_Tool::Surface(face, aFaceLoc);

  bool IsPCurveFound = false;
  int  i             = 1;

  for (;;)
  {
    occ::handle<Geom2d_Curve> aPC;
    occ::handle<Geom_Surface> aS;
    TopLoc_Location           aLoc;
    double                    f, l;

    BRep_Tool::CurveOnSurface(edge, aPC, aS, aLoc, f, l, i);

    if (aPC.IsNull())

      break;

    ++i;

    if (!aFaceSurf.IsNull())
    {
      if (aFaceSurf != aS || aFaceLoc != aLoc)
      {
        continue;
      }
    }

    IsPCurveFound = true;

    occ::handle<Geom_Surface> aST =
      occ::down_cast<Geom_Surface>(aS->Transformed(aLoc.Transformation()));

    occ::handle<Geom2dAdaptor_Curve> GHPC = new Geom2dAdaptor_Curve(aPC, f, l);
    occ::handle<GeomAdaptor_Surface> GAHS = new GeomAdaptor_Surface(aST);

    occ::handle<Adaptor3d_CurveOnSurface> ACS = new Adaptor3d_CurveOnSurface(GHPC, GAHS);

    BRepLib_ValidateEdge aValidateEdge(aGAC, ACS, SameParameter);
    aValidateEdge.SetControlPointsNumber(NbControl - 1);
    aValidateEdge.Process();
    aValidateEdge.UpdateTolerance(maxdev);
    if (!aValidateEdge.IsDone())
    {
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);
    }
  }

  if (!IsPCurveFound && !aFaceSurf.IsNull())
  {
    double                    f, l;
    occ::handle<Geom2d_Curve> aPC = BRep_Tool::CurveOnPlane(edge, aFaceSurf, aFaceLoc, f, l);
    if (!aPC.IsNull())
    {
      occ::handle<Geom2dAdaptor_Curve> GHPC = new Geom2dAdaptor_Curve(aPC, aFirst, aLast);

      occ::handle<Geom_Surface> aST =
        occ::down_cast<Geom_Surface>(aFaceSurf->Transformed(aFaceLoc.Transformation()));
      occ::handle<GeomAdaptor_Surface> GAHS = new GeomAdaptor_Surface(aST);

      occ::handle<Adaptor3d_CurveOnSurface> ACS = new Adaptor3d_CurveOnSurface(GHPC, GAHS);

      BRepLib_ValidateEdge aValidateEdgeOnPlane(aGAC, ACS, SameParameter);
      aValidateEdgeOnPlane.SetControlPointsNumber(NbControl - 1);
      aValidateEdgeOnPlane.Process();
      aValidateEdgeOnPlane.UpdateTolerance(maxdev);
      if (!aValidateEdgeOnPlane.IsDone())
      {
        myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);
      }
    }
  }

  if (maxdev > TE->Tolerance())
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  if (!SameParameter)
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);

  return Status(ShapeExtend_DONE);
}

static bool IsOverlapPartEdges(const TopoDS_Edge& theFirstEdge,
                               const TopoDS_Edge& theSecEdge,
                               const double&      theTolerance,
                               const double&      theStep,
                               const double&      theStartLength,
                               const double&      theEndLength)
{
  NCollection_Sequence<int> aSeqIntervals;
  BRepAdaptor_Curve         aAdCurve1(theFirstEdge);

  BRepExtrema_DistShapeShape aMinDist;
  aMinDist.LoadS1(theSecEdge);

  for (double aS = theStartLength; aS <= theEndLength; aS += theStep / 2)
  {

    gp_Pnt aPoint;
    if (aS <= Precision::Confusion())
    {
      TopoDS_Vertex V1 = TopExp::FirstVertex(theFirstEdge, true);
      aPoint           = BRep_Tool::Pnt(V1);
    }
    else
    {
      GCPnts_AbscissaPoint aAbsPoint(Precision::Confusion(),
                                     aAdCurve1,
                                     aS,
                                     aAdCurve1.FirstParameter());
      if (aAbsPoint.IsDone())
        aAdCurve1.D0(aAbsPoint.Parameter(), aPoint);
      else
        continue;
    }
    BRep_Builder  aB;
    TopoDS_Vertex aV;
    aB.MakeVertex(aV, aPoint, Precision::Confusion());
    aMinDist.LoadS2(aV);
    aMinDist.Perform();
    if (aMinDist.IsDone() && aMinDist.Value() >= theTolerance)
      return false;
  }
  return true;
}

bool ShapeAnalysis_Edge::CheckOverlapping(const TopoDS_Edge& theEdge1,
                                          const TopoDS_Edge& theEdge2,
                                          double&            theTolOverlap,
                                          const double       theDomainDist)
{
  bool              isOverlap = false;
  BRepAdaptor_Curve aAdCurve1(theEdge1);
  double            aLength1 = GCPnts_AbscissaPoint::Length(aAdCurve1);
  BRepAdaptor_Curve aAdCurve2(theEdge2);
  double            aLength2   = GCPnts_AbscissaPoint::Length(aAdCurve2);
  TopoDS_Edge       aFirstEdge = (aLength1 >= aLength2 ? theEdge2 : theEdge1);
  TopoDS_Edge       aSecEdge   = (aLength1 >= aLength2 ? theEdge1 : theEdge2);
  double            aLength    = std::min(aLength1, aLength2);

  double aStep = std::min(aLength1, aLength2) / 2;
  isOverlap    = IsOverlapPartEdges(aFirstEdge,
                                 aSecEdge,
                                 theTolOverlap,
                                 aStep,
                                 0.,
                                 std::min(aLength1, aLength2));

  if (isOverlap)
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
    return isOverlap;
  }
  if (theDomainDist == 0.0)
    return isOverlap;

  double aDomainTol =
    (theDomainDist > std::min(aLength1, aLength2) ? std::min(aLength1, aLength2) : theDomainDist);
  BRepExtrema_DistShapeShape aMinDist(aFirstEdge, aSecEdge, theTolOverlap);
  double                     aresTol = theTolOverlap;
  if (aMinDist.IsDone())
  {
    aresTol = aMinDist.Value();
    if (aresTol >= theTolOverlap)
      return false;
    int NbSol = aMinDist.NbSolution();
    for (int i = 1; i <= NbSol && !isOverlap; i++)
    {
      BRepExtrema_SupportType aType1 = aMinDist.SupportTypeShape1(i);
      double                  aEndLength, aStartLength, aLengthP;
      if (aType1 == BRepExtrema_IsVertex)
      {
        TopoDS_Shape  aSupportShape1 = aMinDist.SupportOnShape1(i);
        TopoDS_Vertex aV1, aV2;
        TopExp::Vertices(aFirstEdge, aV1, aV2, true);
        if (aV1.IsSame(aSupportShape1))
          aLengthP = 0.0;
        else
          aLengthP = aLength;
      }
      else if (aType1 == BRepExtrema_IsOnEdge)
      {
        double aParam1, aFirst, aLast;
        aMinDist.ParOnEdgeS1(i, aParam1);
        BRep_Tool::Range(aFirstEdge, aFirst, aLast);
        BRepAdaptor_Curve anAdaptor(aFirstEdge);
        aLengthP = GCPnts_AbscissaPoint::Length(anAdaptor, aFirst, aParam1);
      }
      else
        continue;
      aStartLength = aLengthP - aDomainTol / 2;
      if (aStartLength < 0.0)
      {
        aStartLength = 0;
        aEndLength   = aDomainTol;
      }
      aEndLength = aLengthP + aDomainTol / 2;
      if (aEndLength > aLength)
      {
        aEndLength   = aLength;
        aStartLength = aEndLength - aDomainTol;
      }
      aStep = (aEndLength - aStartLength) / 5;
      isOverlap =
        (IsOverlapPartEdges(aFirstEdge, aSecEdge, theTolOverlap, aStep, aStartLength, aEndLength));
    }
  }
  if (isOverlap)
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE4);

  theTolOverlap = aresTol;
  return isOverlap;
}

bool ShapeAnalysis_Edge::CheckPCurveRange(const double                     theFirst,
                                          const double                     theLast,
                                          const occ::handle<Geom2d_Curve>& thePC)
{
  constexpr double eps        = Precision::PConfusion();
  bool             isValid    = true;
  bool             IsPeriodic = thePC->IsPeriodic();
  double           aPeriod    = RealLast();
  if (IsPeriodic)
  {
    aPeriod = thePC->Period();
  }
  double fp = thePC->FirstParameter(), lp = thePC->LastParameter();
  if (thePC->DynamicType() == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    const occ::handle<Geom2d_Curve>& aC = occ::down_cast<Geom2d_TrimmedCurve>(thePC)->BasisCurve();
    fp                                  = aC->FirstParameter();
    lp                                  = aC->LastParameter();
    IsPeriodic                          = aC->IsPeriodic();
    if (IsPeriodic)
    {
      aPeriod = aC->Period();
    }
  }
  if (IsPeriodic && (theLast - theFirst > aPeriod + eps))
  {
    isValid = false;
  }
  else if (!IsPeriodic && (theFirst < fp - eps || theLast > lp + eps))
  {
    isValid = false;
  }

  return isValid;
}
