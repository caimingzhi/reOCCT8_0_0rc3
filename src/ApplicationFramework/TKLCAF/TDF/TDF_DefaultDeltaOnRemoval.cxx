#include <TDF_DefaultDeltaOnRemoval.hpp>
#include <TDF_Label.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_DefaultDeltaOnRemoval, TDF_DeltaOnRemoval)

//=================================================================================================

TDF_DefaultDeltaOnRemoval::TDF_DefaultDeltaOnRemoval(const occ::handle<TDF_Attribute>& anAttribute)
    : TDF_DeltaOnRemoval(anAttribute)
{
}

//=================================================================================================

void TDF_DefaultDeltaOnRemoval::Apply()
{
  Label().AddAttribute(Attribute(), true);
}
