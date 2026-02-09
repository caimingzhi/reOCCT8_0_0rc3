#pragma once

#include <Standard.hpp>

#include <TDF_DeltaOnModification.hpp>
class TColStd_HPackedMapOfInteger;
class TDataStd_IntPackedMap;

class TDataStd_DeltaOnModificationOfIntPackedMap : public TDF_DeltaOnModification
{

public:
  Standard_EXPORT TDataStd_DeltaOnModificationOfIntPackedMap(
    const occ::handle<TDataStd_IntPackedMap>& Arr);

  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_DeltaOnModificationOfIntPackedMap, TDF_DeltaOnModification)

private:
  occ::handle<TColStd_HPackedMapOfInteger> myAddition;
  occ::handle<TColStd_HPackedMapOfInteger> myDeletion;
};
