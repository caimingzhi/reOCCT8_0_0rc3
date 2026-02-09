

#include <BSplSLib_Cache.hpp>
#include <BSplSLib.hpp>

#include <NCollection_LocalArray.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

#include <utility>

IMPLEMENT_STANDARD_RTTIEXT(BSplSLib_Cache, Standard_Transient)

namespace
{

  double* ConvertArray(const occ::handle<NCollection_HArray2<double>>& theHArray)
  {
    const NCollection_Array2<double>& anArray = theHArray->Array2();
    return (double*)&(anArray(anArray.LowerRow(), anArray.LowerCol()));
  }

  std::pair<double, double> toLocalParamsD0(double                      theU,
                                            double                      theV,
                                            const BSplCLib_CacheParams& theParamsU,
                                            const BSplCLib_CacheParams& theParamsV)
  {
    const double aNewU        = theParamsU.PeriodicNormalization(theU);
    const double aNewV        = theParamsV.PeriodicNormalization(theV);
    const double aSpanLengthU = 0.5 * theParamsU.SpanLength;
    const double aSpanStartU  = theParamsU.SpanStart + aSpanLengthU;
    const double aSpanLengthV = 0.5 * theParamsV.SpanLength;
    const double aSpanStartV  = theParamsV.SpanStart + aSpanLengthV;
    return {(aNewU - aSpanStartU) / aSpanLengthU, (aNewV - aSpanStartV) / aSpanLengthV};
  }

  std::pair<double, double> toLocalParams(double                      theU,
                                          double                      theV,
                                          const BSplCLib_CacheParams& theParamsU,
                                          const BSplCLib_CacheParams& theParamsV,
                                          double&                     theInvU,
                                          double&                     theInvV)
  {
    const double aNewU        = theParamsU.PeriodicNormalization(theU);
    const double aNewV        = theParamsV.PeriodicNormalization(theV);
    const double aSpanLengthU = 0.5 * theParamsU.SpanLength;
    const double aSpanStartU  = theParamsU.SpanStart + aSpanLengthU;
    const double aSpanLengthV = 0.5 * theParamsV.SpanLength;
    const double aSpanStartV  = theParamsV.SpanStart + aSpanLengthV;

    theInvU = 1.0 / aSpanLengthU;
    theInvV = 1.0 / aSpanLengthV;
    return {(aNewU - aSpanStartU) * theInvU, (aNewV - aSpanStartV) * theInvV};
  }

