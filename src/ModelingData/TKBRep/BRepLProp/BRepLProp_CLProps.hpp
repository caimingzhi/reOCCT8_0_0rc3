#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepAdaptor_Curve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>
#include <LProp_Status.hpp>
class LProp_BadContinuity;
class Standard_DomainError;
class Standard_OutOfRange;
class LProp_NotDefined;
class BRepAdaptor_Curve;
class gp_Vec;
class gp_Pnt;
class gp_Dir;
class BRepLProp_CurveTool;

class BRepLProp_CLProps
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initializes the local properties of the curve <C>
  //! The current point and the derivatives are
  //! computed at the same time, which allows an
  //! optimization of the computation time.
  //! <N> indicates the maximum number of derivations to
  //! be done (0, 1, 2 or 3). For example, to compute
  //! only the tangent, N should be equal to 1.
  //! <Resolution> is the linear tolerance (it is used to test
  //! if a vector is null).
  Standard_EXPORT BRepLProp_CLProps(const BRepAdaptor_Curve& C,
                                    const int                N,
                                    const double             Resolution);

  //! Same as previous constructor but here the parameter is
  //! set to the value <U>.
  //! All the computations done will be related to <C> and <U>.
  Standard_EXPORT BRepLProp_CLProps(const BRepAdaptor_Curve& C,
                                    const double             U,
                                    const int                N,
                                    const double             Resolution);

  //! Same as previous constructor but here the parameter is
  //! set to the value <U> and the curve is set
  //! with SetCurve.
  //! the curve can have a empty constructor
  //! All the computations done will be related to <C> and <U>
  //! when the functions "set" will be done.
  Standard_EXPORT BRepLProp_CLProps(const int N, const double Resolution);

  //! Initializes the local properties of the curve
  //! for the parameter value <U>.
  Standard_EXPORT void SetParameter(const double U);

  //! Initializes the local properties of the curve
  //! for the new curve.
  Standard_EXPORT void SetCurve(const BRepAdaptor_Curve& C);

  //! Returns the Point.
  Standard_EXPORT const gp_Pnt& Value() const;

  //! Returns the first derivative.
  //! The derivative is computed if it has not been yet.
  Standard_EXPORT const gp_Vec& D1();

  //! Returns the second derivative.
  //! The derivative is computed if it has not been yet.
  Standard_EXPORT const gp_Vec& D2();

  //! Returns the third derivative.
  //! The derivative is computed if it has not been yet.
  Standard_EXPORT const gp_Vec& D3();

  //! Returns True if the tangent is defined.
  //! For example, the tangent is not defined if the
  //! three first derivatives are all null.
  Standard_EXPORT bool IsTangentDefined();

  //! output the tangent direction <D>
  Standard_EXPORT void Tangent(gp_Dir& D);

  //! Returns the curvature.
  Standard_EXPORT double Curvature();

  //! Returns the normal direction <N>.
  Standard_EXPORT void Normal(gp_Dir& N);

  //! Returns the centre of curvature <P>.
  Standard_EXPORT void CentreOfCurvature(gp_Pnt& P);

private:
  BRepAdaptor_Curve myCurve;
  double            myU;
  int               myDerOrder;
  double            myCN;
  double            myLinTol;
  gp_Pnt            myPnt;
  gp_Vec            myDerivArr[3];
  gp_Dir            myTangent;
  double            myCurvature;
  LProp_Status      myTangentStatus;
  int               mySignificantFirstDerivativeOrder;
};

