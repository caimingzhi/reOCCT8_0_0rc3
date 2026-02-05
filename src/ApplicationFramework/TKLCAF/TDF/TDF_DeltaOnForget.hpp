#pragma once

#include <Standard.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

//! This class provides default services for an
//! AttributeDelta on an Forget action.
//!
//! Applying this AttributeDelta means RESUMING its
//! attribute.
class TDF_DeltaOnForget : public TDF_AttributeDelta
{

public:
  //! Creates a TDF_DeltaOnForget.
  Standard_EXPORT TDF_DeltaOnForget(const occ::handle<TDF_Attribute>& anAtt);

  //! Applies the delta to the attribute.
  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnForget, TDF_AttributeDelta)
};
