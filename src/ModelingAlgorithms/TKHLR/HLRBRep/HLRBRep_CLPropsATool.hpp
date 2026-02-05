#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class gp_Pnt2d;
class gp_Vec2d;

class HLRBRep_CLPropsATool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the point <P> of parameter <U> on the
  //! Curve from HLRBRep <C>.
  static void Value(const HLRBRep_Curve* A, const double U, gp_Pnt2d& P);

  //! Computes the point <P> and first derivative <V1>
  //! of parameter <U> on the curve <C>.
  static void D1(const HLRBRep_Curve* A, const double U, gp_Pnt2d& P, gp_Vec2d& V1);

  //! Computes the point <P>, the first derivative <V1>
  //! and second derivative <V2> of parameter <U> on the
  //! curve <C>.
  static void D2(const HLRBRep_Curve* A, const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2);

  //! Computes the point <P>, the first derivative <V1>,
  //! the second derivative <V2> and third derivative
  //! <V3> of parameter <U> on the curve <C>.
  static void D3(const HLRBRep_Curve* A,
                 const double         U,
                 gp_Pnt2d&            P,
                 gp_Vec2d&            V1,
                 gp_Vec2d&            V2,
                 gp_Vec2d&            V3);

  //! returns the order of continuity of the curve <C>.
  //! returns 1: first derivative only is computable.
  //! returns 2: first and second derivative only are computable.
  //! returns 3: first, second and third are computable.
  static int Continuity(const HLRBRep_Curve* A);

  //! returns the first parameter bound of the curve.
  static double FirstParameter(const HLRBRep_Curve* A);

  //! returns the last parameter bound of the curve.
  //! FirstParameter must be less than LastParamenter.
  static double LastParameter(const HLRBRep_Curve* A);
};

#include <Standard_NotImplemented.hpp>
#include <HLRBRep_Curve.hpp>
#include <GeomAbs_Shape.hpp>

//=================================================================================================

inline void HLRBRep_CLPropsATool::Value(const HLRBRep_Curve* A, const double U, gp_Pnt2d& P)
{
  P = A->Value(U);
}

//=================================================================================================

inline void HLRBRep_CLPropsATool::D1(const HLRBRep_Curve* A,
                                     const double         U,
                                     gp_Pnt2d&            P,
                                     gp_Vec2d&            V1)
{
  A->D1(U, P, V1);
}

//=================================================================================================

inline void HLRBRep_CLPropsATool::D2(const HLRBRep_Curve* A,
                                     const double         U,
                                     gp_Pnt2d&            P,
                                     gp_Vec2d&            V1,
                                     gp_Vec2d&            V2)
{
  A->D2(U, P, V1, V2);
}

//=================================================================================================

inline void HLRBRep_CLPropsATool::D3(const HLRBRep_Curve* A,
                                     const double         U,
                                     gp_Pnt2d&            P,
                                     gp_Vec2d&            V1,
                                     gp_Vec2d&            V2,
                                     gp_Vec2d&            V3)
{
  A->D3(U, P, V1, V2, V3);
}

//=================================================================================================

inline int HLRBRep_CLPropsATool::Continuity(const HLRBRep_Curve*)
{
  return GeomAbs_C2;
}

//=================================================================================================

inline double HLRBRep_CLPropsATool::FirstParameter(const HLRBRep_Curve* A)
{
  return A->FirstParameter();
}

//=================================================================================================

inline double HLRBRep_CLPropsATool::LastParameter(const HLRBRep_Curve* A)
{
  return A->LastParameter();
}
