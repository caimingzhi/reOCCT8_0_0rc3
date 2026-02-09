#include <BRep_Builder.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepLib.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <BRepOffsetAPI_DraftAngle.hpp>
#include <BRepTools.hpp>
#include <BRepTools_Substitution.hpp>
#include <Draft_Modification.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <Precision.hpp>
#include <Standard_NullObject.hpp>
#include <gp_Pnt.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>

#include <Geom2dInt_GInter.hpp>
#include <IntRes2d_IntersectionPoint.hpp>

BRepOffsetAPI_DraftAngle::BRepOffsetAPI_DraftAngle() = default;

BRepOffsetAPI_DraftAngle::BRepOffsetAPI_DraftAngle(const TopoDS_Shape& S)
{
  myInitialShape = S;
  myModification = new Draft_Modification(S);
}

void BRepOffsetAPI_DraftAngle::Clear()
{
  if (!myModification.IsNull())
  {
    occ::down_cast<Draft_Modification>(myModification)->Clear();
  }
}

void BRepOffsetAPI_DraftAngle::Init(const TopoDS_Shape& S)
{
  myInitialShape = S;
  NotDone();
  if (!myModification.IsNull())
  {
    occ::down_cast<Draft_Modification>(myModification)->Init(S);
  }
  else
  {
    myModification = new Draft_Modification(S);
  }
}

void BRepOffsetAPI_DraftAngle::Add(const TopoDS_Face& F,
                                   const gp_Dir&      D,
                                   const double       Angle,
                                   const gp_Pln&      Plane,
                                   const bool         Flag)
{

  if (std::abs(Angle) <= 1.e-04)
    return;
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),
                               "BRepOffsetAPI_DraftAngle::Add() - initial shape is not set");
  occ::down_cast<Draft_Modification>(myModification)->Add(F, D, Angle, Plane, Flag);
}

bool BRepOffsetAPI_DraftAngle::AddDone() const
{
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),
                               "BRepOffsetAPI_DraftAngle::AddDone() - initial shape is not set");
  return occ::down_cast<Draft_Modification>(myModification)->ProblematicShape().IsNull();
}

void BRepOffsetAPI_DraftAngle::Remove(const TopoDS_Face& F)
{
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),
                               "BRepOffsetAPI_DraftAngle::Remove() - initial shape is not set");
  occ::down_cast<Draft_Modification>(myModification)->Remove(F);
}

const TopoDS_Shape& BRepOffsetAPI_DraftAngle::ProblematicShape() const
{
  Standard_NullObject_Raise_if(
    myInitialShape.IsNull(),
    "BRepOffsetAPI_DraftAngle::ProblematicShape() - initial shape is not set");
  return occ::down_cast<Draft_Modification>(myModification)->ProblematicShape();
}

