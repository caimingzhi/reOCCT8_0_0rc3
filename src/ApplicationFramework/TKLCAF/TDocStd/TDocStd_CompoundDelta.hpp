#pragma once

#include <Standard.hpp>

#include <TDF_Delta.hpp>

class TDocStd_CompoundDelta : public TDF_Delta
{

public:
  Standard_EXPORT TDocStd_CompoundDelta();

  friend class TDocStd_Document;

  DEFINE_STANDARD_RTTIEXT(TDocStd_CompoundDelta, TDF_Delta)
};
