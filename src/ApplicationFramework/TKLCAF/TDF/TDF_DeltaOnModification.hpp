#pragma once

#include <Standard.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

class TDF_DeltaOnModification : public TDF_AttributeDelta
{

public:
  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnModification, TDF_AttributeDelta)

protected:
  Standard_EXPORT TDF_DeltaOnModification(const occ::handle<TDF_Attribute>& anAttribute);
};
