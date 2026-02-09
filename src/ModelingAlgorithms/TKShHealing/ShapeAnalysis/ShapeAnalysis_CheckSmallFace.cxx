

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepLib.hpp>
#include <BRepTools.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_ElementarySurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomLib.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis_CheckSmallFace.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeAnalysis_Wire.hpp>
#include <ShapeAnalysis_WireOrder.hpp>
#include <ShapeExtend.hpp>
#include <ShapeExtend_WireData.hpp>
#include <Standard_ErrorHandler.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_List.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Builder.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

ShapeAnalysis_CheckSmallFace::ShapeAnalysis_CheckSmallFace()
{
  myStatusSpot      = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myStatusStrip     = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myStatusPin       = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myStatusTwisted   = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myStatusSplitVert = ShapeExtend::EncodeStatus(ShapeExtend_OK);
}

static void MinMaxPnt(const gp_Pnt& p,
                      int&          nb,
                      double&       minx,
                      double&       miny,
                      double&       minz,
                      double&       maxx,
                      double&       maxy,
                      double&       maxz)
{
  double x, y, z;
  p.Coord(x, y, z);
  if (nb < 1)
  {
    minx = maxx = x;
    miny = maxy = y;
    minz = maxz = z;
  }
  else
  {
    if (minx > x)
      minx = x;
    if (maxx < x)
      maxx = x;
    if (miny > y)
      miny = y;
    if (maxy < y)
      maxy = y;
    if (minz > z)
      minz = z;
    if (maxz < z)
      maxz = z;
  }
  nb++;
}

static bool MinMaxSmall(const double minx,
                        const double miny,
                        const double minz,
                        const double maxx,
                        const double maxy,
                        const double maxz,
                        const double toler)
{
  double dx = maxx - minx;
  double dy = maxy - miny;
  double dz = maxz - minz;

  return (dx <= toler || Precision::IsInfinite(dx)) && (dy <= toler || Precision::IsInfinite(dy))
         && (dz <= toler || Precision::IsInfinite(dz));
}

int ShapeAnalysis_CheckSmallFace::IsSpotFace(const TopoDS_Face& F,
                                             gp_Pnt&            spot,
                                             double&            spotol,
                                             const double       tol) const
{

  double toler = tol;
  double tolv  = tol;

  bool isWir = false;
  for (TopoDS_Iterator itw(F, false); itw.More(); itw.Next())
  {
    if (itw.Value().ShapeType() != TopAbs_WIRE)
      continue;
    TopoDS_Wire w1 = TopoDS::Wire(itw.Value());
    if (!w1.IsNull())
    {
      isWir = true;
      break;
    }
  }
  if (!isWir)
    return true;
  int    nbv  = 0;
  double minx = 0, miny = 0, minz = 0, maxx = Precision::Infinite(), maxy = Precision::Infinite(),
         maxz = Precision::Infinite();
  TopoDS_Vertex V0;
  bool          same = true;
  for (TopExp_Explorer iv(F, TopAbs_VERTEX); iv.More(); iv.Next())
  {
    TopoDS_Vertex V = TopoDS::Vertex(iv.Current());
    if (V0.IsNull())
      V0 = V;
    else if (same)
    {
      if (!V0.IsSame(V))
        same = false;
    }

    gp_Pnt pnt = BRep_Tool::Pnt(V);

    MinMaxPnt(pnt, nbv, minx, miny, minz, maxx, maxy, maxz);

    if (tol < 0)
    {
      tolv = BRep_Tool::Tolerance(V);
      if (tolv > toler)
        toler = tolv;
    }
  }

  if (!MinMaxSmall(minx, miny, minz, maxx, maxy, maxz, toler))
    return 0;

  for (TopExp_Explorer ie(F, TopAbs_EDGE); ie.More(); ie.Next())
  {
    TopoDS_Edge             E = TopoDS::Edge(ie.Current());
    double                  cf, cl;
    occ::handle<Geom_Curve> C3D = BRep_Tool::Curve(E, cf, cl);
    if (C3D.IsNull())
      continue;
    gp_Pnt debut  = C3D->Value(cf);
    gp_Pnt milieu = C3D->Value((cf + cl) / 2);
    if (debut.SquareDistance(milieu) > toler * toler)
      return 0;
  }

  spot.SetCoord((minx + maxx) / 2., (miny + maxy) / 2., (minz + maxz) / 2.);
  spotol = maxx - minx;
  spotol = std::max(spotol, maxy - miny);
  spotol = std::max(spotol, maxz - minz);
  spotol = spotol / 2.;

  return (same ? 2 : 1);
}

