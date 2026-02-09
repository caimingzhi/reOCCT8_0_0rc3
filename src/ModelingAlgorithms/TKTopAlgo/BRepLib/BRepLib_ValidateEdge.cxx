

#include <BRepLib_ValidateEdge.hpp>

#include <Adaptor3d_CurveOnSurface.hpp>
#include <BRepCheck.hpp>
#include <Extrema_LocateExtPC.hpp>
#include <GeomLib_CheckCurveOnSurface.hpp>
#include <utility>

BRepLib_ValidateEdge::BRepLib_ValidateEdge(occ::handle<Adaptor3d_Curve>          theReferenceCurve,
                                           occ::handle<Adaptor3d_CurveOnSurface> theOtherCurve,
                                           bool                                  theSameParameter)
    : myReferenceCurve(std::move(theReferenceCurve)),
      myOtherCurve(std::move(theOtherCurve)),
      mySameParameter(theSameParameter),
      myControlPointsNumber(22),
      myToleranceForChecking(0),
      myCalculatedDistance(0),
      myExitIfToleranceExceeded(false),
      myIsDone(false),
      myIsExactMethod(false),
      myIsMultiThread(false)
{
}

bool BRepLib_ValidateEdge::CheckTolerance(double theToleranceToCheck)
{
  return correctTolerance(theToleranceToCheck) > myCalculatedDistance;
}

double BRepLib_ValidateEdge::GetMaxDistance()
{
  double aCorrectedTolerance = myCalculatedDistance * 1.00001;
  return aCorrectedTolerance;
}

void BRepLib_ValidateEdge::UpdateTolerance(double& theToleranceToUpdate)
{
  double aCorrectedTolerance = myCalculatedDistance * 1.00001;
  if (aCorrectedTolerance > theToleranceToUpdate)
  {
    theToleranceToUpdate = aCorrectedTolerance;
  }
}

double BRepLib_ValidateEdge::correctTolerance(double theTolerance)
{
  const occ::handle<Adaptor3d_Surface>& aSurface          = myOtherCurve->GetSurface();
  double                                aCurvePrecision   = BRepCheck::PrecCurve(*myReferenceCurve);
  double                                aSurfacePrecision = BRepCheck::PrecSurface(aSurface);
  double                                aToleranceDelta =
    (aCurvePrecision > aSurfacePrecision) ? aCurvePrecision : aSurfacePrecision;
  double aCorrectedTolerance = theTolerance + aToleranceDelta;
  return aCorrectedTolerance;
}

void BRepLib_ValidateEdge::SetExitIfToleranceExceeded(double theToleranceForChecking)
{
  myExitIfToleranceExceeded = true;
  myToleranceForChecking    = correctTolerance(theToleranceForChecking);
}

void BRepLib_ValidateEdge::Process()
{
  if (myIsExactMethod && mySameParameter)
  {
    processExact();
  }
  else
  {
    processApprox();
  }
}

