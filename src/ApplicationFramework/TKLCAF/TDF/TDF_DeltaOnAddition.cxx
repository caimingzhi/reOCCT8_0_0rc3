#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_DeltaOnAddition.hpp>
#include <TDF_Label.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_DeltaOnAddition, TDF_AttributeDelta)

//=================================================================================================

TDF_DeltaOnAddition::TDF_DeltaOnAddition(const occ::handle<TDF_Attribute>& anAtt)
    : TDF_AttributeDelta(anAtt)
{
}

//=================================================================================================

void TDF_DeltaOnAddition::Apply()
{
  occ::handle<TDF_Attribute> currentAtt;
  if (Label().FindAttribute(ID(), currentAtt))
  {
    Label().ForgetAttribute(currentAtt);
  }
}