bool ShapeAnalysis_CheckSmallFace::CheckSpotFace(const TopoDS_Face& F, const double tol)
{
  gp_Pnt spot;
  double spotol;
  int    stat = IsSpotFace(F, spot, spotol, tol);
  if (!stat)
    return false;
  switch (stat)
  {
    case 1:
      myStatusSpot = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
      break;
    case 2:
      myStatusSpot = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
      break;
    default:
      break;
  }
  return true;
}

bool ShapeAnalysis_CheckSmallFace::IsStripSupport(const TopoDS_Face& F, const double tol)
{

  double toler = tol;
  if (toler < 0)
    toler = 1.e-07;

  TopLoc_Location           loc;
  occ::handle<Geom_Surface> surf = BRep_Tool::Surface(F, loc);
  if (surf.IsNull())
    return false;

  occ::handle<Geom_BSplineSurface> bs = occ::down_cast<Geom_BSplineSurface>(surf);
  occ::handle<Geom_BezierSurface>  bz = occ::down_cast<Geom_BezierSurface>(surf);

  if (!bs.IsNull() || !bz.IsNull())
  {
    bool cbz = (!bz.IsNull());
    int  iu, iv, nbu, nbv;
    if (cbz)
    {
      nbu = bz->NbUPoles(), nbv = bz->NbVPoles();
    }
    else
    {
      nbu = bs->NbUPoles(), nbv = bs->NbVPoles();
    }

    double minx = 0., miny = 0., minz = 0., maxx = 0., maxy = 0., maxz = 0.;
    bool   issmall = true;

    for (iu = 1; iu <= nbu; iu++)
    {

      int nb = 0;
      for (iv = 1; iv <= nbv; iv++)
      {
        gp_Pnt unp = (cbz ? bz->Pole(iu, iv) : bs->Pole(iu, iv));
        MinMaxPnt(unp, nb, minx, miny, minz, maxx, maxy, maxz);
      }
      if (!MinMaxSmall(minx, miny, minz, maxx, maxy, maxz, toler))
      {
        issmall = false;
        break;
      }
    }
    if (issmall)
    {
      myStatusStrip = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
      return issmall;
    }
    issmall = true;
    for (iv = 1; iv <= nbv; iv++)
    {

      int nb = 0;
      for (iu = 1; iu <= nbu; iu++)
      {
        gp_Pnt unp = (cbz ? bz->Pole(iu, iv) : bs->Pole(iu, iv));
        MinMaxPnt(unp, nb, minx, miny, minz, maxx, maxy, maxz);
      }
      if (!MinMaxSmall(minx, miny, minz, maxx, maxy, maxz, toler))
      {
        issmall = false;
        break;
      }
    }
    if (issmall)
    {
      myStatusStrip = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
      return issmall;
    }
  }

  return false;
}

