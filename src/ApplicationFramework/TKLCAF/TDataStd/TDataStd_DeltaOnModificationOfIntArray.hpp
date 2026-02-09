#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TDF_DeltaOnModification.hpp>
class TDataStd_IntegerArray;

class TDataStd_DeltaOnModificationOfIntArray : public TDF_DeltaOnModification
{

public:
  Standard_EXPORT TDataStd_DeltaOnModificationOfIntArray(
    const occ::handle<TDataStd_IntegerArray>& Arr);

  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_DeltaOnModificationOfIntArray, TDF_DeltaOnModification)

private:
  occ::handle<NCollection_HArray1<int>> myIndxes;
  occ::handle<NCollection_HArray1<int>> myValues;
  int                                   myUp1;
  int                                   myUp2;
};
