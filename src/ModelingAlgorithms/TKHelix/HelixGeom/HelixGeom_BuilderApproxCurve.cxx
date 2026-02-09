

#include <HelixGeom_BuilderApproxCurve.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>

HelixGeom_BuilderApproxCurve::HelixGeom_BuilderApproxCurve()
    : myErrorStatus(0),
      myWarningStatus(0),
      myTolerance(0.0001),
      myCont(GeomAbs_C2),
      myMaxDegree(8),
      myMaxSeg(150),
      myTolReached(99.0)
{
}

HelixGeom_BuilderApproxCurve::~HelixGeom_BuilderApproxCurve() = default;

void HelixGeom_BuilderApproxCurve::SetApproxParameters(const GeomAbs_Shape aCont,
                                                       const int           aMaxDegree,
                                                       const int           aMaxSeg)
{
  myCont      = aCont;
  myMaxDegree = aMaxDegree;
  myMaxSeg    = aMaxSeg;
}

void HelixGeom_BuilderApproxCurve::ApproxParameters(GeomAbs_Shape& aCont,
                                                    int&           aMaxDegree,
                                                    int&           aMaxSeg) const
{
  aCont      = myCont;
  aMaxDegree = myMaxDegree;
  aMaxSeg    = myMaxSeg;
}

void HelixGeom_BuilderApproxCurve::SetTolerance(const double aTolerance)
{
  myTolerance = aTolerance;
}

double HelixGeom_BuilderApproxCurve::Tolerance() const
{
  return myTolerance;
}

double HelixGeom_BuilderApproxCurve::ToleranceReached() const
{
  return myTolReached;
}

const NCollection_Sequence<occ::handle<Geom_Curve>>& HelixGeom_BuilderApproxCurve::Curves() const
{
  return myCurves;
}

int HelixGeom_BuilderApproxCurve::ErrorStatus() const
{
  return myErrorStatus;
}

int HelixGeom_BuilderApproxCurve::WarningStatus() const
{
  return myWarningStatus;
}
