#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

//! This class provides default services for an
//! AttributeDelta on an ADDITION action.
//!
//! Applying this AttributeDelta means REMOVING its
//! attribute.
class TDF_DeltaOnAddition : public TDF_AttributeDelta
{

public:
  //! Creates a TDF_DeltaOnAddition.
  Standard_EXPORT TDF_DeltaOnAddition(const occ::handle<TDF_Attribute>& anAtt);

  //! Applies the delta to the attribute.
  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnAddition, TDF_AttributeDelta)
};
