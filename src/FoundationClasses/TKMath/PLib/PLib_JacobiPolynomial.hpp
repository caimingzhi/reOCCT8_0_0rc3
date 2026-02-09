#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>

class PLib_JacobiPolynomial
{

public:
  Standard_EXPORT PLib_JacobiPolynomial(const int           theWorkDegree,
                                        const GeomAbs_Shape theConstraintOrder);

  Standard_EXPORT void Points(const int                   theNbGaussPoints,
                              NCollection_Array1<double>& theTabPoints) const;

  Standard_EXPORT void Weights(const int                   theNbGaussPoints,
                               NCollection_Array2<double>& theTabWeights) const;

  Standard_EXPORT void MaxValue(NCollection_Array1<double>& theTabMax) const;

  Standard_EXPORT double MaxError(const int theDimension,
                                  double&   theJacCoeff,
                                  const int theNewDegree) const;

  Standard_EXPORT void ReduceDegree(const int    theDimension,
                                    const int    theMaxDegree,
                                    const double theTol,
                                    double&      theJacCoeff,
                                    int&         theNewDegree,
                                    double&      theMaxError) const;

  Standard_EXPORT double AverageError(const int theDimension,
                                      double&   theJacCoeff,
                                      const int theNewDegree) const;

  Standard_EXPORT void ToCoefficients(const int                         theDimension,
                                      const int                         theDegree,
                                      const NCollection_Array1<double>& theJacCoeff,
                                      NCollection_Array1<double>&       theCoefficients) const;

  Standard_EXPORT void D0(const double theU, NCollection_Array1<double>& theBasisValue) const;

  Standard_EXPORT void D1(const double                theU,
                          NCollection_Array1<double>& theBasisValue,
                          NCollection_Array1<double>& theBasisD1) const;

  Standard_EXPORT void D2(const double                theU,
                          NCollection_Array1<double>& theBasisValue,
                          NCollection_Array1<double>& theBasisD1,
                          NCollection_Array1<double>& theBasisD2) const;

  Standard_EXPORT void D3(const double                theU,
                          NCollection_Array1<double>& theBasisValue,
                          NCollection_Array1<double>& theBasisD1,
                          NCollection_Array1<double>& theBasisD2,
                          NCollection_Array1<double>& theBasisD3) const;

  int WorkDegree() const noexcept { return myWorkDegree; }

  int NivConstr() const noexcept { return myNivConstr; }

protected:
  Standard_EXPORT void D0123(const int                   theNDeriv,
                             const double                theU,
                             NCollection_Array1<double>& theBasisValue,
                             NCollection_Array1<double>& theBasisD1,
                             NCollection_Array1<double>& theBasisD2,
                             NCollection_Array1<double>& theBasisD3) const;

private:
  const int myWorkDegree;
  const int myNivConstr;
  const int myDegree;
};
