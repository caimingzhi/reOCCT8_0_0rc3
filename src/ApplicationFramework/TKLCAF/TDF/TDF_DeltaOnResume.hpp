#pragma once

#include <Standard.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

class TDF_DeltaOnResume : public TDF_AttributeDelta
{

public:
  Standard_EXPORT TDF_DeltaOnResume(const occ::handle<TDF_Attribute>& anAtt);

  Standard_EXPORT void Apply() override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnResume, TDF_AttributeDelta)
};
