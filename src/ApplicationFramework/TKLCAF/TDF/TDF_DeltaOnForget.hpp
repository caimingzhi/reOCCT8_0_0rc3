#pragma once

#include <Standard.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

class TDF_DeltaOnForget : public TDF_AttributeDelta
{

public:
  Standard_EXPORT TDF_DeltaOnForget(const occ::handle<TDF_Attribute>& anAtt);

  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnForget, TDF_AttributeDelta)
};
