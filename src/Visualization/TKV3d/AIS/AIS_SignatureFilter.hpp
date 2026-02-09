#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <AIS_TypeFilter.hpp>
#include <AIS_KindOfInteractive.hpp>
class SelectMgr_EntityOwner;

class AIS_SignatureFilter : public AIS_TypeFilter
{

public:
  Standard_EXPORT AIS_SignatureFilter(const AIS_KindOfInteractive aGivenKind,
                                      const int                   aGivenSignature);

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  DEFINE_STANDARD_RTTIEXT(AIS_SignatureFilter, AIS_TypeFilter)

private:
  int mySig;
};
