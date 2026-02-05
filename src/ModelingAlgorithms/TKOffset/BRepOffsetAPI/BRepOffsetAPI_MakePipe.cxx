#include <BRepOffsetAPI_MakePipe.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>

//=================================================================================================

BRepOffsetAPI_MakePipe::BRepOffsetAPI_MakePipe(const TopoDS_Wire&  Spine,
                                               const TopoDS_Shape& Profile)
    : myPipe(Spine, Profile)
{
  Build();
}

//=======================================================================
// function : BRepOffsetAPI_MakePipe
// purpose  : constructor
//           Set the mode of sweeping
//           It can be:
//           - Frenet
//           - Corrected Frenet
//           - Discrete Trihedron
//           Also set the flag that indicates attempt to approximate
//           a C1-continuous surface if a swept surface proved
//           to be C0.
//=======================================================================

BRepOffsetAPI_MakePipe::BRepOffsetAPI_MakePipe(const TopoDS_Wire&       Spine,
                                               const TopoDS_Shape&      Profile,
                                               const GeomFill_Trihedron aMode,
                                               const bool               ForceApproxC1)
    : myPipe(Spine, Profile, aMode, ForceApproxC1)
{
  Build();
}

//=================================================================================================

const BRepFill_Pipe& BRepOffsetAPI_MakePipe::Pipe() const
{
  return myPipe;
}

//=================================================================================================

void BRepOffsetAPI_MakePipe::Build(const Message_ProgressRange& /*theRange*/)
{
  myShape = myPipe.Shape();
  // Check for emptiness of result
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> theMap;
  TopExp::MapShapes(myShape, theMap);
  if (theMap.Extent() == 1)
    NotDone();
  else
    Done();
}

//=================================================================================================

TopoDS_Shape BRepOffsetAPI_MakePipe::FirstShape()
{
  return myPipe.FirstShape();
}

//=================================================================================================

TopoDS_Shape BRepOffsetAPI_MakePipe::LastShape()
{
  return myPipe.LastShape();
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_MakePipe::Generated(const TopoDS_Shape& S)
{
  myPipe.Generated(S, myGenerated);
  return myGenerated;
}

//=======================================================================
// function : Generated
// purpose  : returns generated elementary subshape
//=======================================================================

TopoDS_Shape BRepOffsetAPI_MakePipe::Generated(const TopoDS_Shape& SSpine,
                                               const TopoDS_Shape& SProfile)
{
  if (SProfile.ShapeType() == TopAbs_EDGE)
  {
    return myPipe.Face(TopoDS::Edge(SSpine), TopoDS::Edge(SProfile));
  }
  else if (SProfile.ShapeType() == TopAbs_VERTEX)
  {
    return myPipe.Edge(TopoDS::Edge(SSpine), TopoDS::Vertex(SProfile));
  }

  // POP pour NT
  TopoDS_Shape bid;
  return bid;
}

//=================================================================================================

double BRepOffsetAPI_MakePipe::ErrorOnSurface() const
{
  return myPipe.ErrorOnSurface();
}
