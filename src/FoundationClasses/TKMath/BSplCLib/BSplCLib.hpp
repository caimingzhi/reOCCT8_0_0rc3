#pragma once

#include <Standard_TypeDef.hpp>

class BSplCLib_EvaluatorFunction
{
public:
  BSplCLib_EvaluatorFunction() = default;

  virtual ~BSplCLib_EvaluatorFunction() = default;

  virtual void Evaluate(const int     theDerivativeRequest,
                        const double* theStartEnd,
                        const double  theParameter,
                        double&       theResult,
                        int&          theErrorCode) const = 0;

  void operator()(const int     theDerivativeRequest,
                  const double* theStartEnd,
                  const double  theParameter,
                  double&       theResult,
                  int&          theErrorCode) const
  {
    Evaluate(theDerivativeRequest, theStartEnd, theParameter, theResult, theErrorCode);
  }

  BSplCLib_EvaluatorFunction(const BSplCLib_EvaluatorFunction&)            = delete;
  BSplCLib_EvaluatorFunction& operator=(const BSplCLib_EvaluatorFunction&) = delete;
};

#include <BSplCLib_KnotDistribution.hpp>
#include <BSplCLib_MultDistribution.hpp>
#include <GeomAbs_BSplKnotDistribution.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray1.hpp>

class gp_Pnt;
class gp_Pnt2d;
class gp_Vec;
class gp_Vec2d;
class math_Matrix;

class BSplCLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Hunt(const NCollection_Array1<double>& theArray,
                                   const double                      theX,
                                   int&                              theXPos);

  Standard_EXPORT static int FirstUKnotIndex(const int                      Degree,
                                             const NCollection_Array1<int>& Mults);

  Standard_EXPORT static int LastUKnotIndex(const int Degree, const NCollection_Array1<int>& Mults);

  Standard_EXPORT static int FlatIndex(const int                      Degree,
                                       const int                      Index,
                                       const NCollection_Array1<int>& Mults,
                                       const bool                     Periodic);

  Standard_EXPORT static void LocateParameter(const int                         Degree,
                                              const NCollection_Array1<double>& Knots,
                                              const NCollection_Array1<int>&    Mults,
                                              const double                      U,
                                              const bool                        IsPeriodic,
                                              const int                         FromK1,
                                              const int                         ToK2,
                                              int&                              KnotIndex,
                                              double&                           NewU);

  Standard_EXPORT static void LocateParameter(const int                         Degree,
                                              const NCollection_Array1<double>& Knots,
                                              const double                      U,
                                              const bool                        IsPeriodic,
                                              const int                         FromK1,
                                              const int                         ToK2,
                                              int&                              KnotIndex,
                                              double&                           NewU);

  Standard_EXPORT static void LocateParameter(const int                         Degree,
                                              const NCollection_Array1<double>& Knots,
                                              const NCollection_Array1<int>*    Mults,
                                              const double                      U,
                                              const bool                        Periodic,
                                              int&                              Index,
                                              double&                           NewU);

  Standard_EXPORT static int MaxKnotMult(const NCollection_Array1<int>& Mults,
                                         const int                      K1,
                                         const int                      K2);

  Standard_EXPORT static int MinKnotMult(const NCollection_Array1<int>& Mults,
                                         const int                      K1,
                                         const int                      K2);

  Standard_EXPORT static int NbPoles(const int                      Degree,
                                     const bool                     Periodic,
                                     const NCollection_Array1<int>& Mults);

  Standard_EXPORT static int KnotSequenceLength(const NCollection_Array1<int>& Mults,
                                                const int                      Degree,
                                                const bool                     Periodic);

  Standard_EXPORT static void KnotSequence(const NCollection_Array1<double>& Knots,
                                           const NCollection_Array1<int>&    Mults,
                                           NCollection_Array1<double>&       KnotSeq,
                                           const bool                        Periodic = false);

  Standard_EXPORT static void KnotSequence(const NCollection_Array1<double>& Knots,
                                           const NCollection_Array1<int>&    Mults,
                                           const int                         Degree,
                                           const bool                        Periodic,
                                           NCollection_Array1<double>&       KnotSeq);

  Standard_EXPORT static int KnotsLength(const NCollection_Array1<double>& KnotSeq,
                                         const bool                        Periodic = false);

  Standard_EXPORT static void Knots(const NCollection_Array1<double>& KnotSeq,
                                    NCollection_Array1<double>&       Knots,
                                    NCollection_Array1<int>&          Mults,
                                    const bool                        Periodic = false);

  Standard_EXPORT static BSplCLib_KnotDistribution KnotForm(const NCollection_Array1<double>& Knots,
                                                            const int FromK1,
                                                            const int ToK2);

  Standard_EXPORT static BSplCLib_MultDistribution MultForm(const NCollection_Array1<int>& Mults,
                                                            const int                      FromK1,
                                                            const int                      ToK2);

  Standard_EXPORT static void KnotAnalysis(const int                         Degree,
                                           const bool                        Periodic,
                                           const NCollection_Array1<double>& CKnots,
                                           const NCollection_Array1<int>&    CMults,
                                           GeomAbs_BSplKnotDistribution&     KnotForm,
                                           int&                              MaxKnotMult);

  Standard_EXPORT static void Reparametrize(const double                U1,
                                            const double                U2,
                                            NCollection_Array1<double>& Knots);

  Standard_EXPORT static void Reverse(NCollection_Array1<double>& Knots);

  Standard_EXPORT static void Reverse(NCollection_Array1<int>& Mults);

  Standard_EXPORT static void Reverse(NCollection_Array1<gp_Pnt>& Poles, const int Last);

  Standard_EXPORT static void Reverse(NCollection_Array1<gp_Pnt2d>& Poles, const int Last);

  Standard_EXPORT static void Reverse(NCollection_Array1<double>& Weights, const int Last);

  Standard_EXPORT static bool IsRational(const NCollection_Array1<double>& Weights,
                                         const int                         I1,
                                         const int                         I2,
                                         const double                      Epsilon = 0.0);

  static inline constexpr int MaxDegree();

  Standard_EXPORT static void Eval(const double U,
                                   const int    Degree,
                                   double&      Knots,
                                   const int    Dimension,
                                   double&      Poles);

  Standard_EXPORT static void BoorScheme(const double U,
                                         const int    Degree,
                                         double&      Knots,
                                         const int    Dimension,
                                         double&      Poles,
                                         const int    Depth,
                                         const int    Length);

  Standard_EXPORT static bool AntiBoorScheme(const double U,
                                             const int    Degree,
                                             double&      Knots,
                                             const int    Dimension,
                                             double&      Poles,
                                             const int    Depth,
                                             const int    Length,
                                             const double Tolerance);

  Standard_EXPORT static void Derivative(const int Degree,
                                         double&   Knots,
                                         const int Dimension,
                                         const int Length,
                                         const int Order,
                                         double&   Poles);

  Standard_EXPORT static void Bohm(const double U,
                                   const int    Degree,
                                   const int    N,
                                   double&      Knots,
                                   const int    Dimension,
                                   double&      Poles);

  static NCollection_Array1<double>* NoWeights();

  static NCollection_Array1<int>* NoMults();

  Standard_EXPORT static void BuildKnots(const int                         Degree,
                                         const int                         Index,
                                         const bool                        Periodic,
                                         const NCollection_Array1<double>& Knots,
                                         const NCollection_Array1<int>*    Mults,
                                         double&                           LK);

  Standard_EXPORT static int PoleIndex(const int                      Degree,
                                       const int                      Index,
                                       const bool                     Periodic,
                                       const NCollection_Array1<int>& Mults);

  Standard_EXPORT static void BuildEval(const int                         Degree,
                                        const int                         Index,
                                        const NCollection_Array1<double>& Poles,
                                        const NCollection_Array1<double>* Weights,
                                        double&                           LP);

  Standard_EXPORT static void BuildEval(const int                         Degree,
                                        const int                         Index,
                                        const NCollection_Array1<gp_Pnt>& Poles,
                                        const NCollection_Array1<double>* Weights,
                                        double&                           LP);

  Standard_EXPORT static void BuildEval(const int                           Degree,
                                        const int                           Index,
                                        const NCollection_Array1<gp_Pnt2d>& Poles,
                                        const NCollection_Array1<double>*   Weights,
                                        double&                             LP);

  Standard_EXPORT static void BuildBoor(const int                         Index,
                                        const int                         Length,
                                        const int                         Dimension,
                                        const NCollection_Array1<double>& Poles,
                                        double&                           LP);

  Standard_EXPORT static int BoorIndex(const int Index, const int Length, const int Depth);

  Standard_EXPORT static void GetPole(const int                   Index,
                                      const int                   Length,
                                      const int                   Depth,
                                      const int                   Dimension,
                                      double&                     LocPoles,
                                      int&                        Position,
                                      NCollection_Array1<double>& Pole);

  Standard_EXPORT static bool PrepareInsertKnots(const int                         Degree,
                                                 const bool                        Periodic,
                                                 const NCollection_Array1<double>& Knots,
                                                 const NCollection_Array1<int>&    Mults,
                                                 const NCollection_Array1<double>& AddKnots,
                                                 const NCollection_Array1<int>*    AddMults,
                                                 int&                              NbPoles,
                                                 int&                              NbKnots,
                                                 const double                      Epsilon,
                                                 const bool                        Add = true);

  Standard_EXPORT static void InsertKnots(const int                         Degree,
                                          const bool                        Periodic,
                                          const int                         Dimension,
                                          const NCollection_Array1<double>& Poles,
                                          const NCollection_Array1<double>& Knots,
                                          const NCollection_Array1<int>&    Mults,
                                          const NCollection_Array1<double>& AddKnots,
                                          const NCollection_Array1<int>*    AddMults,
                                          NCollection_Array1<double>&       NewPoles,
                                          NCollection_Array1<double>&       NewKnots,
                                          NCollection_Array1<int>&          NewMults,
                                          const double                      Epsilon,
                                          const bool                        Add = true);

  Standard_EXPORT static void InsertKnots(const int                         Degree,
                                          const bool                        Periodic,
                                          const NCollection_Array1<gp_Pnt>& Poles,
                                          const NCollection_Array1<double>* Weights,
                                          const NCollection_Array1<double>& Knots,
                                          const NCollection_Array1<int>&    Mults,
                                          const NCollection_Array1<double>& AddKnots,
                                          const NCollection_Array1<int>*    AddMults,
                                          NCollection_Array1<gp_Pnt>&       NewPoles,
                                          NCollection_Array1<double>*       NewWeights,
                                          NCollection_Array1<double>&       NewKnots,
                                          NCollection_Array1<int>&          NewMults,
                                          const double                      Epsilon,
                                          const bool                        Add = true);

  Standard_EXPORT static void InsertKnots(const int                           Degree,
                                          const bool                          Periodic,
                                          const NCollection_Array1<gp_Pnt2d>& Poles,
                                          const NCollection_Array1<double>*   Weights,
                                          const NCollection_Array1<double>&   Knots,
                                          const NCollection_Array1<int>&      Mults,
                                          const NCollection_Array1<double>&   AddKnots,
                                          const NCollection_Array1<int>*      AddMults,
                                          NCollection_Array1<gp_Pnt2d>&       NewPoles,
                                          NCollection_Array1<double>*         NewWeights,
                                          NCollection_Array1<double>&         NewKnots,
                                          NCollection_Array1<int>&            NewMults,
                                          const double                        Epsilon,
                                          const bool                          Add = true);

  Standard_EXPORT static void InsertKnot(const int                         UIndex,
                                         const double                      U,
                                         const int                         UMult,
                                         const int                         Degree,
                                         const bool                        Periodic,
                                         const NCollection_Array1<gp_Pnt>& Poles,
                                         const NCollection_Array1<double>* Weights,
                                         const NCollection_Array1<double>& Knots,
                                         const NCollection_Array1<int>&    Mults,
                                         NCollection_Array1<gp_Pnt>&       NewPoles,
                                         NCollection_Array1<double>*       NewWeights);

  Standard_EXPORT static void InsertKnot(const int                           UIndex,
                                         const double                        U,
                                         const int                           UMult,
                                         const int                           Degree,
                                         const bool                          Periodic,
                                         const NCollection_Array1<gp_Pnt2d>& Poles,
                                         const NCollection_Array1<double>*   Weights,
                                         const NCollection_Array1<double>&   Knots,
                                         const NCollection_Array1<int>&      Mults,
                                         NCollection_Array1<gp_Pnt2d>&       NewPoles,
                                         NCollection_Array1<double>*         NewWeights);

  Standard_EXPORT static void RaiseMultiplicity(const int                         KnotIndex,
                                                const int                         Mult,
                                                const int                         Degree,
                                                const bool                        Periodic,
                                                const NCollection_Array1<gp_Pnt>& Poles,
                                                const NCollection_Array1<double>* Weights,
                                                const NCollection_Array1<double>& Knots,
                                                const NCollection_Array1<int>&    Mults,
                                                NCollection_Array1<gp_Pnt>&       NewPoles,
                                                NCollection_Array1<double>*       NewWeights);

  Standard_EXPORT static void RaiseMultiplicity(const int                           KnotIndex,
                                                const int                           Mult,
                                                const int                           Degree,
                                                const bool                          Periodic,
                                                const NCollection_Array1<gp_Pnt2d>& Poles,
                                                const NCollection_Array1<double>*   Weights,
                                                const NCollection_Array1<double>&   Knots,
                                                const NCollection_Array1<int>&      Mults,
                                                NCollection_Array1<gp_Pnt2d>&       NewPoles,
                                                NCollection_Array1<double>*         NewWeights);

  Standard_EXPORT static bool RemoveKnot(const int                         Index,
                                         const int                         Mult,
                                         const int                         Degree,
                                         const bool                        Periodic,
                                         const int                         Dimension,
                                         const NCollection_Array1<double>& Poles,
                                         const NCollection_Array1<double>& Knots,
                                         const NCollection_Array1<int>&    Mults,
                                         NCollection_Array1<double>&       NewPoles,
                                         NCollection_Array1<double>&       NewKnots,
                                         NCollection_Array1<int>&          NewMults,
                                         const double                      Tolerance);

  Standard_EXPORT static bool RemoveKnot(const int                         Index,
                                         const int                         Mult,
                                         const int                         Degree,
                                         const bool                        Periodic,
                                         const NCollection_Array1<gp_Pnt>& Poles,
                                         const NCollection_Array1<double>* Weights,
                                         const NCollection_Array1<double>& Knots,
                                         const NCollection_Array1<int>&    Mults,
                                         NCollection_Array1<gp_Pnt>&       NewPoles,
                                         NCollection_Array1<double>*       NewWeights,
                                         NCollection_Array1<double>&       NewKnots,
                                         NCollection_Array1<int>&          NewMults,
                                         const double                      Tolerance);

  Standard_EXPORT static bool RemoveKnot(const int                           Index,
                                         const int                           Mult,
                                         const int                           Degree,
                                         const bool                          Periodic,
                                         const NCollection_Array1<gp_Pnt2d>& Poles,
                                         const NCollection_Array1<double>*   Weights,
                                         const NCollection_Array1<double>&   Knots,
                                         const NCollection_Array1<int>&      Mults,
                                         NCollection_Array1<gp_Pnt2d>&       NewPoles,
                                         NCollection_Array1<double>*         NewWeights,
                                         NCollection_Array1<double>&         NewKnots,
                                         NCollection_Array1<int>&            NewMults,
                                         const double                        Tolerance);

  Standard_EXPORT static int IncreaseDegreeCountKnots(const int                      Degree,
                                                      const int                      NewDegree,
                                                      const bool                     Periodic,
                                                      const NCollection_Array1<int>& Mults);

  Standard_EXPORT static void IncreaseDegree(const int                         Degree,
                                             const int                         NewDegree,
                                             const bool                        Periodic,
                                             const int                         Dimension,
                                             const NCollection_Array1<double>& Poles,
                                             const NCollection_Array1<double>& Knots,
                                             const NCollection_Array1<int>&    Mults,
                                             NCollection_Array1<double>&       NewPoles,
                                             NCollection_Array1<double>&       NewKnots,
                                             NCollection_Array1<int>&          NewMults);

  Standard_EXPORT static void IncreaseDegree(const int                         Degree,
                                             const int                         NewDegree,
                                             const bool                        Periodic,
                                             const NCollection_Array1<gp_Pnt>& Poles,
                                             const NCollection_Array1<double>* Weights,
                                             const NCollection_Array1<double>& Knots,
                                             const NCollection_Array1<int>&    Mults,
                                             NCollection_Array1<gp_Pnt>&       NewPoles,
                                             NCollection_Array1<double>*       NewWeights,
                                             NCollection_Array1<double>&       NewKnots,
                                             NCollection_Array1<int>&          NewMults);

  Standard_EXPORT static void IncreaseDegree(const int                           Degree,
                                             const int                           NewDegree,
                                             const bool                          Periodic,
                                             const NCollection_Array1<gp_Pnt2d>& Poles,
                                             const NCollection_Array1<double>*   Weights,
                                             const NCollection_Array1<double>&   Knots,
                                             const NCollection_Array1<int>&      Mults,
                                             NCollection_Array1<gp_Pnt2d>&       NewPoles,
                                             NCollection_Array1<double>*         NewWeights,
                                             NCollection_Array1<double>&         NewKnots,
                                             NCollection_Array1<int>&            NewMults);

  Standard_EXPORT static void IncreaseDegree(const int                         NewDegree,
                                             const NCollection_Array1<gp_Pnt>& Poles,
                                             const NCollection_Array1<double>* Weights,
                                             NCollection_Array1<gp_Pnt>&       NewPoles,
                                             NCollection_Array1<double>*       NewWeights);

  Standard_EXPORT static void IncreaseDegree(const int                           theNewDegree,
                                             const NCollection_Array1<gp_Pnt2d>& thePoles,
                                             const NCollection_Array1<double>*   theWeights,
                                             NCollection_Array1<gp_Pnt2d>&       theNewPoles,
                                             NCollection_Array1<double>*         theNewWeights);

  Standard_EXPORT static void PrepareUnperiodize(const int                      Degree,
                                                 const NCollection_Array1<int>& Mults,
                                                 int&                           NbKnots,
                                                 int&                           NbPoles);

  Standard_EXPORT static void Unperiodize(const int                         Degree,
                                          const int                         Dimension,
                                          const NCollection_Array1<int>&    Mults,
                                          const NCollection_Array1<double>& Knots,
                                          const NCollection_Array1<double>& Poles,
                                          NCollection_Array1<int>&          NewMults,
                                          NCollection_Array1<double>&       NewKnots,
                                          NCollection_Array1<double>&       NewPoles);

  Standard_EXPORT static void Unperiodize(const int                         Degree,
                                          const NCollection_Array1<int>&    Mults,
                                          const NCollection_Array1<double>& Knots,
                                          const NCollection_Array1<gp_Pnt>& Poles,
                                          const NCollection_Array1<double>* Weights,
                                          NCollection_Array1<int>&          NewMults,
                                          NCollection_Array1<double>&       NewKnots,
                                          NCollection_Array1<gp_Pnt>&       NewPoles,
                                          NCollection_Array1<double>*       NewWeights);

  Standard_EXPORT static void Unperiodize(const int                           Degree,
                                          const NCollection_Array1<int>&      Mults,
                                          const NCollection_Array1<double>&   Knots,
                                          const NCollection_Array1<gp_Pnt2d>& Poles,
                                          const NCollection_Array1<double>*   Weights,
                                          NCollection_Array1<int>&            NewMults,
                                          NCollection_Array1<double>&         NewKnots,
                                          NCollection_Array1<gp_Pnt2d>&       NewPoles,
                                          NCollection_Array1<double>*         NewWeights);

  Standard_EXPORT static void PrepareTrimming(const int                         Degree,
                                              const bool                        Periodic,
                                              const NCollection_Array1<double>& Knots,
                                              const NCollection_Array1<int>&    Mults,
                                              const double                      U1,
                                              const double                      U2,
                                              int&                              NbKnots,
                                              int&                              NbPoles);

  Standard_EXPORT static void Trimming(const int                         Degree,
                                       const bool                        Periodic,
                                       const int                         Dimension,
                                       const NCollection_Array1<double>& Knots,
                                       const NCollection_Array1<int>&    Mults,
                                       const NCollection_Array1<double>& Poles,
                                       const double                      U1,
                                       const double                      U2,
                                       NCollection_Array1<double>&       NewKnots,
                                       NCollection_Array1<int>&          NewMults,
                                       NCollection_Array1<double>&       NewPoles);

  Standard_EXPORT static void Trimming(const int                         Degree,
                                       const bool                        Periodic,
                                       const NCollection_Array1<double>& Knots,
                                       const NCollection_Array1<int>&    Mults,
                                       const NCollection_Array1<gp_Pnt>& Poles,
                                       const NCollection_Array1<double>* Weights,
                                       const double                      U1,
                                       const double                      U2,
                                       NCollection_Array1<double>&       NewKnots,
                                       NCollection_Array1<int>&          NewMults,
                                       NCollection_Array1<gp_Pnt>&       NewPoles,
                                       NCollection_Array1<double>*       NewWeights);

  Standard_EXPORT static void Trimming(const int                           Degree,
                                       const bool                          Periodic,
                                       const NCollection_Array1<double>&   Knots,
                                       const NCollection_Array1<int>&      Mults,
                                       const NCollection_Array1<gp_Pnt2d>& Poles,
                                       const NCollection_Array1<double>*   Weights,
                                       const double                        U1,
                                       const double                        U2,
                                       NCollection_Array1<double>&         NewKnots,
                                       NCollection_Array1<int>&            NewMults,
                                       NCollection_Array1<gp_Pnt2d>&       NewPoles,
                                       NCollection_Array1<double>*         NewWeights);

  Standard_EXPORT static void D0(const double                      U,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<double>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 double&                           P);

  Standard_EXPORT static void D0(const double                      U,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 gp_Pnt&                           P);

  Standard_EXPORT static void D0(const double                        U,
                                 const int                           UIndex,
                                 const int                           Degree,
                                 const bool                          Periodic,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>*   Weights,
                                 const NCollection_Array1<double>&   Knots,
                                 const NCollection_Array1<int>*      Mults,
                                 gp_Pnt2d&                           P);

  Standard_EXPORT static void D0(const double                      U,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 gp_Pnt&                           P);

  Standard_EXPORT static void D0(const double                        U,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>*   Weights,
                                 gp_Pnt2d&                           P);

  Standard_EXPORT static void D1(const double                      U,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<double>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 double&                           P,
                                 double&                           V);

  Standard_EXPORT static void D1(const double                      U,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           V);

  Standard_EXPORT static void D1(const double                        U,
                                 const int                           UIndex,
                                 const int                           Degree,
                                 const bool                          Periodic,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>*   Weights,
                                 const NCollection_Array1<double>&   Knots,
                                 const NCollection_Array1<int>*      Mults,
                                 gp_Pnt2d&                           P,
                                 gp_Vec2d&                           V);

  Standard_EXPORT static void D1(const double                      U,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           V);

  Standard_EXPORT static void D1(const double                        U,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>*   Weights,
                                 gp_Pnt2d&                           P,
                                 gp_Vec2d&                           V);

  Standard_EXPORT static void D2(const double                      U,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<double>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 double&                           P,
                                 double&                           V1,
                                 double&                           V2);

  Standard_EXPORT static void D2(const double                      U,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           V1,
                                 gp_Vec&                           V2);

  Standard_EXPORT static void D2(const double                        U,
                                 const int                           UIndex,
                                 const int                           Degree,
                                 const bool                          Periodic,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>*   Weights,
                                 const NCollection_Array1<double>&   Knots,
                                 const NCollection_Array1<int>*      Mults,
                                 gp_Pnt2d&                           P,
                                 gp_Vec2d&                           V1,
                                 gp_Vec2d&                           V2);

  Standard_EXPORT static void D2(const double                      U,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           V1,
                                 gp_Vec&                           V2);

  Standard_EXPORT static void D2(const double                        U,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>*   Weights,
                                 gp_Pnt2d&                           P,
                                 gp_Vec2d&                           V1,
                                 gp_Vec2d&                           V2);

  Standard_EXPORT static void D3(const double                      U,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<double>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 double&                           P,
                                 double&                           V1,
                                 double&                           V2,
                                 double&                           V3);

  Standard_EXPORT static void D3(const double                      U,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           V1,
                                 gp_Vec&                           V2,
                                 gp_Vec&                           V3);

  Standard_EXPORT static void D3(const double                        U,
                                 const int                           UIndex,
                                 const int                           Degree,
                                 const bool                          Periodic,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>*   Weights,
                                 const NCollection_Array1<double>&   Knots,
                                 const NCollection_Array1<int>*      Mults,
                                 gp_Pnt2d&                           P,
                                 gp_Vec2d&                           V1,
                                 gp_Vec2d&                           V2,
                                 gp_Vec2d&                           V3);

  Standard_EXPORT static void D3(const double                      U,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           V1,
                                 gp_Vec&                           V2,
                                 gp_Vec&                           V3);

  Standard_EXPORT static void D3(const double                        U,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>*   Weights,
                                 gp_Pnt2d&                           P,
                                 gp_Vec2d&                           V1,
                                 gp_Vec2d&                           V2,
                                 gp_Vec2d&                           V3);

  Standard_EXPORT static void DN(const double                      U,
                                 const int                         N,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<double>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 double&                           VN);

  Standard_EXPORT static void DN(const double                      U,
                                 const int                         N,
                                 const int                         Index,
                                 const int                         Degree,
                                 const bool                        Periodic,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>* Weights,
                                 const NCollection_Array1<double>& Knots,
                                 const NCollection_Array1<int>*    Mults,
                                 gp_Vec&                           VN);

  Standard_EXPORT static void DN(const double                        U,
                                 const int                           N,
                                 const int                           UIndex,
                                 const int                           Degree,
                                 const bool                          Periodic,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>*   Weights,
                                 const NCollection_Array1<double>&   Knots,
                                 const NCollection_Array1<int>*      Mults,
                                 gp_Vec2d&                           V);

  Standard_EXPORT static void DN(const double                      U,
                                 const int                         N,
                                 const NCollection_Array1<gp_Pnt>& Poles,
                                 const NCollection_Array1<double>& Weights,
                                 gp_Pnt&                           P,
                                 gp_Vec&                           VN);

  Standard_EXPORT static void DN(const double                        U,
                                 const int                           N,
                                 const NCollection_Array1<gp_Pnt2d>& Poles,
                                 const NCollection_Array1<double>&   Weights,
                                 gp_Pnt2d&                           P,
                                 gp_Vec2d&                           VN);

  Standard_EXPORT static int EvalBsplineBasis(const int                         DerivativeOrder,
                                              const int                         Order,
                                              const NCollection_Array1<double>& FlatKnots,
                                              const double                      Parameter,
                                              int&         FirstNonZeroBsplineIndex,
                                              math_Matrix& BsplineBasis,
                                              const bool   isPeriodic = false);

  Standard_EXPORT static int BuildBSpMatrix(const NCollection_Array1<double>& Parameters,
                                            const NCollection_Array1<int>&    OrderArray,
                                            const NCollection_Array1<double>& FlatKnots,
                                            const int                         Degree,
                                            math_Matrix&                      Matrix,
                                            int&                              UpperBandWidth,
                                            int&                              LowerBandWidth);

  Standard_EXPORT static int FactorBandedMatrix(math_Matrix& Matrix,
                                                const int    UpperBandWidth,
                                                const int    LowerBandWidth,
                                                int&         PivotIndexProblem);

  Standard_EXPORT static int SolveBandedSystem(const math_Matrix& Matrix,
                                               const int          UpperBandWidth,
                                               const int          LowerBandWidth,
                                               const int          ArrayDimension,
                                               double&            Array);

  Standard_EXPORT static int SolveBandedSystem(const math_Matrix&            Matrix,
                                               const int                     UpperBandWidth,
                                               const int                     LowerBandWidth,
                                               NCollection_Array1<gp_Pnt2d>& Array);

  Standard_EXPORT static int SolveBandedSystem(const math_Matrix&          Matrix,
                                               const int                   UpperBandWidth,
                                               const int                   LowerBandWidth,
                                               NCollection_Array1<gp_Pnt>& Array);

  Standard_EXPORT static int SolveBandedSystem(const math_Matrix& Matrix,
                                               const int          UpperBandWidth,
                                               const int          LowerBandWidth,
                                               const bool         HomogenousFlag,
                                               const int          ArrayDimension,
                                               double&            Array,
                                               double&            Weights);

  Standard_EXPORT static int SolveBandedSystem(const math_Matrix&            Matrix,
                                               const int                     UpperBandWidth,
                                               const int                     LowerBandWidth,
                                               const bool                    HomogenousFlag,
                                               NCollection_Array1<gp_Pnt2d>& Array,
                                               NCollection_Array1<double>&   Weights);

  Standard_EXPORT static int SolveBandedSystem(const math_Matrix&          Matrix,
                                               const int                   UpperBandWidth,
                                               const int                   LowerBandWidth,
                                               const bool                  HomogeneousFlag,
                                               NCollection_Array1<gp_Pnt>& Array,
                                               NCollection_Array1<double>& Weights);

  Standard_EXPORT static void MergeBSplineKnots(const double                      Tolerance,
                                                const double                      StartValue,
                                                const double                      EndValue,
                                                const int                         Degree1,
                                                const NCollection_Array1<double>& Knots1,
                                                const NCollection_Array1<int>&    Mults1,
                                                const int                         Degree2,
                                                const NCollection_Array1<double>& Knots2,
                                                const NCollection_Array1<int>&    Mults2,
                                                int&                              NumPoles,
                                                occ::handle<NCollection_HArray1<double>>& NewKnots,
                                                occ::handle<NCollection_HArray1<int>>&    NewMults);

  Standard_EXPORT static void FunctionReparameterise(
    const BSplCLib_EvaluatorFunction& Function,
    const int                         BSplineDegree,
    const NCollection_Array1<double>& BSplineFlatKnots,
    const int                         PolesDimension,
    double&                           Poles,
    const NCollection_Array1<double>& FlatKnots,
    const int                         NewDegree,
    double&                           NewPoles,
    int&                              theStatus);

  Standard_EXPORT static void FunctionReparameterise(
    const BSplCLib_EvaluatorFunction& Function,
    const int                         BSplineDegree,
    const NCollection_Array1<double>& BSplineFlatKnots,
    const NCollection_Array1<double>& Poles,
    const NCollection_Array1<double>& FlatKnots,
    const int                         NewDegree,
    NCollection_Array1<double>&       NewPoles,
    int&                              theStatus);

  Standard_EXPORT static void FunctionReparameterise(
    const BSplCLib_EvaluatorFunction& Function,
    const int                         BSplineDegree,
    const NCollection_Array1<double>& BSplineFlatKnots,
    const NCollection_Array1<gp_Pnt>& Poles,
    const NCollection_Array1<double>& FlatKnots,
    const int                         NewDegree,
    NCollection_Array1<gp_Pnt>&       NewPoles,
    int&                              theStatus);

  Standard_EXPORT static void FunctionReparameterise(
    const BSplCLib_EvaluatorFunction&   Function,
    const int                           BSplineDegree,
    const NCollection_Array1<double>&   BSplineFlatKnots,
    const NCollection_Array1<gp_Pnt2d>& Poles,
    const NCollection_Array1<double>&   FlatKnots,
    const int                           NewDegree,
    NCollection_Array1<gp_Pnt2d>&       NewPoles,
    int&                                theStatus);

  Standard_EXPORT static void FunctionMultiply(const BSplCLib_EvaluatorFunction& Function,
                                               const int                         BSplineDegree,
                                               const NCollection_Array1<double>& BSplineFlatKnots,
                                               const int                         PolesDimension,
                                               double&                           Poles,
                                               const NCollection_Array1<double>& FlatKnots,
                                               const int                         NewDegree,
                                               double&                           NewPoles,
                                               int&                              theStatus);

  Standard_EXPORT static void FunctionMultiply(const BSplCLib_EvaluatorFunction& Function,
                                               const int                         BSplineDegree,
                                               const NCollection_Array1<double>& BSplineFlatKnots,
                                               const NCollection_Array1<double>& Poles,
                                               const NCollection_Array1<double>& FlatKnots,
                                               const int                         NewDegree,
                                               NCollection_Array1<double>&       NewPoles,
                                               int&                              theStatus);

  Standard_EXPORT static void FunctionMultiply(const BSplCLib_EvaluatorFunction&   Function,
                                               const int                           BSplineDegree,
                                               const NCollection_Array1<double>&   BSplineFlatKnots,
                                               const NCollection_Array1<gp_Pnt2d>& Poles,
                                               const NCollection_Array1<double>&   FlatKnots,
                                               const int                           NewDegree,
                                               NCollection_Array1<gp_Pnt2d>&       NewPoles,
                                               int&                                theStatus);

  Standard_EXPORT static void FunctionMultiply(const BSplCLib_EvaluatorFunction& Function,
                                               const int                         BSplineDegree,
                                               const NCollection_Array1<double>& BSplineFlatKnots,
                                               const NCollection_Array1<gp_Pnt>& Poles,
                                               const NCollection_Array1<double>& FlatKnots,
                                               const int                         NewDegree,
                                               NCollection_Array1<gp_Pnt>&       NewPoles,
                                               int&                              theStatus);

  Standard_EXPORT static void Eval(const double                      U,
                                   const bool                        PeriodicFlag,
                                   const int                         DerivativeRequest,
                                   int&                              ExtrapMode,
                                   const int                         Degree,
                                   const NCollection_Array1<double>& FlatKnots,
                                   const int                         ArrayDimension,
                                   double&                           Poles,
                                   double&                           Result);

  Standard_EXPORT static void Eval(const double                      U,
                                   const bool                        PeriodicFlag,
                                   const int                         DerivativeRequest,
                                   int&                              ExtrapMode,
                                   const int                         Degree,
                                   const NCollection_Array1<double>& FlatKnots,
                                   const int                         ArrayDimension,
                                   double&                           Poles,
                                   double&                           Weights,
                                   double&                           PolesResult,
                                   double&                           WeightsResult);

  Standard_EXPORT static void Eval(const double                      U,
                                   const bool                        PeriodicFlag,
                                   const bool                        HomogeneousFlag,
                                   int&                              ExtrapMode,
                                   const int                         Degree,
                                   const NCollection_Array1<double>& FlatKnots,
                                   const NCollection_Array1<gp_Pnt>& Poles,
                                   const NCollection_Array1<double>& Weights,
                                   gp_Pnt&                           Point,
                                   double&                           Weight);

  Standard_EXPORT static void Eval(const double                        U,
                                   const bool                          PeriodicFlag,
                                   const bool                          HomogeneousFlag,
                                   int&                                ExtrapMode,
                                   const int                           Degree,
                                   const NCollection_Array1<double>&   FlatKnots,
                                   const NCollection_Array1<gp_Pnt2d>& Poles,
                                   const NCollection_Array1<double>&   Weights,
                                   gp_Pnt2d&                           Point,
                                   double&                             Weight);

  Standard_EXPORT static void TangExtendToConstraint(
    const NCollection_Array1<double>& FlatKnots,
    const double                      C1Coefficient,
    const int                         NumPoles,
    double&                           Poles,
    const int                         Dimension,
    const int                         Degree,
    const NCollection_Array1<double>& ConstraintPoint,
    const int                         Continuity,
    const bool                        After,
    int&                              NbPolesResult,
    int&                              NbKnotsRsult,
    double&                           KnotsResult,
    double&                           PolesResult);

  Standard_EXPORT static void CacheD0(const double                      U,
                                      const int                         Degree,
                                      const double                      CacheParameter,
                                      const double                      SpanLenght,
                                      const NCollection_Array1<gp_Pnt>& Poles,
                                      const NCollection_Array1<double>* Weights,
                                      gp_Pnt&                           Point);

  Standard_EXPORT static void CacheD0(const double                        U,
                                      const int                           Degree,
                                      const double                        CacheParameter,
                                      const double                        SpanLenght,
                                      const NCollection_Array1<gp_Pnt2d>& Poles,
                                      const NCollection_Array1<double>*   Weights,
                                      gp_Pnt2d&                           Point);

  static void CoefsD0(const double                      U,
                      const NCollection_Array1<gp_Pnt>& Poles,
                      const NCollection_Array1<double>* Weights,
                      gp_Pnt&                           Point);

  static void CoefsD0(const double                        U,
                      const NCollection_Array1<gp_Pnt2d>& Poles,
                      const NCollection_Array1<double>*   Weights,
                      gp_Pnt2d&                           Point);

  Standard_EXPORT static void CacheD1(const double                      U,
                                      const int                         Degree,
                                      const double                      CacheParameter,
                                      const double                      SpanLenght,
                                      const NCollection_Array1<gp_Pnt>& Poles,
                                      const NCollection_Array1<double>* Weights,
                                      gp_Pnt&                           Point,
                                      gp_Vec&                           Vec);

  Standard_EXPORT static void CacheD1(const double                        U,
                                      const int                           Degree,
                                      const double                        CacheParameter,
                                      const double                        SpanLenght,
                                      const NCollection_Array1<gp_Pnt2d>& Poles,
                                      const NCollection_Array1<double>*   Weights,
                                      gp_Pnt2d&                           Point,
                                      gp_Vec2d&                           Vec);

  static void CoefsD1(const double                      U,
                      const NCollection_Array1<gp_Pnt>& Poles,
                      const NCollection_Array1<double>* Weights,
                      gp_Pnt&                           Point,
                      gp_Vec&                           Vec);

  static void CoefsD1(const double                        U,
                      const NCollection_Array1<gp_Pnt2d>& Poles,
                      const NCollection_Array1<double>*   Weights,
                      gp_Pnt2d&                           Point,
                      gp_Vec2d&                           Vec);

  Standard_EXPORT static void CacheD2(const double                      U,
                                      const int                         Degree,
                                      const double                      CacheParameter,
                                      const double                      SpanLenght,
                                      const NCollection_Array1<gp_Pnt>& Poles,
                                      const NCollection_Array1<double>* Weights,
                                      gp_Pnt&                           Point,
                                      gp_Vec&                           Vec1,
                                      gp_Vec&                           Vec2);

  Standard_EXPORT static void CacheD2(const double                        U,
                                      const int                           Degree,
                                      const double                        CacheParameter,
                                      const double                        SpanLenght,
                                      const NCollection_Array1<gp_Pnt2d>& Poles,
                                      const NCollection_Array1<double>*   Weights,
                                      gp_Pnt2d&                           Point,
                                      gp_Vec2d&                           Vec1,
                                      gp_Vec2d&                           Vec2);

  static void CoefsD2(const double                      U,
                      const NCollection_Array1<gp_Pnt>& Poles,
                      const NCollection_Array1<double>* Weights,
                      gp_Pnt&                           Point,
                      gp_Vec&                           Vec1,
                      gp_Vec&                           Vec2);

  static void CoefsD2(const double                        U,
                      const NCollection_Array1<gp_Pnt2d>& Poles,
                      const NCollection_Array1<double>*   Weights,
                      gp_Pnt2d&                           Point,
                      gp_Vec2d&                           Vec1,
                      gp_Vec2d&                           Vec2);

  Standard_EXPORT static void CacheD3(const double                      U,
                                      const int                         Degree,
                                      const double                      CacheParameter,
                                      const double                      SpanLenght,
                                      const NCollection_Array1<gp_Pnt>& Poles,
                                      const NCollection_Array1<double>* Weights,
                                      gp_Pnt&                           Point,
                                      gp_Vec&                           Vec1,
                                      gp_Vec&                           Vec2,
                                      gp_Vec&                           Vec3);

  Standard_EXPORT static void CacheD3(const double                        U,
                                      const int                           Degree,
                                      const double                        CacheParameter,
                                      const double                        SpanLenght,
                                      const NCollection_Array1<gp_Pnt2d>& Poles,
                                      const NCollection_Array1<double>*   Weights,
                                      gp_Pnt2d&                           Point,
                                      gp_Vec2d&                           Vec1,
                                      gp_Vec2d&                           Vec2,
                                      gp_Vec2d&                           Vec3);

  static void CoefsD3(const double                      U,
                      const NCollection_Array1<gp_Pnt>& Poles,
                      const NCollection_Array1<double>* Weights,
                      gp_Pnt&                           Point,
                      gp_Vec&                           Vec1,
                      gp_Vec&                           Vec2,
                      gp_Vec&                           Vec3);

  static void CoefsD3(const double                        U,
                      const NCollection_Array1<gp_Pnt2d>& Poles,
                      const NCollection_Array1<double>*   Weights,
                      gp_Pnt2d&                           Point,
                      gp_Vec2d&                           Vec1,
                      gp_Vec2d&                           Vec2,
                      gp_Vec2d&                           Vec3);

  Standard_EXPORT static void BuildCache(const double                      U,
                                         const double                      InverseOfSpanDomain,
                                         const bool                        PeriodicFlag,
                                         const int                         Degree,
                                         const NCollection_Array1<double>& FlatKnots,
                                         const NCollection_Array1<gp_Pnt>& Poles,
                                         const NCollection_Array1<double>* Weights,
                                         NCollection_Array1<gp_Pnt>&       CachePoles,
                                         NCollection_Array1<double>*       CacheWeights);

  Standard_EXPORT static void BuildCache(const double                        U,
                                         const double                        InverseOfSpanDomain,
                                         const bool                          PeriodicFlag,
                                         const int                           Degree,
                                         const NCollection_Array1<double>&   FlatKnots,
                                         const NCollection_Array1<gp_Pnt2d>& Poles,
                                         const NCollection_Array1<double>*   Weights,
                                         NCollection_Array1<gp_Pnt2d>&       CachePoles,
                                         NCollection_Array1<double>*         CacheWeights);

  Standard_EXPORT static void BuildCache(const double                      theParameter,
                                         const double                      theSpanDomain,
                                         const bool                        thePeriodicFlag,
                                         const int                         theDegree,
                                         const int                         theSpanIndex,
                                         const NCollection_Array1<double>& theFlatKnots,
                                         const NCollection_Array1<gp_Pnt>& thePoles,
                                         const NCollection_Array1<double>* theWeights,
                                         NCollection_Array2<double>&       theCacheArray);

  Standard_EXPORT static void BuildCache(const double                        theParameter,
                                         const double                        theSpanDomain,
                                         const bool                          thePeriodicFlag,
                                         const int                           theDegree,
                                         const int                           theSpanIndex,
                                         const NCollection_Array1<double>&   theFlatKnots,
                                         const NCollection_Array1<gp_Pnt2d>& thePoles,
                                         const NCollection_Array1<double>*   theWeights,
                                         NCollection_Array2<double>&         theCacheArray);

  static void PolesCoefficients(const NCollection_Array1<gp_Pnt2d>& Poles,
                                NCollection_Array1<gp_Pnt2d>&       CachePoles);

  Standard_EXPORT static void PolesCoefficients(const NCollection_Array1<gp_Pnt2d>& Poles,
                                                const NCollection_Array1<double>*   Weights,
                                                NCollection_Array1<gp_Pnt2d>&       CachePoles,
                                                NCollection_Array1<double>*         CacheWeights);

  static void PolesCoefficients(const NCollection_Array1<gp_Pnt>& Poles,
                                NCollection_Array1<gp_Pnt>&       CachePoles);

  Standard_EXPORT static void PolesCoefficients(const NCollection_Array1<gp_Pnt>& Poles,
                                                const NCollection_Array1<double>* Weights,
                                                NCollection_Array1<gp_Pnt>&       CachePoles,
                                                NCollection_Array1<double>*       CacheWeights);

  Standard_EXPORT static const double& FlatBezierKnots(const int Degree);

  Standard_EXPORT static void BuildSchoenbergPoints(const int                         Degree,
                                                    const NCollection_Array1<double>& FlatKnots,
                                                    NCollection_Array1<double>&       Parameters);

  Standard_EXPORT static void Interpolate(const int                         Degree,
                                          const NCollection_Array1<double>& FlatKnots,
                                          const NCollection_Array1<double>& Parameters,
                                          const NCollection_Array1<int>&    ContactOrderArray,
                                          NCollection_Array1<gp_Pnt>&       Poles,
                                          int&                              InversionProblem);

  Standard_EXPORT static void Interpolate(const int                         Degree,
                                          const NCollection_Array1<double>& FlatKnots,
                                          const NCollection_Array1<double>& Parameters,
                                          const NCollection_Array1<int>&    ContactOrderArray,
                                          NCollection_Array1<gp_Pnt2d>&     Poles,
                                          int&                              InversionProblem);

  Standard_EXPORT static void Interpolate(const int                         Degree,
                                          const NCollection_Array1<double>& FlatKnots,
                                          const NCollection_Array1<double>& Parameters,
                                          const NCollection_Array1<int>&    ContactOrderArray,
                                          NCollection_Array1<gp_Pnt>&       Poles,
                                          NCollection_Array1<double>&       Weights,
                                          int&                              InversionProblem);

  Standard_EXPORT static void Interpolate(const int                         Degree,
                                          const NCollection_Array1<double>& FlatKnots,
                                          const NCollection_Array1<double>& Parameters,
                                          const NCollection_Array1<int>&    ContactOrderArray,
                                          NCollection_Array1<gp_Pnt2d>&     Poles,
                                          NCollection_Array1<double>&       Weights,
                                          int&                              InversionProblem);

  Standard_EXPORT static void Interpolate(const int                         Degree,
                                          const NCollection_Array1<double>& FlatKnots,
                                          const NCollection_Array1<double>& Parameters,
                                          const NCollection_Array1<int>&    ContactOrderArray,
                                          const int                         ArrayDimension,
                                          double&                           Poles,
                                          int&                              InversionProblem);

  Standard_EXPORT static void Interpolate(const int                         Degree,
                                          const NCollection_Array1<double>& FlatKnots,
                                          const NCollection_Array1<double>& Parameters,
                                          const NCollection_Array1<int>&    ContactOrderArray,
                                          const int                         ArrayDimension,
                                          double&                           Poles,
                                          double&                           Weights,
                                          int&                              InversionProblem);

  Standard_EXPORT static void MovePoint(const double                        U,
                                        const gp_Vec2d&                     Displ,
                                        const int                           Index1,
                                        const int                           Index2,
                                        const int                           Degree,
                                        const NCollection_Array1<gp_Pnt2d>& Poles,
                                        const NCollection_Array1<double>*   Weights,
                                        const NCollection_Array1<double>&   FlatKnots,
                                        int&                                FirstIndex,
                                        int&                                LastIndex,
                                        NCollection_Array1<gp_Pnt2d>&       NewPoles);

  Standard_EXPORT static void MovePoint(const double                      U,
                                        const gp_Vec&                     Displ,
                                        const int                         Index1,
                                        const int                         Index2,
                                        const int                         Degree,
                                        const NCollection_Array1<gp_Pnt>& Poles,
                                        const NCollection_Array1<double>* Weights,
                                        const NCollection_Array1<double>& FlatKnots,
                                        int&                              FirstIndex,
                                        int&                              LastIndex,
                                        NCollection_Array1<gp_Pnt>&       NewPoles);

  Standard_EXPORT static void MovePointAndTangent(const double U,
                                                  const int    ArrayDimension,
                                                  double&      Delta,
                                                  double&      DeltaDerivative,
                                                  const double Tolerance,
                                                  const int    Degree,
                                                  const int    StartingCondition,
                                                  const int    EndingCondition,
                                                  double&      Poles,
                                                  const NCollection_Array1<double>* Weights,
                                                  const NCollection_Array1<double>& FlatKnots,
                                                  double&                           NewPoles,
                                                  int&                              ErrorStatus);

  Standard_EXPORT static void MovePointAndTangent(const double  U,
                                                  const gp_Vec& Delta,
                                                  const gp_Vec& DeltaDerivative,
                                                  const double  Tolerance,
                                                  const int     Degree,
                                                  const int     StartingCondition,
                                                  const int     EndingCondition,
                                                  const NCollection_Array1<gp_Pnt>& Poles,
                                                  const NCollection_Array1<double>* Weights,
                                                  const NCollection_Array1<double>& FlatKnots,
                                                  NCollection_Array1<gp_Pnt>&       NewPoles,
                                                  int&                              ErrorStatus);

  Standard_EXPORT static void MovePointAndTangent(const double    U,
                                                  const gp_Vec2d& Delta,
                                                  const gp_Vec2d& DeltaDerivative,
                                                  const double    Tolerance,
                                                  const int       Degree,
                                                  const int       StartingCondition,
                                                  const int       EndingCondition,
                                                  const NCollection_Array1<gp_Pnt2d>& Poles,
                                                  const NCollection_Array1<double>*   Weights,
                                                  const NCollection_Array1<double>&   FlatKnots,
                                                  NCollection_Array1<gp_Pnt2d>&       NewPoles,
                                                  int&                                ErrorStatus);

  Standard_EXPORT static void Resolution(double&                           PolesArray,
                                         const int                         ArrayDimension,
                                         const int                         NumPoles,
                                         const NCollection_Array1<double>* Weights,
                                         const NCollection_Array1<double>& FlatKnots,
                                         const int                         Degree,
                                         const double                      Tolerance3D,
                                         double&                           UTolerance);

  Standard_EXPORT static void Resolution(const NCollection_Array1<gp_Pnt>& Poles,
                                         const NCollection_Array1<double>* Weights,
                                         const int                         NumPoles,
                                         const NCollection_Array1<double>& FlatKnots,
                                         const int                         Degree,
                                         const double                      Tolerance3D,
                                         double&                           UTolerance);

  Standard_EXPORT static void Resolution(const NCollection_Array1<gp_Pnt2d>& Poles,
                                         const NCollection_Array1<double>*   Weights,
                                         const int                           NumPoles,
                                         const NCollection_Array1<double>&   FlatKnots,
                                         const int                           Degree,
                                         const double                        Tolerance3D,
                                         double&                             UTolerance);

  Standard_EXPORT static int Intervals(const NCollection_Array1<double>& theKnots,
                                       const NCollection_Array1<int>&    theMults,
                                       int                               theDegree,
                                       bool                              isPeriodic,
                                       int                               theContinuity,
                                       double                            theFirst,
                                       double                            theLast,
                                       double                            theTolerance,
                                       NCollection_Array1<double>*       theIntervals);

