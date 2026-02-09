#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <TopAbs_ShapeEnum.hpp>
class SelectMgr_EntityOwner;

class SelectMgr_Filter : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anObj) const = 0;

  Standard_EXPORT virtual bool ActsOn(const TopAbs_ShapeEnum aStandardMode) const;

  DEFINE_STANDARD_RTTIEXT(SelectMgr_Filter, Standard_Transient)
};
