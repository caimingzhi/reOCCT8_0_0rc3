#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDF_DeltaOnModification.hpp>
class TDataStd_ExtStringArray;

class TDataStd_DeltaOnModificationOfExtStringArray : public TDF_DeltaOnModification
{

public:
  Standard_EXPORT TDataStd_DeltaOnModificationOfExtStringArray(
    const occ::handle<TDataStd_ExtStringArray>& Arr);

  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_DeltaOnModificationOfExtStringArray, TDF_DeltaOnModification)

private:
  occ::handle<NCollection_HArray1<int>>                        myIndxes;
  occ::handle<NCollection_HArray1<TCollection_ExtendedString>> myValues;
  int                                                          myUp1;
  int                                                          myUp2;
};
