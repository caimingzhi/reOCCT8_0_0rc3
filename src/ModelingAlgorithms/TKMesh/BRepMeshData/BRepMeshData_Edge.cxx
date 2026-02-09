#include <BRepMeshData_Edge.hpp>
#include <BRepMeshData_PCurve.hpp>
#include <BRepMeshData_Curve.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMeshData_Edge, IMeshData_Edge)

BRepMeshData_Edge::BRepMeshData_Edge(const TopoDS_Edge&                           theEdge,
                                     const occ::handle<NCollection_IncAllocator>& theAllocator)
    : IMeshData_Edge(theEdge),
      myAllocator(theAllocator),
      myPCurves(256, myAllocator),
      myPCurvesMap(1, myAllocator)
{
  SetCurve(IMeshData::ICurveHandle(new (myAllocator) BRepMeshData_Curve(myAllocator)));
}

BRepMeshData_Edge::~BRepMeshData_Edge() = default;

int BRepMeshData_Edge::PCurvesNb() const
{
  return myPCurves.Size();
}

const IMeshData::IPCurveHandle& BRepMeshData_Edge::AddPCurve(
  const IMeshData::IFacePtr& theDFace,
  const TopAbs_Orientation   theOrientation)
{
  const int aPCurveIndex = PCurvesNb();

  IMeshData::IPCurveHandle aPCurve(new (myAllocator)
                                     BRepMeshData_PCurve(theDFace, theOrientation, myAllocator));
  myPCurves.Append(aPCurve);

  if (!myPCurvesMap.IsBound(theDFace))
  {
    myPCurvesMap.Bind(theDFace, IMeshData::ListOfInteger(myAllocator));
  }

  IMeshData::ListOfInteger& aListOfPCurves = myPCurvesMap.ChangeFind(theDFace);
  aListOfPCurves.Append(aPCurveIndex);

  return GetPCurve(aPCurveIndex);
}

const IMeshData::IPCurveHandle& BRepMeshData_Edge::GetPCurve(
  const IMeshData::IFacePtr& theDFace,
  const TopAbs_Orientation   theOrientation) const
{
  const IMeshData::ListOfInteger& aListOfPCurves = myPCurvesMap.Find(theDFace);
  const IMeshData::IPCurveHandle& aPCurve1       = myPCurves(aListOfPCurves.First());
  return (aPCurve1->GetOrientation() == theOrientation) ? aPCurve1
                                                        : myPCurves(aListOfPCurves.Last());
}

const IMeshData::IPCurveHandle& BRepMeshData_Edge::GetPCurve(const int theIndex) const
{
  return myPCurves(theIndex);
}

const IMeshData::ListOfInteger& BRepMeshData_Edge::GetPCurves(
  const IMeshData::IFacePtr& theDFace) const
{
  return myPCurvesMap.Find(theDFace);
}