bool ShapeAnalysis_CheckSmallFace::CheckStripEdges(const TopoDS_Edge& E1,
                                                   const TopoDS_Edge& E2,
                                                   const double       tol,
                                                   double&            dmax) const
{

  double toler = tol;
  if (tol < 0)
  {
    double tole = BRep_Tool::Tolerance(E1) + BRep_Tool::Tolerance(E2);
    if (toler < tole / 2.)
      toler = tole / 2.;
  }

  int nbint = 10;

  ShapeAnalysis_Curve SAC;
  double              cf1, cl1, cf2, cl2, u;
  dmax = 0;
  occ::handle<Geom_Curve> C1, C2;
  C1 = BRep_Tool::Curve(E1, cf1, cl1);
  C2 = BRep_Tool::Curve(E2, cf2, cl2);
  if (C1.IsNull() || C2.IsNull())
    return false;
  cf1                                = std::max(cf1, C1->FirstParameter());
  cl1                                = std::min(cl1, C1->LastParameter());
  occ::handle<Geom_TrimmedCurve> C1T = new Geom_TrimmedCurve(C1, cf1, cl1, true);

  cf1 = C1T->FirstParameter();
  cl1 = C1T->LastParameter();
  occ::handle<Geom_TrimmedCurve> CC;
  cf2                                = std::max(cf2, C2->FirstParameter());
  cl2                                = std::min(cl2, C2->LastParameter());
  occ::handle<Geom_TrimmedCurve> C2T = new Geom_TrimmedCurve(C2, cf2, cl2, true);
  cf2                                = C2T->FirstParameter();
  cl2                                = C2T->LastParameter();

  double cd1 = (cl1 - cf1) / nbint;
  double cd2 = (cl2 - cf2) / nbint;
  double f, l;
  f = cf2;
  l = cl2;
  for (int numcur = 0; numcur < 2; numcur++)
  {
    u = cf1;
    if (numcur)
    {
      CC  = C1T;
      C1T = C2T;
      C2T = CC;
      cd1 = cd2;
      u   = cf2;
      f   = cf1;
      l   = cl1;
    }
    for (int nump = 0; nump <= nbint; nump++)
    {
      gp_Pnt p2, p1 = C1T->Value(u);
      double para;

      GeomAdaptor_Curve GAC(C2T);
      double            dist = SAC.Project(GAC, p1, toler, p2, para);

      if (para < f || para > l)
        return false;
      if (dist > dmax)
        dmax = dist;
      if (dist > toler)
        return false;
      u += cd1;
    }
  }
  return (dmax < toler);
}

bool ShapeAnalysis_CheckSmallFace::FindStripEdges(const TopoDS_Face& F,
                                                  TopoDS_Edge&       E1,
                                                  TopoDS_Edge&       E2,
                                                  const double       tol,
                                                  double&            dmax)
{
  E1.Nullify();
  E2.Nullify();
  int nb = 0;
  for (TopExp_Explorer ex(F, TopAbs_EDGE); ex.More(); ex.Next())
  {
    TopoDS_Edge E = TopoDS::Edge(ex.Current());
    if (nb == 1 && E.IsSame(E1))
      continue;
    TopoDS_Vertex V1, V2;
    TopExp::Vertices(E, V1, V2);
    gp_Pnt p1, p2;
    p1           = BRep_Tool::Pnt(V1);
    p2           = BRep_Tool::Pnt(V2);
    double toler = tol;
    if (toler <= 0)
      toler = (BRep_Tool::Tolerance(V1) + BRep_Tool::Tolerance(V2)) / 2.;

    double dist = p1.Distance(p2);

    double                  cf, cl;
    occ::handle<Geom_Curve> CC;
    CC                = BRep_Tool::Curve(E, cf, cl);
    bool isNullLength = true;
    if (!CC.IsNull())
    {
      gp_Pnt pp = CC->Value((cf + cl) / 2.);
      if (pp.Distance(p1) < toler && pp.Distance(p2) < toler)
        continue;
      isNullLength = false;
    }
    if (dist <= toler && isNullLength)
      continue;
    nb++;
    if (nb == 1)
      E1 = E;
    else if (nb == 2)
      E2 = E;
    else
      return false;
  }

  if (!E1.IsNull() && !E2.IsNull())
  {
    if (!CheckStripEdges(E1, E2, tol, dmax))
      return false;
    else
    {
      myStatusStrip = ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
      return true;
    }
  }
  return false;
}

