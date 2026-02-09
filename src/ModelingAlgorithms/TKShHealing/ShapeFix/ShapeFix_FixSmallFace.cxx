

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepLib.hpp>
#include <ElCLib.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomLib.hpp>
#include <gp_Dir.hpp>
#include <gp_Vec.hpp>
#include <Message_Msg.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeFix_Edge.hpp>
#include <ShapeFix_FixSmallFace.hpp>
#include <ShapeFix_Shape.hpp>
#include <ShapeFix_Wire.hpp>
#include <Standard_Type.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Builder.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeFix_FixSmallFace, ShapeFix_Root)

ShapeFix_FixSmallFace::ShapeFix_FixSmallFace()
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  SetPrecision(Precision::Confusion());
}

void ShapeFix_FixSmallFace::Init(const TopoDS_Shape& S)
{
  myShape = S;
  if (Context().IsNull())
    SetContext(new ShapeBuild_ReShape);
  myResult = myShape;
  Context()->Apply(myShape);
}

void ShapeFix_FixSmallFace::Perform()
{
  FixSpotFace();
  FixStripFace();
}

TopoDS_Shape ShapeFix_FixSmallFace::FixSpotFace()
{

  bool             done = false;
  TopAbs_ShapeEnum st   = myShape.ShapeType();
  if (st == TopAbs_COMPOUND || st == TopAbs_COMPSOLID || st == TopAbs_SOLID || st == TopAbs_SHELL
      || st == TopAbs_FACE)
  {
    for (TopExp_Explorer itf(myShape, TopAbs_FACE); itf.More(); itf.Next())
    {

      TopoDS_Shape tmpFace = Context()->Apply(itf.Current());
      TopoDS_Face  F       = TopoDS::Face(tmpFace);
      if (F.IsNull())
        continue;
      if (myAnalyzer.CheckSpotFace(F, Precision()))
      {
        ReplaceVerticesInCaseOfSpot(F, Precision());
        RemoveFacesInCaseOfSpot(F);
        myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
        done     = true;
      }
    }
    myShape                        = Context()->Apply(myShape);
    occ::handle<ShapeFix_Wire> sfw = new ShapeFix_Wire;
    if (done)
    {
      if (myShape.IsNull())
        return myShape;

      myShape = FixShape();
    }

    myResult = myShape;
  }
  return myShape;
}

bool ShapeFix_FixSmallFace::ReplaceVerticesInCaseOfSpot(TopoDS_Face& F, const double) const
{

  NCollection_Sequence<gp_XYZ> thePositions;
  gp_XYZ                       thePosition;
  BRep_Builder                 theBuilder;
  double                       theMaxDev;
  double                       theMaxTol = 0.0;
  thePositions.Clear();
  gp_Pnt thePoint;

  TopoDS_Shape tmpFace = Context()->Apply(F);
  F                    = TopoDS::Face(tmpFace);

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

  for (TopExp_Explorer iter_vertex(F, TopAbs_VERTEX); iter_vertex.More(); iter_vertex.Next())
  {
    TopoDS_Vertex V = TopoDS::Vertex(iter_vertex.Current());
    thePoint        = BRep_Tool::Pnt(V);
    if (theMaxTol <= (BRep_Tool::Tolerance(V)))
      theMaxTol = BRep_Tool::Tolerance(V);
    thePositions.Append(thePoint.XYZ());
  }

  thePosition  = gp_XYZ(0., 0., 0.);
  int theNbPos = thePositions.Length();
  int i;
  for (i = 1; i <= theNbPos; i++)
    thePosition += thePositions.Value(i);
  if (theNbPos > 1)
    thePosition /= theNbPos;

  theMaxDev = 0.;
  for (i = 1; i <= theNbPos; i++)
  {
    double theDeviation = (thePosition - thePositions.Value(i)).Modulus();
    if (theDeviation > theMaxDev)
      theMaxDev = theDeviation;
  }
  theMaxDev *= 1.00001;

  TopoDS_Vertex theSharedVertex;
  theBuilder.MakeVertex(theSharedVertex);
  theBuilder.UpdateVertex(theSharedVertex, gp_Pnt(thePosition), theMaxDev + theMaxTol / 2);

  TopoDS_Vertex theNewVertex;
  for (TopExp_Explorer iter_vert(F, TopAbs_VERTEX); iter_vert.More(); iter_vert.Next())
  {
    TopoDS_Vertex V = TopoDS::Vertex(iter_vert.Current());
    if (V.Orientation() == TopAbs_FORWARD)

    {
      TopoDS_Shape tmpVertexFwd = theSharedVertex.Oriented(TopAbs_FORWARD);
      theNewVertex              = TopoDS::Vertex(tmpVertexFwd);
    }
    else

    {
      TopoDS_Shape tmpVertexRev = theSharedVertex.Oriented(TopAbs_REVERSED);
      theNewVertex              = TopoDS::Vertex(tmpVertexRev);
    }
    Context()->Replace(V, theNewVertex);
  }
  return true;
}

