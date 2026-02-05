#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TDF_DeltaOnModification.hpp>
class TNaming_NamedShape;

//! This class provides default services for an
//! AttributeDelta on a MODIFICATION action.
//!
//! Applying this AttributeDelta means GOING BACK to
//! the attribute previously registered state.
class TNaming_DeltaOnModification : public TDF_DeltaOnModification
{

public:
  //! Initializes a TDF_DeltaOnModification.
  Standard_EXPORT TNaming_DeltaOnModification(const occ::handle<TNaming_NamedShape>& NS);

  //! Applies the delta to the attribute.
  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TNaming_DeltaOnModification, TDF_DeltaOnModification)

private:
  occ::handle<NCollection_HArray1<TopoDS_Shape>> myOld;
  occ::handle<NCollection_HArray1<TopoDS_Shape>> myNew;
};
