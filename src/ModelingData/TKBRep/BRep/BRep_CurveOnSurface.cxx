#include <BRep_CurveOnSurface.hpp>
#include <BRep_CurveRepresentation.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_CurveOnSurface, BRep_GCurve)

BRep_CurveOnSurface::BRep_CurveOnSurface(const occ::handle<Geom2d_Curve>& PC,
                                         const occ::handle<Geom_Surface>& S,
                                         const TopLoc_Location&           L)
    : BRep_GCurve(L, PC->FirstParameter(), PC->LastParameter()),
      myPCurve(PC),
      mySurface(S)
{
}

void BRep_CurveOnSurface::D0(const double U, gp_Pnt& P) const
{

  gp_Pnt2d P2d = myPCurve->Value(U);
  P            = mySurface->Value(P2d.X(), P2d.Y());
  P.Transform(myLocation.Transformation());
}

bool BRep_CurveOnSurface::IsCurveOnSurface() const
{
  return true;
}

bool BRep_CurveOnSurface::IsCurveOnSurface(const occ::handle<Geom_Surface>& S,
                                           const TopLoc_Location&           L) const
{
  return (S == mySurface) && (L == myLocation);
}

const occ::handle<Geom_Surface>& BRep_CurveOnSurface::Surface() const
{
  return mySurface;
}

const occ::handle<Geom2d_Curve>& BRep_CurveOnSurface::PCurve() const
{
  return myPCurve;
}

void BRep_CurveOnSurface::PCurve(const occ::handle<Geom2d_Curve>& C)
{
  myPCurve = C;
}

occ::handle<BRep_CurveRepresentation> BRep_CurveOnSurface::Copy() const
{
  occ::handle<BRep_CurveOnSurface> C = new BRep_CurveOnSurface(myPCurve, mySurface, Location());

  C->SetRange(First(), Last());
  C->SetUVPoints(myUV1, myUV2);

  return C;
}

void BRep_CurveOnSurface::Update()
{
  double f     = First();
  double l     = Last();
  bool   isneg = Precision::IsNegativeInfinite(f);
  bool   ispos = Precision::IsPositiveInfinite(l);
  if (!isneg)
  {
    myPCurve->D0(f, myUV1);
  }
  if (!ispos)
  {
    myPCurve->D0(l, myUV2);
  }
}

void BRep_CurveOnSurface::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, BRep_GCurve)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myUV1)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myUV2)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myPCurve.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, mySurface.get())
}