bool ShapeAnalysis_CheckSmallFace::CheckSingleStrip(const TopoDS_Face& F,
                                                    TopoDS_Edge&       E1,
                                                    TopoDS_Edge&       E2,
                                                    const double       tol)
{
  double toler = tol;
  double minx, miny, minz, maxx, maxy, maxz;

  TopoDS_Vertex V1, V2;
  int           nb = 0;
  for (TopExp_Explorer itv(F, TopAbs_VERTEX); itv.More(); itv.Next())
  {
    TopoDS_Vertex V = TopoDS::Vertex(itv.Current());
    if (V1.IsNull())
      V1 = V;
    else if (V1.IsSame(V))
      continue;
    else if (V2.IsNull())
      V2 = V;
    else if (V2.IsSame(V))
      continue;
    else
      return false;
  }

  nb = 0;
  for (TopExp_Explorer ite(F, TopAbs_EDGE); ite.More(); ite.Next())
  {
    TopoDS_Edge E = TopoDS::Edge(ite.Current());
    if (nb == 1 && E.IsSame(E1))
      continue;
    TopoDS_Vertex VA, VB;
    TopExp::Vertices(E, VA, VB);
    if (tol < 0)
    {
      double tolv;
      tolv = BRep_Tool::Tolerance(VA);
      if (toler < tolv)
        toler = tolv;
      tolv = BRep_Tool::Tolerance(VB);
      if (toler < tolv)
        toler = tolv;
    }

    if (VA.IsSame(VB))
    {
      double                  cf = 0., cl = 0.;
      occ::handle<Geom_Curve> C3D;
      if (!BRep_Tool::Degenerated(E))
        C3D = BRep_Tool::Curve(E, cf, cl);
      if (C3D.IsNull())
        continue;
      int    np  = 0;
      gp_Pnt deb = C3D->Value(cf);
      MinMaxPnt(deb, np, minx, miny, minz, maxx, maxy, maxz);
      gp_Pnt fin = C3D->Value(cl);
      MinMaxPnt(fin, np, minx, miny, minz, maxx, maxy, maxz);
      gp_Pnt mid = C3D->Value((cf + cl) / 2.);
      MinMaxPnt(mid, np, minx, miny, minz, maxx, maxy, maxz);
      if (!MinMaxSmall(minx, miny, minz, maxx, maxy, maxz, toler))
        return false;
    }
    else
    {

      nb++;
      if (nb > 2)
        return false;
      if (nb == 1)
      {
        V1 = VA;
        V2 = VB;
        E1 = E;
      }
      else if (nb == 2)
      {
        if (V1.IsSame(VA) && !V2.IsSame(VB))
          return false;
        if (V1.IsSame(VB) && !V2.IsSame(VA))
          return false;
        E2 = E;
      }
      else
        return false;
    }
  }

  if (nb < 2)
    return false;

  double dmax;
  if (!CheckStripEdges(E1, E2, tol, dmax))
    return false;
  myStatusStrip = ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
  return true;
}

bool ShapeAnalysis_CheckSmallFace::CheckStripFace(const TopoDS_Face& F,
                                                  TopoDS_Edge&       E1,
                                                  TopoDS_Edge&       E2,
                                                  const double       tol)
{

  if (CheckSingleStrip(F, E1, E2, tol))
    return true;

  double dmax;
  return FindStripEdges(F, E1, E2, tol, dmax);
}

