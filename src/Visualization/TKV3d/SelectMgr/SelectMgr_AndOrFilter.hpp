#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Shared.hpp>
#include <SelectMgr_CompositionFilter.hpp>

enum SelectMgr_FilterType
{
  SelectMgr_FilterType_AND,
  SelectMgr_FilterType_OR
};

class SelectMgr_AndOrFilter : public SelectMgr_CompositionFilter
{

public:
  Standard_EXPORT SelectMgr_AndOrFilter(const SelectMgr_FilterType theFilterType);

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& theObj) const override;

  Standard_EXPORT void SetDisabledObjects(
    const occ::handle<NCollection_Shared<NCollection_Map<const Standard_Transient*>>>& theObjects);

  SelectMgr_FilterType FilterType() const { return myFilterType; }

  void SetFilterType(const SelectMgr_FilterType theFilterType) { myFilterType = theFilterType; }

  DEFINE_STANDARD_RTTIEXT(SelectMgr_AndOrFilter, SelectMgr_CompositionFilter)

private:
  occ::handle<NCollection_Shared<NCollection_Map<const Standard_Transient*>>> myDisabledObjects;

  SelectMgr_FilterType myFilterType;
};
