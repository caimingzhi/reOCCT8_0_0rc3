#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <SelectMgr_CompositionFilter.hpp>
class SelectMgr_EntityOwner;

//! A framework to define an or selection filter.
//! This selects one or another type of sensitive entity.
class SelectMgr_OrFilter : public SelectMgr_CompositionFilter
{

public:
  //! Constructs an empty or selection filter.
  Standard_EXPORT SelectMgr_OrFilter();

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_OrFilter, SelectMgr_CompositionFilter)
};

