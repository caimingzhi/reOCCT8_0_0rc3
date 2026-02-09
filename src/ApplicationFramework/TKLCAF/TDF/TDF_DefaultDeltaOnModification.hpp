#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_DeltaOnModification.hpp>
class TDF_Attribute;

class TDF_DefaultDeltaOnModification : public TDF_DeltaOnModification
{

public:
  Standard_EXPORT TDF_DefaultDeltaOnModification(const occ::handle<TDF_Attribute>& anAttribute);

  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DefaultDeltaOnModification, TDF_DeltaOnModification)
};
