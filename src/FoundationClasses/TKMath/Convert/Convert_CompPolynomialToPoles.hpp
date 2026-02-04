#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

//! Convert a serie of Polynomial N-Dimensional Curves
//! that are have continuity CM to an N-Dimensional Bspline Curve
//! that has continuity CM.
//! (to convert an function (curve) polynomial by span in a BSpline)
//! This class uses the following arguments :
//! NumCurves :  the number of Polynomial Curves
//! Continuity:  the requested continuity for the n-dimensional Spline
//! Dimension :  the dimension of the Spline
//! MaxDegree :  maximum allowed degree for each composite
//! polynomial segment.
//! NumCoeffPerCurve : the number of coefficient per segments = degree - 1
//! Coefficients  :  the coefficients organized in the following way
//! [1..<myNumPolynomials>][1..myMaxDegree +1][1..myDimension]
//! that is : index [n,d,i] is at slot
//! (n-1) * (myMaxDegree + 1) * myDimension + (d-1) * myDimension + i
//! PolynomialIntervals :  nth polynomial represents a polynomial between
//! myPolynomialIntervals->Value(n,0) and
//! myPolynomialIntervals->Value(n,1)
//! TrueIntervals : the nth polynomial has to be mapped linearly to be
//! defined on the following interval :
//! myTrueIntervals->Value(n) and myTrueIntervals->Value(n+1)
//! so that it adequately represents the function with the
//! required continuity
class Convert_CompPolynomialToPoles
{
public:
  DEFINE_STANDARD_ALLOC

  //! Warning!
  //! Continuity can be at MOST the maximum degree of
  //! the polynomial functions
  //! TrueIntervals :
  //! this is the true parameterisation for the composite curve
  //! that is : the curve has myContinuity if the nth curve
  //! is parameterized between myTrueIntervals(n) and myTrueIntervals(n+1)
  //!
  //! Coefficients have to be the implicit "c form":
  //! Coefficients[Numcurves][MaxDegree+1][Dimension]
  //!
  //! Warning!
  //! The NumberOfCoefficient of an polynome is his degree + 1
  //! Example: To convert the linear function f(x) = 2*x + 1 on the
  //! domaine [2,5] to BSpline with the bound [-1,1]. Arguments are :
  //! NumCurves  = 1;
  //! Continuity = 1;
  //! Dimension  = 1;
  //! MaxDegree  = 1;
  //! NumCoeffPerCurve [1] = {2};
  //! Coefficients[2] = {1, 2};
  //! PolynomialIntervals[1,2] = {{2,5}}
  //! TrueIntervals[2] = {-1, 1}
  Standard_EXPORT Convert_CompPolynomialToPoles(
    const int                                       NumCurves,
    const int                                       Continuity,
    const int                                       Dimension,
    const int                                       MaxDegree,
    const occ::handle<NCollection_HArray1<int>>&    NumCoeffPerCurve,
    const occ::handle<NCollection_HArray1<double>>& Coefficients,
    const occ::handle<NCollection_HArray2<double>>& PolynomialIntervals,
    const occ::handle<NCollection_HArray1<double>>& TrueIntervals);

  //! To Convert several span with different order of Continuity.
  //! Warning: The Length of Continuity have to be NumCurves-1
  Standard_EXPORT Convert_CompPolynomialToPoles(
    const int                         NumCurves,
    const int                         Dimension,
    const int                         MaxDegree,
    const NCollection_Array1<int>&    Continuity,
    const NCollection_Array1<int>&    NumCoeffPerCurve,
    const NCollection_Array1<double>& Coefficients,
    const NCollection_Array2<double>& PolynomialIntervals,
    const NCollection_Array1<double>& TrueIntervals);

  //! To Convert only one span.
  Standard_EXPORT Convert_CompPolynomialToPoles(
    const int                         Dimension,
    const int                         MaxDegree,
    const int                         Degree,
    const NCollection_Array1<double>& Coefficients,
    const NCollection_Array1<double>& PolynomialIntervals,
    const NCollection_Array1<double>& TrueIntervals);

  //! number of poles of the n-dimensional BSpline
  Standard_EXPORT int NbPoles() const;

  //! returns the poles of the n-dimensional BSpline
  //! in the following format :
  //! [1..NumPoles][1..Dimension]
  Standard_EXPORT void Poles(occ::handle<NCollection_HArray2<double>>& Poles) const;

  Standard_EXPORT int Degree() const;

  //! Degree of the n-dimensional Bspline
  Standard_EXPORT int NbKnots() const;

  //! Knots of the n-dimensional Bspline
  Standard_EXPORT void Knots(occ::handle<NCollection_HArray1<double>>& K) const;

  //! Multiplicities of the knots in the BSpline
  Standard_EXPORT void Multiplicities(occ::handle<NCollection_HArray1<int>>& M) const;

  Standard_EXPORT bool IsDone() const;

private:
  Standard_EXPORT void Perform(const int                         NumCurves,
                               const int                         MaxDegree,
                               const int                         Dimension,
                               const NCollection_Array1<int>&    NumCoeffPerCurve,
                               const NCollection_Array1<double>& Coefficients,
                               const NCollection_Array2<double>& PolynomialIntervals,
                               const NCollection_Array1<double>& TrueIntervals);

  occ::handle<NCollection_HArray1<double>> myFlatKnots;
  occ::handle<NCollection_HArray1<double>> myKnots;
  occ::handle<NCollection_HArray1<int>>    myMults;
  occ::handle<NCollection_HArray2<double>> myPoles;
  int                                      myDegree;
  bool                                     myDone;
};