bool ShapeFix_FixSmallFace::RemoveFacesInCaseOfSpot(const TopoDS_Face& F) const
{
  for (TopExp_Explorer iter_vert(F, TopAbs_EDGE); iter_vert.More(); iter_vert.Next())
  {
    TopoDS_Edge Ed = TopoDS::Edge(iter_vert.Current());
    Context()->Remove(Ed);
  }
  Context()->Remove(F);
  SendWarning(F, Message_Msg("FixAdvFace.FixSpotFace.MSG0"));
  return true;
}

TopoDS_Shape ShapeFix_FixSmallFace::FixStripFace(const bool wasdone)
{
  if (myShape.IsNull())
    return myShape;
  TopAbs_ShapeEnum st = myShape.ShapeType();

  bool done = wasdone;
  if (st == TopAbs_COMPOUND || st == TopAbs_COMPSOLID || st == TopAbs_SOLID || st == TopAbs_SHELL
      || st == TopAbs_FACE)
  {
    for (TopExp_Explorer itf(myShape, TopAbs_FACE); itf.More(); itf.Next())
    {
      TopoDS_Face F = TopoDS::Face(itf.Current());

      TopoDS_Shape tmpFace = Context()->Apply(F);
      F                    = TopoDS::Face(tmpFace);
      if (F.IsNull())
        continue;

      TopoDS_Edge E1, E2;
      if (myAnalyzer.CheckStripFace(F, E1, E2, Precision()))
      {
        if (ReplaceInCaseOfStrip(F, E1, E2, Precision()))
          RemoveFacesInCaseOfStrip(F);
        myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
        done     = true;
      }
    }
    myShape = Context()->Apply(myShape);

    if (!myShape.IsNull())
    {
      for (TopExp_Explorer exp_s(myShape, TopAbs_SHELL); exp_s.More(); exp_s.Next())
      {
        TopoDS_Shell    Sh = TopoDS::Shell(exp_s.Current());
        TopExp_Explorer ex_sh(Sh, TopAbs_FACE);
        if (!ex_sh.More())
        {
          Context()->Remove(Sh);
        }
      }
      myShape = Context()->Apply(myShape);

      if (done)
      {
        if (myShape.IsNull())
          return myShape;
        TopoDS_Shape theResult;
        myShape = FixShape();

        myResult = myShape;
      }
    }
  }
  return myShape;
}

