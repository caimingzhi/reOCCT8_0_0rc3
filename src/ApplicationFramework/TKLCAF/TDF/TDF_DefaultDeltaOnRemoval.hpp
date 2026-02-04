#pragma once


#include <Standard.hpp>

#include <TDF_DeltaOnRemoval.hpp>
class TDF_Attribute;

//! This class provides a default implementation of a
//! TDF_DeltaOnRemoval.
class TDF_DefaultDeltaOnRemoval : public TDF_DeltaOnRemoval
{

public:
  //! Creates a TDF_DefaultDeltaOnRemoval.
  Standard_EXPORT TDF_DefaultDeltaOnRemoval(const occ::handle<TDF_Attribute>& anAttribute);

  //! Applies the delta to the attribute.
  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DefaultDeltaOnRemoval, TDF_DeltaOnRemoval)
};

