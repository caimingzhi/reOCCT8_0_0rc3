

#include <ChFi2d_AnaFilletAlgo.hpp>

#include <gp_Ax3.hpp>

#include <Standard_TypeMismatch.hpp>

#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>

#include <GeomAPI_ExtremaCurveCurve.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <ShapeAnalysis_Wire.hpp>
#include <Geom_Circle.hpp>

#include <BRepAdaptor_Curve.hpp>
#include <BRep_Tool.hpp>

#include <TopoDS.hpp>
#include <TopoDS_Iterator.hpp>

#include <ProjLib.hpp>
#include <TopExp.hpp>
#include <ElSLib.hpp>

static bool isCW(const BRepAdaptor_Curve& AC)
{
  const double             f      = AC.FirstParameter();
  const double             l      = AC.LastParameter();
  occ::handle<Geom_Circle> circle = occ::down_cast<Geom_Circle>(AC.Curve().Curve());
  gp_Pnt                   start  = AC.Value(f);
  gp_Pnt                   end    = AC.Value(l);
  gp_Pnt                   center = AC.Circle().Location();
  gp_Ax3                   plane  = AC.Circle().Position();

  gp_Pnt m;
  circle->D0(0.5 * (f + l), m);

  gp_Vec startv(center, start), endv(center, end), middlev(center, m);
  double middlea = startv.AngleWithRef(middlev, plane.Direction());
  while (middlea < 0.0)
    middlea += 2.0 * M_PI;
  double enda = startv.AngleWithRef(endv, plane.Direction());
  while (enda < 0.0)
    enda += 2.0 * M_PI;

  bool is_cw = middlea > enda;
  return is_cw;
}

static bool IsEqual(const gp_Pnt& p1, const gp_Pnt& p2)
{
  return p1.SquareDistance(p2) < Precision::SquareConfusion();
}

static bool IsEqual(const gp_Pnt2d& p1, const gp_Pnt2d& p2)
{
  return p1.SquareDistance(p2) < Precision::SquareConfusion();
}

ChFi2d_AnaFilletAlgo::ChFi2d_AnaFilletAlgo()
    : segment1(false),
      x11(0.0),
      y11(0.0),
      x12(0.0),
      y12(0.0),
      xc1(0.0),
      yc1(0.0),
      radius1(0.0),
      cw1(false),
      segment2(false),
      x21(0.0),
      y21(0.0),
      x22(0.0),
      y22(0.0),
      xc2(0.0),
      yc2(0.0),
      radius2(0.0),
      cw2(false)
{
}

ChFi2d_AnaFilletAlgo::ChFi2d_AnaFilletAlgo(const TopoDS_Wire& theWire, const gp_Pln& thePlane)
    : plane(thePlane),
      segment1(false),
      x11(0.0),
      y11(0.0),
      x12(0.0),
      y12(0.0),
      xc1(0.0),
      yc1(0.0),
      radius1(0.0),
      cw1(false),
      segment2(false),
      x21(0.0),
      y21(0.0),
      x22(0.0),
      y22(0.0),
      xc2(0.0),
      yc2(0.0),
      radius2(0.0),
      cw2(false)
{
  Init(theWire, thePlane);
}

ChFi2d_AnaFilletAlgo::ChFi2d_AnaFilletAlgo(const TopoDS_Edge& theEdge1,
                                           const TopoDS_Edge& theEdge2,
                                           const gp_Pln&      thePlane)
    : plane(thePlane),
      segment1(false),
      x11(0.0),
      y11(0.0),
      x12(0.0),
      y12(0.0),
      xc1(0.0),
      yc1(0.0),
      radius1(0.0),
      cw1(false),
      segment2(false),
      x21(0.0),
      y21(0.0),
      x22(0.0),
      y22(0.0),
      xc2(0.0),
      yc2(0.0),
      radius2(0.0),
      cw2(false)
{

  Init(theEdge1, theEdge2, thePlane);
}

