#include <BRepOffsetAPI_NormalProjection.hpp>
#include <TopoDS_Shape.hpp>

BRepOffsetAPI_NormalProjection::BRepOffsetAPI_NormalProjection() = default;

BRepOffsetAPI_NormalProjection::BRepOffsetAPI_NormalProjection(const TopoDS_Shape& S)
{
  myNormalProjector.Init(S);
}

void BRepOffsetAPI_NormalProjection::Init(const TopoDS_Shape& S)
{
  myNormalProjector.Init(S);
}

void BRepOffsetAPI_NormalProjection::Add(const TopoDS_Shape& ToProj)
{
  myNormalProjector.Add(ToProj);
}

void BRepOffsetAPI_NormalProjection::SetParams(const double        Tol3D,
                                               const double        Tol2D,
                                               const GeomAbs_Shape InternalContinuity,
                                               const int           MaxDegree,
                                               const int           MaxSeg)
{
  myNormalProjector.SetParams(Tol3D, Tol2D, InternalContinuity, MaxDegree, MaxSeg);
}

void BRepOffsetAPI_NormalProjection::SetMaxDistance(const double MaxDist)
{
  myNormalProjector.SetMaxDistance(MaxDist);
}

void BRepOffsetAPI_NormalProjection::SetLimit(const bool FaceBounds)
{
  myNormalProjector.SetLimit(FaceBounds);
}

void BRepOffsetAPI_NormalProjection::Compute3d(const bool With3d)
{
  myNormalProjector.Compute3d(With3d);
}

void BRepOffsetAPI_NormalProjection::Build(const Message_ProgressRange&)
{
  myNormalProjector.Build();
  myShape = myNormalProjector.Projection();
  Done();
}

bool BRepOffsetAPI_NormalProjection::IsDone() const
{
  return myNormalProjector.IsDone();
}

const TopoDS_Shape& BRepOffsetAPI_NormalProjection::Couple(const TopoDS_Edge& E) const
{
  return myNormalProjector.Couple(E);
}

const NCollection_List<TopoDS_Shape>& BRepOffsetAPI_NormalProjection::Generated(
  const TopoDS_Shape& S)
{
  return myNormalProjector.Generated(S);
}

const TopoDS_Shape& BRepOffsetAPI_NormalProjection::Projection() const
{
  return myNormalProjector.Projection();
}

const TopoDS_Shape& BRepOffsetAPI_NormalProjection::Ancestor(const TopoDS_Edge& E) const
{
  return myNormalProjector.Ancestor(E);
}

bool BRepOffsetAPI_NormalProjection::BuildWire(NCollection_List<TopoDS_Shape>& ListOfWire) const
{
  return myNormalProjector.BuildWire(ListOfWire);
}
