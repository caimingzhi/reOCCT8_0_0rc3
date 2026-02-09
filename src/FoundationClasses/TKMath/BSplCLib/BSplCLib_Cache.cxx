

#include <BSplCLib_Cache.hpp>
#include <BSplCLib.hpp>

#include <NCollection_LocalArray.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt2d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BSplCLib_Cache, Standard_Transient)

BSplCLib_Cache::BSplCLib_Cache(const int&                        theDegree,
                               const bool&                       thePeriodic,
                               const NCollection_Array1<double>& theFlatKnots,
                               const NCollection_Array1<gp_Pnt2d>&,
                               const NCollection_Array1<double>* theWeights)
    : myIsRational(theWeights != nullptr),
      myParams(theDegree, thePeriodic, theFlatKnots),
      myRowLength(myIsRational ? 3 : 2)
{
}

BSplCLib_Cache::BSplCLib_Cache(const int&                        theDegree,
                               const bool&                       thePeriodic,
                               const NCollection_Array1<double>& theFlatKnots,
                               const NCollection_Array1<gp_Pnt>&,
                               const NCollection_Array1<double>* theWeights)
    : myIsRational(theWeights != nullptr),
      myParams(theDegree, thePeriodic, theFlatKnots),
      myRowLength(myIsRational ? 4 : 3)
{
}

bool BSplCLib_Cache::IsCacheValid(double theParameter) const
{
  return myParams.IsCacheValid(theParameter);
}

void BSplCLib_Cache::BuildCache(const double&                       theParameter,
                                const NCollection_Array1<double>&   theFlatKnots,
                                const NCollection_Array1<gp_Pnt2d>& thePoles2d,
                                const NCollection_Array1<double>*   theWeights)
{

  double aNewParam = myParams.PeriodicNormalization(theParameter);
  myParams.LocateParameter(aNewParam, theFlatKnots);

  NCollection_Array2<double> aPolesWeights(myPolesWeightsBuffer[0],
                                           1,
                                           myParams.Degree + 1,
                                           1,
                                           myRowLength);

  BSplCLib::BuildCache(myParams.SpanStart,
                       myParams.SpanLength,
                       myParams.IsPeriodic,
                       myParams.Degree,
                       myParams.SpanIndex,
                       theFlatKnots,
                       thePoles2d,
                       theWeights,
                       aPolesWeights);
}

void BSplCLib_Cache::BuildCache(const double&                     theParameter,
                                const NCollection_Array1<double>& theFlatKnots,
                                const NCollection_Array1<gp_Pnt>& thePoles,
                                const NCollection_Array1<double>* theWeights)
{

  double aNewParam = myParams.PeriodicNormalization(theParameter);
  myParams.LocateParameter(aNewParam, theFlatKnots);

  NCollection_Array2<double> aPolesWeights(myPolesWeightsBuffer[0],
                                           1,
                                           myParams.Degree + 1,
                                           1,
                                           myRowLength);

  BSplCLib::BuildCache(myParams.SpanStart,
                       myParams.SpanLength,
                       myParams.IsPeriodic,
                       myParams.Degree,
                       myParams.SpanIndex,
                       theFlatKnots,
                       thePoles,
                       theWeights,
                       aPolesWeights);
}

void BSplCLib_Cache::calculateDerivative(double  theParameter,
                                         int     theDerivative,
                                         double* theDerivArray) const
{
  double aLocalParam = myParams.PeriodicNormalization(theParameter);
  aLocalParam        = (aLocalParam - myParams.SpanStart) / myParams.SpanLength;
  calculateDerivativeLocal(aLocalParam, theDerivative, theDerivArray);
}

