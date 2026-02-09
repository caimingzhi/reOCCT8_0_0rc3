#include <TObj_HiddenPartition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_HiddenPartition, TObj_Partition)
IMPLEMENT_TOBJOCAF_PERSISTENCE(TObj_HiddenPartition)

Standard_EXPORT TObj_HiddenPartition::TObj_HiddenPartition(const TDF_Label& theLabel)
    : TObj_Partition(theLabel)
{
}

int TObj_HiddenPartition::GetTypeFlags() const
{
  return TObj_Partition::GetTypeFlags() & (~Visible);
}
