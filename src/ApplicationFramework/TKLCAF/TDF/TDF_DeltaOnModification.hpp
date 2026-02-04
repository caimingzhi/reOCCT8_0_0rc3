#pragma once


#include <Standard.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

//! This class provides default services for an
//! AttributeDelta on a MODIFICATION action.
//!
//! Applying this AttributeDelta means GOING BACK to
//! the attribute previously registered state.
class TDF_DeltaOnModification : public TDF_AttributeDelta
{

public:
  //! Applies the delta to the attribute.
  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnModification, TDF_AttributeDelta)

protected:
  //! Initializes a TDF_DeltaOnModification.
  Standard_EXPORT TDF_DeltaOnModification(const occ::handle<TDF_Attribute>& anAttribute);
};

