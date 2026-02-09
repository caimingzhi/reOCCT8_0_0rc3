#pragma once

#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

#include <BSplCLib_CacheParams.hpp>

class BSplSLib_Cache : public Standard_Transient
{
public:
  Standard_EXPORT BSplSLib_Cache(const int&                        theDegreeU,
                                 const bool&                       thePeriodicU,
                                 const NCollection_Array1<double>& theFlatKnotsU,
                                 const int&                        theDegreeV,
                                 const bool&                       thePeriodicV,
                                 const NCollection_Array1<double>& theFlatKnotsV,
                                 const NCollection_Array2<double>* theWeights = nullptr);

  Standard_EXPORT bool IsCacheValid(double theParameterU, double theParameterV) const;

  Standard_EXPORT void BuildCache(const double&                     theParameterU,
                                  const double&                     theParameterV,
                                  const NCollection_Array1<double>& theFlatKnotsU,
                                  const NCollection_Array1<double>& theFlatKnotsV,
                                  const NCollection_Array2<gp_Pnt>& thePoles,
                                  const NCollection_Array2<double>* theWeights = nullptr);

  Standard_EXPORT void D0(const double& theU, const double& theV, gp_Pnt& thePoint) const;

  Standard_EXPORT void D1(const double& theU,
                          const double& theV,
                          gp_Pnt&       thePoint,
                          gp_Vec&       theTangentU,
                          gp_Vec&       theTangentV) const;

  Standard_EXPORT void D2(const double& theU,
                          const double& theV,
                          gp_Pnt&       thePoint,
                          gp_Vec&       theTangentU,
                          gp_Vec&       theTangentV,
                          gp_Vec&       theCurvatureU,
                          gp_Vec&       theCurvatureV,
                          gp_Vec&       theCurvatureUV) const;

  Standard_EXPORT void D0Local(double theLocalU, double theLocalV, gp_Pnt& thePoint) const;

  Standard_EXPORT void D1Local(double  theLocalU,
                               double  theLocalV,
                               gp_Pnt& thePoint,
                               gp_Vec& theTangentU,
                               gp_Vec& theTangentV) const;

  Standard_EXPORT void D2Local(double  theLocalU,
                               double  theLocalV,
                               gp_Pnt& thePoint,
                               gp_Vec& theTangentU,
                               gp_Vec& theTangentV,
                               gp_Vec& theCurvatureU,
                               gp_Vec& theCurvatureV,
                               gp_Vec& theCurvatureUV) const;

  DEFINE_STANDARD_RTTIEXT(BSplSLib_Cache, Standard_Transient)

private:
  BSplSLib_Cache(const BSplSLib_Cache&) = delete;
  void operator=(const BSplSLib_Cache&) = delete;

private:
  bool                                     myIsRational;
  BSplCLib_CacheParams                     myParamsU, myParamsV;
  occ::handle<NCollection_HArray2<double>> myPolesWeights;
};
