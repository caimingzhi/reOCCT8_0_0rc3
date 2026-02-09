#pragma once

#include <Standard.hpp>

#include <TDF_DeltaOnRemoval.hpp>
class TDF_Attribute;

class TDF_DefaultDeltaOnRemoval : public TDF_DeltaOnRemoval
{

public:
  Standard_EXPORT TDF_DefaultDeltaOnRemoval(const occ::handle<TDF_Attribute>& anAttribute);

  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DefaultDeltaOnRemoval, TDF_DeltaOnRemoval)
};
