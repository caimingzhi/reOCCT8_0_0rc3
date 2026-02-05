#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Boolean.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Pnt.hpp>
#include <AdvApprox_EvaluatorFunction.hpp>
#include <Standard_OStream.hpp>
class AdvApprox_Cutting;

//! this approximate a given function
class AdvApprox_ApproxAFunction
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs approximator tool.
  //!
  //! Warning:
  //! the Func should be valid reference to object of type
  //! inherited from class EvaluatorFunction from Approx
  //! with life time longer than that of the approximator tool;
  //!
  //! the result should be formatted in the following way :
  //! <--Num1DSS--> <--2 * Num2DSS--> <--3 * Num3DSS-->
  //! R[0] ....     R[Num1DSS].....                   R[Dimension-1]
  //!
  //! the order in which each Subspace appears should be consistent
  //! with the tolerances given in the create function and the
  //! results will be given in that order as well that is :
  //! Curve2d(n) will correspond to the nth entry
  //! described by Num2DSS, Curve(n) will correspond to
  //! the nth entry described by Num3DSS
  //! The same type of schema applies to the Poles1d, Poles2d and
  //! Poles.
  Standard_EXPORT AdvApprox_ApproxAFunction(
    const int                                       Num1DSS,
    const int                                       Num2DSS,
    const int                                       Num3DSS,
    const occ::handle<NCollection_HArray1<double>>& OneDTol,
    const occ::handle<NCollection_HArray1<double>>& TwoDTol,
    const occ::handle<NCollection_HArray1<double>>& ThreeDTol,
    const double                                    First,
    const double                                    Last,
    const GeomAbs_Shape                             Continuity,
    const int                                       MaxDeg,
    const int                                       MaxSeg,
    const AdvApprox_EvaluatorFunction&              Func);

  //! Approximation with user methode of cutting
  Standard_EXPORT AdvApprox_ApproxAFunction(
    const int                                       Num1DSS,
    const int                                       Num2DSS,
    const int                                       Num3DSS,
    const occ::handle<NCollection_HArray1<double>>& OneDTol,
    const occ::handle<NCollection_HArray1<double>>& TwoDTol,
    const occ::handle<NCollection_HArray1<double>>& ThreeDTol,
    const double                                    First,
    const double                                    Last,
    const GeomAbs_Shape                             Continuity,
    const int                                       MaxDeg,
    const int                                       MaxSeg,
    const AdvApprox_EvaluatorFunction&              Func,
    const AdvApprox_Cutting&                        CutTool);

  Standard_EXPORT static void Approximation(const int                         TotalDimension,
                                            const int                         TotalNumSS,
                                            const NCollection_Array1<int>&    LocalDimension,
                                            const double                      First,
                                            const double                      Last,
                                            AdvApprox_EvaluatorFunction&      Evaluator,
                                            const AdvApprox_Cutting&          CutTool,
                                            const int                         ContinuityOrder,
                                            const int                         NumMaxCoeffs,
                                            const int                         MaxSegments,
                                            const NCollection_Array1<double>& TolerancesArray,
                                            const int                         code_precis,
                                            int&                              NumCurves,
                                            NCollection_Array1<int>&          NumCoeffPerCurveArray,
                                            NCollection_Array1<double>&       LocalCoefficientArray,
                                            NCollection_Array1<double>&       IntervalsArray,
                                            NCollection_Array1<double>&       ErrorMaxArray,
                                            NCollection_Array1<double>&       AverageErrorArray,
                                            int&                              ErrorCode);

  bool IsDone() const;

  bool HasResult() const;

  //! returns the poles from the algorithms as is
  occ::handle<NCollection_HArray2<double>> Poles1d() const;

  //! returns the poles from the algorithms as is
  occ::handle<NCollection_HArray2<gp_Pnt2d>> Poles2d() const;

  //! -- returns the poles from the algorithms as is
  occ::handle<NCollection_HArray2<gp_Pnt>> Poles() const;

  //! as the name says
  Standard_EXPORT int NbPoles() const;

  //! returns the poles at Index from the 1d subspace
  Standard_EXPORT void Poles1d(const int Index, NCollection_Array1<double>& P) const;

  //! returns the poles at Index from the 2d subspace
  Standard_EXPORT void Poles2d(const int Index, NCollection_Array1<gp_Pnt2d>& P) const;

  //! returns the poles at Index from the 3d subspace
  Standard_EXPORT void Poles(const int Index, NCollection_Array1<gp_Pnt>& P) const;

  int Degree() const;

  int NbKnots() const;

  int NumSubSpaces(const int Dimension) const;

  occ::handle<NCollection_HArray1<double>> Knots() const;

  occ::handle<NCollection_HArray1<int>> Multiplicities() const;

  //! returns the error as is in the algorithms
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> MaxError(const int Dimension) const;

  //! returns the error as is in the algorithms
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> AverageError(const int Dimension) const;

  Standard_EXPORT double MaxError(const int Dimension, const int Index) const;

  Standard_EXPORT double AverageError(const int Dimension, const int Index) const;

  //! display information on approximation.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  Standard_EXPORT void Perform(const int                Num1DSS,
                               const int                Num2DSS,
                               const int                Num3DSS,
                               const AdvApprox_Cutting& CutTool);

  int                                        myNumSubSpaces[3];
  occ::handle<NCollection_HArray1<double>>   my1DTolerances;
  occ::handle<NCollection_HArray1<double>>   my2DTolerances;
  occ::handle<NCollection_HArray1<double>>   my3DTolerances;
  double                                     myFirst;
  double                                     myLast;
  GeomAbs_Shape                              myContinuity;
  int                                        myMaxDegree;
  int                                        myMaxSegments;
  bool                                       myDone;
  bool                                       myHasResult;
  occ::handle<NCollection_HArray2<double>>   my1DPoles;
  occ::handle<NCollection_HArray2<gp_Pnt2d>> my2DPoles;
  occ::handle<NCollection_HArray2<gp_Pnt>>   my3DPoles;
  occ::handle<NCollection_HArray1<double>>   myKnots;
  occ::handle<NCollection_HArray1<int>>      myMults;
  int                                        myDegree;
  void*                                      myEvaluator;
  occ::handle<NCollection_HArray1<double>>   my1DMaxError;
  occ::handle<NCollection_HArray1<double>>   my1DAverageError;
  occ::handle<NCollection_HArray1<double>>   my2DMaxError;
  occ::handle<NCollection_HArray1<double>>   my2DAverageError;
  occ::handle<NCollection_HArray1<double>>   my3DMaxError;
  occ::handle<NCollection_HArray1<double>>   my3DAverageError;
};