void BRepLib_ValidateEdge::processApprox()
{
  myIsDone                           = true;
  double aSquareToleranceForChecking = myToleranceForChecking * myToleranceForChecking;
  double aReferenceFirstParam        = myReferenceCurve->FirstParameter();
  double aReferenceLastParam         = myReferenceCurve->LastParameter();
  double anOtherFirstParam           = myOtherCurve->FirstParameter();
  double anOtherLastParam            = myOtherCurve->LastParameter();
  double aMaxSquareDistance          = 0.;

  int  aControlPointsNumber = (myControlPointsNumber < 1) ? 1 : myControlPointsNumber;
  bool anIsProjection =
    (!mySameParameter
     || std::abs(anOtherFirstParam - aReferenceFirstParam) > Precision::PConfusion()
     || std::abs(anOtherLastParam - aReferenceLastParam) > Precision::PConfusion());

  if (!anIsProjection)
  {
    for (int i = 0; i <= aControlPointsNumber; ++i)
    {
      double aControlPointParam =
        ((aControlPointsNumber - i) * aReferenceFirstParam + i * aReferenceLastParam)
        / aControlPointsNumber;
      gp_Pnt aReferencePoint = myReferenceCurve->Value(aControlPointParam);
      gp_Pnt anOtherPoint    = myOtherCurve->Value(aControlPointParam);
      double aSquareDistance = aReferencePoint.SquareDistance(anOtherPoint);
      if (aSquareDistance > aMaxSquareDistance)
      {
        aMaxSquareDistance = aSquareDistance;
      }

      if (myExitIfToleranceExceeded && aMaxSquareDistance > aSquareToleranceForChecking)
      {
        myCalculatedDistance = std::sqrt(aMaxSquareDistance);
        return;
      }
    }
  }
  else
  {
    gp_Pnt aReferencePoint = myReferenceCurve->Value(aReferenceFirstParam);
    gp_Pnt anOtherPoint    = myOtherCurve->Value(anOtherFirstParam);
    double aSquareDistance = aReferencePoint.SquareDistance(anOtherPoint);
    if (aSquareDistance > aMaxSquareDistance)
    {
      aMaxSquareDistance = aSquareDistance;
    }
    if (myExitIfToleranceExceeded && aMaxSquareDistance > aSquareToleranceForChecking)
    {
      myCalculatedDistance = std::sqrt(aMaxSquareDistance);
      return;
    }

    aReferencePoint = myReferenceCurve->Value(aReferenceLastParam);
    anOtherPoint    = myOtherCurve->Value(anOtherLastParam);
    aSquareDistance = aReferencePoint.SquareDistance(anOtherPoint);
    if (aSquareDistance > aMaxSquareDistance)
    {
      aMaxSquareDistance = aSquareDistance;
    }
    if (myExitIfToleranceExceeded && aMaxSquareDistance > aSquareToleranceForChecking)
    {
      myCalculatedDistance = std::sqrt(aMaxSquareDistance);
      return;
    }

    Extrema_LocateExtPC aReferenceExtrema, anOtherExtrema;
    aReferenceExtrema.Initialize(*myReferenceCurve,
                                 aReferenceFirstParam,
                                 aReferenceLastParam,
                                 myReferenceCurve->Resolution(Precision::Confusion()));
    anOtherExtrema.Initialize(*myOtherCurve,
                              anOtherFirstParam,
                              anOtherLastParam,
                              myOtherCurve->Resolution(Precision::Confusion()));
    for (int i = 1; i < aControlPointsNumber; i++)
    {
      double aReferenceParam =
        ((aControlPointsNumber - i) * aReferenceFirstParam + i * aReferenceLastParam)
        / aControlPointsNumber;
      gp_Pnt aReferenceExtremaPoint = myReferenceCurve->Value(aReferenceParam);
      double anOtherParam = ((aControlPointsNumber - i) * anOtherFirstParam + i * anOtherLastParam)
                            / aControlPointsNumber;
      gp_Pnt anOtherExtremaPoint = myOtherCurve->Value(anOtherParam);

      aReferenceExtrema.Perform(anOtherExtremaPoint, aReferenceParam);
      if (aReferenceExtrema.IsDone())
      {
        if (aReferenceExtrema.SquareDistance() > aMaxSquareDistance)
        {
          aMaxSquareDistance = aReferenceExtrema.SquareDistance();
        }
        if (myExitIfToleranceExceeded && aMaxSquareDistance > aSquareToleranceForChecking)
        {
          myCalculatedDistance = std::sqrt(aMaxSquareDistance);
          return;
        }
      }
      else
      {
        myIsDone = false;

        return;
      }

      anOtherExtrema.Perform(aReferenceExtremaPoint, anOtherParam);
      if (anOtherExtrema.IsDone())
      {
        if (anOtherExtrema.SquareDistance() > aMaxSquareDistance)
        {
          aMaxSquareDistance = anOtherExtrema.SquareDistance();
        }
        if (myExitIfToleranceExceeded && aMaxSquareDistance > aSquareToleranceForChecking)
        {
          myCalculatedDistance = std::sqrt(aMaxSquareDistance);
          return;
        }
      }
      else
      {
        myIsDone = false;

        return;
      }
    }
  }
  myCalculatedDistance = std::sqrt(aMaxSquareDistance);
}

void BRepLib_ValidateEdge::processExact()
{
  GeomLib_CheckCurveOnSurface aCheckCurveOnSurface(myReferenceCurve);
  aCheckCurveOnSurface.SetParallel(myIsMultiThread);
  aCheckCurveOnSurface.Perform(myOtherCurve);
  myIsDone = aCheckCurveOnSurface.IsDone();
  if (myIsDone)
  {
    myCalculatedDistance = aCheckCurveOnSurface.MaxDistance();
  }
}