bool ShapeFix_FixSmallFace::ReplaceInCaseOfStrip(TopoDS_Face& F,
                                                 TopoDS_Edge& E1,
                                                 TopoDS_Edge& E2,
                                                 const double tol) const
{
  if (E1.IsNull() || E2.IsNull())
    return false;
  TopoDS_Edge theSharedEdge;
  TopoDS_Face F1, F2;

  TopoDS_Shape tmpFace = Context()->Apply(F);
  F                    = TopoDS::Face(tmpFace);
  for (TopExp_Explorer expf(myShape, TopAbs_FACE); expf.More(); expf.Next())
  {

    TopoDS_Shape tmpShape = Context()->Apply(expf.Current());
    TopoDS_Face  tempF    = TopoDS::Face(tmpShape);
    if (tempF.IsNull() || tempF.IsSame(F))
      continue;
    for (TopExp_Explorer expe(tempF, TopAbs_EDGE); expe.More(); expe.Next())
    {
      TopoDS_Edge tempE = TopoDS::Edge(expe.Current());
      if (tempE.IsSame(E1))
        F1 = tempF;
      if (tempE.IsSame(E2))
        F2 = tempF;
      if (!F1.IsNull())
        break;
    }
  }

  if (F1.IsNull() && F2.IsNull())
    return true;
  TopoDS_Edge E1tmp = E1;
  TopoDS_Edge E2tmp = E2;
  if (F1.IsNull())
  {
    E1tmp = E2;
    E2tmp = E1;
    F1    = F2;
  }
  theSharedEdge = ComputeSharedEdgeForStripFace(F, E1tmp, E2tmp, F1, tol);

  if (theSharedEdge.IsNull())
    return false;
  if (E1.Orientation() == TopAbs_REVERSED)
  {
    Context()->Replace(E1tmp, theSharedEdge.Oriented(TopAbs_REVERSED));
    if (F.Orientation() == F1.Orientation())
      Context()->Replace(E2tmp, theSharedEdge);
    else
      Context()->Replace(E2tmp, theSharedEdge.Oriented(TopAbs_REVERSED));
  }
  else
  {
    Context()->Replace(E1tmp, theSharedEdge);
    if (F.Orientation() == F1.Orientation())
      Context()->Replace(E2tmp, theSharedEdge.Oriented(TopAbs_REVERSED));
    else
      Context()->Replace(E2tmp, theSharedEdge);
  }

  for (TopExp_Explorer exp_e(F, TopAbs_EDGE); exp_e.More(); exp_e.Next())
  {
    TopoDS_Edge shortedge = TopoDS::Edge(exp_e.Current());
    if (!shortedge.IsSame(E1tmp) && !shortedge.IsSame(E2tmp))
      Context()->Remove(shortedge);
  }

  return true;
}

bool ShapeFix_FixSmallFace::RemoveFacesInCaseOfStrip(const TopoDS_Face& F) const
{
  Context()->Remove(F);
  SendWarning(F, Message_Msg("FixAdvFace.FixStripFace.MSG0"));
  return true;
}