private:
  Standard_EXPORT static void LocateParameter(const NCollection_Array1<double>& Knots,
                                              const double                      U,
                                              const bool                        Periodic,
                                              const int                         K1,
                                              const int                         K2,
                                              int&                              Index,
                                              double&                           NewU,
                                              const double                      Uf,
                                              const double                      Ue);
};

#include <PLib.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>

inline constexpr int BSplCLib::MaxDegree()
{
  return 25;
}

inline NCollection_Array1<double>* BSplCLib::NoWeights()
{
  return nullptr;
}

inline NCollection_Array1<int>* BSplCLib::NoMults()
{
  return nullptr;
}

inline void BSplCLib::CoefsD0(const double                      U,
                              const NCollection_Array1<gp_Pnt>& Poles,
                              const NCollection_Array1<double>* Weights,
                              gp_Pnt&                           P)
{
  BSplCLib::CacheD0(U, Poles.Length() - 1, 0., 1., Poles, Weights, P);
}

inline void BSplCLib::CoefsD0(const double                        U,
                              const NCollection_Array1<gp_Pnt2d>& Poles,
                              const NCollection_Array1<double>*   Weights,
                              gp_Pnt2d&                           P)
{
  BSplCLib::CacheD0(U, Poles.Length() - 1, 0., 1., Poles, Weights, P);
}

