#include <TDF_DeltaOnRemoval.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_DeltaOnRemoval, TDF_AttributeDelta)

//=================================================================================================

TDF_DeltaOnRemoval::TDF_DeltaOnRemoval(const occ::handle<TDF_Attribute>& anAtt)
    : TDF_AttributeDelta(anAtt)
{
}