int ShapeAnalysis_CheckSmallFace::CheckSplittingVertices(
  const TopoDS_Face& F,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                                                        MapEdges,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<double>, TopTools_ShapeMapHasher>& MapParam,
  TopoDS_Compound&                                                                      theAllVert)
{

  int nbv = 0, nbp = 0;

  BRep_Builder theBuilder;

  TopExp_Explorer itv;
  for (itv.Init(F, TopAbs_VERTEX); itv.More(); itv.Next())
    nbv++;

  if (nbv == 0)
    return 0;
  NCollection_Array1<TopoDS_Shape> vtx(1, nbv);
  NCollection_Array1<gp_Pnt>       vtp(1, nbv);
  NCollection_Array1<double>       vto(1, nbv);

  nbp = 0;
  for (itv.Init(F, TopAbs_VERTEX); itv.More(); itv.Next())
  {
    nbp++;
    TopoDS_Vertex unv = TopoDS::Vertex(itv.Current());
    vtx.SetValue(nbp, unv);
    gp_Pnt unp = BRep_Tool::Pnt(unv);
    vtp.SetValue(nbp, unp);
    double unt = myPrecision;
    if (unt < 0)
      unt = BRep_Tool::Tolerance(unv);
    vto.SetValue(nbp, unt);
  }
  nbv = nbp;
  nbp = 0;

  ShapeAnalysis_Curve SAC;
  for (int iv = 1; iv <= nbv; iv++)
  {
    TopoDS_Vertex                  V = TopoDS::Vertex(vtx.Value(iv));
    NCollection_List<TopoDS_Shape> listEdge;
    NCollection_List<double>       listParam;
    bool                           issplit = false;
    for (TopExp_Explorer ite(F, TopAbs_EDGE); ite.More(); ite.Next())
    {
      TopoDS_Edge   E = TopoDS::Edge(ite.Current());
      TopoDS_Vertex V1, V2;
      TopExp::Vertices(E, V1, V2);
      double                  cf, cl;
      occ::handle<Geom_Curve> C3D = BRep_Tool::Curve(E, cf, cl);
      if (C3D.IsNull())
        continue;
      if (V.IsSame(V1) || V.IsSame(V2))
        continue;
      gp_Pnt unp = vtp.Value(iv);
      double unt = vto.Value(iv);
      gp_Pnt proj;
      double param;
      double dist = SAC.Project(C3D, unp, unt * 10., proj, param, cf, cl);
      if (dist == 0.0)
        continue;

      if (dist < unt)
      {

        double fpar, lpar, eps = 1.e-06;
        if (param >= cl || param <= cf)
          continue;
        fpar = param - cf;
        lpar = param - cl;
        if ((std::abs(fpar) < eps) || (std::abs(lpar) < eps))
          continue;
        listEdge.Append(E);
        listParam.Append(param);
        issplit = true;
      }
    }
    if (issplit)
    {
      nbp++;
      theBuilder.Add(theAllVert, V);
      MapEdges.Bind(V, listEdge);
      MapParam.Bind(V, listParam);
    }
  }
  if (nbp != 0)
    myStatusSplitVert = ShapeExtend::EncodeStatus(ShapeExtend_DONE);
  return nbp;
}

static int IsoStat(const NCollection_Array2<gp_Pnt>& poles,
                   const int                         uorv,
                   const int                         rank,
                   const double                      tolpin,
                   const double                      toler)
{
  int    i, np = 0;
  int    i0   = (uorv == 1 ? poles.LowerCol() : poles.LowerRow());
  int    i1   = (uorv == 1 ? poles.UpperCol() : poles.UpperRow());
  double xmin = 0., ymin = 0., zmin = 0., xmax = 0., ymax = 0., zmax = 0.;
  for (i = i0; i <= i1; i++)
  {
    if (uorv == 1)
      MinMaxPnt(poles(rank, i), np, xmin, ymin, zmin, xmax, ymax, zmax);
    else
      MinMaxPnt(poles(i, rank), np, xmin, ymin, zmin, xmax, ymax, zmax);
  }
  if (MinMaxSmall(xmin, ymin, zmin, xmax, ymax, zmax, tolpin))
    return 0;
  if (MinMaxSmall(xmin, ymin, zmin, xmax, ymax, zmax, toler))
    return 1;
  return 2;
}

static bool CheckPoles(const NCollection_Array2<gp_Pnt>& poles, int uorv, int rank)
{
  int i0 = (uorv == 1 ? poles.LowerCol() : poles.LowerRow());
  int i1 = (uorv == 1 ? poles.UpperCol() : poles.UpperRow());
  for (int i = i0; i <= i1 - 1; i++)
  {
    if (uorv == 1)
    {
      if (poles(rank, i).IsEqual(poles(rank, i + 1), 1e-15))
        return true;
    }
    else if (poles(i, rank).IsEqual(poles(i + 1, rank), 1e-15))
      return true;
  }
  return false;
}

