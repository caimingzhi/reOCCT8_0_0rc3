#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_ViewKindEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_XYZ.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_LabelDisplayEntity.hpp>
class IGESData_ViewKindEntity;
class gp_Pnt;
class IGESDimen_LeaderArrow;
class IGESData_IGESEntity;

class IGESDraw_LabelDisplay : public IGESData_LabelDisplayEntity
{

public:
  Standard_EXPORT IGESDraw_LabelDisplay();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViews,
    const occ::handle<NCollection_HArray1<gp_XYZ>>&                               allTextLocations,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>&   allLeaderEntities,
    const occ::handle<NCollection_HArray1<int>>&                                  allLabelLevels,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allDisplayedEntities);

  Standard_EXPORT int NbLabels() const;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int ViewIndex) const;

  Standard_EXPORT gp_Pnt TextLocation(const int ViewIndex) const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> LeaderEntity(const int ViewIndex) const;

  Standard_EXPORT int LabelLevel(const int ViewIndex) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> DisplayedEntity(const int EntityIndex) const;

  Standard_EXPORT gp_Pnt TransformedTextLocation(const int ViewIndex) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_LabelDisplay, IGESData_LabelDisplayEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> theViews;
  occ::handle<NCollection_HArray1<gp_XYZ>>                               theTextLocations;
  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>   theLeaderEntities;
  occ::handle<NCollection_HArray1<int>>                                  theLabelLevels;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>     theDisplayedEntities;
};
