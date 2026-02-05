#pragma once

#include <Standard.hpp>

#include <TDF_AttributeDelta.hpp>
class TDF_Attribute;

//! This class provides default services for an
//! AttributeDelta on an Resume action.
//!
//! Applying this AttributeDelta means FORGETTING its
//! attribute.
class TDF_DeltaOnResume : public TDF_AttributeDelta
{

public:
  //! Creates a TDF_DeltaOnResume.
  Standard_EXPORT TDF_DeltaOnResume(const occ::handle<TDF_Attribute>& anAtt);

  //! Applies the delta to the attribute.
  Standard_EXPORT void Apply() override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDF_DeltaOnResume, TDF_AttributeDelta)
};