TopoDS_Edge ShapeFix_FixSmallFace::ComputeSharedEdgeForStripFace(const TopoDS_Face&,
                                                                 const TopoDS_Edge& E1,
                                                                 const TopoDS_Edge& E2,
                                                                 const TopoDS_Face& F1,
                                                                 const double       tol) const
{

  BRep_Builder theBuilder;

  TopoDS_Edge   theNewEdge;
  TopoDS_Vertex V1, V2, V3, V4;
  TopExp::Vertices(E1, V1, V2);
  TopExp::Vertices(E2, V3, V4);
  gp_Pnt p1, p2;
  double dev;
  p1  = BRep_Tool::Pnt(V1);
  p2  = BRep_Tool::Pnt(V3);
  dev = p1.Distance(p2);
  TopoDS_Vertex theFirstVer;
  TopoDS_Vertex theSecondVer;
  theBuilder.MakeVertex(theFirstVer);
  theBuilder.MakeVertex(theSecondVer);
  gp_XYZ       thePosition;
  TopoDS_Shape temp;

  if ((dev <= BRep_Tool::Tolerance(V1)) || (dev <= BRep_Tool::Tolerance(V3)) || (dev <= tol))
  {
    if (V1.IsSame(V3))

      theFirstVer = V1;

    else
    {
      dev         = (dev / 2) * 1.0001;
      thePosition = (p1.XYZ() + p2.XYZ()) / 2;
      theBuilder.UpdateVertex(theFirstVer, gp_Pnt(thePosition), dev);

      if (V1.Orientation() == TopAbs_FORWARD)
        Context()->Replace(V1, theFirstVer.Oriented(TopAbs_FORWARD));
      else
        Context()->Replace(V1, theFirstVer.Oriented(TopAbs_REVERSED));
      if (V3.Orientation() == TopAbs_FORWARD)
        Context()->Replace(V3, theFirstVer.Oriented(TopAbs_FORWARD));
      else
        Context()->Replace(V3, theFirstVer.Oriented(TopAbs_REVERSED));
    }
    if (V1.IsSame(V2) || V3.IsSame(V4))
      theSecondVer = theFirstVer;
    else
    {
      if (!V2.IsSame(V4))
      {

        p1          = BRep_Tool::Pnt(V2);
        p2          = BRep_Tool::Pnt(V4);
        dev         = p1.Distance(p2);
        thePosition = (p1.XYZ() + p2.XYZ()) / 2;
        theBuilder.UpdateVertex(theSecondVer, gp_Pnt(thePosition), dev);
      }
      else
        theSecondVer = V2;
    }
    if (!V2.IsSame(theSecondVer))
    {
      if (V2.Orientation() == TopAbs_FORWARD)
        Context()->Replace(V2, theSecondVer.Oriented(TopAbs_FORWARD));
      else
        Context()->Replace(V2, theSecondVer.Oriented(TopAbs_REVERSED));
      if (V4.Orientation() == TopAbs_FORWARD)
        Context()->Replace(V4, theSecondVer.Oriented(TopAbs_FORWARD));
      else
        Context()->Replace(V4, theSecondVer.Oriented(TopAbs_REVERSED));
    }
  }
  else
  {
    p2  = BRep_Tool::Pnt(V4);
    dev = p1.Distance(p2);
    if ((dev <= BRep_Tool::Tolerance(V1)) || (dev <= BRep_Tool::Tolerance(V4)) || (dev <= tol))
    {
      if (V1.IsSame(V4))

        theFirstVer = V1;

      else
      {
        dev         = (dev / 2) * 1.0001;
        thePosition = (p1.XYZ() + p2.XYZ()) / 2;
        theBuilder.UpdateVertex(theFirstVer, gp_Pnt(thePosition), dev);

        if (V1.Orientation() == TopAbs_FORWARD)
          Context()->Replace(V1, theFirstVer.Oriented(TopAbs_FORWARD));
        else
          Context()->Replace(V1, theFirstVer.Oriented(TopAbs_REVERSED));
        if (V4.Orientation() == TopAbs_FORWARD)
          Context()->Replace(V4, theFirstVer.Oriented(TopAbs_FORWARD));
        else
          Context()->Replace(V4, theFirstVer.Oriented(TopAbs_REVERSED));
      }
      if (V1.IsSame(V2) || V3.IsSame(V4))
        theSecondVer = theFirstVer;
      else
      {

        if (!V2.IsSame(V3))
        {
          p1          = BRep_Tool::Pnt(V2);
          p2          = BRep_Tool::Pnt(V3);
          dev         = p1.Distance(p2);
          thePosition = (p1.XYZ() + p2.XYZ()) / 2;
          theBuilder.UpdateVertex(theSecondVer, gp_Pnt(thePosition), dev);
        }
        else
          theSecondVer = V2;
      }

      if (!V2.IsSame(theSecondVer))
      {
        if (V2.Orientation() == TopAbs_FORWARD)
          Context()->Replace(V2, theSecondVer.Oriented(TopAbs_FORWARD));
        else
          Context()->Replace(V2, theSecondVer.Oriented(TopAbs_REVERSED));
        if (V3.Orientation() == TopAbs_FORWARD)
          Context()->Replace(V3, theSecondVer.Oriented(TopAbs_FORWARD));
        else
          Context()->Replace(V3, theSecondVer.Oriented(TopAbs_REVERSED));
      }
    }
    else
    {
#ifdef OCCT_DEBUG
      std::cout << "The face is not strip face" << std::endl;
#endif
      return theNewEdge;
    }
  }
  if (theFirstVer.IsNull() || theSecondVer.IsNull())
    return theNewEdge;

  theBuilder.MakeEdge(theNewEdge);
  double                  f, l, fp1, lp1;
  TopLoc_Location         loc;
  occ::handle<Geom_Curve> the3dcurve;
  the3dcurve = BRep_Tool::Curve(E1, f, l);
  occ::handle<Geom2d_Curve> the2dcurve1, the2dcurve2, thenew1, thenew2;
  if (!F1.IsNull())
  {
    the2dcurve1 = BRep_Tool::CurveOnSurface(E1, F1, fp1, lp1);
    if (!the2dcurve1.IsNull() && fp1 != f && lp1 != l)
      GeomLib::SameRange(Precision::Confusion(), the2dcurve1, fp1, lp1, f, l, thenew1);
  }

  double maxdev;
  if ((BRep_Tool::Tolerance(theFirstVer)) <= (BRep_Tool::Tolerance(theSecondVer)))
    maxdev = (BRep_Tool::Tolerance(theSecondVer));
  else
    maxdev = (BRep_Tool::Tolerance(theFirstVer));
  theBuilder.UpdateVertex(theFirstVer, maxdev);
  theBuilder.UpdateVertex(theSecondVer, maxdev);

  theBuilder.SameParameter(theNewEdge, false);
  the3dcurve = BRep_Tool::Curve(E1, f, l);
  theBuilder.UpdateEdge(theNewEdge, the3dcurve, maxdev);
  theBuilder.Range(theNewEdge, f, l);
  if (!F1.IsNull() && !thenew1.IsNull())
  {
    theBuilder.UpdateEdge(theNewEdge, thenew1, F1, maxdev);
  }

  theBuilder.Add(theNewEdge, theFirstVer.Oriented(TopAbs_FORWARD));
  theBuilder.Add(theNewEdge, theSecondVer.Oriented(TopAbs_REVERSED));

  return theNewEdge;
}

