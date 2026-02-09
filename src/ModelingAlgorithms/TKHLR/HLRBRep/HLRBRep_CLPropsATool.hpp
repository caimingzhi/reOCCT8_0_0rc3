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

  static void Value(const HLRBRep_Curve* A, const double U, gp_Pnt2d& P);

  static void D1(const HLRBRep_Curve* A, const double U, gp_Pnt2d& P, gp_Vec2d& V1);

  static void D2(const HLRBRep_Curve* A, const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2);

  static void D3(const HLRBRep_Curve* A,
                 const double         U,
                 gp_Pnt2d&            P,
                 gp_Vec2d&            V1,
                 gp_Vec2d&            V2,
                 gp_Vec2d&            V3);

  static int Continuity(const HLRBRep_Curve* A);

  static double FirstParameter(const HLRBRep_Curve* A);

  static double LastParameter(const HLRBRep_Curve* A);
};

#include <Standard_NotImplemented.hpp>
#include <HLRBRep_Curve.hpp>
#include <GeomAbs_Shape.hpp>

inline void HLRBRep_CLPropsATool::Value(const HLRBRep_Curve* A, const double U, gp_Pnt2d& P)
{
  P = A->Value(U);
}

inline void HLRBRep_CLPropsATool::D1(const HLRBRep_Curve* A,
                                     const double         U,
                                     gp_Pnt2d&            P,
                                     gp_Vec2d&            V1)
{
  A->D1(U, P, V1);
}

inline void HLRBRep_CLPropsATool::D2(const HLRBRep_Curve* A,
                                     const double         U,
                                     gp_Pnt2d&            P,
                                     gp_Vec2d&            V1,
                                     gp_Vec2d&            V2)
{
  A->D2(U, P, V1, V2);
}

inline void HLRBRep_CLPropsATool::D3(const HLRBRep_Curve* A,
                                     const double         U,
                                     gp_Pnt2d&            P,
                                     gp_Vec2d&            V1,
                                     gp_Vec2d&            V2,
                                     gp_Vec2d&            V3)
{
  A->D3(U, P, V1, V2, V3);
}

inline int HLRBRep_CLPropsATool::Continuity(const HLRBRep_Curve*)
{
  return GeomAbs_C2;
}

inline double HLRBRep_CLPropsATool::FirstParameter(const HLRBRep_Curve* A)
{
  return A->FirstParameter();
}

inline double HLRBRep_CLPropsATool::LastParameter(const HLRBRep_Curve* A)
{
  return A->LastParameter();
}
