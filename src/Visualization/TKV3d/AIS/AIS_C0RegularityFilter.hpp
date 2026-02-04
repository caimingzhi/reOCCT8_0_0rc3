#pragma once


#include <Standard.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <SelectMgr_Filter.hpp>
#include <TopAbs_ShapeEnum.hpp>
class TopoDS_Shape;
class SelectMgr_EntityOwner;

class AIS_C0RegularityFilter : public SelectMgr_Filter
{

public:
  Standard_EXPORT AIS_C0RegularityFilter(const TopoDS_Shape& aShape);

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aType) const override;

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& EO) const override;

  DEFINE_STANDARD_RTTIEXT(AIS_C0RegularityFilter, SelectMgr_Filter)

private:
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMapOfEdges;
};