Draft_ErrorStatus BRepOffsetAPI_DraftAngle::Status() const
{
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),
                               "BRepOffsetAPI_DraftAngle::Status() - initial shape is not set");
  return occ::down_cast<Draft_Modification>(myModification)->Error();
}

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_DraftAngle::ConnectedFaces(
  const TopoDS_Face& F) const
{
  Standard_NullObject_Raise_if(
    myInitialShape.IsNull(),
    "BRepOffsetAPI_DraftAngle::ConnectedFaces() - initial shape is not set");
  return occ::down_cast<Draft_Modification>(myModification)->ConnectedFaces(F);
}

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_DraftAngle::ModifiedFaces() const
{
  Standard_NullObject_Raise_if(
    myInitialShape.IsNull(),
    "BRepOffsetAPI_DraftAngle::ModifiedFaces() - initial shape is not set");
  return occ::down_cast<Draft_Modification>(myModification)->ModifiedFaces();
}

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_DraftAngle::Generated(const TopoDS_Shape& S)
{
  myGenerated.Clear();
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),
                               "BRepOffsetAPI_DraftAngle::Generated() - initial shape is not set");
  occ::handle<Draft_Modification> DMod = occ::down_cast<Draft_Modification>(myModification);

  if (S.ShapeType() == TopAbs_FACE)
  {
    occ::handle<Geom_Surface> Surf;
    TopLoc_Location           L;
    double                    Tol;
    bool                      RW, RF;
    if (DMod->NewSurface(TopoDS::Face(S), Surf, L, Tol, RW, RF))
    {
      if (myVtxToReplace.IsEmpty())
      {
        myGenerated.Append(ModifiedShape(S));
      }
      else
      {
        myGenerated.Append(mySubs.Value(ModifiedShape(S)));
      }
    }
  }
  return myGenerated;
}

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_DraftAngle::Modified(const TopoDS_Shape& S)
{
  myGenerated.Clear();
  Standard_NullObject_Raise_if(myInitialShape.IsNull(),
                               "BRepOffsetAPI_DraftAngle::Modified() - initial shape is not set");
  occ::handle<Draft_Modification> DMod = occ::down_cast<Draft_Modification>(myModification);

  if (S.ShapeType() == TopAbs_FACE)
  {
    occ::handle<Geom_Surface> Surf;
    TopLoc_Location           L;
    double                    Tol;
    bool                      RW, RF;

    if (!DMod->NewSurface(TopoDS::Face(S), Surf, L, Tol, RW, RF))
    {

      if (myVtxToReplace.IsEmpty())
      {
        myGenerated.Append(ModifiedShape(S));
      }
      else
      {
        myGenerated.Append(mySubs.Value(ModifiedShape(S)));
      }
      if (myGenerated.Extent() == 1 && myGenerated.First().IsSame(S))
      {
        myGenerated.Clear();
      }
    }
  }
  return myGenerated;
}

TopoDS_Shape BRepOffsetAPI_DraftAngle::ModifiedShape(const TopoDS_Shape& S) const
{
  if (S.ShapeType() == TopAbs_VERTEX)
  {
    if (myVtxToReplace.IsBound(S))
    {
      return myVtxToReplace(S);
    }
  }
  if (myVtxToReplace.IsEmpty())
  {
    return myModifier.ModifiedShape(S);
  }
  else
  {
    const TopoDS_Shape& aNS = myModifier.ModifiedShape(S);
    return mySubs.Value(aNS);
  }
}

void BRepOffsetAPI_DraftAngle::Build(const Message_ProgressRange&)
{
  occ::down_cast<Draft_Modification>(myModification)->Perform();
  if (!occ::down_cast<Draft_Modification>(myModification)->IsDone())
  {
    NotDone();
  }
  else
  {
    DoModif(myInitialShape);
    CorrectWires();
    CorrectVertexTol();
  }
}

