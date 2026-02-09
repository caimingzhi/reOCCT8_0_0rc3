#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <SelectMgr_CompositionFilter.hpp>
class SelectMgr_EntityOwner;

class SelectMgr_AndFilter : public SelectMgr_CompositionFilter
{

public:
  Standard_EXPORT SelectMgr_AndFilter();

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_AndFilter, SelectMgr_CompositionFilter)
};
