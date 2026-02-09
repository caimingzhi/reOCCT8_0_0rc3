#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Boolean.hpp>
#include <GeomAbs_Shape.hpp>
class math_Matrix;

class PLib
{
public:
  DEFINE_STANDARD_ALLOC

  inline static NCollection_Array1<double>* NoWeights() { return nullptr; }

  inline static NCollection_Array2<double>* NoWeights2() { return nullptr; }

  Standard_EXPORT static void SetPoles(const NCollection_Array1<gp_Pnt>& Poles,
                                       NCollection_Array1<double>&       FP);

  Standard_EXPORT static void SetPoles(const NCollection_Array1<gp_Pnt>& Poles,
                                       const NCollection_Array1<double>& Weights,
                                       NCollection_Array1<double>&       FP);

  Standard_EXPORT static void GetPoles(const NCollection_Array1<double>& FP,
                                       NCollection_Array1<gp_Pnt>&       Poles);

  Standard_EXPORT static void GetPoles(const NCollection_Array1<double>& FP,
                                       NCollection_Array1<gp_Pnt>&       Poles,
                                       NCollection_Array1<double>&       Weights);

  Standard_EXPORT static void SetPoles(const NCollection_Array1<gp_Pnt2d>& Poles,
                                       NCollection_Array1<double>&         FP);

  Standard_EXPORT static void SetPoles(const NCollection_Array1<gp_Pnt2d>& Poles,
                                       const NCollection_Array1<double>&   Weights,
                                       NCollection_Array1<double>&         FP);

  Standard_EXPORT static void GetPoles(const NCollection_Array1<double>& FP,
                                       NCollection_Array1<gp_Pnt2d>&     Poles);

  Standard_EXPORT static void GetPoles(const NCollection_Array1<double>& FP,
                                       NCollection_Array1<gp_Pnt2d>&     Poles,
                                       NCollection_Array1<double>&       Weights);

  Standard_EXPORT static double Bin(const int N, const int P);

  Standard_EXPORT static void RationalDerivative(const int  Degree,
                                                 const int  N,
                                                 const int  Dimension,
                                                 double&    Ders,
                                                 double&    RDers,
                                                 const bool All = true);

  Standard_EXPORT static void RationalDerivatives(const int DerivativesRequest,
                                                  const int Dimension,
                                                  double&   PolesDerivatives,
                                                  double&   WeightsDerivatives,
                                                  double&   RationalDerivates);

  Standard_EXPORT static void EvalPolynomial(const double  U,
                                             const int     DerivativeOrder,
                                             const int     Degree,
                                             const int     Dimension,
                                             const double& PolynomialCoeff,
                                             double&       Results);

  Standard_EXPORT static void NoDerivativeEvalPolynomial(const double  U,
                                                         const int     Degree,
                                                         const int     Dimension,
                                                         const int     DegreeDimension,
                                                         const double& PolynomialCoeff,
                                                         double&       Results);

  Standard_EXPORT static void EvalPoly2Var(const double U,
                                           const double V,
                                           const int    UDerivativeOrder,
                                           const int    VDerivativeOrder,
                                           const int    UDegree,
                                           const int    VDegree,
                                           const int    Dimension,
                                           double&      PolynomialCoeff,
                                           double&      Results);

  Standard_EXPORT static int EvalLagrange(const double U,
                                          const int    DerivativeOrder,
                                          const int    Degree,
                                          const int    Dimension,
                                          double&      ValueArray,
                                          double&      ParameterArray,
                                          double&      Results);

  Standard_EXPORT static int EvalCubicHermite(const double U,
                                              const int    DerivativeOrder,
                                              const int    Dimension,
                                              double&      ValueArray,
                                              double&      DerivativeArray,
                                              double&      ParameterArray,
                                              double&      Results);

  Standard_EXPORT static bool HermiteCoefficients(const double FirstParameter,
                                                  const double LastParameter,
                                                  const int    FirstOrder,
                                                  const int    LastOrder,
                                                  math_Matrix& MatrixCoefs);

