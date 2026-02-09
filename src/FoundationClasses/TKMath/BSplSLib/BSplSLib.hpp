#pragma once

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#ifndef _Standard_PrimitiveTypes_HeaderFile
#endif

class BSplSLib_EvaluatorFunction
{
public:
  BSplSLib_EvaluatorFunction() = default;

  virtual ~BSplSLib_EvaluatorFunction() = default;

  virtual void Evaluate(const int    theDerivativeRequest,
                        const double theUParameter,
                        const double theVParameter,
                        double&      theResult,
                        int&         theErrorCode) const = 0;

  void operator()(const int    theDerivativeRequest,
                  const double theUParameter,
                  const double theVParameter,
                  double&      theResult,
                  int&         theErrorCode) const
  {
    Evaluate(theDerivativeRequest, theUParameter, theVParameter, theResult, theErrorCode);
  }

private:
  BSplSLib_EvaluatorFunction(const BSplSLib_EvaluatorFunction&) = default;

  void operator=(const BSplSLib_EvaluatorFunction&) {}
};

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>

class gp_Pnt;
class gp_Vec;

class BSplSLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void RationalDerivative(const int  UDeg,
                                                 const int  VDeg,
                                                 const int  N,
                                                 const int  M,
                                                 double&    Ders,
                                                 double&    RDers,
                                                 const bool All = true);

  Standard_EXPORT static void D0(const double                      U,
                                 const double                      V,
                                 const int                         UIndex,
                                 const int                         VIndex,
                                 const NCollection_Array2<gp_Pnt>& Poles,
                                 const NCollection_Array2<double>* Weights,
                                 const NCollection_Array1<double>& UKnots,
                                 const NCollection_Array1<double>& VKnots,
                                 const NCollection_Array1<int>*    UMults,
                                 const NCollection_Array1<int>*    VMults,
                                 const int                         UDegree,
                                 const int                         VDegree,
                                 const bool                        URat,
                                 const bool                        VRat,
                                 const bool                        UPer,
                                 const bool                        VPer,
                                 gp_Pnt&                           P);

  Standard_EXPORT static void D1(const double                      U,
                                 const double                      V,
                                 const int                         UIndex,
                                 const int                         VIndex,
                                 const NCollection_Array2<gp_Pnt>& Poles,
                                 const NCollection_Array2<double>* Weights,
                                 const NCollection_Array1<double>& UKnots,
                                 const NCollection_Array1<double>& VKnots,
                                 const NCollection_Array1<int>*    UMults,
                                 const NCollection_Array1<int>*    VMults,
                                 const int                         Degree,
                                 const int                         VDegree,
                                 const bool                        URat,
                                 const bool                        VRat,
                                 const bool                        UPer,
                                 const bool                        VPer,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           Vu,
                                 gp_Vec&                           Vv);

  Standard_EXPORT static void D2(const double                      U,
                                 const double                      V,
                                 const int                         UIndex,
                                 const int                         VIndex,
                                 const NCollection_Array2<gp_Pnt>& Poles,
                                 const NCollection_Array2<double>* Weights,
                                 const NCollection_Array1<double>& UKnots,
                                 const NCollection_Array1<double>& VKnots,
                                 const NCollection_Array1<int>*    UMults,
                                 const NCollection_Array1<int>*    VMults,
                                 const int                         UDegree,
                                 const int                         VDegree,
                                 const bool                        URat,
                                 const bool                        VRat,
                                 const bool                        UPer,
                                 const bool                        VPer,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           Vu,
                                 gp_Vec&                           Vv,
                                 gp_Vec&                           Vuu,
                                 gp_Vec&                           Vvv,
                                 gp_Vec&                           Vuv);

  Standard_EXPORT static void D3(const double                      U,
                                 const double                      V,
                                 const int                         UIndex,
                                 const int                         VIndex,
                                 const NCollection_Array2<gp_Pnt>& Poles,
                                 const NCollection_Array2<double>* Weights,
                                 const NCollection_Array1<double>& UKnots,
                                 const NCollection_Array1<double>& VKnots,
                                 const NCollection_Array1<int>*    UMults,
                                 const NCollection_Array1<int>*    VMults,
                                 const int                         UDegree,
                                 const int                         VDegree,
                                 const bool                        URat,
                                 const bool                        VRat,
                                 const bool                        UPer,
                                 const bool                        VPer,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           Vu,
                                 gp_Vec&                           Vv,
                                 gp_Vec&                           Vuu,
                                 gp_Vec&                           Vvv,
                                 gp_Vec&                           Vuv,
                                 gp_Vec&                           Vuuu,
                                 gp_Vec&                           Vvvv,
                                 gp_Vec&                           Vuuv,
                                 gp_Vec&                           Vuvv);

  Standard_EXPORT static void DN(const double                      U,
                                 const double                      V,
                                 const int                         Nu,
                                 const int                         Nv,
                                 const int                         UIndex,
                                 const int                         VIndex,
                                 const NCollection_Array2<gp_Pnt>& Poles,
                                 const NCollection_Array2<double>* Weights,
                                 const NCollection_Array1<double>& UKnots,
                                 const NCollection_Array1<double>& VKnots,
                                 const NCollection_Array1<int>*    UMults,
                                 const NCollection_Array1<int>*    VMults,
                                 const int                         UDegree,
                                 const int                         VDegree,
                                 const bool                        URat,
                                 const bool                        VRat,
                                 const bool                        UPer,
                                 const bool                        VPer,
                                 gp_Vec&                           Vn);

  Standard_EXPORT static void Iso(const double                      Param,
                                  const bool                        IsU,
                                  const NCollection_Array2<gp_Pnt>& Poles,
                                  const NCollection_Array2<double>* Weights,
                                  const NCollection_Array1<double>& Knots,
                                  const NCollection_Array1<int>*    Mults,
                                  const int                         Degree,
                                  const bool                        Periodic,
                                  NCollection_Array1<gp_Pnt>&       CPoles,
                                  NCollection_Array1<double>*       CWeights);

  Standard_EXPORT static void Reverse(NCollection_Array2<gp_Pnt>& Poles,
                                      const int                   Last,
                                      const bool                  UDirection);

  Standard_EXPORT static void HomogeneousD0(const double                      U,
                                            const double                      V,
                                            const int                         UIndex,
                                            const int                         VIndex,
                                            const NCollection_Array2<gp_Pnt>& Poles,
                                            const NCollection_Array2<double>* Weights,
                                            const NCollection_Array1<double>& UKnots,
                                            const NCollection_Array1<double>& VKnots,
                                            const NCollection_Array1<int>*    UMults,
                                            const NCollection_Array1<int>*    VMults,
                                            const int                         UDegree,
                                            const int                         VDegree,
                                            const bool                        URat,
                                            const bool                        VRat,
                                            const bool                        UPer,
                                            const bool                        VPer,
                                            double&                           W,
                                            gp_Pnt&                           P);

  Standard_EXPORT static void HomogeneousD1(const double                      U,
                                            const double                      V,
                                            const int                         UIndex,
                                            const int                         VIndex,
                                            const NCollection_Array2<gp_Pnt>& Poles,
                                            const NCollection_Array2<double>* Weights,
                                            const NCollection_Array1<double>& UKnots,
                                            const NCollection_Array1<double>& VKnots,
                                            const NCollection_Array1<int>*    UMults,
                                            const NCollection_Array1<int>*    VMults,
                                            const int                         UDegree,
                                            const int                         VDegree,
                                            const bool                        URat,
                                            const bool                        VRat,
                                            const bool                        UPer,
                                            const bool                        VPer,
                                            gp_Pnt&                           N,
                                            gp_Vec&                           Nu,
                                            gp_Vec&                           Nv,
                                            double&                           D,
                                            double&                           Du,
                                            double&                           Dv);

  Standard_EXPORT static void Reverse(NCollection_Array2<double>& Weights,
                                      const int                   Last,
                                      const bool                  UDirection);

  Standard_EXPORT static bool IsRational(const NCollection_Array2<double>& Weights,
                                         const int                         I1,
                                         const int                         I2,
                                         const int                         J1,
                                         const int                         J2,
                                         const double                      Epsilon = 0.0);

  Standard_EXPORT static void SetPoles(const NCollection_Array2<gp_Pnt>& Poles,
                                       NCollection_Array1<double>&       FP,
                                       const bool                        UDirection);

  Standard_EXPORT static void SetPoles(const NCollection_Array2<gp_Pnt>& Poles,
                                       const NCollection_Array2<double>& Weights,
                                       NCollection_Array1<double>&       FP,
                                       const bool                        UDirection);

  Standard_EXPORT static void GetPoles(const NCollection_Array1<double>& FP,
                                       NCollection_Array2<gp_Pnt>&       Poles,
                                       const bool                        UDirection);

  Standard_EXPORT static void GetPoles(const NCollection_Array1<double>& FP,
                                       NCollection_Array2<gp_Pnt>&       Poles,
                                       NCollection_Array2<double>&       Weights,
                                       const bool                        UDirection);

  Standard_EXPORT static void MovePoint(const double                      U,
                                        const double                      V,
                                        const gp_Vec&                     Displ,
                                        const int                         UIndex1,
                                        const int                         UIndex2,
                                        const int                         VIndex1,
                                        const int                         VIndex2,
                                        const int                         UDegree,
                                        const int                         VDegree,
                                        const bool                        Rational,
                                        const NCollection_Array2<gp_Pnt>& Poles,
                                        const NCollection_Array2<double>& Weights,
                                        const NCollection_Array1<double>& UFlatKnots,
                                        const NCollection_Array1<double>& VFlatKnots,
                                        int&                              UFirstIndex,
                                        int&                              ULastIndex,
                                        int&                              VFirstIndex,
                                        int&                              VLastIndex,
                                        NCollection_Array2<gp_Pnt>&       NewPoles);

  Standard_EXPORT static void InsertKnots(const bool                        UDirection,
                                          const int                         Degree,
                                          const bool                        Periodic,
                                          const NCollection_Array2<gp_Pnt>& Poles,
                                          const NCollection_Array2<double>* Weights,
                                          const NCollection_Array1<double>& Knots,
                                          const NCollection_Array1<int>&    Mults,
                                          const NCollection_Array1<double>& AddKnots,
                                          const NCollection_Array1<int>*    AddMults,
                                          NCollection_Array2<gp_Pnt>&       NewPoles,
                                          NCollection_Array2<double>*       NewWeights,
                                          NCollection_Array1<double>&       NewKnots,
                                          NCollection_Array1<int>&          NewMults,
                                          const double                      Epsilon,
                                          const bool                        Add = true);

  Standard_EXPORT static bool RemoveKnot(const bool                        UDirection,
                                         const int                         Index,
                                         const int                         Mult,
                                         const int                         Degree,
                                         const bool                        Periodic,
                                         const NCollection_Array2<gp_Pnt>& Poles,
                                         const NCollection_Array2<double>* Weights,
                                         const NCollection_Array1<double>& Knots,
                                         const NCollection_Array1<int>&    Mults,
                                         NCollection_Array2<gp_Pnt>&       NewPoles,
                                         NCollection_Array2<double>*       NewWeights,
                                         NCollection_Array1<double>&       NewKnots,
                                         NCollection_Array1<int>&          NewMults,
                                         const double                      Tolerance);

  Standard_EXPORT static void IncreaseDegree(const bool                        UDirection,
                                             const int                         Degree,
                                             const int                         NewDegree,
                                             const bool                        Periodic,
                                             const NCollection_Array2<gp_Pnt>& Poles,
                                             const NCollection_Array2<double>* Weights,
                                             const NCollection_Array1<double>& Knots,
                                             const NCollection_Array1<int>&    Mults,
                                             NCollection_Array2<gp_Pnt>&       NewPoles,
                                             NCollection_Array2<double>*       NewWeights,
                                             NCollection_Array1<double>&       NewKnots,
                                             NCollection_Array1<int>&          NewMults);

  Standard_EXPORT static void Unperiodize(const bool                        UDirection,
                                          const int                         Degree,
                                          const NCollection_Array1<int>&    Mults,
                                          const NCollection_Array1<double>& Knots,
                                          const NCollection_Array2<gp_Pnt>& Poles,
                                          const NCollection_Array2<double>* Weights,
                                          NCollection_Array1<int>&          NewMults,
                                          NCollection_Array1<double>&       NewKnots,
                                          NCollection_Array2<gp_Pnt>&       NewPoles,
                                          NCollection_Array2<double>*       NewWeights);

  static NCollection_Array2<double>* NoWeights();

  Standard_EXPORT static void BuildCache(const double                      U,
                                         const double                      V,
                                         const double                      USpanDomain,
                                         const double                      VSpanDomain,
                                         const bool                        UPeriodicFlag,
                                         const bool                        VPeriodicFlag,
                                         const int                         UDegree,
                                         const int                         VDegree,
                                         const int                         UIndex,
                                         const int                         VIndex,
                                         const NCollection_Array1<double>& UFlatKnots,
                                         const NCollection_Array1<double>& VFlatKnots,
                                         const NCollection_Array2<gp_Pnt>& Poles,
                                         const NCollection_Array2<double>* Weights,
                                         NCollection_Array2<gp_Pnt>&       CachePoles,
                                         NCollection_Array2<double>*       CacheWeights);

  Standard_EXPORT static void BuildCache(const double                      theU,
                                         const double                      theV,
                                         const double                      theUSpanDomain,
                                         const double                      theVSpanDomain,
                                         const bool                        theUPeriodic,
                                         const bool                        theVPeriodic,
                                         const int                         theUDegree,
                                         const int                         theVDegree,
                                         const int                         theUIndex,
                                         const int                         theVIndex,
                                         const NCollection_Array1<double>& theUFlatKnots,
                                         const NCollection_Array1<double>& theVFlatKnots,
                                         const NCollection_Array2<gp_Pnt>& thePoles,
                                         const NCollection_Array2<double>* theWeights,
                                         NCollection_Array2<double>&       theCacheArray);

  Standard_EXPORT static void CacheD0(const double                      U,
                                      const double                      V,
                                      const int                         UDegree,
                                      const int                         VDegree,
                                      const double                      UCacheParameter,
                                      const double                      VCacheParameter,
                                      const double                      USpanLenght,
                                      const double                      VSpanLength,
                                      const NCollection_Array2<gp_Pnt>& Poles,
                                      const NCollection_Array2<double>* Weights,
                                      gp_Pnt&                           Point);

  static void CoefsD0(const double                      U,
                      const double                      V,
                      const NCollection_Array2<gp_Pnt>& Poles,
                      const NCollection_Array2<double>* Weights,
                      gp_Pnt&                           Point);

  Standard_EXPORT static void CacheD1(const double                      U,
                                      const double                      V,
                                      const int                         UDegree,
                                      const int                         VDegree,
                                      const double                      UCacheParameter,
                                      const double                      VCacheParameter,
                                      const double                      USpanLenght,
                                      const double                      VSpanLength,
                                      const NCollection_Array2<gp_Pnt>& Poles,
                                      const NCollection_Array2<double>* Weights,
                                      gp_Pnt&                           Point,
                                      gp_Vec&                           VecU,
                                      gp_Vec&                           VecV);

  static void CoefsD1(const double                      U,
                      const double                      V,
                      const NCollection_Array2<gp_Pnt>& Poles,
                      const NCollection_Array2<double>* Weights,
                      gp_Pnt&                           Point,
                      gp_Vec&                           VecU,
                      gp_Vec&                           VecV);

  Standard_EXPORT static void CacheD2(const double                      U,
                                      const double                      V,
                                      const int                         UDegree,
                                      const int                         VDegree,
                                      const double                      UCacheParameter,
                                      const double                      VCacheParameter,
                                      const double                      USpanLenght,
                                      const double                      VSpanLength,
                                      const NCollection_Array2<gp_Pnt>& Poles,
                                      const NCollection_Array2<double>* Weights,
                                      gp_Pnt&                           Point,
                                      gp_Vec&                           VecU,
                                      gp_Vec&                           VecV,
                                      gp_Vec&                           VecUU,
                                      gp_Vec&                           VecUV,
                                      gp_Vec&                           VecVV);

  static void CoefsD2(const double                      U,
                      const double                      V,
                      const NCollection_Array2<gp_Pnt>& Poles,
                      const NCollection_Array2<double>* Weights,
                      gp_Pnt&                           Point,
                      gp_Vec&                           VecU,
                      gp_Vec&                           VecV,
                      gp_Vec&                           VecUU,
                      gp_Vec&                           VecUV,
                      gp_Vec&                           VecVV);

  static void PolesCoefficients(const NCollection_Array2<gp_Pnt>& Poles,
                                NCollection_Array2<gp_Pnt>&       CachePoles);

  Standard_EXPORT static void PolesCoefficients(const NCollection_Array2<gp_Pnt>& Poles,
                                                const NCollection_Array2<double>* Weights,
                                                NCollection_Array2<gp_Pnt>&       CachePoles,
                                                NCollection_Array2<double>*       CacheWeights);

  Standard_EXPORT static void Resolution(const NCollection_Array2<gp_Pnt>& Poles,
                                         const NCollection_Array2<double>* Weights,
                                         const NCollection_Array1<double>& UKnots,
                                         const NCollection_Array1<double>& VKnots,
                                         const NCollection_Array1<int>&    UMults,
                                         const NCollection_Array1<int>&    VMults,
                                         const int                         UDegree,
                                         const int                         VDegree,
                                         const bool                        URat,
                                         const bool                        VRat,
                                         const bool                        UPer,
                                         const bool                        VPer,
                                         const double                      Tolerance3D,
                                         double&                           UTolerance,
                                         double&                           VTolerance);

  Standard_EXPORT static void Interpolate(const int                         UDegree,
                                          const int                         VDegree,
                                          const NCollection_Array1<double>& UFlatKnots,
                                          const NCollection_Array1<double>& VFlatKnots,
                                          const NCollection_Array1<double>& UParameters,
                                          const NCollection_Array1<double>& VParameters,
                                          NCollection_Array2<gp_Pnt>&       Poles,
                                          NCollection_Array2<double>&       Weights,
                                          int&                              InversionProblem);

  Standard_EXPORT static void Interpolate(const int                         UDegree,
                                          const int                         VDegree,
                                          const NCollection_Array1<double>& UFlatKnots,
                                          const NCollection_Array1<double>& VFlatKnots,
                                          const NCollection_Array1<double>& UParameters,
                                          const NCollection_Array1<double>& VParameters,
                                          NCollection_Array2<gp_Pnt>&       Poles,
                                          int&                              InversionProblem);

  Standard_EXPORT static void FunctionMultiply(const BSplSLib_EvaluatorFunction& Function,
                                               const int                         UBSplineDegree,
                                               const int                         VBSplineDegree,
                                               const NCollection_Array1<double>& UBSplineKnots,
                                               const NCollection_Array1<double>& VBSplineKnots,
                                               const NCollection_Array1<int>*    UMults,
                                               const NCollection_Array1<int>*    VMults,
                                               const NCollection_Array2<gp_Pnt>& Poles,
                                               const NCollection_Array2<double>* Weights,
                                               const NCollection_Array1<double>& UFlatKnots,
                                               const NCollection_Array1<double>& VFlatKnots,
                                               const int                         UNewDegree,
                                               const int                         VNewDegree,
                                               NCollection_Array2<gp_Pnt>&       NewNumerator,
                                               NCollection_Array2<double>&       NewDenominator,
                                               int&                              theStatus);
};