TopoDS_Shape ShapeFix_FixSmallFace::FixSplitFace(const TopoDS_Shape&)
{
  if (myShape.IsNull())
    return myShape;
  TopAbs_ShapeEnum st   = myShape.ShapeType();
  bool             done = false;
  TopoDS_Compound  theSplittedFaces;
  BRep_Builder     theBuilder;
  if (st == TopAbs_COMPOUND || st == TopAbs_COMPSOLID || st == TopAbs_SOLID || st == TopAbs_SHELL
      || st == TopAbs_FACE)
  {
    for (TopExp_Explorer itf(myShape, TopAbs_FACE); itf.More(); itf.Next())
    {
      TopoDS_Face     F = TopoDS::Face(itf.Current());
      TopoDS_Compound CompSplittedFaces;
      theBuilder.MakeCompound(CompSplittedFaces);
      if (SplitOneFace(F, CompSplittedFaces))
      {
        done = true;
        Context()->Replace(F, CompSplittedFaces);
      }
    }
  }
  if (done)
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
  myShape  = Context()->Apply(myShape);
  myResult = myShape;
  return myShape;
}

bool ShapeFix_FixSmallFace::SplitOneFace(TopoDS_Face& F, TopoDS_Compound& theSplittedFaces)
{
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                                       MapEdges;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<double>, TopTools_ShapeMapHasher> MapParam;
  TopoDS_Compound                                                                      theAllVert;
  BRep_Builder                                                                         theBuilder;
  theBuilder.MakeCompound(theAllVert);

  TopoDS_Shape tmpShape = Context()->Apply(F);
  F                     = TopoDS::Face(tmpShape);
  if (myAnalyzer.CheckSplittingVertices(F, MapEdges, MapParam, theAllVert) != 0)
  {
    TopoDS_Wire tempwire;

    if (theAllVert.IsNull())
      return false;

    TopoDS_Vertex   V;
    TopExp_Explorer itc(theAllVert, TopAbs_VERTEX);
    V = TopoDS::Vertex(itc.Current());
    if (V.IsNull())
      return false;
    gp_Pnt        proj;
    gp_Pnt        vp = BRep_Tool::Pnt(V);
    TopoDS_Vertex theNewVertex;
    TopoDS_Edge   E;
    TopoDS_Edge   theFirstEdge, theSecondEdge;

    {

      ShapeAnalysis_Curve SAC;
      for (TopExp_Explorer ite(F, TopAbs_EDGE); ite.More(); ite.Next())
      {
        E = TopoDS::Edge(ite.Current());
        TopoDS_Vertex V1, V2;
        TopExp::Vertices(E, V1, V2);
        double                  cf, cl;
        occ::handle<Geom_Curve> C3D = BRep_Tool::Curve(E, cf, cl);
        if (C3D.IsNull())
          continue;
        if (V.IsSame(V1) || V.IsSame(V2))
          continue;
        double vt = BRep_Tool::Tolerance(V);
        double param;
        double dist = SAC.Project(C3D, vp, vt * 10., proj, param, cf, cl);
        if (dist == 0)
          continue;
        if (dist <= vt)
        {
          theBuilder.MakeVertex(theNewVertex);
          theBuilder.UpdateVertex(theNewVertex, proj, Precision::Confusion());
          theBuilder.MakeEdge(theFirstEdge);
          theBuilder.MakeEdge(theSecondEdge);
          double                  f, l;
          occ::handle<Geom_Curve> the3dcurve = BRep_Tool::Curve(E, f, l);
          theBuilder.UpdateEdge(theFirstEdge, the3dcurve, Precision::Confusion());
          theBuilder.UpdateEdge(theSecondEdge, the3dcurve, Precision::Confusion());
          if (V1.Orientation() == TopAbs_FORWARD)
          {
            theBuilder.Add(theFirstEdge, V1);
            theBuilder.Add(theFirstEdge, theNewVertex.Oriented(TopAbs_REVERSED));
            theBuilder.Add(theSecondEdge, theNewVertex.Oriented(TopAbs_FORWARD));
            theBuilder.Add(theSecondEdge, V2);
          }
          else
          {
            theBuilder.Add(theFirstEdge, V2);
            theBuilder.Add(theFirstEdge, theNewVertex.Oriented(TopAbs_REVERSED));
            theBuilder.Add(theSecondEdge, theNewVertex.Oriented(TopAbs_FORWARD));
            theBuilder.Add(theSecondEdge, V1);
          }
          theBuilder.Range(theFirstEdge, cf, param);
          theBuilder.Range(theSecondEdge, param, cl);

          TopoDS_Wire twoedges;
          theBuilder.MakeWire(twoedges);
          if (E.Orientation() == TopAbs_FORWARD)
          {
            theBuilder.Add(twoedges, theFirstEdge.Oriented(TopAbs_FORWARD));
            theBuilder.Add(twoedges, theSecondEdge.Oriented(TopAbs_FORWARD));
          }
          else
          {
            theBuilder.Add(twoedges, theFirstEdge.Oriented(TopAbs_REVERSED));
            theBuilder.Add(twoedges, theSecondEdge.Oriented(TopAbs_REVERSED));
          }
          Context()->Replace(E, twoedges);
          break;
        }
      }
      if (theNewVertex.IsNull())
        return false;

      TopoDS_Edge             theSplitEdge;
      gp_Lin                  lin(vp, gp_Dir(gp_Vec(vp, proj)));
      double                  firstparam = ElCLib::Parameter(lin, vp);
      double                  lastparam  = ElCLib::Parameter(lin, proj);
      occ::handle<Geom_Line>  L          = new Geom_Line(vp, gp_Vec(vp, proj));
      occ::handle<Geom_Curve> the3dc     = L;
      theBuilder.MakeEdge(theSplitEdge, the3dc, Precision::Confusion());
      theBuilder.Add(theSplitEdge, V.Oriented(TopAbs_FORWARD));
      theBuilder.Add(theSplitEdge, theNewVertex.Oriented(TopAbs_REVERSED));
      theBuilder.Range(theSplitEdge, firstparam, lastparam);

      occ::handle<ShapeFix_Edge> sfe = new ShapeFix_Edge;
      sfe->FixAddPCurve(theSplitEdge, F, false);

      TopoDS_Wire wireonface;

      TopExp_Explorer itw(F, TopAbs_WIRE);
      wireonface = TopoDS::Wire(itw.Current());
      itw.Next();
      if (itw.More())
        return false;
      occ::handle<ShapeFix_Wire> sfw = new ShapeFix_Wire;
      sfw->Init(wireonface, F, Precision::Confusion());
      sfw->FixReorder();
      wireonface = sfw->Wire();

      TopoDS_Wire w1, w2;
      theBuilder.MakeWire(w1);
      theBuilder.MakeWire(w2);
      theBuilder.MakeWire(tempwire);
      for (TopExp_Explorer itnew(wireonface, TopAbs_EDGE); itnew.More(); itnew.Next())
      {
        TopoDS_Edge ce = TopoDS::Edge(itnew.Current());
        if (ce.IsSame(E))
        {
          theBuilder.Remove(wireonface, ce);
          theBuilder.Add(wireonface, theFirstEdge.Oriented(TopAbs_FORWARD));
          theBuilder.Add(wireonface, theSecondEdge.Oriented(TopAbs_FORWARD));
        }
      }
      sfw->Init(wireonface, F, Precision::Confusion());
      sfw->FixReorder();
      wireonface = sfw->Wire();

      for (TopExp_Explorer itere(wireonface, TopAbs_EDGE); itere.More(); itere.Next())
      {
        TopoDS_Edge   ce = TopoDS::Edge(itere.Current());
        TopoDS_Vertex thecontrol;
        if (ce.Orientation() == TopAbs_FORWARD)
          thecontrol = TopExp::LastVertex(ce);
        else
          thecontrol = TopExp::FirstVertex(ce);
        theBuilder.Add(w1, ce);
        if (thecontrol.IsSame(V))
        {
          theBuilder.Add(w1, theSplitEdge.Oriented(TopAbs_FORWARD));
          TopoDS_Wire wtemp = w1;
          w1                = w2;
          w2                = wtemp;
        }
        if (thecontrol.IsSame(theNewVertex))
        {
          theBuilder.Add(w1, theSplitEdge.Oriented(TopAbs_REVERSED));
          TopoDS_Wire wtemp = w1;
          w1                = w2;
          w2                = wtemp;
        }
      }
      if (w1.IsNull() || w2.IsNull())
        return false;

      TopoDS_Face F1;
      TopoDS_Face F2;
      theBuilder.MakeFace(F1, BRep_Tool::Surface(F), Precision::Confusion());
      theBuilder.MakeFace(F2, BRep_Tool::Surface(F), Precision::Confusion());
      theBuilder.Add(F1, w1);
      theBuilder.Add(F2, w2);
      TopoDS_Compound tf;
      theBuilder.MakeCompound(tf);
      theBuilder.Add(tf, F1);
      theBuilder.Add(tf, F2);

      if (!SplitOneFace(F1, theSplittedFaces))
        theBuilder.Add(theSplittedFaces, F1);
      if (!SplitOneFace(F2, theSplittedFaces))
        theBuilder.Add(theSplittedFaces, F2);
    }
    return true;
  }
  return false;
}