void BSplCLib_Cache::calculateDerivativeLocal(double  theLocalParam,
                                              int     theDerivative,
                                              double* theDerivArray) const
{
  const int aDimension = myRowLength;

  double aTmpContainer[16];

  double* aPntDeriv = myIsRational ? aTmpContainer : theDerivArray;

  int aDerivative = theDerivative;
  if (!myIsRational && myParams.Degree < theDerivative)
  {
    aDerivative = myParams.Degree;
    for (int ind = myParams.Degree * aDimension; ind < (theDerivative + 1) * aDimension; ind++)
    {
      aPntDeriv[ind] = 0.0;
    }
  }

  PLib::EvalPolynomial(theLocalParam,
                       aDerivative,
                       myParams.Degree,
                       aDimension,
                       myPolesWeightsBuffer[0],
                       aPntDeriv[0]);

  double aFactor = 1.0;
  for (int deriv = 1; deriv <= aDerivative; deriv++)
  {
    aFactor /= myParams.SpanLength;
    for (int ind = 0; ind < aDimension; ind++)
    {
      aPntDeriv[aDimension * deriv + ind] *= aFactor;
    }
  }

  if (myIsRational)
  {
    PLib::RationalDerivative(aDerivative,
                             aDerivative,
                             aDimension - 1,
                             aPntDeriv[0],
                             theDerivArray[0]);
  }
}

void BSplCLib_Cache::D0(const double& theParameter, gp_Pnt2d& thePoint) const
{
  double aNewParameter = myParams.PeriodicNormalization(theParameter);
  aNewParameter        = (aNewParameter - myParams.SpanStart) / myParams.SpanLength;

  double*   aPolesArray = const_cast<double*>(myPolesWeightsBuffer);
  double    aPoint[4];
  const int aDimension = myRowLength;

  PLib::NoDerivativeEvalPolynomial(aNewParameter,
                                   myParams.Degree,
                                   aDimension,
                                   myParams.Degree * aDimension,
                                   aPolesArray[0],
                                   aPoint[0]);

  thePoint.SetCoord(aPoint[0], aPoint[1]);
  if (myIsRational)
    thePoint.ChangeCoord().Divide(aPoint[2]);
}

void BSplCLib_Cache::D0(const double& theParameter, gp_Pnt& thePoint) const
{
  double aLocalParam = myParams.PeriodicNormalization(theParameter);
  aLocalParam        = (aLocalParam - myParams.SpanStart) / myParams.SpanLength;
  D0Local(aLocalParam, thePoint);
}

void BSplCLib_Cache::D0Local(double theLocalParam, gp_Pnt& thePoint) const
{

  double aPoint[4];

  PLib::NoDerivativeEvalPolynomial(theLocalParam,
                                   myParams.Degree,
                                   myRowLength,
                                   myParams.Degree * myRowLength,
                                   myPolesWeightsBuffer[0],
                                   aPoint[0]);

  thePoint.SetCoord(aPoint[0], aPoint[1], aPoint[2]);
  if (myIsRational)
  {
    thePoint.ChangeCoord().Divide(aPoint[3]);
  }
}

void BSplCLib_Cache::D1(const double& theParameter, gp_Pnt2d& thePoint, gp_Vec2d& theTangent) const
{
  int    aDimension = myRowLength;
  double aPntDeriv[8];

  calculateDerivative(theParameter, 1, aPntDeriv);
  if (myIsRational)
    aDimension -= 1;

  thePoint.SetCoord(aPntDeriv[0], aPntDeriv[1]);
  theTangent.SetCoord(aPntDeriv[aDimension], aPntDeriv[aDimension + 1]);
}

void BSplCLib_Cache::D1(const double& theParameter, gp_Pnt& thePoint, gp_Vec& theTangent) const
{
  double aLocalParam = myParams.PeriodicNormalization(theParameter);
  aLocalParam        = (aLocalParam - myParams.SpanStart) / myParams.SpanLength;
  D1Local(aLocalParam, thePoint, theTangent);
}

void BSplCLib_Cache::D1Local(double theLocalParam, gp_Pnt& thePoint, gp_Vec& theTangent) const
{
  double aDerivArray[8];
  calculateDerivativeLocal(theLocalParam, 1, aDerivArray);

  const int aDim = myIsRational ? myRowLength - 1 : myRowLength;
  thePoint.SetCoord(aDerivArray[0], aDerivArray[1], aDerivArray[2]);
  theTangent.SetCoord(aDerivArray[aDim], aDerivArray[aDim + 1], aDerivArray[aDim + 2]);
}

