#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_DefaultDeltaOnModification.hpp>
#include <TDF_Label.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_DefaultDeltaOnModification, TDF_DeltaOnModification)

//=================================================================================================

TDF_DefaultDeltaOnModification::TDF_DefaultDeltaOnModification(
  const occ::handle<TDF_Attribute>& anAttribute)
    : TDF_DeltaOnModification(anAttribute)
{
}

//=================================================================================================

void TDF_DefaultDeltaOnModification::Apply()
{
  const occ::handle<TDF_Attribute>& savAtt = Attribute();
  occ::handle<TDF_Attribute>        refAtt;
  if (Label().FindAttribute(savAtt->ID(), refAtt))
    refAtt->DeltaOnModification(this);
}