TopoDS_Face ShapeFix_FixSmallFace::FixFace(const TopoDS_Face& F)
{

  TopoDS_Shape emptyCopied  = F.EmptyCopied();
  TopoDS_Face  theFixedFace = TopoDS::Face(emptyCopied);

  occ::handle<ShapeFix_Face> sff = new ShapeFix_Face;
  sff->SetContext(Context());
  sff->Init(F);
  sff->Perform();

  theFixedFace = sff->Face();
  return theFixedFace;
}

TopoDS_Shape ShapeFix_FixSmallFace::FixShape()
{
  TopoDS_Shape FixSh;
  if (myShape.IsNull())
    return FixSh;

  for (TopExp_Explorer expf(myShape, TopAbs_FACE); expf.More(); expf.Next())
  {
    TopoDS_Face F = TopoDS::Face(expf.Current());

    TopoDS_Shape tmpFace = Context()->Apply(F);
    F                    = TopoDS::Face(tmpFace);
    TopoDS_Face newF     = FixFace(F);
    Context()->Replace(F, newF);
  }
  FixSh = Context()->Apply(myShape);
  return FixSh;
}

TopoDS_Shape ShapeFix_FixSmallFace::Shape()
{
  return myShape;
}

bool ShapeFix_FixSmallFace::FixPinFace(TopoDS_Face&)
{
  return true;
}
