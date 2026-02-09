#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <AIS_KindOfInteractive.hpp>
#include <SelectMgr_Filter.hpp>
class SelectMgr_EntityOwner;

class AIS_TypeFilter : public SelectMgr_Filter
{

public:
  Standard_EXPORT AIS_TypeFilter(const AIS_KindOfInteractive aGivenKind);

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  DEFINE_STANDARD_RTTIEXT(AIS_TypeFilter, SelectMgr_Filter)

protected:
  AIS_KindOfInteractive myKind;
};
