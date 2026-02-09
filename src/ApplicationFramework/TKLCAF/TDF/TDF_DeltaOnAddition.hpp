#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

class TDF_DeltaOnAddition : public TDF_AttributeDelta
{

public:
  Standard_EXPORT TDF_DeltaOnAddition(const occ::handle<TDF_Attribute>& anAtt);

  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnAddition, TDF_AttributeDelta)
};
