#include <TDF_DeltaOnModification.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_DeltaOnModification, TDF_AttributeDelta)

//=================================================================================================

TDF_DeltaOnModification::TDF_DeltaOnModification(const occ::handle<TDF_Attribute>& anAttribute)
    : TDF_AttributeDelta(anAttribute)
{
}

//=================================================================================================

void TDF_DeltaOnModification::Apply()
{
  Attribute()->DeltaOnModification(this);
}
