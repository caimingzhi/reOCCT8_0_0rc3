#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <SelectMgr_Filter.hpp>
#include <TopAbs_ShapeEnum.hpp>
class SelectMgr_EntityOwner;
class TopoDS_Edge;

class AIS_BadEdgeFilter : public SelectMgr_Filter
{

public:
  Standard_EXPORT AIS_BadEdgeFilter();

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aType) const override;

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& EO) const override;

  Standard_EXPORT void SetContour(const int Index);

  Standard_EXPORT void AddEdge(const TopoDS_Edge& anEdge, const int Index);

  Standard_EXPORT void RemoveEdges(const int Index);

  DEFINE_STANDARD_RTTIEXT(AIS_BadEdgeFilter, SelectMgr_Filter)

private:
  NCollection_DataMap<int, NCollection_List<TopoDS_Shape>> myBadEdges;
  int                                                      myContour;
};
