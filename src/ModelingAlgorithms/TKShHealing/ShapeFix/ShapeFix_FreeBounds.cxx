#include <BRep_Builder.hpp>
#include <ShapeAnalysis_FreeBounds.hpp>
#include <ShapeExtend_Explorer.hpp>
#include <ShapeFix_FreeBounds.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>

//=================================================================================================

ShapeFix_FreeBounds::ShapeFix_FreeBounds()
    : myShared(false),
      mySewToler(0.0),
      myCloseToler(0.0),
      mySplitClosed(false),
      mySplitOpen(false)
{
}

//=================================================================================================

ShapeFix_FreeBounds::ShapeFix_FreeBounds(const TopoDS_Shape& shape,
                                         const double        sewtoler,
                                         const double        closetoler,
                                         const bool          splitclosed,
                                         const bool          splitopen)
    : myShared(false),
      mySewToler(sewtoler),
      myCloseToler(closetoler),
      mySplitClosed(splitclosed),
      mySplitOpen(splitopen)
{
  myShape = shape;
  Perform();
}

//=================================================================================================

ShapeFix_FreeBounds::ShapeFix_FreeBounds(const TopoDS_Shape& shape,
                                         const double        closetoler,
                                         const bool          splitclosed,
                                         const bool          splitopen)
    : myShared(true),
      mySewToler(0.),
      myCloseToler(closetoler),
      mySplitClosed(splitclosed),
      mySplitOpen(splitopen)
{
  myShape = shape;
  Perform();
}

//=================================================================================================

bool ShapeFix_FreeBounds::Perform()
{
  ShapeAnalysis_FreeBounds safb;
  if (myShared)
    safb = ShapeAnalysis_FreeBounds(myShape, mySplitClosed, mySplitOpen);
  else
    safb = ShapeAnalysis_FreeBounds(myShape, mySewToler, mySplitClosed, mySplitOpen);

  myWires = safb.GetClosedWires();
  myEdges = safb.GetOpenWires();

  if (myCloseToler > mySewToler)
  {
    ShapeExtend_Explorer                             see;
    occ::handle<NCollection_HSequence<TopoDS_Shape>> newwires,
      open = see.SeqFromCompound(myEdges, false);
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> vertices;
    ShapeAnalysis_FreeBounds::ConnectWiresToWires(open, myCloseToler, myShared, newwires, vertices);
    myEdges.Nullify();
    ShapeAnalysis_FreeBounds::DispatchWires(newwires, myWires, myEdges);

    for (TopExp_Explorer exp(myShape, TopAbs_EDGE); exp.More(); exp.Next())
    {
      TopoDS_Edge Edge = TopoDS::Edge(exp.Current());
      for (TopoDS_Iterator iter(Edge); iter.More(); iter.Next())
      {
        TopoDS_Vertex V = TopoDS::Vertex(iter.Value());
        BRep_Builder  B;
        TopoDS_Vertex newV;
        if (vertices.IsBound(V))
        {
          newV = TopoDS::Vertex(vertices.Find(V));
          newV.Orientation(V.Orientation());
          B.Remove(Edge, V);
          B.Add(Edge, newV);
        }
      }
    }
  }
  return true;
}
