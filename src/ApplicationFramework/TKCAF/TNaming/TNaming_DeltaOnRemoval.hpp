#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_DeltaOnRemoval.hpp>
class TNaming_DeltaOnModification;
class TNaming_NamedShape;

class TNaming_DeltaOnRemoval : public TDF_DeltaOnRemoval
{

public:
  //! Initializes a TDF_DeltaOnModification.
  Standard_EXPORT TNaming_DeltaOnRemoval(const occ::handle<TNaming_NamedShape>& NS);

  //! Applies the delta to the attribute.
  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TNaming_DeltaOnRemoval, TDF_DeltaOnRemoval)

private:
  occ::handle<TNaming_DeltaOnModification> myDelta;
};