  void EvaluatePolynomials(const occ::handle<NCollection_HArray2<double>>& thePolesWeights,
                           const BSplCLib_CacheParams&                     theParamsU,
                           const BSplCLib_CacheParams&                     theParamsV,
                           const bool                                      theIsRational,
                           double                                          theLocalU,
                           double                                          theLocalV,
                           int                                             theUDerivMax,
                           int                                             theVDerivMax,
                           double*                                         theResultArray)
  {
    double* const aPolesArray = ConvertArray(thePolesWeights);
    const int     aDimension  = theIsRational ? 4 : 3;
    const int     aCacheCols  = thePolesWeights->RowLength();

    const bool isMaxU = (theParamsU.Degree > theParamsV.Degree);
    const auto [aMinParam, aMaxParam] =
      isMaxU ? std::make_pair(theLocalV, theLocalU) : std::make_pair(theLocalU, theLocalV);

    const int aMaxDeriv = isMaxU ? theUDerivMax : theVDerivMax;
    const int aMinDeriv = isMaxU ? theVDerivMax : theUDerivMax;

    const int aRowStride = (aMinDeriv + 1) * aDimension;

    NCollection_LocalArray<double> aTransientCoeffs(
      std::max((aMaxDeriv + 1) * aCacheCols, (aMinDeriv + 1) * aDimension));

    PLib::EvalPolynomial(aMaxParam,
                         aMaxDeriv,
                         isMaxU ? theParamsU.Degree : theParamsV.Degree,
                         aCacheCols,
                         aPolesArray[0],
                         aTransientCoeffs[0]);

    PLib::EvalPolynomial(aMinParam,
                         aMinDeriv,
                         isMaxU ? theParamsV.Degree : theParamsU.Degree,
                         aDimension,
                         aTransientCoeffs[0],
                         theResultArray[0]);

    if (aMaxDeriv > 0)
    {

      const int aDeriv = theIsRational ? aMinDeriv : std::min(aMinDeriv, 1);

      PLib::EvalPolynomial(aMinParam,
                           aDeriv,
                           isMaxU ? theParamsV.Degree : theParamsU.Degree,
                           aDimension,
                           aTransientCoeffs[aCacheCols],
                           theResultArray[aRowStride]);

      if (aMaxDeriv > 1)
      {

        const int aDeriv2 = theIsRational ? aMinDeriv : 0;

        if (aDeriv2 == 0)
        {
          PLib::NoDerivativeEvalPolynomial(aMinParam,
                                           isMaxU ? theParamsV.Degree : theParamsU.Degree,
                                           aDimension,
                                           (isMaxU ? theParamsV.Degree : theParamsU.Degree)
                                             * aDimension,
                                           aTransientCoeffs[aCacheCols << 1],
                                           theResultArray[aRowStride << 1]);
        }
        else
        {
          PLib::EvalPolynomial(aMinParam,
                               aDeriv2,
                               isMaxU ? theParamsV.Degree : theParamsU.Degree,
                               aDimension,
                               aTransientCoeffs[aCacheCols << 1],
                               theResultArray[aRowStride << 1]);
        }
      }
    }

    if (theIsRational)
    {

      const int                      aResultSize = (theUDerivMax + 1) * (theVDerivMax + 1) * 3;
      NCollection_LocalArray<double> aTempStorage(aResultSize);

      if (isMaxU)
      {
        BSplSLib::RationalDerivative(theUDerivMax,
                                     theVDerivMax,
                                     theUDerivMax,
                                     theVDerivMax,
                                     theResultArray[0],
                                     aTempStorage[0]);
      }
      else
      {

        BSplSLib::RationalDerivative(theVDerivMax,
                                     theUDerivMax,
                                     theVDerivMax,
                                     theUDerivMax,
                                     theResultArray[0],
                                     aTempStorage[0]);
      }

      for (int i = 0; i < aResultSize; ++i)
      {
        theResultArray[i] = aTempStorage[i];
      }
    }
  }
} // namespace

BSplSLib_Cache::BSplSLib_Cache(const int&                        theDegreeU,
                               const bool&                       thePeriodicU,
                               const NCollection_Array1<double>& theFlatKnotsU,
                               const int&                        theDegreeV,
                               const bool&                       thePeriodicV,
                               const NCollection_Array1<double>& theFlatKnotsV,
                               const NCollection_Array2<double>* theWeights)
    : myIsRational(theWeights != nullptr),
      myParamsU(theDegreeU, thePeriodicU, theFlatKnotsU),
      myParamsV(theDegreeV, thePeriodicV, theFlatKnotsV)
{
  int aMinDegree   = std::min(theDegreeU, theDegreeV);
  int aMaxDegree   = std::max(theDegreeU, theDegreeV);
  int aPWColNumber = (myIsRational ? 4 : 3);
  myPolesWeights =
    new NCollection_HArray2<double>(1, aMaxDegree + 1, 1, aPWColNumber * (aMinDegree + 1));
}

bool BSplSLib_Cache::IsCacheValid(double theParameterU, double theParameterV) const
{
  return myParamsU.IsCacheValid(theParameterU) && myParamsV.IsCacheValid(theParameterV);
}