void BRepOffsetAPI_DraftAngle::CorrectWires()
{
  double TolInter = 1.e-7;
  int    i, j, k;

  NCollection_Sequence<TopoDS_Shape> Eseq;
  NCollection_Sequence<TopoDS_Shape> Wseq;
  NCollection_Sequence<TopoDS_Shape> Fseq;
  TopoDS_Shape                       CurEdge, CurWire, CurFace;
  TopoDS_Iterator                    wit, eit;

  TopExp_Explorer fexp(myShape, TopAbs_FACE);
  for (; fexp.More(); fexp.Next())
  {
    CurFace = fexp.Current();
    wit.Initialize(CurFace);
    for (; wit.More(); wit.Next())
    {
      CurWire = wit.Value();
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> emap;
      eit.Initialize(CurWire);
      for (; eit.More(); eit.Next())
        emap.Add(eit.Value());
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator mapit(emap);
      for (; mapit.More(); mapit.Next())
      {
        CurEdge = mapit.Key();
        if (BRepTools::IsReallyClosed(TopoDS::Edge(CurEdge), TopoDS::Face(CurFace)))
        {
          Eseq.Append(CurEdge);
          Wseq.Append(CurWire);
          Fseq.Append(CurFace);
        }
      }
    }
  }

  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<double>, TopTools_ShapeMapHasher> Emap;

  NCollection_Sequence<TopoDS_Shape>                       NonSeam;
  NCollection_Sequence<TopoDS_Shape>                       NonSeamWires;
  NCollection_Sequence<NCollection_Sequence<double>>       ParsNonSeam;
  NCollection_Sequence<NCollection_Sequence<TopoDS_Shape>> Seam;
  NCollection_Sequence<NCollection_Sequence<double>>       ParsSeam;

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>                   WFmap;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> WWmap;
  for (i = 1; i <= Eseq.Length(); i++)
  {
    CurEdge = Eseq(i);
    CurWire = Wseq(i);
    CurFace = Fseq(i);

    const TopoDS_Face& aFace = TopoDS::Face(CurFace);

    BRepAdaptor_Curve2d aBAC2D1(TopoDS::Edge(CurEdge), aFace);
    BRepAdaptor_Curve2d aBAC2D1R(TopoDS::Edge(CurEdge.Reversed()), aFace);

    TopLoc_Location                  aLoc;
    const occ::handle<Geom_Surface>& aSurf = BRep_Tool::Surface(aFace, aLoc);

    double aTolCurE = BRep_Tool::Tolerance(TopoDS::Edge(CurEdge));

    wit.Initialize(CurFace);
    for (; wit.More(); wit.Next())
    {
      const TopoDS_Shape& aWire = wit.Value();
      if (!aWire.IsSame(CurWire))
      {
        NCollection_Sequence<gp_Pnt> pts;
        bool                         Wadd = false;
        eit.Initialize(aWire);
        for (; eit.More(); eit.Next())
        {
          const TopoDS_Edge& anEdge = TopoDS::Edge(eit.Value());

          BRepAdaptor_Curve2d aBAC2D2(anEdge, aFace);

          Geom2dInt_GInter aGInter;
          aGInter.Perform(aBAC2D1, aBAC2D2, TolInter, TolInter);
          if (!aGInter.IsDone() || aGInter.IsEmpty())
          {

            aGInter.Perform(aBAC2D1R, aBAC2D2, TolInter, TolInter);
            if (!aGInter.IsDone() || aGInter.IsEmpty())
            {
              continue;
            }
          }

          Wadd = true;
          if (!WFmap.IsBound(aWire))
            WFmap.Bind(aWire, CurFace);
          int ind = 0;
          for (j = 1; j <= NonSeam.Length(); j++)
          {
            if (anEdge.IsSame(NonSeam(j)))
            {
              ind = j;
              break;
            }
          }
          if (ind == 0)
          {
            NonSeam.Append(anEdge);
            NonSeamWires.Append(aWire);
            ind = NonSeam.Length();
            NCollection_Sequence<double>       emptyseq1, emptyseq2;
            NCollection_Sequence<TopoDS_Shape> emptyedgeseq;
            ParsNonSeam.Append(emptyseq1);
            Seam.Append(emptyedgeseq);
            ParsSeam.Append(emptyseq2);
          }
          if (!Emap.IsBound(CurEdge))
          {
            NCollection_Sequence<double> emptyseq;
            Emap.Bind(CurEdge, emptyseq);
          }

          double aTolE = BRep_Tool::Tolerance(anEdge);

          double aTolCmp = std::max(aTolCurE, aTolE);

          int aNbIntPnt = aGInter.NbPoints();
          for (k = 1; k <= aNbIntPnt; ++k)
          {
            const IntRes2d_IntersectionPoint& aP2DInt = aGInter.Point(k);
            const gp_Pnt2d&                   aP2D    = aP2DInt.Value();
            gp_Pnt                            aP3D    = aSurf->Value(aP2D.X(), aP2D.Y());

            int ied = 0;
            for (j = 1; j <= pts.Length(); j++)
            {
              if (aP3D.IsEqual(pts(j), aTolCmp))
              {
                ied = j;
                break;
              }
            }
            if (ied == 0)
            {
              pts.Append(aP3D);
              Emap(CurEdge).Append(aP2DInt.ParamOnFirst());
              ParsNonSeam(ind).Append(aP2DInt.ParamOnSecond());
              Seam(ind).Append(CurEdge);
              ParsSeam(ind).Append(aP2DInt.ParamOnFirst());
            }
          }
        }
        if (Wadd)
        {
          if (!WWmap.IsBound(CurWire))
          {
            NCollection_List<TopoDS_Shape> emptylist;
            WWmap.Bind(CurWire, emptylist);
          }
          WWmap(CurWire).Append(aWire);
        }
      }
    }
  }

  for (i = 1; i <= NonSeam.Length(); i++)
  {
    for (j = 1; j < ParsNonSeam(i).Length(); j++)
    {
      for (k = j + 1; k <= ParsNonSeam(i).Length(); k++)
      {
        if (ParsNonSeam(i)(k) < ParsNonSeam(i)(j))
        {
          double temp       = ParsNonSeam(i)(j);
          ParsNonSeam(i)(j) = ParsNonSeam(i)(k);
          ParsNonSeam(i)(k) = temp;
          TopoDS_Shape tmp  = Seam(i)(j);
          Seam(i)(j)        = Seam(i)(k);
          Seam(i)(k)        = tmp;
          temp              = ParsSeam(i)(j);
          ParsSeam(i)(j)    = ParsSeam(i)(k);
          ParsSeam(i)(k)    = temp;
        }
      }
    }
  }
  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<double>, TopTools_ShapeMapHasher>::Iterator
    iter(Emap);
  for (; iter.More(); iter.Next())
  {
    NCollection_Sequence<double> Seq = iter.Value();
    for (i = 1; i < Seq.Length(); i++)
    {
      for (j = i + 1; j <= Seq.Length(); j++)
      {
        if (Seq(j) < Seq(i))
        {
          double temp = Seq(i);
          Seq(i)      = Seq(j);
          Seq(j)      = temp;
        }
      }
    }
    Emap(iter.Key()) = Seq;
  }
  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<double>, TopTools_ShapeMapHasher> EPmap;
  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<TopoDS_Shape>, TopTools_ShapeMapHasher>
    EVmap;
  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<TopoDS_Shape>, TopTools_ShapeMapHasher>
    EWmap;
  iter.Initialize(Emap);
  for (; iter.More(); iter.Next())
  {
    NCollection_Sequence<double> parseq;
    EPmap.Bind(iter.Key(), parseq);
    NCollection_Sequence<TopoDS_Shape> shapeseq;
    EVmap.Bind(iter.Key(), shapeseq);
    NCollection_Sequence<TopoDS_Shape> shapeseq2;
    EWmap.Bind(iter.Key(), shapeseq2);
  }

  BRepTools_Substitution aSub;
  BRep_Builder           BB;
  for (i = 1; i <= NonSeam.Length(); i++)
  {
    TopoDS_Edge                    anEdge = TopoDS::Edge(NonSeam(i));
    NCollection_List<TopoDS_Shape> NewEdges;
    TopoDS_Edge                    NewE;
    TopoDS_Vertex                  Vfirst, Vlast;
    TopExp::Vertices(anEdge, Vfirst, Vlast);
    double par, FirstPar, LastPar;
    BRep_Tool::Range(anEdge, FirstPar, LastPar);
    int firstind         = 1;
    par                  = ParsNonSeam(i)(1);
    TopoDS_Edge SeamEdge = TopoDS::Edge(Seam(i)(1));

    for (j = 1; j <= Eseq.Length(); j++)
      if (SeamEdge.IsSame(Eseq(j)))
        break;
    TopoDS_Face               theFace = TopoDS::Face(Fseq(j));
    TopLoc_Location           L;
    occ::handle<Geom_Surface> theSurf = BRep_Tool::Surface(theFace, L);
    if (std::abs(par - FirstPar) <= Precision::Confusion())
    {
      BB.UpdateVertex(Vfirst, ParsSeam(i)(1), SeamEdge, BRep_Tool::Tolerance(Vfirst));
      EPmap(SeamEdge).Append(ParsSeam(i)(1));
      EVmap(SeamEdge).Append(Vfirst);
      EWmap(SeamEdge).Append(NonSeamWires(i));
      firstind = 2;
    }
    double        prevpar = FirstPar;
    TopoDS_Vertex PrevV   = Vfirst;
    for (j = firstind; j <= ParsNonSeam(i).Length(); j++)
    {
      TopoDS_Shape aLocalShape = anEdge.EmptyCopied();
      NewE                     = TopoDS::Edge(aLocalShape);

      TopoDS_Vertex NewV;
      par = ParsNonSeam(i)(j);
      BB.Range(NewE, prevpar, par);
      SeamEdge = TopoDS::Edge(Seam(i)(j));
      if (j == ParsNonSeam(i).Length() && std::abs(par - LastPar) <= Precision::Confusion())
      {
        NewV = Vlast;
        if (firstind == 2 && j == 2)
        {
          BB.UpdateVertex(Vlast, ParsSeam(i)(j), SeamEdge, BRep_Tool::Tolerance(Vlast));
          EPmap(SeamEdge).Append(ParsSeam(i)(j));
          EVmap(SeamEdge).Append(Vlast);
          EWmap(SeamEdge).Append(NonSeamWires(i));
          break;
        }
      }
      else
      {
        BRepAdaptor_Curve bcur(NewE);
        gp_Pnt            Point = bcur.Value(par);
        NewV                    = BRepLib_MakeVertex(Point);
        BB.UpdateVertex(NewV, par, NewE, 10. * Precision::Confusion());
      }
      BB.UpdateVertex(NewV, ParsSeam(i)(j), SeamEdge, 10. * Precision::Confusion());
      NewE.Orientation(TopAbs_FORWARD);
      BB.Add(NewE, PrevV.Oriented(TopAbs_FORWARD));
      BB.Add(NewE, NewV.Oriented(TopAbs_REVERSED));

      NewEdges.Append(NewE);
      EPmap(SeamEdge).Append(ParsSeam(i)(j));
      EVmap(SeamEdge).Append(NewV);
      EWmap(SeamEdge).Append(NonSeamWires(i));

      prevpar = par;
      PrevV   = NewV;
    }

    TopoDS_Shape aLocalShape = anEdge.EmptyCopied();
    NewE                     = TopoDS::Edge(aLocalShape);

    par = LastPar;
    if (std::abs(prevpar - par) > Precision::Confusion())
    {
      BB.Range(NewE, prevpar, par);
      NewE.Orientation(TopAbs_FORWARD);
      BB.Add(NewE, PrevV.Oriented(TopAbs_FORWARD));
      BB.Add(NewE, Vlast.Oriented(TopAbs_REVERSED));
      NewEdges.Append(NewE);
    }

    aSub.Substitute(anEdge, NewEdges);
  }

  iter.Initialize(EPmap);
  for (; iter.More(); iter.Next())
  {
    NCollection_Sequence<double> Seq;
    Seq = iter.Value();
    NCollection_Sequence<TopoDS_Shape> SeqShape;
    SeqShape = EVmap(iter.Key());
    NCollection_Sequence<TopoDS_Shape> SeqShape2;
    SeqShape2 = EWmap(iter.Key());
    for (i = 1; i < Seq.Length(); i++)
    {
      for (j = i + 1; j <= Seq.Length(); j++)
      {
        if (Seq(j) < Seq(i))
        {
          double temp      = Seq(i);
          Seq(i)           = Seq(j);
          Seq(j)           = temp;
          TopoDS_Shape tmp = SeqShape(i);
          SeqShape(i)      = SeqShape(j);
          SeqShape(j)      = tmp;
          tmp              = SeqShape2(i);
          SeqShape2(i)     = SeqShape2(j);
          SeqShape2(j)     = tmp;
        }
      }
    }

    EPmap(iter.Key()) = Seq;
    EVmap(iter.Key()) = SeqShape;
    EWmap(iter.Key()) = SeqShape2;
  }
  iter.Initialize(EPmap);
  for (; iter.More(); iter.Next())
  {
    NCollection_Sequence<double> Seq;
    Seq = iter.Value();
    NCollection_Sequence<TopoDS_Shape> SeqShape;
    SeqShape = EVmap(iter.Key());
    NCollection_Sequence<TopoDS_Shape> SeqShape2;
    SeqShape2   = EWmap(iter.Key());
    bool remove = true;
    while (remove)
    {
      remove = false;
      for (i = 1; i < Seq.Length(); i++)
      {
        if (std::abs(Seq(i) - Seq(i + 1)) <= Precision::Confusion())
        {
          Seq.Remove(i + 1);
          SeqShape.Remove(i + 1);
          SeqShape2.Remove(i + 1);
          remove = true;
        }
      }
    }
    EPmap(iter.Key()) = Seq;
    EVmap(iter.Key()) = SeqShape;
    EWmap(iter.Key()) = SeqShape2;
  }

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> VEmap;
  iter.Initialize(Emap);
  for (; iter.More(); iter.Next())
  {
    TopoDS_Edge                    anEdge   = TopoDS::Edge(iter.Key());
    bool                           onepoint = false;
    NCollection_List<TopoDS_Shape> NewEdges;
    NCollection_Sequence<double>   Seq;
    Seq = iter.Value();
    NCollection_Sequence<double> Seq2;
    Seq2 = EPmap(anEdge);
    NCollection_Sequence<TopoDS_Shape> SeqVer;
    SeqVer = EVmap(anEdge);
    NCollection_Sequence<TopoDS_Shape> SeqWire;
    SeqWire = EWmap(anEdge);
    TopoDS_Vertex Vfirst, Vlast;
    TopExp::Vertices(anEdge, Vfirst, Vlast);
    double fpar, lpar, FirstPar, LastPar;
    BRep_Tool::Range(anEdge, FirstPar, LastPar);
    fpar = FirstPar;
    lpar = Seq(1);
    TopoDS_Edge NewE;
    int         firstind = 1;
    if (std::abs(fpar - lpar) <= Precision::Confusion())
    {
      firstind = 2;
      fpar     = Seq(1);
      lpar     = Seq(2);
    }
    else
    {
      if (Seq.Length() % 2 != 0)
      {
        VEmap.Bind(Vfirst, anEdge);
        firstind = 2;
        fpar     = Seq(1);
        if (Seq.Length() > 2)
          lpar = Seq(2);
        else
          onepoint = true;
      }
    }
    if (!onepoint)
    {
      TopoDS_Shape aLocalShape = anEdge.EmptyCopied();
      NewE                     = TopoDS::Edge(aLocalShape);

      BB.Range(NewE, fpar, lpar);
      NewE.Orientation(TopAbs_FORWARD);
      if (firstind == 1)
      {
        BB.Add(NewE, Vfirst.Oriented(TopAbs_FORWARD));
        aLocalShape = SeqVer(1).Oriented(TopAbs_REVERSED);
        BB.Add(NewE, TopoDS::Vertex(aLocalShape));
      }
      else
      {
        aLocalShape = SeqVer(1).Oriented(TopAbs_FORWARD);
        BB.Add(NewE, TopoDS::Vertex(aLocalShape));
        aLocalShape = SeqVer(2).Oriented(TopAbs_REVERSED);
        BB.Add(NewE, TopoDS::Vertex(aLocalShape));
      }
      NewEdges.Append(NewE);

      firstind++;
      for (i = firstind; i < Seq.Length(); i += 2)
      {
        aLocalShape = anEdge.EmptyCopied();
        NewE        = TopoDS::Edge(aLocalShape);

        fpar = Seq(i);
        lpar = Seq(i + 1);
        BB.Range(NewE, fpar, lpar);

        for (j = 1; j <= Seq2.Length(); j++)
        {
          if (std::abs(fpar - Seq2(j)) <= Precision::Confusion())
          {
            break;
          }
        }
        NewE.Orientation(TopAbs_FORWARD);
        TopoDS_Shape aLocalShapeCur = SeqVer(j).Oriented(TopAbs_FORWARD);
        BB.Add(NewE, TopoDS::Vertex(aLocalShapeCur));
        aLocalShapeCur = SeqVer(j + 1).Oriented(TopAbs_REVERSED);
        BB.Add(NewE, TopoDS::Vertex(aLocalShapeCur));

        NewEdges.Append(NewE);
      }
    }

    i    = Seq.Length();
    fpar = Seq(i);
    lpar = LastPar;
    if (std::abs(fpar - lpar) <= Precision::Confusion())
      continue;
    TopoDS_Shape aLocalShape = anEdge.EmptyCopied();
    NewE                     = TopoDS::Edge(aLocalShape);

    BB.Range(NewE, fpar, lpar);
    NewE.Orientation(TopAbs_FORWARD);
    aLocalShape = SeqVer(SeqVer.Length()).Oriented(TopAbs_FORWARD);
    BB.Add(NewE, TopoDS::Vertex(aLocalShape));

    BB.Add(NewE, Vlast.Oriented(TopAbs_REVERSED));
    NewEdges.Append(NewE);

    aSub.Substitute(anEdge, NewEdges);
  }

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itve(VEmap);
  for (; itve.More(); itve.Next())
  {
    const TopoDS_Shape& V = itve.Key();
    const TopoDS_Shape& E = itve.Value();
    TopoDS_Shape        W;
    for (i = 1; i <= Eseq.Length(); i++)
    {
      if (E.IsSame(Eseq(i)))
      {
        W = Wseq(i);
        break;
      }
    }
    TopoDS_Shape Etoremove;
    eit.Initialize(W);
    for (; eit.More(); eit.Next())
    {
      TopoDS_Edge CurE = TopoDS::Edge(eit.Value());
      if (CurE.IsSame(E))
        continue;
      TopoDS_Vertex Vfirst, Vlast;
      TopExp::Vertices(CurE, Vfirst, Vlast);
      if (Vfirst.IsSame(V) || Vlast.IsSame(V))
      {
        Etoremove = CurE;
        break;
      }
    }
    if (!Etoremove.IsNull())
    {
      W.Free(true);
      BB.Remove(W, Etoremove);
    }
  }

  aSub.Build(myShape);
  if (aSub.IsCopied(myShape))
  {
    const NCollection_List<TopoDS_Shape>& listSh = aSub.Copy(myShape);
    if (!listSh.IsEmpty())
      myShape = listSh.First();
  }

  NCollection_List<TopoDS_Shape> theCopy;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator itww(WWmap);
  for (; itww.More(); itww.Next())
  {
    CurWire = itww.Key();
    theCopy = aSub.Copy(CurWire);
    CurWire = theCopy.First();
    CurWire.Free(true);
    NCollection_List<TopoDS_Shape>::Iterator itl(itww.Value());
    for (; itl.More(); itl.Next())
    {
      TopoDS_Shape aWire = itl.Value();
      CurFace            = WFmap(aWire);
      theCopy            = aSub.Copy(aWire);
      aWire              = theCopy.First();

      TopLoc_Location           L;
      occ::handle<Geom_Surface> theSurf = BRep_Tool::Surface(TopoDS::Face(CurFace), L);
      eit.Initialize(aWire);
      for (; eit.More(); eit.Next())
      {
        TopoDS_Edge anEdge = TopoDS::Edge(eit.Value());
        gp_Pnt2d    Pfirst, Plast, Pmid;
        BRep_Tool::UVPoints(anEdge, TopoDS::Face(CurFace), Pfirst, Plast);
        BRepAdaptor_Curve2d bc2d(anEdge, TopoDS::Face(CurFace));
        Pmid = bc2d.Value((bc2d.FirstParameter() + bc2d.LastParameter()) / 2.);
        gp_Vec2d offset;
        bool     translate = false;
        if (Pfirst.X() - 2. * M_PI > Precision::Confusion()
            || Plast.X() - 2. * M_PI > Precision::Confusion()
            || Pmid.X() - 2. * M_PI > Precision::Confusion())
        {
          offset.SetCoord(-2. * M_PI, 0);
          translate = true;
        }
        if (Pfirst.X() < -Precision::Confusion() || Plast.X() < -Precision::Confusion()
            || Pmid.X() < -Precision::Confusion())
        {
          offset.SetCoord(2. * M_PI, 0);
          translate = true;
        }
        if (translate)
        {
          const occ::handle<BRep_TEdge>& TE = *((occ::handle<BRep_TEdge>*)&anEdge.TShape());
          NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(
            TE->ChangeCurves());
          occ::handle<BRep_GCurve> GC;

          for (; itcr.More(); itcr.Next())
          {
            GC = occ::down_cast<BRep_GCurve>(itcr.Value());
            if (!GC.IsNull() && GC->IsCurveOnSurface(theSurf, L))
            {
              occ::handle<Geom2d_Curve> PC = GC->PCurve();
              PC                           = occ::down_cast<Geom2d_Curve>(PC->Translated(offset));
              GC->PCurve(PC);
              TE->ChangeCurves().Remove(itcr);
              TE->ChangeCurves().Append(GC);
              break;
            }
          }
        }
      }

      eit.Initialize(aWire, false);
      for (; eit.More(); eit.Next())
      {
        const TopoDS_Shape& anEdge = eit.Value();
        BB.Add(CurWire, anEdge);
      }
      if (aSub.IsCopied(CurFace))
      {
        theCopy = aSub.Copy(CurFace);
        CurFace = theCopy.First();
      }
      CurFace.Free(true);
      BB.Remove(CurFace, aWire);
    }
  }
}