  Standard_EXPORT static void CoefficientsPoles(const NCollection_Array1<gp_Pnt>& Coefs,
                                                const NCollection_Array1<double>* WCoefs,
                                                NCollection_Array1<gp_Pnt>&       Poles,
                                                NCollection_Array1<double>*       WPoles);

  Standard_EXPORT static void CoefficientsPoles(const NCollection_Array1<gp_Pnt2d>& Coefs,
                                                const NCollection_Array1<double>*   WCoefs,
                                                NCollection_Array1<gp_Pnt2d>&       Poles,
                                                NCollection_Array1<double>*         WPoles);

  Standard_EXPORT static void CoefficientsPoles(const NCollection_Array1<double>& Coefs,
                                                const NCollection_Array1<double>* WCoefs,
                                                NCollection_Array1<double>&       Poles,
                                                NCollection_Array1<double>*       WPoles);

  Standard_EXPORT static void CoefficientsPoles(const int                         dim,
                                                const NCollection_Array1<double>& Coefs,
                                                const NCollection_Array1<double>* WCoefs,
                                                NCollection_Array1<double>&       Poles,
                                                NCollection_Array1<double>*       WPoles);

  Standard_EXPORT static void Trimming(const double                U1,
                                       const double                U2,
                                       NCollection_Array1<gp_Pnt>& Coeffs,
                                       NCollection_Array1<double>* WCoeffs);

  Standard_EXPORT static void Trimming(const double                  U1,
                                       const double                  U2,
                                       NCollection_Array1<gp_Pnt2d>& Coeffs,
                                       NCollection_Array1<double>*   WCoeffs);

  Standard_EXPORT static void Trimming(const double                U1,
                                       const double                U2,
                                       NCollection_Array1<double>& Coeffs,
                                       NCollection_Array1<double>* WCoeffs);

  Standard_EXPORT static void Trimming(const double                U1,
                                       const double                U2,
                                       const int                   dim,
                                       NCollection_Array1<double>& Coeffs,
                                       NCollection_Array1<double>* WCoeffs);

  Standard_EXPORT static void CoefficientsPoles(const NCollection_Array2<gp_Pnt>& Coefs,
                                                const NCollection_Array2<double>* WCoefs,
                                                NCollection_Array2<gp_Pnt>&       Poles,
                                                NCollection_Array2<double>*       WPoles);

  Standard_EXPORT static void UTrimming(const double                U1,
                                        const double                U2,
                                        NCollection_Array2<gp_Pnt>& Coeffs,
                                        NCollection_Array2<double>* WCoeffs);

  Standard_EXPORT static void VTrimming(const double                V1,
                                        const double                V2,
                                        NCollection_Array2<gp_Pnt>& Coeffs,
                                        NCollection_Array2<double>* WCoeffs);

  Standard_EXPORT static bool HermiteInterpolate(const int                         Dimension,
                                                 const double                      FirstParameter,
                                                 const double                      LastParameter,
                                                 const int                         FirstOrder,
                                                 const int                         LastOrder,
                                                 const NCollection_Array2<double>& FirstConstr,
                                                 const NCollection_Array2<double>& LastConstr,
                                                 NCollection_Array1<double>&       Coefficients);

  Standard_EXPORT static void JacobiParameters(const GeomAbs_Shape ConstraintOrder,
                                               const int           MaxDegree,
                                               const int           Code,
                                               int&                NbGaussPoints,
                                               int&                WorkDegree);

  Standard_EXPORT static int NivConstr(const GeomAbs_Shape ConstraintOrder);

  Standard_EXPORT static GeomAbs_Shape ConstraintOrder(const int NivConstr);

  Standard_EXPORT static void EvalLength(const int    Degree,
                                         const int    Dimension,
                                         double&      PolynomialCoeff,
                                         const double U1,
                                         const double U2,
                                         double&      Length);

  Standard_EXPORT static void EvalLength(const int    Degree,
                                         const int    Dimension,
                                         double&      PolynomialCoeff,
                                         const double U1,
                                         const double U2,
                                         const double Tol,
                                         double&      Length,
                                         double&      Error);
};
