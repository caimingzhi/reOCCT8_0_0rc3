#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <Standard_Real.hpp>
class gp_Pnt;
class gp_Vec;

class HLRBRep_SLPropsATool
{
public:
  DEFINE_STANDARD_ALLOC

  static void Value(const HLRBRep_SurfacePtr A, const double U, const double V, gp_Pnt& P);

  static void D1(const HLRBRep_SurfacePtr A,
                 const double             U,
                 const double             V,
                 gp_Pnt&                  P,
                 gp_Vec&                  D1U,
                 gp_Vec&                  D1V);

  static void D2(const HLRBRep_SurfacePtr A,
                 const double             U,
                 const double             V,
                 gp_Pnt&                  P,
                 gp_Vec&                  D1U,
                 gp_Vec&                  D1V,
                 gp_Vec&                  D2U,
                 gp_Vec&                  D2V,
                 gp_Vec&                  DUV);

  static gp_Vec DN(const HLRBRep_SurfacePtr A,
                   const double             U,
                   const double             V,
                   const int                Nu,
                   const int                Nv);

  static int Continuity(const HLRBRep_SurfacePtr A);

  static void Bounds(const HLRBRep_SurfacePtr A, double& U1, double& V1, double& U2, double& V2);
};

#include <HLRBRep_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Pnt.hpp>

inline void HLRBRep_SLPropsATool::Value(const HLRBRep_SurfacePtr A,
                                        const double             U,
                                        const double             V,
                                        gp_Pnt&                  P)
{
  P = ((HLRBRep_Surface*)A)->Value(U, V);
}

inline void HLRBRep_SLPropsATool::D1(const HLRBRep_SurfacePtr A,
                                     const double             U,
                                     const double             V,
                                     gp_Pnt&                  P,
                                     gp_Vec&                  D1U,
                                     gp_Vec&                  D1V)
{
  ((HLRBRep_Surface*)A)->D1(U, V, P, D1U, D1V);
}

inline void HLRBRep_SLPropsATool::D2(const HLRBRep_SurfacePtr A,
                                     const double             U,
                                     const double             V,
                                     gp_Pnt&                  P,
                                     gp_Vec&                  D1U,
                                     gp_Vec&                  D1V,
                                     gp_Vec&                  D2U,
                                     gp_Vec&                  D2V,
                                     gp_Vec&                  DUV)
{
  ((HLRBRep_Surface*)A)->D2(U, V, P, D1U, D1V, D2U, D2V, DUV);
}

inline gp_Vec HLRBRep_SLPropsATool::DN(const HLRBRep_SurfacePtr A,
                                       const double             U,
                                       const double             V,
                                       const int                Nu,
                                       const int                Nv)
{
  return ((HLRBRep_Surface*)A)->DN(U, V, Nu, Nv);
}

inline int HLRBRep_SLPropsATool::Continuity(const HLRBRep_SurfacePtr)
{
  return 2;
}

inline void HLRBRep_SLPropsATool::Bounds(const HLRBRep_SurfacePtr,
                                         double& U1,
                                         double& V1,
                                         double& U2,
                                         double& V2)
{
  U1 = V1 = RealFirst();
  U2 = V2 = RealLast();
}
