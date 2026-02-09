#include <BRep_Builder.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <Precision.hpp>
#include <ShapeFix_EdgeConnect.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>

ShapeFix_EdgeConnect::ShapeFix_EdgeConnect() = default;

void ShapeFix_EdgeConnect::Add(const TopoDS_Edge& aFirst, const TopoDS_Edge& aSecond)
{

  TopoDS_Vertex theFirstVertex  = TopExp::LastVertex(aFirst, true);
  TopoDS_Vertex theSecondVertex = TopExp::FirstVertex(aSecond, true);

  if (myVertices.IsBound(theFirstVertex))
  {

    TopoDS_Vertex theFirstShared = TopoDS::Vertex(myVertices(theFirstVertex));
    if (myVertices.IsBound(theSecondVertex))
    {

      TopoDS_Vertex theSecondShared = TopoDS::Vertex(myVertices(theSecondVertex));
      if (!theFirstShared.IsSame(theSecondShared))
      {

        NCollection_List<TopoDS_Shape>& theFirstList  = myLists(theFirstShared);
        NCollection_List<TopoDS_Shape>& theSecondList = myLists(theSecondShared);
        for (NCollection_List<TopoDS_Shape>::Iterator theIterator(theSecondList);
             theIterator.More();
             theIterator.Next())
        {

          myVertices(theIterator.Value()) = theFirstShared;

          theIterator.Next();
        }

        theFirstList.Append(theSecondList);

        myLists.UnBind(theSecondShared);
      }
    }
    else
    {

      myVertices.Bind(theSecondVertex, theFirstShared);

      NCollection_List<TopoDS_Shape>& theFirstList = myLists(theFirstShared);
      theFirstList.Append(theSecondVertex);
      theFirstList.Append(aSecond);
    }
  }
  else
  {
    if (myVertices.IsBound(theSecondVertex))
    {

      TopoDS_Vertex& theSecondShared = TopoDS::Vertex(myVertices(theSecondVertex));

      myVertices.Bind(theFirstVertex, theSecondShared);

      NCollection_List<TopoDS_Shape>& theSecondList = myLists(theSecondShared);
      theSecondList.Append(theFirstVertex);
      theSecondList.Append(aFirst);
    }
    else
    {

      myVertices.Bind(theFirstVertex, theFirstVertex);
      myVertices.Bind(theSecondVertex, theFirstVertex);
      NCollection_List<TopoDS_Shape> theNewList;
      theNewList.Append(theFirstVertex);
      theNewList.Append(aFirst);
      theNewList.Append(theSecondVertex);
      theNewList.Append(aSecond);
      myLists.Bind(theFirstVertex, theNewList);
    }
  }
}

void ShapeFix_EdgeConnect::Add(const TopoDS_Shape& aShape)
{
  for (TopExp_Explorer expw(aShape, TopAbs_WIRE); expw.More(); expw.Next())
  {
    TopoDS_Wire     theWire = TopoDS::Wire(expw.Current());
    TopExp_Explorer expe(theWire, TopAbs_EDGE);
    if (expe.More())
    {

      TopoDS_Edge theEdge  = TopoDS::Edge(expe.Current());
      TopoDS_Edge theFirst = theEdge;
      expe.Next();
      for (; expe.More(); expe.Next())
      {

        TopoDS_Edge theNext = TopoDS::Edge(expe.Current());
        Add(theEdge, theNext);
        theEdge = theNext;
      }

      if (theWire.Closed())
        Add(theEdge, theFirst);
    }
  }
}

