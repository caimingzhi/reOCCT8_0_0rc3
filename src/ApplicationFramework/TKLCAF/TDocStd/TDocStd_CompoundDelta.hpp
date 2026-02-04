#pragma once


#include <Standard.hpp>

#include <TDF_Delta.hpp>

//! A delta set is available at <aSourceTime>. If
//! applied, it restores the TDF_Data in the state it
//! was at <aTargetTime>.
class TDocStd_CompoundDelta : public TDF_Delta
{

public:
  //! Creates a compound delta.
  //! Validates <me> at <aBeginTime>. If applied, it
  //! restores the TDF_Data in the state it was at
  //! <anEndTime>. Reserved to TDF_Data.
  Standard_EXPORT TDocStd_CompoundDelta();

  friend class TDocStd_Document;

  DEFINE_STANDARD_RTTIEXT(TDocStd_CompoundDelta, TDF_Delta)
};