#include <Standard_ConstructionError.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

//=================================================================================================

inline bool AdvApprox_ApproxAFunction::HasResult() const
{
  return myHasResult;
}

//=================================================================================================

inline bool AdvApprox_ApproxAFunction::IsDone() const
{
  return myDone;
}

//=================================================================================================

inline occ::handle<NCollection_HArray2<double>> AdvApprox_ApproxAFunction::Poles1d() const
{
  return my1DPoles;
}

//=================================================================================================

inline occ::handle<NCollection_HArray2<gp_Pnt2d>> AdvApprox_ApproxAFunction::Poles2d() const
{
  return my2DPoles;
}

//=================================================================================================

inline occ::handle<NCollection_HArray2<gp_Pnt>> AdvApprox_ApproxAFunction::Poles() const
{
  return my3DPoles;
}

//=================================================================================================

inline int AdvApprox_ApproxAFunction::Degree() const
{
  return myDegree;
}

//=================================================================================================

inline int AdvApprox_ApproxAFunction::NbKnots() const
{
  return myKnots->Length();
}

//=================================================================================================

inline occ::handle<NCollection_HArray1<double>> AdvApprox_ApproxAFunction::Knots() const

{
  return myKnots;
}

//=================================================================================================

inline occ::handle<NCollection_HArray1<int>> AdvApprox_ApproxAFunction::Multiplicities() const

{
  return myMults;
}

//=================================================================================================

inline int AdvApprox_ApproxAFunction::NumSubSpaces(const int Dimension) const
{
  if (Dimension < 1 || Dimension > 3)
    throw Standard_ConstructionError();
  return myNumSubSpaces[Dimension - 1];
}
