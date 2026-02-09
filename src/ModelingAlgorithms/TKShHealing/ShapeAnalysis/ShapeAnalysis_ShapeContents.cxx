#include <BRep_Tool.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_OffsetCurve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_ElementarySurface.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <ShapeAnalysis_ShapeContents.hpp>
#include <ShapeAnalysis_Wire.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

ShapeAnalysis_ShapeContents::ShapeAnalysis_ShapeContents()
{
  myBigSplineSec     = new NCollection_HSequence<TopoDS_Shape>;
  myIndirectSec      = new NCollection_HSequence<TopoDS_Shape>;
  myOffsetSurfaceSec = new NCollection_HSequence<TopoDS_Shape>;
  myTrimmed3dSec     = new NCollection_HSequence<TopoDS_Shape>;
  myOffsetCurveSec   = new NCollection_HSequence<TopoDS_Shape>;
  myTrimmed2dSec     = new NCollection_HSequence<TopoDS_Shape>;
  ClearFlags();
}

void ShapeAnalysis_ShapeContents::Clear()
{
  myNbSolids           = 0;
  myNbShells           = 0;
  myNbFaces            = 0;
  myNbWires            = 0;
  myNbEdges            = 0;
  myNbVertices         = 0;
  myNbSolidsWithVoids  = 0;
  myNbBigSplines       = 0;
  myNbC0Surfaces       = 0;
  myNbC0Curves         = 0;
  myNbOffsetSurf       = 0;
  myNbIndirectSurf     = 0;
  myNbOffsetCurves     = 0;
  myNbTrimmedCurve2d   = 0;
  myNbTrimmedCurve3d   = 0;
  myNbBSplibeSurf      = 0;
  myNbBezierSurf       = 0;
  myNbTrimSurf         = 0;
  myNbWireWitnSeam     = 0;
  myNbWireWithSevSeams = 0;
  myNbFaceWithSevWires = 0;
  myNbNoPCurve         = 0;
  myNbFreeFaces        = 0;
  myNbFreeWires        = 0;
  myNbFreeEdges        = 0;

  myNbSharedSolids    = 0;
  myNbSharedShells    = 0;
  myNbSharedFaces     = 0;
  myNbSharedWires     = 0;
  myNbSharedFreeWires = 0;
  myNbSharedFreeEdges = 0;
  myNbSharedEdges     = 0;
  myNbSharedVertices  = 0;

  myBigSplineSec->Clear();
  myIndirectSec->Clear();
  myOffsetSurfaceSec->Clear();
  myTrimmed3dSec->Clear();
  myOffsetCurveSec->Clear();
  myTrimmed2dSec->Clear();
}

void ShapeAnalysis_ShapeContents::ClearFlags()
{
  myBigSplineMode     = false;
  myIndirectMode      = false;
  myOffsetSurfaceMode = false;
  myTrimmed3dMode     = false;
  myOffsetCurveMode   = false;
  myTrimmed2dMode     = false;
}