void BSplSLib_Cache::BuildCache(const double&                     theParameterU,
                                const double&                     theParameterV,
                                const NCollection_Array1<double>& theFlatKnotsU,
                                const NCollection_Array1<double>& theFlatKnotsV,
                                const NCollection_Array2<gp_Pnt>& thePoles,
                                const NCollection_Array2<double>* theWeights)
{

  double aNewParamU = myParamsU.PeriodicNormalization(theParameterU);
  double aNewParamV = myParamsV.PeriodicNormalization(theParameterV);

  myParamsU.LocateParameter(aNewParamU, theFlatKnotsU);
  myParamsV.LocateParameter(aNewParamV, theFlatKnotsV);

  double aSpanLengthU = 0.5 * myParamsU.SpanLength;
  double aSpanStartU  = myParamsU.SpanStart + aSpanLengthU;
  double aSpanLengthV = 0.5 * myParamsV.SpanLength;
  double aSpanStartV  = myParamsV.SpanStart + aSpanLengthV;

  BSplSLib::BuildCache(aSpanStartU,
                       aSpanStartV,
                       aSpanLengthU,
                       aSpanLengthV,
                       myParamsU.IsPeriodic,
                       myParamsV.IsPeriodic,
                       myParamsU.Degree,
                       myParamsV.Degree,
                       myParamsU.SpanIndex,
                       myParamsV.SpanIndex,
                       theFlatKnotsU,
                       theFlatKnotsV,
                       thePoles,
                       theWeights,
                       myPolesWeights->ChangeArray2());
}

void BSplSLib_Cache::D0(const double& theU, const double& theV, gp_Pnt& thePoint) const
{
  const auto [aLocalU, aLocalV] = toLocalParamsD0(theU, theV, myParamsU, myParamsV);
  D0Local(aLocalU, aLocalV, thePoint);
}

void BSplSLib_Cache::D0Local(double theLocalU, double theLocalV, gp_Pnt& thePoint) const
{
  double* aPolesArray = ConvertArray(myPolesWeights);
  double  aPoint[4]   = {};

  const int  aDimension               = myIsRational ? 4 : 3;
  const int  aCacheCols               = myPolesWeights->RowLength();
  const bool isMaxU                   = (myParamsU.Degree > myParamsV.Degree);
  const auto [aMinDegree, aMaxDegree] = std::minmax(myParamsU.Degree, myParamsV.Degree);
  const auto [aMinParam, aMaxParam] =
    isMaxU ? std::make_pair(theLocalV, theLocalU) : std::make_pair(theLocalU, theLocalV);

  NCollection_LocalArray<double> aTransientCoeffs(aCacheCols);

  PLib::NoDerivativeEvalPolynomial(aMaxParam,
                                   aMaxDegree,
                                   aCacheCols,
                                   aMaxDegree * aCacheCols,
                                   aPolesArray[0],
                                   aTransientCoeffs[0]);

  PLib::NoDerivativeEvalPolynomial(aMinParam,
                                   aMinDegree,
                                   aDimension,
                                   aDimension * aMinDegree,
                                   aTransientCoeffs[0],
                                   aPoint[0]);

  thePoint.SetCoord(aPoint[0], aPoint[1], aPoint[2]);
  if (myIsRational)
  {
    thePoint.ChangeCoord().Divide(aPoint[3]);
  }
}

void BSplSLib_Cache::D1Local(double  theLocalU,
                             double  theLocalV,
                             gp_Pnt& thePoint,
                             gp_Vec& theTangentU,
                             gp_Vec& theTangentV) const
{
  double aPntDeriv[16] = {};
  EvaluatePolynomials(myPolesWeights,
                      myParamsU,
                      myParamsV,
                      myIsRational,
                      theLocalU,
                      theLocalV,
                      1,
                      1,
                      aPntDeriv);

  const int aDimension = 3;

  thePoint.SetCoord(aPntDeriv[0], aPntDeriv[1], aPntDeriv[2]);

  if (myParamsU.Degree > myParamsV.Degree)
  {
    theTangentV.SetCoord(aPntDeriv[aDimension],
                         aPntDeriv[aDimension + 1],
                         aPntDeriv[aDimension + 2]);
    theTangentU.SetCoord(aPntDeriv[aDimension << 1],
                         aPntDeriv[(aDimension << 1) + 1],
                         aPntDeriv[(aDimension << 1) + 2]);
  }
  else
  {
    theTangentU.SetCoord(aPntDeriv[aDimension],
                         aPntDeriv[aDimension + 1],
                         aPntDeriv[aDimension + 2]);
    theTangentV.SetCoord(aPntDeriv[aDimension << 1],
                         aPntDeriv[(aDimension << 1) + 1],
                         aPntDeriv[(aDimension << 1) + 2]);
  }

  const double aSpanLengthU = 0.5 * myParamsU.SpanLength;
  const double aSpanLengthV = 0.5 * myParamsV.SpanLength;
  theTangentU.Divide(aSpanLengthU);
  theTangentV.Divide(aSpanLengthV);
}