void BRepOffsetAPI_DraftAngle::CorrectVertexTol()
{
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> anInitVertices, anInitEdges, aNewEdges;
  TopExp_Explorer                                        anExp(myInitialShape, TopAbs_EDGE);
  for (; anExp.More(); anExp.Next())
  {
    anInitEdges.Add(anExp.Current());
    TopoDS_Iterator anIter(anExp.Current());
    for (; anIter.More(); anIter.Next())
    {
      anInitVertices.Add(anIter.Value());
    }
  }

  BRep_Builder aBB;
  myVtxToReplace.Clear();
  anExp.Init(myShape, TopAbs_EDGE);
  for (; anExp.More(); anExp.Next())
  {
    const TopoDS_Shape& anE = anExp.Current();

    if (anInitEdges.Contains(anE))
      continue;

    if (aNewEdges.Contains(anE))
      continue;

    aNewEdges.Add(anE);

    double          anETol = BRep_Tool::Tolerance(TopoDS::Edge(anE));
    TopoDS_Iterator anIter(anE);
    for (; anIter.More(); anIter.Next())
    {
      const TopoDS_Vertex& aVtx = TopoDS::Vertex(anIter.Value());
      if (anInitVertices.Contains(aVtx))
      {
        if (myVtxToReplace.IsBound(aVtx))
        {
          aBB.UpdateVertex(TopoDS::Vertex(myVtxToReplace(aVtx)), anETol + Epsilon(anETol));
        }
        else
        {
          double aVTol = BRep_Tool::Tolerance(aVtx);
          if (aVTol < anETol)
          {
            TopoDS_Vertex aNewVtx;
            gp_Pnt        aVPnt = BRep_Tool::Pnt(aVtx);
            aBB.MakeVertex(aNewVtx, aVPnt, anETol + Epsilon(anETol));
            aNewVtx.Orientation(aVtx.Orientation());
            myVtxToReplace.Bind(aVtx, aNewVtx);
          }
        }
      }
      else
      {
        aBB.UpdateVertex(aVtx, anETol + Epsilon(anETol));
      }
    }
  }

  if (myVtxToReplace.IsEmpty())
  {
    return;
  }

  mySubs.Clear();
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator anIter(
    myVtxToReplace);
  for (; anIter.More(); anIter.Next())
  {
    mySubs.Replace(anIter.Key(), anIter.Value());
  }
  mySubs.Apply(myShape);
  myShape = mySubs.Value(myShape);
}
