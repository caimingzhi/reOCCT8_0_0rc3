#include <BRep_PointOnCurve.hpp>
#include <Geom_Curve.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_PointOnCurve, BRep_PointRepresentation)

BRep_PointOnCurve::BRep_PointOnCurve(const double                   P,
                                     const occ::handle<Geom_Curve>& C,
                                     const TopLoc_Location&         L)
    : BRep_PointRepresentation(P, L),
      myCurve(C)
{
}

bool BRep_PointOnCurve::IsPointOnCurve() const
{
  return true;
}

bool BRep_PointOnCurve::IsPointOnCurve(const occ::handle<Geom_Curve>& C,
                                       const TopLoc_Location&         L) const
{
  return (myCurve == C) && (Location() == L);
}

const occ::handle<Geom_Curve>& BRep_PointOnCurve::Curve() const
{
  return myCurve;
}

void BRep_PointOnCurve::Curve(const occ::handle<Geom_Curve>& C)
{
  myCurve = C;
}

void BRep_PointOnCurve::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, BRep_PointRepresentation)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myCurve.get())
}