void ShapeFix_EdgeConnect::Build()
{
  NCollection_List<TopoDS_Shape>::Iterator                          theLIterator;
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator theCIterator;

  NCollection_Sequence<gp_XYZ> thePositions;
  gp_XYZ                       thePosition;
  double                       theMaxDev;
  BRep_Builder                 theBuilder;

  for (NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
         Iterator theSIterator(myLists);
       theSIterator.More();
       theSIterator.Next())
  {
    TopoDS_Vertex                         theSharedVertex = TopoDS::Vertex(theSIterator.Key());
    const NCollection_List<TopoDS_Shape>& theList         = theSIterator.Value();

    thePositions.Clear();

    for (theLIterator.Initialize(theList); theLIterator.More(); theLIterator.Next())
    {
      const TopoDS_Vertex& theVertex = TopoDS::Vertex(theLIterator.Value());
      theLIterator.Next();
      TopoDS_Edge& theEdge = TopoDS::Edge(theLIterator.ChangeValue());

      TopoDS_Vertex theStart, theEnd;
      theEdge.Orientation(TopAbs_FORWARD);
      TopExp::Vertices(theEdge, theStart, theEnd);
      bool use_start = (theVertex.IsSame(theStart));
      bool use_end   = (theVertex.IsSame(theEnd));

      for (theCIterator.Initialize(
             (*((occ::handle<BRep_TEdge>*)&theEdge.TShape()))->ChangeCurves());
           theCIterator.More();
           theCIterator.Next())
      {
        occ::handle<BRep_GCurve> GC = occ::down_cast<BRep_GCurve>(theCIterator.Value());
        if (GC.IsNull())
          continue;

        double theFParam, theLParam;
        GC->Range(theFParam, theLParam);
        gp_Pnt thePoint;
        if (use_start)
        {
          GC->D0(theFParam, thePoint);
          thePositions.Append(thePoint.XYZ());
        }
        if (use_end)
        {
          GC->D0(theLParam, thePoint);
          thePositions.Append(thePoint.XYZ());
        }
      }
    }

    int i, theNbPos = thePositions.Length();

    thePosition = gp_XYZ(0., 0., 0.);

#ifdef POSITION_USES_MEAN_POINT
  #undef POSITION_USES_MEAN_POINT
    for (i = 1; i <= theNbPos; i++)
      thePosition += thePositions.Value(i);
    if (theNbPos > 1)
      thePosition /= theNbPos;
#else
    gp_XYZ theLBound(0., 0., 0.), theRBound(0., 0., 0.);
    for (i = 1; i <= theNbPos; i++)
    {
      thePosition = thePositions.Value(i);
      if (i == 1)
        theLBound = theRBound = thePosition;
      double val = thePosition.X();
      if (val < theLBound.X())
        theLBound.SetX(val);
      else if (val > theRBound.X())
        theRBound.SetX(val);
      val = thePosition.Y();
      if (val < theLBound.Y())
        theLBound.SetY(val);
      else if (val > theRBound.Y())
        theRBound.SetY(val);
      val = thePosition.Z();
      if (val < theLBound.Z())
        theLBound.SetZ(val);
      else if (val > theRBound.Z())
        theRBound.SetZ(val);
    }
    if (theNbPos > 1)
      thePosition = (theLBound + theRBound) / 2.;
#endif

    theMaxDev = 0.;

    for (i = 1; i <= theNbPos; i++)
    {
      double theDeviation = (thePosition - thePositions.Value(i)).Modulus();
      if (theDeviation > theMaxDev)
        theMaxDev = theDeviation;
    }
    theMaxDev *= 1.0001;
    if (theMaxDev < Precision::Confusion())
      theMaxDev = Precision::Confusion();

    theBuilder.UpdateVertex(theSharedVertex, gp_Pnt(thePosition), theMaxDev);

    for (theLIterator.Initialize(theList); theLIterator.More(); theLIterator.Next())
    {
      const TopoDS_Vertex& theVertex = TopoDS::Vertex(theLIterator.Value());
      theLIterator.Next();
      TopoDS_Edge& theEdge = TopoDS::Edge(theLIterator.ChangeValue());

      TopoDS_Vertex theStart, theEnd;
      theEdge.Orientation(TopAbs_FORWARD);
      TopExp::Vertices(theEdge, theStart, theEnd);
      bool use_start = (theVertex.IsSame(theStart));
      bool use_end   = (theVertex.IsSame(theEnd));

      TopoDS_Vertex theOldVertex;
      if (use_start)
        theOldVertex = theStart;
      else
        theOldVertex = theEnd;

      TopoDS_Vertex theNewVertex;

      if (use_start)
      {
        TopoDS_Shape tmpshapeFwd = theSharedVertex.Oriented(TopAbs_FORWARD);
        theNewVertex             = TopoDS::Vertex(tmpshapeFwd);
      }
      else
      {
        TopoDS_Shape tmpshapeRev = theSharedVertex.Oriented(TopAbs_REVERSED);
        theNewVertex             = TopoDS::Vertex(tmpshapeRev);
      }
      if (!theOldVertex.IsSame(theNewVertex))
      {

        bool freeflag = theEdge.Free();
        theEdge.Free(true);
        theBuilder.Remove(theEdge, theOldVertex);
        theBuilder.Add(theEdge, theNewVertex);
        if (use_start && use_end)
        {

          theBuilder.Remove(theEdge, theOldVertex.Oriented(TopAbs_REVERSED));
          theBuilder.Add(theEdge, theNewVertex.Oriented(TopAbs_REVERSED));
        }
        theEdge.Free(freeflag);
      }
    }
  }

  Clear();
}

void ShapeFix_EdgeConnect::Clear()
{
  myVertices.Clear();
  myLists.Clear();
}
