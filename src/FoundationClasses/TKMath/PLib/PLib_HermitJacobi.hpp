#pragma once

#include <Standard.hpp>

#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <PLib_JacobiPolynomial.hpp>

class PLib_HermitJacobi
{

public:
  Standard_EXPORT PLib_HermitJacobi(const int WorkDegree, const GeomAbs_Shape ConstraintOrder);

  Standard_EXPORT double MaxError(const int Dimension,
                                  double&   HermJacCoeff,
                                  const int NewDegree) const;

  Standard_EXPORT void ReduceDegree(const int    Dimension,
                                    const int    MaxDegree,
                                    const double Tol,
                                    double&      HermJacCoeff,
                                    int&         NewDegree,
                                    double&      MaxError) const;

  Standard_EXPORT double AverageError(const int Dimension,
                                      double&   HermJacCoeff,
                                      const int NewDegree) const;

  Standard_EXPORT void ToCoefficients(const int                         Dimension,
                                      const int                         Degree,
                                      const NCollection_Array1<double>& HermJacCoeff,
                                      NCollection_Array1<double>&       Coefficients) const;

  Standard_EXPORT void D0(const double U, NCollection_Array1<double>& BasisValue) const;

  Standard_EXPORT void D1(const double                U,
                          NCollection_Array1<double>& BasisValue,
                          NCollection_Array1<double>& BasisD1) const;

  Standard_EXPORT void D2(const double                U,
                          NCollection_Array1<double>& BasisValue,
                          NCollection_Array1<double>& BasisD1,
                          NCollection_Array1<double>& BasisD2) const;

  Standard_EXPORT void D3(const double                U,
                          NCollection_Array1<double>& BasisValue,
                          NCollection_Array1<double>& BasisD1,
                          NCollection_Array1<double>& BasisD2,
                          NCollection_Array1<double>& BasisD3) const;

  int WorkDegree() const noexcept { return myJacobi.WorkDegree(); }

  int NivConstr() const noexcept { return myJacobi.NivConstr(); }

protected:
  Standard_EXPORT void D0123(const int                   NDerive,
                             const double                U,
                             NCollection_Array1<double>& BasisValue,
                             NCollection_Array1<double>& BasisD1,
                             NCollection_Array1<double>& BasisD2,
                             NCollection_Array1<double>& BasisD3) const;

private:
  const PLib_JacobiPolynomial myJacobi;
};
