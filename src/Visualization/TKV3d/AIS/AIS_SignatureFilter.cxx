#include <AIS_InteractiveObject.hpp>
#include <AIS_SignatureFilter.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_SignatureFilter, AIS_TypeFilter)

AIS_SignatureFilter::AIS_SignatureFilter(const AIS_KindOfInteractive TheKind,
                                         const int                   TheSignature)
    : AIS_TypeFilter(TheKind),
      mySig(TheSignature)
{
}

bool AIS_SignatureFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& anObj) const
{
  occ::handle<AIS_InteractiveObject> IO =
    occ::down_cast<AIS_InteractiveObject>(anObj->Selectable());
  if (IO.IsNull())
    return false;

  return (IO->Signature() == mySig && IO->Type() == myKind);
}