inline void BSplCLib::CoefsD1(const double                      U,
                              const NCollection_Array1<gp_Pnt>& Poles,
                              const NCollection_Array1<double>* Weights,
                              gp_Pnt&                           P,
                              gp_Vec&                           Vec)
{
  BSplCLib::CacheD1(U, Poles.Length() - 1, 0., 1., Poles, Weights, P, Vec);
}

inline void BSplCLib::CoefsD1(const double                        U,
                              const NCollection_Array1<gp_Pnt2d>& Poles,
                              const NCollection_Array1<double>*   Weights,
                              gp_Pnt2d&                           P,
                              gp_Vec2d&                           Vec)
{
  BSplCLib::CacheD1(U, Poles.Length() - 1, 0., 1., Poles, Weights, P, Vec);
}

inline void BSplCLib::CoefsD2(const double                      U,
                              const NCollection_Array1<gp_Pnt>& Poles,
                              const NCollection_Array1<double>* Weights,
                              gp_Pnt&                           P,
                              gp_Vec&                           Vec1,
                              gp_Vec&                           Vec2)
{
  BSplCLib::CacheD2(U, Poles.Length() - 1, 0., 1., Poles, Weights, P, Vec1, Vec2);
}

inline void BSplCLib::CoefsD2(const double                        U,
                              const NCollection_Array1<gp_Pnt2d>& Poles,
                              const NCollection_Array1<double>*   Weights,
                              gp_Pnt2d&                           P,
                              gp_Vec2d&                           Vec1,
                              gp_Vec2d&                           Vec2)
{
  BSplCLib::CacheD2(U, Poles.Length() - 1, 0., 1., Poles, Weights, P, Vec1, Vec2);
}

