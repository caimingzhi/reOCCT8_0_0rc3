#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepExtrema_ExtPF.hpp>
#include <Extrema_ExtPS.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <LocOpe.hpp>
#include <LocOpe_Generator.hpp>
#include <LocOpe_GluedShape.hpp>
#include <LocOpe_Gluer.hpp>
#include <LocOpe_Spliter.hpp>
#include <LocOpe_WiresOnShape.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <StdFail_NotDone.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>

static TopAbs_Orientation GetOrientation(const TopoDS_Face&, const TopoDS_Face&);

static bool Contains(const NCollection_List<TopoDS_Shape>&, const TopoDS_Shape&);

void LocOpe_Gluer::Init(const TopoDS_Shape& Sbase, const TopoDS_Shape& Snew)
{
  mySb = Sbase;
  mySn = Snew;
  myMapEF.Clear();
  myMapEE.Clear();
  myDescF.Clear();
  myDone = false;
  myOri  = TopAbs_INTERNAL;
  myOpe  = LocOpe_INVALID;
}

void LocOpe_Gluer::Bind(const TopoDS_Face& Fnew, const TopoDS_Face& Fbase)
{
  TopExp_Explorer exp(mySn, TopAbs_FACE);

  for (; exp.More(); exp.Next())
  {
    if (exp.Current().IsSame(Fnew))
    {
      break;
    }
  }
  if (!exp.More())
  {
    throw Standard_ConstructionError();
  }

  TopoDS_Shape aLocalFace = Fnew.Oriented(exp.Current().Orientation());
  TopoDS_Face  Fnor       = TopoDS::Face(aLocalFace);

  for (exp.Init(mySb, TopAbs_FACE); exp.More(); exp.Next())
  {
    if (exp.Current().IsSame(Fbase))
    {
      break;
    }
  }
  if (!exp.More())
  {
    throw Standard_ConstructionError();
  }

  aLocalFace       = Fbase.Oriented(exp.Current().Orientation());
  TopoDS_Face Fbor = TopoDS::Face(aLocalFace);

  TopAbs_Orientation Ori = GetOrientation(Fnor, Fbor);

  if (myOri == TopAbs_INTERNAL)
  {
    myOri = Ori;
    if (myOri == TopAbs_REVERSED)
    {
      mySn.Reverse();
      myOpe = LocOpe_CUT;
    }
    else
    {
      myOpe = LocOpe_FUSE;
    }
  }
  else if (Ori != TopAbs_FORWARD)
  {
    myOpe = LocOpe_INVALID;
  }

  for (exp.Init(Fnor, TopAbs_EDGE); exp.More(); exp.Next())
  {
    const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());

    if (!myMapEF.Contains(edg))
    {
      myMapEF.Add(edg, Fbor);
    }

    else if (!myMapEF.FindFromKey(edg).IsSame(Fbor))
    {

      myMapEF.ChangeFromKey(edg).Nullify();
    }
  }

  myMapEF.Add(Fnor, Fbor);
}

void LocOpe_Gluer::Bind(const TopoDS_Edge& Enew, const TopoDS_Edge& Ebase)
{
  if (myMapEE.IsBound(Enew) && !myMapEE(Enew).IsSame(Ebase))
  {
    throw Standard_ConstructionError();
  }
  myMapEE.Bind(Enew, Ebase);
}