void BSplCLib_Cache::D2(const double& theParameter,
                        gp_Pnt2d&     thePoint,
                        gp_Vec2d&     theTangent,
                        gp_Vec2d&     theCurvature) const
{
  int    aDimension = myRowLength;
  double aPntDeriv[12];

  calculateDerivative(theParameter, 2, aPntDeriv);
  if (myIsRational)
    aDimension -= 1;

  thePoint.SetCoord(aPntDeriv[0], aPntDeriv[1]);
  theTangent.SetCoord(aPntDeriv[aDimension], aPntDeriv[aDimension + 1]);
  theCurvature.SetCoord(aPntDeriv[aDimension << 1], aPntDeriv[(aDimension << 1) + 1]);
}

void BSplCLib_Cache::D2(const double& theParameter,
                        gp_Pnt&       thePoint,
                        gp_Vec&       theTangent,
                        gp_Vec&       theCurvature) const
{
  double aLocalParam = myParams.PeriodicNormalization(theParameter);
  aLocalParam        = (aLocalParam - myParams.SpanStart) / myParams.SpanLength;
  D2Local(aLocalParam, thePoint, theTangent, theCurvature);
}

void BSplCLib_Cache::D2Local(double  theLocalParam,
                             gp_Pnt& thePoint,
                             gp_Vec& theTangent,
                             gp_Vec& theCurvature) const
{
  double aDerivArray[12];
  calculateDerivativeLocal(theLocalParam, 2, aDerivArray);

  const int aDim   = myIsRational ? myRowLength - 1 : myRowLength;
  const int aShift = aDim << 1;
  thePoint.SetCoord(aDerivArray[0], aDerivArray[1], aDerivArray[2]);
  theTangent.SetCoord(aDerivArray[aDim], aDerivArray[aDim + 1], aDerivArray[aDim + 2]);
  theCurvature.SetCoord(aDerivArray[aShift], aDerivArray[aShift + 1], aDerivArray[aShift + 2]);
}

void BSplCLib_Cache::D3(const double& theParameter,
                        gp_Pnt2d&     thePoint,
                        gp_Vec2d&     theTangent,
                        gp_Vec2d&     theCurvature,
                        gp_Vec2d&     theTorsion) const
{
  int    aDimension = myRowLength;
  double aPntDeriv[16];

  calculateDerivative(theParameter, 3, aPntDeriv);
  if (myIsRational)
    aDimension -= 1;

  thePoint.SetCoord(aPntDeriv[0], aPntDeriv[1]);
  theTangent.SetCoord(aPntDeriv[aDimension], aPntDeriv[aDimension + 1]);
  int aShift = aDimension << 1;
  theCurvature.SetCoord(aPntDeriv[aShift], aPntDeriv[aShift + 1]);
  aShift += aDimension;
  theTorsion.SetCoord(aPntDeriv[aShift], aPntDeriv[aShift + 1]);
}

void BSplCLib_Cache::D3(const double& theParameter,
                        gp_Pnt&       thePoint,
                        gp_Vec&       theTangent,
                        gp_Vec&       theCurvature,
                        gp_Vec&       theTorsion) const
{
  double aLocalParam = myParams.PeriodicNormalization(theParameter);
  aLocalParam        = (aLocalParam - myParams.SpanStart) / myParams.SpanLength;
  D3Local(aLocalParam, thePoint, theTangent, theCurvature, theTorsion);
}

void BSplCLib_Cache::D3Local(double  theLocalParam,
                             gp_Pnt& thePoint,
                             gp_Vec& theTangent,
                             gp_Vec& theCurvature,
                             gp_Vec& theTorsion) const
{
  double aDerivArray[16];
  calculateDerivativeLocal(theLocalParam, 3, aDerivArray);

  const int aDim    = myIsRational ? myRowLength - 1 : myRowLength;
  const int aShift2 = aDim << 1;
  const int aShift3 = aShift2 + aDim;
  thePoint.SetCoord(aDerivArray[0], aDerivArray[1], aDerivArray[2]);
  theTangent.SetCoord(aDerivArray[aDim], aDerivArray[aDim + 1], aDerivArray[aDim + 2]);
  theCurvature.SetCoord(aDerivArray[aShift2], aDerivArray[aShift2 + 1], aDerivArray[aShift2 + 2]);
  theTorsion.SetCoord(aDerivArray[aShift3], aDerivArray[aShift3 + 1], aDerivArray[aShift3 + 2]);
}