#include <BSplCLib.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>

inline void BSplSLib::CoefsD0(const double                      U,
                              const double                      V,
                              const NCollection_Array2<gp_Pnt>& Poles,
                              const NCollection_Array2<double>* Weights,
                              gp_Pnt&                           Point)
{
  BSplSLib::CacheD0(U,
                    V,
                    Poles.RowLength() - 1,
                    Poles.ColLength() - 1,
                    0.,
                    0.,
                    1.,
                    1.,
                    Poles,
                    Weights,
                    Point);
}

inline void BSplSLib::CoefsD1(const double                      U,
                              const double                      V,
                              const NCollection_Array2<gp_Pnt>& Poles,
                              const NCollection_Array2<double>* Weights,
                              gp_Pnt&                           Point,
                              gp_Vec&                           VecU,
                              gp_Vec&                           VecV)
{
  BSplSLib::CacheD1(U,
                    V,
                    Poles.RowLength() - 1,
                    Poles.ColLength() - 1,
                    0.,
                    0.,
                    1.,
                    1.,
                    Poles,
                    Weights,
                    Point,
                    VecU,
                    VecV);
}

inline void BSplSLib::CoefsD2(const double                      U,
                              const double                      V,
                              const NCollection_Array2<gp_Pnt>& Poles,
                              const NCollection_Array2<double>* Weights,
                              gp_Pnt&                           Point,
                              gp_Vec&                           VecU,
                              gp_Vec&                           VecV,
                              gp_Vec&                           VecUU,
                              gp_Vec&                           VecUV,
                              gp_Vec&                           VecVV)
{
  BSplSLib::CacheD2(U,
                    V,
                    Poles.RowLength() - 1,
                    Poles.ColLength() - 1,
                    0.,
                    0.,
                    1.,
                    1.,
                    Poles,
                    Weights,
                    Point,
                    VecU,
                    VecV,
                    VecUU,
                    VecUV,
                    VecVV);
}

inline void BSplSLib::PolesCoefficients(const NCollection_Array2<gp_Pnt>& Poles,
                                        NCollection_Array2<gp_Pnt>&       CachePoles)
{
  BSplSLib::PolesCoefficients(Poles, BSplSLib::NoWeights(), CachePoles, BSplSLib::NoWeights());
}

inline NCollection_Array2<double>* BSplSLib::NoWeights()
{
  return nullptr;
}
