#pragma once

#include <BSplCLib_CacheParams.hpp>

class BSplCLib_Cache : public Standard_Transient
{
public:
  Standard_EXPORT BSplCLib_Cache(const int&                          theDegree,
                                 const bool&                         thePeriodic,
                                 const NCollection_Array1<double>&   theFlatKnots,
                                 const NCollection_Array1<gp_Pnt2d>& thePoles2d,
                                 const NCollection_Array1<double>*   theWeights = nullptr);

  Standard_EXPORT BSplCLib_Cache(const int&                        theDegree,
                                 const bool&                       thePeriodic,
                                 const NCollection_Array1<double>& theFlatKnots,
                                 const NCollection_Array1<gp_Pnt>& thePoles,
                                 const NCollection_Array1<double>* theWeights = nullptr);

  Standard_EXPORT bool IsCacheValid(double theParameter) const;

  Standard_EXPORT void BuildCache(const double&                       theParameter,
                                  const NCollection_Array1<double>&   theFlatKnots,
                                  const NCollection_Array1<gp_Pnt2d>& thePoles2d,
                                  const NCollection_Array1<double>*   theWeights);

  Standard_EXPORT void BuildCache(const double&                     theParameter,
                                  const NCollection_Array1<double>& theFlatKnots,
                                  const NCollection_Array1<gp_Pnt>& thePoles,
                                  const NCollection_Array1<double>* theWeights = nullptr);

  Standard_EXPORT void D0(const double& theParameter, gp_Pnt2d& thePoint) const;
  Standard_EXPORT void D0(const double& theParameter, gp_Pnt& thePoint) const;

  Standard_EXPORT void D1(const double& theParameter,
                          gp_Pnt2d&     thePoint,
                          gp_Vec2d&     theTangent) const;
  Standard_EXPORT void D1(const double& theParameter, gp_Pnt& thePoint, gp_Vec& theTangent) const;

  Standard_EXPORT void D2(const double& theParameter,
                          gp_Pnt2d&     thePoint,
                          gp_Vec2d&     theTangent,
                          gp_Vec2d&     theCurvature) const;
  Standard_EXPORT void D2(const double& theParameter,
                          gp_Pnt&       thePoint,
                          gp_Vec&       theTangent,
                          gp_Vec&       theCurvature) const;

  Standard_EXPORT void D3(const double& theParameter,
                          gp_Pnt2d&     thePoint,
                          gp_Vec2d&     theTangent,
                          gp_Vec2d&     theCurvature,
                          gp_Vec2d&     theTorsion) const;
  Standard_EXPORT void D3(const double& theParameter,
                          gp_Pnt&       thePoint,
                          gp_Vec&       theTangent,
                          gp_Vec&       theCurvature,
                          gp_Vec&       theTorsion) const;

  Standard_EXPORT void D0Local(double theLocalParam, gp_Pnt& thePoint) const;

  Standard_EXPORT void D1Local(double theLocalParam, gp_Pnt& thePoint, gp_Vec& theTangent) const;

  Standard_EXPORT void D2Local(double  theLocalParam,
                               gp_Pnt& thePoint,
                               gp_Vec& theTangent,
                               gp_Vec& theCurvature) const;

  Standard_EXPORT void D3Local(double  theLocalParam,
                               gp_Pnt& thePoint,
                               gp_Vec& theTangent,
                               gp_Vec& theCurvature,
                               gp_Vec& theTorsion) const;

  DEFINE_STANDARD_RTTIEXT(BSplCLib_Cache, Standard_Transient)

protected:
  void calculateDerivative(double theParameter, int theDerivative, double* theDerivArray) const;

  void calculateDerivativeLocal(double  theLocalParam,
                                int     theDerivative,
                                double* theDerivArray) const;

  BSplCLib_Cache(const BSplCLib_Cache&) = delete;
  void operator=(const BSplCLib_Cache&) = delete;

private:
  bool                 myIsRational;
  BSplCLib_CacheParams myParams;
  int                  myRowLength;
  double               myPolesWeightsBuffer[128];
};
