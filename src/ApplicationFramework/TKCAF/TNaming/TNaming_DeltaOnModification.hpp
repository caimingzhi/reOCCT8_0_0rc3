#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TDF_DeltaOnModification.hpp>
class TNaming_NamedShape;

class TNaming_DeltaOnModification : public TDF_DeltaOnModification
{

public:
  Standard_EXPORT TNaming_DeltaOnModification(const occ::handle<TNaming_NamedShape>& NS);

  Standard_EXPORT void Apply() override;

  DEFINE_STANDARD_RTTIEXT(TNaming_DeltaOnModification, TDF_DeltaOnModification)

private:
  occ::handle<NCollection_HArray1<TopoDS_Shape>> myOld;
  occ::handle<NCollection_HArray1<TopoDS_Shape>> myNew;
};