void BSplSLib_Cache::D2Local(double  theLocalU,
                             double  theLocalV,
                             gp_Pnt& thePoint,
                             gp_Vec& theTangentU,
                             gp_Vec& theTangentV,
                             gp_Vec& theCurvatureU,
                             gp_Vec& theCurvatureV,
                             gp_Vec& theCurvatureUV) const
{
  double aPntDeriv[36] = {};
  EvaluatePolynomials(myPolesWeights,
                      myParamsU,
                      myParamsV,
                      myIsRational,
                      theLocalU,
                      theLocalV,
                      2,
                      2,
                      aPntDeriv);

  const int aDimension = 3;
  const int aShift     = aDimension;
  const int aShift2    = aDimension << 1;
  const int aShift3    = aShift2 + aDimension;
  const int aShift4    = aShift3 + aDimension;
  const int aShift6    = 6 * aDimension;

  thePoint.SetCoord(aPntDeriv[0], aPntDeriv[1], aPntDeriv[2]);

  if (myParamsU.Degree > myParamsV.Degree)
  {
    theTangentV.SetCoord(aPntDeriv[aShift], aPntDeriv[aShift + 1], aPntDeriv[aShift + 2]);
    theCurvatureV.SetCoord(aPntDeriv[aShift2], aPntDeriv[aShift2 + 1], aPntDeriv[aShift2 + 2]);
    theTangentU.SetCoord(aPntDeriv[aShift3], aPntDeriv[aShift3 + 1], aPntDeriv[aShift3 + 2]);
    theCurvatureUV.SetCoord(aPntDeriv[aShift4], aPntDeriv[aShift4 + 1], aPntDeriv[aShift4 + 2]);
    theCurvatureU.SetCoord(aPntDeriv[aShift6], aPntDeriv[aShift6 + 1], aPntDeriv[aShift6 + 2]);
  }
  else
  {

    theTangentU.SetCoord(aPntDeriv[aShift], aPntDeriv[aShift + 1], aPntDeriv[aShift + 2]);
    theCurvatureU.SetCoord(aPntDeriv[aShift2], aPntDeriv[aShift2 + 1], aPntDeriv[aShift2 + 2]);
    theTangentV.SetCoord(aPntDeriv[aShift3], aPntDeriv[aShift3 + 1], aPntDeriv[aShift3 + 2]);
    theCurvatureUV.SetCoord(aPntDeriv[aShift4], aPntDeriv[aShift4 + 1], aPntDeriv[aShift4 + 2]);
    theCurvatureV.SetCoord(aPntDeriv[aShift6], aPntDeriv[aShift6 + 1], aPntDeriv[aShift6 + 2]);
  }

  const double aSpanLengthU  = 0.5 * myParamsU.SpanLength;
  const double aSpanLengthV  = 0.5 * myParamsV.SpanLength;
  const double aSpanLengthU2 = aSpanLengthU * aSpanLengthU;
  const double aSpanLengthV2 = aSpanLengthV * aSpanLengthV;
  theTangentU.Divide(aSpanLengthU);
  theTangentV.Divide(aSpanLengthV);
  theCurvatureU.Divide(aSpanLengthU2);
  theCurvatureV.Divide(aSpanLengthV2);
  theCurvatureUV.Divide(aSpanLengthU * aSpanLengthV);
}

