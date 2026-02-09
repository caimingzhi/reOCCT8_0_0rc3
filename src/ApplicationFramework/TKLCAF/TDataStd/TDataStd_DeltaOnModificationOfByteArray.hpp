#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TDF_DeltaOnModification.hpp>
class TDataStd_ByteArray;

class TDataStd_DeltaOnModificationOfByteArray : public TDF_DeltaOnModification
{

public:
  Standard_EXPORT TDataStd_DeltaOnModificationOfByteArray(
    const occ::handle<TDataStd_ByteArray>& Arr);

  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_DeltaOnModificationOfByteArray, TDF_DeltaOnModification)

private:
  occ::handle<NCollection_HArray1<int>>     myIndxes;
  occ::handle<NCollection_HArray1<uint8_t>> myValues;
  int                                       myUp1;
  int                                       myUp2;
};
