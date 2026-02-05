#include <BRep_GCurve.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_GCurve, BRep_CurveRepresentation)

//=================================================================================================

BRep_GCurve::BRep_GCurve(const TopLoc_Location& L, const double First, const double Last)
    : BRep_CurveRepresentation(L),
      myFirst(First),
      myLast(Last)

{
}

//=================================================================================================

void BRep_GCurve::Update() {}

//=================================================================================================

void BRep_GCurve::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, BRep_CurveRepresentation)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myFirst)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myLast)
}