void BSplSLib_Cache::D1(const double& theU,
                        const double& theV,
                        gp_Pnt&       thePoint,
                        gp_Vec&       theTangentU,
                        gp_Vec&       theTangentV) const
{

  double anInvU = 0.0, anInvV = 0.0;
  const auto [aLocalU, aLocalV] = toLocalParams(theU, theV, myParamsU, myParamsV, anInvU, anInvV);

  double aPntDeriv[16] = {};
  EvaluatePolynomials(myPolesWeights,
                      myParamsU,
                      myParamsV,
                      myIsRational,
                      aLocalU,
                      aLocalV,
                      1,
                      1,
                      aPntDeriv);

  const int aDimension = 3;
  thePoint.SetCoord(aPntDeriv[0], aPntDeriv[1], aPntDeriv[2]);

  if (myParamsU.Degree > myParamsV.Degree)
  {
    theTangentV.SetCoord(aPntDeriv[aDimension],
                         aPntDeriv[aDimension + 1],
                         aPntDeriv[aDimension + 2]);
    theTangentU.SetCoord(aPntDeriv[aDimension << 1],
                         aPntDeriv[(aDimension << 1) + 1],
                         aPntDeriv[(aDimension << 1) + 2]);
  }
  else
  {
    theTangentU.SetCoord(aPntDeriv[aDimension],
                         aPntDeriv[aDimension + 1],
                         aPntDeriv[aDimension + 2]);
    theTangentV.SetCoord(aPntDeriv[aDimension << 1],
                         aPntDeriv[(aDimension << 1) + 1],
                         aPntDeriv[(aDimension << 1) + 2]);
  }

  theTangentU.Multiply(anInvU);
  theTangentV.Multiply(anInvV);
}

void BSplSLib_Cache::D2(const double& theU,
                        const double& theV,
                        gp_Pnt&       thePoint,
                        gp_Vec&       theTangentU,
                        gp_Vec&       theTangentV,
                        gp_Vec&       theCurvatureU,
                        gp_Vec&       theCurvatureV,
                        gp_Vec&       theCurvatureUV) const
{

  double anInvU = 0.0, anInvV = 0.0;
  const auto [aLocalU, aLocalV] = toLocalParams(theU, theV, myParamsU, myParamsV, anInvU, anInvV);

  double aPntDeriv[36] = {};
  EvaluatePolynomials(myPolesWeights,
                      myParamsU,
                      myParamsV,
                      myIsRational,
                      aLocalU,
                      aLocalV,
                      2,
                      2,
                      aPntDeriv);

  const int aDimension = 3;
  const int aShift     = aDimension;
  const int aShift2    = aDimension << 1;
  const int aShift3    = aShift2 + aDimension;
  const int aShift4    = aShift3 + aDimension;
  const int aShift6    = 6 * aDimension;

  thePoint.SetCoord(aPntDeriv[0], aPntDeriv[1], aPntDeriv[2]);

  if (myParamsU.Degree > myParamsV.Degree)
  {
    theTangentV.SetCoord(aPntDeriv[aShift], aPntDeriv[aShift + 1], aPntDeriv[aShift + 2]);
    theCurvatureV.SetCoord(aPntDeriv[aShift2], aPntDeriv[aShift2 + 1], aPntDeriv[aShift2 + 2]);
    theTangentU.SetCoord(aPntDeriv[aShift3], aPntDeriv[aShift3 + 1], aPntDeriv[aShift3 + 2]);
    theCurvatureUV.SetCoord(aPntDeriv[aShift4], aPntDeriv[aShift4 + 1], aPntDeriv[aShift4 + 2]);
    theCurvatureU.SetCoord(aPntDeriv[aShift6], aPntDeriv[aShift6 + 1], aPntDeriv[aShift6 + 2]);
  }
  else
  {
    theTangentU.SetCoord(aPntDeriv[aShift], aPntDeriv[aShift + 1], aPntDeriv[aShift + 2]);
    theCurvatureU.SetCoord(aPntDeriv[aShift2], aPntDeriv[aShift2 + 1], aPntDeriv[aShift2 + 2]);
    theTangentV.SetCoord(aPntDeriv[aShift3], aPntDeriv[aShift3 + 1], aPntDeriv[aShift3 + 2]);
    theCurvatureUV.SetCoord(aPntDeriv[aShift4], aPntDeriv[aShift4 + 1], aPntDeriv[aShift4 + 2]);
    theCurvatureV.SetCoord(aPntDeriv[aShift6], aPntDeriv[aShift6 + 1], aPntDeriv[aShift6 + 2]);
  }

  theTangentU.Multiply(anInvU);
  theTangentV.Multiply(anInvV);
  theCurvatureU.Multiply(anInvU * anInvU);
  theCurvatureV.Multiply(anInvV * anInvV);
  theCurvatureUV.Multiply(anInvU * anInvV);
}