void ShapeAnalysis_ShapeContents::Perform(const TopoDS_Shape& Shape)
{
  Clear();

  TopExp_Explorer                                        exp;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapsh;

  for (exp.Init(Shape, TopAbs_SOLID); exp.More(); exp.Next())
  {
    TopoDS_Solid sol = TopoDS::Solid(exp.Current());
    sol.Location(TopLoc_Location());
    mapsh.Add(sol);
    int nbs = 0;
    for (TopExp_Explorer shel(sol, TopAbs_SHELL); shel.More(); shel.Next())
      nbs++;
    if (nbs > 1)
      myNbSolidsWithVoids++;
    myNbSolids++;
  }
  myNbSharedSolids = mapsh.Extent();

  mapsh.Clear();
  int nbfaceshell = 0;
  for (exp.Init(Shape, TopAbs_SHELL); exp.More(); exp.Next())
  {
    myNbShells++;
    TopoDS_Shell she = TopoDS::Shell(exp.Current());
    she.Location(TopLoc_Location());
    mapsh.Add(she);
    for (TopExp_Explorer shel(she, TopAbs_FACE); shel.More(); shel.Next())
      nbfaceshell++;
  }
  myNbSharedShells = mapsh.Extent();

  mapsh.Clear();
  for (exp.Init(Shape, TopAbs_FACE); exp.More(); exp.Next())
  {
    TopoDS_Face face = TopoDS::Face(exp.Current());
    myNbFaces++;
    TopLoc_Location           loc;
    occ::handle<Geom_Surface> surf = BRep_Tool::Surface(face, loc);
    face.Location(TopLoc_Location());
    mapsh.Add(face);
    occ::handle<Geom_RectangularTrimmedSurface> trsu =
      occ::down_cast<Geom_RectangularTrimmedSurface>(surf);
    if (!trsu.IsNull())
    {
      myNbTrimSurf++;
      surf = trsu->BasisSurface();
    }

    if (!surf.IsNull() && !(surf->IsCNu(1) && surf->IsCNv(1)))
    {
      myNbC0Surfaces++;
    }

    occ::handle<Geom_BSplineSurface> bsps = occ::down_cast<Geom_BSplineSurface>(surf);
    if (!bsps.IsNull())
    {
      myNbBSplibeSurf++;
      if (bsps->NbUPoles() * bsps->NbVPoles() > 8192)
      {
        myNbBigSplines++;
        if (myBigSplineMode)
          myBigSplineSec->Append(face);
      }
    }
    occ::handle<Geom_ElementarySurface> els = occ::down_cast<Geom_ElementarySurface>(surf);
    if (!els.IsNull())
    {
      if (!els->Position().Direct())
      {
        myNbIndirectSurf++;
        if (myIndirectMode)
          myIndirectSec->Append(face);
      }
    }
    if (surf->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
    {
      myNbOffsetSurf++;
      if (myOffsetSurfaceMode)
        myOffsetSurfaceSec->Append(face);
    }
    else if (surf->IsKind(STANDARD_TYPE(Geom_BezierSurface)))
    {
      myNbBezierSurf++;
    }

    int maxseam = 0, nbwires = 0;
    for (TopExp_Explorer wires(face, TopAbs_WIRE); wires.More(); wires.Next())
    {
      TopoDS_Wire wire   = TopoDS::Wire(wires.Current());
      int         nbseam = 0;
      nbwires++;
      for (TopExp_Explorer edg(wire, TopAbs_EDGE); edg.More(); edg.Next())
      {
        TopoDS_Edge edge = TopoDS::Edge(edg.Current());
        double      first, last;
        if (BRep_Tool::IsClosed(edge, face))
          nbseam++;
        occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(edge, first, last);
        if (!c3d.IsNull())
        {
          if (c3d->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
          {
            myNbTrimmedCurve3d++;
            if (myTrimmed3dMode)
              myTrimmed3dSec->Append(face);
          }
        }
        occ::handle<Geom2d_Curve> c2d = BRep_Tool::CurveOnSurface(edge, face, first, last);
        if (c2d.IsNull())
          myNbNoPCurve++;
        else if (c2d->IsKind(STANDARD_TYPE(Geom2d_OffsetCurve)))
        {
          myNbOffsetCurves++;
          if (myOffsetCurveMode)
            myOffsetCurveSec->Append(face);
        }
        else if (c2d->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve)))
        {
          myNbTrimmedCurve2d++;
          if (myTrimmed2dMode)
            myTrimmed2dSec->Append(face);
        }
      }
      if (nbseam > maxseam)
        maxseam = nbseam;
    }
    if (maxseam == 1)
      myNbWireWitnSeam++;
    else if (maxseam > 1)
      myNbWireWithSevSeams++;
    if (nbwires > 1)
      myNbFaceWithSevWires++;
  }
  myNbSharedFaces = mapsh.Extent();

  mapsh.Clear();
  for (exp.Init(Shape, TopAbs_WIRE); exp.More(); exp.Next())
  {
    TopoDS_Wire wire = TopoDS::Wire(exp.Current());
    wire.Location(TopLoc_Location());
    mapsh.Add(wire);
    myNbWires++;
  }
  myNbSharedWires = mapsh.Extent();

  myNbFreeFaces = myNbFaces - nbfaceshell;

  mapsh.Clear();
  for (exp.Init(Shape, TopAbs_EDGE); exp.More(); exp.Next())
  {
    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
    edge.Location(TopLoc_Location());
    mapsh.Add(edge);
    TopLoc_Location loc;
    double          first, last;
    myNbEdges++;
    occ::handle<Geom_Curve> c3d = BRep_Tool::Curve(edge, loc, first, last);
    if (!c3d.IsNull() && c3d->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
    {
      myNbOffsetCurves++;
      if (myOffsetCurveMode)
        myOffsetCurveSec->Append(edge);
    }
    if (!c3d.IsNull() && !c3d->IsCN(1))
      myNbC0Curves++;
  }
  myNbSharedEdges = mapsh.Extent();

  mapsh.Clear();
  for (exp.Init(Shape, TopAbs_VERTEX); exp.More(); exp.Next())
  {
    TopoDS_Vertex vert = TopoDS::Vertex(exp.Current());
    vert.Location(TopLoc_Location());
    myNbVertices++;
    mapsh.Add(vert);
  }
  myNbSharedVertices = mapsh.Extent();

  mapsh.Clear();
  for (exp.Init(Shape, TopAbs_EDGE, TopAbs_FACE); exp.More(); exp.Next())
  {
    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
    edge.Location(TopLoc_Location());
    myNbFreeEdges++;
    mapsh.Add(edge);
  }
  myNbSharedFreeEdges = mapsh.Extent();

  mapsh.Clear();
  for (exp.Init(Shape, TopAbs_WIRE, TopAbs_FACE); exp.More(); exp.Next())
  {
    TopoDS_Wire wire = TopoDS::Wire(exp.Current());
    wire.Location(TopLoc_Location());
    myNbFreeWires++;
    mapsh.Add(wire);
  }
  myNbSharedFreeWires = mapsh.Extent();
}