void ChFi2d_AnaFilletAlgo::Init(const TopoDS_Wire& theWire, const gp_Pln& thePlane)
{
  plane = thePlane;
  TopoDS_Iterator itr(theWire);
  for (; itr.More(); itr.Next())
  {
    if (e1.IsNull())
      e1 = TopoDS::Edge(itr.Value());
    else if (e2.IsNull())
      e2 = TopoDS::Edge(itr.Value());
  }
  if (e1.IsNull() || e2.IsNull())
    throw Standard_TypeMismatch(
      "The algorithm expects a wire consisting of two linear or circular edges.");

  BRepAdaptor_Curve AC1(e1);
  if (AC1.GetType() != GeomAbs_Line && AC1.GetType() != GeomAbs_Circle)
    throw Standard_TypeMismatch("A segment or an arc of circle is expected.");

  TopoDS_Vertex v1, v2;
  TopExp::Vertices(e1, v1, v2, true);
  if (v1.IsNull() || v2.IsNull())
    throw Standard_Failure("An infinite edge.");

  gp_Pnt   P1 = BRep_Tool::Pnt(v1);
  gp_Pnt   P2 = BRep_Tool::Pnt(v2);
  gp_Pnt2d p1 = ProjLib::Project(thePlane, P1);
  gp_Pnt2d p2 = ProjLib::Project(thePlane, P2);
  p1.Coord(x11, y11);
  p2.Coord(x12, y12);

  segment1 = true;
  if (AC1.GetType() == GeomAbs_Circle)
  {
    segment1  = false;
    gp_Circ c = AC1.Circle();

    gp_Pnt2d loc = ProjLib::Project(thePlane, c.Location());
    loc.Coord(xc1, yc1);

    radius1 = c.Radius();
    cw1     = isCW(AC1);
  }

  BRepAdaptor_Curve AC2(e2);
  if (AC2.GetType() != GeomAbs_Line && AC2.GetType() != GeomAbs_Circle)
    throw Standard_TypeMismatch("A segment or an arc of circle is expected.");

  TopExp::Vertices(e2, v1, v2, true);
  if (v1.IsNull() || v2.IsNull())
    throw Standard_Failure("An infinite edge.");

  P1 = BRep_Tool::Pnt(v1);
  P2 = BRep_Tool::Pnt(v2);
  p1 = ProjLib::Project(thePlane, P1);
  p2 = ProjLib::Project(thePlane, P2);
  p1.Coord(x21, y21);
  p2.Coord(x22, y22);

  segment2 = true;
  if (AC2.GetType() == GeomAbs_Circle)
  {
    segment2  = false;
    gp_Circ c = AC2.Circle();

    gp_Pnt2d loc = ProjLib::Project(thePlane, c.Location());
    loc.Coord(xc2, yc2);

    radius2 = c.Radius();
    cw2     = isCW(AC2);
  }
}

void ChFi2d_AnaFilletAlgo::Init(const TopoDS_Edge& theEdge1,
                                const TopoDS_Edge& theEdge2,
                                const gp_Pln&      thePlane)
{

  TopoDS_Vertex v11, v12, v21, v22;
  TopExp::Vertices(theEdge1, v11, v12, true);
  TopExp::Vertices(theEdge2, v21, v22, true);
  if (v11.IsNull() || v12.IsNull() || v21.IsNull() || v22.IsNull())
    throw Standard_Failure("An infinite edge.");

  gp_Pnt p11 = BRep_Tool::Pnt(v11);
  gp_Pnt p12 = BRep_Tool::Pnt(v12);
  gp_Pnt p21 = BRep_Tool::Pnt(v21);
  gp_Pnt p22 = BRep_Tool::Pnt(v22);

  gp_Pnt pcommon;
  if (IsEqual(p11, p21) || IsEqual(p11, p22))
  {
    pcommon = p11;
  }
  else if (IsEqual(p12, p21) || IsEqual(p12, p22))
  {
    pcommon = p12;
  }
  else
    throw Standard_Failure("The edges have no common point.");

  bool is1stReversed(false), is2ndReversed(false);
  if (IsEqual(pcommon, p11))
    is1stReversed = true;
  else if (IsEqual(pcommon, p22))
    is2ndReversed = true;

  BRepBuilderAPI_MakeWire mkWire;
  if (is1stReversed)
    mkWire.Add(TopoDS::Edge(theEdge1.Reversed()));
  else
    mkWire.Add(theEdge1);
  if (is2ndReversed)
    mkWire.Add(TopoDS::Edge(theEdge2.Reversed()));
  else
    mkWire.Add(theEdge2);
  if (!mkWire.IsDone())
    throw Standard_Failure("Can't make a wire.");

  const TopoDS_Wire& W = mkWire.Wire();
  Init(W, thePlane);
}

