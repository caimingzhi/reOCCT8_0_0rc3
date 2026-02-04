#pragma once


#include <CPnts_AbscissaPoint.hpp>

class Adaptor3d_Curve;
class Adaptor2d_Curve2d;

//! Provides an algorithm to compute a point on a curve
//! situated at a given distance from another point on the curve,
//! the distance being measured along the curve (curvilinear abscissa on the curve).
//! This algorithm is also used to compute the length of a curve.
//! An AbscissaPoint object provides a framework for:
//! -   defining the point to compute
//! -   implementing the construction algorithm
//! -   consulting the result.
class GCPnts_AbscissaPoint
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the length of the 3D Curve.
  Standard_EXPORT static double Length(const Adaptor3d_Curve& theC);

  //! Computes the length of the 2D Curve.
  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& theC);

  //! Computes the length of the 3D Curve with the given tolerance.
  Standard_EXPORT static double Length(const Adaptor3d_Curve& theC, const double theTol);

  //! Computes the length of the 2D Curve with the given tolerance.
  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& theC, const double theTol);

  //! Computes the length of the 3D Curve.
  Standard_EXPORT static double Length(const Adaptor3d_Curve& theC,
                                       const double           theU1,
                                       const double           theU2);

  //! Computes the length of the 2D Curve.
  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& theC,
                                       const double             theU1,
                                       const double             theU2);

  //! Computes the length of the 3D Curve with the given tolerance.
  Standard_EXPORT static double Length(const Adaptor3d_Curve& theC,
                                       const double           theU1,
                                       const double           theU2,
                                       const double           theTol);

  //! Computes the length of the Curve with the given tolerance.
  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& theC,
                                       const double             theU1,
                                       const double             theU2,
                                       const double             theTol);

public:
  //! Empty constructor.
  Standard_EXPORT GCPnts_AbscissaPoint();

  //! The algorithm computes a point on a curve at the
  //! distance theAbscissa from the point of parameter theU0.
  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor3d_Curve& theC,
                                       const double           theAbscissa,
                                       const double           theU0);

  //! The algorithm computes a point on a curve at
  //! the distance theAbscissa from the point of parameter
  //! theU0 with the given tolerance.
  Standard_EXPORT GCPnts_AbscissaPoint(const double           theTol,
                                       const Adaptor3d_Curve& theC,
                                       const double           theAbscissa,
                                       const double           theU0);

  //! The algorithm computes a point on a curve at
  //! the distance theAbscissa from the point of parameter
  //! theU0 with the given tolerance.
  Standard_EXPORT GCPnts_AbscissaPoint(const double             theTol,
                                       const Adaptor2d_Curve2d& theC,
                                       const double             theAbscissa,
                                       const double             theU0);

  //! The algorithm computes a point on a curve at the
  //! distance theAbscissa from the point of parameter theU0.
  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor2d_Curve2d& theC,
                                       const double             theAbscissa,
                                       const double             theU0);

  //! The algorithm computes a point on a curve at the
  //! distance theAbscissa from the point of parameter theU0.
  //! theUi is the starting value used in the iterative process
  //! which find the solution, it must be close to the final solution.
  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor3d_Curve& theC,
                                       const double           theAbscissa,
                                       const double           theU0,
                                       const double           theUi);

  //! The algorithm computes a point on a curve at the
  //! distance theAbscissa from the point of parameter theU0.
  //! theUi is the starting value used in the iterative process
  //! which find the solution, it must be closed to the final solution
  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor2d_Curve2d& theC,
                                       const double             theAbscissa,
                                       const double             theU0,
                                       const double             theUi);

  //! The algorithm computes a point on a curve at the
  //! distance theAbscissa from the point of parameter theU0.
  //! theUi is the starting value used in the iterative process
  //! which find the solution, it must be close to the final solution
  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor3d_Curve& theC,
                                       const double           theAbscissa,
                                       const double           theU0,
                                       const double           theUi,
                                       const double           theTol);

  //! The algorithm computes a point on a curve at the
  //! distance theAbscissa from the point of parameter theU0.
  //! theUi is the starting value used in the iterative process
  //! which find the solution, it must be close to the final solution
  Standard_EXPORT GCPnts_AbscissaPoint(const Adaptor2d_Curve2d& theC,
                                       const double             theAbscissa,
                                       const double             theU0,
                                       const double             theUi,
                                       const double             theTol);

  //! True if the computation was successful, False otherwise.
  //! IsDone is a protection against:
  //! -   non-convergence of the algorithm
  //! -   querying the results before computation.
  bool IsDone() const { return myComputer.IsDone(); }

  //! Returns the parameter on the curve of the point
  //! solution of this algorithm.
  //! Exceptions
  //! StdFail_NotDone if the computation was not
  //! successful, or was not done.
  double Parameter() const { return myComputer.Parameter(); }

private:
  //! Computes the length of the Curve with the optional tolerance.
  template <class TheCurve>
  static double length(const TheCurve& theC,
                       const double    theU1,
                       const double    theU2,
                       const double*   theTol);

  //! Performs algorithm from the point of parameter.
  template <class TheCurve>
  void compute(const TheCurve& theC, const double theAbscissa, const double theU0);

  //! Performs algorithm from the point of parameter with the given tolerance.
  template <class TheCurve>
  void advCompute(const double    theTol,
                  const TheCurve& theC,
                  const double    theAbscissa,
                  const double    theU0);

private:
  CPnts_AbscissaPoint myComputer;
};

