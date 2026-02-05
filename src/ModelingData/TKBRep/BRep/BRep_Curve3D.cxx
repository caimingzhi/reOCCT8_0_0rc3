#include <BRep_Curve3D.hpp>
#include <BRep_CurveRepresentation.hpp>
#include <Geom_Curve.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_Curve3D, BRep_GCurve)

//=================================================================================================

BRep_Curve3D::BRep_Curve3D(const occ::handle<Geom_Curve>& C, const TopLoc_Location& L)
    : BRep_GCurve(L,
                  C.IsNull() ? RealFirst() : C->FirstParameter(),
                  C.IsNull() ? RealLast() : C->LastParameter()),
      myCurve(C)
{
}

//=================================================================================================

void BRep_Curve3D::D0(const double U, gp_Pnt& P) const
{
  // should be D0 NYI
  P = myCurve->Value(U);
}

//=================================================================================================

bool BRep_Curve3D::IsCurve3D() const
{
  return true;
}

//=================================================================================================

const occ::handle<Geom_Curve>& BRep_Curve3D::Curve3D() const
{
  return myCurve;
}

//=================================================================================================

void BRep_Curve3D::Curve3D(const occ::handle<Geom_Curve>& C)
{
  myCurve = C;
}

//=================================================================================================

occ::handle<BRep_CurveRepresentation> BRep_Curve3D::Copy() const
{
  occ::handle<BRep_Curve3D> C = new BRep_Curve3D(myCurve, Location());

  C->SetRange(First(), Last());
  return C;
}

//=================================================================================================

void BRep_Curve3D::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, BRep_GCurve)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myCurve.get())
}