inline void BSplCLib::CoefsD3(const double                      U,
                              const NCollection_Array1<gp_Pnt>& Poles,
                              const NCollection_Array1<double>* Weights,
                              gp_Pnt&                           P,
                              gp_Vec&                           Vec1,
                              gp_Vec&                           Vec2,
                              gp_Vec&                           Vec3)
{
  BSplCLib::CacheD3(U, Poles.Length() - 1, 0., 1., Poles, Weights, P, Vec1, Vec2, Vec3);
}

inline void BSplCLib::CoefsD3(const double                        U,
                              const NCollection_Array1<gp_Pnt2d>& Poles,
                              const NCollection_Array1<double>*   Weights,
                              gp_Pnt2d&                           P,
                              gp_Vec2d&                           Vec1,
                              gp_Vec2d&                           Vec2,
                              gp_Vec2d&                           Vec3)
{
  BSplCLib::CacheD3(U, Poles.Length() - 1, 0., 1., Poles, Weights, P, Vec1, Vec2, Vec3);
}

inline void BSplCLib::PolesCoefficients(const NCollection_Array1<gp_Pnt>& Poles,
                                        NCollection_Array1<gp_Pnt>&       CachePoles)
{
  BSplCLib::PolesCoefficients(Poles, PLib::NoWeights(), CachePoles, PLib::NoWeights());
}

inline void BSplCLib::PolesCoefficients(const NCollection_Array1<gp_Pnt2d>& Poles,
                                        NCollection_Array1<gp_Pnt2d>&       CachePoles)
{
  BSplCLib::PolesCoefficients(Poles, PLib::NoWeights(), CachePoles, PLib::NoWeights());
}