void LocOpe_Gluer::Perform()
{
  int ind;
  if (myDone)
  {
    return;
  }
  if (mySb.IsNull() || mySn.IsNull() || myMapEF.IsEmpty() || myOpe == LocOpe_INVALID)
  {
    throw Standard_ConstructionError();
  }

  occ::handle<LocOpe_WiresOnShape> theWOnS = new LocOpe_WiresOnShape(mySb);
  occ::handle<LocOpe_GluedShape>   theGS   = new LocOpe_GluedShape(mySn);

  int lmap = myMapEF.Extent();

  for (ind = 1; ind <= lmap; ind++)
  {
    TopoDS_Shape S = myMapEF.FindKey(ind);
    if (S.ShapeType() == TopAbs_EDGE)
    {
      TopoDS_Shape S2 = myMapEF(ind);
      if (!S2.IsNull())
      {
        theWOnS->Bind(TopoDS::Edge(S), TopoDS::Face(S2));
      }
    }
    else
    {
      theGS->GlueOnFace(TopoDS::Face(S));
    }
  }

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itm(myMapEE);
  for (; itm.More(); itm.Next())
  {
    theWOnS->Bind(TopoDS::Edge(itm.Key()), TopoDS::Edge(itm.Value()));
  }

  theWOnS->BindAll();

  if (!theWOnS->IsDone())
  {
    return;
  }

  LocOpe_Spliter theSplit(mySb);
  theSplit.Perform(theWOnS);
  if (!theSplit.IsDone())
  {
    return;
  }

  TopExp_Explorer exp(mySb, TopAbs_FACE);
  for (; exp.More(); exp.Next())
  {
    myDescF.Bind(exp.Current(), theSplit.DescendantShapes(exp.Current()));
  }

  for (exp.Init(mySn, TopAbs_FACE); exp.More(); exp.Next())
  {
    NCollection_List<TopoDS_Shape> thelist;
    myDescF.Bind(exp.Current(), thelist);
    if (Contains(theGS->OrientedFaces(), exp.Current()))
    {
      myDescF(exp.Current()).Append(exp.Current());
    }
  }

  LocOpe_Generator theGen(theSplit.ResultingShape());
  theGen.Perform(theGS);

  myDone = theGen.IsDone();
  if (myDone)
  {
    myRes = theGen.ResultingShape();

    AddEdges();

    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator itd;
    for (itd.Initialize(myDescF); itd.More(); itd.Next())
    {
      NCollection_List<TopoDS_Shape>           newDesc;
      NCollection_List<TopoDS_Shape>::Iterator itl;
      for (itl.Initialize(itd.Value()); itl.More(); itl.Next())
      {
        NCollection_List<TopoDS_Shape>::Iterator itl2(
          theGen.DescendantFace(TopoDS::Face(itl.Value())));
        for (; itl2.More(); itl2.Next())
        {
          const TopoDS_Face& descface = TopoDS::Face(itl2.Value());
          if (!descface.IsNull())
          {
            newDesc.Append(descface);
          }
        }
      }
      myDescF(itd.Key()) = newDesc;
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    theMapEF1, theMapEF2;
  TopExp::MapShapesAndAncestors(mySn, TopAbs_EDGE, TopAbs_FACE, theMapEF1);
  TopExp::MapShapesAndAncestors(myRes, TopAbs_EDGE, TopAbs_FACE, theMapEF2);

  for (ind = 1; ind <= theMapEF1.Extent(); ind++)
  {
    const TopoDS_Edge&                    edg = TopoDS::Edge(theMapEF1.FindKey(ind));
    const NCollection_List<TopoDS_Shape>& LL  = theMapEF1(ind);
    if (LL.Extent() == 2)
    {
      const TopoDS_Face& fac1    = TopoDS::Face(LL.First());
      const TopoDS_Face& fac2    = TopoDS::Face(LL.Last());
      GeomAbs_Shape      thecont = BRep_Tool::Continuity(edg, fac1, fac2);
      if (thecont >= GeomAbs_G1)
      {

        int ind2 = theMapEF2.FindIndex(edg);
        if (ind2 != 0)
        {
          const NCollection_List<TopoDS_Shape>& LL2 = theMapEF2(ind2);
          if (LL2.Extent() == 2)
          {
            const TopoDS_Face& ff1 = TopoDS::Face(LL2.First());
            const TopoDS_Face& ff2 = TopoDS::Face(LL2.Last());
            if ((ff1.IsSame(fac1) && ff2.IsSame(fac2)) || (ff1.IsSame(fac2) && ff2.IsSame(fac1)))
            {
            }
            else
            {
              BRep_Builder B;
              B.Continuity(edg, ff1, ff2, thecont);
            }
          }
        }
      }
    }
  }

  theWOnS->InitEdgeIterator();
  while (theWOnS->MoreEdge())
  {
    TopoDS_Edge edg = theWOnS->Edge();
    for (ind = 1; ind <= theMapEF2.Extent(); ind++)
    {
      const TopoDS_Edge& edg1 = TopoDS::Edge(theMapEF2.FindKey(ind));
      if (edg1.IsSame(edg))
      {
        myEdges.Append(edg);

        const NCollection_List<TopoDS_Shape>& L = theMapEF2(ind);
        if (L.Extent() == 2)
        {
          const TopoDS_Face& fac1 = TopoDS::Face(L.First());
          const TopoDS_Face& fac2 = TopoDS::Face(L.Last());
          if (LocOpe::TgtFaces(edg, fac1, fac2))
          {
            myTgtEdges.Append(edg);
            GeomAbs_Shape thecont = BRep_Tool::Continuity(edg, fac1, fac2);
            if (thecont < GeomAbs_G1)
            {
              BRep_Builder B;
              B.Continuity(edg, fac1, fac2, GeomAbs_G1);
            }
          }
        }
      }
    }
    theWOnS->NextEdge();
  }
}

const NCollection_List<TopoDS_Shape>& LocOpe_Gluer::DescendantFaces(const TopoDS_Face& F) const
{
  if (!myDone)
  {
    throw StdFail_NotDone();
  }
  if (myDescF.IsBound(F))
    return myDescF(F);
  static NCollection_List<TopoDS_Shape> nullList;
  return nullList;
}

static TopAbs_Orientation GetOrientation(const TopoDS_Face& Fn, const TopoDS_Face& Fb)
{

  occ::handle<Geom_Surface> Sn, Sb;
  Sn = BRep_Tool::Surface(Fn);
  Sb = BRep_Tool::Surface(Fb);

  TopExp_Explorer exp;
  double          f, l;
  gp_Pnt2d        ptvtx;
  gp_Pnt          pvt;
  gp_Vec          d1u, d1v, n1, n2;

  GeomAdaptor_Surface GAS(Sb);
  const double        TolU = GAS.UResolution(Precision::Confusion());
  const double        TolV = GAS.VResolution(Precision::Confusion());
  Extrema_ExtPS       anExtPS;
  anExtPS.Initialize(GAS,
                     GAS.FirstUParameter(),
                     GAS.LastUParameter(),
                     GAS.FirstVParameter(),
                     GAS.LastVParameter(),
                     TolU,
                     TolV);
  anExtPS.SetFlag(Extrema_ExtFlag_MIN);

  for (exp.Init(Fn, TopAbs_EDGE); exp.More(); exp.Next())
  {
    const TopoDS_Edge&        edg = TopoDS::Edge(exp.Current());
    occ::handle<Geom2d_Curve> C2d = BRep_Tool::CurveOnSurface(edg, Fn, f, l);
    if (Precision::IsNegativeInfinite(f) && Precision::IsPositiveInfinite(l))
    {
      f = -100.;
      l = 100.;
    }
    else if (Precision::IsNegativeInfinite(f))
    {
      f = l - 200.;
    }
    else if (Precision::IsPositiveInfinite(l))
    {
      l = f + 200.;
    }
    double deltau = (l - f) / 20.;
    for (int i = 1; i <= 21; i++)
    {
      C2d->D0(f + (i - 1) * deltau, ptvtx);
      Sn->D1(ptvtx.X(), ptvtx.Y(), pvt, d1u, d1v);
      n1 = d1u.Crossed(d1v);
      if (n1.Magnitude() > Precision::Confusion())
      {
        n1.Normalize();
        if (Fn.Orientation() == TopAbs_REVERSED)
        {
          n1.Reverse();
        }

        anExtPS.Perform(pvt);
        if (anExtPS.IsDone())
        {
          double dist2min = RealLast();
          int    jmin     = 0;
          for (int j = 1; j <= anExtPS.NbExt(); j++)
          {
            if (anExtPS.SquareDistance(j) < dist2min)
            {
              jmin     = j;
              dist2min = anExtPS.SquareDistance(j);
            }
          }
          if (jmin != 0)
          {
            double uu, vv;
            anExtPS.Point(jmin).Parameter(uu, vv);
            Sb->D1(uu, vv, pvt, d1u, d1v);
            n2 = d1u.Crossed(d1v);
            if (n2.Magnitude() > Precision::Confusion())
            {
              n2.Normalize();
              if (Fb.Orientation() == TopAbs_REVERSED)
              {
                n2.Reverse();
              }
              if (n1.Dot(n2) > 0.)
              {
                return TopAbs_REVERSED;
              }
              return TopAbs_FORWARD;
            }
          }
        }
      }
    }
  }
  return TopAbs_INTERNAL;
}

static bool Contains(const NCollection_List<TopoDS_Shape>& L, const TopoDS_Shape& S)
{
  NCollection_List<TopoDS_Shape>::Iterator it;
  for (it.Initialize(L); it.More(); it.Next())
  {
    if (it.Value().IsSame(S))
    {
      return true;
    }
  }
  return false;
}

void LocOpe_Gluer::AddEdges()
{
  TopExp_Explorer exp, expsb;
  exp.Init(mySn, TopAbs_EDGE);

  TopLoc_Location Loc;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MapV, MapFPrism, MapE;
  TopExp_Explorer                                               vexp;
  int                                                           flag, i;

  TopExp::MapShapes(mySn, TopAbs_FACE, MapFPrism);

  for (expsb.Init(myRes, TopAbs_FACE); expsb.More(); expsb.Next())
  {
    if (!MapFPrism.Contains(expsb.Current()))
    {
      MapV.Clear();
      TopExp::MapShapes(expsb.Current(), TopAbs_VERTEX, MapV);
      TopExp::MapShapes(expsb.Current(), TopAbs_EDGE, MapE);
      for (exp.Init(mySn, TopAbs_EDGE); exp.More(); exp.Next())
      {
        TopoDS_Edge e = TopoDS::Edge(exp.Current());
        if (MapE.Contains(e))
          continue;
        flag = 0;
        vexp.Init(e, TopAbs_VERTEX);
        for (; vexp.More(); vexp.Next())
        {
          TopoDS_Vertex v = TopoDS::Vertex(vexp.Current());
          if (MapV.Contains(v))
          {
            flag = 1;
          }
        }
        if (flag == 1)
        {

          vexp.Init(e, TopAbs_VERTEX);
          BRepExtrema_ExtPF ext;
          ext.Initialize(TopoDS::Face(expsb.Current()));
          flag = 0;
          for (; vexp.More(); vexp.Next())
          {
            TopoDS_Vertex v = TopoDS::Vertex(vexp.Current());
            if (!MapV.Contains(v))
            {
              ext.Perform(v, TopoDS::Face(expsb.Current()));
              if (!ext.IsDone() || ext.NbExt() == 0)
              {
                flag = 0;
                break;
              }
              else
              {
                double dist2min = ext.SquareDistance(1);
                for (i = 2; i <= ext.NbExt(); i++)
                {
                  dist2min = std::min(dist2min, ext.SquareDistance(i));
                }
                if (dist2min >= BRep_Tool::Tolerance(v) * BRep_Tool::Tolerance(v))
                {
                  flag = 0;
                  break;
                }
                else
                  flag = 1;
              }
            }
            else
              flag = 1;
          }
          if (flag == 1)
          {
          }
        }
      }
    }
  }
}
