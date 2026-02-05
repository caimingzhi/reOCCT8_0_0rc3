#pragma once

#include <TObj_Partition.hpp>

/**
 * This class is partition is predefined hidden flag
 */

class TObj_HiddenPartition : public TObj_Partition
{
public:
  //! constructor
  Standard_EXPORT TObj_HiddenPartition(const TDF_Label& theLabel);

  //! Returns all flags of father except Visible
  Standard_EXPORT int GetTypeFlags() const override;

protected:
  //! Persistence of TObj object
  DECLARE_TOBJOCAF_PERSISTENCE(TObj_HiddenPartition, TObj_Partition)
public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_HiddenPartition, TObj_Partition)
};

//! Define handle class for TObj_HiddenPartition

#ifdef _MSC_VER
  #pragma once
#endif
