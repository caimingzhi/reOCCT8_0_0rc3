#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_DeltaOnModification.hpp>
class TDF_Attribute;

//! This class provides a default implementation of a
//! TDF_DeltaOnModification.
class TDF_DefaultDeltaOnModification : public TDF_DeltaOnModification
{

public:
  //! Creates a TDF_DefaultDeltaOnModification.
  //! <anAttribute> must be the backup copy.
  Standard_EXPORT TDF_DefaultDeltaOnModification(const occ::handle<TDF_Attribute>& anAttribute);

  //! Applies the delta to the attribute.
  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TDF_DefaultDeltaOnModification, TDF_DeltaOnModification)
};

