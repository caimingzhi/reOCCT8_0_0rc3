#pragma once

#include <Standard.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

//! This class provides default services for an
//! AttributeDelta on a REMOVAL action.
//!
//! Applying this AttributeDelta means ADDING its
//! attribute.
class TDF_DeltaOnRemoval : public TDF_AttributeDelta
{

public:
  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnRemoval, TDF_AttributeDelta)

protected:
  //! Initializes a TDF_DeltaOnRemoval.
  Standard_EXPORT TDF_DeltaOnRemoval(const occ::handle<TDF_Attribute>& anAtt);
};
