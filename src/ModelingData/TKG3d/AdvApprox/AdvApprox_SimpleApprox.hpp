#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <GeomAbs_Shape.hpp>
#include <AdvApprox_EvaluatorFunction.hpp>
#include <Standard_OStream.hpp>
#include <PLib_JacobiPolynomial.hpp>

class AdvApprox_SimpleApprox
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AdvApprox_SimpleApprox(const int                          TotalDimension,
                                         const int                          TotalNumSS,
                                         const GeomAbs_Shape                Continuity,
                                         const int                          WorkDegree,
                                         const int                          NbGaussPoints,
                                         const PLib_JacobiPolynomial&       JacobiBase,
                                         const AdvApprox_EvaluatorFunction& Func);

  Standard_EXPORT void Perform(const NCollection_Array1<int>&    LocalDimension,
                               const NCollection_Array1<double>& LocalTolerancesArray,
                               const double                      First,
                               const double                      Last,
                               const int                         MaxDegree);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int Degree() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Coefficients() const;

  Standard_EXPORT occ::handle<NCollection_HArray2<double>> FirstConstr() const;

  Standard_EXPORT occ::handle<NCollection_HArray2<double>> LastConstr() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> SomTab() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> DifTab() const;

  Standard_EXPORT double MaxError(const int Index) const;

  Standard_EXPORT double AverageError(const int Index) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  int                                      myTotalNumSS;
  int                                      myTotalDimension;
  int                                      myNbGaussPoints;
  int                                      myWorkDegree;
  int                                      myNivConstr;
  PLib_JacobiPolynomial                    myJacPol;
  occ::handle<NCollection_HArray1<double>> myTabPoints;
  occ::handle<NCollection_HArray2<double>> myTabWeights;
  void*                                    myEvaluator;
  int                                      myDegree;
  occ::handle<NCollection_HArray1<double>> myCoeff;
  occ::handle<NCollection_HArray2<double>> myFirstConstr;
  occ::handle<NCollection_HArray2<double>> myLastConstr;
  occ::handle<NCollection_HArray1<double>> mySomTab;
  occ::handle<NCollection_HArray1<double>> myDifTab;
  occ::handle<NCollection_HArray1<double>> myMaxError;
  occ::handle<NCollection_HArray1<double>> myAverageError;
  bool                                     done;
};
