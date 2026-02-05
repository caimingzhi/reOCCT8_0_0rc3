#include <BRepMesh_ShapeVisitor.hpp>
#include <TopExp.hpp>
#include <ShapeAnalysis.hpp>
#include <TopExp_Explorer.hpp>
#include <IMeshData_Edge.hpp>
#include <IMeshData_Wire.hpp>
#include <IMeshData_Face.hpp>
#include <ShapeAnalysis_Wire.hpp>
#include <ShapeAnalysis_WireOrder.hpp>
#include <ShapeExtend_WireData.hpp>
#include <Precision.hpp>
#include <IMeshData_Status.hpp>
#include <IMeshTools_Context.hpp>
#include <BRepTools.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_ShapeVisitor, IMeshTools_ShapeVisitor)

//=================================================================================================

BRepMesh_ShapeVisitor::BRepMesh_ShapeVisitor(const occ::handle<IMeshData_Model>& theModel)
    : myModel(theModel),
      myDEdgeMap(1, new NCollection_IncAllocator(IMeshData::MEMORY_BLOCK_SIZE_HUGE))
{
}

//=================================================================================================

BRepMesh_ShapeVisitor::~BRepMesh_ShapeVisitor() = default;

//=================================================================================================

void BRepMesh_ShapeVisitor::Visit(const TopoDS_Edge& theEdge)
{
  if (!myDEdgeMap.IsBound(theEdge))
  {
    myModel->AddEdge(theEdge);
    myDEdgeMap.Bind(theEdge, myModel->EdgesNb() - 1);
  }
}

//=================================================================================================

void BRepMesh_ShapeVisitor::Visit(const TopoDS_Face& theFace)
{
  BRepTools::Update(theFace);
  const IMeshData::IFaceHandle& aDFace = myModel->AddFace(theFace);

  // Outer wire should always be the first in the model.
  TopoDS_Wire aOuterWire = ShapeAnalysis::OuterWire(theFace);
  if (!addWire(aOuterWire, aDFace))
  {
    aDFace->SetStatus(IMeshData_Failure);
    return;
  }

  TopExp_Explorer aWireIt(theFace, TopAbs_WIRE);
  for (; aWireIt.More(); aWireIt.Next())
  {
    const TopoDS_Wire& aWire = TopoDS::Wire(aWireIt.Current());
    if (aWire.IsSame(aOuterWire))
    {
      continue;
    }

    if (!addWire(aWire, aDFace))
    {
      // If there is a failure on internal wire, just skip it.
      // The most significant is an outer wire.
      aDFace->SetStatus(IMeshData_UnorientedWire);
    }
  }
}

//=================================================================================================

bool BRepMesh_ShapeVisitor::addWire(const TopoDS_Wire&            theWire,
                                    const IMeshData::IFaceHandle& theDFace)
{
  if (theWire.IsNull())
  {
    return false;
  }

  occ::handle<ShapeExtend_WireData> aWireData = new ShapeExtend_WireData(theWire, true, false);
  ShapeAnalysis_Wire aWireTool(aWireData, theDFace->GetFace(), Precision::Confusion());

  ShapeAnalysis_WireOrder aOrderTool;
  aWireTool.CheckOrder(aOrderTool, true, false);
  if (aWireTool.LastCheckStatus(ShapeExtend_FAIL))
  {
    return false;
  }

  if (aWireTool.LastCheckStatus(ShapeExtend_DONE3))
  {
    theDFace->SetStatus(IMeshData_UnorientedWire);
  }

  const int aEdgesNb = aOrderTool.NbEdges();
  if (aEdgesNb != aWireData->NbEdges())
  {
    return false;
  }

  const IMeshData::IWireHandle& aDWire = theDFace->AddWire(theWire, aEdgesNb);
  for (int i = 1; i <= aEdgesNb; ++i)
  {
    const int          aEdgeIndex = aOrderTool.Ordered(i);
    const TopoDS_Edge& aEdge      = aWireData->Edge(aEdgeIndex);
    if (aEdge.Orientation() != TopAbs_EXTERNAL)
    {
      const IMeshData::IEdgeHandle& aDEdge = myModel->GetEdge(myDEdgeMap.Find(aEdge));

      aDEdge->AddPCurve(theDFace.get(), aEdge.Orientation());
      aDWire->AddEdge(aDEdge.get(), aEdge.Orientation());
    }
  }

  return true;
}
