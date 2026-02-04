#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <SelectMgr_CompositionFilter.hpp>
class SelectMgr_EntityOwner;

//! A framework to define a selection filter for two or
//! more types of entity.
class SelectMgr_AndFilter : public SelectMgr_CompositionFilter
{

public:
  //! Constructs an empty selection filter object for two or
  //! more types of entity.
  Standard_EXPORT SelectMgr_AndFilter();

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_AndFilter, SelectMgr_CompositionFilter)
};

