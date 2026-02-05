#pragma once

#include <Standard.hpp>

#include <TDF_DeltaOnModification.hpp>
class TColStd_HPackedMapOfInteger;
class TDataStd_IntPackedMap;

//! This class provides default services for an
//! AttributeDelta on a MODIFICATION action.
class TDataStd_DeltaOnModificationOfIntPackedMap : public TDF_DeltaOnModification
{

public:
  //! Initializes a TDF_DeltaOnModification.
  Standard_EXPORT TDataStd_DeltaOnModificationOfIntPackedMap(
    const occ::handle<TDataStd_IntPackedMap>& Arr);

  //! Applies the delta to the attribute.
  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_DeltaOnModificationOfIntPackedMap, TDF_DeltaOnModification)

private:
  occ::handle<TColStd_HPackedMapOfInteger> myAddition;
  occ::handle<TColStd_HPackedMapOfInteger> myDeletion;
};
