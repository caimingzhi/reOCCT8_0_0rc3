#include <StepToTopoDS_NMTool.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopExp_Explorer.hpp>

StepToTopoDS_NMTool::StepToTopoDS_NMTool()
{
  myIDEASCase  = false;
  myActiveFlag = false;
}

StepToTopoDS_NMTool::StepToTopoDS_NMTool(
  const NCollection_DataMap<occ::handle<StepRepr_RepresentationItem>, TopoDS_Shape>& MapOfRI,
  const NCollection_DataMap<TCollection_AsciiString, TopoDS_Shape>&                  MapOfRINames)
{
  myIDEASCase  = false;
  myActiveFlag = false;
  Init(MapOfRI, MapOfRINames);
}

void StepToTopoDS_NMTool::Init(
  const NCollection_DataMap<occ::handle<StepRepr_RepresentationItem>, TopoDS_Shape>& MapOfRI,
  const NCollection_DataMap<TCollection_AsciiString, TopoDS_Shape>&                  MapOfRINames)
{
  myRIMap      = MapOfRI;
  myRINamesMap = MapOfRINames;
}

void StepToTopoDS_NMTool::SetActive(const bool isActive)
{
  myActiveFlag = isActive;
}

bool StepToTopoDS_NMTool::IsActive()
{
  return myActiveFlag;
}

void StepToTopoDS_NMTool::CleanUp()
{
  myRIMap.Clear();
  myRINamesMap.Clear();
}

bool StepToTopoDS_NMTool::IsBound(const occ::handle<StepRepr_RepresentationItem>& RI)
{
  return myRIMap.IsBound(RI);
}

bool StepToTopoDS_NMTool::IsBound(const TCollection_AsciiString& RIName)
{
  return myRINamesMap.IsBound(RIName);
}

void StepToTopoDS_NMTool::Bind(const occ::handle<StepRepr_RepresentationItem>& RI,
                               const TopoDS_Shape&                             S)
{
  myRIMap.Bind(RI, S);
}

void StepToTopoDS_NMTool::Bind(const TCollection_AsciiString& RIName, const TopoDS_Shape& S)
{
  myRINamesMap.Bind(RIName, S);
}

const TopoDS_Shape& StepToTopoDS_NMTool::Find(const occ::handle<StepRepr_RepresentationItem>& RI)
{
  return myRIMap.Find(RI);
}

const TopoDS_Shape& StepToTopoDS_NMTool::Find(const TCollection_AsciiString& RIName)
{
  return myRINamesMap.Find(RIName);
}

void StepToTopoDS_NMTool::RegisterNMEdge(const TopoDS_Shape& Edge)
{
  if (!this->isEdgeRegisteredAsNM(Edge))
    myNMEdges.Append(Edge);
}

bool StepToTopoDS_NMTool::IsSuspectedAsClosing(const TopoDS_Shape& BaseShell,
                                               const TopoDS_Shape& SuspectedShell)
{
  return this->IsPureNMShell(SuspectedShell) && this->isAdjacentShell(BaseShell, SuspectedShell);
}

void StepToTopoDS_NMTool::SetIDEASCase(const bool IDEASCase)
{
  myIDEASCase = IDEASCase;
}

bool StepToTopoDS_NMTool::IsIDEASCase()
{
  return myIDEASCase;
}

bool StepToTopoDS_NMTool::IsPureNMShell(const TopoDS_Shape& Shell)
{
  bool            result = true;
  TopExp_Explorer edgeExp(Shell, TopAbs_EDGE);
  for (; edgeExp.More(); edgeExp.Next())
  {
    const TopoDS_Shape& currentEdge = edgeExp.Current();
    if (!this->isEdgeRegisteredAsNM(currentEdge))
    {
      result = false;
      break;
    }
  }
  return result;
}

bool StepToTopoDS_NMTool::isEdgeRegisteredAsNM(const TopoDS_Shape& Edge)
{
  bool                                     result = false;
  NCollection_List<TopoDS_Shape>::Iterator it(myNMEdges);
  for (; it.More(); it.Next())
  {
    TopoDS_Shape currentShape = it.Value();
    if (currentShape.IsSame(Edge))
    {
      result = true;
      break;
    }
  }
  return result;
}

bool StepToTopoDS_NMTool::isAdjacentShell(const TopoDS_Shape& ShellA, const TopoDS_Shape& ShellB)
{
  if (ShellA.IsSame(ShellB))
    return false;

  TopExp_Explorer edgeExpA(ShellA, TopAbs_EDGE);
  for (; edgeExpA.More(); edgeExpA.Next())
  {
    const TopoDS_Shape& currentEdgeA = edgeExpA.Current();
    TopExp_Explorer     edgeExpB(ShellB, TopAbs_EDGE);
    for (; edgeExpB.More(); edgeExpB.Next())
    {
      const TopoDS_Shape& currentEdgeB = edgeExpB.Current();
      if (currentEdgeA.IsSame(currentEdgeB))
        return true;
    }
  }

  return false;
}
