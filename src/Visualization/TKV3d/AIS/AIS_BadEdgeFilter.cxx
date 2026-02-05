#include <AIS_BadEdgeFilter.hpp>
#include <Standard_Type.hpp>
#include <StdSelect_BRepOwner.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_BadEdgeFilter, SelectMgr_Filter)

//=================================================================================================

AIS_BadEdgeFilter::AIS_BadEdgeFilter()
{
  myContour = 0;
}

//=================================================================================================

bool AIS_BadEdgeFilter::ActsOn(const TopAbs_ShapeEnum aType) const
{
  return (aType == TopAbs_EDGE);
}

//=================================================================================================

bool AIS_BadEdgeFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& EO) const
{
  if (myContour == 0)
    return true;

  occ::handle<StdSelect_BRepOwner> aBO(occ::down_cast<StdSelect_BRepOwner>(EO));
  if (aBO.IsNull())
    return true;

  const TopoDS_Shape& aShape = aBO->Shape();

  if (myBadEdges.IsBound(myContour))
  {
    NCollection_List<TopoDS_Shape>::Iterator it(myBadEdges.Find(myContour));
    for (; it.More(); it.Next())
    {
      if (it.Value().IsSame(aShape))
        return false;
    }
  }
  return true;
}

//=================================================================================================

void AIS_BadEdgeFilter::AddEdge(const TopoDS_Edge& anEdge, const int Index)
{
  if (myBadEdges.IsBound(Index))
  {
    myBadEdges.ChangeFind(Index).Append(anEdge);
  }
  else
  {
    NCollection_List<TopoDS_Shape> LS;
    LS.Append(anEdge);
    myBadEdges.Bind(Index, LS);
  }
}

//=================================================================================================

void AIS_BadEdgeFilter::RemoveEdges(const int Index)
{
  myBadEdges.UnBind(Index);
}

//=================================================================================================

void AIS_BadEdgeFilter::SetContour(const int Index)
{
  myContour = Index;
}