bool ShapeAnalysis_CheckSmallFace::CheckPin(const TopoDS_Face& F, int& whatrow, int& sens)
{
  TopLoc_Location           loc;
  occ::handle<Geom_Surface> surf = BRep_Tool::Surface(F, loc);
  if (surf->IsKind(STANDARD_TYPE(Geom_ElementarySurface)))
    return false;

  double toler = myPrecision;
  if (toler < 0)
    toler = 1.e-4;
  double tolpin = 1.e-9;

  int                              nbu = 0, nbv = 0;
  occ::handle<Geom_BSplineSurface> bs = occ::down_cast<Geom_BSplineSurface>(surf);
  occ::handle<Geom_BezierSurface>  bz = occ::down_cast<Geom_BezierSurface>(surf);
  if (!bs.IsNull())
  {
    nbu = bs->NbUPoles();
    nbv = bs->NbVPoles();
  }
  if (!bz.IsNull())
  {
    nbu = bz->NbUPoles();
    nbv = bz->NbVPoles();
  }
  if (nbu == 0 || nbv == 0)
    return false;

  NCollection_Array2<gp_Pnt> allpoles(1, nbu, 1, nbv);
  if (!bs.IsNull())
    bs->Poles(allpoles);
  if (!bz.IsNull())
    bz->Poles(allpoles);

  sens     = 0;
  int stat = 0;
  whatrow  = 0;
  stat     = IsoStat(allpoles, 1, 1, tolpin, toler);
  if (stat)
  {
    sens    = 1;
    whatrow = nbu;
  }

  stat = IsoStat(allpoles, 1, nbu, tolpin, toler);
  if (stat)
  {
    sens    = 1;
    whatrow = nbu;
  }

  stat = IsoStat(allpoles, 2, 1, tolpin, toler);
  if (stat)
  {
    sens    = 2;
    whatrow = 1;
  }

  stat = IsoStat(allpoles, 2, nbv, tolpin, toler);
  if (stat)
  {
    sens    = 2;
    whatrow = nbv;
  }

  if (!sens)
    return false;

  switch (stat)
  {
    case 1:
      myStatusPin = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
      break;
    case 2:
      myStatusPin = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
      break;
    default:
      break;
  }

  if (stat == 1)
  {

    if (CheckPoles(allpoles, 2, nbv) || CheckPoles(allpoles, 2, 1) || CheckPoles(allpoles, 1, nbu)
        || CheckPoles(allpoles, 1, 1))
      myStatusPin = ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
  }

  return true;
}

static double TwistedNorm(const double x1,
                          const double y1,
                          const double z1,
                          const double x2,
                          const double y2,
                          const double z2)
{
  return (x1 * x2) + (y1 * y2) + (z1 * z2);
}

bool ShapeAnalysis_CheckSmallFace::CheckTwisted(const TopoDS_Face& F,
                                                double&            paramu,
                                                double&            paramv)
{
  TopLoc_Location           loc;
  occ::handle<Geom_Surface> surf = BRep_Tool::Surface(F, loc);
  if (surf->IsKind(STANDARD_TYPE(Geom_ElementarySurface)))
    return false;

  double toler = myPrecision;
  if (toler < 0)
    toler = 1.e-4;

  GeomAdaptor_Surface GAS(surf);

  int                        nbint = 5;
  NCollection_Array2<double> nx(1, nbint + 1, 1, nbint + 1);
  NCollection_Array2<double> ny(1, nbint + 1, 1, nbint + 1);
  NCollection_Array2<double> nz(1, nbint + 1, 1, nbint + 1);
  int                        iu, iv;
  double                     umin, umax, vmin, vmax;
  surf->Bounds(umin, umax, vmin, vmax);
  double u = umin, du = (umax - umin) / nbint;
  double v = vmin, dv = (umax - umin) / nbint;

  for (iu = 1; iu <= nbint; iu++)
  {
    for (iv = 1; iv <= nbint; iv++)
    {

      gp_Pnt curp;
      gp_Vec V1, V2, VXnorm;
      GAS.D1(u, v, curp, V1, V2);
      VXnorm = V1.Crossed(V2);
      nx.SetValue(iu, iv, VXnorm.X());
      ny.SetValue(iu, iv, VXnorm.Y());
      nz.SetValue(iu, iv, VXnorm.Z());
      v += dv;
    }
    u += du;
    v = vmin;
  }

  for (iu = 1; iu < nbint; iu++)
  {
    for (iv = 1; iv < nbint; iv++)
    {

      if (TwistedNorm(nx(iu, iv),
                      ny(iu, iv),
                      nz(iu, iv),
                      nx(iu, iv + 1),
                      ny(iu, iv + 1),
                      nz(iu, iv + 1))
            < 0.
          || TwistedNorm(nx(iu, iv),
                         ny(iu, iv),
                         nz(iu, iv),
                         nx(iu + 1, iv),
                         ny(iu + 1, iv),
                         nz(iu + 1, iv))
               < 0.)
      {
        myStatusTwisted = ShapeExtend::EncodeStatus(ShapeExtend_DONE);
        paramu          = umin + du * iu - du / 2;
        paramv          = vmin + dv * iv - dv / 2;
        return true;
      }
    }
  }

  return false;
}

