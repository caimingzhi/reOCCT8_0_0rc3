#pragma once

#include <Standard.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

class TDF_DeltaOnRemoval : public TDF_AttributeDelta
{

public:
  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnRemoval, TDF_AttributeDelta)

protected:
  Standard_EXPORT TDF_DeltaOnRemoval(const occ::handle<TDF_Attribute>& anAtt);
};
