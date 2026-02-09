#pragma once

#include <TObj_Partition.hpp>

class TObj_HiddenPartition : public TObj_Partition
{
public:
  Standard_EXPORT TObj_HiddenPartition(const TDF_Label& theLabel);

  Standard_EXPORT int GetTypeFlags() const override;

protected:
  DECLARE_TOBJOCAF_PERSISTENCE(TObj_HiddenPartition, TObj_Partition)
public:
  DEFINE_STANDARD_RTTIEXT(TObj_HiddenPartition, TObj_Partition)
};

#ifdef _MSC_VER
  #pragma once
#endif