bool ShapeAnalysis_CheckSmallFace::CheckPinFace(
  const TopoDS_Face&                                                        F,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& mapEdges,
  const double                                                              toler)
{

  TopExp_Explorer exp_w(F, TopAbs_WIRE);
  exp_w.More();
  double                            coef1      = 0, coef2;
  TopoDS_Wire                       theCurWire = TopoDS::Wire(exp_w.Current());
  ShapeAnalysis_WireOrder           wi;
  ShapeAnalysis_Wire                sfw;
  occ::handle<ShapeExtend_WireData> sbwd = new ShapeExtend_WireData(theCurWire);
  sfw.Load(sbwd);
  sfw.CheckOrder(wi);
  occ::handle<NCollection_HSequence<TopoDS_Shape>> newedges =
    new NCollection_HSequence<TopoDS_Shape>();
  int nb = wi.NbEdges();
  int i  = 0;
  for (i = 1; i <= nb; i++)
    newedges->Append(sbwd->Edge(wi.Ordered(i)));
  for (i = 1; i <= nb; i++)
    sbwd->Set(TopoDS::Edge(newedges->Value(i)), i);

  theCurWire       = sbwd->Wire();
  i                = 1;
  bool        done = false;
  double      tol  = Precision::Confusion();
  TopoDS_Edge theFirstEdge, theSecondEdge;
  double      d1 = 0, d2 = 0;
  for (TopExp_Explorer exp_e(F, TopAbs_EDGE); exp_e.More(); exp_e.Next())
  {
    TopoDS_Vertex V1, V2;
    gp_Pnt        p1, p2;
    if (i == 1)
    {
      theFirstEdge = TopoDS::Edge(exp_e.Current());
      V1           = TopExp::FirstVertex(theFirstEdge);
      V2           = TopExp::LastVertex(theFirstEdge);
      p1           = BRep_Tool::Pnt(V1);
      p2           = BRep_Tool::Pnt(V2);
      tol          = std::max(BRep_Tool::Tolerance(V1), BRep_Tool::Tolerance(V2));
      if (toler > 0)
        tol = toler;
      d1 = p1.Distance(p2);
      if (d1 == 0)
        return false;
      if (d1 / tol >= 1)
        coef1 = d1 / tol;
      else
        continue;
      if (coef1 <= 3)
        continue;
      i++;
      continue;
    }

    theSecondEdge = TopoDS::Edge(exp_e.Current());
    V1            = TopExp::FirstVertex(theSecondEdge);
    V2            = TopExp::LastVertex(theSecondEdge);

    p1 = BRep_Tool::Pnt(V1);
    p2 = BRep_Tool::Pnt(V2);
    if (toler == -1)
      tol = std::max(BRep_Tool::Tolerance(V1), BRep_Tool::Tolerance(V2));
    else
      tol = toler;
    if (p1.Distance(p2) > tol)
      continue;

    d2 = p1.Distance(p2);
    if (d2 == 0)
      return false;
    if (d2 / tol >= 1)
      coef2 = d2 / tol;
    else
      continue;
    if (coef2 <= 3)
      continue;
    if (coef1 > coef2 * 10)
      continue;
    if (coef2 > coef1 * 10)
    {
      theFirstEdge = theSecondEdge;
      coef1        = coef2;
      continue;
    }

    if (CheckPinEdges(theFirstEdge, theSecondEdge, coef1, coef2, toler))
    {
      mapEdges.Bind(theFirstEdge, theSecondEdge);
      myStatusPinFace = ShapeExtend::EncodeStatus(ShapeExtend_DONE);
      done            = true;
    }

    theFirstEdge = theSecondEdge;
    coef1        = coef2;
  }
  return done;
}

