#include <Standard_Type.hpp>
#include <TDF_DeltaOnRemoval.hpp>
#include <TNaming_DeltaOnModification.hpp>
#include <TNaming_DeltaOnRemoval.hpp>
#include <TNaming_NamedShape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TNaming_DeltaOnRemoval, TDF_DeltaOnRemoval)

//=================================================================================================

TNaming_DeltaOnRemoval::TNaming_DeltaOnRemoval(const occ::handle<TNaming_NamedShape>& NS)
    : TDF_DeltaOnRemoval(NS)
{
  myDelta = new TNaming_DeltaOnModification(NS);
}

//=================================================================================================

void TNaming_DeltaOnRemoval::Apply()
{
  myDelta->Apply();
}