bool ChFi2d_AnaFilletAlgo::Perform(const double radius)
{
  bool bRet(false);
  if (e1.IsNull() || e2.IsNull() || radius < Precision::Confusion())
  {
    return bRet;
  }

  double xc = 0.0, yc = 0.0;
  double start = 0.0, end = 0.0;
  double xstart = DBL_MAX, ystart = DBL_MAX;
  double xend = DBL_MAX, yend = DBL_MAX;
  bool   cw = false;

  bool isCut(false);
  if (!segment1 || !segment2)
  {
    BRepBuilderAPI_MakeWire mkWire(e1, e2);
    if (mkWire.IsDone())
    {
      const TopoDS_Wire&      W = mkWire.Wire();
      BRepBuilderAPI_MakeFace mkFace(plane);
      if (mkFace.IsDone())
      {
        const TopoDS_Face& F = mkFace.Face();
        ShapeAnalysis_Wire analyzer(W, F, Precision::Confusion());
        if (analyzer.CheckSelfIntersection())
        {

          isCut = true;
          if (!Cut(plane, e1, e2))
          {
            return false;
          }
        }
      }
    }
  }

  BRepAdaptor_Curve AC1(e1), AC2(e2);
  if (segment1 && segment2)
  {
    bRet = SegmentFilletSegment(radius, xc, yc, cw, start, end);
  }
  else if (segment1 && !segment2)
  {
    bRet = SegmentFilletArc(radius, xc, yc, cw, start, end, xend, yend);
  }
  else if (!segment1 && segment2)
  {
    bRet = ArcFilletSegment(radius, xc, yc, cw, start, end, xstart, ystart);
  }
  else if (!segment1 && !segment2)
  {
    bRet = ArcFilletArc(radius, xc, yc, cw, start, end);
  }

  if (!bRet)
    return false;

  if (!plane.Position().Direct())
    cw = !cw;

  gp_Pnt        center = ElSLib::Value(xc, yc, plane);
  const gp_Dir& normal = plane.Position().Direction();
  gp_Circ       circ(gp_Ax2(center, cw ? -normal : normal), radius);

  const double delta1 = AC1.LastParameter() - AC1.FirstParameter();
  const double delta2 = AC2.LastParameter() - AC2.FirstParameter();
  if (!isCut && (start > delta1 || end > delta2))
  {

    const double little = 100.0 * Precision::Confusion();
    const double d1     = fabs(start - delta1);
    const double d2     = fabs(end - delta2);
    if (d1 < little || d2 < little)
    {
      if (segment1 && segment2)
      {
        bRet = SegmentFilletSegment(radius - little, xc, yc, cw, start, end);
      }
      else if (segment1 && !segment2)
      {
        bRet = SegmentFilletArc(radius - little, xc, yc, cw, start, end, xend, yend);
      }
      else if (!segment1 && segment2)
      {
        bRet = ArcFilletSegment(radius - little, xc, yc, cw, start, end, xstart, ystart);
      }
      else if (!segment1 && !segment2)
      {
        bRet = ArcFilletArc(radius - little, xc, yc, cw, start, end);
      }
      if (bRet)
      {

        if (!plane.Position().Direct())
          cw = !cw;

        center = ElSLib::Value(xc, yc, plane);
        circ.SetLocation(center);
        circ.SetRadius(radius - little);
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  if (bRet)
  {

    gp_Pnt pstart;
    if (xstart != DBL_MAX)
    {
      pstart = ElSLib::Value(xstart, ystart, plane);
    }
    else
    {
      if (e1.Orientation() == TopAbs_FORWARD)
        pstart = AC1.Value(AC1.LastParameter() - start);
      else
        pstart = AC1.Value(AC1.FirstParameter() + start);
    }

    gp_Pnt pend;
    if (xend != DBL_MAX)
    {
      pend = ElSLib::Value(xend, yend, plane);
    }
    else
    {
      if (e2.Orientation() == TopAbs_FORWARD)
        pend = AC2.Value(AC2.FirstParameter() + end);
      else
        pend = AC2.Value(AC2.LastParameter() - end);
    }

    BRepBuilderAPI_MakeEdge mkEdge(circ, pstart, pend);
    bRet = mkEdge.IsDone();
    if (bRet)
    {
      fillet = mkEdge.Edge();

      gp_Pnt p1, p2;
      shrinke1.Nullify();
      if (e1.Orientation() == TopAbs_FORWARD)
      {
        p1 = AC1.Value(AC1.FirstParameter());
        p2 = pstart;
      }
      else
      {
        p1 = pstart;
        p2 = AC1.Value(AC1.LastParameter());
      }
      if (segment1)
      {
        BRepBuilderAPI_MakeEdge mkSegment1;
        mkSegment1.Init(AC1.Curve().Curve(), p1, p2);
        if (mkSegment1.IsDone())
          shrinke1 = mkSegment1.Edge();
      }
      else
      {
        BRepBuilderAPI_MakeEdge mkCirc1;
        mkCirc1.Init(AC1.Curve().Curve(), p1, p2);
        if (mkCirc1.IsDone())
          shrinke1 = mkCirc1.Edge();
      }

      shrinke2.Nullify();
      if (e1.Orientation() == TopAbs_FORWARD)
      {
        p1 = pend;
        p2 = AC2.Value(AC2.LastParameter());
      }
      else
      {
        p1 = AC2.Value(AC2.FirstParameter());
        p2 = pend;
      }
      if (segment2)
      {
        BRepBuilderAPI_MakeEdge mkSegment2;
        mkSegment2.Init(AC2.Curve().Curve(), p1, p2);
        if (mkSegment2.IsDone())
          shrinke2 = mkSegment2.Edge();
      }
      else
      {
        BRepBuilderAPI_MakeEdge mkCirc2;
        mkCirc2.Init(AC2.Curve().Curve(), p1, p2);
        if (mkCirc2.IsDone())
          shrinke2 = mkCirc2.Edge();
      }

      bRet = !shrinke1.IsNull() && !shrinke2.IsNull();
    }
  }

  return bRet;
}

const TopoDS_Edge& ChFi2d_AnaFilletAlgo::Result(TopoDS_Edge& theE1, TopoDS_Edge& theE2)
{
  theE1 = shrinke1;
  theE2 = shrinke2;
  return fillet;
}

bool ChFi2d_AnaFilletAlgo::SegmentFilletSegment(const double radius,
                                                double&      xc,
                                                double&      yc,
                                                bool&        cw,
                                                double&      start,
                                                double&      end)
{

  gp_Pnt2d p11(x11, y11);
  gp_Pnt2d p12(x12, y12);
  gp_Pnt2d p22(x22, y22);

  if (IsEqual(p12, p11) || IsEqual(p12, p22))
  {
    return false;
  }

  gp_Vec2d v1(p12, p11);
  gp_Vec2d v2(p12, p22);
  v1.Normalize();
  v2.Normalize();

  gp_Vec2d bisec = 0.5 * (v1 + v2);

  if (bisec.SquareMagnitude() < Precision::SquareConfusion())
    return false;

  bisec.Normalize();

  double beta = v1.Angle(bisec);

  double L = radius / sin(fabs(beta));

  gp_Pnt2d pc = p12.Translated(L * bisec);
  pc.Coord(xc, yc);

  start = sqrt(L * L - radius * radius);
  end   = start;

  cw = beta > 0.0;
  return true;
}

bool ChFi2d_AnaFilletAlgo::SegmentFilletArc(const double radius,
                                            double&      xc,
                                            double&      yc,
                                            bool&        cw,
                                            double&      start,
                                            double&      end,
                                            double&      xend,
                                            double&      yend)
{

  gp_Pnt2d p12(x12, y12);
  gp_Pnt2d p11(x11, y11);
  gp_Pnt2d pc2(xc2, yc2);

  if (p11.SquareDistance(p12) < gp::Resolution())
    return false;

  gp_Vec2d v1(p12, p11);
  gp_Vec2d v2(p12, pc2);

  if (cw2)
    v2.Rotate(+M_PI_2);
  else
    v2.Rotate(-M_PI_2);

  double angle = v1.Angle(v2);
  if (fabs(angle) < Precision::Angular())
    return false;

  v2.Normalize();
  v1.Normalize();
  gp_Vec2d bisec = 0.5 * (v1 + v2);

  if (bisec.SquareMagnitude() < gp::Resolution())
    return false;

  bisec.Normalize();
  gp_Pnt2d nearp = p12.Translated(radius * bisec);
  gp_Lin2d nearl(p12, bisec);

  gp_Vec2d d1(v1);
  gp_Lin2d line(p11, -d1);
  d1.Rotate(M_PI_2);
  line.Translate(radius * d1);
  if (line.Distance(nearp) > radius)
    line.Translate(-2.0 * radius * d1);

  gp_Ax2d   axes(pc2, gp::DX2d());
  gp_Circ2d circ(axes, radius2 + radius);
  if (radius2 > radius && circ.Distance(nearp) > radius)
    circ.SetRadius(radius2 - radius);

  IntAna2d_AnaIntersection intersector(line, circ);
  if (!intersector.IsDone() || !intersector.NbPoints())
    return false;

  int    i;
  double minDist = DBL_MAX;
  for (i = 1; i <= intersector.NbPoints(); ++i)
  {
    const IntAna2d_IntPoint& intp = intersector.Point(i);
    const gp_Pnt2d&          p    = intp.Value();

    double d = nearl.Distance(p);
    if (d < minDist)
    {
      minDist = d;
      p.Coord(xc, yc);
    }
  }

  gp_Pnt2d     pc(xc, yc);
  double       L2  = pc.SquareDistance(p12);
  const double Rf2 = radius * radius;
  start            = sqrt(L2 - Rf2);

  gp_Vec2d pcc(pc2, pc);
  end = fabs(gp_Vec2d(pc2, p12).Angle(pcc));

  line.SetLocation(pc2);
  line.SetDirection(pcc);
  circ.SetLocation(pc2);
  circ.SetRadius(radius2);
  intersector.Perform(line, circ);
  if (!intersector.IsDone() || !intersector.NbPoints())
    return false;

  xend = DBL_MAX;
  yend = DBL_MAX;
  for (i = 1; i <= intersector.NbPoints(); ++i)
  {
    const IntAna2d_IntPoint& intp = intersector.Point(i);
    const gp_Pnt2d&          p    = intp.Value();

    const double d2 = p.SquareDistance(pc);
    if (fabs(d2 - Rf2) < Precision::Confusion())
    {
      p.Coord(xend, yend);
      break;
    }
  }

  angle = v1.Angle(v2);
  cw    = angle > 0.0;
  return true;
}

bool ChFi2d_AnaFilletAlgo::ArcFilletSegment(const double radius,
                                            double&      xc,
                                            double&      yc,
                                            bool&        cw,
                                            double&      start,
                                            double&      end,
                                            double&      xstart,
                                            double&      ystart)
{

  gp_Pnt2d p12(x12, y12);
  gp_Pnt2d p22(x22, y22);
  gp_Pnt2d pc1(xc1, yc1);

  if (p12.SquareDistance(p22) < gp::Resolution())
    return false;

  gp_Vec2d v1(p12, pc1);
  gp_Vec2d v2(p12, p22);

  if (cw1)
    v1.Rotate(-M_PI_2);
  else
    v1.Rotate(+M_PI_2);

  double angle = v1.Angle(v2);
  if (fabs(angle) < Precision::Angular())
    return false;

  v1.Normalize();
  v2.Normalize();
  gp_Vec2d bisec = 0.5 * (v1 + v2);

  if (bisec.SquareMagnitude() < gp::Resolution())
    return false;

  bisec.Normalize();
  gp_Pnt2d nearPoint = p12.Translated(radius * bisec);
  gp_Lin2d nearLine(p12, bisec);

  gp_Vec2d aD2Vec(v2);
  gp_Lin2d line(p22, -aD2Vec);
  aD2Vec.Rotate(M_PI_2);
  line.Translate(radius * aD2Vec);
  if (line.Distance(nearPoint) > radius)
    line.Translate(-2.0 * radius * aD2Vec);

  gp_Ax2d   axes(pc1, gp::DX2d());
  gp_Circ2d circ(axes, radius1 + radius);
  if (radius1 > radius && circ.Distance(nearPoint) > radius)
    circ.SetRadius(radius1 - radius);

  IntAna2d_AnaIntersection intersector(line, circ);
  if (!intersector.IsDone() || !intersector.NbPoints())
    return false;

  int    i;
  double minDist = DBL_MAX;
  for (i = 1; i <= intersector.NbPoints(); ++i)
  {
    const IntAna2d_IntPoint& intp = intersector.Point(i);
    const gp_Pnt2d&          p    = intp.Value();

    double d = nearLine.Distance(p);
    if (d < minDist)
    {
      minDist = d;
      p.Coord(xc, yc);
    }
  }

  gp_Pnt2d     pc(xc, yc);
  double       L2  = pc.SquareDistance(p12);
  const double Rf2 = radius * radius;
  end              = sqrt(L2 - Rf2);

  gp_Vec2d pcc(pc1, pc);
  start = fabs(gp_Vec2d(pc1, p12).Angle(pcc));

  line.SetLocation(pc1);
  line.SetDirection(pcc);
  circ.SetLocation(pc1);
  circ.SetRadius(radius1);
  intersector.Perform(line, circ);
  if (!intersector.IsDone() || !intersector.NbPoints())
    return false;

  xstart = DBL_MAX;
  ystart = DBL_MAX;
  for (i = 1; i <= intersector.NbPoints(); ++i)
  {
    const IntAna2d_IntPoint& intp = intersector.Point(i);
    const gp_Pnt2d&          p    = intp.Value();

    const double d2 = p.SquareDistance(pc);
    if (fabs(d2 - Rf2) < Precision::SquareConfusion())
    {
      p.Coord(xstart, ystart);
      break;
    }
  }

  angle = v2.Angle(v1);
  cw    = angle < 0.0;
  return true;
}

bool ChFi2d_AnaFilletAlgo::ArcFilletArc(const double radius,
                                        double&      xc,
                                        double&      yc,
                                        bool&        cw,
                                        double&      start,
                                        double&      end)
{

  const gp_Pnt2d pc1(xc1, yc1);
  const gp_Pnt2d pc2(xc2, yc2);
  const gp_Pnt2d p12(x12, y12);

  gp_Vec2d v1(pc1, p12);
  gp_Vec2d v2(pc2, p12);

  if (cw1)
    v1.Rotate(+M_PI_2);
  else
    v1.Rotate(-M_PI_2);
  if (cw2)
    v2.Rotate(-M_PI_2);
  else
    v2.Rotate(+M_PI_2);

  v1.Normalize();
  v2.Normalize();
  gp_Vec2d bisec = 0.5 * (v1 + v2);
  if (bisec.SquareMagnitude() < gp::Resolution())
    return false;

  const gp_Pnt2d checkp = p12.Translated(radius * bisec);
  const gp_Lin2d checkl(p12, bisec);

  gp_Ax2d   axes(pc1, gp::DX2d());
  gp_Circ2d c1(axes, radius1 + radius);
  if (radius1 > radius && c1.Distance(checkp) > radius)
    c1.SetRadius(radius1 - radius);

  axes.SetLocation(pc2);
  gp_Circ2d c2(axes, radius2 + radius);
  if (radius2 > radius && c2.Distance(checkp) > radius)
    c2.SetRadius(radius2 - radius);

  IntAna2d_AnaIntersection intersector(c1, c2);
  if (!intersector.IsDone() || !intersector.NbPoints())
    return false;

  gp_Pnt2d pc;
  double   minDist = DBL_MAX;
  for (int i = 1; i <= intersector.NbPoints(); ++i)
  {
    const IntAna2d_IntPoint& intp = intersector.Point(i);
    const gp_Pnt2d&          p    = intp.Value();

    double d = checkp.SquareDistance(p);
    if (d < minDist)
    {
      minDist = d;
      pc      = p;
    }
  }
  pc.Coord(xc, yc);

  double angle = v1.Angle(v2);
  if (fabs(angle) < Precision::Angular())
  {
    angle = gp_Vec2d(pc, pc1).Angle(gp_Vec2d(pc, pc2));
    cw    = angle < 0.0;
  }
  else
  {
    cw = angle > 0.0;
  }

  start = fabs(gp_Vec2d(pc1, p12).Angle(gp_Vec2d(pc1, pc)));
  end   = fabs(gp_Vec2d(pc2, p12).Angle(gp_Vec2d(pc2, pc)));
  return true;
}

bool ChFi2d_AnaFilletAlgo::Cut(const gp_Pln& thePlane, TopoDS_Edge& theE1, TopoDS_Edge& theE2)
{
  gp_Pnt                    p;
  bool                      found(false);
  double                    param1 = 0.0, param2 = 0.0;
  double                    f1, l1, f2, l2;
  occ::handle<Geom_Curve>   c1 = BRep_Tool::Curve(theE1, f1, l1);
  occ::handle<Geom_Curve>   c2 = BRep_Tool::Curve(theE2, f2, l2);
  GeomAPI_ExtremaCurveCurve extrema(c1, c2, f1, l1, f2, l2);
  if (extrema.NbExtrema())
  {
    int i, nb = extrema.NbExtrema();
    for (i = 1; i <= nb; ++i)
    {
      const double d = extrema.Distance(i);
      if (d < Precision::Confusion())
      {
        extrema.Parameters(i, param1, param2);
        if (fabs(l1 - param1) > Precision::Confusion()
            && fabs(f2 - param2) > Precision::Confusion())
        {
          found = true;
          extrema.Points(i, p, p);
          break;
        }
      }
    }
  }

  if (found)
  {
    BRepBuilderAPI_MakeEdge mkEdge1(c1, f1, param1);
    if (mkEdge1.IsDone())
    {
      theE1 = mkEdge1.Edge();

      BRepBuilderAPI_MakeEdge mkEdge2(c2, param2, l2);
      if (mkEdge2.IsDone())
      {
        theE2 = mkEdge2.Edge();

        gp_Pnt2d p2d = ProjLib::Project(thePlane, p);
        p2d.Coord(x12, y12);
        x21 = x12;
        y21 = y12;
        return true;
      }
    }
  }
  return false;
}