bool ShapeAnalysis_CheckSmallFace::CheckPinEdges(const TopoDS_Edge& theFirstEdge,
                                                 const TopoDS_Edge& theSecondEdge,
                                                 const double       coef1,
                                                 const double       coef2,
                                                 const double       toler) const
{

  double                  cf1, cl1, cf2, cl2;
  occ::handle<Geom_Curve> C1, C2, C3;
  C1 = BRep_Tool::Curve(theFirstEdge, cf1, cl1);
  C2 = BRep_Tool::Curve(theSecondEdge, cf2, cl2);
  gp_Pnt p1, p2, pp1, pp2, pv;
  double d1 = (cf1 - cl1) / coef1;
  double d2 = (cf2 - cl2) / coef2;

  p1  = C1->Value(cf1);
  p2  = C1->Value(cl1);
  pp1 = C2->Value(cf2);
  pp2 = C2->Value(cl2);
  double        tol;
  double        paramc1 = 0, paramc2 = 0;
  TopoDS_Vertex theSharedV = TopExp::LastVertex(theFirstEdge);
  if (toler == -1)
    tol = BRep_Tool::Tolerance(theSharedV);
  else
    tol = toler;
  pv = BRep_Tool::Pnt(theSharedV);
  if (pv.Distance(p1) <= tol)
    paramc1 = cf1;
  else if (pv.Distance(p2) <= tol)
    paramc1 = cl1;
  if (pv.Distance(pp1) <= tol)
    paramc2 = cf2;
  else if (pv.Distance(pp2) <= tol)
    paramc2 = cl2;

  gp_Pnt proj;
  if (p1.Distance(p2) < pp1.Distance(pp2))
  {
    C3 = C1;
    if (paramc1 == cf1)
      proj = C1->Value(paramc1 + (coef1 - 3) * d1);
    else
      proj = C1->Value(paramc1 - 3 * d1);
  }
  else
  {
    C3 = C2;
    if (paramc2 == cf2)
      proj = C2->Value(paramc2 + (coef2 - 3) * d2);
    else
      proj = C2->Value(paramc2 - 3 * d2);
  }
  double              param;
  GeomAdaptor_Curve   GAC(C3);
  double              f = C3->FirstParameter();
  double              l = C3->LastParameter();
  gp_Pnt              result;
  ShapeAnalysis_Curve SAC;
  double              dist = SAC.Project(GAC, proj, tol, result, param);

  if (param < f || param > l)
    return false;
  if (dist > tol)
    return false;
  if (dist <= tol)
  {

    gp_Vec V11, V12, V21, V22;
    gp_Pnt tmp;
    C1->D2(paramc1, tmp, V11, V21);
    C2->D2(paramc2, tmp, V12, V22);
    double angle1 = 0, angle2 = 0;
    try
    {
      angle1 = V11.Angle(V12);
      angle2 = V21.Angle(V22);
    }
    catch (Standard_Failure const&)
    {
#ifdef OCCT_DEBUG
      std::cout << "Couldn't compute angle between derivative vectors" << std::endl;
#endif
      return false;
    }

    return (angle1 <= 0.001 && angle2 <= 0.01)
           || ((M_PI - angle2) <= 0.001 && (M_PI - angle2) <= 0.01);
  }

  return false;
}
